//Author: Maciej Dowbor
//Last Accessed: 21/07/2021

#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics/Sprite.hpp>
#include <vector>
#include <list>
#include <memory>

#include "MapObjectsEnum.h"
#include "MapObject.h"
#include "Macros.h"

//===========================================================================================
//Description: Used for path finding, navigation around the map and battles
//===========================================================================================
class Tile : public sf::Sprite
{
private:
	//Tile data
	bool m_isOccupied;
	MapObjectsEnum m_mapObjectType;
	int m_objectVectorIndex;
	int m_tileVectorIndex;

	//Path Finding Data
	bool m_isObstacle;
	bool m_isVisited;

	float m_localGoal;
	float m_globalGoal;

	std::vector<Tile*>m_surroundingTiles;
	Tile* m_pParentTile;
public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	Tile();

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~Tile();

	//===========================================================================================
	//Description: Sets tile position
	//===========================================================================================
	void setPosition(const float& positionX, const float& positionY);

	//===========================================================================================
	//Description: Sets parent tile, used to create path
	//===========================================================================================
	void setParentTile(Tile* parentTile);

	//===========================================================================================
	//Description: Sets parent tile to nullptr
	//===========================================================================================
	void resetParent();

	//===========================================================================================
	//Description: Returns parent tile
	//===========================================================================================
	Tile* getParentTile();

	//===========================================================================================
	//Description: Toggles obstacle bool state
	//===========================================================================================
	void toggleIsObstacle();

	//===========================================================================================
	//Description: Sets obstacle bool state
	//===========================================================================================
	void setIsObstacle(const bool state);

	//===========================================================================================
	//Description: Returns obstacle bool state
	//===========================================================================================
	const bool getIsObstacle() const;

	//===========================================================================================
	//Description: Sets visited bool
	//===========================================================================================
	void setIsVisited(const bool state);

	//===========================================================================================
	//Description: Returns visited bool
	//===========================================================================================
	const bool getIsVisited() const;

	//===========================================================================================
	//Description: Sets local goal
	//===========================================================================================
	void setLocalGoal(const float& goal);

	//===========================================================================================
	//Description: Returns local goal
	//===========================================================================================
	const float& getLocalGoal() const;

	//===========================================================================================
	//Description: Sets global goal, used to indicate distance between self and end tile
	//===========================================================================================
	void setGlobalGoal(const float& goal);

	//===========================================================================================
	//Description: Returns global goal
	//===========================================================================================
	const float& getGlobalGoal() const;

	//===========================================================================================
	//Description: Returns a vector of neighbouring tiles
	//===========================================================================================
	std::vector<Tile*>& getSurroundingTilesVector();

	//===========================================================================================
	//Description: Sets tile occupied status
	//===========================================================================================
	void setIsOccupied(const bool state);

	//===========================================================================================
	//Description: Returns if a tile is occupied
	//===========================================================================================
	const bool getIsOccupied() const;

	//===========================================================================================
	//Description: Sets map object type
	//===========================================================================================
	void setMapObjectType(const MapObjectsEnum& mapObject);

	//===========================================================================================
	//Description: Returns map object type
	//===========================================================================================
	const MapObjectsEnum& getMapObjectType() const;

	//===========================================================================================
	//Description: Sets map object vector index
	//===========================================================================================
	void setMapObjectVectorIndex(const int& objectIndex);

	//===========================================================================================
	//Description: Returns map object vector index
	//===========================================================================================
	const int& getMapObjectVectorIndex() const;

	//===========================================================================================
	//Description: Sets tile vector position index
	//===========================================================================================
	void setTileVectorIndex(const int& tileVectorIndex);

	//===========================================================================================
	//Description: Returns tile vector position index
	//===========================================================================================
	const int& getTileVectorIndex() const;

	//===========================================================================================
	//Description: Decrements map object vector index
	//===========================================================================================
	void decrementMapObjectVectorIndex();

	//===========================================================================================
	//Description: Resets tile properties
	//===========================================================================================
	void resetTileProperties();
};

#endif // !TILE_H