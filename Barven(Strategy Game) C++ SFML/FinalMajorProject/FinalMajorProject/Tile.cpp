#include "Tile.h"

Tile::Tile() :
	m_isOccupied(false),
	m_mapObjectType(MapObjectsEnum::none),
	m_objectVectorIndex(0),
	m_tileVectorIndex(0),
	m_isObstacle(false),
	m_isVisited(false),
	m_localGoal(0),
	m_globalGoal(0),
	m_pParentTile(nullptr)
{

}

Tile::~Tile()
{
}

void Tile::setPosition(const float& positionX, const float& positionY)
{
	sf::Sprite::setPosition(positionX, positionY);

}

void Tile::setParentTile(Tile* parentTile)
{
	m_pParentTile = parentTile;
}

void Tile::resetParent()
{
	m_pParentTile = nullptr;
}

Tile* Tile::getParentTile()
{
	return m_pParentTile;
}

void Tile::toggleIsObstacle()
{
	m_isObstacle = !m_isObstacle;
}

void Tile::setIsObstacle(const bool state)
{
	m_isObstacle = state;
}

const bool Tile::getIsObstacle() const
{
	return m_isObstacle;
}

void Tile::setIsVisited(const bool state)
{
	m_isVisited = state;
}

const bool Tile::getIsVisited() const
{
	return m_isVisited;
}

void Tile::setLocalGoal(const float& goal)
{
	m_localGoal = goal;
}

void Tile::setGlobalGoal(const float& goal)
{
	m_globalGoal = goal;
}

const float& Tile::getLocalGoal() const
{
	return m_localGoal;
}

const float& Tile::getGlobalGoal() const
{
	return m_globalGoal;
}

std::vector<Tile*>& Tile::getSurroundingTilesVector()
{
	return m_surroundingTiles;
}

void Tile::setIsOccupied(const bool state)
{
	m_isOccupied = state;
}

const bool Tile::getIsOccupied() const
{
	return m_isOccupied;
}

void Tile::setMapObjectType(const MapObjectsEnum& mapObject)
{
	m_mapObjectType = mapObject;
}

const MapObjectsEnum& Tile::getMapObjectType() const
{
	return m_mapObjectType;
}

void Tile::setMapObjectVectorIndex(const int& objectIndex)
{
	m_objectVectorIndex = objectIndex;
}

const int& Tile::getMapObjectVectorIndex() const
{
	return m_objectVectorIndex;
}

void Tile::setTileVectorIndex(const int& tileVectorIndex)
{
	m_tileVectorIndex = tileVectorIndex;
}

const int& Tile::getTileVectorIndex() const
{
	return m_tileVectorIndex;
}

void Tile::decrementMapObjectVectorIndex()
{
	m_objectVectorIndex--;
}

void Tile::resetTileProperties()
{
	m_isObstacle = false;
	m_isOccupied = false;
	m_mapObjectType = MapObjectsEnum::none;
	m_objectVectorIndex = 0;
}
