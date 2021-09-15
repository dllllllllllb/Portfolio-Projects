//Author: Maciej Dowbor
//Module: MED5149
//Date last accessed: 20/01/2021

#include "Enemy.h"

Enemy::Enemy( ) :
	m_type							( EnemyType::shooter ),
	m_behaviourState				( EnemyState::inactive ),
	m_idleAnimationCounter			( 12.5 ),
	m_idleAnimationSpeed			( k_idleAnimationSpeed ),
	m_idleAnimationYCoefficient		( -1 ),
	m_shootingTimer					( 0 ),
	m_idleAnimationErrorAllowance	( k_idleAnimationXRange + k_idleAnimationXRange * 0.3 ),
	m_health						( k_enemyHealth ),
	m_rateOfFire					( k_enemyRateOfFire ),
	m_speed							( k_enemySpeed ),
	m_numOfBehaviours				( k_numOfBehavioursShooter ),
	m_behaviourChancesTotal			( 0 ),
	m_isDisplacedByIdleAnimation	( false ),
	m_windowBorderX					( k_windowSizeX + 32 ),
	m_isInStartPosition				( false ),
	m_gotHit						( false )
{
	m_pBehaviourChances = new int[m_numOfBehaviours]
	{
		k_enemyDiveChance
	};
	calcTotalBehaviourChance( );
}

Enemy::~Enemy( )
{
	delete[] m_pBehaviourChances;
	m_pBehaviourChances = nullptr;
}

void Enemy::update( const float &deltaTime, const sf::Vector2f &playerPosition )
{
	switch( m_behaviourState ) //Updates enemy based on their behaviour state
	{
		case EnemyState::inactive:
		{
		}
		break;

		case EnemyState::idle:
		{
			idleAnimation( deltaTime );
		}
		break;

		case EnemyState::resetingPosition:
		{
			resetPosition( deltaTime );
		}
		break;

		case EnemyState::dive:
		{
			dive( deltaTime );
		}
		break;

		case EnemyState::initialManeuver:
		{
			initialManeuver( deltaTime );
		}
		break;

		case EnemyState::movingRight:
		{
			moveRight( deltaTime );
		}
		break;

		case EnemyState::kamikaze:
		{
			kamikazeManeuver( deltaTime, playerPosition );
		}
		break;

		default:
		break;
	}

	if( m_gotHit )
	{
		gotHit( deltaTime );
	}
}

void Enemy::dive( const float &deltaTime )
{
	if( getPosition( ).y < k_diveManeuverDepth )
	{
		float diveCompletionPercentageFraction = getPosition( ).y / ( k_diveManeuverDepth - m_startPosition.y ); //Calculates the percentage of completed dive as a fraction
		float newX = sin( diveCompletionPercentageFraction * k_diveOscillationInterval ) * k_diveOscilationDistanceX; //Calculates enemy x position based on the completion percentage
		move( newX * deltaTime, m_speed * deltaTime );
	}
	else
	{
		m_behaviourState = EnemyState::resetingPosition; //If the y position is bigger than dive depth, enemy will return to its position
	}
}

void Enemy::resetPosition( const float &deltaTime )
{
	sf::Vector2f targetPosition = m_startPosition - getPosition( ); //Calculates difference between pos1 and pos2

	float totalDistance = abs( targetPosition.x ) + abs( targetPosition.y ); //Absolute x and y distance

	float xMovementDirection = targetPosition.x / totalDistance; //Determines ratio x and y ratio at which the enemy has to move to intersect its start position
	float yMovementDirection = targetPosition.y / totalDistance;

	float tempSpeed = 0;

	//Decides which speed to move at
	if( m_isDisplacedByIdleAnimation ) 
	{
		tempSpeed = k_idleAnimationSpeed;
	}
	else
	{
		tempSpeed = m_speed;
	}

	move( xMovementDirection * tempSpeed * deltaTime, yMovementDirection * m_speed * deltaTime );

	if( getPosition( ).y <= m_startPosition.y ) //Checks if the eney is at it's starting position, only checks y as the enemy moves in ratios so if either x or y are in position, both must be in position
	{
		setPosition( m_startPosition ); //Sets to start position to make sure idle animation works correctly

		//Reset idle animation vars
		m_idleAnimationCounter		= 12.5;
		m_idleAnimationYCoefficient = -1;
		m_idleAnimationSpeed		= k_idleAnimationSpeed;

		m_behaviourState = EnemyState::idle; //Changes behaviour to idle
		m_isDisplacedByIdleAnimation = false;
	}
}

