//Author: Maciej Dowbor
//Last Accessed: 17/05/2021

#ifndef MAPOBJECTEDITORSETTINGS_H
#define MAPOBJECTEDITORSETTINGS_H

#include <string>

namespace MapObjectEditorSettings
{
	static const int c_numOfObjectTypes = 7; //Order based on MapObjectEnum.h
	static const int c_numOfvariablesToChange[c_numOfObjectTypes]{ 0, 1, 2, 0, 1, 0, 0 };
	static const int c_maxNumOfVariablesToChange = 2; //Highest number in the array above
	static const std::string c_variablesToChangeNames[c_numOfObjectTypes][c_maxNumOfVariablesToChange]{ {""}, {"Owner Index"}, { "Unit Index", "Num Of Units"}, {""}, {"Owner Index"}, {""}, {""} };
}

#endif // !MAPOBJECTEDITORSETTINGS_H
