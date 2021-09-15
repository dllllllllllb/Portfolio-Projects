//Author: Maciej Dowbor
//Last Accessed: 17/05/2021

#ifndef UITOOLSETTINGS_H
#define UITOOLSETTINGS_H

#include <string>

namespace UIToolSettings
{
	static const int c_numOfButtons = 5;
	static const int c_positionX[c_numOfButtons]{ 225, 450, 675, 900, 960 };
	static const int c_positionY[c_numOfButtons]{ 100, 100, 100, 100, 540 };
	static const int c_buttonWidth = 200;
	static const int c_buttonHeight = 60;

	static const int c_titleCharSize = 24;
	static const int c_contentCharSize = 18;

	static const std::string c_buttonTitle[c_numOfButtons]{ "Width", "Height", "Position X", "PositionY", "" };
	static const std::string c_buttonContentText = "Type Here";
}
#endif // !UITOOLSETTINGS_H
