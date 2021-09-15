//Author: Maciej Dowbor
//Last Accessed: 02/09/2021

#ifndef MAPHANDLERSETTINGS_H
#define MAPHANDLERSETTINGS_H

namespace MapHandlerSettings
{
	//Drawing quadrants
	static const int c_drawQuadrantWidth = 2; //Size in number of tiles
	static const int c_drawQuadrantHeight = 2;

	static const int c_quadrantsSafetyNet = 4;

	//Starting units settings
	static const int c_numOfStartingUnits = 3;
									  //[x][y][z]: x == numberOfFaction, y == available starting units, z == range of available units (min , max) 
	static const int c_rangeOfStartUnits[2][c_numOfStartingUnits][2]{ { { 10, 20 }, { 4, 7 }, { 2, 3 } },
																	  { { 20, 30 }, { 4, 7 }, { 3, 4 } }
																										};

	//Map UI
	static const int c_numberOfDaysPerWeek = 7;
	static const int c_numberOfDaysPerMonth = 28; //For games sake


	//Map object information feedback

}

#endif // !MAPHANDLERSETTINGS_H
