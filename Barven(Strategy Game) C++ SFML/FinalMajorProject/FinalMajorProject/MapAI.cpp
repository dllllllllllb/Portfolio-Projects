#include "MapAI.h"

namespace settings = MapAISettings;

MapAI::MapAI(DataHandler& rDataHandler, PlayerHandler& rPlayerHandler, TurnHandler& rTurnHandler, CombatHandler& rCombatHandler, MapHandler& rMapHandler, Town& rTown, SpecialBuildingInteractions& rSpecialBuildingInteractions) :
	m_dataHandler(rDataHandler),
	m_playerHandler(rPlayerHandler),
	m_turnHandler(rTurnHandler),
	m_combatHandler(rCombatHandler),
	m_mapHandler(rMapHandler),
	m_town(rTown),
	m_specialBuildingsInteractions(rSpecialBuildingInteractions),
	m_pTileHandler(nullptr),
	m_playerIndex(0),
	m_isCombatInitiated(false),
	m_wasPrioSetThisTurn(false)
{
	setUpMapObjectsPointers();

	m_mapHandler.setMakeNewAIPlayerDataFunction(std::bind(&MapAI::makeNewAIPlayerData, this, std::placeholders::_1));
	m_mapHandler.setAITakeTurnFunction(std::bind(&MapAI::takeTurn, this));
	m_mapHandler.setFunctionToCallWhenDeletingAIPlayer(std::bind(&MapAI::deleteAIPlayerData, this, std::placeholders::_1));

	m_pTileHandler = m_mapHandler.getTileHandlerPointer();
}

MapAI::~MapAI()
{
}

void MapAI::setUpMapObjectsPointers()
{
	m_pTownMapObjects = &m_mapHandler.getVectorOfTownMapObjects();
	m_pTownData = &m_mapHandler.getVectorOfTownDatas();
	m_pUnitMapObjects = &m_mapHandler.getVectorOfUnitMapObjects();
	m_pResourceMinesMapObjects = &m_mapHandler.getVectorOfResourceMineObjects();
	m_pResourceMapObjects = &m_mapHandler.getVectorOfResourceObjects();
	m_pSpecialBuildingsMapObjects = &m_mapHandler.getVectorOfSpecialBuildingMapObjects();
}

void MapAI::makeNewAIPlayerData(const int& playerIndex)
{
	m_AIPlayerData.push_back(std::unique_ptr<MapAIPlayerData>(new MapAIPlayerData()));
	m_AIPlayerData[m_AIPlayerData.size() - 1]->setPlayerIndex(playerIndex);
	m_AIPlayerData[m_AIPlayerData.size() - 1]->addNewAIHeroData();
}

void MapAI::takeTurn()
{
	m_playerIndex = m_turnHandler.getCurrentPlayerIndex();
	m_isCombatInitiated = false;
	int playerAIDataIndex = 0;
	for (auto& AIData : m_AIPlayerData)
	{
		if (AIData->getPlayerIndex() == m_playerIndex)
		{
			break;
		}
		playerAIDataIndex++;
	}

	MapAIPlayerData& playerAIData = *m_AIPlayerData[playerAIDataIndex];

	if (!m_wasPrioSetThisTurn)
	{
		determinePriorities(playerAIData);
	}

	int heroIndex = 0;
	for (auto& hero : m_playerHandler.getPlayer(m_playerIndex).getVectorOfOwnedHeroes())
	{
		if (hero->getCurrentMovementPoints() > 0)
		{
			makeAMove(heroIndex, *hero, playerAIData);
		}

		if (m_isCombatInitiated)
		{
			break;
		}
		heroIndex++;
	}

	if (!m_isCombatInitiated && didAIFinishItsTurn())
	{
		upgradeTownBuildings();
		m_mapHandler.nextTurn();
		m_wasPrioSetThisTurn = false;
	}
}

const bool MapAI::didAIFinishItsTurn()
{
	bool didAIFinishItsTurn = true;

	for (auto& hero : m_playerHandler.getPlayer(m_playerIndex).getVectorOfOwnedHeroes())
	{
		if (hero->getCurrentMovementPoints() > 0)
		{
			didAIFinishItsTurn = false;
			break;
		}
	}

	return didAIFinishItsTurn;
}

void MapAI::determinePriorities(MapAIPlayerData& playerAIData)
{
	m_wasPrioSetThisTurn = true;
	Player& playerReference = m_playerHandler.getPlayer(m_playerIndex);

	std::pair<MapAIPriorityEnum, int> priority = determineOverallPlayerPriority(playerAIData, playerReference); //First == Priority type, Second == Priority object index
	int heroIndex = 0;
	for (auto& hero : playerReference.getVectorOfOwnedHeroes())
	{
		if (priority.first != MapAIPriorityEnum::none)
		{
			playerAIData.getAIHeroData(heroIndex).resetPriority();
			playerAIData.getAIHeroData(heroIndex).setPriority(priority.first);
			if (priority.second >= 0)
			{
				playerAIData.getAIHeroData(heroIndex).setPriorityObjectIndex(priority.second);
			}
		}
		else
		{
			determineIndividualHeroPriority(*hero, heroIndex, playerReference, playerAIData);
		}
		heroIndex++;
	}

}

