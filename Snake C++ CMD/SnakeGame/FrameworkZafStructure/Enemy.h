#ifndef ENEMY_H
#define ENEMY_H

#include "CharObject.h"
#include "Vector2.h"

class EnemySnake : public CharObject
{
private:
	int m_length;
	int m_speedX;
	int m_speedY;
	int m_distanceToTarget;
	int m_playerLength = 100;


	int x, y;
	int posX, posY;
	int tempPosX, tempPosY;
	int targetX, targetY;

	CharObject m_segments;

	Vector2 m_enemyPosition[1000];
	Vector2 m_playerPosition[1000];

	enum class Direction { idle, up, down, left, right };
	Direction dirToGoX, dirToGoY, currentDir, prevDirX, prevDirY;
	Direction m_direction[1000];
	Direction m_prevDirectionX = Direction::idle;
	Direction m_prevDirectionY = Direction::idle;

public:
	void initialize( int speed, int length );

	//void playerCollisions();
	//void calcPositions();
	void findPath( Vector2 target );
	void findPathv2( Vector2 target );
	//void findPathv3( Vector2 target );

	void movement();
	void draw();
	void erase();


	void getPlayerPosition( int i, Vector2 position );
	void getPlayerLength( int value );
};

#endif // !ENEMY_H
