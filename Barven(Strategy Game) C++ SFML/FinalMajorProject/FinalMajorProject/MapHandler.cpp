#include "MapHandler.h"
namespace settings = MapHandlerSettings;
MapHandler::MapHandler(sf::RenderWindow& rWindow, Textures& rTextures, Audio& rAudio, DataHandler& rDataHandler, UIHandler& rUIHandler, GameSetUpScreen& rGameSetUpScreen, ViewManager& rViewManager, PlayerHandler& rPlayerHandler, TurnHandler& rTurnHandler, CombatHandler& rCombatHandler, MapUI& rMapUI, GameEnd& rGameEnd) :
	m_window(rWindow),
	m_dataHandler(rDataHandler),
	m_UIHandler(rUIHandler),
	m_tileHandler(rWindow, rTextures),
	m_gameSetUpScreen(rGameSetUpScreen),
	m_textures(rTextures),
	m_audio(rAudio),
	m_viewManager(rViewManager),
	m_playerHandler(rPlayerHandler),
	m_turnHandler(rTurnHandler),
	m_combatHandler(rCombatHandler),
	m_mapUI(rMapUI),
	m_gameEnd(rGameEnd),
	m_heroMovementFeedback(rWindow, rTextures),
	m_mapWidth(0),
	m_mapHeight(0),
	m_numOfPlayers(0),
	m_tileSize(0),
	m_isMapLoaded(false),
	m_isPathValid(false),
	m_tileIndexToMoveTo(0),
	m_numOfMovementPointsTheMoveWillConsume(0),
	m_numOfPositionsWithinRange(0),
	m_numOfTownMapObjects(0),
	m_numOfUnitMapObjects(0),
	m_numOfResourceMinesMapObjects(0),
	m_numOfResourceMapObjects(0),
	m_numOfSpecialBuildingMapObjects(0),
	m_numOfLandscapeMapObjects(0),
	m_horizontalQuadrantsToDisplay(0),
	m_verticalQuadrantsToDisplay(0),
	m_maxHorizontalQuadrants(0),
	m_maxVerticalQuadrants(0),
	m_lastValidStartQuadrant(0)
{
	m_gameSetUpScreen.setConfirmationFunctionPointer(std::bind(&MapHandler::loadTheMap, this));
	m_combatHandler.setFunctionToCallWhenCombatIsWon(std::bind(&MapHandler::functionToCallAfterBattleConcluded, this, std::placeholders::_1, std::placeholders::_2));
	m_tileHandler.setIsTesting(false);
	m_mapUI.setMapHandlerFunctionPointers(std::bind(&MapHandler::enterTown, this, std::placeholders::_1), std::bind(&MapHandler::selectHero, this, std::placeholders::_1), std::bind(&MapHandler::updateResourcesPerTurnMapUI, this), std::bind(&MapHandler::nextTurn, this));
}

MapHandler::~MapHandler()
{
}

