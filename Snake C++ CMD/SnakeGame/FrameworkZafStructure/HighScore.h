//Author: Maciej Dowbor
//Module: MED5148
//Date last accessed: 28/10/2020

#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <string>


//=============================================================
// Class Name   : HighScore
//-------------------------------------------------------------
// Purpose      : Store hight score data
//-------------------------------------------------------------
// Used in      : HighScoreTable.h
//				  HighScoreTable.cpp
//=============================================================
class HighScore
{

private:
	std::string m_name; //Stores players name
	int m_score; //Stores score

public:
	//========================================================
	// Function Name	: HighScore()
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: HighScore constructor
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	HighScore();

	//========================================================
	// Function Name	: ~HighScore()
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: HighScore destructor
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	~HighScore();

	//========================================================
	// Function Name	: setName()
	//--------------------------------------------------------
	// Parameters		: Players name
	//--------------------------------------------------------
	// Purpose			: Set players name
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	void setName( std::string string );

	//========================================================
	// Function Name	: getName()
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: Returns stored name
	//--------------------------------------------------------
	// Returns			: Name as string
	//========================================================
	std::string getName();

	//========================================================
	// Function Name	: setScore()
	//--------------------------------------------------------
	// Parameters		: Score
	//--------------------------------------------------------
	// Purpose			: Set score
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	void setScore( int score );

	//========================================================
	// Function Name	: getScore
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: Returns stored score
	//--------------------------------------------------------
	// Returns			: Score as int
	//========================================================
	int getScore();

};
#endif // !HIGHSCORE_H

