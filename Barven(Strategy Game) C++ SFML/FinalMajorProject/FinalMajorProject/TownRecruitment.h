//Author: Maciej Dowbor
//Last Accessed: 30/08/2021

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
	Textures* m_pTextures;
	ConfirmationWindow* m_pConfirmationWindow;
	UnitsPanel& m_unitsPanel;
	ResourcesBar& m_resourcesBar;

	std::vector<std::unique_ptr<UnitRecruitmentButton>> m_recruitButtons;

	PurchaseUnitWindow m_purchaseUnitWindow;

	PopUpTextBox m_purchaseErrorPopUpWindow;

	UnitData* m_unitsStationedInsideTheTown[c_numOfUnitsPerFaction];

	Player* m_pPlayer;
	TownData* m_pTownData;

	int m_selectedUnitIndex;
	float m_purchaseErrorPopUpTimer;

public:

	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	TownRecruitment(sf::RenderWindow& window, Textures* pTextures, Fonts* pFonts, ConfirmationWindow* pConfirmationWindow, UnitsPanel& rTownHeroesUnitsPanel, ResourcesBar& rResourcesBar);

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
	bool update(const sf::Vector2f& mousePosition, const float& deltaTime);

	//===========================================================================================
	//Description: Draws contents of this class
	//===========================================================================================
	void draw();
};
#endif // !TOWNRECRUITMENT_H
