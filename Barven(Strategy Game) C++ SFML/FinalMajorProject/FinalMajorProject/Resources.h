//Author: Maciej Dowbor
//Last Accessed: 14/07/2021

#ifndef RESOURCES_H
#define RESOURCES_H

#include "ResourcesEnum.h"

//===========================================================================================
//Description: Stores resources data
//===========================================================================================
class Resources
{
private:
	int m_gold;
	int m_wood;
	int m_stone;

public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	Resources();

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~Resources();

	//===========================================================================================
	//Description: Increments specified resource by passed value
	//===========================================================================================
	void incrementResourceValue(const ResourcesEnum& resourceType, const int& value);

	//===========================================================================================
	//Description: Returns resource value
	//===========================================================================================
	const int& getResource(const ResourcesEnum& resourceType) const;
};

#endif // !RESOURCES_H

