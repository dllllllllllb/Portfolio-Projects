//Author: Maciej Dowbor
//Last Accessed: 30/09/2021

#ifndef COMBATUNITEDITORSETTINGS_H
#define COMBATUNITEDITORSETTINGS_H

#include <string>

namespace CombatUnitEditorSettings
{
	static const int c_borderGap = 20;

	//Unit panel
	static const int c_unitPanelWidth = 456;

	//Icon list
	static const int c_unitIconWidth = 58;
	static const int c_unitIconHeight = 64;
	static const int c_numOfUnitsToDisplay = 7;

	//Buttons
	static const int c_numOfButtons = 3;
	static const int c_buttonBorder = 2;

	static const int c_buttonWidth = 150;
	static const int c_buttonHeight = 50;

	static const int c_textCharSize = 16;
	static const int c_titleCharSize = 20;

	static const std::string c_inputButtonTitleText = "Num of Units";
	static const std::string c_applySettingsButtonText = "Apply";
	static const std::string c_buttonText[c_numOfButtons] { "Apply", "Delete", "Close" };
}

#endif // !COMBATUNITEDITORSETTINGS_H

