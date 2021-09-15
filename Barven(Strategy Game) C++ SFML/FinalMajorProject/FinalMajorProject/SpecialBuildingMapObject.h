//Author: Maciej Dowbor
//Last Accessed: 17/05/2021

#ifndef SPECIALBUILDINGMAPOBJECT_H
#define SPECIALBUILDINGMAPOBJECT_H

#include "SpecialBuildingEnum.h"
#include "MapObject.h"

//===========================================================================================
//Description: Special building map object, such as arenas and watch towers
//===========================================================================================
class SpecialBuildingMapObject : public MapObject
{
private:
	bool m_isVisited;
	SpecialBuildingEnum m_buildingType;
public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	SpecialBuildingMapObject();

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~SpecialBuildingMapObject();

	//===========================================================================================
	//Description: Set up position, texture and origin
	//===========================================================================================
	void setUp(const sf::Vector2f position, const sf::Texture* pTexture);

	//===========================================================================================
	//Description: Set is visited
	//===========================================================================================
	void setIsVisited(const bool state);

	//===========================================================================================
	//Description: Return is visited
	//===========================================================================================
	const bool getIsVisited() const;

	//===========================================================================================
	//Description: Set building type
	//===========================================================================================
	void setBuildingType(const SpecialBuildingEnum& buildingType);

	//===========================================================================================
	//Description: Return building type
	//===========================================================================================
	const SpecialBuildingEnum& getBuildingType() const;
};

#endif // !SPECIALBUILDINGMAPOBJECT_H

