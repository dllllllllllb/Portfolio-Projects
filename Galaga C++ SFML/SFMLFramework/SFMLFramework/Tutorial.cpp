//Author: Maciej Dowbor
//Module: MED5149
//Date last accessed: 20/01/2021

#include "Tutorial.h"

Tutorial::Tutorial( sf::RenderWindow &window, Textures *textures ) :
	m_window	( window ),
	m_pTextures	( textures )
{
	m_exitButton.setUp( "Menu", m_pTextures->m_menuFont, k_characterSize, m_pTextures->m_button, k_exitButtonPosition.x, k_exitButtonPosition.y );
	m_exitButtonText = m_exitButton.getText( );

	m_tutorialImage.setTexture( m_pTextures->m_tutorial );
	m_tutorialImage.setOrigin( m_tutorialImage.getLocalBounds( ).width * 0.5f, m_tutorialImage.getLocalBounds( ).height * 0.5f );
	m_tutorialImage.setPosition( k_windowSizeX * 0.5f, k_windowSizeY * 0.5f );
}

Tutorial::~Tutorial( )
{
}

void Tutorial::update( )
{
	if( m_exitButton.checkMouseCollision( m_mouse.getPosition( m_window ) ) && m_mouse.isButtonPressed( sf::Mouse::Button::Left ) )
	{
		g_gameState = GameState::menu;
	}
}

void Tutorial::draw( )
{
	m_window.draw( m_tutorialImage );
	m_window.draw( m_exitButton );
	m_window.draw( *m_exitButtonText );
}