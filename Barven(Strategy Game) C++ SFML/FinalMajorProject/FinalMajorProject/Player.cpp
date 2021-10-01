#include "Player.h"

Player::Player(sf::RenderWindow& rWindow) :
	m_window(rWindow),
	m_pTownDataVector(nullptr),
	m_factionIndex(0),
	m_playerIndex(0),
	m_selectedHeroIndex(0),
	m_isPlayerAI(false),
	m_pDataHandler(nullptr),
	m_numOfOwnedGoldMines(0),
	m_numOfOwnedWoodMines(0),
	m_numOfOwnedStoneMines(0),
	m_goldPerTurn(0),
	m_woodPerTurn(0),
	m_stonePerTurn(0)
{
	
}

Player::~Player()
{
}

Resources& Player::getResources()
{
	return m_resources;
}

Hero& Player::getHero(const int& heroIndex)
{
	return *m_heroes[heroIndex];
}

Hero& Player::getSelectedHero()
{
	return *m_heroes[m_selectedHeroIndex];
}

void Player::setFactionIndex(const int& factionIndex)
{
	m_factionIndex = factionIndex;
}

const int& Player::getFactionIndex() const
{
	return m_factionIndex;
}

void Player::setPlayerIndex(const int& playerIndex)
{
	m_playerIndex = playerIndex;
}

const int& Player::getPlayerIndex() const
{
	return m_playerIndex;
}

void Player::setSelectedHeroIndex(const int& heroIndex)
{
	m_selectedHeroIndex = heroIndex;
}

const int& Player::getSelectedHeroIndex() const
{
	return m_selectedHeroIndex;
}

void Player::addOwnedTown(const int& townIndex)
{
	m_ownedTownIndexes.push_back(townIndex);
}

void Player::removeOwnedTown(const int& townIndex)
{
	for (int i = 0; i < m_ownedTownIndexes.size(); i++)
	{
		if (m_ownedTownIndexes[i] == townIndex)
		{
			m_ownedTownIndexes.erase(m_ownedTownIndexes.begin() + i);
			break;
		}
	}
}

std::vector<int>& Player::getVectorOfOwnedTownsIndexes()
{
	return m_ownedTownIndexes;
}

std::vector<std::unique_ptr<Hero>>& Player::getVectorOfOwnedHeroes()
{
	return m_heroes;
}

void Player::setTownDataVectorPointer(std::vector<std::unique_ptr<TownData>>& rTownDataVector)
{
	m_pTownDataVector = &rTownDataVector;
}

void Player::updateResourcesPerTurn()
{
	m_goldPerTurn = m_numOfOwnedGoldMines * ResourcesPerTurnSettings::c_goldPerMine;

	for (int& townIndex : m_ownedTownIndexes)
	{
		m_goldPerTurn += ResourcesPerTurnSettings::c_goldPerTownHallLevel[m_pTownDataVector->at(townIndex)->getTownBuildingData().getData(TownBuildingEnum::townHall)];
	}

	m_woodPerTurn = m_numOfOwnedWoodMines * ResourcesPerTurnSettings::c_woodPerMine;
	m_stonePerTurn = m_numOfOwnedStoneMines * ResourcesPerTurnSettings::c_stonePerMine;
}

void Player::addResourcesGainedPerTurnToPlayersResources()
{
	m_resources.incrementResourceValue(ResourcesEnum::gold, m_goldPerTurn);
	m_resources.incrementResourceValue(ResourcesEnum::wood, m_woodPerTurn);
	m_resources.incrementResourceValue(ResourcesEnum::stone, m_stonePerTurn);
}

void Player::incrementOwnedMines(const ResourcesEnum& mineType)
{
	switch (mineType)
	{
	case ResourcesEnum::gold:
		m_numOfOwnedGoldMines++;
		break;

	case ResourcesEnum::wood:
		m_numOfOwnedWoodMines++;
		break;

	case ResourcesEnum::stone:
		m_numOfOwnedStoneMines++;
		break;

	default:
		break;
	}
}

void Player::decrementOwnedMines(const ResourcesEnum& mineType)
{
	switch (mineType)
	{
	case ResourcesEnum::gold:
		m_numOfOwnedGoldMines--;
		break;

	case ResourcesEnum::wood:
		m_numOfOwnedWoodMines--;
		break;

	case ResourcesEnum::stone:
		m_numOfOwnedStoneMines--;
		break;

	default:
		break;
	}
}

const int& Player::getNumberOfMines(const ResourcesEnum& mineType) const
{
	switch (mineType)
	{
	case ResourcesEnum::gold:
		return m_numOfOwnedGoldMines;
		break;

	case ResourcesEnum::wood:
		return m_numOfOwnedWoodMines;
		break;

	case ResourcesEnum::stone:
		return m_numOfOwnedStoneMines;
		break;

	default:
		return 0;
		break;
	}
}

const int& Player::getNumberOfResourcesPerTurn(const ResourcesEnum& resourceType) const
{
	switch (resourceType)
	{
	case ResourcesEnum::gold:
		return m_goldPerTurn;
		break;

	case ResourcesEnum::wood:
		return m_woodPerTurn;
		break;

	case ResourcesEnum::stone:
		return m_stonePerTurn;
		break;

	default:
		return 0;
		break;
	}
}

void Player::setIsPlayerAI(const bool state)
{
	m_isPlayerAI = state;
}

const bool Player::getIsPlayerAI() const
{
	return m_isPlayerAI;
}

void Player::makeNewHero(const sf::Vector2f& startPosition, const int& occupiedTileIndex, const bool giveHeroBasicUnit)
{
	m_heroes.push_back(std::unique_ptr<Hero>(new Hero()));
	m_heroes[m_heroes.size() - 1]->setPlayerIndex(m_playerIndex);
	m_heroes[m_heroes.size() - 1]->setUpHero(m_pDataHandler->getFactionData(m_factionIndex).getHeroData().getHeroTexture(), startPosition);
	m_heroes[m_heroes.size() - 1]->setOccupiedTileIndex(occupiedTileIndex);
	m_heroes[m_heroes.size() - 1]->setFunctionToCallWhenObjectArrivesAtDestination(m_functionToCallWhenHeroArrivesAtDestination);

	if (giveHeroBasicUnit)
	{
		m_heroes[m_heroes.size() - 1]->addUnit(0, &m_pDataHandler->getFactionData(m_factionIndex).getUnitData(0));
		m_heroes[m_heroes.size() - 1]->getUnit(0).incrementNumOfUnits(1);
		m_heroes[m_heroes.size() - 1]->getUnit(0).initializeUnitSpecificData();
		m_heroes[m_heroes.size() - 1]->updateUnitsStats();
		m_updateHeroesMapUI();
	}
}

void Player::setDataHandlerPointer(DataHandler* pDataHandler)
{
	m_pDataHandler = pDataHandler;
}

void Player::setFunctionToCallWhenHeroArrivesAtDestination(std::function<void()> function)
{
	m_functionToCallWhenHeroArrivesAtDestination = function;
}

void Player::setFunctionToUpdateHeroesMapUI(std::function<void()> function)
{
	m_updateHeroesMapUI = function;
}

const bool Player::getDoesPlayerHaveHeroes()
{
	return m_heroes.size() > 0;
}

void Player::updateHeroes(const float& deltaTime)
{
	for (auto& hero : m_heroes)
	{
		hero->updateMovement(deltaTime);
	}
}

void Player::drawHeros()
{
	for (auto& hero : m_heroes)
	{
		m_window.draw(*hero);
	}
}