void MapHandler::loadTheMap()
{
	if (!m_isMapLoaded)
	{
		srand(time(NULL));
		m_dataHandler.loadMapData(m_gameSetUpScreen.getChosenMapIndex());
		json& tempMapData = m_dataHandler.getLoadedMapData();

		m_tileHandler.setUpTiles(tempMapData["mapWidth"], tempMapData["mapHeight"], tempMapData["tileSize"], 0, 0);

		m_numOfPlayers = tempMapData["numOfPlayers"];
		m_mapWidth = tempMapData["mapWidth"];
		m_mapHeight = tempMapData["mapHeight"];
		m_tileSize = tempMapData["tileSize"];

		//Tiles
		for (int i = 0; i < tempMapData["numberOfTiles"]; i++)
		{
			Tile& tempTile = *m_tileHandler.getTile(i);

			tempTile.setIsObstacle(tempMapData["tiles"][i]["isObstacle"]);
			tempTile.setIsOccupied(tempMapData["tiles"][i]["isOccupied"]);
			tempTile.setMapObjectType((MapObjectsEnum)tempMapData["tiles"][i]["mapObjectType"]);
			tempTile.setMapObjectVectorIndex(tempMapData["tiles"][i]["mapObjectVectorIndex"]);
		}

		//Towns
		m_numOfTownMapObjects = tempMapData["numberOfTownObjects"];
		for (int i = 0; i < tempMapData["numberOfTownObjects"]; i++)
		{
			m_townMapObjects.push_back(std::unique_ptr<TownMapObject>(new TownMapObject()));

			m_townMapObjects[i]->setOwnerIndex(tempMapData["townObjects"][i]["ownerIndex"]);
			m_townMapObjects[i]->setTileIndex(tempMapData["townObjects"][i]["tileIndex"]);

			//Player selected factions
			if (i >= 0 && i < tempMapData["numOfPlayers"])
			{
				int factionID = m_gameSetUpScreen.getPlayerChosenFaction(i);
				if (factionID >= c_numOfFactions)
				{
					factionID = rand() % c_numOfFactions;
				}
				m_townMapObjects[i]->setFactionIndex(factionID);
				m_townMapObjects[i]->setUp(m_tileHandler.getTile(m_townMapObjects[i]->getTileIndex())->getPosition(), m_dataHandler.getFactionData(factionID).getBuildingsData().getMapTexture());
				m_townMapObjects[i]->setOwnerIndex(i);

				//Make players
				m_playerHandler.makeNewPlayer(factionID);
				m_playerHandler.getPlayer(i).setDataHandlerPointer(&m_dataHandler);
				m_playerHandler.getPlayer(i).setFunctionToCallWhenHeroArrivesAtDestination(std::bind(&MapHandler::objectInteraction, this));
				m_playerHandler.getPlayer(i).setFunctionToUpdateHeroesMapUI(std::bind(&MapHandler::updateHeroesMapUI, this));


				m_playerHandler.getPlayer(i).setIsPlayerAI(m_gameSetUpScreen.getIfPlayerIsAI(i));
				if (m_gameSetUpScreen.getIfPlayerIsAI(i))
				{
					m_makeNewAIPlayerDataFunction(i);
				}
				m_playerHandler.getPlayer(i).setTownDataVectorPointer(m_townData);
				m_playerHandler.getPlayer(i).addOwnedTown(i);
				m_playerHandler.getPlayer(i).setPlayerIndex(i);
			}
			else //Unoccupied town factions
			{
				int factionIndex = rand() % c_numOfFactions;
				m_townMapObjects[i]->setFactionIndex(factionIndex);
				m_townMapObjects[i]->setUp(m_tileHandler.getTile(m_townMapObjects[i]->getTileIndex())->getPosition(), m_dataHandler.getFactionData(factionIndex).getBuildingsData().getMapTexture());
			}
		}

		//Set base town data
		for (int i = 0; i < m_numOfTownMapObjects; i++)
		{
			m_townData.push_back(std::unique_ptr<TownData>(new TownData()));
			m_townData[i]->setMapData(m_townMapObjects[i]->getTileIndex(), m_townMapObjects[i]->getPosition());
			for (int k = 0; k < c_numOfUnitsPerFaction; k++) //Set Unit Data
			{
				m_townData[i]->setUnitData(k, m_dataHandler.getFactionData(m_townMapObjects[i]->getFactionIndex()).getUnitData(k));
				if (m_townData[i]->getTownBuildingData().getData(static_cast<TownBuildingEnum>(5 + k))) //5 == first unit data position in enum , checks if town has building coresponding to the unit
				{
					m_townData[i]->getAvailableUnitsToRecruit()[k] = m_dataHandler.getFactionData(m_townMapObjects[i]->getFactionIndex()).getUnitData(k).getIntData(UnitDataEnum::growthPerWeek);
				}
			}
		}

		//Units
		m_numOfUnitMapObjects = tempMapData["numberOfUnitObjects"];
		for (int i = 0; i < tempMapData["numberOfUnitObjects"]; i++)
		{
			m_unitMapObjects.push_back(std::unique_ptr<UnitMapObject>(new UnitMapObject()));
			m_unitMapObjects[i]->setFactionIndex(tempMapData["unitObjects"][i]["factionIndex"]);
			m_unitMapObjects[i]->setNumberOfUnits(tempMapData["unitObjects"][i]["numberOfUnits"]);
			m_unitMapObjects[i]->setTileIndex(tempMapData["unitObjects"][i]["tileIndex"]);
			m_unitMapObjects[i]->setUnitIndex(tempMapData["unitObjects"][i]["unitIndex"]);

			m_unitMapObjects[i]->setUp(m_tileHandler.getTile(m_unitMapObjects[i]->getTileIndex())->getPosition(), m_dataHandler.getFactionData(m_unitMapObjects[i]->getFactionIndex()).getUnitData(m_unitMapObjects[i]->getUnitIndex()).getUnitMapSprite());

			//Set up "unit protection zone"
			int tempTileIndex = tempMapData["unitObjects"][i]["tileIndex"];
			for (auto& neighbourTile : m_tileHandler.getTile(tempTileIndex)->getSurroundingTilesVector())
			{
				if (neighbourTile->getTileVectorIndex() <= tempTileIndex + 1 && neighbourTile->getMapObjectType() == MapObjectsEnum::none)
				{
					neighbourTile->setIsObstacle(true);
				}
			}
		}

		//Resource mines
		m_numOfResourceMinesMapObjects = tempMapData["numberOfResourceMines"];
		for (int i = 0; i < tempMapData["numberOfResourceMines"]; i++)
		{
			m_resourceMinesMapObjects.push_back(std::unique_ptr<ResourceMineMapObject>(new ResourceMineMapObject()));
			m_resourceMinesMapObjects[i]->setTileIndex(tempMapData["resourceMineObjects"][i]["tileIndex"]);
			m_resourceMinesMapObjects[i]->setOwnerIndex(tempMapData["resourceMineObjects"][i]["ownerIndex"]);
			m_resourceMinesMapObjects[i]->setMineTypeInt(tempMapData["resourceMineObjects"][i]["mineType"]);

			m_tileHandler.getTile(tempMapData["resourceMineObjects"][i]["tileIndex"] - 1)->setMapObjectType(MapObjectsEnum::resourceMine);
			m_tileHandler.getTile(tempMapData["resourceMineObjects"][i]["tileIndex"] + 1)->setMapObjectType(MapObjectsEnum::resourceMine);

			m_resourceMinesMapObjects[i]->setUp(m_tileHandler.getTile(m_resourceMinesMapObjects[i]->getTileIndex())->getPosition(), m_dataHandler.getResourceMineData(m_resourceMinesMapObjects[i]->getMineType()).getMineMapTexture());
		}

		//Resources
		m_numOfResourceMapObjects = tempMapData["numberOfResources"];
		for (int i = 0; i < tempMapData["numberOfResources"]; i++)
		{
			m_resourceMapObjects.push_back(std::unique_ptr<ResourceMapObject>(new ResourceMapObject()));

			m_resourceMapObjects[i]->setResourceAmount(tempMapData["resourceObjects"][i]["resourceAmount"]);
			m_resourceMapObjects[i]->setResourceType((ResourcesEnum)tempMapData["resourceObjects"][i]["resourceType"]);
			m_resourceMapObjects[i]->setTileIndex(tempMapData["resourceObjects"][i]["tileIndex"]);

			m_resourceMapObjects[i]->setUp(m_tileHandler.getTile(m_resourceMapObjects[i]->getTileIndex())->getPosition(), &m_textures.m_resourceTextures[(int)m_resourceMapObjects[i]->getResourceType()]);
		}

		//Special buildings
		m_numOfSpecialBuildingMapObjects = tempMapData["numberOfSpecialBuildings"];
		for (int i = 0; i < m_numOfSpecialBuildingMapObjects; i++)
		{
			m_specialBuildingsMapObjects.push_back(std::unique_ptr<SpecialBuildingMapObject>(new SpecialBuildingMapObject()));

			m_specialBuildingsMapObjects[i]->setBuildingType((SpecialBuildingEnum)tempMapData["specialBuildingObjects"][i]["buildingType"]);
			m_specialBuildingsMapObjects[i]->setIsVisited(tempMapData["specialBuildingObjects"][i]["isVisited"]);
			m_specialBuildingsMapObjects[i]->setTileIndex(tempMapData["specialBuildingObjects"][i]["tileIndex"]);

			m_tileHandler.getTile(tempMapData["specialBuildingObjects"][i]["tileIndex"] - 1)->setMapObjectType(MapObjectsEnum::specialBuilding);
			m_tileHandler.getTile(tempMapData["specialBuildingObjects"][i]["tileIndex"] + 1)->setMapObjectType(MapObjectsEnum::specialBuilding);

			m_specialBuildingsMapObjects[i]->setUp(m_tileHandler.getTile(m_specialBuildingsMapObjects[i]->getTileIndex())->getPosition(), &m_textures.m_specialBuildings[(int)m_specialBuildingsMapObjects[i]->getBuildingType()]);
		}

		//Landscape
		m_numOfLandscapeMapObjects = tempMapData["numberOfLandscapeObjects"];
		for (int i = 0; i < m_numOfLandscapeMapObjects; i++)
		{
			m_landscapeMapObjects.push_back(std::unique_ptr<LandscapeMapObject>(new LandscapeMapObject()));

			m_landscapeMapObjects[i]->setTileIndex(tempMapData["landscapeObjects"][i]["tileIndex"]);
			m_landscapeMapObjects[i]->setLandscapeType((LandscapeTypeEnum)tempMapData["landscapeObjects"][i]["objectType"]);
			m_landscapeMapObjects[i]->setObjectIndex(tempMapData["landscapeObjects"][i]["objectIndex"]);

			switch (m_landscapeMapObjects[i]->getLandscapeType())
			{
			case LandscapeTypeEnum::tree:
				m_landscapeMapObjects[i]->setUp(m_tileHandler.getTile(m_landscapeMapObjects[i]->getTileIndex())->getPosition(), &m_textures.m_treeLandscapes[m_landscapeMapObjects[i]->getObjectIndex()]);
				break;

			case LandscapeTypeEnum::rocky:
				m_landscapeMapObjects[i]->setUp(m_tileHandler.getTile(m_landscapeMapObjects[i]->getTileIndex())->getPosition(), &m_textures.m_rockyLandscapes[m_landscapeMapObjects[i]->getObjectIndex()]);
				break;

			case LandscapeTypeEnum::other:
				m_landscapeMapObjects[i]->setUp(m_tileHandler.getTile(m_landscapeMapObjects[i]->getTileIndex())->getPosition(), &m_textures.m_otherLandscapes[m_landscapeMapObjects[i]->getObjectIndex()]);
				break;

			default:
				break;
			}
		}

		setUpMapQuadrants(m_window.getSize().x, m_window.getSize().y);

		m_viewManager.setMapBoundaries(m_mapWidth * m_tileSize, m_mapHeight * m_tileSize, 300);
		m_viewManager.setMapSectionVariables(m_tileSize, m_maxHorizontalQuadrants);
		m_dataHandler.deleteLoadedMapData();

		Global::g_UILayer = UILayerEnum::map;
		Global::g_updateGame = true;

		//Create starting heroes for each player
		for (int i = 0; i < m_numOfPlayers; i++)
		{
			int factionIndex = m_playerHandler.getPlayer(i).getFactionIndex();

			//Create hero and set data
			m_playerHandler.getPlayer(i).makeNewHero(m_townMapObjects[i]->getPosition(), m_townMapObjects[i]->getTileIndex(), false);

			//Add startting units
			int numberOfUnitsToAdd = 0;
			int rangeOfUnits = 0;
			for (int k = 0; k < settings::c_numOfStartingUnits; k++)
			{
				//Add new unit
				m_playerHandler.getPlayer(i).getHero(0).addUnit(k, &m_dataHandler.getFactionData(factionIndex).getUnitData(k));

				//Increment number of units
				rangeOfUnits = settings::c_rangeOfStartUnits[factionIndex][k][1] - settings::c_rangeOfStartUnits[factionIndex][k][0];
				numberOfUnitsToAdd = rand() % rangeOfUnits + settings::c_rangeOfStartUnits[factionIndex][k][0];
				m_playerHandler.getPlayer(i).getHero(0).getUnit(k).incrementNumOfUnits(numberOfUnitsToAdd);
				m_playerHandler.getPlayer(i).getHero(0).getUnit(k).initializeUnitSpecificData();
			}
			m_playerHandler.getPlayer(i).getHero(0).updateUnitsStats();
		}

		m_playerHandler.updateResourcesBarValues(m_turnHandler.getCurrentPlayerIndex());

		for (int i = 0; i < m_playerHandler.getNumberOfPlayers(); i++)
		{
			m_playerHandler.getPlayer(i).updateResourcesPerTurn();
		}
		m_isMapLoaded = true;
	}

	updateEntireMapUI();

	m_audio.playMusic(MusicEnum::mapMusic, 0);
}

