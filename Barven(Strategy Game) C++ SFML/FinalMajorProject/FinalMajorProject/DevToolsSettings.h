//Author: Maciej Dowbor
//Last Accessed: 17/05/2021

#ifndef DEVTOOLSSETTINGS_H
#define DEVTOOLSSETTINGS_H
#include <string>

namespace DevToolsSettings
{
	static const int c_numOfButtons = 7;
	static const float c_positionX[c_numOfButtons]{ 1720, 225, 225, 225, 225, 225, 225 };
	static const float c_positionY[c_numOfButtons]{ 1000, 100, 250, 400, 550, 700, 850 };
	static const int c_buttonWidth = 350;
	static const int c_buttonHeight = 100;

	static const std::string c_buttonName[c_numOfButtons]{ "Back", "UI Tool", "Path Finding", "Unit Creator", "Town Tool", "Map Creator", "Combat Tool" };
	static const int c_buttonCharSize = 50;
}
#endif // !DEVTOOLSSETTINGS_H
