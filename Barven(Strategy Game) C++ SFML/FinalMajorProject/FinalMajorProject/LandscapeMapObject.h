//Author: Maciej Dowbor
//Last Accessed: 17/05/2021

#ifndef LANDSCAPEMAPOBJECT_H
#define LANDSCAPEMAPOBJECT_H

#include "MapObject.h"
#include "LandscapeTypeEnum.h"

//===========================================================================================
//Description: Landscape map object
//===========================================================================================
class LandscapeMapObject : public MapObject
{
private:
	int m_objectIndex;
	LandscapeTypeEnum m_landscapeType;
public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	LandscapeMapObject();

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~LandscapeMapObject();

	//===========================================================================================
	//Description: Sets up objects position and texture
	//===========================================================================================
	void setUp(const sf::Vector2f position, const sf::Texture* pTexture);

	//===========================================================================================
	//Description: Sets object index
	//===========================================================================================
	void setObjectIndex(const int& index);

	//===========================================================================================
	//Description: Returns object index
	//===========================================================================================
	const int& getObjectIndex() const;

	//===========================================================================================
	//Description: Sets landscape type
	//===========================================================================================
	void setLandscapeType(const LandscapeTypeEnum& landscapeType);

	//===========================================================================================
	//Description: Returns landscape type
	//===========================================================================================
	const LandscapeTypeEnum& getLandscapeType() const;


};

#endif // !LANDSCAPEMAPOBJECT_H

