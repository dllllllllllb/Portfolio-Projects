//Author: Maciej Dowbor
//Last Accessed: 18/08/2021

#ifndef COMBATAI_H
#define COMBATAI_H

#include <functional>

#include "CombatUnit.h"
#include "TileHandler.h"

//===========================================================================================
//Description: Combat AI that determines what a unit should do
//===========================================================================================
class CombatAI
{
private:
	TileHandler& m_tileHandler;

	int m_tileSize;
	int m_unitIndexToInteractWith;
	int m_tileIndexToInteractWith;

	bool m_isAIAttacker;
	bool m_canUnitsInteract;

	std::vector<std::unique_ptr<CombatUnit>>& m_pCombatUnits;
	std::vector<int> m_enemyUnitIndexes;
	std::vector<int>* m_pTilesWithinMovementRange;

	std::function<void()> m_attackFunction;
	std::function<void()> m_defendFunction;
	std::function<void()> m_waitFunction;
	std::function<void(const int)> m_moveFunction;
	

public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	CombatAI(TileHandler& rTileHandler, std::vector<std::unique_ptr<CombatUnit>>& rCombatUnits);
	
	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~CombatAI();

	//===========================================================================================
	//Description: Sets neccessary variables for the combat handler to function
	//===========================================================================================
	void setUpCombatAIVariables(const int& tileSize, std::vector<int>* pTilesWithinMovementRange, std::function<void()> attackFunction, std::function<void()> defendFunction, std::function<void()> waitFunction, std::function<void(const int)> moveFunction);
	
	//===========================================================================================
	//Description: Determines which side the AI is on and identifies its enemies
	//===========================================================================================
	void setAIParameters(const bool isAttacker);

	//===========================================================================================
	//Description: Loops through all combat units, indentifies enemies that are still alive and 
	//			   stores their index
	//===========================================================================================
	void updateEnemyUnits();

	//===========================================================================================
	//Description: Returns a bool based on whether the two units are next to eachother
	//===========================================================================================
	const bool areUnitsNextToEachother(const int& unitAIndex, const int& unitBIndex);

	//===========================================================================================
	//Description: Compares two position vectors to see if they are next to eachother
	//===========================================================================================
	const bool checkIfObjectsAreNextToEachother(const sf::Vector2f& posA, const sf::Vector2f& posB);

	//===========================================================================================
	//Description: Checks if units movement path is valid
	//===========================================================================================
	const bool checkIfPathIsValid(const int& endTile, const CombatUnit& unit);

	//===========================================================================================
	//Description: Determines what the current unit should do based on it's position, stats and
	//			   enemies
	//===========================================================================================
	void takeTurn(const int& currentUnitTurnIndex);

	//===========================================================================================
	//Description: Returns index of unit that will be interacted with
	//===========================================================================================
	const int& getUnitIndexToInteractWith() const;

	//===========================================================================================
	//Description: Returns a bool if current unit can interact with another unit
	//===========================================================================================
	const bool getCanUnitsInteract() const;

	//===========================================================================================
	//Description: Returns index of tile that the unit will interact with
	//===========================================================================================
	const int& getTileIndexToInteractWith() const;

	//===========================================================================================
	//Description: Calls defend function, used outside of this class as a failsafe if unit cannot
	//			   determine what they could do
	//===========================================================================================
	void defend();
};

#endif // !COMBATAI_H

