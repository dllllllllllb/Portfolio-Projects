//Author: Maciej Dowbor
//Module: MED5149
//Date last accessed: 20/01/2021

#include "BulletPool.h"

BulletPool::BulletPool( const sf::Texture &texture, const int &numOfBullets )
{
	//Load bullets
	m_pBullets = new Bullet[numOfBullets];

	for( int i = 0; i < numOfBullets; i++ )
	{
		m_pBullets[i].load( texture );
	}

	//Load sound
	m_pBuffer = new sf::SoundBuffer[k_numOfBulletSoundBuffers];
	m_pShootSound = new sf::Sound[k_numOfBulletSoundBuffers];

	for( int i = 0; i < k_numOfBulletSoundBuffers; i++ )
	{
		ASSERT( m_pBuffer[i].loadFromFile( "Assets/Audio/ShootPlayer.wav" ) );
		m_pShootSound[i].setBuffer( m_pBuffer[i] );
		m_pShootSound[i].setVolume( k_shootVolume );
	}
}

BulletPool::~BulletPool( )
{
	delete[] m_pBullets;
	m_pBullets = nullptr;

	delete[] m_pBuffer;
	m_pBuffer = nullptr;

	delete[] m_pShootSound;
	m_pShootSound = nullptr;
}

Bullet *BulletPool::getBullet( const int &index )
{
	return &m_pBullets[index];
}

void BulletPool::playSound( )
{
	for( int i = 0; i < k_numOfBulletSoundBuffers; i++ ) //Checks if a sound is not played
	{
		if( m_pShootSound[i].getStatus( ) != sf::Sound::Status::Playing )
		{
			float pitch = rand( ) % 5 * 0.1 + 1; //Randomises the pitch so the sound effect won't sound the same every time it's played
			m_pShootSound[i].setPitch( pitch );
			m_pShootSound[i].play( );
			break;
		}
	}
}