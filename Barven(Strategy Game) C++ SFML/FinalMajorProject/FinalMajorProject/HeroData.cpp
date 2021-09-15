#include "HeroData.h"
HeroData::HeroData() :
	m_baseAttack(1),
	m_baseDefence(1),
	m_baseMagicPower(1),
	m_baseWisdom(1)
{
}

HeroData::~HeroData()
{
}

void HeroData::setHeroBaseStat(const HeroStatsEnum& heroStat, const int& statValue)
{
	switch (heroStat)
	{
	case HeroStatsEnum::attack:
		m_baseAttack = statValue;
		break;

	case HeroStatsEnum::defence:
		m_baseDefence = statValue;
		break;

	case HeroStatsEnum::magicPower:
		m_baseMagicPower = statValue;
		break;

	case HeroStatsEnum::wisdom:
		m_baseWisdom = statValue;
		break;

	default:
		break;
	}
}

const int& HeroData::getHeroStat(const HeroStatsEnum& heroStat) const
{
	switch (heroStat)
	{
	case HeroStatsEnum::attack:
		return m_baseAttack;
		break;

	case HeroStatsEnum::defence:
		return m_baseDefence;
		break;

	case HeroStatsEnum::magicPower:
		return m_baseMagicPower;
		break;

	case HeroStatsEnum::wisdom:
		return m_baseWisdom;
		break;

	default:
		break;
	}
}

void HeroData::loadHeroTexture()
{
	m_heroMapTexture.loadFromFile("Assets/Sprites/Heroes/CastleHeroMapSprite.png");
}

sf::Texture& HeroData::getHeroTexture()
{
	return m_heroMapTexture;
}