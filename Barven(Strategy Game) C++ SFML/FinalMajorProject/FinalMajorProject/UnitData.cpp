#include "UnitData.h"
UnitData::UnitData() :
	m_spriteFilePath(""),
	m_index(0),
	m_health(0),
	m_attack(0),
	m_minDamage(0),
	m_maxDamage(0),
	m_isRanged(0),
	m_ammunition(0),
	m_range(0),
	m_defence(0),
	m_isFlying(0),
	m_speed(0),
	m_growthPerWeek(0),
	m_cost(0),
	m_unitName(""),
	m_iconFilePath(""),
	m_faction(""),
	m_specialProperty(UnitSpecialPropertyEnum::none),
	m_AIValue(0)
{
}

UnitData::~UnitData()
{
}

const UnitSpecialPropertyEnum& UnitData::getSpecialProperty() const
{
	return m_specialProperty;
}

const sf::Texture& UnitData::getUnitSprite() const
{
	return m_unitSprite;
}

const sf::Texture& UnitData::getUnitIcon() const
{
	return m_unitIcon;
}

const sf::Texture& UnitData::getUnitMapSprite() const
{
	return m_unitMapSprite;
}

const UnitData* UnitData::getUnitData() const
{
	return this;
}

void UnitData::loadTextures()
{
	m_unitSprite.loadFromFile(m_spriteFilePath);
	m_unitIcon.loadFromFile(m_iconFilePath);
	m_unitMapSprite.loadFromFile(m_unitMapSpriteFilePath);
}

void UnitData::loadJSONData(const json& JSONData)
{
	for (int i = 0; i < c_unitDataEnumLength; i++)
	{
		setData(static_cast<UnitDataEnum>(i), JSONData[c_unitDataEnumStrings[i]]);
	}
}

template<typename variableType>
void UnitData::setData(const UnitDataEnum unitData, const variableType& value)
{
	switch (unitData)
	{
	case UnitDataEnum::sprite:
		m_spriteFilePath = value;
		break;

	case UnitDataEnum::index:
		m_index = value;
		break;

	case UnitDataEnum::health:
		m_health = value;
		break;

	case UnitDataEnum::attack:
		m_attack = value;
		break;

	case UnitDataEnum::minDamage:
		m_minDamage = value;
		break;

	case UnitDataEnum::maxDamage:
		m_maxDamage = value;
		break;

	case UnitDataEnum::isRanged:
		m_isRanged = value;
		break;

	case UnitDataEnum::ammunition:
		m_ammunition = value;
		break;

	case UnitDataEnum::range:
		m_range = value;
		break;

	case UnitDataEnum::defence:
		m_defence = value;
		break;

	case UnitDataEnum::isFlying:
		m_isFlying = value;
		break;

	case UnitDataEnum::speed:
		m_speed = value;
		break;

	case UnitDataEnum::growthPerWeek:
		m_growthPerWeek = value;
		break;

	case UnitDataEnum::cost:
		m_cost = value;
		break;

	case UnitDataEnum::unitName:
		m_unitName = value;
		break;

	case UnitDataEnum::unitIcon:
		m_iconFilePath = value;
		break;

	case UnitDataEnum::faction:
		m_faction = value;
		break;

	case UnitDataEnum::mapSprite:
		m_unitMapSpriteFilePath = value;
		break;

	case UnitDataEnum::AIValue:
		m_AIValue = value;
		break;

	default:
		break;
	}
}

const int& UnitData::getIntData(const UnitDataEnum unitData) const
{
	switch (unitData)
	{
	case UnitDataEnum::index:
		return m_index;
		break;

	case UnitDataEnum::health:
		return m_health;
		break;

	case UnitDataEnum::attack:
		return m_attack;
		break;

	case UnitDataEnum::minDamage:
		return m_minDamage;
		break;

	case UnitDataEnum::maxDamage:
		return m_maxDamage;
		break;

	case UnitDataEnum::isRanged:
		return m_isRanged;
		break;

	case UnitDataEnum::ammunition:
		return m_ammunition;
		break;

	case UnitDataEnum::range:
		return m_range;
		break;

	case UnitDataEnum::defence:
		return m_defence;
		break;

	case UnitDataEnum::isFlying:
		return m_isFlying;
		break;

	case UnitDataEnum::speed:
		return m_speed;
		break;

	case UnitDataEnum::growthPerWeek:
		return m_growthPerWeek;
		break;

	case UnitDataEnum::cost:
		return m_cost;
		break;

	case UnitDataEnum::AIValue:
		return m_AIValue;
		break;

	default:
		return 0;
		break;
	}
}

const int& UnitData::getBattleData(const UnitBattleDataEnum& unitBattleData) const
{
	switch (unitBattleData)
	{
	case UnitBattleDataEnum::health:
		return m_health;
		break;

	case UnitBattleDataEnum::attack:
		return m_attack;
		break;

	case UnitBattleDataEnum::ammunition:
		return m_ammunition;
		break;

	case UnitBattleDataEnum::range:
		return m_range;
		break;

	case UnitBattleDataEnum::defence:
		return m_defence;
		break;

	case UnitBattleDataEnum::speed:
		return m_speed;
		break;

	default:
		return 0;
		break;
	}
}

const std::string& UnitData::getStringData(const UnitDataEnum unitData) const
{
	switch (unitData)
	{
	case UnitDataEnum::sprite:
		return m_spriteFilePath;
		break;

	case UnitDataEnum::unitName:
		return m_unitName;
		break;

	case UnitDataEnum::unitIcon:
		return m_iconFilePath;
		break;

	case UnitDataEnum::faction:
		return m_faction;
		break;

	case UnitDataEnum::mapSprite:
		return m_unitMapSpriteFilePath;
		break;

	default:
		return "";
		break;
	}
}