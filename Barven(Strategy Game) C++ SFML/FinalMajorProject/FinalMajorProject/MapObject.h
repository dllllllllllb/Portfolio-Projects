//Author: Maciej Dowbor
//Last Accessed: 17/06/2021

#ifndef MAPOBJECT_H
#define MAPOBJECT_H

#include <SFML/Graphics/Sprite.hpp>
#include "MapObjectDataEnums.h"


//===========================================================================================
//Description: Base class for every map object
//===========================================================================================
class MapObject : public sf::Sprite
{
private:
	int m_tileIndex;

public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	MapObject();

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~MapObject();

	//===========================================================================================
	//Description: Sets tile index the object is on
	//===========================================================================================
	void setTileIndex(const int& tileIndex);

	//===========================================================================================
	//Description: Returns tile index the object is on
	//===========================================================================================
	const int& getTileIndex() const;

	//===========================================================================================
	//Description: Returns self
	//===========================================================================================
	MapObject* getSelf();
};


#endif // !MAPOBJECT_H

