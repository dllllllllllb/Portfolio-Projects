//Author: Maciej Dowbor
//Module: MED5148
//Date last accessed: 28/10/2020

#include "HighScore.h"

//Constructor
HighScore::HighScore()
	:m_name(""),
	 m_score(0)
{
}

//Destructor
HighScore::~HighScore()
{
}

//Sets players name
void HighScore::setName( std::string string )
{
	m_name = string; //Sets players name
}

//Sets score
void HighScore::setScore( int score )
{
	m_score = score;//Sets score
}

//Return players name
std::string HighScore::getName()
{
	return m_name; //Return stored name
}

//Return score
int HighScore::getScore()
{
	return m_score; //Return stored score
}
