//Author: Maciej Dowbor
//Module: MED5148
//Date last accessed: 28/10/2020

#include "CharObject.h"

//Constructor
CharObject::CharObject()
	:m_char('a'),
	m_textAttribute(15)

{
	setPosition( 0, 0 );
}

//Constructor
CharObject::CharObject( char objChar, int x, int y, int textAttribute )
	:m_char(objChar),
	 m_textAttribute( textAttribute )
{
	setPosition( x, y );
}

//Destructor
CharObject::~CharObject()
{

}

//Draw
void CharObject::draw()
{
	drawChar( m_char, m_position, m_textAttribute ); //Draws a char in given position in given color (see Helpers.h/cpp)
}

//Erase
void CharObject::erase()
{
	drawChar( ' ', m_position, 15 ); //Draws an empty space in given position (see Helpers.h/cpp)
}

//Set position using Vector2
void CharObject::setPosition( Vector2 position ) 
{
	m_position = position; //Sets position to given position, stored as Vector2 (see Vector2.h/cpp)
}

//Get position
Vector2 CharObject::getVector2()
{
	return m_position; //Returns position as Vector2 (see Vector2.h/cpp)
}

//Get x coordinate
int CharObject::getX() const
{
	return m_position.x; //Returns positions x coordinate as int
}

//Get y coordinate
int CharObject::getY() const
{
	return m_position.y; //Returns positions y coordinate as int
}

//Set position using x and y coordinates
void CharObject::setPosition( int xValue, int yValue )
{
	m_position.x = xValue; //Sets positions x coordinate to given value
	m_position.y = yValue; //Sets positions y coordinate to given value
}

//Initialize all class values
void CharObject::initialize( char objChar, int x, int y, int textAttribute )
{
	m_char = objChar; //Sets char
	m_textAttribute = textAttribute; //Sets char color
	setPosition( x, y ); //Sets position
}

//Set char color
void CharObject::setTextAttribute( int textAttribute )
{
	m_textAttribute = textAttribute; //Sets char color
}

//Set positions x coordinate
void CharObject::setX( int value )
{
	m_position.x = value; //Sets positions x coordinate
}

//Set positions y coordinate
void CharObject::setY( int value )
{
	m_position.y = value; //Sets positions y coordinate
}