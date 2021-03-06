//Author: Maciej Dowbor
//Last Accessed: 14/04/2021


//=============================================================================================
//=============================================================================================
//=============================================================================================
//				NOT IN USE, OLD DATA HANDLER FOR .TXT BEFORE JSON IMPLEMENTATION
//=============================================================================================
//=============================================================================================
//=============================================================================================

//#ifndef DATAHANDLEROLD_H
//#define DATAHANDLEROLD_H
//
//#include <fstream>
//#include <direct.h>
//
//#include <SFML/System.hpp>
//#include <json.hpp>
//
//#include "ConstantVariables.h"
//#include "FactionData.h"
//#include "Textures.h"
//
//using json = nlohmann::json;
//
////===========================================================================================
////Description: Handles loading, storing and saveing data
////===========================================================================================
//class DataHandlerOLD
//{
//private:
//	std::ifstream m_fileRead;
//	std::ofstream m_fileWrite;
//	FactionData m_factionData[c_numOfFactions];
//
//public:
//	//===========================================================================================
//	//Description: Class constructor
//	//===========================================================================================
//	DataHandlerOLD();
//
//	//===========================================================================================
//	//Description: Class destructor
//	//===========================================================================================
//	~DataHandlerOLD();
//
//	//===========================================================================================
//	//Description: Loads unit data from txt files
//	//===========================================================================================
//	void loadUnitData();
//
//	//===========================================================================================
//	//Description: Saves unit date in txt files
//	//===========================================================================================
//	void saveUnitData(const std::string& directory, const UnitData& unitData);
//
//	//===========================================================================================
//	//Description: Adds directory to a file
//	//===========================================================================================
//	void addDirectoryToFile(const std::string& fileDirectory, const std::string& directoryToAdd);
//
//	//===========================================================================================
//	//Description: Returns faction data reference
//	//===========================================================================================
//	FactionData& getFactionData(const int& factionIndex);
//};

//#endif // !DATAHANDLEROLD_H

