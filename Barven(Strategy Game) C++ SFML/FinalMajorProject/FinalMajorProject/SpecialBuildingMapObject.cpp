#include "SpecialBuildingMapObject.h"

SpecialBuildingMapObject::SpecialBuildingMapObject() :
	m_isVisited(false),
	m_buildingType(SpecialBuildingEnum::arena)
{
}

SpecialBuildingMapObject::~SpecialBuildingMapObject()
{
}

void SpecialBuildingMapObject::setUp(const sf::Vector2f position, const sf::Texture* pTexture)
{
	//Position rounded to int to make sure its displayed properly
	int x = position.x;
	int y = position.y;

	setPosition(x, y);
	setTexture(*pTexture, true);

	//Origing rounded to int to make sure its displayed properly
	int originX = getGlobalBounds().width * 0.5f - 16;
	setOrigin(originX, getGlobalBounds().height - 32);
}

void SpecialBuildingMapObject::setIsVisited(const bool state)
{
	m_isVisited = state;
}

const bool SpecialBuildingMapObject::getIsVisited() const
{
	return m_isVisited;
}

void SpecialBuildingMapObject::setBuildingType(const SpecialBuildingEnum& buildingType)
{
	m_buildingType = buildingType;
}

const SpecialBuildingEnum& SpecialBuildingMapObject::getBuildingType() const
{
	return m_buildingType;
}
