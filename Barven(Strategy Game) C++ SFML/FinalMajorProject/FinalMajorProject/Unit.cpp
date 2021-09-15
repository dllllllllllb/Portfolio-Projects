#include "Unit.h"
Unit::Unit() :
	m_pBaseUnitData(nullptr),
	m_numOfUnits(0),
	m_health(0),
	m_currentHealth(0),
	m_attack(0),
	m_ammunition(0),
	m_range(0),
	m_defence(0),
	m_speed(0),
	m_isDataSet(false)
{
}

Unit::~Unit()
{
}

void Unit::setNumOfUnits(const int& value)
{
	m_numOfUnits = value;
}

void Unit::incrementNumOfUnits(const int& value)
{
	m_numOfUnits += value;
}

const int& Unit::getNumOfUnits() const
{
	return m_numOfUnits;
}

void Unit::setUnitSpecificData(const UnitBattleDataEnum& dataType, const int& value)
{
	switch (dataType)
	{
	case UnitBattleDataEnum::health:
		m_health = value;
		break;

	case UnitBattleDataEnum::attack:
		m_attack = value;
		break;

	case UnitBattleDataEnum::ammunition:
		m_ammunition = value;
		break;

	case UnitBattleDataEnum::range:
		m_range = value;
		break;

	case UnitBattleDataEnum::defence:
		m_defence = value;
		break;

	case UnitBattleDataEnum::speed:
		m_speed = value;
		break;

	default:
		break;
	}
}

const int& Unit::getUnitSpecificData(const UnitBattleDataEnum& dataType)
{
	switch (dataType)
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
		break;
	}
}

void Unit::initializeUnitSpecificData()
{
	if (m_isDataSet)
	{
		for (int i = 0; i < 6; i++)
		{
			setUnitSpecificData(static_cast<UnitBattleDataEnum>(i), m_pBaseUnitData->getBattleData(static_cast<UnitBattleDataEnum>(i)));
		}
		m_currentHealth = m_health;
	}
}

void Unit::resetCurrentHealth()
{
	m_currentHealth = m_health;
}

void Unit::setCurrentHealth(const int& value)
{
	m_currentHealth = value;
}

const int& Unit::getCurrentHealth() const
{
	return m_currentHealth;
}

void Unit::incrementCurrentHealth(const int& value)
{
	m_currentHealth += value;
}

void Unit::setBaseUnitData(const UnitData* baseUnitData)
{
	m_pBaseUnitData = baseUnitData;
	initializeUnitSpecificData();
}

const UnitData* Unit::getBaseUnitData() const
{
	return m_pBaseUnitData;
}

void Unit::setIsUnitDataSet(const bool state)
{
	m_isDataSet = state;
}

void Unit::toggleIsDataSet()
{
	m_isDataSet = !m_isDataSet;
}

const bool Unit::getIsDataSet() const
{
	return m_isDataSet;
}

void Unit::resetUnitData()
{
	m_pBaseUnitData = nullptr;
	m_numOfUnits = 0;
	m_health = 0;
	m_currentHealth = 0;
	m_attack = 0;
	m_ammunition = 0;
	m_range = 0;
	m_defence = 0;
	m_speed = 0;
	m_isDataSet = false;
}
