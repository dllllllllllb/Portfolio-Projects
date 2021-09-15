//Author: Maciej Dowbor
//Module: MED5149
//Date last accessed: 20/01/2021
#include "Menu.h"

Menu::Menu( sf::RenderWindow &window, Textures *textures ) :
	m_window	( window ),
	m_pTextures	( textures )
{
	setUpButtons( );
}

Menu::~Menu( )
{
}

void Menu::update( )
{
	mouseControl( );
}

void Menu::draw( )
{
	m_window.draw( m_playButton );
	m_window.draw( m_highScoreButton );
	m_window.draw( m_optionsButton );
	m_window.draw( m_quitButton );

	m_window.draw( *m_pPlayText );
	m_window.draw( *m_pHighScoreText );
	m_window.draw( *m_pOptionsText );
	m_window.draw( *m_pQuitText );
}

void Menu::setUpButtons( )
{
	m_playButton		.setUp( "Play", m_pTextures->m_menuFont, k_characterSize, m_pTextures->m_button, k_buttonPositionX, k_buttonPositionY );
	m_highScoreButton	.setUp( "HighScores", m_pTextures->m_menuFont, 28, m_pTextures->m_button, k_buttonPositionX, k_buttonPositionY + 110 );
	m_optionsButton		.setUp( "Tutorial", m_pTextures->m_menuFont, 36, m_pTextures->m_button, k_buttonPositionX, k_buttonPositionY + 220 );
	m_quitButton		.setUp( "Quit", m_pTextures->m_menuFont, k_characterSize, m_pTextures->m_button, k_buttonPositionX, k_buttonPositionY + 330 );

	m_pPlayText			= m_playButton.getText( );
	m_pHighScoreText	= m_highScoreButton.getText( );
	m_pOptionsText		= m_optionsButton.getText( );
	m_pQuitText			= m_quitButton.getText( );
}

void Menu::mouseControl( )
{
	if( m_playButton.checkMouseCollision( m_mouse.getPosition( m_window ) ) && m_mouse.isButtonPressed( sf::Mouse::Button::Left ) )
	{
		g_gameState = GameState::game;
	}

	if( m_highScoreButton.checkMouseCollision( m_mouse.getPosition( m_window ) ) && m_mouse.isButtonPressed( sf::Mouse::Button::Left ) )
	{
		g_gameState = GameState::highScore;
	}

	if( m_optionsButton.checkMouseCollision( m_mouse.getPosition( m_window ) ) && m_mouse.isButtonPressed( sf::Mouse::Button::Left ) )
	{
		g_gameState = GameState::tutorial;
	}

	if( m_quitButton.checkMouseCollision( m_mouse.getPosition( m_window ) ) && m_mouse.isButtonPressed( sf::Mouse::Button::Left ) )
	{
		m_window.close( );
	}
}