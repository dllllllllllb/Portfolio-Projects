//Author: Maciej Dowbor
//Last Accessed: 02/09/2021

#ifndef PLAYERSETTINGSTABLE_H
#define PLAYERSETTINGSTABLE_H

#include <iostream>

#include "TextInputBox.h"
#include "IconButton.h"
#include "TextBox.h"
#include "PlayerSettingsTableSettings.h"
#include "GlobalVariables.h"
#include "DataHandler.h"
#include "TickBox.h"

//===========================================================================================
//Description: Table for setting players/AI names, factions and bonuses 
//===========================================================================================
class PlayerSettingsTable
{
private:
	sf::RenderWindow& m_window;
	Textures* m_pTextures;
	UIElement m_background;
	DataHandler& m_dataHandler;
	std::vector<std::unique_ptr<TextBox>> m_pCollumnTitles;
	std::vector<std::unique_ptr<TextInputBox>> m_pPlayerNameInput;
	std::vector<std::unique_ptr<IconButton>> m_pFactionSelectionButton;
	std::vector<std::unique_ptr<IconButton>> m_pBonusSelectionButton;
	std::vector<std::unique_ptr<TickBox>> m_pIsAITickBox;

	int m_numOfAvailablePlayers;
	std::vector<int> m_selectedFactionID;
	std::vector<int> m_selectedBonusID;

public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	PlayerSettingsTable(sf::RenderWindow& rWindow, Textures* pTextures, Fonts* pFonts, DataHandler& rDataHandler);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~PlayerSettingsTable();

	//===========================================================================================
	//Description: Sets up the settings table
	//===========================================================================================
	void initialize();

	//===========================================================================================
	//Description: Updates buttons and input buttons
	//===========================================================================================
	void update(const sf::Vector2f& mousePosition);

	//===========================================================================================
	//Description: Checks if a button was pressed
	//===========================================================================================
	void updateButtonClick(const sf::Vector2f& mousePosition);

	//===========================================================================================
	//Description: Updates input buttons
	//===========================================================================================
	void updateInputButtons();

	//===========================================================================================
	//Description: Resets input button focus
	//===========================================================================================
	void resetInputButtonFocus();

	//===========================================================================================
	//Description: Sets number of available players based on the map, activates / deactivates
	//			   player option based on this number
	//===========================================================================================
	void setNumberOfAvailablePlayers(const int& numOfAvailablePlayers);

	//===========================================================================================
	//Description: Changes colour of the row to white / black if the row is active / inactive for
	//			   player feedback
	//===========================================================================================
	void updateInactiveRowsPlayerFeedback();

	//===========================================================================================
	//Description: Returns players name
	//===========================================================================================
	const std::string& getPlayerName(const int& playerIndex);

	//===========================================================================================
	//Description: Returns index of chosen faction by the player
	//===========================================================================================
	const int& getPlayersChosenFaction(const int& playerIndex);

	//===========================================================================================
	//Description: Returns a bool that determines if player is AI
	//===========================================================================================
	const bool getIsPlayerAI(const int& playerIndex);

	//===========================================================================================
	//Description: Draws contents of this class
	//===========================================================================================
	void draw();
};

#endif // !PLAYERSETTINGSTABLE_H

