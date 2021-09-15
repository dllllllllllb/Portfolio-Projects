//Author: Maciej Dowbor
//Module: MED5149
//Date last accessed: 20/01/2021

#include "WaveData.h"

WaveData::WaveData( ) :
	m_waveSize( 0 )
{
	m_waveSetup = new int[1];
}

WaveData::~WaveData( )
{
	safeDelete( m_waveSetup );
}

void WaveData::setWaveData( const std::string &arraySize, const std::string *waveSetup )
{
	safeDelete( m_waveSetup ); //Makes sure that the file is empty

	int arrPos	= 0;
	m_waveSize	= std::stoi( arraySize );	//Translates string to int
	m_waveSetup = new int[m_waveSize];		//Creates an array based on the wave size

	//Loops through rows and collumns to get a number represented by a char, translate it to an intiger and allocate it in appropriate place in the array
	for( int row = 0; row < k_numOfEnemyRows; row++ )
	{
		for( int collumn = 0; waveSetup[row][collumn] != '\0'; collumn++ )
		{
			m_waveSetup[arrPos] = waveSetup[row][collumn] - '0';
			arrPos++;
		}
	}
}

const int *WaveData::getWaveSetup( )
{
	return m_waveSetup;
}

const int WaveData::getWaveSize( ) const
{
	return m_waveSize;
}