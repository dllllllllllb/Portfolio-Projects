//Author: Maciej Dowbor
//Module: MED5149
//Date last accessed: 20/01/2021

#include "Player.h"

Player::Player( sf::RenderWindow &window, const sf::Texture &playerTexture, const sf::Texture &bulletTexture, UserInterface *UI, EnemyDropHandler *enemyDropHandler ) :
	m_bulletPool			( bulletTexture, k_numOfBullets ),
	m_fireTimer				( 0 ),
	m_rateOfFire			( k_playerRateOfFire ),
	m_speed					( k_playerSpeed ),
	m_reloaded				( false ),
	m_isKeyPressed			( false ),
	m_rotation				( 0.f ),
	m_window				( window ),
	m_pUserInterface		( UI ),
	m_pEnemyDropHandler		( enemyDropHandler ),
	m_health				( k_maxPlayerHealth ),
	m_shield				( k_maxPlayerShield ),
	m_score					( 0 ),
	m_credits				( 0 ),
	m_weaponType			( PlayerWeapons::singleShot ),
	m_bulletWidth			( m_bulletPool.getBullet( 0 )->getLocalBounds( ).width ),
	m_areControlsActive		( true ),
	m_tookDamage			( false ),
	m_invulnerabilityTimer	( 0 )
{
	load( playerTexture );
	setPosition( k_playerStartPosition );
	setUpAudio( );
}

Player::~Player( )
{
}

void Player::update( const float &deltaTime )
{
	if( m_areControlsActive )
	{
		checkInput( deltaTime );
	}

	updateBullets( deltaTime );

	if( !m_reloaded )
	{
		reload( deltaTime );
	}

	checkDropsCollision( );

	if( m_tookDamage )
	{
		invulnerability( deltaTime );
	}
}

void Player::checkInput( const float &deltaTime )
{
	m_isKeyPressed = false;
	m_rotation = getRotation( );

	//Move right
	if( ( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Right ) || sf::Keyboard::isKeyPressed( sf::Keyboard::Key::D ) ) && g_isWindowSelected )
	{
		move( m_speed * deltaTime, 0.f );
		m_isKeyPressed = true;
		smoothRotation( deltaTime, true );

		if( getPosition( ).x > k_windowSizeX ) //If player gets off the screen, they will appear on the other side
		{
			setPosition( 0, k_playerStartPosition.y );
		}
	}

	//Move left
	if( ( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Left ) || sf::Keyboard::isKeyPressed( sf::Keyboard::Key::A ) ) && g_isWindowSelected )
	{
		move( -m_speed * deltaTime, 0.f );
		m_isKeyPressed = true;
		smoothRotation( deltaTime, false );

		if( getPosition( ).x < 0 ) //If player gets off the screen, they will appear on the other side
		{
			setPosition( k_windowSizeX, k_playerStartPosition.y );
		}
	}

	//Shoot
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Space ) && g_isWindowSelected )
	{
		shoot( );
	}

	//Reset player rotation
	if( !m_isKeyPressed )
	{
		resetRotation( deltaTime );
	}
}

void Player::smoothRotation( const float &deltaTime, const bool movingRight )
{
	if( movingRight )
	{
		//Rotate right
		if( m_rotation <= 45 || m_rotation >= 310 )
		{
			rotate( k_playerRotationSpeed * deltaTime );
		}
	}
	else
	{
		//Rotate left
		if( m_rotation >= 315 || m_rotation <= 50 )
		{
			rotate( -k_playerRotationSpeed * deltaTime );
		}
	}
}

void Player::resetRotation( const float &deltaTime )
{
	if( m_rotation != 0 )
	{
		if( m_rotation <= 2 || m_rotation >= 358 )
		{
			setRotation( 0 );
		}

		if( m_rotation <= 180 )
		{
			rotate( -k_playerRotationSpeed * deltaTime );
		}
		else
		{
			rotate( k_playerRotationSpeed * deltaTime );
		}
	}
}

void Player::shoot( )
{
	switch( m_weaponType )
	{
		case PlayerWeapons::singleShot:
		singleShot( );
		break;

		case PlayerWeapons::doubleShot:
		doubleShot( );
		break;

		case PlayerWeapons::tripleShot:
		tripleShot( );
		break;

		case PlayerWeapons::quadraShot:
		quadraShot( );
		break;

		default:
		break;
	}
}