void MapHandler::setUpMapQuadrants(const int& screenWidth, const int& screenHeight)
{
	int horizontalTilesToDisplay = std::ceil(screenWidth / m_tileHandler.getTileSize());
	int verticalTilesToDisplay = std::ceil(screenHeight / m_tileHandler.getTileSize());

	m_horizontalQuadrantsToDisplay = (horizontalTilesToDisplay / settings::c_drawQuadrantWidth) + settings::c_quadrantsSafetyNet;
	m_verticalQuadrantsToDisplay = (verticalTilesToDisplay / settings::c_drawQuadrantHeight) + settings::c_quadrantsSafetyNet;

	//For testing
	//m_horizontalQuadrantsToDisplay = 2;
	//m_verticalQuadrantsToDisplay = 2;

	//Calculates number of horizontal and vertical sections to split the map
	m_maxHorizontalQuadrants = m_tileHandler.getNumOfHorizontalTiles() / settings::c_drawQuadrantWidth;
	m_maxVerticalQuadrants = m_tileHandler.getNumOfVerticalTiles() / settings::c_drawQuadrantHeight;

	//For some reason std::ceil doesn't work to round up the result to the nearest int so I have to round them up this way
	if (m_tileHandler.getNumOfHorizontalTiles() % settings::c_drawQuadrantWidth > 0)
	{
		m_maxHorizontalQuadrants++;
	}
	if (m_tileHandler.getNumOfVerticalTiles() % settings::c_drawQuadrantHeight > 0)
	{
		m_maxVerticalQuadrants++;
	}

	//Allocate memory for map sections
	for (int i = 0; i < m_maxHorizontalQuadrants * m_maxVerticalQuadrants; i++)
	{
		m_mapQuadrants.push_back(std::unique_ptr<MapQuadrantData>(new MapQuadrantData()));
	}

	m_lastValidStartQuadrant = (m_maxHorizontalQuadrants * m_maxVerticalQuadrants) - m_horizontalQuadrantsToDisplay - (m_maxHorizontalQuadrants * m_verticalQuadrantsToDisplay);

	int tileIndex = 0;
	int mapSectionIndex = 0;
	int tileIndexToCheckForMapObject = 0;

	for (int sectionIndexY = m_maxVerticalQuadrants - 1; sectionIndexY >= 0; sectionIndexY--)  //Loops through each map section row starting from the bottom
	{
		for (int sectionIndexX = m_maxHorizontalQuadrants - 1; sectionIndexX >= 0; sectionIndexX--) //Loops through each map section collumn starting from the right
		{
			mapSectionIndex = sectionIndexY * m_maxHorizontalQuadrants + sectionIndexX; //Calculates map section index

			for (int tileIndexY = 0; tileIndexY < settings::c_drawQuadrantHeight; tileIndexY++) //Loops through each tile row in the current map section starting from the top
			{
				if (sectionIndexY * settings::c_drawQuadrantHeight + tileIndexY < m_mapHeight) //Makes sure that the tile row is withing map limits
				{
					for (int tileIndexX = 0; tileIndexX < settings::c_drawQuadrantWidth; tileIndexX++) //Loops through each tile collumn in the current map section starting from the left
					{
						if (sectionIndexX * settings::c_drawQuadrantWidth + tileIndexX < m_mapWidth) //Makes sure that the tile collumn is within map limits
						{
							tileIndex = (((sectionIndexY * settings::c_drawQuadrantHeight) + tileIndexY) * m_mapWidth) + (sectionIndexX * settings::c_drawQuadrantWidth + tileIndexX); //Calculates tile index to add to the map section
							m_mapQuadrants[mapSectionIndex]->addTileIndex(tileIndex); //Adds appropriate tile to current map section
						}
						else
						{
							break;
						}
					}
				}
				else
				{
					break;
				}
			}
		}
	}

	for (std::unique_ptr<MapQuadrantData>& mapQuadrant : m_mapQuadrants) //Loops through all map sections
	{
		std::vector<int>& tileIndexes = mapQuadrant->getTileIndexesVector(); //Gets reference to the vector of tile indexes in current map section

		for (size_t row = 0; row < tileIndexes.size() / settings::c_drawQuadrantWidth; row++)
		{
			for (int collumn = settings::c_drawQuadrantWidth - 1; collumn >= 0; collumn--)
			{
				tileIndexToCheckForMapObject = (row * settings::c_drawQuadrantWidth) + collumn;

				Tile* tile = m_tileHandler.getTile(tileIndexes[tileIndexToCheckForMapObject]);

				if (tile->getIsOccupied()) //Checks if the tile has an object on it
				{
					switch (tile->getMapObjectType()) //Switches based on type of object on the tile and uses polymorphism to add various types of objects into one vector
					{
					case MapObjectsEnum::town:
						mapQuadrant->addMapObjectPointer(m_townMapObjects[tile->getMapObjectVectorIndex()]->getSelf());
						break;

					case MapObjectsEnum::unit:
						mapQuadrant->addMapObjectPointer(m_unitMapObjects[tile->getMapObjectVectorIndex()]->getSelf());
						break;

					case MapObjectsEnum::specialBuilding:
						mapQuadrant->addMapObjectPointer(m_specialBuildingsMapObjects[tile->getMapObjectVectorIndex()]->getSelf());
						break;

					case MapObjectsEnum::resourceMine:
						mapQuadrant->addMapObjectPointer(m_resourceMinesMapObjects[tile->getMapObjectVectorIndex()]->getSelf());
						break;

					case MapObjectsEnum::resource:
						mapQuadrant->addMapObjectPointer(m_resourceMapObjects[tile->getMapObjectVectorIndex()]->getSelf());
						break;

					case MapObjectsEnum::landscape:
						mapQuadrant->addMapObjectPointer(m_landscapeMapObjects[tile->getMapObjectVectorIndex()]->getSelf());
						break;

					default:
						break;
					}
				}
			}
		}
	}
}

