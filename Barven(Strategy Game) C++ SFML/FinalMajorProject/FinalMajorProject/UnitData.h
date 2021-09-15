//Author: Maciej Dowbor
//Last Accessed: 02/09/2021
#ifndef UNITDATA_H
#define UNITDATA_H

#include <SFML/Graphics/Texture.hpp>
#include "json.hpp"

#include "ConstantVariables.h"
#include "UnitDataEnum.h"
#include "UnitSpecialPropertyEnum.h"

using json = nlohmann::json;

//===========================================================================================
//Description: Data container for base unit data
//===========================================================================================
class UnitData
{
protected:
	int m_index;
	int m_health;
	int m_attack;
	int m_minDamage;
	int m_maxDamage;
	int m_isRanged;
	int m_ammunition;
	int m_range;
	int m_defence;
	int m_isFlying;
	int m_speed;
	int m_growthPerWeek;
	int m_cost;
	int m_AIValue;

	std::string m_spriteFilePath;
	std::string m_unitName;
	std::string m_iconFilePath;
	std::string m_faction;
	std::string m_unitMapSpriteFilePath;

	sf::Texture m_unitSprite;
	sf::Texture m_unitIcon;
	sf::Texture m_unitMapSprite;

	UnitSpecialPropertyEnum m_specialProperty;

public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	UnitData();

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~UnitData();

	//===========================================================================================
	//Description: Returns special property
	//===========================================================================================
	const UnitSpecialPropertyEnum& getSpecialProperty() const;

	//===========================================================================================
	//Description: Returns sprite texture
	//===========================================================================================
	const sf::Texture& getUnitSprite() const;

	//===========================================================================================
	//Description: Returns icon texture
	//===========================================================================================
	const sf::Texture& getUnitIcon() const;

	//===========================================================================================
	//Description: Returns unit map sprite
	//===========================================================================================
	const sf::Texture& getUnitMapSprite() const;

	//===========================================================================================
	//Description: Returns a pointer to this unit data object
	//===========================================================================================
	const UnitData* getUnitData() const;

	//===========================================================================================
	//Description: Loads textures
	//===========================================================================================
	void loadTextures();

	//===========================================================================================
	//Description: Loads JSON into standard variables to reduce memory usage during run time
	//===========================================================================================
	void loadJSONData(const json& JSONData);

	//===========================================================================================
	//Description: sets data
	//===========================================================================================
	template<typename variableType>
	void setData(const UnitDataEnum unitData, const variableType& value);

	//===========================================================================================
	//Description: Returns int data
	//===========================================================================================
	const int& getIntData(const UnitDataEnum unitData) const;

	//===========================================================================================
	//Description: Returns unit battle data
	//===========================================================================================
	const int& getBattleData(const UnitBattleDataEnum& unitBattleData) const;

	//===========================================================================================
	//Description: Returns string data
	//===========================================================================================
	const std::string& getStringData(const UnitDataEnum unitData) const;
};

#endif // !UNITDATA_H
