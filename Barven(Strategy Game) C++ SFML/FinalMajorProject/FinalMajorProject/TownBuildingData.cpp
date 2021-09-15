#include "TownBuildingData.h"
TownBuildingData::TownBuildingData() :
	m_canBuildingBePurchased(true),
	m_towHall(0),
	m_fort(0),
	m_marketPlace(0),
	m_artefactShop(0),
	m_magicGuild(0),
	m_unit0(1),
	m_unit1(0),
	m_unit2(0),
	m_unit3(0),
	m_unit4(0),
	m_unit5(0),
	m_unit6(0)

{
}

TownBuildingData::~TownBuildingData()
{
}

void TownBuildingData::setData(const TownBuildingEnum& building, const int& value)
{
	switch (building)
	{
	case TownBuildingEnum::townHall:
		m_towHall = value;
		break;

	case TownBuildingEnum::fort:
		m_fort = value;
		break;

	case TownBuildingEnum::marketPlace:
		m_marketPlace = value;
		break;

	case TownBuildingEnum::artefactShop:
		m_artefactShop = value;
		break;

	case TownBuildingEnum::magicGuild:
		m_magicGuild = value;
		break;

	case TownBuildingEnum::unit0:
		m_unit0 = value;
		break;

	case TownBuildingEnum::unit1:
		m_unit1 = value;
		break;

	case TownBuildingEnum::unit2:
		m_unit2 = value;
		break;

	case TownBuildingEnum::unit3:
		m_unit3 = value;
		break;

	case TownBuildingEnum::unit4:
		m_unit4 = value;
		break;

	case TownBuildingEnum::unit5:
		m_unit5 = value;
		break;

	case TownBuildingEnum::unit6:
		m_unit6 = value;
		break;

	default:
		break;
	}
}

void TownBuildingData::incrementData(const TownBuildingEnum& building)
{
	switch (building)
	{
	case TownBuildingEnum::townHall:
		m_towHall++;
		break;

	case TownBuildingEnum::fort:
		m_fort++;
		break;

	case TownBuildingEnum::marketPlace:
		m_marketPlace++;
		break;

	case TownBuildingEnum::artefactShop:
		m_artefactShop++;
		break;

	case TownBuildingEnum::magicGuild:
		m_magicGuild++;
		break;

	case TownBuildingEnum::unit0:
		m_unit0++;
		break;

	case TownBuildingEnum::unit1:
		m_unit1++;
		break;

	case TownBuildingEnum::unit2:
		m_unit2++;
		break;

	case TownBuildingEnum::unit3:
		m_unit3++;
		break;

	case TownBuildingEnum::unit4:
		m_unit4++;
		break;

	case TownBuildingEnum::unit5:
		m_unit5++;
		break;

	case TownBuildingEnum::unit6:
		m_unit6++;
		break;

	default:
		break;
	}
}

const int& TownBuildingData::getData(const TownBuildingEnum& building) const
{
	switch (building)
	{
	case TownBuildingEnum::townHall:
		return m_towHall;
		break;

	case TownBuildingEnum::fort:
		return m_fort;
		break;

	case TownBuildingEnum::marketPlace:
		return m_marketPlace;
		break;

	case TownBuildingEnum::artefactShop:
		return m_artefactShop;
		break;

	case TownBuildingEnum::magicGuild:
		return m_magicGuild;
		break;

	case TownBuildingEnum::unit0:
		return m_unit0;
		break;

	case TownBuildingEnum::unit1:
		return m_unit1;
		break;

	case TownBuildingEnum::unit2:
		return m_unit2;
		break;

	case TownBuildingEnum::unit3:
		return m_unit3;
		break;

	case TownBuildingEnum::unit4:
		return m_unit4;
		break;

	case TownBuildingEnum::unit5:
		return m_unit5;
		break;

	case TownBuildingEnum::unit6:
		return m_unit6;
		break;

	default:
		return 0;
		break;
	}
}

void TownBuildingData::setCanBuildingBePurchased(const bool state)
{
	m_canBuildingBePurchased = state;
}

const bool TownBuildingData::getCanBuildingBePurchased() const
{
	return m_canBuildingBePurchased;
}
