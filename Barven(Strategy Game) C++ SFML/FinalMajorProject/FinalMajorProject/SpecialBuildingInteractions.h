//Author: Maciej Dowbor
//Last Accessed: 14/07/2021

#ifndef SPECIALBUILDINGINTERACTIONS_H
#define SPECIALBUILDINGINTERACTIONS_H

#include <iostream>

#include "Player.h"
#include "SpecialBuildingEnum.h"
#include "TextBox.h"
#include "IconButton.h"
#include "TextBox.h"
#include "ConfirmationWindow.h"
#include "SpecialBuildingInteractionsSettings.h"
#include "HeroStatsEnum.h"

//===========================================================================================
//Description: Class that handles hero interactions with special map buildings
//===========================================================================================
class SpecialBuildingInteractions
{
private:
	sf::RenderWindow& m_window;
	Textures& m_textures;
	Fonts& m_fonts;
	Audio& m_audio;
	ConfirmationWindow& m_confirmationWindow;
	Player* m_pPlayer;

	std::vector<std::unique_ptr<IconButton>> m_iconButtons;
	TextBox m_textBox;

	bool m_isActive;
	int m_activeIconButtons;
	int m_interactionIndex;

public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	SpecialBuildingInteractions(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts, Audio& rAudio, ConfirmationWindow& rConfirmationWindow);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~SpecialBuildingInteractions();

	//===========================================================================================
	//Description: Initialize neccessary components
	//===========================================================================================
	void initialize();

	//===========================================================================================
	//Description: Determines what functions to call
	//===========================================================================================
	void specialInteraction(const SpecialBuildingEnum& buildingType, Player* pPlayer);

	//===========================================================================================
	//Description: Sets up necessary elements for arena interaction
	//===========================================================================================
	void arenaInteractionSetUp();

	//===========================================================================================
	//Description: Logic called when a hero interacts with the arena
	//===========================================================================================
	void arenaInteraction();

	//===========================================================================================
	//Description: Updates appropriate elements based on what special building hero is interacting with
	//===========================================================================================
	void update(const sf::Vector2f& mousePosition);

	//===========================================================================================
	//Description: Toggles m_isActive between true and false state
	//===========================================================================================
	void toggleIsActive();

	//===========================================================================================
	//Description: Draws appropriate elements based on what special building hero is interacting with
	//===========================================================================================
	void draw();
};

#endif // !SPECIALBUILDINGINTERACTIONS_H