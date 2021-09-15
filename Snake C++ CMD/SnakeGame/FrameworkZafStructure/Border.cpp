//Author: Maciej Dowbor
//Module: MED5148
//Date last accessed: 28/10/2020

#include "Border.h"

//Constructor
Border::Border()
{
	m_char = g_borderChar;
	m_position.setPosition( 0, 0 );
	setTextAttribute( 13 );
}

//Destructor
Border::~Border()
{

}

//Draw Border
void Border::drawBorder()
{
	//Top border
	for( int i = 0; i < g_borderSizeX; i++ ) //Loops based on the size of the border
	{
		setPosition( g_borderOriginX + i, g_borderOriginY ); //x position of the border is increased by the i value and set as a Vector2 (see Vector2.h/cpp)
		draw(); //Draws a border segment at the position set above
	}
		//Comments apply to Bottom border, Left border and Right border

	//Bottom border
	for( int i = 0; i < g_borderSizeX + 1; i++ )
	{
		setPosition( g_borderOriginX + i, g_borderCollBottom );
		draw();
	}

	//Left border
	for( int i = 0; i < borderSizeY; i++ )
	{
		setPosition( g_borderOriginX, g_borderOriginY + i );
		draw();
	}

	//Right border
	for( int i = 0; i < borderSizeY; i++ )
	{
		setPosition( g_borderCollRight, g_borderOriginY + i );
		draw();
	}
}
