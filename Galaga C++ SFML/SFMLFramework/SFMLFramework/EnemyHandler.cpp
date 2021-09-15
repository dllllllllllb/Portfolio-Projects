//Author: Maciej Dowbor
//Module: MED5149
//Date last accessed: 20/01/2021
#include "EnemyHandler.h"

EnemyHandler::EnemyHandler( sf::RenderWindow &window,
							Textures *textures,
							EnemyDropHandler *dropHandler,
							Player *player,
							WaveHandler *waveHandler,
							UserInterface *UI,
							Shop *shop ) :
	m_pTextures							( textures ),
	m_bulletPool						( textures->m_bullet, k_numOfEnemyBullets ),
	m_numOfEnemies						( 0 ),
	m_currentEnemies					( 0 ),
	m_behaviourRNGTimer					( 0 ),
	m_pPlayerBulletPool					( player->getBulletPool( ) ),
	m_window							( window ),
	m_pDropHandler						( dropHandler ),
	m_pPlayer							( player ),
	m_pWaveHandler						( waveHandler ),
	m_currentWave						( 0 ),
	m_pShop								( shop ),
	m_isShopActive						( false ),
	m_pUI								( UI ),
	m_areEnemiesInPosition				( false ),
	m_enemiesInPosition					( 0 ),
	m_timeBetweenActivatingEnemiesTimer	( 0 ),
	m_areAllEnemiesDestroyed			( false ),
	m_areTanksInsPosition				( false ),
	m_checkForInactiveEnemies			( false )

{
	m_pEnemies			= new Enemy[1];
	m_pBufferExplosion	= new sf::SoundBuffer[k_numOfExplosionBuffers];
	m_pSoundExplosion	= new sf::Sound[k_numOfExplosionBuffers];

	spawnEnemies( );
	rotateBullets( );
	setUpAudio( );
}

EnemyHandler::~EnemyHandler( )
{
	delete[] m_pEnemies;
	m_pEnemies = nullptr;

	delete[] m_pBufferExplosion;
	m_pBufferExplosion = nullptr;

	delete[] m_pSoundExplosion;
	m_pSoundExplosion = nullptr;
}

void EnemyHandler::update( const float &deltaTime )
{
	//Tested std::vector vs looping through all entities and checking active state
	//sdt::vector version is faster so I used it, if I didn't forget, I should have included prnt screens of testing results in the zip file

	m_activeEnemies		.clear( );
	m_activeEnemyBullets.clear( );

	for( int i = 0; i < m_numOfEnemies; i++ ) //Checks for active enemies and adds their index to a vector array
	{
		if( m_pEnemies[i].getActiveState( ) )
		{
			m_activeEnemies.push_back( i );
		}
	}

	for( int i = 0; i < k_numOfEnemyBullets; i++ ) //Checks for active bullets and adds their index to a vector array
	{
		if( m_bulletPool.getBullet( i )->getActiveState( ) )
		{
			m_activeEnemyBullets.push_back( i );
		}
	}
	m_activeEnemiesSize = m_activeEnemies.size( );
	m_activeEnemyBulletsSize = m_activeEnemyBullets.size( );

	if( m_areEnemiesInPosition ) 
	{
		m_behaviourRNGTimer += deltaTime;

		for( int i = 0; i < m_activeEnemiesSize; i++ )
		{
			if( m_behaviourRNGTimer > k_behaviourRNGInterval )
			{
				determineBehaviour( m_activeEnemies[i] );
			}
			m_pEnemies[m_activeEnemies[i]].update( deltaTime, m_pPlayer->getPosition( ) );
			m_pEnemies[m_activeEnemies[i]].shoot( deltaTime, &m_bulletPool );

			//Check for bullet collisions
			checkForPlayerBulletCollision( m_activeEnemies[i] );
		}

		if( m_behaviourRNGTimer > k_behaviourRNGInterval )
		{
			m_behaviourRNGTimer = 0; //Cant be inside for loop above as it will only roll for the 1st enemy and reset the timer
		}

		checkPlayerCollisions( );

		if( m_areAllEnemiesDestroyed ) //Makes sure all enemies are destroyed and all drops are inactive before activating shop
		{
			if( !m_pDropHandler->getAreDropsActive( ) )
			{
				if( m_currentWave < k_numOfWaves )
				{
					m_pShop->toggleActiveState( );
					m_areAllEnemiesDestroyed = false;
				}
				else
				{
					m_areAllEnemiesDestroyed = false;
					m_pUI->toggleVictory( ); //toggles victory state
				}
			}
		}

		if( !m_areTanksInsPosition )
		{
			checkIfTankEnemiesAreInPosition( );
		}

		checkIfShopIsActive( );
	}
	else 
	{
		moveEnemiesInPosition( deltaTime );
		for( int i = 0; i < m_activeEnemiesSize; i++ )
		{
			m_pEnemies[m_activeEnemies[i]].update( deltaTime, m_pPlayer->getPosition( ) );
			m_pEnemies[m_activeEnemies[i]].shoot( deltaTime, &m_bulletPool );
			checkForPlayerBulletCollision( m_activeEnemies[i] );
		}
	}

	checkForEnemyBulletCollision( );
	updateBullets( deltaTime );
}

