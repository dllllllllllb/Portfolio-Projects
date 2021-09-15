//Author: Maciej Dowbor
//Module: MED5148
//Date last accessed: 28/10/2020

#ifndef DEFEATSCREEN_H
#define DEFEATSCREEN_H

#include "Alignment.h"
#include "Text.h"

//=============================================================
// Class Name   : DefeatScreen
//-------------------------------------------------------------
// Purpose      : Defeat state, display defeat screen, show 
//				  players score
//-------------------------------------------------------------
// Used in      : Alignment.h
//				  DefeatScreen.cpp
//				  Game.h
//				  Game.cpp
//=============================================================
class DefeatScreen
{
private:
	Text m_defeatBanner[7]; //Array of text rows to hold and display banner
	int m_defeatTextRows = 7; //Num of lines banner takes up
	Text m_scoreText; //Text to display score
	Text m_instruction; //Text to display instructions


public:
	//========================================================
	// Function Name	: DefeatScreen
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: DefeatScreen constructor
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	DefeatScreen();

	//========================================================
	// Function Name	: ~DefeatScreen()
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: DefeatScreen destructor
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	~DefeatScreen();
	
	//========================================================
	// Function Name	: detectInput()
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: Detects keyboard input
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	void detectInput();

	//========================================================
	// Function Name	: drawDefeatScreen
	//--------------------------------------------------------
	// Parameters		: Players score
	//--------------------------------------------------------
	// Purpose			: Draws defeat screen in the console
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	void drawDefeatScreen( int score );
};

#endif // 
