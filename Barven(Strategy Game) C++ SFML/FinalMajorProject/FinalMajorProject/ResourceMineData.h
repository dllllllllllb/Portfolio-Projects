//Author: Maciej Dowbor
//Last Accessed: 29/04/2021

#ifndef RESOURCEMINEDATA_H
#define RESOURCEMINEDATA_H

#include <SFML/Graphics/Texture.hpp>
#include "ResourcesEnum.h"

//===========================================================================================
//Description: Hold resource mine data
//===========================================================================================
class ResourceMineData
{
private:
	int m_resourceGainPerDay;
	ResourcesEnum m_mineResourceType;
	sf::Texture m_mineMapTexture;

public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	ResourceMineData();

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~ResourceMineData();

	//===========================================================================================
	//Description: Sets mine map texture
	//===========================================================================================
	void setMineMapTexture(const std::string& mineTextureFilePath);

	//===========================================================================================
	//Description: Returns mine map texture
	//===========================================================================================
	const sf::Texture* getMineMapTexture() const;

	//===========================================================================================
	//Description: Set resource gan per day
	//===========================================================================================
	void setResourceGainPerDay(const int& resourceGainPerDay);

	//===========================================================================================
	//Description: Return resource gain per dat
	//===========================================================================================
	const int& getResourceGainPerDay() const;

	//===========================================================================================
	//Description: Set mine type
	//===========================================================================================
	void setMineType(const ResourcesEnum& mineType);

	//===========================================================================================
	//Description: Return mine type
	//===========================================================================================
	const ResourcesEnum& getMineType() const;
};

#endif // !RESOURCEMINEDATA_H

