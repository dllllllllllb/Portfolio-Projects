#include "TownData.h"

TownData::TownData() :
	m_occupiedTileIndex(0)
{
	//Set base data for unit recruitment
	for (int i = 0; i < c_numOfUnitsPerFaction; i++)
	{
		m_unitData[i] = nullptr;
		m_availableUnitsToRecruit.push_back(0);
	}

	//Reserve memory for units stationed inside the town
	for (int i = 0; i < c_numOfUnitsPerFaction; i++)
	{
		m_unitsStationedInsideTheTown.push_back(std::shared_ptr<Unit>(new Unit()));
	}
}

TownData::~TownData()
{
}

void TownData::setUnitData(const int& unitIndex, UnitData& unitData)
{
	m_unitData[unitIndex] = &unitData;
}

UnitData* TownData::getUnitData(const int& unitIndex) const
{
	return m_unitData[unitIndex];
}

void TownData::setTownBuildingData( TownBuildingData& townBuildingData)
{
	m_townBuildingData = townBuildingData;
}

TownBuildingData& TownData::getTownBuildingData()
{
	return m_townBuildingData;
}

std::vector<int>& TownData::getAvailableUnitsToRecruit()
{
	return m_availableUnitsToRecruit;
}

void TownData::addUnit(const int& vectorIndex, UnitData* unitToAdd)
{
	m_unitsStationedInsideTheTown[vectorIndex]->setBaseUnitData(unitToAdd);
	m_unitsStationedInsideTheTown[vectorIndex]->toggleIsDataSet();
	m_unitsStationedInsideTheTown[vectorIndex]->initializeUnitSpecificData();
}

std::vector<std::shared_ptr<Unit>>& TownData::getVectorOfUnitsStationedInsideTheTown()
{
	return m_unitsStationedInsideTheTown;
}

void TownData::addWeeklyUnitsToRecruit()
{
	float availableUnitsMultiplier = 1;
	availableUnitsMultiplier += (0.5f * m_townBuildingData.getData(TownBuildingEnum::fort)); //Level 2 fort gives 2x the normal units

	for (int i = 0; i < c_numOfUnitsPerFaction; i++)
	{
		if (m_townBuildingData.getData(static_cast<TownBuildingEnum>(5 + i))) //5 == first unit data position in enum
		{
			m_availableUnitsToRecruit[i] += static_cast<int>(m_unitData[i]->getIntData(UnitDataEnum::growthPerWeek) * availableUnitsMultiplier);
		}
	}
}

void TownData::setMapData(const int& occupiedTileIndex, const sf::Vector2f& townPosition)
{
	m_occupiedTileIndex = occupiedTileIndex;
	m_townMapPosition = townPosition;
}

const int& TownData::getOccupiedTileIndex() const
{
	return m_occupiedTileIndex;
}

const sf::Vector2f& TownData::getTownMapPosition() const
{
	return m_townMapPosition;
}