std::pair<MapAIPriorityEnum, int> MapAI::determineOverallPlayerPriority(MapAIPlayerData& AIPlayerData, Player& player)
{
	//Player priorities
	std::pair<MapAIPriorityEnum, int> priority; //First == Priority type, Second == Priority object index
	priority.first = MapAIPriorityEnum::none;
	priority.second = -1; //Negative to indicate no priority object index was set

	//Check if enemy is near your towns
	for (auto& enemyPlayer : m_playerHandler.getVectorOfPlayers())
	{
		if (enemyPlayer->getPlayerIndex() != m_playerIndex)
		{
			for (auto& enemyHero : enemyPlayer->getVectorOfOwnedHeroes())
			{
				for (int& ownedTownIndex : player.getVectorOfOwnedTownsIndexes())
				{
					if (getDistanceInTilesBetweenTwoPositions(enemyHero->getPosition(), m_pTownMapObjects->at(ownedTownIndex)->getPosition()) < HeroSettings::c_maxMovementRange)
					{
						int distance = getPathDistanceInTiles(m_pTileHandler->checkTileCollision(enemyHero->getPosition()), m_pTownMapObjects->at(ownedTownIndex)->getTileIndex());

						if (distance > 0 && distance <= HeroSettings::c_maxMovementRange)
						{
							priority.first = MapAIPriorityEnum::protectTown;
							priority.second = ownedTownIndex;
							break;
						}
					}
				}
			}
		}
	}

	//Check resources
	if (priority.first == MapAIPriorityEnum::none)
	{
		if (player.getResources().getResource(ResourcesEnum::gold) < settings::c_minimumGold)
		{
			priority.first = MapAIPriorityEnum::resourceGold;
		}
		else if (player.getResources().getResource(ResourcesEnum::wood) < settings::c_minimumWood)
		{
			priority.first = MapAIPriorityEnum::resourceWood;
		}
		else if (player.getResources().getResource(ResourcesEnum::stone) < settings::c_minumumStone)
		{
			priority.first = MapAIPriorityEnum::resourceStone;
		}
	}
	return priority;
}

void MapAI::determineIndividualHeroPriority(Hero& playerHero, const int& heroIndex, Player& player, MapAIPlayerData& AIPlayerData)
{
	//If priority is to attack town, check if AI still has stronger army
	if (AIPlayerData.getAIHeroData(heroIndex).getPriority() == MapAIPriorityEnum::attackEnemyTown)
	{
		//Town index
		int townOwnerIndex = m_pTownMapObjects->at(AIPlayerData.getAIHeroData(heroIndex).getPriorityObjectIndex())->getOwnerIndex();

		if (townOwnerIndex >= 0 && townOwnerIndex < m_playerHandler.getNumberOfPlayers()) //Make sure town is occupied by a player
		{
			if (getArmyStrength(playerHero.getVectorOfUnits()) < getPlayersTotalArmyStrength(townOwnerIndex))
			{
				AIPlayerData.getAIHeroData(heroIndex).resetPriority();
				findClosestTownToRecruitUnits(heroIndex, playerHero, AIPlayerData);
			}
		}
	}

	//Check if hero already has a priority set
	if (AIPlayerData.getAIHeroData(heroIndex).getPriority() == MapAIPriorityEnum::none)
	{
		bool wasHeroPrioritySet = false;
		int occupiedTileIndex = playerHero.getOccupiedTileIndex();

		//Check if hero is in town
		checkIfHeroIsInTownToRecruitUnits(occupiedTileIndex, player, heroIndex, AIPlayerData);

		//Check if enemy hero with weaker army is in range
		if (!wasHeroPrioritySet)
		{
			wasHeroPrioritySet = checkIfEnemyHeroWithWeakerArmyIsClose(playerHero, heroIndex, AIPlayerData);
		}

		//Search for closest object of interest
		if (!wasHeroPrioritySet)
		{
			wasHeroPrioritySet = findClosestMapObjectOfInterest(playerHero, heroIndex, AIPlayerData);
		}

		if (!wasHeroPrioritySet)
		{
			//Nothing to do this turn
			playerHero.setCurrentMovementPoints(0);
		}
	}
}

void MapAI::checkIfHeroIsInTownToRecruitUnits(const int& occupiedTileIndex, Player& player, const int& heroIndex, MapAIPlayerData& AIPlayerData)
{
	for (int& ownedTownsIndex : player.getVectorOfOwnedTownsIndexes())
	{
		if (m_pTownMapObjects->at(ownedTownsIndex)->getTileIndex() == occupiedTileIndex)
		{
			for (int& unitsToRecruit : m_pTownData->at(ownedTownsIndex)->getAvailableUnitsToRecruit())
			{
				if (unitsToRecruit > 0)
				{
					if (player.getResources().getResource(ResourcesEnum::gold) >= settings::c_minimumGold)
					{
						recruitUnitsAtTown(ownedTownsIndex);
						transferUnitsFromTownToHero(player.getHero(heroIndex), *m_pTownData->at(ownedTownsIndex));
					}
					break;
				}
			}
		}
	}
}

const bool MapAI::checkIfEnemyHeroWithWeakerArmyIsClose(Hero& playerHero, const int& playerHeroIndex, MapAIPlayerData& AIPlayerData)
{
	bool wasPrioSet = false;
	for (auto& enemyPlayer : m_playerHandler.getVectorOfPlayers())
	{
		if (m_playerIndex != enemyPlayer->getPlayerIndex())
		{
			for (auto& enemyHero : enemyPlayer->getVectorOfOwnedHeroes())
			{
				if (getDistanceInTilesBetweenTwoPositions(playerHero.getPosition(), enemyHero->getPosition()) < HeroSettings::c_maxMovementRange)
				{
					if (checkIfOpponentHasStrongerArmy(playerHero, *enemyHero))
					{
						int distance = getPathDistanceInTiles(m_pTileHandler->checkTileCollision(playerHero.getPosition()), enemyHero->getOccupiedTileIndex());

						if (distance > 0 && distance <= HeroSettings::c_maxMovementRange)
						{
							AIPlayerData.getAIHeroData(playerHeroIndex).setPriority(MapAIPriorityEnum::attackEnemyHero);
							AIPlayerData.getAIHeroData(playerHeroIndex).setPriorityTileIndex(enemyHero->getOccupiedTileIndex());
							AIPlayerData.getAIHeroData(playerHeroIndex).setPriorityObjectIndex(enemyPlayer->getPlayerIndex());
							wasPrioSet = true;
							break;
						}
					}
					else
					{
						AIPlayerData.getAIHeroData(playerHeroIndex).resetPriority();
						AIPlayerData.getAIHeroData(playerHeroIndex).setPriority(MapAIPriorityEnum::recruitUnits);
						wasPrioSet = true;
					}
				}
			}
		}
	}

	return wasPrioSet;
}

