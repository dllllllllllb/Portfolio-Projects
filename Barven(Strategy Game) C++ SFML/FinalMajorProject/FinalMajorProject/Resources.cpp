#include "Resources.h"
Resources::Resources() :
	m_gold(10000),
	m_wood(100),
	m_stone(100)
{
}

Resources::~Resources()
{
}

void Resources::incrementResourceValue(const ResourcesEnum& resourceType, const int& value)
{
	switch (resourceType)
	{
	case ResourcesEnum::gold:
		m_gold += value;
		break;

	case ResourcesEnum::wood:
		m_wood += value;
		break;

	case ResourcesEnum::stone:
		m_stone += value;
		break;

	default:
		break;
	}
}

const int& Resources::getResource(const ResourcesEnum& resourceType) const
{
	switch (resourceType)
	{
	case ResourcesEnum::gold:
		return m_gold;
		break;

	case ResourcesEnum::wood:
		return m_wood;
		break;

	case ResourcesEnum::stone:
		return m_stone;
		break;

	default:
		return 0;
		break;
	}
}

