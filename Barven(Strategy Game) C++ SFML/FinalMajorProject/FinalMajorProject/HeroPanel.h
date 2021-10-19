//Author: Maciej Dowbor
//Last Accessed: 29/09/2021

#ifndef HEROPANEL_H
#define HEROPANEL_H

#include "UnitsPanel.h"
#include "HeroStatsDisplay.h"
#include "HeroPanelSettings.h"
#include "TextBox.h"
#include "BasicButton.h"
#include "IconButton.h"
#include "Bar.h"
#include "UpgradeHeroStatsPanel.h"


//===========================================================================================
//Description: Shows heros information and allows to interact with heros units
//===========================================================================================
class HeroPanel
{
private:
	sf::RenderWindow& m_window;
	Textures& m_textures;
	Fonts& m_fonts;

	UIElement m_background;
	TextBox m_heroLevel;
	HeroStatsDisplay m_heroStatsDisplay;
	UnitsPanel m_unitsPanel;
	BasicButton m_closeButton;
	IconButton m_addStatsButton;
	UpgradeHeroStatsPanel m_upgradeHeroStatsPanel;

	bool m_isActive;
	bool m_canHeroInteractWithUnits;
	bool m_canHeroUpgradeStats;
	Hero* m_pSelectedHero;

public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	HeroPanel(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts, Audio& rAudio);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~HeroPanel();

	//===========================================================================================
	//Description: Sets up elements of this class to appropriate positions
	//===========================================================================================
	void setUpHeroPanel();

	//===========================================================================================
	//Description: Sets hero data and updates appropriate elements
	//===========================================================================================
	void setHeroData(Hero* hero, const bool canHeroInteractWithUnits);

	//===========================================================================================
	//Description: Sets heros stats
	//===========================================================================================
	void setHeroStats();

	//===========================================================================================
	//Description: Updates unit panel and checks if player closed the panel
	//===========================================================================================
	void update(const sf::Vector2f& mousePosition);

	//===========================================================================================
	//Description: Toggles active state between true and false
	//===========================================================================================
	void toggleIsActive();

	//===========================================================================================
	//Description: Sets active state of this class
	//===========================================================================================
	void setIsActive(const bool state);

	//===========================================================================================
	//Description: Draws contents of this class
	//===========================================================================================
	void draw();

	//===========================================================================================
	//Description: Returns reference to unit panel
	//===========================================================================================
	UnitsPanel& getUnitsPanel();

	//===========================================================================================
	//Description: Returns hero level text box reference
	//===========================================================================================
	TextBox& getHeroLevelTextBox();

	//===========================================================================================
	//Description: Returns reference to hero stats display
	//===========================================================================================
	HeroStatsDisplay& getHeroStatsDisplay();
};


#endif // !HEROPANEL_H

