//Author: Maciej Dowbor
//Module: MED5149
//Date last accessed: 20/01/2021

#include "HighScoreData.h"

HighScoreData::HighScoreData( ) :
	m_name( "" ),
	m_score( 0 )
{
}

HighScoreData::~HighScoreData( )
{
}

void HighScoreData::setName( const std::string &name )
{
	m_name = name;
}

std::string &HighScoreData::getName( )
{
	return m_name;
}

void HighScoreData::setScore( const int score )
{
	m_score = score;
}

int HighScoreData::getScore( )
{
	return m_score;
}