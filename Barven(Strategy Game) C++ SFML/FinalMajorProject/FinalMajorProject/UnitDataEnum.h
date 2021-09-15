//Author: Maciej Dowbor
//Last Accessed: 02/09/2021

#ifndef UNITDATAENUM_H
#define UNITDATAENUM_H

#include <string>
#include "ConstantVariables.h"

enum class UnitDataEnum
{
	sprite,
	index,
	health,
	attack,
	minDamage,
	maxDamage,
	isRanged,
	ammunition,
	range,
	defence,
	isFlying,
	speed,
	growthPerWeek,
	cost,
	unitName,
	unitIcon,
	faction,
	mapSprite,
	AIValue
};

static const std::string c_unitDataEnumStrings[c_unitDataEnumLength]{ "sprite", "index", "health", "attack", "minDamage", "maxDamage", "isRanged", "ammunition", "range", "defence", "isFlying", "speed", "growthPerWeek", "cost", "unitName", "unitIcon", "faction", "mapSprite", "AIValue" };

enum class UnitBattleDataEnum
{
	health,
	attack,
	ammunition,
	range,
	defence,
	speed
};

#endif // !UNITDATAENUM_H
