#ifndef GAMESETUPSCREENSETTINGS_H
#define GAMESETUPSCREENSETTINGS_H

#include <string>

namespace GameSetUpScreenSettings
{
	//Drop Down options
	static const int c_numOfOptionsToDisplay = 5;
	static const int c_optionTextCharSize = 16;
	static const int c_optionWidth = 200;
	static const int c_optionHeight = 40;

	static const std::string c_primaryOptionTitle = "Selected Map";
	static const std::string c_primaryOptionContentText = "select map";
	static const int c_primaryOptionTitleCharSize = 20;

	static const int c_optionPositionYOffset = 200;
	static const int c_optionPositionXOffset = 220;
	static const int c_dropDownOptionsSpaceing = c_optionHeight + 2;

	//Buttons
	static const int c_numOfButtons = 2;
	static const int c_buttonWidth = 300;
	static const int c_buttonHeight = 100;
	static const int c_buttonCharSize = 50;
	static const int c_buttonPosX[2]{ 1700, 220 };
	static const int c_buttonPosY = 960;
	static const std::string c_buttonName[c_numOfButtons]{ "Start Game", "Back" };

	//Refresh button
	static const int c_refreshButtonPositionXOffset = 135;
	static const int c_refreshButtonPositionYOffset = -15;

}

#endif // !GAMESETUPSCREENSETTINGS_H

