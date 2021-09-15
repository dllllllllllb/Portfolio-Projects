//Author: Zafar Qamar & Maciej Dowbor
//Module: MED5148
//Date last accessed: 28/10/2020

#ifndef HELPERS_H
#define HELPERS_H

#include "Vector2.h"

	//========================================================
	// Function Name	: drawChar()
	//--------------------------------------------------------
	// Parameters		: Char to draw
	//					  Position
	//					  Char color
	//--------------------------------------------------------
	// Purpose			: To draw a character in console at a
	//					  specific position
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
void drawChar( char c, Vector2 positionVector, int textAttribute );
#endif