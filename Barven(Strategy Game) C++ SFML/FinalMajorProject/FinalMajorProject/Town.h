//Author: Maciej Dowbor
//Last Accessed: 01/10/2021

#ifndef TOWN_H
#define TOWN_H

#include <iostream> //For debuging

#include "ConfirmationWindow.h"
#include "DataHandler.h"
#include "PopUpTextBox.h"
#include "TownBuilding.h"
#include "TownEnum.h"
#include "TownRecruitment.h"
#include "TownSettings.h"
#include "TownData.h"
#include "Player.h"
#include "FactionBuildingData.h"
#include "UnitsPanel.h"
#include "TownTrading.h"

//===========================================================================================
//Description: Town interaction logic. Uses "TownSettings.h" to set up buttons
//===========================================================================================
class Town
{
private:
	sf::RenderWindow& m_window;
	UIElement m_background;
	UIElement m_sectionBackground;
	TownEnum m_townEnum;
	Textures* m_pTextures;

	ConfirmationWindow& m_confirmationWindow;
	PopUpTextBox m_popUpTextBox;

	//Navigation
	std::vector<std::unique_ptr<Button>> m_buttons;

	//Build
	TownBuilding m_townBuilding;

	//Recruitment
	TownRecruitment m_recruitment;

	//Unit Panels
	UnitsPanel m_townsUnitsPannel;
	UnitsPanel m_visitingHeroUnitsPannel;

	//Town trading
	TownTrading m_townTrading;

	bool m_isTownActive;
	bool m_isHeroVisiting;
	bool m_isLastSelectedUnitInHerosPanel;
	Hero* m_pVisitingHero;

public:

	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	Town(sf::RenderWindow& window, Textures* pTextures, Fonts* pFonts, ConfirmationWindow& rConfirmationWindow, ResourcesBar& rResourcesBar);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~Town();

	//===========================================================================================
	//Description: Sets backgrounds, buttons, loads and stores data and calls initializers of
	//			   other elements in this class
	//===========================================================================================
	void initialize();

	//===========================================================================================
	//Description: Sets up buttons
	//===========================================================================================
	void setUpButtons();

	//===========================================================================================
	//Description: Sets appropriate town data and updates every data based elements
	//===========================================================================================
	void setTownData(const int& factionIndex, TownData& townData, FactionBuildingData& factionBuildingData, Player& player, const bool isHeroVisiting);

	//===========================================================================================
	//Description: Sets visiting hero data
	//===========================================================================================
	void setVisitingHeroData(Hero* hero);

	//===========================================================================================
	//Description: Repositiones town elements
	//===========================================================================================
	void reposition();

	//===========================================================================================
	//Description: Checks for button presses and switches town state
	//===========================================================================================
	void update(const sf::Vector2f& mousePosition, const float& deltaTime);

	//===========================================================================================
	//Description: Updates unit panels and interaction between them
	//===========================================================================================
	void updateUnitPanels(const sf::Vector2f& mousePosition);

	//===========================================================================================
	//Description: Checks if player wants to transfer units
	//===========================================================================================
	void transferUnitsBetweenTownAndHero();

	//===========================================================================================
	//Description: Toggles between true and false state that defines if town is active
	//===========================================================================================
	void toggleIsTownActive();

	//===========================================================================================
	//Description: Sets a bool that defines if town is active
	//===========================================================================================
	void setIsTownActive(const bool state);

	//===========================================================================================
	//Description: Draws contents of this class
	//===========================================================================================
	void draw();

	//===========================================================================================
	//Description: Changes current UI Layer enum to "confirmation"
	//===========================================================================================
	void changeUILayerToConfirmation();

	//===========================================================================================
	//Description: Changes current UI Layer enum to "town"
	//===========================================================================================
	void changeUILayerToTown();

	//===========================================================================================
	//Description: Returns a reference to base faction building data
	//===========================================================================================
	FactionBuildingData& getBaseFactionBuildingData();

	//===========================================================================================
	//Description: Returns reference to town building data
	//===========================================================================================
	TownBuilding& getTownBuildingReference();
};

#endif // !TOWN_H