//Author: Maciej Dowbor
//Module: MED5148
//Date last accessed: 28/10/2020

#include "Snake.h"

#include <conio.h>
#include <Windows.h>

//Constructor
Snake::Snake()
	:m_speedX(2),
	 m_speedY(1),
	 m_length(1)
{
	m_segments[0].initialize( g_snakeChar, g_snakeStartX, g_snakeStartY, 15 );
}

//Constructor
Snake::Snake( int length, int speed, int snakeColour )
	:m_speedX(speed * 2),
	 m_speedY(speed),
	 m_length(length)
{
	m_segments[0].initialize( g_snakeChar, g_snakeStartX, g_snakeStartY, snakeColour );
}

//Destructor
Snake::~Snake()
{
	delete m_segments;
}

//Checks for players input
void Snake::checkForInput()
{
	//if( GetAsyncKeyState( VK_UP ) & 0x8000 ){
	//	if( m_direction != m_direction::down )
	//	{
	//		m_direction = m_direction::up;
	//	}
	//}
	//
	//if( GetAsyncKeyState( VK_DOWN & 0x8000 ) ){
	//	if( m_direction != m_direction::up )
	//	{
	//		m_direction = m_direction::down;
	//	}
	//}
	//
	//if( GetAsyncKeyState( VK_RIGHT & 0x8000 ) ){
	//	if( m_direction != m_direction::left )
	//	{
	//		m_direction = m_direction::right;
	//	}
	//}
	//
	//if( GetAsyncKeyState( VK_LEFT & 0x8000 ) ){
	//	if( m_direction != m_direction::right )
	//	{
	//		m_direction = m_direction::left;
	//	}
	//}
	
	if( _kbhit() ) //Checks if a key is pressed
	{
		switch( _getch() ) //Compares the pressed key with given options
		{
		case 'w': //Up
		case  72:
			if( m_direction != m_direction::down ) //Makes sure the snake can't instantly change to opposite direction (Game rule)
			{
				m_direction = m_direction::up; //Changes snakes direction to up
			}
			break;

		case 's': //Down
		case  80:
			if( m_direction != m_direction::up ) //Makes sure the snake can't instantly change to opposite direction (Game rule)
			{
				m_direction = m_direction::down; //Changes snakes direction to down
			}
			break;

		case 'd': //Right
		case  77:
			if( m_direction != m_direction::left ) //Makes sure the snake can't instantly change to opposite direction (Game rule)
			{
				m_direction = m_direction::right; //Changes snakes direction to right
			}
			break;

		case 'a': //Left
		case  75:
			if( m_direction != m_direction::right ) //Makes sure the snake can't instantly change to opposite direction (Game rule)
			{
				m_direction = m_direction::left; //Changes snakes direction to left
			}
			break;

		default:
			
			break;
		}
	}
}

//Moves the snake
void Snake::movement()
{
	switch( m_direction )
	{
	case m_direction::up: //Up
		m_segments[0].setY( m_segments[0].getY() - m_speedY ); //Moves the snake up
		break;

	case m_direction::down: //Down
		m_segments[0].setY( m_segments[0].getY() + m_speedY ); //Moves the snake down
		break;

	case m_direction::left: //Left
		m_segments[0].setX( m_segments[0].getX() - m_speedX ); //Moves the snake left
		break;

	case m_direction::right: //Right
		m_segments[0].setX( m_segments[0].getX() + m_speedX ); //Moves the snake right
		break;

	default:
		break;
	}
}

//Logic when collision occurs
void Snake::collisionHappened()
{
	m_segments[0].setPosition( m_segments[1].getVector2() ); //Sets snakes head position to its previous position
	m_direction = m_direction::idle; //Changes snakes direction to idle
	g_gameState = GameState::defeat; //Changes the game state to defeat
}

//Collision detection
bool Snake::detectCollision( int collisionType, int collisionX, int collisionY )
{
	int x, y;
	x = m_segments[0].getX(); //Stores snakes head position
	y = m_segments[0].getY();

	switch( collisionType ) //Switches between types of collision specified
	{
	case 0:
		if( x <= collisionX ) 
		{
			return true;
		}
		else { return false; }
		break;

	case 1:
		if( y <= collisionY )
		{
			return true;
		}
		else { return false; }
		break;

	case 2:
		if( x >= collisionX )
		{
			return true;
		}
		else { return false; }
		break;

	case 3:
		if( y >= collisionY )
		{
			return true;
		}
		else { return false; }
		break;

	case 4:
		if( x == collisionX && y == collisionY )
		{
			return true;
		}
		else{ return false; }
		break;

	default:
		return false;
	}
}

//Collisions with the border
void Snake::borderCollision()
{
	//Border collision
	if(
		detectCollision( 1, 0, g_borderOriginY ) || //Top border
		detectCollision( 3, 0, g_borderCollBottom ) || //Bottom border
		detectCollision( 0, g_borderOriginX, 0 ) || //Left border
		detectCollision( 2, g_borderCollRight, 0 )     //Right border
		)
	{
		collisionHappened(); 
	}
}

//Collision with the fruit
bool Snake::fruitCollision( Vector2& positionVector )
{
	if( detectCollision( 4, positionVector.x, positionVector.y ) )
	{
		increaseLength(); //Increases snakes length

		return true;
	}
	else
	{
		return false;
	}
}

//Collisions with snakes segments
void Snake::snakeCollision()
{
	for( int i = 1; i < m_length; i++ ) //Loops based on snakes length
	{
		if( detectCollision( 4, m_segments[i].getX(), m_segments[i].getY() ) )
		{
			collisionHappened();
		}
	}
}

//Increase snakes length
void Snake::increaseLength()
{
	m_length++;
}

//Update snakes tail positions
void Snake::updateTailPositions()
{
	int k;

	for( int i = m_length; i >= 1; i-- ) //Loops based on snakes length
	{
		k = i - 1;
		m_segments[i].setPosition( m_segments[k].getVector2() ); //Moves current segment position up
	}
}

//Resets snakes vars to default
void Snake::resetVars()
{
	m_length = 1;
	m_direction = m_direction::idle;
	m_segments[0].setPosition( g_snakeStartX, g_snakeStartY );
}

//Get snake length
int Snake::getSnakeLength()
{
	return m_length;
}

//Get snake segment position
Vector2 Snake::getPosition( int& i )
{
	return m_segments[i].getVector2();
}

//Erase last segment
void Snake::erase()
{
	m_segments[m_length].erase();
}


//Draw snake
void Snake::draw()
{
	m_segments[0].draw(); //Draws snakes head
	if( m_length > 1 )	//Checks if the snake is longer than one 
	{
		drawChar( 'o', m_segments[1].getVector2(), 2 ); //Draws snakes tail as different char
	}

	updateTailPositions(); //Updates tail positions
}