void EnemyHandler::determineBehaviour( const int &index )
{
	if( m_pEnemies[index].getBehaviourState( ) == EnemyState::idle ) //Makes sure enemies are idle
	{
		int randomNum = rand( ) % 100;
		if( randomNum < k_chanceToSwitchBehaviour )
		{
			m_pEnemies[index].choseBehaviour( );
		}
	}
}

void EnemyHandler::checkForPlayerBulletCollision( const int &index )
{
	Bullet *pBullet;
	for( int k = 0; k < k_numOfBullets; k++ )
	{
		pBullet = m_pPlayerBulletPool->getBullet( k );

		if( pBullet->getActiveState( ) )
		{
			if( m_pEnemies[index].collisionCheck( pBullet->getPosition( ) ) && m_pEnemies[index].getActiveState( ) )
			{
				pBullet->toggleState( );
				if( m_pEnemies[index].takeDamage( ) )
				{
					enemyDestroyed( index );
				}
			}
		}
	}
}

void EnemyHandler::checkNumOfEnemies( )
{
	if( m_currentEnemies <= 0 )
	{
		m_areAllEnemiesDestroyed = true;
	}
}

void EnemyHandler::spawnEnemies( )
{
	if( m_currentWave < k_numOfWaves )
	{
		m_areTanksInsPosition = false;
		createEnemies( m_pWaveHandler->getWaveData( m_currentWave ) );
	}
}

void EnemyHandler::checkIfShopIsActive( )
{
	if( m_isShopActive )
	{
		if( !m_pShop->getAcviteState( ) )
		{
			m_areAllEnemiesDestroyed = false;
			m_isShopActive = false;
			m_areEnemiesInPosition = false;
			m_currentWave++;
			m_pUI->updateText( UIVariable::wave, m_currentWave + 1 );
			spawnEnemies( );
		}
	}

	if( m_isShopActive != m_pShop->getAcviteState( ) )
	{
		m_isShopActive = true;
	}
}

void EnemyHandler::checkForEnemyBulletCollision( )
{
	Bullet *pBullet;

	for( int i = 0; i < m_activeEnemyBulletsSize; i++ )
	{
		pBullet = m_bulletPool.getBullet( m_activeEnemyBullets[i] );

		if( m_pPlayer->collisionCheck( pBullet->getPosition( ) ) )
		{
			m_pPlayer->changeValueInt( PlayerValues::health, -k_enemyDamage );
			pBullet->toggleState( );
		}
	}
}

void EnemyHandler::moveEnemiesInPosition( const float &deltaTime )
{
	//Systematically moves enemies into position
	m_timeBetweenActivatingEnemiesTimer += deltaTime;

	if( m_timeBetweenActivatingEnemiesTimer > k_timeBetweenActivatingEnemies )
	{
		m_timeBetweenActivatingEnemiesTimer = 0;

		for( int i = m_enemiesInPosition; i < m_numOfEnemies / 2; i++ ) //Releases two enemies at a time
		{
			m_enemiesInPosition++;
			m_pEnemies[i].setEnemyBehaviour( EnemyState::initialManeuver );
			int temp = m_numOfEnemies - 1 - i;
			m_pEnemies[temp].setEnemyBehaviour( EnemyState::initialManeuver );
			break;
		}

		if( m_enemiesInPosition + 1 > m_numOfEnemies / 2 )
		{
			if( !m_checkForInactiveEnemies )
			{
				m_checkForInactiveEnemies = true;
			}
			else
			{
				for( int k = 0; k < m_numOfEnemies; k++ ) //Makes sure that all enemies are on the screen
				{
					if( m_pEnemies[k].getActiveState( ) )
					{
						if( m_pEnemies[k].getBehaviourState( ) == EnemyState::inactive )
						{
							m_pEnemies[k].setEnemyBehaviour( EnemyState::initialManeuver );
						}
					}
				}
				m_enemiesInPosition = 0;
				m_areEnemiesInPosition = true;
				m_checkForInactiveEnemies = false;
			}
		}
	}
}

void EnemyHandler::enemyDestroyed( const int &index )
{
	m_pEnemies[index].toggleState( );

	int rng = rand( ) % k_dropSpawnRNG;
	if( rng < 4 )
	{
		m_pDropHandler->spawnDrops( m_pEnemies[index].getPosition( ) );
	}
	m_pPlayer->changeValueInt( PlayerValues::score, k_scoreIncrement );

	playExplosion( );

	m_currentEnemies--;
	checkNumOfEnemies( );
}

