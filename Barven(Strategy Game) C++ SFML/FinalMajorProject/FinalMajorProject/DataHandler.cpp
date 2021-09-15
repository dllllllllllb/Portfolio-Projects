#include "DataHandler.h"
namespace settings = DataHandlerSettings;
DataHandler::DataHandler()
{
}

DataHandler::~DataHandler()
{
}

void DataHandler::loadData()
{
	loadTownData();
	loadUnitData();
	loadResourceMinesData();
	loadCoreMapsData();

	//Temporary
	m_factionData[0].getHeroData().loadHeroTexture();
	m_factionData[1].getHeroData().loadHeroTexture();
}

void DataHandler::loadTownData()
{
	int factionIndex = 0;
	std::string factionBuildingsDirectory = "";

	std::ifstream buildingsRead;

	m_fileRead.open(settings::c_facitonsBuildingsDataFile);
	if (m_fileRead.is_open())
	{
		while (std::getline(m_fileRead, factionBuildingsDirectory))
		{
			buildingsRead.open(factionBuildingsDirectory);
			if (buildingsRead.is_open())
			{
				buildingsRead >> m_factionData[factionIndex].getBuildingsData().getData();
				m_factionData[factionIndex].getBuildingsData().loadTextures();
			}
			buildingsRead.close();

			factionIndex++;

			if (factionIndex >= c_numOfFactions)
			{
				break;
			}
		}
	}
	m_fileRead.close();
}

void DataHandler::loadUnitData()
{
	int factionIndex = 0;
	int unitIndex = 0;

	std::string factionUnitsDirectory = "";
	std::string factionUnitDataDirectory = "";

	std::ifstream factionRead;
	std::ifstream unitRead;

	m_fileRead.open(settings::c_factionsUnitsDataFile);

	//Opens a txt file that holds unit direcotries of all factions
	if (m_fileRead.is_open())
	{
		while (std::getline(m_fileRead, factionUnitsDirectory))
		{
			factionRead.open(factionUnitsDirectory);

			//Opens unit data directory for given faction
			if (factionRead.is_open())
			{
				while (std::getline(factionRead, factionUnitDataDirectory))
				{
					//Opens unit data holder for individual unit
					unitRead.open(factionUnitDataDirectory);
					if (unitRead.is_open())
					{
						json tempJSON;
						unitRead >> tempJSON;

						m_factionData[factionIndex].getUnitData(unitIndex).loadJSONData(tempJSON);

						//Loads unit textures to memory
						m_factionData[factionIndex].getUnitData(unitIndex).loadTextures();

						unitIndex++;
					}
					unitRead.close();
				}
			}
			factionRead.close();

			unitIndex = 0;
			factionIndex++;

			if (factionIndex >= c_numOfFactions)
			{
				break;
			}
		}
	}
	m_fileRead.close();
}

void DataHandler::loadResourceMinesData()
{
	m_fileRead.open(settings::c_resourceMinesDataFile);
	if (m_fileRead.is_open())
	{
		json tempFile;
		m_fileRead >> tempFile;

		for (int i = 0; i < c_numOfResourceMines; i++)
		{
			m_resourceMines[i].setMineType((ResourcesEnum)i);
			m_resourceMines[i].setMineMapTexture(tempFile["mineMapTextures"][i]);
			m_resourceMines[i].setResourceGainPerDay(tempFile["resourceGainPerDay"][i]);
		}
	}
	m_fileRead.close();
}

void DataHandler::saveUnitData(const std::string& directory, const json& jsonData)
{
	// Faction directory
	std::string dirString = settings::c_factionsDirectory + directory;
	if (_mkdir(dirString.c_str()))
	{
		//Directory made
	}

	//Units directory
	dirString += "\\Units";
	if (_mkdir(dirString.c_str()))
	{
		//Directory made
	}

	//Save unit data
	dirString += "\\Unit" + std::to_string(jsonData.value("index", 0)) + ".json";

	m_fileWrite.open(dirString);
	if (m_fileWrite.is_open())
	{
		m_fileWrite << jsonData.dump(1);
	}
	m_fileWrite.close();

	std::string	unitDataString = settings::c_factionsDirectory + directory + "\\Units\\UnitData.txt";

	//Open/create unitData.txt in FactionX/Units and save dirString in it
	addDirectoryToFile(unitDataString, dirString);

	//Open FactionsUnitsData in Factions folder and save the directory to the UnitData.txt created above
	addDirectoryToFile(settings::c_factionsUnitsDataFile, unitDataString);
}

