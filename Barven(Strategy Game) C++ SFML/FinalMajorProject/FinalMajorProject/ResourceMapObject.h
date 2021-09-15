//Author: Maciej Dowbor
//Last Accessed: 29/04/2021

#ifndef RESOURCEMAPOBJECT_H
#define RESOURCEMAPOBJECT_H

#include "MapObject.h"
#include "ResourcesEnum.h"

//===========================================================================================
//Description: Resource map object
//===========================================================================================
class ResourceMapObject : public MapObject
{
private:
	int m_resourceAmount;
	ResourcesEnum m_resourceType;

public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	ResourceMapObject();

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~ResourceMapObject();

	//===========================================================================================
	//Description: Sets up objects position and texture
	//===========================================================================================
	void setUp(const sf::Vector2f position, const sf::Texture* pTexture);

	//===========================================================================================
	//Description: Sets resource amount
	//===========================================================================================
	void setResourceAmount(const int& resourceAmount);

	//===========================================================================================
	//Description: Returns resource amount
	//===========================================================================================
	const int& getResourceAmount() const;

	//===========================================================================================
	//Description: Sets resource type as int
	//===========================================================================================
	void setResourceType(const int& resourceType);

	//===========================================================================================
	//Description: Sets resource type as enum
	//===========================================================================================
	void setResourceType(const ResourcesEnum& resourceType);

	//===========================================================================================
	//Description: Returns resource type as enum
	//===========================================================================================
	const ResourcesEnum& getResourceType() const;

	//===========================================================================================
	//Description: Robust way of setting variables, made with expansion in mind.
	//			   Used by map object editor window
	//===========================================================================================
	void setVariable(const MapObjectDataEnum::Resource& variable, const int& value);

	//===========================================================================================
	//Description: Robust way of getting variables, made with expansion in mind.
	//			   Used by map object editor window
	//===========================================================================================
	const int& getVariable(const MapObjectDataEnum::Resource& variable) const;

};

#endif // !RESOURCEMAPOBJECT_H

