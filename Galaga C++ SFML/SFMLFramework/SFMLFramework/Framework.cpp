//Author: Maciej Dowbor
//Module: MED5149
//Date last accessed: 20/01/2021

#include "Framework.h"

//Global / extern vars in "Settings.h" need to be defined outside of "Settings.h"
GameState g_gameState = GameState::menu; //Sets initial game state
bool g_isWindowSelected = true;

Framework::Framework( sf::RenderWindow &window ) :
	m_window		( window ),
	m_deltaTime		( 0.0f ),
	m_background	( window, &m_textures ),
	m_isHighScoreIni( false ),
	m_isGameIni		( false ),
	m_isMenuIni		( false ),
	m_isTutorialIni	( false ),
	m_totalTime		( 0 ),
	m_numOfFrames	( 0 )

{
	m_window.setFramerateLimit( k_frameRateLimit );
	m_window.setVerticalSyncEnabled( true );

	//Create main classes on the heap
	m_pHighScoreTable = new HighScoreTable( m_window, &m_textures );
	m_pGame = new Game( window, &m_textures, m_pHighScoreTable );
	m_pMenu = new Menu( window, &m_textures );
	m_pTutorial = new Tutorial( window, &m_textures );

	//Loads and plays background music
	m_music.openFromFile( "Assets/Audio/Backgroundmusic.wav" );
	m_music.setLoop( true );
	m_music.setVolume( k_musicVolume );
	m_music.play( );
}

Framework::~Framework( )
{
	safeDelete( m_pGame );
	safeDelete( m_pMenu );
	safeDelete( m_pHighScoreTable );
	safeDelete( m_pTutorial );
}

void Framework::run( )
{
	while( m_window.isOpen( ) )
	{
		checkWindowEvents( );
		m_window.clear( ); //Clears the window
		m_deltaTime = m_clock.restart( ).asSeconds( ); //Time passed since last frame

		//Testing framerate
		m_totalTime += m_deltaTime;
		m_numOfFrames++;
		//std::cout << "Frame Rate: " << m_deltaTime << "\n" << "Average Frame Rate: " << m_totalTime / m_numOfFrames << "\n";

		//Background
		m_background.update( m_deltaTime );
		m_background.draw( );


		//Calls functions based on the current game state
		switch( g_gameState )
		{
			case GameState::menu:
			menu( );
			break;

			case GameState::game:
			game( );
			break;

			case GameState::tutorial:
			tutorial( );
			break;

			case GameState::highScore:
			highscore( );
			break;

			default:
			break;
		}

		m_window.display( );
	}
}

void Framework::menu( )
{
	//Every game state resets bools to make sure that any initialize functions are called when player moves from one game state to another
	if( !m_isMenuIni )
	{
		m_isMenuIni			= true;
		m_isGameIni			= false;
		m_isTutorialIni		= false;
		m_isHighScoreIni	= false;
	}
	m_pMenu->update( );
	m_pMenu->draw( );
}

void Framework::game( )
{
	if( !m_isGameIni )
	{
		m_pGame->initialize( );
		m_isMenuIni			= false;
		m_isGameIni			= true;
		m_isTutorialIni		= false;
		m_isHighScoreIni	= false;
	}
	m_pGame->update( m_deltaTime );
	m_pGame->render( );
}

void Framework::tutorial( )
{
	if( !m_isTutorialIni )
	{
		m_isMenuIni			= false;
		m_isGameIni			= false;
		m_isTutorialIni		= true;
		m_isHighScoreIni	= false;
	}
	m_pTutorial->update( );
	m_pTutorial->draw( );
}

void Framework::highscore( )
{
	if( !m_isHighScoreIni )
	{
		m_isMenuIni			= false;
		m_isGameIni			= false;
		m_isTutorialIni		= false;
		m_isHighScoreIni	= true;
		m_pHighScoreTable->readData( );
	}
	m_pHighScoreTable->update( );
	m_pHighScoreTable->draw( );
}

void Framework::checkWindowEvents( )
{
	sf::Event event;
	while( m_window.pollEvent( event ) )
	{
		if( event.type == sf::Event::Closed ) //Checks if player requested to close the window
		{
			m_window.close( );
		}

		//Checks if player clicked off the game window, used in player controls to make sure that the player only moves when the window is selected
		if( event.type == sf::Event::GainedFocus )
		{
			g_isWindowSelected = true;
		}

		if( event.type == sf::Event::LostFocus )
		{
			g_isWindowSelected = false;
		}
	}
}