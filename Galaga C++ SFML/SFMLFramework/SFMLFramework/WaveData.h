//Author: Maciej Dowbor
//Module: MED5149
//Date last accessed: 20/01/2021

#ifndef WAVEDATA_H
#define WAVEDATA_H

#include <cstddef>
#include <iostream>
#include <string>

#include "Helpers.h"
#include "Settings.h"

//=====================================================================================================	
//Class		: WaveData
//-----------------------------------------------------------------------------------------------------
//Purpose	: Translates and holds wave data loaded from txt file
//=====================================================================================================
class WaveData
{
private:
	int m_waveSize;
	int *m_waveSetup;

public:

	WaveData( );
	//=================================================================================================
	//Purpose	: Constructor
	//-------------------------------------------------------------------------------------------------
	//Parameters: -
	//-------------------------------------------------------------------------------------------------
	//Returns	: -
	//=================================================================================================

	~WaveData( );
	//=================================================================================================
	//Purpose	: Destructor
	//-------------------------------------------------------------------------------------------------
	//Parameters: -
	//-------------------------------------------------------------------------------------------------
	//Returns	: -
	//=================================================================================================

	void setWaveData( const std::string &arraySize, const std::string *waveSetup );
	//=================================================================================================
	//Purpose	: Translates string to int and stores it in variables
	//-------------------------------------------------------------------------------------------------
	//Parameters: Array size and wave setup
	//-------------------------------------------------------------------------------------------------
	//Returns	: -
	//=================================================================================================

	const int *getWaveSetup( );
	//=================================================================================================
	//Purpose	: Return pointer to wave setup
	//-------------------------------------------------------------------------------------------------
	//Parameters: -
	//-------------------------------------------------------------------------------------------------
	//Returns	: Pointer to wave setup
	//=================================================================================================

	const int  getWaveSize( )  const;
	//=================================================================================================
	//Purpose	: Return wave size
	//-------------------------------------------------------------------------------------------------
	//Parameters: -
	//-------------------------------------------------------------------------------------------------
	//Returns	: Wave size
	//=================================================================================================
};

#endif // !WAVEDATA_H