void Player::singleShot( )
{
	Bullet *bulletPtr;

	if( m_reloaded )
	{
		for( int i = 0; i < k_numOfBullets; i++ )
		{
			bulletPtr = m_bulletPool.getBullet( i );

			//Get first inactive bullet
			if( !bulletPtr->getActiveState( ) )
			{
				bulletPtr->toggleState( ); //Flips state to active
				bulletPtr->setPosition( getPosition( ) ); //Sets bullets position
				m_reloaded = false;
				m_bulletPool.playSound( );

				break;
			}
		}
	}
}

void Player::doubleShot( )
{
	Bullet *bulletPtr;

	if( m_reloaded )
	{
		for( int k = 0; k < 2; k++ )
		{
			for( int i = 0; i < k_numOfBullets; i++ )
			{
				bulletPtr = m_bulletPool.getBullet( i );

				//Get first inactive bullet
				if( !bulletPtr->getActiveState( ) )
				{
					bulletPtr->toggleState( ); //Flips state to active

					if( k )
					{
						bulletPtr->setPosition( getPosition( ).x - m_bulletWidth, k_playerStartPosition.y ); //Sets bullets position
						m_bulletPool.playSound( );
					}
					else
					{
						bulletPtr->setPosition( getPosition( ).x + m_bulletWidth, k_playerStartPosition.y );
					}
					m_reloaded = false;

					break;
				}
			}
		}
	}
}

void Player::tripleShot( )
{
	Bullet *bulletPtr;

	if( m_reloaded )
	{
		for( int k = 0; k < 3; k++ )
		{
			for( int i = 0; i < k_numOfBullets; i++ )
			{
				bulletPtr = m_bulletPool.getBullet( i );

				//Get first inactive bullet
				if( !bulletPtr->getActiveState( ) )
				{
					bulletPtr->toggleState( ); //Flips state to active
					m_reloaded = false;

					switch( k )
					{
						case 0:
						bulletPtr->setBulletTrajectory( BulletTrajectory::left );
						bulletPtr->setPosition( getPosition( ).x - m_bulletWidth, k_playerStartPosition.y );
						bulletPtr->setRotation( 315 );
						break;

						case 1:
						bulletPtr->setBulletTrajectory( BulletTrajectory::up );
						bulletPtr->setPosition( getPosition( ) );
						m_bulletPool.playSound( );
						bulletPtr->setRotation( 0 );
						break;

						case 2:
						bulletPtr->setBulletTrajectory( BulletTrajectory::right );
						bulletPtr->setPosition( getPosition( ).x + m_bulletWidth, k_playerStartPosition.y );
						bulletPtr->setRotation( 45 );
						break;

						default:
						break;
					}

					break;
				}
			}
		}
	}
}

void Player::quadraShot( )
{
	Bullet *bulletPtr;

	if( m_reloaded )
	{
		for( int k = 0; k < 4; k++ )
		{
			for( int i = 0; i < k_numOfBullets; i++ )
			{
				bulletPtr = m_bulletPool.getBullet( i );

				//Get first inactive bullet
				if( !bulletPtr->getActiveState( ) )
				{
					bulletPtr->toggleState( ); //Flips state to active
					m_reloaded = false;

					switch( k )
					{
						case 0:
						bulletPtr->setPosition( getPosition( ).x - m_bulletWidth * 2, k_playerStartPosition.y );
						break;

						case 1:
						bulletPtr->setPosition( getPosition( ).x - m_bulletWidth * 0.75, k_playerStartPosition.y );
						m_bulletPool.playSound( );
						break;

						case 2:
						bulletPtr->setPosition( getPosition( ).x + m_bulletWidth * 0.75, k_playerStartPosition.y );
						break;

						case 3:
						bulletPtr->setPosition( getPosition( ).x + m_bulletWidth * 2, k_playerStartPosition.y );
						break;

						default:
						break;
					}

					break;
				}
			}
		}
		m_bulletPool.playSound( );
	}
}

