//Author: Maciej Dowbor
//Last Accessed: 01/10/2021

#ifndef TOWNRECRUITMENT_H
#define TOWNRECRUITMENT_H

#include "TownBuildingData.h"
#include "ConfirmationWindow.h"
#include "UnitRecruitmentButton.h"
#include "PurchaseUnitWindow.h"
#include "TownRecruitmentSettings.h"
#include "Player.h"
#include "UnitsPanel.h"
#include "ResourcesBar.h"
#include "TownData.h"
#include "PopUpTextBox.h"

//===========================================================================================
//Description: Logic for recruiting units in town
//===========================================================================================
class TownRecruitment
{
private:

	sf::RenderWindow& m_window;
	Textures& m_textures;
	ConfirmationWindow& m_confirmationWindow;
	UnitsPanel& m_unitsPanel;
	ResourcesBar& m_resourcesBar;

	std::vector<std::unique_ptr<UnitRecruitmentButton>> m_recruitButtons;

	PurchaseUnitWindow m_purchaseUnitWindow;

	PopUpTextBox m_purchaseErrorPopUpWindow;

	Button m_purchaseHeroButton;

	UnitData* m_unitsStationedInsideTheTown[c_numOfUnitsPerFaction];

	Player* m_pPlayer;
	TownData* m_pTownData;

	std::function<void(Hero*)> m_functionToCallAfterPurchasingHero;

	int m_selectedUnitIndex;
	float m_purchaseErrorPopUpTimer;
	bool m_isHeroInTown;

public:

	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	TownRecruitment(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts, Audio& rAudio, ConfirmationWindow& rConfirmationWindow, UnitsPanel& rTownHeroesUnitsPanel, ResourcesBar& rResourcesBar);

	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	~TownRecruitment();

	//===========================================================================================
	//Description: Sets unit data pointer to given unit index
	//===========================================================================================
	void setUnitDataPointer(const int& index, UnitData* unitData);

	//===========================================================================================
	//Description: Repositions town recruitment
	//===========================================================================================
	void reposition();

	//===========================================================================================
	//Description: Initializes unit buttons
	//===========================================================================================
	void initialize();

	//===========================================================================================
	//Description: Updates recruitment buttons names and icons
	//===========================================================================================
	void updateRecruitmentButtonsNameAndIcons();

	//===========================================================================================
	//Description: Updates function pointer to call when accept button is pressed in the
	//			   confirmation window
	//===========================================================================================
	void updateConfirmationFunctionPointer();

	//===========================================================================================
	//Description: Sets purchase window details to the first unit
	//===========================================================================================
	void setDefaultPurchaseWindowContent();

	//===========================================================================================
	//Description: Sets appropriate player data
	//===========================================================================================
	void setPlayerSpecificData(Player* player, TownData* pTownData, const int& factionIndex);

	//===========================================================================================
	//Description: Checks if player meets conditions to purchase units, charges the player and
	//			   adds units to the visiting hero
	//===========================================================================================
	void purchaseUnits();

	//===========================================================================================
	//Description: Creates a new hero
	//===========================================================================================
	void purchaseNewHero();

	//===========================================================================================
	//Description: Refreshes contents of the purchase window
	//===========================================================================================
	void refreshPurchaseWindow();

	//===========================================================================================
	//Description: Updates error pop up
	//===========================================================================================
	void updatePurchaseErrorPopUpWindow(const float& deltaTime);

	//===========================================================================================
	//Description: Sets appropriate error message and activated error pop up to be displayed
	//===========================================================================================
	void activateUnitPurchaseErrorPopUp(const int& messageIndex);

	//===========================================================================================
	//Description: Updates class logic
	//===========================================================================================
	void update(const sf::Vector2f& mousePosition, const float& deltaTime);

	//===========================================================================================
	//Description: Sets a bool that determines if hero is in town
	//===========================================================================================
	void setIsHeroInTown(const bool state);

	//===========================================================================================
	//Description: Sets a function to call after purchasing a hero
	//===========================================================================================
	void setFunctionToCallAfterPurchasingAHero(std::function<void(Hero*)> function);

	//===========================================================================================
	//Description: Draws contents of this class
	//===========================================================================================
	void draw();
};
#endif // !TOWNRECRUITMENT_H
