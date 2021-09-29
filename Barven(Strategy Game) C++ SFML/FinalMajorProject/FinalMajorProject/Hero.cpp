#include "Hero.h"

namespace settings = HeroSettings;

Hero::Hero() :
	m_playerIndex(0),
	m_occupiedTileIndex(0),
	m_currentNumberOfUnits(0),
	m_currentMovementPoints(settings::c_maxMovementRange),
	m_heroLevel(1),
	m_currentExperience(0),
	m_experienceRequiredToLevelUp(settings::c_baseExperienceRequirementForLevelUp),
	m_statUpgradePoints(0),
	m_statAttack(1),
	m_statDefence(1),
	m_statMagicPower(1),
	m_statWisdom(1)
{
	//Reserve unit data
	for (int i = 0; i < c_numOfUnitsPerFaction; i++)
	{
		m_heroUnits.push_back(std::shared_ptr<Unit>(new Unit()));
	}
}

Hero::~Hero()
{
}

Unit& Hero::getUnit(const int& index)
{
	return *m_heroUnits[index];
}

std::vector<std::shared_ptr<Unit>>& Hero::getVectorOfUnits()
{
	return m_heroUnits;
}

std::vector<int>& Hero::getVectorOfVisitedSpecialBuildingsIndexes()
{
	return m_indexesOfVisitedSpecialBuildings;
}

void Hero::setUpHero(sf::Texture& heroSprite, const sf::Vector2f& startPosition)
{
	setTexture(heroSprite, true);
	sf::Sprite::setOrigin(0, getGlobalBounds().height - 32);
	sf::Sprite::setPosition(startPosition);
}

void Hero::addUnit(const int& vectorIndex, UnitData* unitToAdd)
{
	m_heroUnits[vectorIndex]->setBaseUnitData(unitToAdd);
	m_heroUnits[vectorIndex]->toggleIsDataSet();
	m_heroUnits[vectorIndex]->initializeUnitSpecificData();
	m_currentNumberOfUnits++;
	updateUnitsStats();
}

void Hero::deleteUnit(const int& vectorIndex)
{
	m_heroUnits[vectorIndex]->resetUnitData();
	m_currentNumberOfUnits--;
}

void Hero::swapUnitsPositionsInVector(const int& unitIndexA, const int& unitIndexB)
{
	auto tempUnit = m_heroUnits[unitIndexA];

	m_heroUnits[unitIndexA] = m_heroUnits[unitIndexB];
	m_heroUnits[unitIndexB] = tempUnit;
}

void Hero::updateNumberOfUnits()
{
	m_currentNumberOfUnits = 0;
	for (auto& unit : m_heroUnits) //Loop through all unit
	{
		if (unit->getIsDataSet()) //Check if the data is set
		{
			m_currentNumberOfUnits++;
		}
	}
}

void Hero::updateUnitsStats()
{
	int meleeDamageValue = 0;
	int defenceValue = 0;

	for (int i = 0; i < c_numOfUnitsPerFaction; i++)
	{
		if (m_heroUnits[i]->getIsDataSet())
		{
			meleeDamageValue = m_heroUnits[i]->getBaseUnitData()->getIntData(UnitDataEnum::attack) + m_statAttack;
			m_heroUnits[i]->setUnitSpecificData(UnitBattleDataEnum::attack, meleeDamageValue);

			defenceValue = m_heroUnits[i]->getBaseUnitData()->getIntData(UnitDataEnum::defence) + m_statDefence;
			m_heroUnits[i]->setUnitSpecificData(UnitBattleDataEnum::defence, defenceValue);
		}
	}
}

void Hero::incrementHeroLevel()
{
	m_heroLevel++;
	m_statUpgradePoints++;
	m_currentExperience -= m_experienceRequiredToLevelUp;
	updateExperienceRequiredToLevelUp();
}

const int& Hero::getHeroLevel() const
{
	return m_heroLevel;
}

void Hero::decrementStatUpgradePoints()
{
	m_statUpgradePoints--;
}

const int& Hero::getStatUpgradePoints() const
{
	return m_statUpgradePoints;
}

void Hero::addHeroExperience(const int& experience)
{
	//Experience gained from defeated enemies is determined by their AIValue, to keep numbers smaller, experience gained is 
	// is multiplied by a fraction defined in HeroSettings.h
	m_currentExperience += experience * settings::c_experienceGainedMultiplier;

	while (m_currentExperience > m_experienceRequiredToLevelUp)
	{
		incrementHeroLevel();
	}
}

void Hero::updateExperienceRequiredToLevelUp()
{
	m_experienceRequiredToLevelUp += settings::c_baseExperienceRequirementForLevelUp;
	m_experienceRequiredToLevelUp *= settings::c_experienceRequiredMultiplier;
}

void Hero::decrementMovementPoints(const int& decrementValue)
{
	m_currentMovementPoints -= decrementValue;
	if (m_currentMovementPoints < 0)
	{
		m_currentMovementPoints = 0;
	}
}

void Hero::setCurrentMovementPoints(const int& movementPoints)
{
	m_currentMovementPoints = movementPoints;
}

void Hero::resetMovementPoints()
{
	m_currentMovementPoints = settings::c_maxMovementRange;
}

const int& Hero::getCurrentMovementPoints() const
{
	return m_currentMovementPoints;
}

void Hero::incrementHeroStat(const HeroStatsEnum& heroStatType, const int& incrementValue)
{
	switch (heroStatType)
	{
	case HeroStatsEnum::attack:
		m_statAttack += incrementValue;
		break;

	case HeroStatsEnum::defence:
		m_statDefence += incrementValue;
		break;

	case HeroStatsEnum::magicPower:
		m_statMagicPower += incrementValue;
		break;

	case HeroStatsEnum::wisdom:
		m_statWisdom += incrementValue;
		break;

	default:
		break;
	}

	updateUnitsStats();
}

const int& Hero::getHeroStat(const HeroStatsEnum& heroStatType)
{
	switch (heroStatType)
	{
	case HeroStatsEnum::attack:
		return m_statAttack;
		break;

	case HeroStatsEnum::defence:
		return m_statDefence;
		break;

	case HeroStatsEnum::magicPower:
		return m_statMagicPower;
		break;

	case HeroStatsEnum::wisdom:
		return m_statWisdom;
		break;

	default:
		break;
	}
}

void Hero::update(const float& deltaTime)
{
	updateMovement(deltaTime);
}

const int& Hero::getCurrentNumberOfUnits() const
{
	return m_currentNumberOfUnits;
}

void Hero::setPlayerIndex(const int& playerIndex)
{
	m_playerIndex = playerIndex;
}

const int& Hero::getPlayerIndex() const
{
	return m_playerIndex;
}

void Hero::setOccupiedTileIndex(const int& tileIndex)
{
	m_occupiedTileIndex = tileIndex;
}

const int& Hero::getOccupiedTileIndex() const
{
	return m_occupiedTileIndex;
}
