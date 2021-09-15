//Author: Maciej Dowbor
//Module: MED5149
//Date last accessed: 20/01/2021

#include "WaveHandler.h"

WaveHandler::WaveHandler( )
{
	m_fileName = new std::string( "WaveSetup.txt" );

	loadWaveData( );
}

WaveHandler::~WaveHandler( )
{
	safeDelete( m_fileName );
}

void WaveHandler::loadWaveData( )
{
	m_file.open( *m_fileName );

	if( m_file.is_open( ) )
	{
		std::string waveSize;
		std::string waveSetup[k_numOfEnemyRows];

		for( int i = 0; i < k_numOfWaves; i++ )
		{
			//Clears temporary variables
			waveSize.clear( );

			for( int z = 0; z < k_numOfEnemyRows; z++ )
			{
				waveSetup[z].clear( );
			}

			//Reads txt file line by line and stores it as string
			std::getline( m_file, waveSize );
			for( int k = 0; k < k_numOfEnemyRows; k++ )
			{
				std::getline( m_file, waveSetup[k] );
			}
			//Passes the strings to wave data to translate and store
			m_waveData[i].setWaveData( waveSize, waveSetup );
		}
	}

	m_file.close( );
}

WaveData &WaveHandler::getWaveData( const int &index )
{
	return m_waveData[index];
}