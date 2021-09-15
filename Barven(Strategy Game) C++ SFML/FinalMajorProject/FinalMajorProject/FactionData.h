//Author: Maciej Dowbor
//Last Accessed: 23/06/2021

#ifndef FACTIONDATA_H
#define FACTIONDATA_H

#include "ConstantVariables.h"
#include "UnitData.h"
#include "FactionBuildingData.h"
#include "HeroData.h"

//===========================================================================================
//Description: Data container for all faction specific data
//===========================================================================================
class FactionData
{
private:
	UnitData m_units[c_numOfUnitsPerFaction];
	FactionBuildingData m_buildings;
	HeroData m_heroData;
public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	FactionData();

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~FactionData();

	//===========================================================================================
	//Description: Returns unit data based on index
	//===========================================================================================
	UnitData& getUnitData(const int& index);

	//===========================================================================================
	//Description: Returns buildings data
	//===========================================================================================
	FactionBuildingData& getBuildingsData();

	//===========================================================================================
	//Description: Returns hero data
	//===========================================================================================
	HeroData& getHeroData();
};

#endif // !FACTIONDATA_H