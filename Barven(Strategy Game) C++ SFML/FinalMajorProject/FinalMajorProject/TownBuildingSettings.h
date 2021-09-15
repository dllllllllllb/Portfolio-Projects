//Author: Maciej Dowbor
//Last Accessed: 18/08/2021

#ifndef TOWNBUILDINGSETTINGS_H
#define TOWNBUILDINGSETTINGS_H

#include <string>
namespace TownBuildingSettings
{
	static const int c_numOfBuildings = 12;
	static const int c_numOfBasicBuildings = 5;
	static const float c_positionXOffset[c_numOfBuildings]{ -215, 215, -310, 0, 310, -397.5, -132.5, 132.5, 397.5, -310, 0, 310 };
	static const int c_positionYOffset[c_numOfBuildings]{ -290, -290, -100, -100, -100, 90, 90, 90, 90, 280, 280, 280 };

	static const int c_buildingCostGold[8]{ 2500, 5000, 10000, 2500, 5000, 500, 7500, 2000 };
	static const int c_buildingCostWood[8]{ 0, 0, 0, 0, 10, 5, 10, 5 };
	static const int c_buildingCostStone[8]{ 0, 0, 0, 5, 10, 0, 10, 5 };

	static const int c_basicBuildingsMaxLevel[c_numOfBasicBuildings]{ 3, 2, 1, 1, 1 };

	//Town buildings upgrade
	static const int c_townBuildingUpgradeButtonSizeX = 250;
	static const int c_townBuildingUpgradeButtonSizeY = 150;

	//PopUp Width
	static const int c_popUpWidth[2]{ 150, 250 };
}

#endif // !TOWNBUILDINGSETTINGS_H