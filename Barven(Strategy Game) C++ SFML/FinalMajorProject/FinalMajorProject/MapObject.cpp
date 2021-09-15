#include "MapObject.h"

MapObject::MapObject() :
	m_tileIndex(0)
{

}

MapObject::~MapObject()
{
}

void MapObject::setTileIndex(const int& tileIndex)
{
	m_tileIndex = tileIndex;
}

const int& MapObject::getTileIndex() const
{
	return m_tileIndex;
}

MapObject* MapObject::getSelf()
{
	return this;
}

