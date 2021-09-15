//Author: Maciej Dowbor
//Last Accessed: 02/08/2021

#ifndef MAPCREATORENUM_H
#define MAPCREATORENUM_H

enum class MapCreatorEnum
{
	towns,
	resourceMines,
	resources,
	specialBuildings,
	unitFactionSelection,
	landscapeTree,
	landscapeRocky,
	landscapeOther,
	mapSize
};

enum class MapCreatorTownsEnum
{
	player,
	enemyAI,
	neutral
};

enum class MapCreatorResourcesEnum
{
	gold,
	wood,
	stone,
	random
};

enum class MapCreatorSpecialBuildingsEnum
{
	arena,
	watchTower
};

enum class MapCreatorLandscapeTypeEnum
{
	none,
	tree,
	rocky,
	other
};

#endif // !MAPCREATORENUM_H
