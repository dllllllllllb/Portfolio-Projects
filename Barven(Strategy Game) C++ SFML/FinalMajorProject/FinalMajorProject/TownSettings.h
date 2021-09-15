//Author: Maciej Dowbor
//Last Accessed: 17/05/2021

#ifndef TOWNSETTINGS_H
#define TOWNDSETTINGS_H

#include <string>

namespace TownSettings
{
	static const int c_numOfButtons = 6;
	static const int c_buttonWidth = 300;
	static const int c_buttonHeight = 100;
	static const std::string c_buttonText[c_numOfButtons]{ "Build", "Recruit", "Trade", "Spells", "Artefacts", "Exit" };
	static const int c_charSize = 64;
	static const float c_screenBorderOffset = 42.5;
	static const int c_gapBetweenButtons = 25;
	static const int c_unitPanelPosition = 50;
}

#endif // !TOWNSETTINGS_H
