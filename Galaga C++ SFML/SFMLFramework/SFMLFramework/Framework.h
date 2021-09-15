//Author: Maciej Dowbor
//Module: MED5149
//Date last accessed: 20/01/2021

#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include "Background.h"
#include "Player.h"
#include "Game.h"
#include "Menu.h"
#include "Tutorial.h"
#include "Textures.h"

//=====================================================================================================	
//Class		: Framework
//-----------------------------------------------------------------------------------------------------
//Purpose	: Application framework
//=====================================================================================================	
class Framework
{
private:

	sf::Clock			m_clock;
	float				m_deltaTime;
	sf::RenderWindow	&m_window;
	Textures			m_textures;
	sf::Music			m_music;

	//High score
	HighScoreTable		*m_pHighScoreTable;
	bool				m_isHighScoreIni;
	void highscore( );
	//=================================================================================================						
	//Purpose	: Call high score functions
	//-------------------------------------------------------------------------------------------------
	//Parameters: -
	//-------------------------------------------------------------------------------------------------
	//Returns	: -
	//=================================================================================================

	//Game
	Game				*m_pGame;
	bool				m_isGameIni;
	void game( );
	//=================================================================================================						
	//Purpose	: Call game functions
	//-------------------------------------------------------------------------------------------------
	//Parameters: -
	//-------------------------------------------------------------------------------------------------
	//Returns	: -
	//=================================================================================================

	//Menu
	Menu				*m_pMenu;
	bool				m_isMenuIni;
	void menu( );
	//=================================================================================================						
	//Purpose	: Call menu fonctions
	//-------------------------------------------------------------------------------------------------
	//Parameters: -
	//-------------------------------------------------------------------------------------------------
	//Returns	: -
	//=================================================================================================

	//Tutorial
	Tutorial			*m_pTutorial;
	bool				m_isTutorialIni;
	void tutorial( );
	//=================================================================================================						
	//Purpose	: Call tutorial functions
	//-------------------------------------------------------------------------------------------------
	//Parameters: -
	//-------------------------------------------------------------------------------------------------
	//Returns	: -
	//=================================================================================================

	//Background
	Background			m_background;


	void checkWindowEvents( );
	//=================================================================================================						
	//Purpose	: Checks for window event
	//-------------------------------------------------------------------------------------------------
	//Parameters: -
	//-------------------------------------------------------------------------------------------------
	//Returns	: -
	//=================================================================================================

	//Performance testing
	float				m_totalTime;
	int					m_numOfFrames;

public:

	Framework( sf::RenderWindow &window );
	//=================================================================================================						
	//Purpose	: Constructor
	//-------------------------------------------------------------------------------------------------
	//Parameters: Reference to render window
	//-------------------------------------------------------------------------------------------------
	//Returns	: -
	//=================================================================================================

	~Framework( );
	//=================================================================================================						
	//Purpose	: Destructor
	//-------------------------------------------------------------------------------------------------
	//Parameters: -
	//-------------------------------------------------------------------------------------------------
	//Returns	: -
	//=================================================================================================

	void run( );
	//=================================================================================================						
	//Purpose	: Run application main loop
	//-------------------------------------------------------------------------------------------------
	//Parameters: -
	//-------------------------------------------------------------------------------------------------
	//Returns	: -
	//=================================================================================================
};

#endif // !FRAMEWORK_H