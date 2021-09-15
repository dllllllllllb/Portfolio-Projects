//Author: Maciej Dowbor
//Module: MED5148
//Date last accessed: 28/10/2020

#include <conio.h>
#include "DefeatScreen.h"

//Constructor
DefeatScreen::DefeatScreen()
{
	//Sets banner text, alignment, y position and color
	m_defeatBanner[0].set( " ______   _______  _______  _______  _______  _______ ", Alignment::middle, 5, 13 ); 
	m_defeatBanner[1].set( "|      | |       ||       ||       ||   _   ||       |", Alignment::middle, 6, 13 );
	m_defeatBanner[2].set( "|  _    ||    ___||    ___||    ___||  |_|  ||_     _|", Alignment::middle, 7, 13 );
	m_defeatBanner[3].set( "| | |   ||   |___ |   |___ |   |___ |       |  |   |  ", Alignment::middle, 8, 13 );
	m_defeatBanner[4].set( "| |_|   ||    ___||    ___||    ___||       |  |   |  ", Alignment::middle, 9, 13 );
	m_defeatBanner[5].set( "|       ||   |___ |   |    |   |___ |   _   |  |   |  ", Alignment::middle, 10, 13 );
	m_defeatBanner[6].set( "|______| |_______||___|    |_______||__| |__|  |___|  ", Alignment::middle, 11, 13 );

	//Sets score text, alignment, y position and color
	m_scoreText.set( "F I N A L  S C O R E: ", Alignment::middle, 17, 15 );

	//Sets instruction text, alignment, y position and color
	m_instruction.set( "P R E S S  E N T E R  T O  C O N T I N U E", Alignment::middle, 22, 15 );
}

//Destructor
DefeatScreen::~DefeatScreen()
{

}

//Detect input
void DefeatScreen::detectInput()
{
	if( _kbhit() ) //Checks if a key is pressed
	{
		if( _getch() == 13 ) //Gets pressed key value and checks if appropriate key got hit (enter)
		{
			g_gameState = GameState::highscore; //Changes the game state to highscore (see Alignment.h)
		}
	}
}

//Draw defeat screen
void DefeatScreen::drawDefeatScreen( int score )
{
	m_scoreText.deleteText(); //Resets score text
	m_scoreText.updateText( "F I N A L  S C O R E: " + std::to_string( score ) ); //Sets score text
	for( int i = 0; i < m_defeatTextRows; i++ ) //Draws banner line by line
	{
		m_defeatBanner[i].draw();
	}
	m_scoreText.draw(); //Draws score text
	m_instruction.draw(); //Draws instruction text
	
	
}