void MapHandler::setMakeNewAIPlayerDataFunction(std::function<void(int)> function)
{
	m_makeNewAIPlayerDataFunction = function;
}

void MapHandler::setAITakeTurnFunction(std::function<void()> function)
{
	m_AITakeTurnFunction = function;
}

void MapHandler::checkMapInteractions(sf::Vector2f& mousePosition)
{
	if (m_playerHandler.getPlayer(m_turnHandler.getCurrentPlayerIndex()).getIsPlayerAI())
	{
		m_window.clear();
		m_viewManager.setUIView();
		m_UIHandler.drawAITurnInformation();
		m_window.display();
		m_AITakeTurnFunction();
	}
	else if (Global::g_isLMBPressed && m_playerHandler.getPlayer(m_turnHandler.getCurrentPlayerIndex()).getDoesPlayerHaveHeroes())
	{
		int tileIndex = m_tileHandler.checkTileCollision(mousePosition);
		if (tileIndex > -1) //If there is no tile collision, function above returns -1, this makes sure that there was a collision between tile and mouse
		{
			Tile* pTile = m_tileHandler.getTile(tileIndex);

			//Determines interaction based on tile properties
			if (pTile->getIsOccupied() && pTile->getMapObjectType() != MapObjectsEnum::landscape) //Check if its occupied and it's not landscape map object
			{
				movePlayer(tileIndex);
			}
			else if (pTile->getIsObstacle())
			{
				//Don't move
			}
			else
			{
				movePlayer(tileIndex);
			}
			
		}

		Global::objectPressed();
	}

	if (Global::g_isRMBPressed)
	{
		int tileIndex = m_tileHandler.checkTileCollision(mousePosition);

		checkIfAHeroWasPressed(tileIndex);

		updateMapObjInfoFeedback(mousePosition, tileIndex);

		Global::RMBPressed();
	}
}

void MapHandler::checkIfKeyWasPressed()
{
	static bool canSpaceBePressed = false;

	//Space
	if (!canSpaceBePressed && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		canSpaceBePressed = true;
	}

	if (canSpaceBePressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		objectInteraction();
		canSpaceBePressed = false;
	}
}

void MapHandler::updateMapObjInfoFeedback(const sf::Vector2f& mousePosition, const int& tileIndex)
{
	if (!m_UIHandler.getMapObjectsInformationBoxReference().getIsActive())
	{
		Tile& tile = *m_tileHandler.getTile(tileIndex);
		if (tile.getIsOccupied())
		{
			int objectVectorIndex = tile.getMapObjectVectorIndex();
			bool setPopUp = false;
			bool wasBuildingVisited = false; //For special buildings
			std::string textToSet = "";
			sf::Vector2f windowMousePosition = sf::Vector2f(m_window.mapCoordsToPixel(mousePosition).x, m_window.mapCoordsToPixel(mousePosition).y);

			switch (tile.getMapObjectType())
			{
			case MapObjectsEnum::town:
				setPopUp = true;
				if (m_townMapObjects[objectVectorIndex]->getOwnerIndex() >= 0)
				{
					textToSet = "This town is owned by: " + m_gameSetUpScreen.getPlayerName(m_townMapObjects[objectVectorIndex]->getOwnerIndex());
				}
				else
				{
					textToSet = "This town is not owned by any player";
				}
				break;

			case MapObjectsEnum::unit:
				setPopUp = true;
				textToSet = "Number of units: " + std::to_string(m_unitMapObjects[objectVectorIndex]->getNumberOfUnits());
				break;

			case MapObjectsEnum::specialBuilding:
				setPopUp = true;
				for (int& visitedIndex : m_playerHandler.getPlayer(m_turnHandler.getCurrentPlayerIndex()).getSelectedHero().getVectorOfVisitedSpecialBuildingsIndexes())
				{
					if (objectVectorIndex == visitedIndex)
					{
						wasBuildingVisited = true;
						break;
					}
				}

				if (wasBuildingVisited)
				{
					textToSet = "This building was visited by selected hero";
				}
				else
				{
					textToSet = "This building was not visited by selected hero";
				}
				break;

			case MapObjectsEnum::resourceMine:
				setPopUp = true;
				if (m_resourceMinesMapObjects[objectVectorIndex]->getOwnerIndex() >= 0)
				{
					textToSet = "This mine is owned by: " + m_gameSetUpScreen.getPlayerName(m_resourceMinesMapObjects[objectVectorIndex]->getOwnerIndex());
				}
				else
				{
					textToSet = "This mine is not owned by any player";
				}

				break;

			case MapObjectsEnum::resource:
				setPopUp = true;
				textToSet = "Number of resources: " + std::to_string(m_resourceMapObjects[objectVectorIndex]->getResourceAmount());
				break;

			case MapObjectsEnum::none:
			case MapObjectsEnum::landscape:
			default:
				break;
			}

			if (setPopUp)
			{
				m_UIHandler.getMapObjectsInformationBoxReference().setInformation(windowMousePosition, textToSet);
			}
		}
	}
}

void MapHandler::movePlayer(const int& tileIndex)
{
	if (tileIndex != m_playerHandler.getPlayer(m_turnHandler.getCurrentPlayerIndex()).getSelectedHero().getOccupiedTileIndex())
	{
		if (m_isPathValid && m_tileIndexToMoveTo == tileIndex)
		{
			m_playerHandler.getPlayer(m_turnHandler.getCurrentPlayerIndex()).getSelectedHero().decrementMovementPoints(m_numOfMovementPointsTheMoveWillConsume);
			m_playerHandler.getPlayer(m_turnHandler.getCurrentPlayerIndex()).getSelectedHero().setMovementPath(m_tileHandler.getTilePositionVectorForThePathFound()); //Set found path to the player

			m_heroMovementFeedback.setIsActive(false);
			m_isPathValid = false;
		}
		else
		{
			setOutAPath(tileIndex);
		}
	}
}

void MapHandler::setOutAPath(const int& tileIndex)
{
	//Gets tile index that the hero is currently on
	int startTileIndex = m_tileHandler.checkTileCollision(m_playerHandler.getPlayer(m_turnHandler.getCurrentPlayerIndex()).getSelectedHero().getPosition());
	bool isUnitProtectingATile = false;

	//Sets appropriate variables to find a path
	m_tileHandler.setTileProperty(startTileIndex, TilePropertiesEnum::start);
	m_tileHandler.setTileProperty(tileIndex, TilePropertiesEnum::end);

	m_tileHandler.findPath();

	m_isPathValid = checkIfPathIsWithinMovementRange(); //m_isPathValid is used when determine to move using set path / find a new path if false
	if (m_isPathValid)
	{
		m_tileIndexToMoveTo = tileIndex;
	}
	m_heroMovementFeedback.setMovementPathFeedback(m_numOfPositionsWithinRange, &m_tileHandler.getTilePositionVectorForThePathFound());
}

