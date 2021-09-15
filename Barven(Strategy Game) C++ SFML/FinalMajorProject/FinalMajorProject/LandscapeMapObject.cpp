#include "LandscapeMapObject.h"
LandscapeMapObject::LandscapeMapObject() : 
	m_objectIndex(0),
	m_landscapeType(LandscapeTypeEnum::none)
{
}

LandscapeMapObject::~LandscapeMapObject()
{
}

void LandscapeMapObject::setUp(const sf::Vector2f position, const sf::Texture* pTexture)
{
	setPosition(position);
	setTexture(*pTexture, true);

	//By setting their origin by ints, it makes sure that the rendered sprite is sharp
	int x = getGlobalBounds().width * 0.5f;
	int y = getGlobalBounds().height - 32;
	
	setOrigin(x, y);
}

void LandscapeMapObject::setObjectIndex(const int& objectIndex)
{
	m_objectIndex = objectIndex;
}

const int& LandscapeMapObject::getObjectIndex() const
{
	return m_objectIndex;
}

void LandscapeMapObject::setLandscapeType(const LandscapeTypeEnum& landscapeType)
{
	m_landscapeType = landscapeType;
}

const LandscapeTypeEnum& LandscapeMapObject::getLandscapeType() const
{
	return m_landscapeType;
}