void DataHandler::loadCoreMapsData()
{
	json coreMapData;

	//Make sure vectors are empty
	m_mapNames.clear();
	m_mapDirectories.clear();
	m_mapNumberOfPlayers.clear();

	m_fileRead.open(settings::c_coreMapDataDirectory);
	if (m_fileRead.is_open())
	{
		m_fileRead >> coreMapData;

		for (size_t i = 0; i < coreMapData["maps"].size(); i++)
		{
			m_mapNames.push_back(coreMapData["maps"][i]["mapName"]);
			m_mapDirectories.push_back(coreMapData["maps"][i]["mapDirectory"]);
			m_mapNumberOfPlayers.push_back(coreMapData["maps"][i]["maxNumberOfPlayers"]);
		}
	}
	m_fileRead.close();
}

void DataHandler::loadMapData(const int& mapIndex)
{
	m_fileRead.open(m_mapDirectories[mapIndex]);
	if (m_fileRead.is_open())
	{
		m_fileRead >> m_loadedMapData;
	}
	m_fileRead.close();
}

json& DataHandler::getLoadedMapData()
{
	return m_loadedMapData;
}

void DataHandler::deleteLoadedMapData()
{
	m_loadedMapData.clear();
}

void DataHandler::saveMapData(const std::string& mapName, const json& jsonData)
{
	json coreMapData;
	json coreMapDataToAdd;
	bool isMapNameTaken = false;

	std::string directory = settings::c_mapDataSaveDirectory;
	directory += mapName + ".json";

	//Save core map data
	m_fileRead.open(settings::c_coreMapDataDirectory);
	if (m_fileRead.is_open())
	{
		m_fileRead >> coreMapData;
	}
	m_fileRead.close();

	//Check if the map already exists
	for (size_t i = 0; i < coreMapData["maps"].size(); i++)
	{
		if (coreMapData["maps"][i]["mapName"] == mapName)
		{
			isMapNameTaken = true;
			break;
		}
	}

	//Add new core map data and save it
	if (!isMapNameTaken)
	{
		//Save main map data
		m_fileWrite.open(directory);
		if (m_fileWrite.is_open())
		{
			m_fileWrite << jsonData.dump(1);
		}
		m_fileWrite.close();

		coreMapDataToAdd["mapName"] = mapName;
		coreMapDataToAdd["mapDirectory"] = directory;
		coreMapDataToAdd["maxNumberOfPlayers"] = jsonData["numOfPlayers"];
		coreMapData["maps"].push_back(coreMapDataToAdd);

		m_fileWrite.open(settings::c_coreMapDataDirectory);
		if (m_fileWrite.is_open())
		{
			m_fileWrite << coreMapData.dump(1);
		}
		m_fileWrite.close();
	}
}

void DataHandler::addDirectoryToFile(const std::string& fileDirectory, const std::string& directoryToAdd)
{
	std::string tempString = "";
	std::vector<std::string> tempDataVector;
	bool isDuplicate = false;

	//Check if the file exists, if not, make it
	m_fileRead.open(fileDirectory);
	if (!m_fileRead.is_open())
	{
		m_fileWrite.open(fileDirectory);
		if (m_fileWrite.is_open())
		{
			m_fileWrite << "";
		}
		m_fileWrite.close();
	}
	m_fileRead.close();

	m_fileRead.open(fileDirectory);
	if (m_fileRead.is_open())
	{
		//Check for duplicate directory
		while (std::getline(m_fileRead, tempString))
		{
			if (tempString == directoryToAdd)
			{
				isDuplicate = true;
			}
		}
	}
	m_fileRead.close();

	if (!isDuplicate)
	{
		//Save data to file
		m_fileWrite.open(fileDirectory, std::fstream::app);
		if (m_fileWrite.is_open())
		{
			m_fileWrite << directoryToAdd << "\n";
		}
		m_fileWrite.close();
	}
}

FactionData& DataHandler::getFactionData(const int& factionIndex)
{
	return m_factionData[factionIndex];
}

const ResourceMineData& DataHandler::getResourceMineData(const ResourcesEnum& mineType) const
{
	return m_resourceMines[(int)mineType];
}

std::vector<std::string>& DataHandler::getMapNames()
{
	return m_mapNames;
}

const int& DataHandler::getMapMaxNumberOfPlayers(const int& mapIndex) const
{
	return m_mapNumberOfPlayers[mapIndex];
}