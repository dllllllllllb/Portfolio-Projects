//Author: Maciej Dowbor
//Last Accessed: 29/09/2021

#ifndef UPGRADEHEROSTATSPANEL_H
#define UPGRADEHEROSTATSPANEL_H

#include "GlobalVariables.h"
#include "UpgradeHeroStatsPanelSetiings.h"
#include "IconButton.h"
#include "TextBox.h"
#include "Hero.h"

//===========================================================================================
//Description: Allows player to upgrade heroes stats
//===========================================================================================
class UpgradeHeroStatsPanel
{
private:
	sf::RenderWindow& m_window;
	Textures& m_textures;
	TextBox m_basePanel;
	std::vector<std::unique_ptr<IconButton>> m_heroStatsUpgradeButtons;
	IconButton m_exitButton;

	bool m_isActive;
	Hero* m_pHeroPointer;

public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	UpgradeHeroStatsPanel(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~UpgradeHeroStatsPanel();

	//===========================================================================================
	//Description: Sets up elements of this class
	//===========================================================================================
	void setUpUpgradeHeroStatsPanel();

	//===========================================================================================
	//Description: Sets appropriate hero data
	//===========================================================================================
	void setHeroAndUpdatePanel(Hero& hero);

	//===========================================================================================
	//Description: Toggles is active between true and false
	//===========================================================================================
	void toggleIsActive();

	//===========================================================================================
	//Description: Updates panel text
	//===========================================================================================
	void updatePanelText();

	//===========================================================================================
	//Description: Updates interaction with elements in this class
	//===========================================================================================
	const bool update(const sf::Vector2f& mousePosition);

	//===========================================================================================
	//Description: Draws elements of this class
	//===========================================================================================
	void draw();
};


#endif // !UPGRADEHEROSTATSPANEL_H

