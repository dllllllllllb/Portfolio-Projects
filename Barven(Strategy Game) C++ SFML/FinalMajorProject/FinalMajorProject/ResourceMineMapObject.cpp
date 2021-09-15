#include "ResourceMineMapObject.h"
ResourceMineMapObject::ResourceMineMapObject() : 
	m_mineType(ResourcesEnum::gold),
	m_ownerIndex(-1)
{
}

ResourceMineMapObject::~ResourceMineMapObject()
{
}

void ResourceMineMapObject::setUp(const sf::Vector2f position, const sf::Texture* pTexture)
{
	//Position rounded to int to make sure its displayed properly
	int x = position.x;
	int y = position.y;

	setPosition(x, y);
	setTexture(*pTexture, true);

	//Origing rounded to int to make sure its displayed properly
	int originX = getGlobalBounds().width - 64;
	setOrigin(originX, 32);
}

void ResourceMineMapObject::setMineTypeEnum(const ResourcesEnum& mineType)
{
	m_mineType = mineType;
}

void ResourceMineMapObject::setMineTypeInt(const int& mineType)
{
	m_mineType = (ResourcesEnum)mineType;
}

const ResourcesEnum& ResourceMineMapObject::getMineType() const
{
	return m_mineType;
}

void ResourceMineMapObject::setOwnerIndex(const int& ownerIndex)
{
	m_ownerIndex = ownerIndex;
}

const int& ResourceMineMapObject::getOwnerIndex() const
{
	return m_ownerIndex;
}

void ResourceMineMapObject::setVariable(const MapObjectDataEnum::ResourceMine& variable, const int& value)
{
	switch (variable)
	{
	case MapObjectDataEnum::ResourceMine::ownerIndex:
		m_ownerIndex = value;
		break;

	default:
		break;
	}
}

const int& ResourceMineMapObject::getVariable(const MapObjectDataEnum::ResourceMine& variable) const
{
	switch (variable)
	{
	case MapObjectDataEnum::ResourceMine::ownerIndex:
		return m_ownerIndex;
		break;

	default:
		return 0;
		break;
	}
}