const bool MapAI::findClosestMapObjectOfInterest(Hero& playerHero, const int& heroIndex, MapAIPlayerData& AIPlayerData)
{
	bool wasPrioSet = false;

	MapAIPriorityEnum prioToSet = MapAIPriorityEnum::none;
	int closestObjectVectorIndex = -1;
	int closestObjectTileIndex = -1;
	int closestDistanceToObject = 999;

	int objectVectorIndex = 0;
	int heroArmyStrength = getArmyStrength(playerHero.getVectorOfUnits());

	//Check resource mines
	for (auto& mine : *m_pResourceMinesMapObjects)
	{
		if (mine->getOwnerIndex() != m_playerIndex)
		{
			//Check if hero has stronger army than mine defender
			if (heroArmyStrength > checkIfNeighbouringTilesHaveAUnitProtectingAndReturnTheirArmyStrength(mine->getTileIndex()))
			{
				int distanceToCompare = getDistanceInTilesBetweenTwoPositions(playerHero.getPosition(), mine->getPosition());
				if (distanceToCompare < closestDistanceToObject)
				{
					int tileIndexToMoveTo = mine->getTileIndex();

					//Check if unit is protecting it
					if (checkIfNeighbouringTilesHaveAUnitProtectingAndReturnTheirArmyStrength(tileIndexToMoveTo))
					{
						tileIndexToMoveTo += m_pTileHandler->getNumOfHorizontalTiles();
					}

					distanceToCompare = getPathDistanceInTiles(m_pTileHandler->checkTileCollision(playerHero.getPosition()), tileIndexToMoveTo);
					if (distanceToCompare > 0 && distanceToCompare < closestDistanceToObject)
					{
						prioToSet = MapAIPriorityEnum::closestResourceMine;
						closestObjectVectorIndex = objectVectorIndex;
						closestObjectTileIndex = mine->getTileIndex();
						closestDistanceToObject = distanceToCompare;
						wasPrioSet = true;
					}
				}
			}
		}
		objectVectorIndex++;
	}

	//Check arenas
	objectVectorIndex = 0;
	for (auto& specialMapObject : *m_pSpecialBuildingsMapObjects)
	{
		if (specialMapObject->getBuildingType() == SpecialBuildingEnum::arena)
		{
			bool wasThisArenaVisited = false;
			for (int& visitedIndex : playerHero.getVectorOfVisitedSpecialBuildingsIndexes())
			{
				if (visitedIndex == objectVectorIndex)
				{
					wasThisArenaVisited = true;
					break;
				}

			}

			if (!wasThisArenaVisited)
			{
				//Check if hero has stronger army than arena defender
				if (heroArmyStrength > checkIfNeighbouringTilesHaveAUnitProtectingAndReturnTheirArmyStrength(specialMapObject->getTileIndex()))
				{
					int distanceToCompare = getDistanceInTilesBetweenTwoPositions(playerHero.getPosition(), specialMapObject->getPosition());
					if (distanceToCompare < closestDistanceToObject)
					{
						int tileIndexToMoveTo = specialMapObject->getTileIndex();

						//Check if unit is protecting it
						if (checkIfNeighbouringTilesHaveAUnitProtectingAndReturnTheirArmyStrength(tileIndexToMoveTo))
						{
							tileIndexToMoveTo += m_pTileHandler->getNumOfHorizontalTiles();
						}

						distanceToCompare = getPathDistanceInTiles(m_pTileHandler->checkTileCollision(playerHero.getPosition()), tileIndexToMoveTo);
						if (distanceToCompare > 0 && distanceToCompare < closestDistanceToObject)
						{
							prioToSet = MapAIPriorityEnum::arena;
							closestObjectVectorIndex = objectVectorIndex;
							closestObjectTileIndex = specialMapObject->getTileIndex();
							closestDistanceToObject = distanceToCompare;
							wasPrioSet = true;
						}
					}
				}
			}
		}
		objectVectorIndex++;
	}

	//Check towns
	objectVectorIndex = 0;
	for (auto& town : *m_pTownMapObjects)
	{
		if (town->getOwnerIndex() != m_playerIndex)
		{
			int distanceToCompare = getDistanceInTilesBetweenTwoPositions(playerHero.getPosition(), town->getPosition());
			if (distanceToCompare < closestDistanceToObject)
			{
				int tileIndexToMoveTo = town->getTileIndex();

				//Check if unit is protecting it
				if (checkIfNeighbouringTilesHaveAUnitProtectingAndReturnTheirArmyStrength(tileIndexToMoveTo))
				{
					tileIndexToMoveTo += m_pTileHandler->getNumOfHorizontalTiles();
				}

				distanceToCompare = getPathDistanceInTiles(m_pTileHandler->checkTileCollision(playerHero.getPosition()), tileIndexToMoveTo);
				if (distanceToCompare > 0 && distanceToCompare < closestDistanceToObject)
				{
					//Compare defending army strength
					int enemyPlayerArmyStrength = getArmyStrength(m_pTownData->at(objectVectorIndex)->getVectorOfUnitsStationedInsideTheTown());

					if (town->getOwnerIndex() < m_playerHandler.getNumberOfPlayers() && town->getOwnerIndex() >= 0) //Check if this town belongs to a player
					{
						//Get combined armies strength
						for (auto& enemyHero : m_playerHandler.getPlayer(town->getOwnerIndex()).getVectorOfOwnedHeroes())
						{
							enemyPlayerArmyStrength += getArmyStrength(enemyHero->getVectorOfUnits());
						}
					}

					if (heroArmyStrength >= enemyPlayerArmyStrength)
					{
						prioToSet = MapAIPriorityEnum::attackEnemyTown;
						closestObjectVectorIndex = objectVectorIndex;
						closestObjectTileIndex = town->getTileIndex();
						closestDistanceToObject = distanceToCompare;
						wasPrioSet = true;
					}
				}
			}
		}
		objectVectorIndex++;
	}

	//SetPriority
	AIPlayerData.getAIHeroData(heroIndex).setPriority(prioToSet);
	AIPlayerData.getAIHeroData(heroIndex).setPriorityObjectIndex(closestObjectVectorIndex);
	AIPlayerData.getAIHeroData(heroIndex).setPriorityTileIndex(closestObjectTileIndex);

	return wasPrioSet;
}

