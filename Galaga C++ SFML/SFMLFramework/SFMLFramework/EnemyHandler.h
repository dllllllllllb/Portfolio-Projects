//Author: Maciej Dowbor
//Module: MED5149
//Date last accessed: 20/01/2021

#ifndef ENEMYHANDLER_H
#define ENEMYHANDLER_H

#include <SFML/System/Time.hpp>
#include <SFML/Window.hpp>
#include <vector>

#include "Enemy.h"
#include "EnemyDropHandler.h"
#include "EnemyStateEnum.h"
#include "Player.h"
#include "Shop.h"
#include "UserInterface.h"
#include "WaveData.h"
#include "WaveHandler.h"

//=====================================================================================================	
//Class		: EnemyHandler
//-----------------------------------------------------------------------------------------------------
//Purpose	: Manages enemy behaviour
//====================================================================================================
class EnemyHandler
{
private:

	Textures			*m_pTextures;
	Enemy				*m_pEnemies;
	BulletPool			m_bulletPool;
	int					m_numOfEnemies;
	int					m_currentEnemies;
	float				m_behaviourRNGTimer;
	BulletPool			*m_pPlayerBulletPool;
	sf::RenderWindow	&m_window;
	EnemyDropHandler	*m_pDropHandler;
	Player				*m_pPlayer;
	WaveHandler			*m_pWaveHandler;
	int					m_currentWave;
	Shop				*m_pShop;
	bool				m_isShopActive;
	UserInterface		*m_pUI;
	bool				m_areEnemiesInPosition;
	int					m_enemiesInPosition;
	float				m_timeBetweenActivatingEnemiesTimer;
	bool				m_areAllEnemiesDestroyed;
	bool				m_areTanksInsPosition;
	std::vector<int>	m_activeEnemies;
	std::vector<int>	m_activeEnemyBullets;
	int					m_activeEnemiesSize;
	int					m_activeEnemyBulletsSize;
	bool				m_checkForInactiveEnemies;

	sf::SoundBuffer		*m_pBufferExplosion;
	sf::Sound			*m_pSoundExplosion;

public:

	EnemyHandler( sf::RenderWindow &window,
				  Textures *textures,
				  EnemyDropHandler *dropHandler,
				  Player *player,
				  WaveHandler *waveHandler,
				  UserInterface *UI,
				  Shop *shop );
	//=================================================================================================						
	//Purpose	: Constructor
	//-------------------------------------------------------------------------------------------------
	//Parameters: Render window reference, textures, dropHandler, player, waveHandler, UI and shop
	//			  pointers
	//-------------------------------------------------------------------------------------------------
	//Returns	: -
	//=================================================================================================

	~EnemyHandler( );
	//=================================================================================================						
	//Purpose	: Destructor
	//-------------------------------------------------------------------------------------------------
	//Parameters: -
	//-------------------------------------------------------------------------------------------------
	//Returns	: -
	//=================================================================================================

	void update( const float &deltaTime );
	//=================================================================================================						
	//Purpose	: Updates contents of the class
	//-------------------------------------------------------------------------------------------------
	//Parameters: Time passed since last frame
	//-------------------------------------------------------------------------------------------------
	//Returns	: -
	//=================================================================================================

	void determineBehaviour( const int &index );
	//=================================================================================================						
	//Purpose	: Determines if an enemy should change their behaviour
	//-------------------------------------------------------------------------------------------------
	//Parameters: Enemy index
	//-------------------------------------------------------------------------------------------------
	//Returns	: -
	//=================================================================================================

	void checkForPlayerBulletCollision( const int &index );
	//=================================================================================================						
	//Purpose	: Checks in an enemy got hit by player bullet
	//-------------------------------------------------------------------------------------------------
	//Parameters: Enemy index
	//-------------------------------------------------------------------------------------------------
	//Returns	: -
	//=================================================================================================

	void checkNumOfEnemies( );
	//=================================================================================================						
	//Purpose	: Checks if there are active enemies 
	//-------------------------------------------------------------------------------------------------
	//Parameters: -
	//-------------------------------------------------------------------------------------------------
	//Returns	: -
	//=================================================================================================

	void spawnEnemies( );
	//=================================================================================================						
	//Purpose	: Checks if there is another wave to spawn enemies
	//-------------------------------------------------------------------------------------------------
	//Parameters: -
	//-------------------------------------------------------------------------------------------------
	//Returns	: -
	//=================================================================================================

	void checkIfShopIsActive( );
	//=================================================================================================						
	//Purpose	: Checks if shop is active
	//-------------------------------------------------------------------------------------------------
	//Parameters: -
	//-------------------------------------------------------------------------------------------------
	//Returns	: -
	//=================================================================================================

