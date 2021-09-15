#include "MapAIPlayerData.h"
MapAIPlayerData::MapAIPlayerData() : 
	m_playerIndex(0)
{
}

MapAIPlayerData::~MapAIPlayerData()
{
}

void MapAIPlayerData::setPlayerIndex(const int& playerIndex)
{
	m_playerIndex = playerIndex;
}

const int& MapAIPlayerData::getPlayerIndex() const
{
	return m_playerIndex;
}

void MapAIPlayerData::addNewAIHeroData()
{
	m_AIHeroData.push_back(std::unique_ptr<MapAIHeroData>(new MapAIHeroData()));
	m_AIHeroData[m_AIHeroData.size() - 1]->setHeroIndex(m_AIHeroData.size() - 1);
}

MapAIHeroData& MapAIPlayerData::getAIHeroData(const int& index)
{
	return *m_AIHeroData[index];
}

void MapAIPlayerData::deleteAIHeroData(const int& heroDataVectorIndex)
{
	m_AIHeroData.erase(m_AIHeroData.begin() + heroDataVectorIndex);
}

void MapAIPlayerData::updateAIHeroIndex()
{
	for (int i = 0; i < m_AIHeroData.size(); i++)
	{
		m_AIHeroData[i]->setHeroIndex(i);
	}
}
