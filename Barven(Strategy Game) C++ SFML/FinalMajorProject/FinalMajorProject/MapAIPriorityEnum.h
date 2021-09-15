//Author: Maciej Dowbor
//Last Accessed: 10/09/2021

#ifndef MAPAIPRIORITYENUM_H
#define MAPAIPRIORITYENUM_H

enum class MapAIPriorityEnum
{
	none,
	resourceGold,
	resourceWood,
	resourceStone,
	recruitUnits,
	protectTown,
	attackEnemyHero,
	attackEnemyTown,
	attackMapUnit,
	closestResourceMine,
	arena,
	collectGold,
	collectWood,
	collectStone,
	collectResource
};

#endif // !MAPAIPRIORITYENUM_H

