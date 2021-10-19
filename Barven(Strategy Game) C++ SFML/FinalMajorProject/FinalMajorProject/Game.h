//Author: Maciej Dowbor
//Last Accessed: 19/10/2021

#ifndef GAME_H
#define GAME_H

#include "Cursor.h"
#include "MapAI.h" //Stores most header files

//===========================================================================================
//Description: Handles all game logic
//===========================================================================================
class Game
{
private:
	sf::RenderWindow& m_window;
	UIHandler m_UIHandler;
	TurnHandler m_turnHandler;
	PlayerHandler m_playerHandler;
	CombatHandler m_combatHandler;
	GameEnd m_gameEnd;
	MapHandler m_mapHandler;
	ViewManager m_viewManager;
	Cursor m_cursor;
	ConfirmationWindow m_confirmationWindow;
	MapAI m_mapAI;
	sf::Mouse& m_mouse;


public:

	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	Game(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts, Audio& rAudio, DataHandler& rDataHandler, GameSetUpScreen& rGameSetUpScreen, sf::Mouse& rMouse);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~Game();

	//===========================================================================================
	//Description: Initializes members of this class
	//===========================================================================================
	void initialize();

	//===========================================================================================
	//Description: General update function
	//===========================================================================================
	void update(sf::Vector2f& mousePosition, const float& deltaTime);

	//===========================================================================================
	//Description: Updates game logic
	//===========================================================================================
	void updateGame(const float& deltaTile);

	//===========================================================================================
	//Description: Updates UI logic
	//===========================================================================================
	void updateUI(sf::Vector2f& mousePosition, const float& deltaTime);

	//===========================================================================================
	//Description: Updates combat handler logic
	//===========================================================================================
	void updateCombatHandler(sf::Vector2f& mousePosition, const float& deltaTime);

	//===========================================================================================
	//Description: Draws elements of this class
	//===========================================================================================
	void draw();

	//===========================================================================================
	//Description: Draws game specific members of this class
	//===========================================================================================
	void drawGame();
};

#endif // !GAME_H
