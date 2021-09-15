#include "ResourceMapObject.h"

ResourceMapObject::ResourceMapObject() :
	m_resourceAmount(0),
	m_resourceType(ResourcesEnum::gold)
{
}

ResourceMapObject::~ResourceMapObject()
{
}

void ResourceMapObject::setResourceAmount(const int& resourceAmount)
{
	m_resourceAmount = resourceAmount;
}

const int& ResourceMapObject::getResourceAmount() const
{
	return m_resourceAmount;
}

void ResourceMapObject::setResourceType(const int& resourceType)
{
	m_resourceType = (ResourcesEnum)resourceType;
}

void ResourceMapObject::setResourceType(const ResourcesEnum& resourceType)
{
	m_resourceType = resourceType;
}

const int& ResourceMapObject::getVariable(const MapObjectDataEnum::Resource& variable) const
{
	switch (variable)
	{
	case MapObjectDataEnum::Resource::resourceAmount:
		return m_resourceAmount;
		break;

	default:
		return 0;
		break;
	}
}

void ResourceMapObject::setVariable(const MapObjectDataEnum::Resource& variable, const int& value)
{
	switch (variable)
	{
	case MapObjectDataEnum::Resource::resourceAmount:
		m_resourceAmount = value;
		break;

	default:
		break;
	}
}

const ResourcesEnum& ResourceMapObject::getResourceType() const
{
	return m_resourceType;
}

void ResourceMapObject::setUp(const sf::Vector2f position, const sf::Texture* pTexture)
{
	setTexture(*pTexture, true);

	//Position rounded to int to make sure object is displayed properly
	int x = position.x;
	int y = position.y;

	setPosition(x, y);
	setOrigin(0, getGlobalBounds().height - 32);
}
