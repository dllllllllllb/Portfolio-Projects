//Author: Maciej Dowbor
//Last Accessed: 17/05/2021

#ifndef UNITCREATIONSETTINGS_H
#define UNITCREATIONSETTINGS_H

#include <string>

namespace UnitCreator
{
	static const int c_numOfButtons = 16;
	static const int c_buttonPosX[c_numOfButtons]{ 1160, 660, 660, 660, 1260, 1260, 1260, 660, 660, 1260, 660, 1260, 960, 960, 760, 960 };
	static const int c_buttonPosY[c_numOfButtons]{ 200, 300, 400, 500, 400, 500, 600, 600, 700, 700, 800, 800, 100, 800, 200, 900 };
	static const int c_buttonWidth = 200;
	static const int c_widerButtonWidth = 350;
	static const int c_buttonHeight = 60;

	static const int c_buttonContentCharSize = 14;
	static const std::string c_buttonContent = "Type Here";
	static const int c_buttonNameCharSize = 24;
	static const std::string c_buttonName[c_numOfButtons] = { "Texture File", "Unit ID", "Health", "Attack", "Is Ranged", "Ammunition", "Range", "Defence", "Is Flying", "Speed", "Weekly Growth", "Unit Cost", "Unit Name", "Icon File", "Faction", "Map Sprite" };
}
#endif // !UNITCREATIONSETTINGS_H
