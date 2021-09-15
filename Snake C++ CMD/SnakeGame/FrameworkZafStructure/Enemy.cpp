#include "Enemy.h"
#include <cmath>
#include "Vector2.h"

void EnemySnake::initialize( int speed, int length )
{
	m_segments.initialize( enemyChar, 21, 9 );
	m_speedX = speed * 2;  //To vaguely nullify CMD font scaling
	m_speedY = speed;
	m_length = length;
}

void EnemySnake::findPath( Vector2 target )
{
	int x, y;
	int posX, posY;
	int tempPosX, tempPosY;
	Direction dirToGo;

	//Current AI position
	posX = m_segments.getX();
	posY = m_segments.getY();

	//Min number of moves AI has to make in x / y direction
	x = ( target.x - posX ) / 2; //Snake moves 2 places at once on x axis hence /2
	y = target.y - posY;

	if( x > 0 ) //Determines which direction to go
	{
		dirToGo = Direction::right;
	}
	else
	{
		dirToGo = Direction::left;
	}

	x = abs( x );
	for( int i = 0; i < x; i++ ) //Assigns direction to go to an array
	{
		m_direction[i] = dirToGo;
	}

	if( y > 0 ) //Determines which direction to go
	{
		dirToGo = Direction::down;
	}
	else
	{
		dirToGo = Direction::up;
	}

	y = abs( y );
	m_distanceToTarget = x + y;
	for( int i = x; i < m_distanceToTarget; i++ ) //Assigns direction to go to an array
	{
		m_direction[i] = dirToGo;
	}

	//Predicts snake movement
	for( int i = 0; i < m_distanceToTarget; i++ ) //
	{
		switch( m_direction[i] )
		{
		case Direction::up:
			posY -= m_speedY;
			break;

		case Direction::down:
			posY += m_speedY;
			break;

		case Direction::left:
			posX -= m_speedX;
			break;

		case Direction::right:
			posX += m_speedX;
			break;
		}

		m_enemyPosition[i].setPosition( posX, posY );
		for( int k = 0; k < m_playerLength; k++ )
		{
			if( m_enemyPosition[i].x == m_playerPosition[k].x &&
				m_enemyPosition[i].y == m_playerPosition[k].y )
			{
				switch( m_direction[i] )
				{
				case Direction::up:

					//Resets position
					posY += m_speedY;

					//Store positions
					tempPosX = posX;
					tempPosY = posY;

					//Check left
					posX -= m_speedX;
					m_enemyPosition[i].setPosition( posX, posY );

					for( int j = 0; j < m_playerLength; j++ )
					{
						if( m_enemyPosition[i].x == m_playerPosition[j].x &&
							m_enemyPosition[i].y == m_playerPosition[j].y )
						{
							//Check right
							posX = tempPosX;
							posX += m_speedX;
							m_enemyPosition[i].setPosition( posX, posY );
							for( int z = 0; z < m_playerLength; z++ )
							{
								if( m_enemyPosition[i].x == m_playerPosition[z].x &&
									m_enemyPosition[i].y == m_playerPosition[z].y )
								{
									break;
								}
								else
								{
									m_direction[i] = Direction::right;
								}
							}
						}
						else
						{
							m_direction[i] = Direction::left;
						}
					}
					break;

				case Direction::down:

					//Resets position
					posY -= m_speedY;

					//Store positions
					tempPosX = posX;
					tempPosY = posY;

					//Check left
					posX -= m_speedX;
					m_enemyPosition[i].setPosition( posX, posY );

					for( int j = 0; j < m_playerLength; j++ )
					{
						if( m_enemyPosition[i].x == m_playerPosition[j].x &&
							m_enemyPosition[i].y == m_playerPosition[j].y )
						{
							//Check right
							posX = tempPosX;
							posX += m_speedX;
							m_enemyPosition[i].setPosition( posX, posY );
							for( int z = 0; z < m_playerLength; z++ )
							{
								if( m_enemyPosition[i].x == m_playerPosition[z].x &&
									m_enemyPosition[i].y == m_playerPosition[z].y )
								{
									break;
								}
								else
								{
									m_direction[i] = Direction::right;
								}
							}
						}
						else
						{
							m_direction[i] = Direction::left;
						}
					}
					break;

				case Direction::left:

					//Resets position
					posX += m_speedX;

					//Store positions
					tempPosX = posX;
					tempPosY = posY;

					//Check up
					posY -= m_speedY;
					m_enemyPosition[i].setPosition( posX, posY );

					for( int j = 0; j < m_playerLength; j++ )
					{
						if( m_enemyPosition[i].x == m_playerPosition[j].x &&
							m_enemyPosition[i].y == m_playerPosition[j].y )
						{
							//Check down
							posX = tempPosX;
							posX += m_speedX;
							m_enemyPosition[i].setPosition( posX, posY );
							for( int z = 0; z < m_playerLength; z++ )
							{
								if( m_enemyPosition[i].x == m_playerPosition[z].x &&
									m_enemyPosition[i].y == m_playerPosition[z].y )
								{
									break;
								}
								else
								{
									m_direction[i] = Direction::down;
								}
							}
						}
						else
						{
							m_direction[i] = Direction::up;
						}
					}
					break;

				case Direction::right:

					//Resets position
					posX -= m_speedX;

					//Store positions
					tempPosX = posX;
					tempPosY = posY;

					//Check up
					posY -= m_speedY;
					m_enemyPosition[i].setPosition( posX, posY );

					for( int j = 0; j < m_playerLength; j++ )
					{
						if( m_enemyPosition[i].x == m_playerPosition[j].x &&
							m_enemyPosition[i].y == m_playerPosition[j].y )
						{
							//Check down
							posX = tempPosX;
							posX += m_speedX;
							m_enemyPosition[i].setPosition( posX, posY );
							for( int z = 0; z < m_playerLength; z++ )
							{
								if( m_enemyPosition[i].x == m_playerPosition[z].x &&
									m_enemyPosition[i].y == m_playerPosition[z].y )
								{
									break;
								}
								else
								{
									m_direction[i] = Direction::down;
								}
							}
						}
						else
						{
							m_direction[i] = Direction::up;
						}
					}
					break;
				}
			}
		}
	}
}

