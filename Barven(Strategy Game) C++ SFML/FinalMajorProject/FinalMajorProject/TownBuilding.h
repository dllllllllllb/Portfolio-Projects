//Author: Maciej Dowbor
//Last Accessed: 10/09/2021

#ifndef TOWNBUILDING_H
#define TOWNBUILDING_H

#include <iostream>

#include "ConfirmationWindow.h"
#include "GlobalVariables.h"
#include "PopUpTextBox.h"
#include "TownBuildingData.h"
#include "TownBuildingUpgrade.h"
#include "TownBuildingSettings.h"
#include "TownData.h"
#include "FactionBuildingData.h"
#include "Resources.h"
#include "ResourcesBar.h"

//===========================================================================================
//Description: 
//===========================================================================================
class TownBuilding
{
private:

	sf::RenderWindow& m_window;
	Textures* m_pTextures;
	ResourcesBar& m_resourcesBar;
	
	FactionBuildingData* m_pFactionBuildingData;
	TownBuildingData* m_pTownBuildingData;
	Resources* m_pResources;
	TownData* m_pTownData;
	ConfirmationWindow* m_pConfirmationWindow;
	PopUpTextBox* m_pPopUpTextBox;
	int m_selectedBuildingIndex;

	std::vector<std::unique_ptr<TownBuildingUpgrade>> m_upgradeButtons;

public:

	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	TownBuilding(sf::RenderWindow& window, Textures* pTextures, Fonts* pFonts, ConfirmationWindow* pConfirmationWindow, PopUpTextBox* pPopUpTextBox, ResourcesBar& rResourcesBar);
	
	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~TownBuilding();

	//===========================================================================================
	//Description: Sets up buttons
	//===========================================================================================
	void setUpUpgradeButtons();

	//===========================================================================================
	//Description: Updates buttons name and texture
	//===========================================================================================
	void updateUpgradeButtonNameAndTexture(const int& buttonIndex, const std::string& buildingName, const sf::Texture& buildingTexture);

	//===========================================================================================
	//Description: Sets appropriate data pointers
	//===========================================================================================
	void setBuildingDataPointers(TownBuildingData* townBuildingData, FactionBuildingData* factionBuildingData, Resources* resources, TownData* townData);
	
	//===========================================================================================
	//Description: Sets pop up information
	//===========================================================================================
	void setPopUpInformation(const int& buttonIndex);

	//===========================================================================================
	//Description: Updates buildings purchase availability
	//===========================================================================================
	void updateBuildingAvailability();

	//===========================================================================================
	//Description: Checks if the player has enough resources to purchase base buildings
	//===========================================================================================
	void checkIfBaseBuildingCanBePurchased(const int& buttonIndex, const int& upgradeCostIndex);

	//===========================================================================================
	//Description: Checks if the player has enough resources to purchase unit buildings
	//===========================================================================================
	void checkIfUnitBuildingCanBePurchased(const int& unitIndex);

	//===========================================================================================
	//Description: Updates function pointer to call when accept button is pressed in the
	//			   confirmation window
	//===========================================================================================
	void updateConfirmationFunctionPointer();

	//===========================================================================================
	//Description: Charges player for the building purchase
	//===========================================================================================
	void chargePlayerForPurchase();

	//===========================================================================================
	//Description: Charges player for base building purchase
	//===========================================================================================
	void chargeForBasicBuildings(const int& upgradeCostIndex);
#
	//===========================================================================================
	//Description: Charges player for unit building purchase
	//===========================================================================================
	void chargeForUnitBuildings();

	//===========================================================================================
	//Description: Calculates cost index of base buildings
	//===========================================================================================
	const int calculateUpgradeCostIndexForBasicBuildings(const int& buildingIndex);

	//===========================================================================================
	//Description: Repositions updgrade buttons
	//===========================================================================================
	void repositionUpgradeButtons();

	//===========================================================================================
	//Description: Updates logic 
	//===========================================================================================
	bool update(const sf::Vector2f& mousePosition);

	//===========================================================================================
	//Description: Increments town building level
	//===========================================================================================
	void incrementTownBuildingLevel();

	//===========================================================================================
	//Description: Draws contents of this class
	//===========================================================================================
	void draw();

	//===========================================================================================
	//Description: Returns a reference to base faction building data
	//===========================================================================================
	FactionBuildingData& getBaseFactionBuildingData();

	//===========================================================================================
	//Description: Return vector reference of upgrade buttons
	//===========================================================================================
	std::vector<std::unique_ptr<TownBuildingUpgrade>>& getUpgradeButtonsVectorReference();

	//===========================================================================================
	//Description: Sets selected town building index
	//===========================================================================================
	void setSelectedBuildingIndex(const int& buildingIndex);
};


#endif // !TOWNBUILDING_H

