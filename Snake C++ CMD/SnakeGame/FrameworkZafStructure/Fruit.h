//Author: Maciej Dowbor
//Module: MED5148
//Date last accessed: 28/10/2020

#ifndef FRUIT_H
#define FRUIT_H
#include "CharObject.h"

//=============================================================
// Class Name   : Fruit
//-------------------------------------------------------------
// Purpose      : Spawn fruit in a random position within border
//-------------------------------------------------------------
// Used in      : fruit.cpp
//				  Game.h
//				  Game.cpp
//=============================================================
class Fruit : public CharObject
{
private:

	Vector2 m_snakePositions[1000]; //Stores snake positions as Vector2 (see Vector2.h/cpp)
									//Used to make sure fruit won't spawn on top of snake
	int m_snakeLenght; //Stores snakes length

	//========================================================
	// Function Name	: genRandPosition()
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: Generate random x and y coordinates
	//					  and sets them as fruits position
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	void genRandPosition();

public:
	//========================================================
    // Function Name	: Fruit()
    //--------------------------------------------------------
    // Parameters		: -
    //--------------------------------------------------------
    // Purpose			: Fruit constructor
    //--------------------------------------------------------
    // Returns			: -
    //========================================================
	Fruit();

	//========================================================
	// Function Name	: ~Fruit()
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: Fruit destructor
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	~Fruit();

	//========================================================
	// Function Name	: spawnFruit()
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: Spawns fruit
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	void spawnFruit();

	//========================================================
	// Function Name	: checkForSnakeCol()
	//--------------------------------------------------------
	// Parameters		: Snakes length
	//--------------------------------------------------------
	// Purpose			: Checks if the fruit has the same
	//					  position as any snake element
	//--------------------------------------------------------
	// Returns			: True/false
	//========================================================
	bool checkForSnakeCol( int snakeLength);

	//========================================================
	// Function Name	: getSnakeLength()
	//--------------------------------------------------------
	// Parameters		: Snakes length
	//--------------------------------------------------------
	// Purpose			: Get snakes length
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	void getSnakeLength( int snakeLength );

	//========================================================
	// Function Name	: saveSnakePos
	//--------------------------------------------------------
	// Parameters		: int to determine position in array
	//					  where the snakes position will be 
	//					  saved
	//					  Snakes position
	//--------------------------------------------------------
	// Purpose			: Get and store snakes positions
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	void saveSnakePos( int i, Vector2 pos);
};

#endif
