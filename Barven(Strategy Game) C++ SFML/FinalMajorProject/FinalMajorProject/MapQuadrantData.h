//Author: Maciej Dowbor
//Last Accessed: 17/06/2021

#ifndef MAPQUADRANTDATA_H
#define MAPQUADRANTDATA_H

#include <vector>

#include "MapObject.h"

//===========================================================================================
//Description: Stores tiles and map object located in an small area of the map
//===========================================================================================
class MapQuadrantData
{
private:
	std::vector<int> m_tileIndexes;
	std::vector<MapObject*> m_mapObjectPointers;

public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	MapQuadrantData();

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~MapQuadrantData();

	//===========================================================================================
	//Description: Adds a new tile index to the tiles vector
	//===========================================================================================
	void addTileIndex(const int& tileIndex);

	//===========================================================================================
	//Description: Returns a reference to vector of tile indexes
	//===========================================================================================
	std::vector<int>& getTileIndexesVector();

	//===========================================================================================
	//Description: Adds a new map object to the map objects vector, uses polymorphisim to store
	//			   various types of map objects in one vector for the ease of use
	//===========================================================================================
	void addMapObjectPointer(MapObject* mapObject);

	//===========================================================================================
	//Description: Returns a reference to vector of map objects
	//===========================================================================================
	std::vector<MapObject*>& getMapObjectPointersVector();
};

#endif // !MAPQUADRANTDATA_H