void MapHandler::objectInteraction()
{
	int playerIndex = m_turnHandler.getCurrentPlayerIndex();
	int tileIndex = m_tileHandler.checkTileCollision(m_playerHandler.getPlayer(m_turnHandler.getCurrentPlayerIndex()).getSelectedHero().getPosition());
	m_playerHandler.getPlayer(m_turnHandler.getCurrentPlayerIndex()).getSelectedHero().setOccupiedTileIndex(tileIndex);

	if (tileIndex > -1) //Makes sure that tile index is valid
	{
		//Set appropriate variables
		Tile* pTile = m_tileHandler.getTile(tileIndex);
		Player& rPlayer = m_playerHandler.getPlayer(m_turnHandler.getCurrentPlayerIndex());

		int objectVectorIndex = 0;
		int resourceValue = 0;
		int ownerIndex = -1;
		bool buildingVisited = false;
		bool isUnitProtectingThatTile = false;
		int protectingUnitVectorIndex = 0;

		//Check if player initiated combat vs another player
		for (int i = 0; i < m_playerHandler.getNumberOfPlayers(); i++)
		{
			if (i != m_turnHandler.getCurrentPlayerIndex())
			{
				for (std::unique_ptr<Hero>& defenderHero : m_playerHandler.getPlayer(i).getVectorOfOwnedHeroes())
				{
					if (defenderHero->getOccupiedTileIndex() == tileIndex)
					{
						m_combatHandler.setUpPlayerVsPlayer(&rPlayer.getSelectedHero(), &*defenderHero, rPlayer.getIsPlayerAI(), m_playerHandler.getPlayer(i).getIsPlayerAI());
						return;
						break;
					}
				}
			}
		}


		//Check if the tile is protected by a unit
		if (pTile->getIsOccupied())
		{
			for (auto& tileNeighbour : pTile->getSurroundingTilesVector()) //Loop through neighbouring tiles
			{
				if (tileNeighbour->getMapObjectType() == MapObjectsEnum::unit) //Check if the neighbour tile has a map unit on it
				{
					if (tileNeighbour->getTileVectorIndex() >= tileIndex - 1) //Makes sure that the tile is in the range of protected tiles by the map unit
					{
						isUnitProtectingThatTile = true;
						protectingUnitVectorIndex = tileNeighbour->getMapObjectVectorIndex();
						break;
					}
				}
			}   
		}

		if (isUnitProtectingThatTile)
		{
			//Unit interaction
			m_combatHandler.setUpPlayerVsMapUnit(&rPlayer.getSelectedHero(), &*m_unitMapObjects[protectingUnitVectorIndex], rPlayer.getIsPlayerAI());
		}
		else
		{
			if (pTile->getIsOccupied()) //Checks if tile is occupied
			{
				objectVectorIndex = pTile->getMapObjectVectorIndex();

				switch (pTile->getMapObjectType()) //Checks what map object is on this tile
				{
				case MapObjectsEnum::none:
					//Nothing
					break;

				case MapObjectsEnum::town:
					m_mapUI.setIsActive(false);
					m_UIHandler.getHeroPanelReference().setIsActive(false);
					if (m_townMapObjects[objectVectorIndex]->getOwnerIndex() == m_turnHandler.getCurrentPlayerIndex())
					{
						m_UIHandler.getTownReference().setTownData(m_townMapObjects[objectVectorIndex]->getFactionIndex(), *m_townData[objectVectorIndex], m_dataHandler.getFactionData(m_townMapObjects[objectVectorIndex]->getFactionIndex()).getBuildingsData(), rPlayer, true);
					}
					else
					{
						bool doesTownHaveUnitsInIt = false;
						for (auto& unit : m_townData[objectVectorIndex]->getVectorOfUnitsStationedInsideTheTown())
						{
							if (unit->getIsDataSet())
							{
								doesTownHaveUnitsInIt = true;
								break;
							}
						}

						if (doesTownHaveUnitsInIt) //Battle
						{
							m_combatHandler.setUpPlayerVsTown(&rPlayer.getSelectedHero(), &m_townData[objectVectorIndex]->getVectorOfUnitsStationedInsideTheTown(), rPlayer.getIsPlayerAI(), m_playerHandler.getPlayer(m_townMapObjects[objectVectorIndex]->getOwnerIndex()).getIsPlayerAI());
						}
						else //Occupy the town
						{
							//Remove town from current owner
							removeTownFromCurrentOwner(objectVectorIndex);

							//Set new owner, enmter town and update ui
							addNewTownToCurrentPlayer(objectVectorIndex);
						}
					}
					break;

				case MapObjectsEnum::unit:
					//Battle
					m_combatHandler.setUpPlayerVsMapUnit(&rPlayer.getSelectedHero(), &*m_unitMapObjects[pTile->getMapObjectVectorIndex()], rPlayer.getIsPlayerAI());
					break;

				case MapObjectsEnum::specialBuilding:
					//Check if building was visited
					for (int visitedIndex : rPlayer.getSelectedHero().getVectorOfVisitedSpecialBuildingsIndexes())
					{
						if (visitedIndex == objectVectorIndex)
						{
							buildingVisited = true;
							break;
						}
					}

					if (!buildingVisited)
					{
						rPlayer.getSelectedHero().getVectorOfVisitedSpecialBuildingsIndexes().push_back(objectVectorIndex);
						m_UIHandler.getSpecialBuildingsInteractionReference().specialInteraction(m_specialBuildingsMapObjects[objectVectorIndex]->getBuildingType(), &m_playerHandler.getPlayer(m_turnHandler.getCurrentPlayerIndex()));
					}
					break;

				case MapObjectsEnum::resourceMine:
					ownerIndex = m_resourceMinesMapObjects[objectVectorIndex]->getOwnerIndex();
					if (ownerIndex != m_turnHandler.getCurrentPlayerIndex())
					{
						if (ownerIndex >= 0 && ownerIndex < m_numOfPlayers)
						{
							m_playerHandler.getPlayer(ownerIndex).decrementOwnedMines(m_resourceMinesMapObjects[objectVectorIndex]->getMineType());
						}
						rPlayer.incrementOwnedMines(m_resourceMinesMapObjects[objectVectorIndex]->getMineType());
						m_resourceMinesMapObjects[objectVectorIndex]->setOwnerIndex(m_turnHandler.getCurrentPlayerIndex());
						updateResourcesPerTurnMapUI();
					}
					break;

				case MapObjectsEnum::resource:
				{
					//Add collected resources
					rPlayer.getResources().incrementResourceValue(m_resourceMapObjects[objectVectorIndex]->getResourceType(), m_resourceMapObjects[objectVectorIndex]->getVariable(MapObjectDataEnum::Resource::resourceAmount));

					//Update resource bar UI
					m_UIHandler.getResourceBarReference().updateResourcesBarValues(rPlayer.getResources());

					//Delete map object
					deleteMapObjectFromMapSection(m_resourceMapObjects[objectVectorIndex]->getPosition()); //Delete the object from the map section so it will no longer be drawn

					m_resourceMapObjects.erase(m_resourceMapObjects.begin() + objectVectorIndex); //Delete the object from map data vector
					for (int i = objectVectorIndex; i < m_resourceMapObjects.size(); i++)
					{
						m_tileHandler.getTile(m_resourceMapObjects[i]->getTileIndex())->decrementMapObjectVectorIndex(); //Adjust object index references to match edited vector
					}

					//Reset tile
					pTile->resetTileProperties();

					m_audio.playSFX(SFXEnum::pickup);
				}
				break;

				case MapObjectsEnum::landscape:
					//Nothing
					break;

				default:
					break;
				}
			}
		}
	}
}