void MapAI::makeAMove(const int& heroIndex, Hero& hero, MapAIPlayerData& playerAIData)
{
	std::cout << "Priority Index: " << static_cast<int>(playerAIData.getAIHeroData(heroIndex).getPriority()) << "\n";
	std::cout << "Priority Object Index: " << playerAIData.getAIHeroData(heroIndex).getPriorityObjectIndex() << "\n";
	std::cout << "Priority Tile Index: " << playerAIData.getAIHeroData(heroIndex).getPriorityTileIndex() << "\n\n";

	switch (playerAIData.getAIHeroData(heroIndex).getPriority())
	{
	case MapAIPriorityEnum::resourceGold:
		findClosestMine(heroIndex, ResourcesEnum::gold, hero, playerAIData);
		break;

	case MapAIPriorityEnum::resourceWood:
		findClosestMine(heroIndex, ResourcesEnum::wood, hero, playerAIData);
		break;

	case MapAIPriorityEnum::resourceStone:
		findClosestMine(heroIndex, ResourcesEnum::stone, hero, playerAIData);
		break;

	case MapAIPriorityEnum::recruitUnits:
		findClosestTownToRecruitUnits(heroIndex, hero, playerAIData);
		break;

	case MapAIPriorityEnum::protectTown:
		recruitUnitsAtTown(playerAIData.getAIHeroData(heroIndex).getPriorityObjectIndex());
		playerAIData.getAIHeroData(heroIndex).setPriorityTileIndex(m_pTownMapObjects->at(playerAIData.getAIHeroData(heroIndex).getPriorityObjectIndex())->getTileIndex());
		break;

	case MapAIPriorityEnum::attackEnemyHero:
		//vars set when priority was determined
		break;

	case MapAIPriorityEnum::attackEnemyTown:
		//Vars set when priority was determined
		break;

	case MapAIPriorityEnum::attackMapUnit:
		// No use yet
		break;

	case MapAIPriorityEnum::closestResourceMine:
		//Vars set when priority was determined
		break;

	case MapAIPriorityEnum::arena:
		//Vars set when priority was determined
		break;

	case MapAIPriorityEnum::collectGold:
		// No use yet
		break;

	case MapAIPriorityEnum::collectWood:
		// No use yet
		break;

	case MapAIPriorityEnum::collectStone:
		// No use yet
		break;

	case MapAIPriorityEnum::none:
	default:
		break;
	}

	if (moveHeroToPriority(heroIndex, hero, playerAIData))
	{
		if (playerAIData.getAIHeroData(heroIndex).getPriority() == MapAIPriorityEnum::none)
		{
			determineIndividualHeroPriority(hero, heroIndex, m_playerHandler.getPlayer(m_playerIndex), playerAIData);
		}

		makeAMove(heroIndex, hero, playerAIData);
	}
}

bool MapAI::moveHeroToPriority(const int& heroIndex, Hero& hero, MapAIPlayerData& playerAIData)
{
	bool doesHeroHaveRemainingMovementPoints = false;
	bool doesHeroNeedToAttackAMapUnit = false;
	MapAIHeroData& heroAIData = playerAIData.getAIHeroData(heroIndex);
	Tile* destinationTile = nullptr;
	int prioIndex = heroAIData.getPriorityTileIndex(); //RETURNS -1 PRIO TILE INDEX NOT SET
	if (prioIndex >= 0)
	{
		destinationTile = m_pTileHandler->getTile(heroAIData.getPriorityTileIndex());


		//Check if destination has a unit protecting it
		for (auto& neighbourTile : destinationTile->getSurroundingTilesVector())
		{
			if (neighbourTile->getMapObjectType() == MapObjectsEnum::unit)
			{
				//Check if hero has strong enough army
				if (checkIfOpponentHasStrongerArmy(hero, *m_pUnitMapObjects->at(neighbourTile->getMapObjectVectorIndex())))
				{
					destinationTile = neighbourTile;
					doesHeroNeedToAttackAMapUnit = true;
				}
				else //Heros army is too weak, change prio to recruiting units
				{
					heroAIData.resetPriority();
					findClosestTownToRecruitUnits(heroIndex, hero, playerAIData);
					return doesHeroHaveRemainingMovementPoints = hero.getCurrentMovementPoints() > 0;
				}
				break;
			}
		}

		//Move hero
		moveHeroToAppropriateTile(hero.getOccupiedTileIndex(), destinationTile->getTileVectorIndex(), hero);

		//Check if hero arrived at priority destination
		if (hero.getOccupiedTileIndex() == destinationTile->getTileVectorIndex())
		{
			if (doesHeroNeedToAttackAMapUnit)
			{
				m_combatHandler.setUpPlayerVsMapUnit(&hero, &*m_pUnitMapObjects->at(destinationTile->getMapObjectVectorIndex()), true);
				m_isCombatInitiated = m_combatHandler.getIsCombatActive();
			}
			else
			{
				heroMapInteraction(heroIndex, hero, playerAIData);
			}
		}

		if (m_isCombatInitiated)
		{
			doesHeroHaveRemainingMovementPoints = false;
		}
		else
		{
			doesHeroHaveRemainingMovementPoints = hero.getCurrentMovementPoints() > 0;
		}
	}
	else
	{
		hero.setCurrentMovementPoints(0);
		doesHeroHaveRemainingMovementPoints = false;
	}

	return doesHeroHaveRemainingMovementPoints;
}