void EnemyHandler::checkIfTankEnemiesAreInPosition( )
{
	int numOfTanksActive		= 0;
	int numOfTanksInPosition	= 0;
	std::vector<int> tanksId;	//Vector of active tanks indexes

	for( int i = 0; i < m_activeEnemiesSize; i++ )
	{
		if( m_pEnemies[m_activeEnemies[i]].getEnemyType( ) == EnemyType::tank )
		{
			numOfTanksActive++;

			if( m_pEnemies[m_activeEnemies[i]].getBehaviourState( ) == EnemyState::idle )
			{
				numOfTanksInPosition++;
				tanksId.push_back( m_activeEnemies[i] );
			}
		}
	}

	if( numOfTanksActive == numOfTanksInPosition )
	{
		for( int j = 0; j < tanksId.size( ); j++ )
		{
			m_pEnemies[tanksId[j]].setEnemyBehaviour( EnemyState::movingRight );
		}
		m_areTanksInsPosition = true;
	}
}

void EnemyHandler::checkPlayerCollisions( )
{
	sf::Vector2f playerPosition = m_pPlayer->getPosition( );

	for( int i = 0; i < m_activeEnemiesSize; i++ )
	{
		EnemyState state = m_pEnemies[m_activeEnemies[i]].getBehaviourState( );

		if( state == EnemyState::kamikaze || state == EnemyState::dive ) //Only checks collision between player and enemies that are either diving or flying towards player as other enemies are too high to collide with the player
		{
			if( m_pEnemies[m_activeEnemies[i]].collisionCheck( playerPosition ) )
			{
				enemyDestroyed( m_activeEnemies[i] );
				m_pPlayer->changeValueInt( PlayerValues::health, -k_enemyDamage );
			}
		}
	}
}

void EnemyHandler::createEnemies( WaveData &waveData )
{
	m_numOfEnemies			= 0;
	int sizeOfArray			= waveData.getWaveSize( );
	const int *pWaveSetup	= waveData.getWaveSetup( );

	for( int i = 0; i < sizeOfArray; i++ ) //Counts how many enemies there are in the wave
	{
		if( pWaveSetup[i] != 0 )
		{
			m_numOfEnemies++;
		}
	}

	deleteEnemies( ); //Deletes current enemies and creates a new array
	m_pEnemies = new Enemy[m_numOfEnemies];
	m_currentEnemies = m_numOfEnemies;

	//Sets temporary variables
	float tempPosX				= k_enemyMinPosX;
	float tempPosY				= k_enemyMinPosY;
	int   entitiesPerRowCounter = 0;
	int   emptyFields			= 0;
	int   currEnemy				= 0;
	int	  enemySize				= m_pTextures->m_enemyShooter.getSize( ).x;
	int   enemyCounter			= 0;

	sf::Vector2f startPos1 = sf::Vector2f( k_enemyStartPosition.x - 64, k_enemyStartPosition.y );
	sf::Vector2f startPos2 = sf::Vector2f( k_enemyStartPosition.x + 64, k_enemyStartPosition.y );

	for( int i = 0; i < sizeOfArray; i++ ) //Loops through the entire array and pick up enemies and empty spaces based on key: 0 == Empty, 1 == Shooter, 2 == Kamikaze, 3 == Tank, 4 == Elite, 5 == Boss
	{
		currEnemy = i - emptyFields;
		sf::Vector2f tempVector;

		//Enemies are spawned off screen in two places and are systematically moved to their actual positions
		//This determines in which place current enemy will be spawned

		//Made an "if" statement this way for demonstration only, I would normally do a proper "if" statement
		( enemyCounter <= m_numOfEnemies / 2 ) ? ( tempVector = startPos1 ) : ( tempVector = startPos2 );

		switch( pWaveSetup[i] )
		{
			case 0: //No enemy
			{
				emptyFields++;
			}
			break;

			case 1: //Shooter
			{
				enemyCounter++;
				m_pEnemies[currEnemy].load( m_pTextures->m_enemyShooter );
				m_pEnemies[currEnemy].setPosition( tempVector );
				m_pEnemies[currEnemy].setStartPosition( sf::Vector2f( tempPosX, tempPosY ) );
				//EnemyType is set to Shooter by default
			}
			break;

			case 2: //Kamikaze
			{
				enemyCounter++;
				m_pEnemies[currEnemy].load( m_pTextures->m_enemyKamikaze );
				m_pEnemies[currEnemy].setPosition( tempVector );
				m_pEnemies[currEnemy].setStartPosition( sf::Vector2f( tempPosX, tempPosY ) );
				m_pEnemies[currEnemy].setType( EnemyType::kamikaze );
			}
			break;

			case 3: //Tank
			{
				enemyCounter++;
				m_pEnemies[currEnemy].load( m_pTextures->m_enemyTank );
				m_pEnemies[currEnemy].setPosition( tempVector );
				m_pEnemies[currEnemy].setStartPosition( sf::Vector2f( tempPosX, tempPosY ) );
				m_pEnemies[currEnemy].setType( EnemyType::tank );
			}
			break;

			case 4: //Elite
			{
				enemyCounter++;
				m_pEnemies[currEnemy].load( m_pTextures->m_enemyElite );
				m_pEnemies[currEnemy].setPosition( tempVector );
				m_pEnemies[currEnemy].setStartPosition( sf::Vector2f( tempPosX, tempPosY ) );
				m_pEnemies[currEnemy].setType( EnemyType::elite );
			}
			break;

			case 5: //Boss
			{
				enemyCounter++;
				m_pEnemies[currEnemy].load( m_pTextures->m_enemyBoss );
				m_pEnemies[currEnemy].setPosition( tempVector );
				m_pEnemies[currEnemy].setStartPosition( sf::Vector2f( tempPosX, tempPosY ) );
				m_pEnemies[currEnemy].setType( EnemyType::boss );
			}
			break;

			default:
			{
			}
			break;
		}

		//Calculates next position of an enemy
		entitiesPerRowCounter++;
		tempPosX += enemySize;
		if( entitiesPerRowCounter >= k_enemiesPerRow )
		{
			tempPosX = k_enemyMinPosX;
			tempPosY += enemySize;
			entitiesPerRowCounter = 0;
		}
	}
}

