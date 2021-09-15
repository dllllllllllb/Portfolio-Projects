//Author: Maciej Dowbor
//Module: MED5149
//Date last accessed: 20/01/2021

#include "Bullet.h"

Bullet::Bullet( ) :
	m_trajectory		( BulletTrajectory::up ),
	m_isTrajectorySet	( false ),
	m_directionX		( 0 ),
	m_directionY		( 0 )
{
	m_isActive = false;
}

Bullet::~Bullet( )
{
}

void Bullet::updatePlayer( const float &deltaTime )
{
	//Updates bullet based on its trajectory
	switch( m_trajectory )
	{
		case BulletTrajectory::left: //Bullet shifts to the left
		move( -k_bulletSpeedX * deltaTime, k_bulletSpeedY * deltaTime );
		break;

		case BulletTrajectory::up: //Bullet travelles straight up
		move( 0, k_bulletSpeedY * deltaTime );
		break;

		case BulletTrajectory::right: //Bullet shifts to the right
		move( k_bulletSpeedX * deltaTime, k_bulletSpeedY * deltaTime );
		break;

		default:
		break;
	}

	if( getPosition( ).y < -16 ) //Checks if the bullet is off screen
	{
		toggleState( ); //Deactivates the bullet

		if( m_trajectory != BulletTrajectory::up ) //Resets its values if they have been changed
		{
			m_trajectory = BulletTrajectory::up;
			setRotation( 0 );
		}
	}
}

void Bullet::updateEnemy( const float &deltaTime, const sf::Vector2f &playerPosition )
{
	if( m_trajectory == BulletTrajectory::player ) //Checks bullet trajectory
	{
		if( !m_isTrajectorySet ) //Calculates the trajectory and rotation of the bullet
		{
			//Gets the difference in x and y coordinates
			float deltaX = playerPosition.x - getPosition( ).x;
			float deltaY = playerPosition.y - getPosition( ).y;
			float deltaYRotation = getPosition( ).y - playerPosition.y; //Used for rotation, due to the way x and y axis values are set up it need to be y1 - y2 to calculate accurate rotation

			float totalDistance = abs( deltaX ) + abs( deltaY ); //Gets modular of x and y distance between bullet and player position
			m_directionX = deltaX / totalDistance; //Calculates ratio at which the bullet will need to travel each update to intersect player position at the time of launch
			m_directionY = deltaY / totalDistance;

			float rotationAngle = atan2( deltaX, deltaYRotation ) * 180 / M_PI; //Calculates angle of the trajectory line
			setRotation( rotationAngle );

			m_isTrajectorySet = true;
		}

		move( m_directionX * k_enemyBulletSpeed * deltaTime, m_directionY * k_enemyBulletSpeed * deltaTime );

		if( getPosition( ).y > k_windowSizeY ) //Checks if the bullet is off the screen and resets its values
		{
			m_isTrajectorySet = false;
			m_trajectory = BulletTrajectory::none;
			setRotation( 180 );
			toggleState( );
		}
	}
	else
	{
		move( 0, k_enemyBulletSpeed * deltaTime );

		if( getPosition( ).y > k_windowSizeY )
		{
			toggleState( );
		}
	}
}

void Bullet::setBulletTrajectory( const BulletTrajectory &trajectory )
{
	m_trajectory = trajectory;
}