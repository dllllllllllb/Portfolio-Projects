//Author: Maciej Dowbor
//Last Accessed: 17/05/2021

#ifndef UNITMAPOBJECT_H
#define UNITMAPOBJECT_H

#include "MapObject.h"
//===========================================================================================
//Description: Unit mnap object
//===========================================================================================
class UnitMapObject : public MapObject
{
private:
	int m_numOfUnits;
	int m_factionIndex;
	int m_unitIndex;
public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	UnitMapObject();

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~UnitMapObject();

	//===========================================================================================
	//Description: Sets up objects position and texture
	//===========================================================================================
	void setUp(const sf::Vector2f& position, const sf::Texture& texture);

	//===========================================================================================
	//Description: Sets number of units
	//===========================================================================================
	void setNumberOfUnits(const int& numOfUnits);

	//===========================================================================================
	//Description: Returns number of units
	//===========================================================================================
	const int& getNumberOfUnits()const;

	//===========================================================================================
	//Description: Sets faction index
	//===========================================================================================
	void setFactionIndex(const int& factionIndex);

	//===========================================================================================
	//Description: Returns faction index
	//===========================================================================================
	const int& getFactionIndex() const;

	//===========================================================================================
	//Description: Sets unit index
	//===========================================================================================
	void setUnitIndex(const int& unitIndex);

	//===========================================================================================
	//Description: Returns unit index
	//===========================================================================================
	const int& getUnitIndex() const;

	//===========================================================================================
	//Description: Robust way of setting variables, made with expansion in mind.
	//			   Used by map object editor window
	//===========================================================================================
	void setVariable(const MapObjectDataEnum::Units& variable, const int& value);

	//===========================================================================================
	//Description: Robust way of setting variables, made with expansion in mind.
	//			   Used by map object editor window
	//===========================================================================================
	const int& getVariable(const MapObjectDataEnum::Units& variable) const;
};

#endif // !UNITMAPOBJECT_H