void EnemySnake::movement()
{
	switch( m_direction[0] ){
	case Direction::up:
		m_segments.setY( m_segments.getY() - m_speedY );
		break;

	case Direction::down:
		m_segments.setY( m_segments.getY() + m_speedY );
		break;

	case Direction::left:
		m_segments.setX( m_segments.getX() - m_speedX );
		break;

	case Direction::right:
		m_segments.setX( m_segments.getX() + m_speedX );
		break;
	}
}

void EnemySnake::draw()
{
	m_segments.draw();
}

void EnemySnake::erase()
{
	m_segments.erase();
}
void EnemySnake::getPlayerPosition( int i, Vector2 position )
{
	m_playerPosition[i] = position;
}
void EnemySnake::getPlayerLength( int value )
{
	m_playerLength = value;
}

void EnemySnake::findPathv2( Vector2 target )
{
	int x, y;
	int posX, posY;
	int tempPosX, tempPosY;
	int targetX, targetY;
	Direction dirToGoX, dirToGoY, currentDir, prevDirX, prevDirY;
	int i = 0;

	//Current AI position
	posX = m_segments.getX();
	posY = m_segments.getY();

	//Get target position
	targetX = target.x;
	targetY = target.y;

	//Min number of moves AI has to make in x / y direction
	x = ( target.x - posX ) / 2; //Snake moves 2 places at once on x axis hence /2
	y = target.y - posY;

	if( x > 0 ) //Determines which direction to go
	{
		dirToGoX = Direction::right;
	}
	else
	{
		dirToGoX = Direction::left;
	}

	if( y > 0 ) //Determines which direction to go
	{
		dirToGoY = Direction::down;
	}
	else
	{
		dirToGoY = Direction::up;
	}

	x = abs( x );
	y = abs( y );
	m_distanceToTarget = x + y;

	//Predict movement along Y axis
	while( posY != targetY )
	{
		currentDir = dirToGoY;

		//Stores position before move
		tempPosX = posX;
		tempPosY = posY;

		switch( currentDir )
		{
		case EnemySnake::Direction::up:

			if( m_prevDirectionY == Direction::down )
			{
				switch( m_prevDirectionX )
				{
				case EnemySnake::Direction::right:
					//Check right
					posX = tempPosX; //resets positions
					posY = tempPosY;

					posX += m_speedX;
					m_enemyPosition[i].setPosition( posX, posY );

					for( int z = 0; z < m_playerLength; z++ )
					{
						if( m_enemyPosition[i].x == m_playerPosition[z].x &&
							m_enemyPosition[i].y == m_playerPosition[z].y )
						{
							//Check down
							posX = tempPosX; //resets positions
							posY = tempPosY;

							posY += m_speedY;
							m_enemyPosition[i].setPosition( posX, posY );

							for( int h = 0; h < m_playerLength; h++ )
							{
								if( m_enemyPosition[i].x == m_playerPosition[h].x &&
									m_enemyPosition[i].y == m_playerPosition[h].y )
								{
									//enemy cant move == enemy loses
									posX = tempPosX;
									posY = tempPosY;
									m_enemyPosition[i].setPosition( posX, posY );
									m_direction[i] = Direction::idle;
								}
								else
								{
									m_direction[i] = Direction::down;
									m_prevDirectionY = Direction::down;
								}
							}
						}
						else
						{
							m_direction[i] = Direction::right;
							m_prevDirectionX = Direction::right;
						}

						break;
					}

				case EnemySnake::Direction::left:
					//Check left
					posX = tempPosX; //resets positions
					posY = tempPosY;

					posX -= m_speedX;
					m_enemyPosition[i].setPosition( posX, posY );

					for( int z = 0; z < m_playerLength; z++ )
					{
						if( m_enemyPosition[i].x == m_playerPosition[z].x &&
							m_enemyPosition[i].y == m_playerPosition[z].y )
						{
							//Check down
							posX = tempPosX; //resets positions
							posY = tempPosY;

							posY += m_speedY;
							m_enemyPosition[i].setPosition( posX, posY );

							for( int h = 0; h < m_playerLength; h++ )
							{
								if( m_enemyPosition[i].x == m_playerPosition[h].x &&
									m_enemyPosition[i].y == m_playerPosition[h].y )
								{
									//enemy cant move == enemy loses
									posX = tempPosX;
									posY = tempPosY;
									m_enemyPosition[i].setPosition( posX, posY );
									m_direction[i] = Direction::idle;
								}
								else
								{
									m_direction[i] = Direction::down;
									m_prevDirectionY = Direction::down;
								}
							}
						}
						else
						{
							m_direction[i] = Direction::left;
							m_prevDirectionX = Direction::left;
						}

						break;
					}
				}
			}
			else
			{
				posY -= m_speedY;

				m_enemyPosition[i].setPosition( posX, posY );
			}

			for( int k = 0; k < m_playerLength; k++ )
			{
				if( m_enemyPosition[i].x == m_playerPosition[k].x &&
					m_enemyPosition[i].y == m_playerPosition[k].y )
				{
					//Check left
					posX = tempPosX; //resets positions
					posY = tempPosY;

					posX -= m_speedX;
					m_enemyPosition[i].setPosition( posX, posY );

					for( int j = 0; j < m_playerLength; j++ )
					{
						if( m_enemyPosition[i].x == m_playerPosition[j].x &&
							m_enemyPosition[i].y == m_playerPosition[j].y )
						{
							//Check right
							posX = tempPosX; //resets positions
							posY = tempPosY;

							posX += m_speedX;
							m_enemyPosition[i].setPosition( posX, posY );

							for( int z = 0; z < m_playerLength; z++ )
							{
								if( m_enemyPosition[i].x == m_playerPosition[z].x &&
									m_enemyPosition[i].y == m_playerPosition[z].y )
								{
									if( m_prevDirectionY != Direction::up ){
										//Check down
										posX = tempPosX; //resets positions
										posY = tempPosY;

										posY += m_speedY;
										m_enemyPosition[i].setPosition( posX, posY );

										for( int h = 0; h < m_playerLength; h++ )
										{
											if( m_enemyPosition[i].x == m_playerPosition[h].x &&
												m_enemyPosition[i].y == m_playerPosition[h].y )
											{
												//enemy cant move == enemy loses
												posX = tempPosX;
												posY = tempPosY;
												m_enemyPosition[i].setPosition( posX, posY );
												m_direction[i] = Direction::idle;
											}
											else
											{
												m_direction[i] = Direction::down;
												m_prevDirectionY = Direction::down;
											}
										}
									}
									else
									{
										//enemy cant move == enemy loses
										posX = tempPosX;
										posY = tempPosY;
										m_enemyPosition[i].setPosition( posX, posY );
										m_direction[i] = Direction::idle;
									}
									break;
								}
								else
								{
									m_direction[i] = Direction::right;
									m_prevDirectionX = Direction::right;
								}
							}
						}
						else
						{
							m_direction[i] = Direction::left;
							m_prevDirectionX = Direction::left;
						}
					}
				}
				else
				{
					m_direction[i] = Direction::up;
					m_prevDirectionY = Direction::up;
				}
			}

		case EnemySnake::Direction::down:

			if( m_prevDirectionY == Direction::up )
			{
				switch( m_prevDirectionX )
				{
				case EnemySnake::Direction::right:
					//Check right
					posX = tempPosX; //resets positions
					posY = tempPosY;

					posX += m_speedX;
					m_enemyPosition[i].setPosition( posX, posY );

					for( int z = 0; z < m_playerLength; z++ )
					{
						if( m_enemyPosition[i].x == m_playerPosition[z].x &&
							m_enemyPosition[i].y == m_playerPosition[z].y )
						{
							//Check up
							posX = tempPosX; //resets positions
							posY = tempPosY;

							posY -= m_speedY;
							m_enemyPosition[i].setPosition( posX, posY );

							for( int h = 0; h < m_playerLength; h++ )
							{
								if( m_enemyPosition[i].x == m_playerPosition[h].x &&
									m_enemyPosition[i].y == m_playerPosition[h].y )
								{
									//enemy cant move == enemy loses
									posX = tempPosX;
									posY = tempPosY;
									m_enemyPosition[i].setPosition( posX, posY );
									m_direction[i] = Direction::idle;
								}
								else
								{
									m_direction[i] = Direction::up;
									m_prevDirectionY = Direction::up;
								}
							}
						}
						else
						{
							m_direction[i] = Direction::right;
							m_prevDirectionX = Direction::right;
						}

						break;
					}

				case EnemySnake::Direction::left:
					//Check left
					posX = tempPosX; //resets positions
					posY = tempPosY;

					posX -= m_speedX;
					m_enemyPosition[i].setPosition( posX, posY );

					for( int z = 0; z < m_playerLength; z++ )
					{
						if( m_enemyPosition[i].x == m_playerPosition[z].x &&
							m_enemyPosition[i].y == m_playerPosition[z].y )
						{
							//Check up
							posX = tempPosX; //resets positions
							posY = tempPosY;

							posY -= m_speedY;
							m_enemyPosition[i].setPosition( posX, posY );

							for( int h = 0; h < m_playerLength; h++ )
							{
								if( m_enemyPosition[i].x == m_playerPosition[h].x &&
									m_enemyPosition[i].y == m_playerPosition[h].y )
								{
									//enemy cant move == enemy loses
									posX = tempPosX;
									posY = tempPosY;
									m_enemyPosition[i].setPosition( posX, posY );
									m_direction[i] = Direction::idle;
								}
								else
								{
									m_direction[i] = Direction::up;
									m_prevDirectionY = Direction::up;
								}
							}
						}
						else
						{
							m_direction[i] = Direction::left;
							m_prevDirectionX = Direction::left;
						}

						break;
					}
				}
			}
			else
			{
				posY += m_speedY;

				m_enemyPosition[i].setPosition( posX, posY );
			}

			for( int k = 0; k < m_playerLength; k++ )
			{
				if( m_enemyPosition[i].x == m_playerPosition[k].x &&
					m_enemyPosition[i].y == m_playerPosition[k].y )
				{
					//Check left
					posX = tempPosX; //resets positions
					posY = tempPosY;

					posX -= m_speedX;
					m_enemyPosition[i].setPosition( posX, posY );

					for( int j = 0; j < m_playerLength; j++ )
					{
						if( m_enemyPosition[i].x == m_playerPosition[j].x &&
							m_enemyPosition[i].y == m_playerPosition[j].y )
						{
							//Check right
							posX = tempPosX; //resets positions
							posY = tempPosY;

							posX += m_speedX;
							m_enemyPosition[i].setPosition( posX, posY );

							for( int z = 0; z < m_playerLength; z++ )
							{
								if( m_enemyPosition[i].x == m_playerPosition[z].x &&
									m_enemyPosition[i].y == m_playerPosition[z].y )
								{
									if( m_prevDirectionY != Direction::down ){
										//Check down
										posX = tempPosX; //resets positions
										posY = tempPosY;

										posY += m_speedY;
										m_enemyPosition[i].setPosition( posX, posY );

										for( int h = 0; h < m_playerLength; h++ )
										{
											if( m_enemyPosition[i].x == m_playerPosition[h].x &&
												m_enemyPosition[i].y == m_playerPosition[h].y )
											{
												//enemy cant move == enemy loses
												posX = tempPosX;
												posY = tempPosY;
												m_enemyPosition[i].setPosition( posX, posY );
												m_direction[i] = Direction::idle;
											}
											else
											{
												m_direction[i] = Direction::down;
												m_prevDirectionY = Direction::down;
											}
										}
									}
									else
									{
										//enemy cant move == enemy loses
										posX = tempPosX;
										posY = tempPosY;
										m_enemyPosition[i].setPosition( posX, posY );
										m_direction[i] = Direction::idle;
									}
									break;
								}
								else
								{
									m_direction[i] = Direction::right;
									m_prevDirectionX = Direction::right;
								}
							}
						}
						else
						{
							m_direction[i] = Direction::left;
							m_prevDirectionX = Direction::left;
						}
					}
				}
				else
				{
					m_direction[i] = Direction::up;
					m_prevDirectionY = Direction::up;
				}
			}
		default:
			break;
		}

		i++;
		if( i > 500 ){
			break;
		}
	}

	//Predict movement along X axis
	while( posX != targetX )
	{
		currentDir = dirToGoX;

		//Stores position before move
		tempPosX = posX;
		tempPosY = posY;

		switch( currentDir )
		{
		case EnemySnake::Direction::left:

			if( m_prevDirectionX == Direction::right )
			{
				switch( m_prevDirectionY )
				{
				case EnemySnake::Direction::up:
					//Check up
					posX = tempPosX; //resets positions
					posY = tempPosY;

					posY -= m_speedY;
					m_enemyPosition[i].setPosition( posX, posY );

					for( int z = 0; z < m_playerLength; z++ )
					{
						if( m_enemyPosition[i].x == m_playerPosition[z].x &&
							m_enemyPosition[i].y == m_playerPosition[z].y )
						{
							//Check right
							posX = tempPosX; //resets positions
							posY = tempPosY;

							posX += m_speedX;
							m_enemyPosition[i].setPosition( posX, posY );

							for( int h = 0; h < m_playerLength; h++ )
							{
								if( m_enemyPosition[i].x == m_playerPosition[h].x &&
									m_enemyPosition[i].y == m_playerPosition[h].y )
								{
									//enemy cant move == enemy loses
									posX = tempPosX;
									posY = tempPosY;
									m_enemyPosition[i].setPosition( posX, posY );
									m_direction[i] = Direction::idle;
								}
								else
								{
									m_direction[i] = Direction::right;
									m_prevDirectionX = Direction::right;
								}
							}
						}
						else
						{
							m_direction[i] = Direction::up;
							m_prevDirectionY = Direction::up;
						}

						break;
					}

				case EnemySnake::Direction::down:
					//Check down
					posX = tempPosX; //resets positions
					posY = tempPosY;

					posY += m_speedY;
					m_enemyPosition[i].setPosition( posX, posY );

					for( int z = 0; z < m_playerLength; z++ )
					{
						if( m_enemyPosition[i].x == m_playerPosition[z].x &&
							m_enemyPosition[i].y == m_playerPosition[z].y )
						{
							//Check right
							posX = tempPosX; //resets positions
							posY = tempPosY;

							posX += m_speedX;
							m_enemyPosition[i].setPosition( posX, posY );

							for( int h = 0; h < m_playerLength; h++ )
							{
								if( m_enemyPosition[i].x == m_playerPosition[h].x &&
									m_enemyPosition[i].y == m_playerPosition[h].y )
								{
									//enemy cant move == enemy loses
									posX = tempPosX;
									posY = tempPosY;
									m_enemyPosition[i].setPosition( posX, posY );
									m_direction[i] = Direction::idle;
								}
								else
								{
									m_direction[i] = Direction::right;
									m_prevDirectionX = Direction::right;
								}
							}
						}
						else
						{
							m_direction[i] = Direction::down;
							m_prevDirectionY = Direction::down;
						}

						break;
					}
				}
			}
			else
			{
				posX -= m_speedX;

				m_enemyPosition[i].setPosition( posX, posY );
			}

			for( int k = 0; k < m_playerLength; k++ )
			{
				if( m_enemyPosition[i].x == m_playerPosition[k].x &&
					m_enemyPosition[i].y == m_playerPosition[k].y )
				{
					//Check up
					posX = tempPosX; //resets positions
					posY = tempPosY;

					posY -= m_speedY;
					m_enemyPosition[i].setPosition( posX, posY );

					for( int j = 0; j < m_playerLength; j++ )
					{
						if( m_enemyPosition[i].x == m_playerPosition[j].x &&
							m_enemyPosition[i].y == m_playerPosition[j].y )
						{
							//Check down
							posX = tempPosX; //resets positions
							posY = tempPosY;

							posY += m_speedY;
							m_enemyPosition[i].setPosition( posX, posY );

							for( int z = 0; z < m_playerLength; z++ )
							{
								if( m_enemyPosition[i].x == m_playerPosition[z].x &&
									m_enemyPosition[i].y == m_playerPosition[z].y )
								{
									if( m_prevDirectionY != Direction::left ){
										//Check right
										posX = tempPosX; //resets positions
										posY = tempPosY;

										posX += m_speedX;
										m_enemyPosition[i].setPosition( posX, posY );

										for( int h = 0; h < m_playerLength; h++ )
										{
											if( m_enemyPosition[i].x == m_playerPosition[h].x &&
												m_enemyPosition[i].y == m_playerPosition[h].y )
											{
												//enemy cant move == enemy loses
												posX = tempPosX;
												posY = tempPosY;
												m_enemyPosition[i].setPosition( posX, posY );
												m_direction[i] = Direction::idle;
											}
											else
											{
												m_direction[i] = Direction::right;
												m_prevDirectionX = Direction::right;
											}
										}
									}
									else
									{
										//enemy cant move == enemy loses
										posX = tempPosX;
										posY = tempPosY;
										m_enemyPosition[i].setPosition( posX, posY );
										m_direction[i] = Direction::idle;
									}
									break;
								}
								else
								{
									m_direction[i] = Direction::down;
									m_prevDirectionY = Direction::down;
								}
							}
						}
						else
						{
							m_direction[i] = Direction::up;
							m_prevDirectionY = Direction::up;
						}
					}
				}
				else
				{
					m_direction[i] = Direction::left;
					m_prevDirectionX = Direction::left;
				}
			}
			break;

		case EnemySnake::Direction::right: //WORKING ON THIS NOW BTW

			if( m_prevDirectionX == Direction::left )
			{
				switch( m_prevDirectionY )
				{
				case EnemySnake::Direction::up:
					//Check up
					posX = tempPosX; //resets positions
					posY = tempPosY;

					posY -= m_speedY;
					m_enemyPosition[i].setPosition( posX, posY );

					for( int z = 0; z < m_playerLength; z++ )
					{
						if( m_enemyPosition[i].x == m_playerPosition[z].x &&
							m_enemyPosition[i].y == m_playerPosition[z].y )
						{
							//Check left
							posX = tempPosX; //resets positions
							posY = tempPosY;

							posX -= m_speedX;
							m_enemyPosition[i].setPosition( posX, posY );

							for( int h = 0; h < m_playerLength; h++ )
							{
								if( m_enemyPosition[i].x == m_playerPosition[h].x &&
									m_enemyPosition[i].y == m_playerPosition[h].y )
								{
									//enemy cant move == enemy loses
									posX = tempPosX;
									posY = tempPosY;
									m_enemyPosition[i].setPosition( posX, posY );
									m_direction[i] = Direction::idle;
								}
								else
								{
									m_direction[i] = Direction::left;
									m_prevDirectionX = Direction::left;
								}
							}
						}
						else
						{
							m_direction[i] = Direction::up;
							m_prevDirectionY = Direction::up;
						}

						break;
					}

				case EnemySnake::Direction::down:
					//Check down
					posX = tempPosX; //resets positions
					posY = tempPosY;

					posY += m_speedY;
					m_enemyPosition[i].setPosition( posX, posY );

					for( int z = 0; z < m_playerLength; z++ )
					{
						if( m_enemyPosition[i].x == m_playerPosition[z].x &&
							m_enemyPosition[i].y == m_playerPosition[z].y )
						{
							//Check left
							posX = tempPosX; //resets positions
							posY = tempPosY;

							posX -= m_speedX;
							m_enemyPosition[i].setPosition( posX, posY );

							for( int h = 0; h < m_playerLength; h++ )
							{
								if( m_enemyPosition[i].x == m_playerPosition[h].x &&
									m_enemyPosition[i].y == m_playerPosition[h].y )
								{
									//enemy cant move == enemy loses
									posX = tempPosX;
									posY = tempPosY;
									m_enemyPosition[i].setPosition( posX, posY );
									m_direction[i] = Direction::idle;
								}
								else
								{
									m_direction[i] = Direction::left;
									m_prevDirectionX = Direction::left;
								}
							}
						}
						else
						{
							m_direction[i] = Direction::down;
							m_prevDirectionY = Direction::down;
						}

						break;
					}
				}
			}
			else
			{
				posX += m_speedX;

				m_enemyPosition[i].setPosition( posX, posY );
			}

			for( int k = 0; k < m_playerLength; k++ )
			{
				if( m_enemyPosition[i].x == m_playerPosition[k].x &&
					m_enemyPosition[i].y == m_playerPosition[k].y )
				{
					//Check up
					posX = tempPosX; //resets positions
					posY = tempPosY;

					posY -= m_speedY;
					m_enemyPosition[i].setPosition( posX, posY );

					for( int j = 0; j < m_playerLength; j++ )
					{
						if( m_enemyPosition[i].x == m_playerPosition[j].x &&
							m_enemyPosition[i].y == m_playerPosition[j].y )
						{
							//Check down
							posX = tempPosX; //resets positions
							posY = tempPosY;

							posY += m_speedY;
							m_enemyPosition[i].setPosition( posX, posY );

							for( int z = 0; z < m_playerLength; z++ )
							{
								if( m_enemyPosition[i].x == m_playerPosition[z].x &&
									m_enemyPosition[i].y == m_playerPosition[z].y )
								{
									if( m_prevDirectionY != Direction::right ){
										//Check left
										posX = tempPosX; //resets positions
										posY = tempPosY;

										posX -= m_speedX;
										m_enemyPosition[i].setPosition( posX, posY );

										for( int h = 0; h < m_playerLength; h++ )
										{
											if( m_enemyPosition[i].x == m_playerPosition[h].x &&
												m_enemyPosition[i].y == m_playerPosition[h].y )
											{
												//enemy cant move == enemy loses
												posX = tempPosX;
												posY = tempPosY;
												m_enemyPosition[i].setPosition( posX, posY );
												m_direction[i] = Direction::idle;
											}
											else
											{
												m_direction[i] = Direction::left;
												m_prevDirectionX = Direction::left;
											}
										}
									}
									else
									{
										//enemy cant move == enemy loses
										posX = tempPosX;
										posY = tempPosY;
										m_enemyPosition[i].setPosition( posX, posY );
										m_direction[i] = Direction::idle;
									}
									break;
								}
								else
								{
									m_direction[i] = Direction::down;
									m_prevDirectionY = Direction::down;
								}
							}
						}
						else
						{
							m_direction[i] = Direction::up;
							m_prevDirectionY = Direction::up;
						}
					}
				}
				else
				{
					m_direction[i] = Direction::right;
					m_prevDirectionX = Direction::right;
				}
			}
			break;
		default:
			break;
		}

		i++;
		if( i > 998 ){
			break;
		}
	}
}


