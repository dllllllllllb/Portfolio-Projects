#include "ResourceMineData.h"

ResourceMineData::ResourceMineData() :
	m_resourceGainPerDay(0),
	m_mineResourceType(ResourcesEnum::gold)
{
}

ResourceMineData::~ResourceMineData()
{
}

void ResourceMineData::setMineMapTexture(const std::string& mineTextureFilePath)
{
	m_mineMapTexture.loadFromFile(mineTextureFilePath);
}

const sf::Texture* ResourceMineData::getMineMapTexture() const
{
	return &m_mineMapTexture;
}

void ResourceMineData::setResourceGainPerDay(const int& resourceGainPerWeek)
{
	m_resourceGainPerDay = resourceGainPerWeek;
}

const int& ResourceMineData::getResourceGainPerDay() const
{
	return m_resourceGainPerDay;
}

void ResourceMineData::setMineType(const ResourcesEnum& mineType)
{
	m_mineResourceType = mineType;
}

const ResourcesEnum& ResourceMineData::getMineType() const
{
	return m_mineResourceType;
}
