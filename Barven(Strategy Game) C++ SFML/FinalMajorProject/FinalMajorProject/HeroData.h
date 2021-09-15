//Author: Maciej Dowbor
//Last Accessed: 23/06/2021

#ifndef HERODATA_H
#define HERODATA_H

#include "SFML/Graphics/Texture.hpp"
#include "HeroStatsEnum.h"

//===========================================================================================
//Description: Data container for Heroes, stores base stats, sprites etc.
//===========================================================================================
class HeroData
{
private:
	int m_baseAttack;
	int m_baseDefence;
	int m_baseMagicPower;
	int m_baseWisdom;

	sf::Texture m_heroMapTexture;

public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	HeroData();

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~HeroData();

	//===========================================================================================
	//Description: Sets hero base stats
	//===========================================================================================
	void setHeroBaseStat(const HeroStatsEnum& heroStat, const int& statValue);

	//===========================================================================================
	//Description: Returns hero stat
	//===========================================================================================
	const int& getHeroStat(const HeroStatsEnum& heroStat) const;

	//===========================================================================================
	//Description: Loads texture from file
	//===========================================================================================
	void loadHeroTexture();

	//===========================================================================================
	//Description: Returns hero texture
	//===========================================================================================
	sf::Texture& getHeroTexture();
};

#endif // !HERODATA_H
