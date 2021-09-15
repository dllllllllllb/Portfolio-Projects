#include "FactionData.h"
FactionData::FactionData()
{
}

FactionData::~FactionData()
{
}

UnitData& FactionData::getUnitData(const int& index)
{
	return m_units[index];
}

FactionBuildingData& FactionData::getBuildingsData()
{
	return m_buildings;
}

HeroData& FactionData::getHeroData()
{
	return m_heroData;
}