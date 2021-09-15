//Author: Maciej Dowbor
//Module: MED5148
//Date last accessed: 28/10/2020

#ifndef BORDER_H
#define BORDER_H

#include "CharObject.h"

//=============================================================
// Class Name   : Border
//-------------------------------------------------------------
// Purpose      : Initialize and draw playing area border
//-------------------------------------------------------------
// Used in      : Border.cpp
//				  Game.cpp      
//				  Game.h      
//=============================================================
class Border : public CharObject
{
private:
	

public:

	//========================================================
	// Function Name	: Border()
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: Border constructor
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	Border();

	//========================================================
	// Function Name	: ~Border()
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: Border destructor
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	~Border();

	//========================================================
	// Function Name	: drawBorder()
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: Draw border on the screen
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	void drawBorder();
};

#endif // !BORDER_H