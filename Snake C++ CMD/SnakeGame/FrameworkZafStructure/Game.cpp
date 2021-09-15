//Author: Maciej Dowbor
//Module: MED5148
//Date last accessed: 28/10/2020

#include "Alignment.h"
#include "Game.h"

#include <stdlib.h>
#include <windows.h>

//Global / extern vars in "Settings.h" need to be defined outside of "Settings.h"
GameState g_gameState = GameState::menu; //Sets game state to menu
int difficulty = diffNormal; //Sets game difficulty to normal


void Game::run() //Main loop
{
	//Hide cursor (not my code) ref: https://stackoverflow.com/questions/18028808/remove-blinking-underscore-on-console-cmd-prompt
	HANDLE out = GetStdHandle( STD_OUTPUT_HANDLE );
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo( out, &cursorInfo );
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo( out, &cursorInfo );

	while( true ) //Loops infinitely until application is closed
	{

		switch( g_gameState ) //Determines which functions to call based on game state
		{
		case GameState::menu: //Menu
			if( !menuInitialized ) //Checks if the game state is initialized to make sure its only called once
			{
				system( "cls" ); //Cleans the console as it will be redrawing the whole scene
				o_menu.initialize(); //Initializes the menu
				highScoreInitialized = false;
				menuInitialized = true;
			}
			o_menu.detectInput(); //Checks for user input
			break;

		case GameState::game: //Game

			if( !gameInitialized ) //Checks if the game state is initialized to make sure its only called once
			{ 
				system( "cls" ); //Cleans the console as it will be redrawing the whole scene
				initializeGame(); //Initializes the game
				menuInitialized = false;
				gameInitialized = true;
			}
			play(); //Calls all functions necessary to play the game
			break;

		case GameState::defeat:
			if( !defeatInitialized ) //Checks if the game state is initialized to make sure its only called once
			{
				system( "cls" ); //Cleans the console as it will be redrawing the whole scene
				o_defeatScreen.drawDefeatScreen( m_score ); //Draws defeat screen
				gameInitialized = false;
				defeatInitialized = true;
			}
			o_defeatScreen.detectInput(); //Checks for user input
			break;

		case GameState::highscore:
			if (!highScoreInitialized) //Checks if the game state is initialized to make sure its only called once
			{
				system( "cls" ); //Cleans the console as it will be redrawing the whole scene
				o_highScoreTable.initialize(); //Initializes high score table
				o_highScoreTable.getScore( m_score ); //Stores the score in high score table
				if (defeatInitialized) //Checks if defeat is initialized to make sure that player can only enter their score after they are defeated in game
				{
					o_highScoreTable.enterName(); //Allows the player to enter their name
				}
				defeatInitialized = false;
				menuInitialized = false;
				highScoreInitialized = true;
			}
			o_highScoreTable.detectInput(); //Checks for user input
		}

	}
}

void Game::play() //Calls all functions necessary to play the game
{
	unrender(); //Unrenders everything necessary
	update(); //Executes game logic
	render(); //Renders everything necessary
	Sleep( difficulty ); //Makes the game update every "difficulty" time in ms
}


void Game::initializeGame() //Initializes the game
{
	spawnFruit(); //Spawns the fruit
	o_snake.resetVars(); //Reset snake values
	m_score = 0; //Resets the score

	//Text
	m_gameModeText.set( "Game Mode: " + o_menu.getGameModeString(), Alignment::middle, 1 ,15); //Sets game mode text
	m_scoreText.set( "Score: " + std::to_string(m_score), Alignment::left, 3, 15 ); //Sets score text
	m_snakeLengthText.set( "Snake Length: " + std::to_string(o_snake.getSnakeLength()), Alignment::right, 3, 15 ); //Sets snake length text
	m_difficultyText.set( "Difficulty: " + o_menu.getDifficultyString(), Alignment::middle, 3, 15 ); //Sets difficulty text

	//Draws all text on the screen
	m_gameModeText.draw();
	m_scoreText.draw();
	m_snakeLengthText.draw();
	m_difficultyText.draw();

	//Draws objects on the screen
	o_snake.draw();
	o_border.drawBorder();

	FlushConsoleInputBuffer( GetStdHandle( STD_INPUT_HANDLE ) );

	
}

void Game::update() //Game logic
{
	o_snake.checkForInput(); //Checks for player input
	o_snake.movement(); //Moves the snake
	collisions(); //Checks for collisions
	
}

void Game::collisions() //Checks for collisions
{
	o_snake.borderCollision(); //Checks for border collisions

	o_snake.snakeCollision(); //Checks for snake - Snake collisions

	if( o_snake.fruitCollision( m_fruitPosition ) ) //Checks if snakes head collided with the fruit
	{
		spawnFruit(); //Spawns fruit

		//Text
		//Update score
		m_scoreText.deleteLastChar( std::to_string( m_score ).length() ); //Deletes current score text
		m_score += m_scoreIncrement; //Increases players score
		m_scoreText.updateText( m_score ); //Updates score text
		
		//Update length
		m_snakeLengthText.deleteLastChar( std::to_string( o_snake.getSnakeLength() - 1 ).length() ); //Deletes current snakes length text
		m_snakeLengthText.updateText( o_snake.getSnakeLength() ); //Updates snakes length text
	}
}

void Game::render() //Draws everything needed on the screen
{
	o_snake.draw(); //Draws snake
	m_scoreText.draw(); //Draws score text
	m_snakeLengthText.draw(); //Draws snakes length text
}

void Game::unrender() //Unrenders everything necessary
{
	o_snake.erase();
}

void Game::getSnakePositions() //Saves snake positions in fruit object
{
	for( int i = 0; i < o_snake.getSnakeLength(); i++ ) //Loops based on snakes length
	{
		o_fruit.saveSnakePos( i, o_snake.getPosition( i ) ); //Saves position of each snake segment in the fruit object to use to check for collisions
	}
}

void Game::spawnFruit() //Spawns fruit
{
	getSnakePositions(); //Saves snake positions in fruit object
	o_fruit.getSnakeLength( o_snake.getSnakeLength() ); //Saves snakes length in fruit object
	o_fruit.spawnFruit(); //Spawns fruit
	m_fruitPosition = o_fruit.getVector2(); //Sets fruit position to a local variable to check for fruit collisions
}

