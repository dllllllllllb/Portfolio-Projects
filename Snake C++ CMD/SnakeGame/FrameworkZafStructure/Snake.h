//Author: Maciej Dowbor
//Module: MED5148
//Date last accessed: 28/10/2020

#ifndef SNAKE_H
#define SNAKE_H

#include "CharObject.h"

//=============================================================
// Class Name   : Snake
//-------------------------------------------------------------
// Purpose      : Player controlled object
//-------------------------------------------------------------
// Used in      : Game.cpp
//				  Game.h
//				  Snake.cpp
//=============================================================
class Snake
{
private:
	//vars
	int m_speedY; //Snakes speed in Y axis
	int m_speedX; //Snakes speed in X axis
	int m_length; //Snakes length

	CharObject m_segments[200]; //Snakes segments
	

	enum  class m_direction { idle, up, down, left, right }; //Directions in which the snake can move
	m_direction m_direction = m_direction::idle;			 //Initial direction

	//Functions

	//========================================================
	// Function Name	: collisionHappened()
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: Call logic after collision happened
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	void collisionHappened();

	//========================================================
	// Function Name	: detectCollision()
	//--------------------------------------------------------
	// Parameters		: Collision type
	//					  X coordinate of where collision happened
	//					  Y coordinate of where collision happened			  
	//--------------------------------------------------------
	// Purpose			: Detect collisions
	//--------------------------------------------------------
	// Returns			: True/False
	//========================================================
	bool detectCollision( int collisionType, int collisionX, int collisionY );

public:

	//========================================================
	// Function Name	: Snake()
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: Default Snake constructor
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	Snake();

	//========================================================
	// Function Name	: Snake()
	//--------------------------------------------------------
	// Parameters		: Snakes starting length
	//					  Snakes speed
	//					  Snakes color
	//--------------------------------------------------------
	// Purpose			: Default CharObject constructor
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	Snake( int length, int speed, int snakeColour );

	//========================================================
	// Function Name	: ~Snake()
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: Snake destructor
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	~Snake();

	//========================================================
	// Function Name	: checkForInput()
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: Detects player input
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	void checkForInput();

	//========================================================
	// Function Name	: movement()
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: Move the snake
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	void movement();

	//========================================================
	// Function Name	: borderCollision()
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: Checks for border collisions
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	void borderCollision();

	//========================================================
	// Function Name	: fruitCollision()
	//--------------------------------------------------------
	// Parameters		: Fruits position as Vector2
	//--------------------------------------------------------
	// Purpose			: Check for collision with the fruit
	//--------------------------------------------------------
	// Returns			: True/False
	//========================================================
	bool fruitCollision( Vector2& positionVector );

	//========================================================
	// Function Name	: snakeCollision()
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: Detects collision with itself
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	void snakeCollision();

	//========================================================
	// Function Name	: increaseLenght()
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: Increase snakes length
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	void increaseLength();

	//========================================================
	// Function Name	: updateTailPositions
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: Update snakes tail positions
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	void updateTailPositions();

	//========================================================
	// Function Name	: resetVars()
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: Resets snakes variables to default
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	void resetVars();
	
	//========================================================
	// Function Name	: getSnakeLength()
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: Returns snakes length
	//--------------------------------------------------------
	// Returns			: Snakes length as int
	//========================================================
	int getSnakeLength();

	//========================================================
	// Function Name	: getPosition()
	//--------------------------------------------------------
	// Parameters		: Snakes segment number
	//--------------------------------------------------------
	// Purpose			: Returns position of snakes segment
	//--------------------------------------------------------
	// Returns			: Snakes segment position as Vector2
	//========================================================
	Vector2 getPosition(int& i);

	//========================================================
	// Function Name	: draw()
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: Draws the snake
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	void draw();

	//========================================================
	// Function Name	: erase()
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: erases last snake segment
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	void erase();
	
};
#endif