void MapAI::heroMapInteraction(const int& heroIndex, Hero& hero, MapAIPlayerData& playerAIData)
{
	switch (playerAIData.getAIHeroData(heroIndex).getPriority())
	{
	case MapAIPriorityEnum::resourceGold:
	case MapAIPriorityEnum::resourceWood:
	case MapAIPriorityEnum::resourceStone:
	case MapAIPriorityEnum::closestResourceMine:
	case MapAIPriorityEnum::collectGold:
	case MapAIPriorityEnum::collectWood:
	case MapAIPriorityEnum::collectStone:
	case MapAIPriorityEnum::collectResource:
		m_mapHandler.objectInteraction();
		if (!areResourcesNearBy(hero, heroIndex, playerAIData))
		{
			playerAIData.getAIHeroData(heroIndex).resetPriority();
		}
		break;

	case MapAIPriorityEnum::attackMapUnit:
	case MapAIPriorityEnum::attackEnemyTown:
	case MapAIPriorityEnum::attackEnemyHero:
		m_mapHandler.objectInteraction();
		m_isCombatInitiated = m_combatHandler.getIsCombatActive();
		playerAIData.getAIHeroData(heroIndex).resetPriority();
		break;

	case MapAIPriorityEnum::recruitUnits:
		recruitUnitsAtTown(playerAIData.getAIHeroData(heroIndex).getPriorityObjectIndex());
		transferUnitsFromTownToHero(hero, *m_pTownData->at(playerAIData.getAIHeroData(heroIndex).getPriorityObjectIndex()));
		playerAIData.getAIHeroData(heroIndex).resetPriority();
		break;

	case MapAIPriorityEnum::protectTown:
		transferUnitsFromTownToHero(hero, *m_pTownData->at(playerAIData.getAIHeroData(heroIndex).getPriorityObjectIndex()));
		playerAIData.getAIHeroData(heroIndex).resetPriority();
		checkIfEnemyHeroWithWeakerArmyIsClose(hero, heroIndex, playerAIData);
		if (playerAIData.getAIHeroData(heroIndex).getPriority() != MapAIPriorityEnum::none)
		{
			makeAMove(heroIndex, hero, playerAIData);
			return;
		}
		break;

	case MapAIPriorityEnum::arena:
		arenaInteraction(hero, playerAIData.getAIHeroData(heroIndex).getPriorityObjectIndex());
		playerAIData.getAIHeroData(heroIndex).resetPriority();
		break;

	case MapAIPriorityEnum::none:
	default:
		break;
	}

}

void MapAI::upgradeTownBuildings()
{
	Player& player = m_playerHandler.getPlayer(m_playerIndex);
	Resources& resources = player.getResources();
	TownBuilding& townBuilding = m_town.getTownBuildingReference();

	for (int& ownedTownIndex : player.getVectorOfOwnedTownsIndexes())
	{
		bool wasBuildingPurchased = false;
		TownData& townData = *m_pTownData->at(ownedTownIndex);
		auto& upgradeButtons = townBuilding.getUpgradeButtonsVectorReference();

		townBuilding.setBuildingDataPointers(&townData.getTownBuildingData(), &m_dataHandler.getFactionData(m_pTownMapObjects->at(ownedTownIndex)->getFactionIndex()).getBuildingsData(), &resources, &townData);
		townBuilding.updateBuildingAvailability();

		//Check if unit buildings are available to purchase
		for (int buildingIndex = 5; buildingIndex < 5 + c_numOfUnitsPerFaction; buildingIndex++) //5 == first unit building index
		{
			if (upgradeButtons[buildingIndex]->getCanBePurchased())
			{
				townBuilding.setSelectedBuildingIndex(buildingIndex);
				townBuilding.incrementTownBuildingLevel();
				wasBuildingPurchased = true;
				break;
			}
		}

		//Check if town hall is available to purchase
		if (!wasBuildingPurchased && upgradeButtons[static_cast<int>(TownBuildingEnum::townHall)]->getCanBePurchased())
		{
			townBuilding.setSelectedBuildingIndex(static_cast<int>(TownBuildingEnum::townHall));
			townBuilding.incrementTownBuildingLevel();
			wasBuildingPurchased = true;
		}

		//Check if fort is available to purchase
		if (!wasBuildingPurchased && upgradeButtons[static_cast<int>(TownBuildingEnum::fort)]->getCanBePurchased())
		{
			townBuilding.setSelectedBuildingIndex(static_cast<int>(TownBuildingEnum::fort));
			townBuilding.incrementTownBuildingLevel();
		}
	}

	Global::g_updateGame = true;
	Global::g_UILayer = UILayerEnum::map;
}