void EnemyHandler::deleteEnemies( )
{
	delete[] m_pEnemies;
	m_pEnemies = nullptr;
}

void EnemyHandler::drawEnemies( )
{
	for( int i = 0; i < m_activeEnemiesSize; i++ )
	{
		m_window.draw( m_pEnemies[m_activeEnemies[i]] );
	}
}

void EnemyHandler::updateBullets( const float &deltaTime )
{
	Bullet *pBullet;

	for( int i = 0; i < m_activeEnemyBulletsSize; i++ )
	{
		pBullet = m_bulletPool.getBullet( m_activeEnemyBullets[i] );
		pBullet->updateEnemy( deltaTime, m_pPlayer->getPosition( ) );
	}
}

void EnemyHandler::drawBullets( )
{
	Bullet *pBullet;

	for( int i = 0; i < m_activeEnemyBulletsSize; i++ )
	{
		pBullet = m_bulletPool.getBullet( m_activeEnemyBullets[i] );

		m_window.draw( *pBullet );
	}
}

void EnemyHandler::rotateBullets( )
{
	for( int i = 0; i < k_numOfEnemyBullets; i++ )
	{
		m_bulletPool.getBullet( i )->setRotation( 180 );
	}
}

void EnemyHandler::setUpAudio( )
{
	for( int i = 0; i < k_numOfExplosionBuffers; i++ )
	{
		ASSERT( m_pBufferExplosion[i].loadFromFile( "Assets/Audio/Explosion.wav" ) );

		m_pSoundExplosion[i].setBuffer( m_pBufferExplosion[i] );
		m_pSoundExplosion[i].setVolume( k_explosionVolume );
	}
}

void EnemyHandler::playExplosion( )
{
	for( int i = 0; i < k_numOfExplosionBuffers; i++ )
	{
		if( m_pSoundExplosion[i].getStatus( ) != sf::Sound::Status::Playing )
		{
			m_pSoundExplosion[i].play( );
			break;
		}
	}
}

BulletPool *EnemyHandler::getBulletPool( )
{
	return &m_bulletPool;
}

void EnemyHandler::reset( )
{
	m_numOfEnemies						= 0;
	m_currentEnemies					= 0;
	m_behaviourRNGTimer					= 0;
	m_currentWave						= 0;
	m_isShopActive						= false;
	m_areEnemiesInPosition				= false;
	m_enemiesInPosition					= 0;
	m_timeBetweenActivatingEnemiesTimer = 0;
	m_areAllEnemiesDestroyed			= false;
	m_areTanksInsPosition				= false;
	m_checkForInactiveEnemies			= false;
	spawnEnemies( );
	rotateBullets( );

	for( int i = 0; i < k_numOfEnemyBullets; i++ ) //Deactivates bullets and resets their trajectory
	{
		if( m_bulletPool.getBullet( i )->getActiveState( ) )
		{
			m_bulletPool.getBullet( i )->toggleState( );
			m_bulletPool.getBullet( i )->setBulletTrajectory( BulletTrajectory::none );
		}
	}
}