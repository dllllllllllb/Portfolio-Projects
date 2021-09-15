//Author: Maciej Dowbor
//Last Accessed: 30/08/2021

#ifndef TOWNDATA_H
#define TOWNDATA_H

#include "ConstantVariables.h"
#include "Unit.h"
#include "TownBuildingData.h"


//===========================================================================================
//Description: Holds town data
//===========================================================================================
class TownData
{
private:
	UnitData* m_unitData[c_numOfUnitsPerFaction];
	TownBuildingData m_townBuildingData;
	std::vector<int> m_availableUnitsToRecruit;
	std::vector<std::shared_ptr<Unit>> m_unitsStationedInsideTheTown;

public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	TownData();

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~TownData();

	//===========================================================================================
	//Description: Sets unit data reference to given unit based on unitIndex
	//===========================================================================================
	void setUnitData(const int& unitIndex, UnitData& unitData);

	//===========================================================================================
	//Description: Returns unit data reference based on unitIndex
	//===========================================================================================
	UnitData* getUnitData(const int& unitIndex) const;

	//===========================================================================================
	//Description: Sets town building data reference
	//===========================================================================================
	void setTownBuildingData( TownBuildingData& townBuildingData);

	//===========================================================================================
	//Description: Return town building data reference
	//===========================================================================================
	TownBuildingData& getTownBuildingData();

	//===========================================================================================
	//Description: Returns vector of available units to recruit
	//===========================================================================================
	std::vector<int>& getAvailableUnitsToRecruit();

	//===========================================================================================
	//Description: Adds a new unit in specified vector position
	//===========================================================================================
	void addUnit(const int& vectorIndex, UnitData* unitToAdd);

	//===========================================================================================
	//Description: Returns a vector of units stationed inside this town
	//===========================================================================================
	std::vector<std::shared_ptr<Unit>>& getVectorOfUnitsStationedInsideTheTown();

	//===========================================================================================
	//Description: Updates available units to recruit based on purchased buildings
	//===========================================================================================
	void addWeeklyUnitsToRecruit();
};

#endif // !TOWNDATA_H

