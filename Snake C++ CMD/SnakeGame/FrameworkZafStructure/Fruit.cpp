//Author: Maciej Dowbor
//Module: MED5148
//Date last accessed: 28/10/2020

#include "Fruit.h"
#include <cstdlib>

//Generate random position
void Fruit::genRandPosition()
{
	int x, y; //Temp variables

	x = rand() % ( g_borderSizeX - 2 ) + g_borderOriginX + 1; //Generates random x value within given range considering border
	y = rand() % ( borderSizeY - 2 ) + g_borderOriginY + 1; //Generates random y value within given range considering border

	//Snake starts at odd X value and moves horizontally by 2 spaces
	//This makes sure that the fruit spawns in a position the snake can collide with
	//Checks if the x value is even, if true, it will decrease its value by 1
	//This works because the fruit cant spawn on x < 1, so the fruit wont spawn on either left/right border
	if( x % 2 == 0 )
	{
		x--;
	}	

	setPosition( x, y ); //Sets fruits position
}

//Constructor
Fruit::Fruit()
	:m_snakeLenght(0)
{
	m_char = g_fruitChar; //Sets fruits char
	m_position.setPosition( 0, 0 ); //Sets fruits position
	setTextAttribute( 12 ); //Sets fruit color 12 == red
}

//Destructor
Fruit::~Fruit()
{
	delete m_snakePositions;
}

//Spawn fruit
void Fruit::spawnFruit()
{
	genRandPosition(); //Generates random position

	if( checkForSnakeCol( m_snakeLenght ) ) //Checks for collision with snake elements
	{ 
		spawnFruit(); //If the fruit collides with the snake on spawn, the function is ran again to generate new spawn position and 
				      //check for collisions
	}
	else
	{
		draw(); //Draws the fruit
	}
}

//Checks for collisions with the snake
bool Fruit::checkForSnakeCol( int snakeLength )
{
	for( int i = 0; i < snakeLength; i++ ) //Loops based on snakes length
	{
		if( m_position.x == m_snakePositions[i].x &&  //Compares x and y values of fruit and a snake segment each loop
			m_position.y == m_snakePositions[i].y )
		{
			return true;
			break;
		}
	}

	return false;
}

//Gets snakes length
void Fruit::getSnakeLength( int snakeLength )
{
	m_snakeLenght = snakeLength; //Sets snakes length
}

void Fruit::saveSnakePos( int i, Vector2 pos )
{
	m_snakePositions[i] = pos; //Saves snakes position as Vector2 (see Vector2.h/cpp)
}
