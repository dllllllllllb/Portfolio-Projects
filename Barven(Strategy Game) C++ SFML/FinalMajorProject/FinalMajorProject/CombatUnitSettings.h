//Author: Maciej Dowbor
//Last Accessed: 02/08/2021

#ifndef COMBATUNITSETTINGS_H
#define COMBATUNITSSETTINGS_H

namespace CombatUnitSettings
{
	static const int c_numOfAmendableVariables = 6;
	static const int c_maxSingleTileUnitWidth = 100;

	static const int c_charSize = 12;
	static const int c_textBoxWidth = 50;
	static const int c_textBoxHeight = 20;

	static const int c_textBoxOffsetY = 64 - c_textBoxHeight / 2;

	static const int c_smallAttackerTextBoxOffsetX = c_textBoxWidth / 2;
	static const int c_largeAttackerTextBoxOffsetX = c_smallAttackerTextBoxOffsetX - 64;

	static const int c_smallDefenderTextBoxOffsetX = 64 - c_textBoxWidth / 2;
	static const int c_largeDefenderTextBoxOffsetX = c_smallDefenderTextBoxOffsetX + 64;
}

#endif // !COMBATUNITSETTINGS_H
