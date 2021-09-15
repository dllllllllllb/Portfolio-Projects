//Author: Maciej Dowbor
//Last Accessed: 17/05/2021

#ifndef RESOURCESENUM_H
#define RESOURCESENUM_H

#include <string>

enum class ResourcesEnum
{
	gold,
	wood,
	stone,
	random
};

static const std::string resourceEnumString[4]{ "gold", "wood", "stone", "random" };

#endif // !RESOURCESENUM_H

