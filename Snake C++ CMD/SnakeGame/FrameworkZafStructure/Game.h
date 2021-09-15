//Author: Maciej Dowbor
//Module: MED5148
//Date last accessed: 28/10/2020

#ifndef GAME_H
#define GAME_H

#include "Snake.h"
#include "Fruit.h"
#include "Border.h"
#include "Vector2.h"
#include "Text.h"
#include "Settings.h"

#include "DefeatScreen.h"
#include "HighScoreTable.h"
#include "Menu.h"

//=============================================================
// Class Name   : Game
//-------------------------------------------------------------
// Purpose      : Application framework
//-------------------------------------------------------------
// Used in      : Source.cpp
//=============================================================
class Game 
{
private:

	//Menu
	Menu o_menu;

	//Defeat Screen
	DefeatScreen o_defeatScreen;

	//High Score Table
	HighScoreTable o_highScoreTable; 

	//Objects
	Snake o_snake { 1, 1, 10 };
	Fruit o_fruit; 
	Border o_border; 

	//Vectors
	Vector2 m_fruitPosition; //Holds fruit position as Vector2 (See Vector2.h/cpp)

	//Text
	Text m_scoreText; //Score text
	Text m_snakeLengthText; //Snake length text
	Text m_gameModeText; //Game mode text
	Text m_difficultyText; //Difficulty text

	//Variables
	int m_score = 0; //Score 

	//Used to make sure that every game state is initialized only once
	bool gameInitialized = false;
	bool menuInitialized = false;
	bool defeatInitialized = false;
	bool highScoreInitialized = false;

	//Functions

	//========================================================
    // Function Name	: play()
    //--------------------------------------------------------
    // Parameters		: -
    //--------------------------------------------------------
    // Purpose			: Call all functions necessary to play
	//					  the game
    //--------------------------------------------------------
    // Returns			: -
    //========================================================
	void play();

	//========================================================
    // Function Name	: initializeGame()
    //--------------------------------------------------------
    // Parameters		: -
    //--------------------------------------------------------
    // Purpose			: Initializes everything needed for
	//					  the game to start
    //--------------------------------------------------------
    // Returns			: -
    //========================================================
	void initializeGame();

	//========================================================
    // Function Name	: update()
    //--------------------------------------------------------
    // Parameters		: -
    //--------------------------------------------------------
    // Purpose			: Execute game logic
    //--------------------------------------------------------
    // Returns			: -
    //========================================================
	void update();

	//========================================================
    // Function Name	: collisions()
    //--------------------------------------------------------
    // Parameters		: -
    //--------------------------------------------------------
    // Purpose			: Check for collisions
    //--------------------------------------------------------
    // Returns			: -
    //========================================================
	void collisions();

	//========================================================
    // Function Name	: render()
    //--------------------------------------------------------
    // Parameters		: -
    //--------------------------------------------------------
    // Purpose			: Draw everything thats needed
	//					  on screen
    //--------------------------------------------------------
    // Returns			: -
    //========================================================
	void render();

	//========================================================
    // Function Name	: unrender()
    //--------------------------------------------------------
    // Parameters		: -
    //--------------------------------------------------------
    // Purpose			: Unrenders everything necessary
    //--------------------------------------------------------
    // Returns			: -
    //========================================================
	void unrender();

	//========================================================
	// Function Name	: getSnakePositions()
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: Save snake positions in fruit object
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	void getSnakePositions();

	//========================================================
	// Function Name	: spawnFruit()
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: Spawns fruit
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	void spawnFruit();

public:
	//========================================================
	// Function Name	: run()
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: Runs the application
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	void run();

};
#endif