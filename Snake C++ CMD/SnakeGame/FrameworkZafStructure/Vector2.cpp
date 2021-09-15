//Author: Maciej Dowbor
//Module: MED5148
//Date last accessed: 28/10/2020

#include "Vector2.h"

//Constructor
Vector2::Vector2()
	:x(0),
	 y(0)
{
}

//Get x coordinate
int Vector2::getX() const
{
	return x;
}

//Get y coordinate
int Vector2::getY() const
{
	return y;
}

//Set x and y coordinates
void Vector2::setPosition( int xValue, int yValue )
{
	x = xValue;
	y = yValue;
}