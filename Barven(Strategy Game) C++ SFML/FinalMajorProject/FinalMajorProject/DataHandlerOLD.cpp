//#include "DataHandlerOLD.h"
////=============================================================================================
////=============================================================================================
////=============================================================================================
////				NOT IN USE, OLD DATA HANDLER FOR .TXT BEFORE JSON IMPLEMENTATION
////=============================================================================================
////=============================================================================================
////=============================================================================================
//DataHandlerOLD::DataHandlerOLD()
//{
//}
//
//DataHandlerOLD::~DataHandlerOLD()
//{
//}
//
//void DataHandlerOLD::loadUnitData()
//{
//	//int factionIndex = 0;
//	//int unitIndex = 0;
//	//
//	//std::string faction = "";
//	//std::string unit = "";
//	//
//	//std::ifstream factionRead;
//	//std::ifstream unitRead;
//	//
//	//
//	//m_fileRead.open(c_factionsUnitsDataFile);
//	//
//	//if (m_fileRead.is_open())
//	//{
//	//	while (std::getline(m_fileRead, faction))
//	//	{
//	//		factionRead.open(faction);
//	//
//	//		if (factionRead.is_open())
//	//		{
//	//			while (std::getline(factionRead, unit))
//	//			{
//	//
//	//				unitRead.open(unit);
//	//
//	//				if (unitRead.is_open())
//	//				{
//	//					std::string content = "";
//	//					UnitData* tempUnit = m_factionData[factionIndex].getUnit(unitIndex);
//	//
//	//					int tempint = 0;
//	//
//	//					while (std::getline(unitRead, content))
//	//					{
//	//						switch (tempint)
//	//						{
//	//						case 0:
//	//							tempUnit->loadUnitSprite(content);
//	//							break;
//	//
//	//						case 13:
//	//							tempUnit->setUnitName(content);
//	//							break;
//	//
//	//						case 14:
//	//							tempUnit->loadUnitIcon(content);
//	//							break;
//	//
//	//						default:
//	//							tempUnit->setData((UnitDataEnum)tempint, std::stoi(content));
//	//							break;
//	//						}
//	//						tempint++;
//	//					}
//	//
//	//					unitIndex++;
//	//					unitRead.close();
//	//				}
//	//			}
//	//		}
//	//		factionIndex++;
//	//	}
//	//	factionRead.close();
//	//}
//	//
//	//m_fileRead.close();
//}
//
//void DataHandlerOLD::saveUnitData(const std::string& directory, const UnitData& unitData)
//{
//	////Faction directory
//	//std::string dirString = c_factionsDirectory +  directory;
//	//if (_mkdir(dirString.c_str()))
//	//{
//	//	//Directory made
//	//}
//	//
//	////Units directory
//	//dirString += "\\Units";
//	//if (_mkdir(dirString.c_str()))
//	//{
//	//	//Directory made
//	//}
//	//
//	////Save unit data
//	//dirString += "\\Unit" + std::to_string(unitData.getIntData(UnitDataEnum::index)) + ".txt";
//	//
//	//m_fileWrite.open(dirString);
//	//if (m_fileWrite.is_open())
//	//{
//	//	for (int i = 0; i < c_unitDataEnumLength; i++)
//	//	{
//	//		switch (i)
//	//		{
//	//		case 0:
//	//			m_fileWrite << unitData.getSpriteFilePath() << "\n";
//	//			break;
//	//
//	//		case 4:
//	//			m_fileWrite << std::to_string(unitData.getBoolData((UnitDataEnum)i)) << "\n";
//	//			break;
//	//
//	//		case 9:
//	//			m_fileWrite << std::to_string(unitData.getBoolData((UnitDataEnum)i)) << "\n";
//	//			break;
//	//
//	//		case 13:
//	//			m_fileWrite << unitData.getUnitName() << "\n";
//	//			break;
//	//
//	//		case 14:
//	//			m_fileWrite << unitData.getIconFilePath() << "\n";
//	//			break;
//	//
//	//		default:
//	//			m_fileWrite << std::to_string(unitData.getIntData((UnitDataEnum)i)) << "\n";
//	//			break;
//	//		}
//	//	}
//	//}
//	//m_fileWrite.close();
//	//
//	//std::string	unitDataString = c_factionsDirectory + directory + "\\Units\\UnitData.txt";
//	//
//	////Open/create unitData.txt in FactionX/Units and save dirString in it
//	//addDirectoryToFile(unitDataString, dirString);
//	//
//	////Open FactionsUnitsData in Factions folder and save the directory to the UnitData.txt created above
//	//addDirectoryToFile(c_factionsUnitsDataFile, unitDataString);
//}
//
//void DataHandlerOLD::addDirectoryToFile(const std::string& fileDirectory, const std::string& directoryToAdd)
//{
//	//std::string tempString = "";
//	//std::vector<std::string> tempDataVector;
//	//bool isDuplicate = false;
//	//
//	////Check if the file exists, if not, make it
//	//m_fileRead.open(fileDirectory);
//	//if (!m_fileRead.is_open())
//	//{
//	//	m_fileWrite.open(fileDirectory);
//	//	if (m_fileWrite.is_open())
//	//	{
//	//		m_fileWrite << "";
//	//	}
//	//	m_fileWrite.close();
//	//}
//	//m_fileRead.close();
//	//
//	//m_fileRead.open(fileDirectory);
//	//if (m_fileRead.is_open())
//	//{
//	//	//Check for duplicate directory
//	//	while (std::getline(m_fileRead, tempString))
//	//	{
//	//		if (tempString == directoryToAdd)
//	//		{
//	//			isDuplicate = true;
//	//		}
//	//	}
//	//
//	//	if (!isDuplicate)
//	//	{
//	//		//Read the file frome the start
//	//		m_fileRead.clear();
//	//		m_fileRead.seekg(0);
//	//
//	//		//Store content of the file
//	//		while (std::getline(m_fileRead, tempString))
//	//		{
//	//			tempDataVector.push_back(tempString);			
//	//		}				
//	//		tempDataVector.push_back(directoryToAdd);
//	//	}
//	//}
//	//m_fileRead.close();
//	//
//	//if (!isDuplicate)
//	//{
//	//	//Save data to file
//	//	m_fileWrite.open(fileDirectory);
//	//	if (m_fileWrite.is_open())
//	//	{
//	//		for (std::string data : tempDataVector)
//	//		{
//	//			m_fileWrite << data <<"\n";
//	//		}
//	//	}
//	//	m_fileWrite.close();
//	//}
//}
//
//FactionData& DataHandlerOLD::getFactionData(const int& factionIndex)
//{
//	return m_factionData[factionIndex];
//}