void MapAI::findClosestMine(const int& heroIndex, const ResourcesEnum& mineType, Hero& hero, MapAIPlayerData& AIPlayerData)
{
	bool wasMineFound = false;
	int mineVectorIndex = -1;
	int mineTileIndex = -1;
	int closestDistance = 999;


	int heroArmyStrength = getArmyStrength(hero.getVectorOfUnits());

	int iteratorIndex = 0;
	for (auto& mine : *m_pResourceMinesMapObjects)
	{
		if (mine->getMineType() == mineType)
		{
			if (mine->getOwnerIndex() != m_playerIndex)
			{
				if (heroArmyStrength > checkIfNeighbouringTilesHaveAUnitProtectingAndReturnTheirArmyStrength(mine->getTileIndex()))
				{
					int distanceToCompare = getDistanceInTilesBetweenTwoPositions(hero.getPosition(), mine->getPosition());

					if (distanceToCompare < closestDistance)
					{
						int tileIndexToMoveTo = mine->getTileIndex();

						//Check if unit is protecting it
						if (checkIfNeighbouringTilesHaveAUnitProtectingAndReturnTheirArmyStrength(tileIndexToMoveTo))
						{
							tileIndexToMoveTo += m_pTileHandler->getNumOfHorizontalTiles();
						}

						distanceToCompare = getPathDistanceInTiles(m_pTileHandler->checkTileCollision(hero.getPosition()), tileIndexToMoveTo);
						if (distanceToCompare > 0 && distanceToCompare < closestDistance)
						{
							mineVectorIndex = iteratorIndex;
							mineTileIndex = mine->getTileIndex();
							wasMineFound = true;
						}
					}
				}
			}
		}
		iteratorIndex++;
	}

	if (mineVectorIndex >= 0)
	{
		AIPlayerData.getAIHeroData(heroIndex).setPriorityObjectIndex(mineVectorIndex);
		AIPlayerData.getAIHeroData(heroIndex).setPriorityTileIndex(mineTileIndex);
	}
	else if(wasMineFound)
	{
		AIPlayerData.getAIHeroData(heroIndex).resetPriority();
		AIPlayerData.getAIHeroData(heroIndex).setPriority(MapAIPriorityEnum::recruitUnits);
		makeAMove(heroIndex, hero, AIPlayerData);
	}
	else
	{
		AIPlayerData.getAIHeroData(heroIndex).resetPriority();
		determineIndividualHeroPriority(hero, heroIndex, m_playerHandler.getPlayer(m_playerIndex), AIPlayerData);
		makeAMove(heroIndex, hero, AIPlayerData);
	}
}

void MapAI::findClosestTownToRecruitUnits(const int& heroIndex, Hero& hero, MapAIPlayerData& AIPlayerData)
{

	int closestTownDistance = 999;
	int closestTownIndex = 0;
	bool isATownWithUnitsAvailable = false;
	int closestTownIndexWithUnits = 0;

	int iterator = 0;
	for (int& townIndex : m_playerHandler.getPlayer(m_playerIndex).getVectorOfOwnedTownsIndexes())
	{		
		if (getDistanceInTilesBetweenTwoPositions(hero.getPosition(), m_pTownMapObjects->at(townIndex)->getPosition()) < closestTownDistance)
		{
			int didstanceInTilesToCompare = getPathDistanceInTiles(m_pTileHandler->checkTileCollision(hero.getPosition()), m_pTownMapObjects->at(townIndex)->getTileIndex());
			if (didstanceInTilesToCompare < closestTownDistance)
			{
				closestTownDistance = didstanceInTilesToCompare;
				closestTownIndex = townIndex;

				for (int& unitsToRecruit : m_pTownData->at(townIndex)->getAvailableUnitsToRecruit())
				{
					if (unitsToRecruit > 0)
					{
						isATownWithUnitsAvailable = true;
						closestTownIndexWithUnits = townIndex;
						break;
					}
				}
			}
		}
		iterator++;
	}

	AIPlayerData.getAIHeroData(heroIndex).setPriority(MapAIPriorityEnum::recruitUnits);

	if (isATownWithUnitsAvailable)
	{
		AIPlayerData.getAIHeroData(heroIndex).setPriorityObjectIndex(closestTownIndexWithUnits);
		AIPlayerData.getAIHeroData(heroIndex).setPriorityTileIndex(m_pTownMapObjects->at(closestTownIndexWithUnits)->getTileIndex());
	}
	else
	{
		AIPlayerData.getAIHeroData(heroIndex).setPriorityObjectIndex(closestTownIndex);
		AIPlayerData.getAIHeroData(heroIndex).setPriorityTileIndex(m_pTownMapObjects->at(closestTownIndex)->getTileIndex());
	}
	
}

void MapAI::recruitUnitsAtTown(const int& townIndex)
{
	bool areUnitsAvailableToRecruit = false;
	int gold = m_playerHandler.getPlayer(m_pTownMapObjects->at(townIndex)->getOwnerIndex()).getResources().getResource(ResourcesEnum::gold);
	int factionIndex = m_pTownMapObjects->at(townIndex)->getFactionIndex();


	int unitToRecruitIndex = 0;
	for (auto& numberOfUnits : m_pTownData->at(townIndex)->getAvailableUnitsToRecruit())
	{
		if (numberOfUnits > 0)
		{
			int costPerUnit = m_dataHandler.getFactionData(factionIndex).getUnitData(unitToRecruitIndex).getIntData(UnitDataEnum::cost);
			if (gold >= costPerUnit)
			{
				int numOfUnitsAvailableToPurchase = checkHowManyUnitsCanBePurchased(gold, factionIndex, unitToRecruitIndex);

				if (numOfUnitsAvailableToPurchase > numberOfUnits) //Make sure that number of units to recruit doesn't exceede available unitss
				{
					numOfUnitsAvailableToPurchase = numberOfUnits;
				}

				if (addUnitToArmy(numOfUnitsAvailableToPurchase, m_dataHandler.getFactionData(factionIndex).getUnitData(unitToRecruitIndex), m_pTownData->at(townIndex)->getVectorOfUnitsStationedInsideTheTown()))
				{
					//Units recruited
					m_playerHandler.getPlayer(m_pTownMapObjects->at(townIndex)->getOwnerIndex()).getResources().incrementResourceValue(ResourcesEnum::gold, -(numOfUnitsAvailableToPurchase * costPerUnit));
					gold = m_playerHandler.getPlayer(m_pTownMapObjects->at(townIndex)->getOwnerIndex()).getResources().getResource(ResourcesEnum::gold);
					m_pTownData->at(townIndex)->getAvailableUnitsToRecruit()[unitToRecruitIndex] -= numOfUnitsAvailableToPurchase;

				}
			}
		}
		unitToRecruitIndex++;
	}
}

