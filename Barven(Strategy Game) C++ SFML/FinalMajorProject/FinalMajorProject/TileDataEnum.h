//Author: Maciej Dowbor
//Last Accessed: 17/05/2021

#ifndef TILEDATAENUM_H
#define TILEDATAENUM_H

#include <string>

enum class TileDataEnum
{
	positionX,
	positionY,
	isObstacle,
	objectType,
	objectIndex
};

static const std::string tileDataEnumString[5]{ "positionX", "positionY", "isObstacle", "objectType", "objectIndex" };

#endif // !TILEDATAENUM_H