void MapHandler::nextTurn()
{
	if (m_turnHandler.incrementCurrentPlayer()) //If true, turn was incremented
	{
		for (auto& player : m_playerHandler.getVectorOfPlayers())
		{
			player->addResourcesGainedPerTurnToPlayersResources();

			for (auto& hero : player->getVectorOfOwnedHeroes())
			{
				hero->resetMovementPoints();
			}

			for (int& townIndex : player->getVectorOfOwnedTownsIndexes())
			{
				m_townData[townIndex]->getTownBuildingData().setCanBuildingBePurchased(true);
			}
		}

		if (!(m_turnHandler.getCurrentTurn() % settings::c_numberOfDaysPerWeek)) //Every 7 days refresh number of units available to recruit
		{
			for (auto& townData : m_townData)
			{
				townData->addWeeklyUnitsToRecruit();
			}

			m_audio.playSFX(SFXEnum::newWeek);
		}
		else
		{
			m_audio.playSFX(SFXEnum::newDay);
		}
	}

	m_audio.playMusic(MusicEnum::mapMusic, 0); //Resets music to synch with player turn, indicates a new turn

	updateEntireMapUI();

	//Reset hero movement variables
	m_isPathValid = false;
	m_heroMovementFeedback.setIsActive(false);

	//Set up hero for next turn
	Player& currentPlayer = m_playerHandler.getPlayer(m_turnHandler.getCurrentPlayerIndex());

	//Set view to main hero
	if (currentPlayer.getDoesPlayerHaveHeroes())
	{
		currentPlayer.setSelectedHeroIndex(0);
		m_viewManager.setGameViewPosition(currentPlayer.getSelectedHero().getPosition());
	}
	else
	{
		int playersFirstTownIndex = currentPlayer.getVectorOfOwnedTownsIndexes()[0];
		m_viewManager.setGameViewPosition(m_townMapObjects[playersFirstTownIndex]->getPosition());
	}

	//Make sure the proper variables are active
	Global::g_UILayer = UILayerEnum::map;
	Global::g_updateGame = true;
}

void MapHandler::updateEntireMapUI()
{
	m_UIHandler.getResourceBarReference().updateResourcesBarValues(m_playerHandler.getPlayer(m_turnHandler.getCurrentPlayerIndex()).getResources());
	updateCurrentTurnMapUI();
	updateResourcesPerTurnMapUI();
	updateTownsMapUI();
	updateHeroesMapUI();
}

void MapHandler::updateTownsMapUI()
{
	IconButtonList& townButtonList = m_mapUI.getTownButoonList();
	Player& currentPlayer = m_playerHandler.getPlayer(m_turnHandler.getCurrentPlayerIndex());


	//Update Towns
	std::vector<int>& ownedTownsIndexes = currentPlayer.getVectorOfOwnedTownsIndexes();
	townButtonList.resetButtonIcons(); //Reset all buttons

	if (townButtonList.getNumberOfButtonsInUse() < ownedTownsIndexes.size()) //Makes sure there are enough spaces
	{
		for (int i = 0; i < ownedTownsIndexes.size() - townButtonList.getNumberOfButtonsInUse(); i++)
		{
			townButtonList.addNewButtonIcon(m_textures.m_baseMapUIButtonIcon); //Make new buttons if there isn't enough space
		}
	}
	
	int iteratorIndex = 0;
	for (int& townIndex : ownedTownsIndexes) //Loop through all owned towns
	{
		townButtonList.updateButtonIcon(iteratorIndex, m_dataHandler.getFactionData(m_townMapObjects[townIndex]->getFactionIndex()).getBuildingsData().getTownIconTexture());  //Updates button icons based on town type
		iteratorIndex++;
	}
}

void MapHandler::updateHeroesMapUI()
{
	IconButtonList& heroButtonList = m_mapUI.getHeroButoonList();
	Player& currentPlayer = m_playerHandler.getPlayer(m_turnHandler.getCurrentPlayerIndex());

	auto& vectorOfHeroes = currentPlayer.getVectorOfOwnedHeroes();
	heroButtonList.resetButtonIcons();

	if (heroButtonList.getNumberOfButtonsInUse() < vectorOfHeroes.size()) //Makes sure there are enough spaces
	{
		for (int i = 0; i < vectorOfHeroes.size() - heroButtonList.getNumberOfButtonsInUse(); i++)
		{
			heroButtonList.addNewButtonIcon(m_textures.m_baseMapUIButtonIcon); //Make new buttons if there isn't enough space
		}
	}

	int iteratorIndex = 0;
	for (auto& hero : vectorOfHeroes)
	{
		heroButtonList.updateButtonIcon(iteratorIndex, m_textures.m_defaultHeroButtonIcon); //Update button icon
		iteratorIndex++;
	}
}

void MapHandler::updateCurrentTurnMapUI()
{
	//Update Turn Information
	TextBox& turnInformation = m_mapUI.getTurnInformationTextBox();
	int currentTurn = m_turnHandler.getCurrentTurn();
	int month = 0;
	int week = 0;
	int day = 0;

	if (currentTurn > 0)
	{
		month = currentTurn / settings::c_numberOfDaysPerMonth;

		currentTurn -= month * settings::c_numberOfDaysPerMonth;

		week = currentTurn / settings::c_numberOfDaysPerWeek;

		currentTurn -= week * settings::c_numberOfDaysPerWeek;

		day = currentTurn;
	}

	std::string turnInformationString = "Day: " + std::to_string(day + 1) + " Week: " + std::to_string(week) + " Month: " + std::to_string(month);
	turnInformation.setTextAndUpdate(turnInformationString);
}

void MapHandler::updateResourcesPerTurnMapUI()
{
	Player& currentPlayer = m_playerHandler.getPlayer(m_turnHandler.getCurrentPlayerIndex());
	TextBox& resourcesPerTurn = m_mapUI.getResourcesPerTurnTextBox();

	currentPlayer.updateResourcesPerTurn();

	std::string resourcesPerTurnString = "Gold: " + std::to_string(currentPlayer.getNumberOfResourcesPerTurn(ResourcesEnum::gold)) +
		", Wood: " + std::to_string(currentPlayer.getNumberOfResourcesPerTurn(ResourcesEnum::wood)) +
		", Stone: " + std::to_string(currentPlayer.getNumberOfResourcesPerTurn(ResourcesEnum::stone));
	
	resourcesPerTurn.setTextAndUpdate(resourcesPerTurnString);
}

void MapHandler::enterTown(const int& townIndex)
{
	if (m_playerHandler.getPlayer(m_turnHandler.getCurrentPlayerIndex()).getVectorOfOwnedTownsIndexes().size() > townIndex)
	{
		int townObjectVectorIndex = m_playerHandler.getPlayer(m_turnHandler.getCurrentPlayerIndex()).getVectorOfOwnedTownsIndexes()[townIndex];
		m_UIHandler.getTownReference().setTownData(m_townMapObjects[townObjectVectorIndex]->getFactionIndex(), *m_townData[townObjectVectorIndex], m_dataHandler.getFactionData(m_townMapObjects[townObjectVectorIndex]->getFactionIndex()).getBuildingsData(), m_playerHandler.getPlayer(m_turnHandler.getCurrentPlayerIndex()), false);
	}
}

void MapHandler::selectHero(const int& heroIndex)
{
	if (m_playerHandler.getPlayer(m_turnHandler.getCurrentPlayerIndex()).getVectorOfOwnedHeroes().size() > heroIndex)
	{
		m_viewManager.setGameViewPosition(m_playerHandler.getPlayer(m_turnHandler.getCurrentPlayerIndex()).getHero(heroIndex).getPosition());
		m_UIHandler.getHeroPanelReference().setHeroData(&m_playerHandler.getPlayer(m_turnHandler.getCurrentPlayerIndex()).getHero(heroIndex), true);
		m_playerHandler.getPlayer(m_turnHandler.getCurrentPlayerIndex()).setSelectedHeroIndex(heroIndex);
	}
}

