//Author: Maciej Dowbor
//Last Accessed: 17/06/2021

#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <direct.h> //For _mkdir == creates folder directories
#include <fstream>
#include "json.hpp"
#include <SFML/System.hpp>

#include "ConstantVariables.h"
#include "FactionData.h"
#include "ResourceMineData.h"
#include "Textures.h"
#include "DataHandlerSettings.h"

using json = nlohmann::json;

//===========================================================================================
//Description: Handles loading, storing and saveing data
//===========================================================================================
class DataHandler
{
private:
	std::ifstream m_fileRead;
	std::ofstream m_fileWrite;
	FactionData m_factionData[c_numOfFactions];
	ResourceMineData m_resourceMines[c_numOfResourceMines];

	std::vector<std::string> m_mapNames;
	std::vector<std::string> m_mapDirectories;
	std::vector<int> m_mapNumberOfPlayers;

	json m_loadedMapData;

public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	DataHandler();

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~DataHandler();

	//===========================================================================================
	//Description: Loads data
	//===========================================================================================
	void loadData();

	//===========================================================================================
	//Description: Loads town data from JSON files
	//===========================================================================================
	void loadTownData();

	//===========================================================================================
	//Description: Loads unit data from JSON files
	//===========================================================================================
	void loadUnitData();

	//===========================================================================================
	//Description: Loads resource mines data
	//===========================================================================================
	void loadResourceMinesData();

	//===========================================================================================
	//Description: Saves unit date in JSON files
	//===========================================================================================
	void saveUnitData(const std::string& directory, const json& jsonData);

	//===========================================================================================
	//Description: Loads core data for every map
	//===========================================================================================
	void loadCoreMapsData();

	//===========================================================================================
	//Description: Loads map data to a json file
	//===========================================================================================
	void loadMapData(const int& mapIndex);

	//===========================================================================================
	//Description: Returns a reference to loaded map data
	//===========================================================================================
	json& getLoadedMapData();

	//===========================================================================================
	//Description: Clears loaded map data
	//===========================================================================================
	void deleteLoadedMapData();

	//===========================================================================================
	//Description: Saves map data as JSON file
	//===========================================================================================
	void saveMapData(const std::string& mapName, const json& jsonData);

	//===========================================================================================
	//Description: Adds directory to a file
	//===========================================================================================
	void addDirectoryToFile(const std::string& fileDirectory, const std::string& directoryToAdd);

	//===========================================================================================
	//Description: Returns faction data reference
	//===========================================================================================
	FactionData& getFactionData(const int& factionIndex);

	//===========================================================================================
	//Description: Returns resource mine data
	//===========================================================================================
	const ResourceMineData& getResourceMineData(const ResourcesEnum& mineType) const;

	//===========================================================================================
	//Description: Returns a list of map names
	//===========================================================================================
	std::vector<std::string>& getMapNames();

	//===========================================================================================
	//Description: Returns number of players based on map index given
	//===========================================================================================
	const int& getMapMaxNumberOfPlayers(const int& mapIndex) const;
};

#endif // !DATAHANDLER_H
