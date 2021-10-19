//Author: Maciej Dowbor
//Last Accessed: 10/09/2021

#ifndef GAMESETUPSCREEN_H
#define GAMESETUPSCREEN_H

#include <functional>
#include "PlayerSettingsTable.h"
#include "DropDownList.h"
#include "GameSetUpScreenSettings.h"
#include "DataHandler.h"
#include "IconButton.h"

//===========================================================================================
//Description: Fully customizable drop down list
//===========================================================================================
class GameSetUpScreen
{
private:
	sf::RenderWindow& m_window;
	DataHandler& m_dataHandler;
	Textures& m_textures;
	PlayerSettingsTable m_playerSettingsTable;
	DropDownList m_mapSelectionDropDown;
	Button m_startGameButton;
	Button m_backButton;
	IconButton m_refreshDropDownListButton;

	std::function<void()> m_pLoadMapFunction;
	
public:

	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	GameSetUpScreen(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts, Audio& rAudio, DataHandler& rDataHandler);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~GameSetUpScreen();

	//===========================================================================================
	//Description: Initializes elements of the class and loads map names into the drop down list 
	//===========================================================================================
	void initialize();

	//===========================================================================================
	//Description: Sets up start, back and refresh buttons
	//===========================================================================================
	void setUpButtons();

	//===========================================================================================
	//Description: Calls update function of the elements of this class
	//===========================================================================================
	void update(const sf::Vector2f& mousePosition);

	//===========================================================================================
	//Description: Checks for mouse collisions
	//===========================================================================================
	void updateButtons(const sf::Vector2f& mousePosition);

	//===========================================================================================
	//Description: Returns players chosen faction
	//===========================================================================================
	const int& getPlayerChosenFaction(const int& playerIndex);

	//===========================================================================================
	//Description: Returns index of selected map
	//===========================================================================================
	const int& getChosenMapIndex();

	//===========================================================================================
	//Description: Returns a bool that determines if player is AI
	//===========================================================================================
	const bool getIfPlayerIsAI(const int& playerIndex);

	//===========================================================================================
	//Description: Returns player name
	//===========================================================================================
	const std::string& getPlayerName(const int& playerIndex);

	//===========================================================================================
	//Description: Sets function pointer to load map function in map handler class
	//===========================================================================================
	void setConfirmationFunctionPointer(std::function<void()> function);

	//===========================================================================================
	//Description: Updates max number of players in the player settings table
	//===========================================================================================
	void updateAvailablePlayers();

	//===========================================================================================
	//Description: Draws contents of this class
	//===========================================================================================
	void draw();

};

#endif // !GAMESETUPSCREEN_H