const int MapAI::getDistanceInTilesBetweenTwoPositions(const sf::Vector2f& posA, const sf::Vector2f& posB)
{
	int distance = 0;

	distance += abs(posA.x - posB.x) / m_pTileHandler->getTileSize();
	distance += abs(posA.y - posB.y) / m_pTileHandler->getTileSize();
	
	return distance;
}

const bool MapAI::checkIfOpponentHasStrongerArmy(Hero& playerHero, Hero& enemyHero)
{
	int playerStrength = 0;
	int enemyStrength = 0;

	//Player army strength
	playerStrength = getArmyStrength(playerHero.getVectorOfUnits());
	enemyStrength = getArmyStrength(enemyHero.getVectorOfUnits());

	//Ai bias to make sure they won't fight only when they have an advantage
	playerStrength *= settings::c_AIArmyStrengthBias;

	return playerStrength >= enemyStrength;
}

const int MapAI::getArmyStrength(std::vector<std::shared_ptr<Unit>>& vectorOfUnits)
{
	int armyStrength = 0;

	for (auto& unit : vectorOfUnits)
	{
		if (unit->getIsDataSet())
		{
			armyStrength += unit->getNumOfUnits() * unit->getBaseUnitData()->getIntData(UnitDataEnum::AIValue);
		}
	}

	return armyStrength;
}

const bool MapAI::checkIfOpponentHasStrongerArmy(Hero& playerHero, UnitMapObject& enemyUnits)
{
	int playerStrength = 0;
	int enemyStrength = 0;

	playerStrength = getArmyStrength(playerHero.getVectorOfUnits());
	enemyStrength = enemyUnits.getNumberOfUnits() * m_dataHandler.getFactionData(enemyUnits.getFactionIndex()).getUnitData(enemyUnits.getUnitIndex()).getIntData(UnitDataEnum::AIValue);

	playerStrength *= settings::c_AIArmyStrengthBias;

	return playerStrength >= enemyStrength;
}

const int MapAI::getPathDistanceInTiles(const int& startTileIndex, const int& endTileIndex)
{
	int distance = 0;

	m_pTileHandler->setTileProperty(startTileIndex, TilePropertiesEnum::start);
	m_pTileHandler->setTileProperty(endTileIndex, TilePropertiesEnum::end);

	m_pTileHandler->findPath();

	distance = m_pTileHandler->getTilePositionVectorForThePathFound().size();

	return distance;
}

const int MapAI::checkIfNeighbouringTilesHaveAUnitProtectingAndReturnTheirArmyStrength(const int& tileIndex)
{
	int unitStrength = 0;

	for (Tile*& neighbourTile : m_pTileHandler->getTile(tileIndex)->getSurroundingTilesVector())
	{
		if (neighbourTile->getMapObjectType() == MapObjectsEnum::unit)
		{
			std::unique_ptr<UnitMapObject>& unit = m_pUnitMapObjects->at(neighbourTile->getMapObjectVectorIndex());
			unitStrength = unit->getNumberOfUnits() * m_dataHandler.getFactionData(unit->getFactionIndex()).getUnitData(unit->getUnitIndex()).getIntData(UnitDataEnum::AIValue);
			break;
		}
	}

	return unitStrength;
}

const int MapAI::checkHowManyUnitsCanBePurchased(const int& gold, const int& factionIndex, const int& unitIndex)
{
	return std::floor(gold / m_dataHandler.getFactionData(factionIndex).getUnitData(unitIndex).getIntData(UnitDataEnum::cost));
}

const bool MapAI::addUnitToArmy(const int& numberOfUnits, UnitData& unitToAdd, std::vector<std::shared_ptr<Unit>>& army)
{
	bool wasUnitAdded = false;

	//Check if unit is already in the army
	for (auto& unit : army)
	{
		if (unit->getIsDataSet())
		{
			if (unit->getBaseUnitData()->getStringData(UnitDataEnum::unitName) == unitToAdd.getStringData(UnitDataEnum::unitName))
			{
				wasUnitAdded = true;
				unit->incrementNumOfUnits(numberOfUnits);
				break;
			}
		}
	}

	if (!wasUnitAdded)
	{
		for (auto& unit : army)
		{
			if (!unit->getIsDataSet())
			{
				unit->setBaseUnitData(&unitToAdd);
				unit->incrementNumOfUnits(numberOfUnits);
				unit->toggleIsDataSet();
				unit->initializeUnitSpecificData();
				wasUnitAdded = true;
				break;
			}
		}
	}

	return wasUnitAdded;
}

void MapAI::transferUnitsBetweenTwoArmies(std::vector<std::shared_ptr<Unit>>& armyToTransferTo, std::vector<std::shared_ptr<Unit>>& armyToTransferFrom)
{
	int numberOfUnitsToTransfer = 0;
	int numberOfUnitsTransfered = 0;

	for (auto& unit : armyToTransferFrom)
	{
		if (unit->getIsDataSet())
		{
			numberOfUnitsToTransfer++;
		}
	}

	//Check if army already has these units
	for (auto& unitToTransfer : armyToTransferFrom)
	{
		if (unitToTransfer->getIsDataSet())
		{
			for (auto& unit : armyToTransferTo)
			{
				if (unit->getIsDataSet())
				{
					if (unitToTransfer->getBaseUnitData()->getStringData(UnitDataEnum::unitName) == unit->getBaseUnitData()->getStringData(UnitDataEnum::unitName))
					{
						unit->incrementNumOfUnits(unitToTransfer->getNumOfUnits()); //value == 0
						unitToTransfer->resetUnitData();
						numberOfUnitsTransfered++;
						break;
					}
				}
			}
		}
	}

	//Check if all units have already been transfered
	if (numberOfUnitsTransfered < numberOfUnitsToTransfer) //Transfer remaining units
	{
		for (auto& unitToTransfer : armyToTransferFrom)
		{
			if (unitToTransfer->getIsDataSet())
			{
				for (auto& unit : armyToTransferTo)
				{
					if (!unit->getIsDataSet())
					{
						std::shared_ptr<Unit> tempUnit = unit;
						unit = unitToTransfer;
						unitToTransfer = unit;
						numberOfUnitsTransfered++;
						break;
					}
				}
			}
		}
	}

	//Check if all units have already been transfered
	if (numberOfUnitsTransfered < numberOfUnitsToTransfer) //Swap current units for stronger ones
	{
		for (auto& unitToTransfer : armyToTransferFrom)
		{
			if (unitToTransfer->getIsDataSet())
			{
				int unitToTransferStrength = unitToTransfer->getNumOfUnits() * unitToTransfer->getBaseUnitData()->getIntData(UnitDataEnum::AIValue);
				for (auto& unit : armyToTransferTo)
				{
					if (unit->getIsDataSet())
					{
						int unitToSwapStrength = unit->getNumOfUnits() * unit->getBaseUnitData()->getIntData(UnitDataEnum::AIValue);
						if (unitToTransferStrength > unitToSwapStrength)
						{
							std::shared_ptr<Unit> tempUnit = unit;
							unit = unitToTransfer;
							unitToTransfer = unit;
							break;
						}
					}
				}
			}
		}
	}
}

