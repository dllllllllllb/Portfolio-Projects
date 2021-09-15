//Author: Maciej Dowbor
//Last Accessed: 18/08/2021

#ifndef COMBATHANDLERSETTINGS_H
#define COMBATHANDLERSETTINGS_H

#include <string>

namespace CombatHandlerSettings
{
	static const int c_tileSize = 64;
	static const int c_numOfHorizontalTiles = 15;
	static const int c_numOfVerticalTiles = 9;
	static const int c_combatAreaBorder = 220;
	static const int c_maxNumOfUnits = 7;

	static const int c_minimumNumOfUnitsPerCombatUnits = 3;

	static const int c_selectedUnitMaxAlpha = 255;
	static const int c_selectedUnitMinAlpha = 100;
	static const float c_alphaChangeRate = 1.2f;

	static const int c_startUnitPositions[c_maxNumOfUnits][c_maxNumOfUnits]{ {4},
																			 {2, 6},
																			 {1, 4, 7},
																			 {1, 3, 5, 7},
																			 {0, 2, 4, 6, 8},
																			 {0, 1, 3, 5, 7, 8},
																			 {0, 1, 2, 4, 6, 7, 8}
	};

	static const float c_bonusPercentagePerPointDifference = 2.5f;

	//Buttons
	static const int c_numOfButtons = 3;

	//Blood splash animation
	static const int c_textureSize = 128;
	static const int c_numOfFrames = 30;

	//Unit information card
	static const int c_unitInformationCardYOffset = 10;

	//Logs console
	static const int c_consoleWidth = 300;
	static const int c_consoleTextSize = 14;
	static const int c_consoleTitleSize = 24;
	static const std::string c_consoleTitle = "Combat Logs";

}
#endif // !COMBATHANDLERSETTINGS_H
