//Author: Maciej Dowbor
//Last Accessed: 29/04/2021

#ifndef TOWNMAPOBJECT_H
#define TOWNMAPOBJECT_H

#include "MapObject.h"

//===========================================================================================
//Description: Town map object
//===========================================================================================
class TownMapObject : public MapObject
{
private:
	int m_ownerIndex;
	int m_factionIndex;
public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	TownMapObject();

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~TownMapObject();

	//===========================================================================================
	//Description: Sets up objects position and texture
	//===========================================================================================
	void setUp(const sf::Vector2f position, const sf::Texture& pTexture);

	//===========================================================================================
	//Description: Sets owner index
	//===========================================================================================
	void setOwnerIndex(const int& ownerIndex);

	//===========================================================================================
	//Description: Returns owner index
	//===========================================================================================
	const int& getOwnerIndex() const;

	//===========================================================================================
	//Description: Sets faction index
	//===========================================================================================
	void setFactionIndex(const int& factionIndex);

	//===========================================================================================
	//Description: Returns faction index
	//===========================================================================================
	const int& getFactionIndex() const;

	//===========================================================================================
	//Description: Robust way of setting variables, made with expansion in mind.
	//			   Used by map object editor window
	//===========================================================================================
	void setVariable(const MapObjectDataEnum::Town& variable, const int& value);

	//===========================================================================================
	//Description: Robust way of returning variables, made with expansion in mind.
	//			   Used by map object editor window
	//===========================================================================================
	const int getVariable(const MapObjectDataEnum::Town& variable) const;
};
#endif // !TOWNMAPOBJECT_H