	void checkForEnemyBulletCollision( );
	//=================================================================================================						
	//Purpose	: Checks if player got hit by enemy bullet
	//-------------------------------------------------------------------------------------------------
	//Parameters: -
	//-------------------------------------------------------------------------------------------------
	//Returns	: -
	//=================================================================================================

	void moveEnemiesInPosition( const float &deltaTime );
	//=================================================================================================						
	//Purpose	: Enemies spawn off screen, this function periodically makes enemies move into their 
	//			  starting position
	//-------------------------------------------------------------------------------------------------
	//Parameters: -
	//-------------------------------------------------------------------------------------------------
	//Returns	: -
	//=================================================================================================

	void enemyDestroyed( const int &index );
	//=================================================================================================						
	//Purpose	: Destroys enemies, determines if a drop should be spawned and increments score
	//-------------------------------------------------------------------------------------------------
	//Parameters: Enemy index
	//-------------------------------------------------------------------------------------------------
	//Returns	: -
	//=================================================================================================

	void checkIfTankEnemiesAreInPosition( );
	//=================================================================================================						
	//Purpose	: Checks if all tanks are in their position to change their behaviour simultaneously
	//-------------------------------------------------------------------------------------------------
	//Parameters: -
	//-------------------------------------------------------------------------------------------------
	//Returns	: -
	//=================================================================================================

	void checkPlayerCollisions( );
	//=================================================================================================						
	//Purpose	: Checks if an enemy collided with player
	//-------------------------------------------------------------------------------------------------
	//Parameters: -
	//-------------------------------------------------------------------------------------------------
	//Returns	: -
	//=================================================================================================

	void createEnemies( WaveData &waveData );
	//=================================================================================================						
	//Purpose	: Creates enemies
	//-------------------------------------------------------------------------------------------------
	//Parameters: Wave data
	//-------------------------------------------------------------------------------------------------
	//Returns	: -
	//=================================================================================================

	void deleteEnemies( );
	//=================================================================================================						
	//Purpose	: Deletes array of enemies
	//-------------------------------------------------------------------------------------------------
	//Parameters: -
	//-------------------------------------------------------------------------------------------------
	//Returns	: -
	//=================================================================================================

	void drawEnemies( );
	//=================================================================================================						
	//Purpose	: Draws enemies
	//-------------------------------------------------------------------------------------------------
	//Parameters: -
	//-------------------------------------------------------------------------------------------------
	//Returns	: -
	//=================================================================================================

	void updateBullets( const float &deltaTime );
	//=================================================================================================						
	//Purpose	: Updates enemy bullets
	//-------------------------------------------------------------------------------------------------
	//Parameters: Time passed since last frame
	//-------------------------------------------------------------------------------------------------
	//Returns	: -
	//=================================================================================================

	void drawBullets( );
	//=================================================================================================						
	//Purpose	: Draws bullets
	//-------------------------------------------------------------------------------------------------
	//Parameters: -
	//-------------------------------------------------------------------------------------------------
	//Returns	: -
	//=================================================================================================

	void rotateBullets( );
	//=================================================================================================						
	//Purpose	: Rotate bullets to their correct orientation
	//-------------------------------------------------------------------------------------------------
	//Parameters: -
	//-------------------------------------------------------------------------------------------------
	//Returns	: -
	//=================================================================================================

	void setUpAudio( );
	//=================================================================================================						
	//Purpose	: Sets up audio
	//-------------------------------------------------------------------------------------------------
	//Parameters: -
	//-------------------------------------------------------------------------------------------------
	//Returns	: -
	//=================================================================================================

	void playExplosion( );
	//=================================================================================================						
	//Purpose	: Play explosion sound effect
	//-------------------------------------------------------------------------------------------------
	//Parameters: -
	//-------------------------------------------------------------------------------------------------
	//Returns	: -
	//=================================================================================================

	BulletPool *getBulletPool( );
	//=================================================================================================						
	//Purpose	: Return bullet pool pointer
	//-------------------------------------------------------------------------------------------------
	//Parameters: -
	//-------------------------------------------------------------------------------------------------
	//Returns	: Bullet pool pointer
	//=================================================================================================

	void reset( );
	//=================================================================================================						
	//Purpose	: Resets all values and deactivates all bullets
	//-------------------------------------------------------------------------------------------------
	//Parameters: -
	//-------------------------------------------------------------------------------------------------
	//Returns	: -
	//=================================================================================================

};
#endif // !ENEMYHANDLER_H