void Player::drawBullets( )
{
	Bullet *bulletPtr;

	for( int i = 0; i < k_numOfBullets; i++ )
	{
		bulletPtr = m_bulletPool.getBullet( i );

		if( bulletPtr->getActiveState( ) )
		{
			m_window.draw( *bulletPtr );
		}
	}
}

BulletPool *Player::getBulletPool( )
{
	return &m_bulletPool;
}

void Player::setWeaponType( const PlayerWeapons &weaponType )
{
	m_weaponType = weaponType;
}

void Player::changeValueInt( const PlayerValues &variable, const int &value )
{
	switch( variable )
	{
		case PlayerValues::health:
		{
			if( value < 0 )
			{
				if( !m_tookDamage )
				{
					takeDamage( value );
				}
			}
			else
			{
				m_health += value;
			}
			m_pUserInterface->updateText( UIVariable::health, m_health );
		}
		break;

		case PlayerValues::shield:
		{
			m_shield += value;
			m_pUserInterface->updateText( UIVariable::shield, m_shield );
		}
		break;

		case PlayerValues::score:
		{
			m_score += value;
			m_pUserInterface->updateText( UIVariable::score, m_score );
		}
		break;

		case PlayerValues::credits:
		{
			m_credits += value;
			m_pUserInterface->updateText( UIVariable::credits, m_credits );
		}
		break;

		default:
		break;
	}
}

void Player::changeValueFloat( const PlayerValues &variable, const float &value )
{
	switch( variable )
	{
		case PlayerValues::rateOfFire:
		{
			m_rateOfFire += value;
		}
		break;

		case PlayerValues::speed:
		{
			m_speed += value;
		}

		default:
		break;
	}
}

const int &Player::getValue( const PlayerValues &variable ) const
{
	switch( variable )
	{
		case PlayerValues::health:
		{
			return m_health;
		}
		break;

		case PlayerValues::shield:
		{
			return m_shield;
		}
		break;

		case PlayerValues::score:
		{
			return m_score;
		}
		break;

		case PlayerValues::credits:
		{
			return m_credits;
		}
		break;

		default:
		break;
	}
}

void Player::toggleControls( )
{
	m_areControlsActive = !m_areControlsActive;
	setRotation( 0 );
}

void Player::reset( )
{
	m_fireTimer				= 0;
	m_rateOfFire			= k_playerRateOfFire;
	m_speed					= k_playerSpeed;
	m_reloaded				= false;
	m_isKeyPressed			= false;
	m_rotation				= 0.0f;
	m_health				= k_maxPlayerHealth;
	m_shield				= k_maxPlayerShield;
	m_score					= 0;
	m_credits				= 0;
	m_weaponType			= PlayerWeapons::singleShot;
	m_areControlsActive		= true;
	m_tookDamage			= false;
	m_invulnerabilityTimer	= 0;

	setPosition( k_playerStartPosition );

	Bullet *tempBullet;
	for( int i = 0; i < k_numOfBullets; i++ ) //Reset all player bullets
	{
		tempBullet = m_bulletPool.getBullet( i );
		if( tempBullet->getActiveState( ) )
		{
			tempBullet->toggleState( );
			tempBullet->setBulletTrajectory( BulletTrajectory::up );
			tempBullet->setRotation( 0 );
		}
	}
}

const PlayerWeapons Player::getWeaponType( ) const
{
	return m_weaponType;
}

void Player::updateBullets( const float &deltaTime )
{
	Bullet *bulletPtr;

	for( int i = 0; i < k_numOfBullets; i++ )
	{
		bulletPtr = m_bulletPool.getBullet( i );

		if( bulletPtr->getActiveState( ) )
		{
			bulletPtr->updatePlayer( deltaTime );
		}
	}
}

void Player::reload( const float &deltaTime )
{
	m_fireTimer -= deltaTime;
	if( m_fireTimer <= 0 )
	{
		m_reloaded = true;
		m_fireTimer = m_rateOfFire;
	}
}

