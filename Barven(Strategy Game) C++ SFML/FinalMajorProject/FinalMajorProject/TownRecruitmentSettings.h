//Author: Maciej Dowbor
//Last Accessed: 01/10/2021

#ifndef TOWNRECRUITMENTSETTINGS_H
#define TOWNRECRUITMENTSETTINGS_H

#include <string>

namespace TownRecruitmentSettings
{
	static const int c_recruitButtonXCentreOffset = -420;
	static const float c_recruitButtonFirstPosY = -301.25;
	static const int c_recruitButtonSpaceing = 100;

	//Pop up window
	//0 == Not enough gold, 1 == Not enough space, 2 == No units to recruit
	static const std::string c_purchaseErrorMessages[3]{ "You don't have enough gold to recruit these units", "You don't have space in your army to recruit these units", "There aren't any available units to recruit" };

	static const int c_popUpPositionXOffset = 140;
	static const int c_popUpPositionYOffset = 305;

	static const float c_purchaseErrorPopUpDuration = 2.5f;

	//Town recruit button
	static const int c_titleCharSize = 24;
	static const int c_recruitButtonWidth = 250;
	static const int c_recruitButtonHeight = 76;

	//Purchase hero button
	static const int c_purchaseHeroButtonXOffset = 140;
	static const int c_purchaseHeroButtonYOffset = 350;
	static const int c_purchaseHeroButtonCharSize = 20;
	static const std::string c_purchaseHeroButtonText = "Purchase new Hero\n      2500g";
	static const int c_purchaseHeroPrice = 2500;
}
#endif // !TOWNRECRUITMENTSETTINGS_H
