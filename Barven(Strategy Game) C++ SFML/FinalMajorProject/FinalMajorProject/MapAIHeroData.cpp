#include "MapAIHeroData.h"
MapAIHeroData::MapAIHeroData():
	m_heroIndex(0),
	m_priorityObjectIndex(-1),
	m_priorityTileIndex(-1),
	m_priority(MapAIPriorityEnum::none)
{
}

MapAIHeroData::~MapAIHeroData()
{
}

void MapAIHeroData::setHeroIndex(const int& index)
{
	m_heroIndex = index;
}

const int& MapAIHeroData::getHeroIndex() const
{
	return m_heroIndex;
}

void MapAIHeroData::setPriorityObjectIndex(const int& index)
{
	m_priorityObjectIndex = index;
}

const int& MapAIHeroData::getPriorityObjectIndex() const
{
	return m_priorityObjectIndex;
}

void MapAIHeroData::setPriorityTileIndex(const int& index)
{
	m_priorityTileIndex = index;
}

const int& MapAIHeroData::getPriorityTileIndex() const
{
	return m_priorityTileIndex;
}

void MapAIHeroData::setPriority(const MapAIPriorityEnum& priority)
{
	m_priority = priority;
}

const MapAIPriorityEnum MapAIHeroData::getPriority() const
{
	return m_priority;
}

void MapAIHeroData::resetPriority()
{
	m_priority = MapAIPriorityEnum::none;
	m_priorityObjectIndex = -1;
	m_priorityTileIndex = -1;
}