const bool MapHandler::checkIfAHeroWasPressed(const int& tilePressed)
{
	bool didPlayerClickOnAHero = false;
	int heroIterator = 0;

	//Check current Player heroes
	std::vector<std::unique_ptr<Hero>>& currentPlayerHeroVector = m_playerHandler.getPlayer(m_turnHandler.getCurrentPlayerIndex()).getVectorOfOwnedHeroes();
	for (std::unique_ptr<Hero>& hero : currentPlayerHeroVector)
	{
		if (hero->getOccupiedTileIndex() == tilePressed)
		{
			didPlayerClickOnAHero = true;
			selectHero(heroIterator);
			m_UIHandler.getHeroPanelReference().setIsActive(true);
			break;
		}
		heroIterator++;
	}

	//If current player hero wasn't selected check if enemy hero was
	if (!didPlayerClickOnAHero)
	{
		for (int i = 0; i < m_playerHandler.getNumberOfPlayers(); i++)
		{
			if (i != m_turnHandler.getCurrentPlayerIndex())
			{
				for (std::unique_ptr<Hero>& hero : m_playerHandler.getPlayer(i).getVectorOfOwnedHeroes())
				{
					if (hero->getOccupiedTileIndex() == tilePressed)
					{
						didPlayerClickOnAHero = true;
						m_UIHandler.getHeroPanelReference().setHeroData(&*hero, false);
						m_UIHandler.getHeroPanelReference().setIsActive(true);
						break;
					}
				}
			}
		}
	}

	return didPlayerClickOnAHero;
}

TileHandler* MapHandler::getTileHandlerPointer()
{
	return &m_tileHandler;
}

void MapHandler::deleteMapObjectFromMapSection(const sf::Vector2f& objectPosition)
{
	//Calculate map section index
	int x = std::floor((objectPosition.x / m_tileSize) / settings::c_drawQuadrantWidth);
	int y = std::floor((objectPosition.y / m_tileSize) / settings::c_drawQuadrantHeight);
	int mapSectionIndex = y * m_maxHorizontalQuadrants + x;

	int objectIndex = 0;

	//Checks for matching position to find correct map object to delete
	for (auto mapObject : m_mapQuadrants[mapSectionIndex]->getMapObjectPointersVector())
	{
		if (mapObject->getPosition() == objectPosition)
		{
			m_mapQuadrants[mapSectionIndex]->getMapObjectPointersVector().erase(m_mapQuadrants[mapSectionIndex]->getMapObjectPointersVector().begin() + objectIndex);
			break;
		}
		objectIndex++;
	}
}

void MapHandler::addNewTownToCurrentPlayer(const int& townIndex)
{
	m_townMapObjects[townIndex]->setOwnerIndex(m_turnHandler.getCurrentPlayerIndex());
	m_playerHandler.getPlayer(m_turnHandler.getCurrentPlayerIndex()).addOwnedTown(townIndex);
	updateTownsMapUI();
	if (Global::g_UILayer != UILayerEnum::gameEnd)
	{
		m_UIHandler.getTownReference().setTownData(m_townMapObjects[townIndex]->getFactionIndex(), *m_townData[townIndex], m_dataHandler.getFactionData(m_townMapObjects[townIndex]->getFactionIndex()).getBuildingsData(), m_playerHandler.getPlayer(m_turnHandler.getCurrentPlayerIndex()), true);
	}
}

void MapHandler::removeTownFromCurrentOwner(const int& townIndex)
{
	//Remove town from current owner
	int townOwnerIndex = m_townMapObjects[townIndex]->getOwnerIndex();
	std::vector<int>& townOwnersOwnedTowns = m_playerHandler.getPlayer(townOwnerIndex).getVectorOfOwnedTownsIndexes();
	for (int i = 0; i < townOwnersOwnedTowns.size(); i++)
	{
		if (townOwnersOwnedTowns[i] == townIndex)
		{
			townOwnersOwnedTowns.erase(townOwnersOwnedTowns.begin() + i);
			break;
		}
	}

	checkIfPlayerHasNoHeroesAndTownsLeft(townOwnerIndex);
}

void MapHandler::checkIfPlayerHasNoHeroesAndTownsLeft(const int& playerIndex)
{
	Player& player = m_playerHandler.getPlayer(playerIndex);

	if (!player.getDoesPlayerHaveHeroes() && player.getVectorOfOwnedTownsIndexes().size() <= 0)
	{
		deletePlayer(playerIndex);
	}
}

void MapHandler::deleteHero(const int playerIndex, const int heroIndex)
{
	auto& vectorOfHeroes = m_playerHandler.getPlayer(playerIndex).getVectorOfOwnedHeroes();
	vectorOfHeroes.erase(vectorOfHeroes.begin() + heroIndex);
	if (vectorOfHeroes.size() > 0)
	{
		m_playerHandler.getPlayer(playerIndex).setSelectedHeroIndex(vectorOfHeroes.size() - 1);
	}
}

void MapHandler::deletePlayer(const int playerIndex)
{
	//Update appropriate player turn
	if (m_turnHandler.getCurrentPlayerIndex() >= playerIndex)
	{
		m_turnHandler.setCurrentPlayerIndex(m_turnHandler.getCurrentPlayerIndex() - 1);
	}

	//Update player index references
	for (int i = playerIndex; i < m_playerHandler.getNumberOfPlayers(); i++)
	{
		for (int& townIndex : m_playerHandler.getPlayer(i).getVectorOfOwnedTownsIndexes())
		{
			m_townMapObjects[townIndex]->setOwnerIndex(i - 1);
		}

		for (auto& hero : m_playerHandler.getPlayer(i).getVectorOfOwnedHeroes())
		{
			hero->setPlayerIndex(i - 1);
		}
	}

	//Update mine owners
	for (auto& mine : m_resourceMinesMapObjects)
	{
		if (mine->getOwnerIndex() >= playerIndex)
		{
			mine->setOwnerIndex(mine->getOwnerIndex() - 1);
		}
	}

	if (m_playerHandler.getPlayer(playerIndex).getIsPlayerAI())
	{
		m_deletePlayerAIDataFunction(playerIndex);
	}

	//Delete player
	m_playerHandler.deletePlayer(playerIndex);

	if (m_playerHandler.getNumberOfPlayers() == 1)
	{
		//Player won
		m_gameEnd.setEndGameInformation(m_playerHandler.getPlayer(0), !m_playerHandler.getPlayer(0).getIsPlayerAI(), m_turnHandler);
		Global::g_UILayer = UILayerEnum::gameEnd;
	}

}

