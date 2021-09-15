//Author: Maciej Dowbor
//Module: MED5148
//Date last accessed: 28/10/2020

#ifndef HIGHSCORETABLE_H
#define HIGHSCORETABLE_H

#include "HighScore.h"
#include "Text.h"

#include <conio.h>
#include <fstream>
#include <iostream>
#include <sstream>

//=============================================================
// Class Name   : HighScoreTable
//-------------------------------------------------------------
// Purpose      : Read/write data into a text file
//				  Draw the high score table on the screen
//				  Organize high score table in descending order		  
//-------------------------------------------------------------
// Used in      : Game.cpp
//		          Game.h
//				  HighScoreTable.cpp
//=============================================================
class HighScoreTable
{
private:
	std::ifstream m_highScoreFileIn; //Used to read data from a txt file
	std::ofstream m_highScoreFileOut; //Used to write data to a txt file

	HighScore m_highScores[10]; //Stores players name and score
	int m_highScoreLength = 10; //Number of high scores to display
	int m_tablePositionY = 16; //Y position from which the high score table will be drawn
	int m_nameInputPosY = 28; //Y position where the player will be asked to write their name
	int m_score; //Stores players score

	Text m_banner[7]; //High Score banner
	Text m_textToDraw; //Text that will be used to draw high scores

	std::string m_playerName; //Stores players name
	const std::string m_HighScoreFile; //Name of the file where high scores will be stored
	
	//========================================================
	// Function Name	: sortTable()
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: Sorts the table in descending order
	//					  based on players score
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	void sortTable();

	//========================================================
	// Function Name	: writeData()
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: Writes stored data into a text 
	//					  document
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	void writeData();

public:
	//========================================================
	// Function Name	: HighScoreTable()
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: High Score Table constructor
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	HighScoreTable();

	//========================================================
	// Function Name	: ~HighScoreTable()
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: High Score Table destructor
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	~HighScoreTable();

	//========================================================
	// Function Name	: readData()
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: Reads data from a txt file and 
	//					  stores it in m_highScores
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	void readData();

	//========================================================
	// Function Name	: initializeBanner()
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: Sets up the banner text
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	void initializeBanner();

	//========================================================
	// Function Name	: drawTable()
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: Draws high score table on the screen
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	void drawTable();

	//========================================================
	// Function Name	: drawBanner()
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: Draws banner on the screen
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	void drawBanner();

	//========================================================
	// Function Name	: enterName()
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: Draws text that tells player to 
	//					  enter their name, waits for the
	//					  player to type their name and
	//					  changes the game state to menu
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	void enterName();

	//========================================================
	// Function Name	: getScore()
	//--------------------------------------------------------
	// Parameters		: Players score
	//--------------------------------------------------------
	// Purpose			: Returns players score
	//--------------------------------------------------------
	// Returns			: Players score
	//========================================================
	void getScore( int score );

	//========================================================
	// Function Name	: detectInput()
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: Detects player input
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	void detectInput();

	//========================================================
	// Function Name	: initialize()
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: Initialize high score table
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	void initialize();
};

#endif // !HIGHSCORETABLE_H