void MapAI::transferUnitsFromTownToHero(Hero& hero, TownData& townData)
{
	transferUnitsBetweenTwoArmies(hero.getVectorOfUnits(), townData.getVectorOfUnitsStationedInsideTheTown());
	hero.updateNumberOfUnits();
	hero.updateUnitsStats();
}

void MapAI::moveHeroToAppropriateTile(const int& startTile, const int& destinationTile, Hero& hero)
{
	if (startTile != destinationTile)
	{
		m_pTileHandler->setTileProperty(startTile, TilePropertiesEnum::start);
		m_pTileHandler->setTileProperty(destinationTile, TilePropertiesEnum::end);

		m_pTileHandler->findPath();

		if (m_pTileHandler->getTile(destinationTile)->getParentTile() != nullptr)
		{
			auto& path = m_pTileHandler->getTilePositionVectorForThePathFound();
			int positionToMoveTo = 0;
			int movementPointsConsumed = 0;
			int heroMovementPoints = hero.getCurrentMovementPoints();

			for (int i = path.size() - 1; i >= 1; i--)
			{
				movementPointsConsumed += m_mapHandler.calculateHowManyMovementPointsTheMoveConsumes(path[i - 1], path[i]);
				if (movementPointsConsumed > heroMovementPoints)
				{
					movementPointsConsumed -= m_mapHandler.calculateHowManyMovementPointsTheMoveConsumes(path[i - 1], path[i]); //Revert added movement points
					positionToMoveTo = i - 1;
					break;
				}
				positionToMoveTo = i - 1;
			}

			hero.setPosition(path[positionToMoveTo]);
			hero.setOccupiedTileIndex(m_pTileHandler->checkTileCollision(path[positionToMoveTo]));
			hero.decrementMovementPoints(movementPointsConsumed);
		}
	}

}

void MapAI::deleteAIPlayerData(int playerIndex)
{
	for (auto& playerData : m_AIPlayerData)
	{
		if (playerData->getPlayerIndex() > playerIndex)
		{
			playerData->setPlayerIndex(playerData->getPlayerIndex() - 1);
		}
	}

	int iterator = 0;
	for (auto& playerData : m_AIPlayerData)
	{
		if (playerData->getPlayerIndex() == playerIndex)
		{
			m_AIPlayerData.erase(m_AIPlayerData.begin() + iterator);
		}
		iterator++;
	}
}

void MapAI::arenaInteraction(Hero& hero, const int& arenaIndex)
{
	//Increment either attack or defence by 2
	hero.incrementHeroStat(static_cast<HeroStatsEnum>(rand() % 2), 2);
	hero.getVectorOfVisitedSpecialBuildingsIndexes().push_back(arenaIndex);
}

const bool MapAI::areResourcesNearBy(Hero& hero, const int& heroIndex, MapAIPlayerData& AIPlayerData)
{
	bool areResourcesClose = false;
	int heroTileIndex = hero.getOccupiedTileIndex();

	for (int y = -settings::c_maxRangeToCollectResource; y < settings::c_maxRangeToCollectResource; y++)
	{
		int tileToCheckY = heroTileIndex + (y * m_pTileHandler->getNumOfHorizontalTiles());
		for (int x = -settings::c_maxRangeToCollectResource; x < settings::c_maxRangeToCollectResource; x++)
		{
			if (m_pTileHandler->getTile(tileToCheckY + x)->getMapObjectType() == MapObjectsEnum::resource)
			{
				AIPlayerData.getAIHeroData(heroIndex).setPriority(MapAIPriorityEnum::collectResource);
				AIPlayerData.getAIHeroData(heroIndex).setPriorityObjectIndex(m_pTileHandler->getTile(tileToCheckY + x)->getMapObjectVectorIndex());
				AIPlayerData.getAIHeroData(heroIndex).setPriorityTileIndex(tileToCheckY + x);
				areResourcesClose = true;
				break;
			}
		}
	}

	return areResourcesClose;
}

void MapAI::updatePlayerIndex()
{
	m_playerIndex = m_turnHandler.getCurrentPlayerIndex();
}

const int MapAI::getPlayersTotalArmyStrength(const int& playerIndex)
{
	int totalArmyStrength = 0;

	for (auto& hero : m_playerHandler.getPlayer(playerIndex).getVectorOfOwnedHeroes())
	{
		totalArmyStrength += getArmyStrength(hero->getVectorOfUnits());
	}

	for (int& ownedTownIndex : m_playerHandler.getPlayer(playerIndex).getVectorOfOwnedTownsIndexes())
	{
		totalArmyStrength += getArmyStrength(m_pTownData->at(ownedTownIndex)->getVectorOfUnitsStationedInsideTheTown());
	}

	return totalArmyStrength;
}
