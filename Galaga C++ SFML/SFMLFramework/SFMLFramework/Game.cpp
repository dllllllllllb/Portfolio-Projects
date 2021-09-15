//Author: Maciej Dowbor
//Module: MED5149
//Date last accessed: 20/01/2021

#include "Game.h"

Game::Game( sf::RenderWindow &window, Textures *textures, HighScoreTable *highScoreTable ) :
	m_window			( window ),
	m_textures			( *textures ),
	m_userInterface		( window, highScoreTable ),
	m_enemyDropHandler	( window, &m_textures ),
	m_player			( window, m_textures.m_player, m_textures.m_bullet, &m_userInterface, &m_enemyDropHandler ),
	m_shop				( window, &m_textures, &m_player ),
	m_enemyHandler		( window, &m_textures, &m_enemyDropHandler, &m_player, &m_waveHandler, &m_userInterface, &m_shop )

{
}

Game::~Game( )
{
}

void Game::initialize( )
{
	m_userInterface		.reset( );
	m_enemyDropHandler	.reset( );
	m_player			.reset( );
	m_enemyHandler		.reset( );
}

void Game::update( const float &deltaTime )
{
	m_player			.update( deltaTime );
	m_enemyHandler		.update( deltaTime );
	m_enemyDropHandler	.update( deltaTime );

	if( m_shop.getAcviteState( ) )
	{
		m_shop.update( );
	}
}

void Game::render( )
{
	m_enemyDropHandler	.drawDrops( );
	m_enemyHandler		.drawEnemies( );
	m_enemyHandler		.drawBullets( );
	m_player			.drawBullets( );
	m_window			.draw( m_player );
	m_userInterface		.drawUI( );

	if( m_shop.getAcviteState( ) )
	{
		m_shop.draw( );
	}
}