void MapHandler::functionToCallAfterBattleConcluded(const CombatTypeEnum combatType, const bool didAttackerWin)
{
	//Units are automatically updated after fight in combat handler, this is only to update what happends with the losing side
	Global::toggleUpdateGame();

	if (didAttackerWin) //Attacker is always a hero
	{
		//Defender lost
		switch (combatType)
		{
		case CombatTypeEnum::playerVsMapUnit:
			{
				int unitTileIndex = m_combatHandler.getUnitMapObject()->getTileIndex();
				int unitVectorIndex = m_tileHandler.getTile(m_combatHandler.getUnitMapObject()->getTileIndex())->getMapObjectVectorIndex();
				m_tileHandler.getTile(unitTileIndex)->resetTileProperties();

				//Get rid of unit protection zone
				for (auto& neighbourTile : m_tileHandler.getTile(unitTileIndex)->getSurroundingTilesVector())
				{
					if (neighbourTile->getTileVectorIndex() <= unitTileIndex + 1 && neighbourTile->getMapObjectType() == MapObjectsEnum::none)
					{
						neighbourTile->setIsObstacle(false);
					}
				}

				deleteMapObjectFromMapSection(m_combatHandler.getUnitMapObject()->getPosition());
				m_unitMapObjects.erase(m_unitMapObjects.begin() + unitVectorIndex);

				for (int i = unitVectorIndex; i < m_unitMapObjects.size(); i++)
				{
					m_tileHandler.getTile(m_unitMapObjects[i]->getTileIndex())->decrementMapObjectVectorIndex(); //Adjust object index references to match edited vector
				}
			}
			break;

		case CombatTypeEnum::playerVsPlayer:
			{
				if (m_playerHandler.getPlayer(m_combatHandler.getDefenderHero()->getPlayerIndex()).getVectorOfOwnedTownsIndexes().size() > 0)
				{
					//int defenderTownIndex = m_playerHandler.getPlayer(m_combatHandler.getDefenderHero()->getPlayerIndex()).getVectorOfOwnedTownsIndexes()[0];
					//m_combatHandler.getDefenderHero()->setPosition(m_townMapObjects[defenderTownIndex]->getPosition());
					//m_combatHandler.getDefenderHero()->setOccupiedTileIndex(m_townMapObjects[defenderTownIndex]->getTileIndex());
					//m_combatHandler.getDefenderHero()->setCurrentMovementPoints(0);
					//
					////Add 1 tier 1 unit to make sure that you won't get error when starting combat
					//m_combatHandler.getDefenderHero()->addUnit(0, m_townData[defenderTownIndex]->getUnitData(0));
					//m_combatHandler.getDefenderHero()->getUnit(0).incrementNumOfUnits(1);
					//m_combatHandler.getDefenderHero()->updateNumberOfUnits();
					deleteHero(m_combatHandler.getDefenderHero()->getPlayerIndex(), 0);
				}
				else
				{
					deletePlayer(m_combatHandler.getDefenderHero()->getPlayerIndex());
				}
			}
			break;

		case CombatTypeEnum::playerVsTown:
			{
				//do nothing
			}
			break;

		default:
			break;
		}

		objectInteraction(); //Check if attacker is on an interactable object
	}
	else //Attacker lost
	{
		//Sent Hero who lost back to their starting town
		if (m_playerHandler.getPlayer(m_combatHandler.getAttackerHero()->getPlayerIndex()).getVectorOfOwnedTownsIndexes().size() > 0)
		{
			//int attackerTownIndex = m_playerHandler.getPlayer(m_combatHandler.getAttackerHero()->getPlayerIndex()).getVectorOfOwnedTownsIndexes()[0];
			//m_combatHandler.getAttackerHero()->setPosition(m_townMapObjects[attackerTownIndex]->getPosition());
			//m_combatHandler.getAttackerHero()->setOccupiedTileIndex(m_townMapObjects[attackerTownIndex]->getTileIndex());
			//m_combatHandler.getAttackerHero()->setCurrentMovementPoints(0);
			//
			////Add 1 tier 1 unit to make sure that you won't get error when starting combat
			//m_combatHandler.getAttackerHero()->addUnit(0, m_townData[attackerTownIndex]->getUnitData(0));
			//m_combatHandler.getAttackerHero()->getUnit(0).incrementNumOfUnits(1);
			//m_combatHandler.getAttackerHero()->updateNumberOfUnits();

			deleteHero(m_combatHandler.getAttackerHero()->getPlayerIndex(), 0);
		}
		else
		{
			deletePlayer(m_combatHandler.getAttackerHero()->getPlayerIndex());
		}
	}

	m_audio.playMusic(MusicEnum::mapMusic, 0);
}

const bool MapHandler::checkIfPathIsWithinMovementRange()
{
	bool isPathWithingMovementRange = true;
	int movementPointsConsumed = 0;
	int maxMovementPoints = m_playerHandler.getPlayer(m_turnHandler.getCurrentPlayerIndex()).getSelectedHero().getCurrentMovementPoints();
	auto& path = m_tileHandler.getTilePositionVectorForThePathFound();
	int pathSize = path.size();

	for (int i = pathSize - 1; i >= 1; i--) //Loop through all movement positions and calculate movement cost
	{
		movementPointsConsumed += calculateHowManyMovementPointsTheMoveConsumes(path[i - 1], path[i]);
		if (movementPointsConsumed > maxMovementPoints) //Check if movement cost exceeds heros movement points
		{
			isPathWithingMovementRange = false;
			m_numOfPositionsWithinRange = pathSize - i;
			break;
		}
		m_numOfPositionsWithinRange = pathSize - i;
	}

	if (isPathWithingMovementRange)
	{
		m_numOfMovementPointsTheMoveWillConsume = movementPointsConsumed;
		m_numOfPositionsWithinRange++;
	}

	return isPathWithingMovementRange;
}

const int MapHandler::calculateHowManyMovementPointsTheMoveConsumes(const sf::Vector2f& posA, const sf::Vector2f& posB)
{
	int movementPointsConsumed = 0;

	//Check horizontal
	if (abs(posA.x - posB.x) >= m_tileSize)
	{
		movementPointsConsumed++;
	}

	//Check vertical
	if (abs(posA.y - posB.y) >= m_tileSize)
	{
		movementPointsConsumed++;
	}

	return movementPointsConsumed;
}

void MapHandler::draw()
{
	int quadrantIndex = 0;
	int startCollumn = m_viewManager.getFirstMapSectionToDraw() % m_maxHorizontalQuadrants - 1;
	if (startCollumn < 0)
	{
		startCollumn = 0;
	}

	int startRow = std::floor(m_viewManager.getFirstMapSectionToDraw() / m_maxHorizontalQuadrants);

	//Determine which map sections to draw
	int firstHorizontalSectionToDraw = startCollumn + m_horizontalQuadrantsToDisplay;
	if (firstHorizontalSectionToDraw > m_maxHorizontalQuadrants)
	{
		firstHorizontalSectionToDraw = m_maxHorizontalQuadrants;
	}

	//Draw tiles
	for (int row = startRow; row < startRow + m_verticalQuadrantsToDisplay; row++)
	{
		if (row < m_maxVerticalQuadrants)
		{
			for (int collumn = firstHorizontalSectionToDraw - 1; collumn >= startCollumn; collumn--)
			{
				quadrantIndex = collumn + (row * m_maxHorizontalQuadrants);

				m_tileHandler.drawSpecificTiles(m_mapQuadrants[quadrantIndex]->getTileIndexesVector());
			}
		}
		else
		{
			break;
		}
	}

	//Draw map objects
	for (int row = startRow; row < startRow + m_verticalQuadrantsToDisplay; row++)
	{
		if (row < m_maxVerticalQuadrants)
		{
			for (int collumn = firstHorizontalSectionToDraw - 1; collumn >= startCollumn; collumn--)
			{
				quadrantIndex = collumn + (row * m_maxHorizontalQuadrants);

				for (MapObject* mapObject : m_mapQuadrants[quadrantIndex]->getMapObjectPointersVector())
				{
					m_window.draw(*mapObject);
				}
			}
		}
		else
		{
			break;
		}
	}

	m_heroMovementFeedback.draw();
}

void MapHandler::setFunctionToCallWhenDeletingAIPlayer(std::function<void(int)> function)
{
	m_deletePlayerAIDataFunction = function;
}

std::vector<std::unique_ptr<TownMapObject>>& MapHandler::getVectorOfTownMapObjects()
{
	return m_townMapObjects;
}

std::vector<std::unique_ptr<TownData>>& MapHandler::getVectorOfTownDatas()
{
	return m_townData;
}

std::vector<std::unique_ptr<UnitMapObject>>& MapHandler::getVectorOfUnitMapObjects()
{
	return m_unitMapObjects;
}

std::vector<std::unique_ptr<ResourceMineMapObject>>& MapHandler::getVectorOfResourceMineObjects()
{
	return m_resourceMinesMapObjects;
}

std::vector<std::unique_ptr<ResourceMapObject>>& MapHandler::getVectorOfResourceObjects()
{
	return m_resourceMapObjects;
}

std::vector<std::unique_ptr<SpecialBuildingMapObject>>& MapHandler::getVectorOfSpecialBuildingMapObjects()
{
	return m_specialBuildingsMapObjects;
}
