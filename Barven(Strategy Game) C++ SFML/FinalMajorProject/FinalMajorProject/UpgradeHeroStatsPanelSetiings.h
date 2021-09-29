//Author: Maciej Dowbor
//Last Accessed: 29/09/2021

#ifndef UPGRADEHEROSTATSPANELSETTINGS_H
#define UPGRADEHEROSTATSPANELSETTINGS_H

#include <string>

namespace UpgradeHeroStatsPanelSettings
{
	static const int c_numOfSkills = 4;
	static const int c_skillIconWidth = 80;
	static const int c_skillIconHeight = 90;
	static const int c_skillIconSpaceing = 10;
	static const int c_skillIconYOffset = 40;
	static const int c_basePanelWidth = c_skillIconWidth * c_numOfSkills + c_skillIconSpaceing * (c_numOfSkills + 1) + 200;
	static const int c_basePanelHeight = 180;

	static const int c_titleCharSize = 24;
	static const int c_textCharSize = 16;
	static const std::string c_panelTitle = "Hero Upgrade Panel";
	static const std::string c_panelText = "Click on a stat you want to upgrade. Remaining upgrades: ";
}

#endif // !UPGRADEHEROSTATSPANELSETTINGS_H