void Enemy::shoot( const float &deltaTime, BulletPool *bulletPool )
{
	Bullet *pBullet;
	m_shootingTimer += rand( ) % 10 * deltaTime;

	if( m_shootingTimer > m_rateOfFire )
	{
		int chanceToFire = rand( ) % k_enemyChanceToshootRange;
		if( chanceToFire < 1 )
		{
			for( int i = 0; i < k_numOfBullets; i++ ) //Loops through all bullets to get an inactive one
			{
				pBullet = bulletPool->getBullet( i );

				if( !pBullet->getActiveState( ) )
				{
					if( m_type == EnemyType::elite || m_type == EnemyType::boss ) //Checks enemy type to decide bullet trajectory
					{
						pBullet->setBulletTrajectory( BulletTrajectory::player );
					}
					pBullet->toggleState( );
					pBullet->setPosition( getPosition( ) );
					m_shootingTimer = 0;
					bulletPool->playSound( );
					break;
				}
			}
		}
	}
}

const EnemyState &Enemy::getBehaviourState( ) const
{
	return m_behaviourState;
}

const EnemyType &Enemy::getEnemyType( ) const
{
	return m_type;
}

void Enemy::idleAnimation( const float &deltaTime )
{
	//Quadratic equation to move entities left and right on a curved trajectory
	float positionY = k_idleAnimationXCoefficient * m_idleAnimationCounter * m_idleAnimationCounter - m_idleAnimationCounter;

	move( m_idleAnimationCounter * deltaTime, positionY * deltaTime * m_idleAnimationYCoefficient );
	m_idleAnimationCounter += m_idleAnimationSpeed * deltaTime;

	if( m_idleAnimationCounter > k_idleAnimationXRange || m_idleAnimationCounter < -k_idleAnimationXRange ) //Changes x and y movement direciton based on the stage of animation
	{
		m_idleAnimationSpeed *= -1;
		m_idleAnimationYCoefficient *= -1;

		//If the animation is outside of max bounds it gets reset to the max bound to make sure animation is consistent
		if( m_idleAnimationCounter > 25 )
		{
			m_idleAnimationCounter = 25;
		}
		else if( m_idleAnimationCounter < -25 )
		{
			m_idleAnimationCounter = -25;
		}
	}

	//Makes sure that enemies won't wonder off too far from their original position
	if( getPosition( ).x > m_startPosition.x + m_idleAnimationErrorAllowance || getPosition( ).x < m_startPosition.x -m_idleAnimationErrorAllowance )
	{
		m_isDisplacedByIdleAnimation = true;
		m_behaviourState = EnemyState::resetingPosition;
	}
}

