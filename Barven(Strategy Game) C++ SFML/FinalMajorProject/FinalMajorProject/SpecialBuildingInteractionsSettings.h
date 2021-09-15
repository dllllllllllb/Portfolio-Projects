//Author: Maciej Dowbor
//Last Accessed: 14/07/2021

#ifndef SPECIALBUILDINGINTERACTIONSSETTINGS_H
#define SPECIALBUILDINGINTERACTIONSSETTINGS_H

#include <string>

namespace SpecialBuildingInteractionsSettings
{
	static const int c_numOfInteractions = 2;
	static const int c_numOfIconButtons = 2;
	static const int c_heroPrimaryStatIconWidth = 80;
	static const int c_heroPrimaryStatIconHeight = 90;
	static const int c_iconButtonsSpaceing = 30;

	static const int c_titleCharSize = 16;

	//In SpecialBuildingEnum order
	static const int c_numberOfIconButtonsRequired[c_numOfInteractions]{ 2, 0 };

	//Arena
	static const int c_arenaStatIncrease = 2;
	static const std::string c_arenaText = "Chose +2 to Attack or Defence";
}

#endif // !SPECIALBUILDINGINTERACTIONSSETTINGS_H

