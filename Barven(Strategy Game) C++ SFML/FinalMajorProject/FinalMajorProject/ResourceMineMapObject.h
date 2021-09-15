//Author: Maciej Dowbor
//Last Accessed: 17/05/2021

#ifndef RESOURCEMINEMAPOBJECT_H
#define RESOURCEMINEMAPOBJECT_H

#include "MapObject.h"
#include "ResourcesEnum.h"

class ResourceMineMapObject : public MapObject
{
private:
	ResourcesEnum m_mineType;
	int m_ownerIndex;
public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	ResourceMineMapObject();

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~ResourceMineMapObject();

	//===========================================================================================
	//Description: Sets up objects position and texture
	//===========================================================================================
	void setUp(const sf::Vector2f position, const sf::Texture* pTexture);

	//===========================================================================================
	//Description: Set mine type as enum
	//===========================================================================================
	void setMineTypeEnum(const ResourcesEnum& mineType);

	//===========================================================================================
	//Description: Set mine type as int
	//===========================================================================================
	void setMineTypeInt(const int& mineType);

	//===========================================================================================
	//Description: Return mine type as enum
	//===========================================================================================
	const ResourcesEnum& getMineType() const;

	//===========================================================================================
	//Description: Set owner index
	//===========================================================================================
	void setOwnerIndex(const int& ownerIndex);

	//===========================================================================================
	//Description: Return owner index
	//===========================================================================================
	const int& getOwnerIndex() const;

	//===========================================================================================
	//Description: Robust way of setting variables, made with expansion in mind.
	//			   Used by map object editor window
	//===========================================================================================
	void setVariable(const MapObjectDataEnum::ResourceMine& variable, const int& value);

	//===========================================================================================
	//Description: Robust way of returning variables, made with expansion in mind.
	//			   Used by map object editor window
	//===========================================================================================
	const int& getVariable(const MapObjectDataEnum::ResourceMine& variable) const;
};


#endif // !RESOURCEMINEMAPOBJECT_H

