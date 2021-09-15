#include "MapQuadrantData.h"

MapQuadrantData::MapQuadrantData()
{
}

MapQuadrantData::~MapQuadrantData()
{
}

void MapQuadrantData::addTileIndex(const int& tileIndex)
{
	m_tileIndexes.push_back(tileIndex);
}

std::vector<int>& MapQuadrantData::getTileIndexesVector()
{
	return m_tileIndexes;
}

void MapQuadrantData::addMapObjectPointer(MapObject* mapObject)
{
	m_mapObjectPointers.push_back(mapObject);
}

std::vector<MapObject*>& MapQuadrantData::getMapObjectPointersVector()
{
	return m_mapObjectPointers;
}
