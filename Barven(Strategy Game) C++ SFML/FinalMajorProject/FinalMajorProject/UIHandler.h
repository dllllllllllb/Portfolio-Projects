//Author: Maciej Dowbor
//Last Accessed: 30/08/2021

#ifndef UIHANDLER_H
#define UIHANDLER_H

#include "ResourcesBar.h"
#include "SpecialBuildingInteractions.h"
#include "Town.h"
#include "MapUI.h"
#include "HeroPanel.h"
#include "MapObjectsInformationBox.h"

//===========================================================================================
//Description: Handles all UI interaction and drawing
//===========================================================================================
class UIHandler
{
private:
	ResourcesBar m_resourceBar;
	SpecialBuildingInteractions m_specialBuildingInteractions;
	Town m_townInteraction;
	MapUI m_mapUI;
	HeroPanel m_heroPanel;
	MapObjectsInformationBox m_mapObjInfoBox;

public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	UIHandler(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts, ConfirmationWindow& rConfirmationWindow);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~UIHandler();

	//===========================================================================================
	//Description: Initializes contents of this class
	//===========================================================================================
	void initialize();

	//===========================================================================================
	//Description: Updates UI elements
	//===========================================================================================
	void update(sf::Vector2f& mousePosition, const float& deltaTime);

	//===========================================================================================
	//Description: Returns resource bar reference
	//===========================================================================================
	ResourcesBar& getResourceBarReference();

	//===========================================================================================
	//Description: Returns special building interactions reference
	//===========================================================================================
	SpecialBuildingInteractions& getSpecialBuildingsInteractionReference();

	//===========================================================================================
	//Description: Returns town reference
	//===========================================================================================
	Town& getTownReference();

	//===========================================================================================
	//Description: Returns a reference to map ui
	//===========================================================================================
	MapUI& getMapUIReference();

	//===========================================================================================
	//Description: Returns hero panel reference
	//===========================================================================================
	HeroPanel& getHeroPanelReference();

	//===========================================================================================
	//Description: Return reference to map object information box
	//===========================================================================================
	MapObjectsInformationBox& getMapObjectsInformationBoxReference();

	//===========================================================================================
	//Description: Draws contents of this class
	//===========================================================================================
	void draw();
};

#endif // !UIHANDLER_H
