#include "UnitMapObject.h"

UnitMapObject::UnitMapObject() :
	m_numOfUnits(0),
	m_factionIndex(0),
	m_unitIndex(0)
{
}

UnitMapObject::~UnitMapObject()
{
}

void UnitMapObject::setUp(const sf::Vector2f& position, const sf::Texture& texture)
{
	//Rounded to int to make sure its rendered properly
	int posX = position.x;
	int posY = position.y;

	setPosition(posX, posY);
	setTexture(texture, true);

	//Rounded to int to make sure its rendered properly
	int originY = getGlobalBounds().height -32;
	setOrigin(0, originY);
}

void UnitMapObject::setNumberOfUnits(const int& numOfUnits)
{
	m_numOfUnits = numOfUnits;
}

const int& UnitMapObject::getNumberOfUnits() const
{
	return m_numOfUnits;
}

void UnitMapObject::setFactionIndex(const int& factionIndex)
{
	m_factionIndex = factionIndex;
}

const int& UnitMapObject::getFactionIndex() const
{
	return m_factionIndex;
}

void UnitMapObject::setUnitIndex(const int& unitIndex)
{
	m_unitIndex = unitIndex;
}

const int& UnitMapObject::getUnitIndex() const
{
	return m_unitIndex;
}

void UnitMapObject::setVariable(const MapObjectDataEnum::Units& variable, const int& value)
{
	switch (variable)
	{
	case MapObjectDataEnum::Units::unitIndex:
		m_unitIndex = value;
		break;

	case MapObjectDataEnum::Units::numOfUnits:
		m_numOfUnits = value;
		break;

	default:
		break;
	}
}

const int& UnitMapObject::getVariable(const MapObjectDataEnum::Units& variable) const
{
	switch (variable)
	{
	case MapObjectDataEnum::Units::unitIndex:
		return m_unitIndex;
		break;

	case MapObjectDataEnum::Units::numOfUnits:
		return m_numOfUnits;
		break;

	default:
		return 0;
		break;
	}
}
