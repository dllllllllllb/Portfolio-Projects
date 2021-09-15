//Author: Maciej Dowbor
//Last Accessed: 30/08/2021

#ifndef HERO_H
#define HERO_H

#include "Unit.h"
#include "HeroStatsEnum.h"
#include "HeroSettings.h"
#include "ConstantVariables.h"
#include "DataHandler.h"
#include "MoveableObject.h"

//===========================================================================================
//Description: Controlled by player, holds hero stats and units. Used to interact with the map
//===========================================================================================
class Hero : public MoveableObject
{
private:
	int m_playerIndex;
	int m_occupiedTileIndex;

	int m_currentNumberOfUnits;
	std::vector<std::shared_ptr<Unit>> m_heroUnits;
	std::vector<int> m_indexesOfVisitedSpecialBuildings;

	//Hero Movement Variables
	int m_currentMovementPoints;

	//Hero Stats
	int m_heroLevel;
	int m_statAttack;
	int m_statDefence;
	int m_statMagicPower;
	int m_statWisdom;

public:

	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	Hero();

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~Hero();

	//===========================================================================================
	//Description: Returns unit in the vector based on index passed
	//===========================================================================================
	Unit& getUnit(const int& index);

	//===========================================================================================
	//Description: Returns a vector of all units owned by this hero
	//===========================================================================================
	std::vector<std::shared_ptr<Unit>>& getVectorOfUnits();

	//===========================================================================================
	//Description: Returns a vector of special building that were visited
	//===========================================================================================
	std::vector<int>& getVectorOfVisitedSpecialBuildingsIndexes();

	//===========================================================================================
	//Description: Sets heros textures and starting position on the map
	//===========================================================================================
	void setUpHero(sf::Texture& heroSprite, const sf::Vector2f& startPosition);

	//===========================================================================================
	//Description: Adds a unit to Heros army
	//===========================================================================================
	void addUnit(const int& vectorIndex, UnitData* unitToAdd);

	//===========================================================================================
	//Description: Deletes unit from passed vector index
	//===========================================================================================
	void deleteUnit(const int& vectorIndex);

	//===========================================================================================
	//Description: Swaps units position in the unit vector
	//===========================================================================================
	void swapUnitsPositionsInVector(const int& unitIndexA, const int& unitIndexB);

	//===========================================================================================
	//Description: Updates number of units currently owned by the hero
	//===========================================================================================
	void updateNumberOfUnits();

	//===========================================================================================
	//Description: Updates units individual stats based on Heroes stats (Heroes buff all their units)
	//===========================================================================================
	void updateUnitsStats();

	//===========================================================================================
	//Description: Increment heros level
	//===========================================================================================
	void incrementHeroLevel();

	//===========================================================================================
	//Description: Return heros level
	//===========================================================================================
	const int& getHeroLevel() const;

	//===========================================================================================
	//Description: Decrement current movement points
	//===========================================================================================
	void decrementMovementPoints(const int& decrementValue);

	//===========================================================================================
	//Description: Set current movement points
	//===========================================================================================
	void setCurrentMovementPoints(const int& movementPoints);

	//===========================================================================================
	//Description: Reset movement points to max
	//===========================================================================================
	void resetMovementPoints();

	//===========================================================================================
	//Description: Returns current movement points
	//===========================================================================================
	const int& getCurrentMovementPoints() const;

	//===========================================================================================
	//Description: Increments Heroes stats
	//===========================================================================================
	void incrementHeroStat(const HeroStatsEnum& heroStatType, const int& incrementValue);

	//===========================================================================================
	//Description: Returns value of hero stat
	//===========================================================================================
	const int& getHeroStat(const HeroStatsEnum& heroStatType);

	//===========================================================================================
	//Description: Update hero
	//===========================================================================================
	void update(const float& deltaTime);

	//===========================================================================================
	//Description: Returns current number of units in heroes army
	//===========================================================================================
	const int& getCurrentNumberOfUnits() const;

	//===========================================================================================
	//Description: Sets player index that owns this hero
	//===========================================================================================
	void setPlayerIndex(const int& playerIndex);

	//===========================================================================================
	//Description: Returns player index that owns this hero
	//===========================================================================================
	const int& getPlayerIndex() const;

	//===========================================================================================
	//Description: Sets index of the tile the hero is on
	//===========================================================================================
	void setOccupiedTileIndex(const int& tileIndex);

	//===========================================================================================
	//Description: Returns the index of tile the hero is on
	//===========================================================================================
	const int& getOccupiedTileIndex() const;
};

#endif // !HERO_H