void Player::checkDropsCollision( )
{
	for( int dropType = 0; dropType < k_numOfDropTypes; dropType++ )
	{
		EnemyDrop *pDrops = m_pEnemyDropHandler->getDrop( static_cast< EnemyDropType >( dropType ) );

		for( int dropIndex = 0; dropIndex < k_numOfDrops; dropIndex++ )
		{
			if( pDrops[dropIndex].getActiveState( ) )
			{
				if( pDrops[dropIndex].getPosition( ).y > 950 ) //Checking collision above this y coordinate makes no sense because it cant collide with the player
				{
					if( collisionCheck( pDrops[dropIndex].getPosition( ) ) )
					{
						//Collision happened
						switch( dropType )
						{
							case 0: //Credit
							{
								int credits = 0;
								int rng = rand( ) % k_numOfMoneyValues;
								switch( rng )
								{
									case 0:
									{
										credits = k_creditIncrementSmall;
									}
									break;

									case 1:
									{
										credits = k_creditIncrementMedium;
									}
									break;

									case 2:
									{
										credits = k_creditIncrementLarge;
									}
									break;
								}
								changeValueInt( PlayerValues::credits, credits );
								m_soundCoinPickup.play( );
							}
							break;

							case 1: //health
							{
								if( m_health < k_maxPlayerHealth )
								{
									changeValueInt( PlayerValues::health, k_healthIncrement );
								}
								m_soundPickup.play( );
							}
							break;

							case 2: //Bomb
							{
								changeValueInt( PlayerValues::health, -k_bombDamage );
								m_soundTakingDamage.play( );
							}
							break;

							case 3: //Shield
							{
								if( m_shield < k_maxPlayerShield )
								{
									changeValueInt( PlayerValues::shield, k_shieldIncrement );
								}
								m_soundPickup.play( );
							}
							break;

							case 4: //Upgrade
							{
							//Later
							}
							break;

							default:
							break;
						}
						pDrops[dropIndex].toggleState( );
						m_pEnemyDropHandler->decreaseNumOfActiveDrops( );
					}
				}
			}
		}
	}
}

void Player::takeDamage( const int &damage )
{
	int tempDamage = abs( damage ); //Damage is taken in as minus so it needs to be converted to abs value for ease of use

	if( m_shield >= tempDamage ) //Damage is first dealt to shield
	{
		m_shield -= tempDamage;
		m_pUserInterface->updateText( UIVariable::shield, m_shield );
	}
	else
	{
		m_health -= tempDamage;
		if( m_areControlsActive )
		{
			checkHealth( );
		}
	}

	m_soundTakingDamage.play( );
	m_tookDamage = true;
	setColor( sf::Color( 255, 255, 255, 128 ) ); //Makes player half transparent
}

void Player::checkHealth( )
{
	if( m_health <= 0 )
	{
		m_health = 0;
		m_pUserInterface->updateText( UIVariable::health, m_health );
		m_pUserInterface->toggleDefeat( );
		m_areControlsActive = false;
		m_soundDeath.play( );
	}
}

void Player::invulnerability( const float &deltaTime )
{
	m_invulnerabilityTimer += deltaTime;
	if( m_invulnerabilityTimer > k_invulnerabilityTime )
	{
		m_tookDamage = false;
		setColor( sf::Color( 255, 255, 255, 255 ) ); //Resets player alpha 
		m_invulnerabilityTimer = 0;
	}
}

void Player::setUpAudio( )
{
	ASSERT( m_bufferDeath		.loadFromFile( "Assets/Audio/death.wav" ) );
	ASSERT( m_bufferPickup		.loadFromFile( "Assets/Audio/Pick up.wav" ) );
	ASSERT( m_bufferCoinPickup	.loadFromFile( "Assets/Audio/Coin pickup.wav" ) );
	ASSERT( m_bufferTakingDamage.loadFromFile( "Assets/Audio/takingDamage.wav" ) );

	m_soundDeath.setBuffer( m_bufferDeath );

	m_soundPickup.setBuffer( m_bufferPickup );
	m_soundPickup.setVolume( k_pickupVolume );

	m_soundCoinPickup.setBuffer( m_bufferCoinPickup );
	m_soundCoinPickup.setVolume( k_coinPickupVolume );

	m_soundTakingDamage.setBuffer( m_bufferTakingDamage );
	m_soundTakingDamage.setVolume( k_coinPickupVolume );
}