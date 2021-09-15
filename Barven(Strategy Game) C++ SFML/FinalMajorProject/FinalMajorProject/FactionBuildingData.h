//Author: Maciej Dowbor
//Last Accessed: 18/08/2021

#ifndef FACTIONBUILDINGDATA_H
#define FACTIONBUILDINGDATA_H

#include "json.hpp"
#include <SFML/Graphics/Texture.hpp>

#include "TownBuildingEnum.h"
#include "TownBuildingSettings.h"

using json = nlohmann::json;

//===========================================================================================
//Description: Stores basic faction building data
//===========================================================================================
class FactionBuildingData
{
private:

	json m_data;
	sf::Texture m_buildingTextures[TownBuildingSettings::c_numOfBuildings];
	sf::Texture m_mapTexture;
	sf::Texture m_townIcon;

public:

	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	FactionBuildingData();

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~FactionBuildingData();

	//===========================================================================================
	//Description: Loads building textures
	//===========================================================================================
	void loadTextures();

	//===========================================================================================
	//Description: Returns building texture
	//===========================================================================================
	sf::Texture& getBuildingTexture(const TownBuildingEnum& building);

	//===========================================================================================
	//Description: Returns map texture
	//===========================================================================================
	sf::Texture& getMapTexture();

	//===========================================================================================
	//Description: Returns town icon texture
	//===========================================================================================
	sf::Texture& getTownIconTexture();

	//===========================================================================================
	//Description: Returns reference to json data
	//===========================================================================================
	json& getData();

};

#endif // !FACTIONBUILDINGDATA_H

