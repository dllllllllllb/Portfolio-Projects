//Author: Maciej Dowbor
//Last Accessed: 14/04/2021

#ifndef TOWNBUILDINGDATA_H
#define TOWNBUILDINGDATA_H

#include "TownBuildingEnum.h"

//===========================================================================================
//Description: Stores individual town building data
//===========================================================================================
class TownBuildingData
{
private:
	bool m_canBuildingBePurchased;
	int m_towHall;
	int m_fort;
	int m_marketPlace;
	int m_artefactShop;
	int m_magicGuild;
	int m_unit0;
	int m_unit1;
	int m_unit2;
	int m_unit3;
	int m_unit4;
	int m_unit5;
	int m_unit6;

public:

	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	TownBuildingData();

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~TownBuildingData();
	
	//===========================================================================================
	//Description: Sets building level based on building enum and value passed
	//===========================================================================================
	void setData(const TownBuildingEnum& building, const int& value);

	//===========================================================================================
	//Description: Increments building level by one
	//===========================================================================================
	void incrementData(const TownBuildingEnum& building);

	//===========================================================================================
	//Description: Returns buildings level
	//===========================================================================================
	const int& getData(const TownBuildingEnum& building) const;

	//===========================================================================================
	//Description: Sets bool if a building can be purchased this turn
	//===========================================================================================
	void setCanBuildingBePurchased(const bool state);

	//===========================================================================================
	//Description: Returns a bool if a building can be purchased this turn
	//===========================================================================================
	const bool getCanBuildingBePurchased() const;

};

#endif // !TOWNBUILDINGDATA_H