void Enemy::setType( const EnemyType &enemyType )
{
	delete[] m_pBehaviourChances;
	m_pBehaviourChances = nullptr;

	m_type = enemyType;

	//This algorithm was designed for easy implementation of new behaviours
	//Changes enemy variable based on their type and determines its behaviours
	switch( m_type )
	{
		case EnemyType::shooter:
		{
			m_health			= k_enemyHealth;
			m_speed				= k_enemySpeed;
			m_rateOfFire		= k_enemyRateOfFire;
			m_numOfBehaviours	= k_numOfBehavioursShooter;

			m_pBehaviourChances = new int[m_numOfBehaviours]  //Array of chances of behaviours, to implement a new behaviour you simply increase num of behaviours and add a chance for the new behaviour to happen below
			{
				k_enemyDiveChance
			};
		}
		break;

		case EnemyType::kamikaze:
		{
			m_health			= k_enemyKamikazeHealth;
			m_speed				= k_enemyKamikazeSpeed;
			m_rateOfFire		= k_enemyKamikazeRateOfFire;
			m_numOfBehaviours	= k_numOfBehavioursKamikaze;

			m_pBehaviourChances = new int[m_numOfBehaviours]
			{
				k_enemyDiveChance, k_enemyKamikazeChance
			};
		}
		break;

		case EnemyType::tank:
		{
			m_health			= k_enemyTankHealth;
			m_speed				= k_enemyTankSpeed;
			m_rateOfFire		= k_enemyTankRateOfFire;
			m_numOfBehaviours	= k_numOfBehavioursTank;

			m_pBehaviourChances = new int[m_numOfBehaviours]
			{
				k_enemyMoveRightChance
			};
		}
		break;

		case EnemyType::elite:
		{
			m_health			= k_enemyEliteHealth;
			m_speed				= k_enemySpeed;
			m_rateOfFire		= k_enemyEliteRateOfFire;
			m_numOfBehaviours	= k_numOfBehavioursElite;

			m_pBehaviourChances = new int[m_numOfBehaviours]
			{
				k_enemyDiveChance
			};
		}
		break;

		case EnemyType::boss:
		{
			m_health			= k_enemyBossHealth;
			m_speed				= k_enemyBossSpeed;
			m_rateOfFire		= k_enemyBossRateOfFire;
			m_numOfBehaviours	= k_numOfBehavioursBoss;

			m_pBehaviourChances = new int[m_numOfBehaviours]
			{
				k_enemyDiveChance
			};
		}
		break;

		default:
		break;
	}

	calcTotalBehaviourChance( );
	m_windowBorderX += getTexture( )->getSize( ).x * 0.5f; //Used for moveRight() to loop enemies back to the other side of the screen when they move off it
}

void Enemy::choseBehaviour( )
{
	//This algorithm was designed for easy implementation of new behaviours
	int tempChance = 0;

	int randomNum = rand( ) % m_behaviourChancesTotal; //Determines what behaviour based on all chances for behaviours for this enemy type

	switch( m_type )
	{
		case EnemyType::shooter:
		{
			for( int behaviourIndex = 0; behaviourIndex < m_numOfBehaviours; behaviourIndex++ ) //Loops through all behaviours for a given enemy type
			{
				tempChance += m_pBehaviourChances[behaviourIndex]; //Adds chances and compares it to generated number and selects behaviour based o current iteration of the loop
				if( randomNum <= tempChance )					   //To add more behaviours you need to add another case: and state which behaviour it coresponds to
				{
					switch( behaviourIndex )
					{
						case 0:
						{
							m_behaviourState = EnemyState::dive;
						}
						break;

						default:
						break;
					}
				}
			}
		}
		break;

		case EnemyType::kamikaze:
		{
			for( int behaviourIndex = 0; behaviourIndex < m_numOfBehaviours; behaviourIndex++ )
			{
				tempChance += m_pBehaviourChances[behaviourIndex];
				if( randomNum <= tempChance )
				{
					switch( behaviourIndex )
					{
						case 0:
						{
							m_behaviourState = EnemyState::dive;
						}
						break;

						case 1:
						{
							m_behaviourState = EnemyState::kamikaze;
						}

						default:
						break;
					}
				}
			}
		}
		break;

		case EnemyType::tank:
		{
			//For now I want all tanks to move right as soon as they are in position so I'm commenting this bit of code out but leaving it
			//in case I will want to change that later

			//for( int behaviourIndex = 0; behaviourIndex < m_numOfBehaviours; behaviourIndex++ )
			//{
			//	tempChance += m_pBehaviourChances[behaviourIndex];
			//	if( randomNum <= tempChance )
			//	{
			//		switch( behaviourIndex )
			//		{
			//			case 0:
			//			{
			//				m_behaviourState = EnemyState::dive;
			//			}
			//			break;
			//
			//			case 1:
			//			{
			//				m_behaviourState = EnemyState::movingRight;
			//			}
			//
			//			default:
			//			break;
			//		}
			//	}
			//}
		}
		break;

		case EnemyType::elite:
		{
			for( int behaviourIndex = 0; behaviourIndex < m_numOfBehaviours; behaviourIndex++ )
			{
				tempChance += m_pBehaviourChances[behaviourIndex];
				if( randomNum <= tempChance )
				{
					switch( behaviourIndex )
					{
						case 0:
						{
							m_behaviourState = EnemyState::dive;
						}
						break;

						default:
						break;
					}
				}
			}
		}
		break;

		case EnemyType::boss:
		{
			for( int behaviourIndex = 0; behaviourIndex < m_numOfBehaviours; behaviourIndex++ )
			{
				tempChance += m_pBehaviourChances[behaviourIndex];
				if( randomNum <= tempChance )
				{
					switch( behaviourIndex )
					{
						case 0:
						{
							m_behaviourState = EnemyState::dive;
						}
						break;

						default:
						break;
					}
				}
			}
		}
		break;

		default:
		break;
	}
}

