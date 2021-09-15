//Author: Maciej Dowbor
//Last Accessed: 18/08/2021

#ifndef PLAYERSETTINGSTABLESETTINGS_H
#define PLAYERSETTINGSTABLESETTINGS_H

#include <string>

namespace PlayerSettingsTableSettings
{
	static const int c_backgroundBorder = 50;

	static const int c_numOfMaxPlayers = 8;
	static const int c_numOfCollumns = 4;

	static const int c_buttonWidth[2]{ 150, 90 };
	static const int c_buttonHeight = 50;

	static const int c_tableStartHeight = 300;

	static const int c_buttonXOffset[c_numOfCollumns]{ -139, -15, 79, 173 };
	static const int c_buttonOffsetY = 52;

	static const int c_collumnTitleTextSize = 20;
	static const int c_playerNameTextSize = 16;

	static const std::string c_defaultPlayerName = "Player";
	static const std::string c_collumnTitles[c_numOfCollumns]{ "Player Name", "Faction", "Bonus", "AI" };

	static const int c_numOfBonusOptions = 3;
}

#endif // !PLAYERSETTINGSTABLESETTINGS_H
