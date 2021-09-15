//Author: Maciej Dowbor
//Module: MED5149
//Date last accessed: 20/01/2021

#include "EnemyDropHandler.h"

EnemyDropHandler::EnemyDropHandler( sf::RenderWindow &window, Textures *textures ) :
	m_window			( window ),
	m_pTextures			( textures ),
	m_numOfActiveDrops	( 0 ),
	m_areDropsActive	( false )
{
	initializeDrops( );
}

EnemyDropHandler::~EnemyDropHandler( )
{
}

void EnemyDropHandler::initializeDrops( )
{
	//Change sprites later
	for( int i = 0; i < k_numOfDrops; i++ )
	{
		//Credits
		m_creditDrops[i]	.load( m_pTextures->m_creditDrop );
		//drop type is set to money as default

		//Health
		m_healthDrops[i]	.load( m_pTextures->m_healthDrop );
		m_healthDrops[i]	.setDropType( EnemyDropType::health );

		//Bombs
		m_bombDrops[i]		.load( m_pTextures->m_bombDrop );
		m_bombDrops[i]		.setDropType( EnemyDropType::bomb );

		//Shield
		m_shieldDrops[i]	.load( m_pTextures->m_shieldDrop );
		m_shieldDrops[i]	.setDropType( EnemyDropType::shield );
	}
}

void EnemyDropHandler::update( const float &deltaTime )
{
	//Check if any drops are active
	if( m_numOfActiveDrops > 0 )
	{
		m_areDropsActive = true;
	}
	else
	{
		m_areDropsActive = false;
	}

	//Update drops
	for( int i = 0; i < k_numOfDrops; i++ )
	{
		//Credit drop
		if( m_creditDrops[i].getActiveState( ) ) //Checks if there are any active drops
		{
			m_creditDrops[i].move( 0.f, k_dropsSpeed * deltaTime ); //Drop moves down the screen

			if( m_creditDrops[i].getPosition( ).y > k_windowSizeY ) //Checks if the drop is outside of the screen
			{
				m_creditDrops[i].toggleState( ); //Deactivated the drop
				decreaseNumOfActiveDrops( ); //Decrements number of active drops
			}
		}

		//Health drops
		if( m_healthDrops[i].getActiveState( ) )
		{
			m_healthDrops[i].move( 0.f, k_dropsSpeed * deltaTime );

			if( m_healthDrops[i].getPosition( ).y > k_windowSizeY )
			{
				m_healthDrops[i].toggleState( );
				decreaseNumOfActiveDrops( );
			}
		}

		//Bomb drops
		if( m_bombDrops[i].getActiveState( ) )
		{
			m_bombDrops[i].move( 0.f, k_dropsSpeed * deltaTime );

			if( m_bombDrops[i].getPosition( ).y > k_windowSizeY )
			{
				m_bombDrops[i].toggleState( );
				decreaseNumOfActiveDrops( );
			}
		}

		//Shield drops
		if( m_shieldDrops[i].getActiveState( ) )
		{
			m_shieldDrops[i].move( 0.f, k_dropsSpeed * deltaTime );

			if( m_shieldDrops[i].getPosition( ).y > k_windowSizeY )
			{
				m_shieldDrops[i].toggleState( );
				decreaseNumOfActiveDrops( );
			}
		}
	}
}

void EnemyDropHandler::spawnDrops( const sf::Vector2f &spawnPosition )
{
	//Randomly choses which drop to spawn
	EnemyDrop *pDrop = m_creditDrops;

	int RNG = rand( ) % k_numOfDropTypes;

	switch( RNG )
	{
		case 0: //Money
		pDrop = m_creditDrops;
		break;

		case 1: //Health shards
		pDrop = m_healthDrops;
		break;

		case 2: //Bomb
		pDrop = m_bombDrops;
		break;

		case 3: //Shield
		pDrop = m_shieldDrops;
		break;

		default:
		break;
	}

	for( int i = 0; i < k_numOfDrops; i++ )
	{
		if( !pDrop[i].getActiveState( ) ) //Checks if there are inactive drops of that type to spawn
		{
			pDrop[i].setPosition( spawnPosition ); 
			pDrop[i].toggleState( );
			m_numOfActiveDrops++;
			break;
		}
	}
}

void EnemyDropHandler::drawDrops( )
{
	for( int i = 0; i < k_numOfDrops; i++ )
	{
		if( m_creditDrops[i].getActiveState( ) )
		{
			m_window.draw( m_creditDrops[i] );
		}

		if( m_healthDrops[i].getActiveState( ) )
		{
			m_window.draw( m_healthDrops[i] );
		}

		if( m_bombDrops[i].getActiveState( ) )
		{
			m_window.draw( m_bombDrops[i] );
		}

		if( m_shieldDrops[i].getActiveState( ) )
		{
			m_window.draw( m_shieldDrops[i] );
		}
	}
}

void EnemyDropHandler::decreaseNumOfActiveDrops( )
{
	m_numOfActiveDrops--;
}

const bool EnemyDropHandler::getAreDropsActive( ) const
{
	return m_areDropsActive;
}

EnemyDrop *EnemyDropHandler::getDrop( const EnemyDropType &dropType )
{
	switch( dropType )
	{
		case EnemyDropType::credit:
		return m_creditDrops;
		break;

		case EnemyDropType::health:
		return m_healthDrops;
		break;

		case EnemyDropType::bomb:
		return m_bombDrops;
		break;

		case EnemyDropType::shield:
		return m_shieldDrops;
		break;

		default:
		break;
	}
}

void EnemyDropHandler::reset( )
{
	for( int i = 0; i < k_numOfDrops; i++ )
	{
		if( m_creditDrops[i].getActiveState( ) )
		{
			m_creditDrops[i].toggleState( );
		}

		if( m_healthDrops[i].getActiveState( ) )
		{
			m_healthDrops[i].toggleState( );
		}

		if( m_bombDrops[i].getActiveState( ) )
		{
			m_bombDrops[i].toggleState( );
		}

		if( m_shieldDrops[i].getActiveState( ) )
		{
			m_shieldDrops[i].toggleState( );
		}
	}

	m_numOfActiveDrops = 0;
	m_areDropsActive = false;
}