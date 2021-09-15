//Author: Maciej Dowbor
//Module: MED5149
//Date last accessed: 20/01/2021

#include "Background.h"

Background::Background( sf::RenderWindow &window, Textures *textures ) :
	m_window	( window ),
	m_pTextures	( textures )
{
	m_pStars = new BackgroundStar[k_numOfBackgroundStars];

	//Loops through all stars, sets their texture and randomizes their size
	for( int i = 0; i < k_numOfBackgroundStars; i++ )
	{
		m_pStars[i].setUp( m_pTextures->m_star );
		float value = ( rand( ) % 5 + 10 ) * 0.1f;
		m_pStars[i].setScale( value, value );
	}
}

Background::~Background( )
{
	delete[] m_pStars;
	m_pStars = nullptr;
}

void Background::update( const float &deltaTime )
{
	//Updates all stars
	for( int i = 0; i < k_numOfBackgroundStars; i++ )
	{
		m_pStars[i].update( deltaTime );
	}
}

void Background::draw( )
{
	//Draws all stars
	for( int i = 0; i < k_numOfBackgroundStars; i++ )
	{
		m_window.draw( m_pStars[i] );
	}
}