#include "TownMapObject.h"

TownMapObject::TownMapObject() :
	m_ownerIndex(-1),
	m_factionIndex(0)
{
}

TownMapObject::~TownMapObject()
{
}

void TownMapObject::setUp(const sf::Vector2f position, const sf::Texture& pTexture)
{
	//Rounded to int to make sure its rendered properly
	int posX = position.x;
	int posY = position.y;

	setPosition(posX, posY);
	setTexture(pTexture, true);

	//Rounded to int to make sure its rendered properly
	int originX = getGlobalBounds().width * 0.5f;
	int originY = getGlobalBounds().height - 32;
	setOrigin(originX, originY);
}

void TownMapObject::setOwnerIndex(const int& ownerIndex)
{
	m_ownerIndex = ownerIndex;
}

const int& TownMapObject::getOwnerIndex() const
{
	return m_ownerIndex;
}

void TownMapObject::setFactionIndex(const int& factionIndex)
{
	m_factionIndex = factionIndex;
}

const int& TownMapObject::getFactionIndex() const
{
	return m_factionIndex;
}

void TownMapObject::setVariable(const MapObjectDataEnum::Town& variable, const int& value)
{
	switch (variable)
	{
	case MapObjectDataEnum::Town::ownerIndex:
		m_ownerIndex = value;
		break;

	default:
		break;
	}
}

const int TownMapObject::getVariable(const MapObjectDataEnum::Town& variable) const
{
	switch (variable)
	{
	case MapObjectDataEnum::Town::ownerIndex:
		return m_ownerIndex;
		break;

	default:
		return 0;
		break;
	}
}
