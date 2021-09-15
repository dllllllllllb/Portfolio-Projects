#include "FactionBuildingData.h"
FactionBuildingData::FactionBuildingData()
{
}

FactionBuildingData::~FactionBuildingData()
{
}

void FactionBuildingData::loadTextures()
{
	for (int i = 0; i < TownBuildingSettings::c_numOfBuildings; i++)
	{
		m_buildingTextures[i].loadFromFile(m_data["buildingsSprites"][i]);
	}
	m_mapTexture.loadFromFile(m_data["mapSprite"]);
	m_townIcon.loadFromFile(m_data["townIcon"]);
}

sf::Texture& FactionBuildingData::getBuildingTexture(const TownBuildingEnum& building)
{
	return m_buildingTextures[(int)building];
}

sf::Texture& FactionBuildingData::getTownIconTexture()
{
	return m_townIcon;
}

json& FactionBuildingData::getData()
{
	return m_data;
}

sf::Texture& FactionBuildingData::getMapTexture()
{
	return m_mapTexture;
}