void Enemy::calcTotalBehaviourChance( )
{
	m_behaviourChancesTotal = 0;
	for( int i = 0; i < m_numOfBehaviours; i++ )
	{
		m_behaviourChancesTotal += m_pBehaviourChances[i];
	}
}

void Enemy::setStartPosition( const sf::Vector2f &position )
{
	m_startPosition = position;
}

void Enemy::initialManeuver( const float &deltaTime )
{
	//Moves enemies down
	move( 0, k_initialEnemySpeed * deltaTime );

	//Checks if the enemy is below y value and makes it reset to their starting position
	if( getPosition( ).y >= k_enemyInitialManouver.y )
	{
		m_idleAnimationCounter = 0;
		m_idleAnimationYCoefficient = -1;
		m_idleAnimationSpeed = k_idleAnimationSpeed;

		m_behaviourState = EnemyState::resetingPosition;
	}
}

void Enemy::moveRight( const float &deltaTime )
{
	if( !m_isInStartPosition ) //Checks if its in its y starting position to synchronise with the rest of enemies
	{
		float targetY = m_startPosition.y - getPosition( ).y;
		float totalDistance = abs( targetY );
		float directionYmovement = targetY / totalDistance;
		move( 0, directionYmovement * deltaTime * k_idleAnimationSpeed ); //Moves to its starting y position

		if( totalDistance < 1 )
		{
			setPosition( getPosition( ).x, m_startPosition.y );
			m_isInStartPosition = true;
		}
	}

	move( k_enemyTankBehaviourSpeed * deltaTime, 0 ); //Moves enemy to the right
	if( getPosition( ).x > m_windowBorderX ) //If the enemy is off the screen, it moves it to the other side of the screen
	{
		setPosition( 0 - getTexture( )->getSize( ).x * 0.5f, getPosition( ).y );
	}
}

void Enemy::setEnemyBehaviour( const EnemyState &enemyBehaviour )
{
	m_behaviourState = enemyBehaviour;
}

void Enemy::kamikazeManeuver( const float &deltaTime, const sf::Vector2f &playerPosition )
{
	//Moves towards player, works in the same way as resetPosition()

	sf::Vector2f targetPosition = playerPosition - getPosition( );
	float totalDistance = abs( targetPosition.x ) + abs( targetPosition.y );

	float xMovementDirection = targetPosition.x / totalDistance;
	float yMovementDirection = targetPosition.y / totalDistance;

	move( xMovementDirection * m_speed * deltaTime, yMovementDirection * m_speed * deltaTime );
}

const int &Enemy::getHealth( ) const
{
	return m_health;
}

const bool Enemy::takeDamage( )
{
	//Decrements health, changes its colour to red and checks if the enemy is destroyed

	m_health--;
	m_gotHit = true;
	setColor( sf::Color::Red );

	if( m_health < 1 )
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Enemy::gotHit( const float &deltaTime )
{
	//Resets enemy colour to white after time

	static float timer = 0;
	timer += deltaTime;

	if( timer > k_damageIndicatorTime )
	{
		m_gotHit = false;
		setColor( sf::Color::White );
		timer = 0;
	}
}