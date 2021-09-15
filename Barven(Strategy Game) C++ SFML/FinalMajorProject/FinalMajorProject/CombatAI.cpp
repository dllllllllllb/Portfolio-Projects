#include "CombatAI.h"

CombatAI::CombatAI(TileHandler& rTileHandler, std::vector<std::unique_ptr<CombatUnit>>& rCombatUnits) :
	m_tileHandler(rTileHandler),
	m_tileSize(64),
	m_unitIndexToInteractWith(0),
	m_tileIndexToInteractWith(0),
	m_isAIAttacker(false),
	m_canUnitsInteract(false),
	m_pCombatUnits(rCombatUnits),
	m_pTilesWithinMovementRange(nullptr)
{

}

CombatAI::~CombatAI()
{
}

void CombatAI::setUpCombatAIVariables(const int& tileSize, std::vector<int>* pTilesWithinMovementRange, std::function<void()> attackFunction, std::function<void()> defendFunction, std::function<void()> waitFunction, std::function<void(const int)> moveFunction)
{
	m_tileSize = tileSize;
	m_pTilesWithinMovementRange = pTilesWithinMovementRange;
	m_attackFunction = attackFunction;
	m_defendFunction = defendFunction;
	m_waitFunction = waitFunction;
	m_moveFunction = moveFunction;
}

void CombatAI::setAIParameters(const bool isAttacker)
{
	m_isAIAttacker = isAttacker;
	updateEnemyUnits();
}

void CombatAI::updateEnemyUnits()
{
	m_enemyUnitIndexes.clear();
	int unitIndexCounter = 0;
	std::list<int> enemyUnitIndexes;

	//Get all enemy unit indexes that are still alive
	for (auto& unit : m_pCombatUnits)
	{
		if (unit->getIsAttacker() != m_isAIAttacker && unit->getNumOfUnits() > 0)
		{
			enemyUnitIndexes.push_back(unitIndexCounter);
		}
		unitIndexCounter++;
	}

	//Sort them in descending order based on unit type index
	for (int& unitIndex : enemyUnitIndexes)
	{
		bool wasEnemyUnitAdded = false;
		if (!m_enemyUnitIndexes.size())
		{
			m_enemyUnitIndexes.push_back(unitIndex);
		}
		else
		{
			for (int i = 0; i < m_enemyUnitIndexes.size(); i++)
			{
				wasEnemyUnitAdded = false;
				if (m_pCombatUnits[unitIndex]->getBaseUnitData()->getIntData(UnitDataEnum::index) > m_pCombatUnits[m_enemyUnitIndexes[i]]->getBaseUnitData()->getIntData(UnitDataEnum::index))
				{
					m_enemyUnitIndexes.insert(m_enemyUnitIndexes.begin() + i, unitIndex);
					wasEnemyUnitAdded = true;
					break;
				}
			}

			if (!wasEnemyUnitAdded)
			{
				m_enemyUnitIndexes.push_back(unitIndex);
			}
		}
	}
}

const bool CombatAI::areUnitsNextToEachother(const int& unitAIndex, const int& unitBIndex)
{
	bool areUnitsNextToEachother = false;
	CombatUnit& unitA = *m_pCombatUnits[unitAIndex];
	CombatUnit& unitB = *m_pCombatUnits[unitBIndex];

	areUnitsNextToEachother = checkIfObjectsAreNextToEachother(unitA.getPosition(), unitB.getPosition());

	if (!areUnitsNextToEachother && (unitA.getIsLargeUnit() || unitB.getIsLargeUnit())) //If units aren't next to eachother, check if one of the units is large and check again using different parameters
	{
		std::list<sf::Vector2f> unitAPositions;
		std::list<sf::Vector2f> unitBPositions;

		for (int i = 0; i < m_tileHandler.getNumOfHorizontalTiles() * m_tileHandler.getNumOfVerticalTiles(); i++) //Loop through all tiles
		{
			Tile& tile = *m_tileHandler.getTile(i);
			if (tile.getIsOccupied()) //Check if the tile is occupied and see if object index matches one of the units
			{
				int unitVectorIndex = tile.getMapObjectVectorIndex();

				if (unitVectorIndex == unitAIndex)
				{
					unitAPositions.push_back(tile.getPosition());
				}
				else if (unitVectorIndex == unitBIndex)
				{
					unitBPositions.push_back(tile.getPosition());
				}
			}
		}

		for (sf::Vector2f& posA : unitAPositions) //Loop through all occupied tiles and see if any of them are next to eachother
		{
			for (sf::Vector2f& posB : unitBPositions)
			{
				if (checkIfObjectsAreNextToEachother(posA, posB))
				{
					areUnitsNextToEachother = true;
					break;
				}
			}
		}
	}

	return areUnitsNextToEachother;
}

const bool CombatAI::checkIfObjectsAreNextToEachother(const sf::Vector2f& posA, const sf::Vector2f& posB)
{
	return (abs(posA.x - posB.x) <= m_tileSize && abs(posA.y - posB.y) <= m_tileSize);
}

const bool CombatAI::checkIfPathIsValid(const int& endTile, const CombatUnit& unit)
{
	bool isPathValid = false;
	int unitStartTileIndex = unit.getOccupiedTileIndex();
	int largeUnittileIndexToIgnore = unitStartTileIndex;

	//Sets start and end tile in tile handler to find path
	m_tileHandler.setTileProperty(unitStartTileIndex, TilePropertiesEnum::start);
	m_tileHandler.setTileProperty(endTile, TilePropertiesEnum::end);

	if (unit.getIsLargeUnit()) //Gets rid of tile collision for large units for smooth path finding
	{
		if (unit.getIsAttacker())
		{
			largeUnittileIndexToIgnore--;
		}
		else
		{
			largeUnittileIndexToIgnore++;
		}
		m_tileHandler.getTile(unitStartTileIndex)->setIsObstacle(false);
		m_tileHandler.getTile(largeUnittileIndexToIgnore)->setIsObstacle(false);

		m_tileHandler.fintPathForALargeUnit(unit.getIsAttacker());
	}
	else
	{
		m_tileHandler.findPath();
	}

	if (m_tileHandler.getTile(endTile)->getParentTile() != nullptr) //If end tile does't have a parent tile it means that no path was found
	{
		isPathValid = true;
	}

	//Sets back tile properties
	m_tileHandler.getTile(unitStartTileIndex)->setIsObstacle(true);
	if (unit.getIsLargeUnit())
	{
		m_tileHandler.getTile(largeUnittileIndexToIgnore)->setIsObstacle(true);
	}

	return isPathValid;
}

void CombatAI::takeTurn(const int& currentUnitTurnIndex)
{
	updateEnemyUnits();
	m_canUnitsInteract = false;
	bool didUnitMakeAMove = false;

	CombatUnit& currentUnit = *m_pCombatUnits[currentUnitTurnIndex];
	int minimumDamageToDeal = currentUnit.getBaseUnitData()->getIntData(UnitDataEnum::minDamage) * currentUnit.getNumOfUnits();


	//Check if unit is ranged
	if (currentUnit.getBaseUnitData()->getIntData(UnitDataEnum::isRanged))
	{
		//Check if enemy is next to you
		for (int& enemyUnitIndex : m_enemyUnitIndexes)
		{
			if (areUnitsNextToEachother(currentUnitTurnIndex, enemyUnitIndex))
			{
				//Attack enemy next to you
				m_unitIndexToInteractWith = enemyUnitIndex;
				m_canUnitsInteract = true;
				m_attackFunction();
				didUnitMakeAMove = true;
				break;
			}
		}

		//Check if enemy have a ranged unit
		if (!didUnitMakeAMove)
		{
			for (int& enemyUnitIndex : m_enemyUnitIndexes)
			{
				if (m_pCombatUnits[enemyUnitIndex]->getBaseUnitData()->getIntData(UnitDataEnum::isRanged))
				{	
					//Attack ranged unit
					m_unitIndexToInteractWith = enemyUnitIndex;
					m_canUnitsInteract = true;
					m_attackFunction();
					didUnitMakeAMove = true;
					break;
				}
			}
		}

		if (!didUnitMakeAMove)
		{
			for (int& enemyUnitIndex : m_enemyUnitIndexes) //Loop through enemies and see who you could kill at least 1 enemy unit (since units are ordered from high tier to low tier, strongest unit will be prioritised)
			{
				if (m_pCombatUnits[enemyUnitIndex]->getCurrentHealth() <= minimumDamageToDeal)
				{
					if (m_pCombatUnits[enemyUnitIndex]->getNumOfUnits() + 1 >= minimumDamageToDeal / m_pCombatUnits[enemyUnitIndex]->getBaseUnitData()->getIntData(UnitDataEnum::health))
					{
						m_unitIndexToInteractWith = enemyUnitIndex;
						m_canUnitsInteract = true;
						m_attackFunction();
						didUnitMakeAMove = true;
						break;
					}
				}
			}

			if (!didUnitMakeAMove) //If no move was made, attack the lowest tier unit
			{
				if (m_enemyUnitIndexes.size())
				{
					m_unitIndexToInteractWith = m_enemyUnitIndexes[m_enemyUnitIndexes.size() - 1];
					m_canUnitsInteract = true;
					m_attackFunction();
					didUnitMakeAMove = true;
				}
			}
		}
	}
	else 
	{
		//Check if enemy units are in range and add them to the list
		std::list<std::pair<int,int>> enemyUnitsIndexInRange; //first == unit index, second == tile index
		for (int& tileIndex : *m_pTilesWithinMovementRange)
		{
			Tile& tile = *m_tileHandler.getTile(tileIndex);
			if (tile.getIsOccupied())
			{
				int unitVectorIndex = tile.getMapObjectVectorIndex();
				if (m_pCombatUnits[unitVectorIndex]->getIsAttacker() != m_isAIAttacker) //Check if unit is on the opposite "team"
				{
					bool isDuplicate = false;
					for (auto& enemyIndex : enemyUnitsIndexInRange)
					{
						if (enemyIndex.first == unitVectorIndex) //Check if unit is a duplicate
						{
							isDuplicate = true;
							break;
						}
					}
					if (!isDuplicate) //If unit is not a duplicate, add it to the list
					{
						enemyUnitsIndexInRange.push_back(std::pair<int, int>(unitVectorIndex, tileIndex));
					}
				}

			}
			else //If tile is not occupied, check surrounding tiles as enemy can be attacked if it's next to the max movement range tile
			{
				for (Tile* neighbourTile : tile.getSurroundingTilesVector())
				{
					if (neighbourTile->getIsOccupied())
					{
						int unitVectorIndex = neighbourTile->getMapObjectVectorIndex();
						if (m_pCombatUnits[unitVectorIndex]->getIsAttacker() != m_isAIAttacker)
						{
							bool isDuplicate = false;
							for (auto& enemyIndex : enemyUnitsIndexInRange)
							{
								if (enemyIndex.first == unitVectorIndex)
								{
									isDuplicate = true;
									break;
								}
							}
			
							if (!isDuplicate)
							{
								enemyUnitsIndexInRange.push_back(std::pair<int, int>(unitVectorIndex, neighbourTile->getTileVectorIndex()));
							}
						}
					}
				}
			}
		}

		//Attack
		if (enemyUnitsIndexInRange.size()) //If there is at least 1 unit within movement range, attack
		{
			m_canUnitsInteract = true;
			
			//Check if unit is next to an enemy
			for (auto& enemyUnitIndex : enemyUnitsIndexInRange)
			{
				if (areUnitsNextToEachother(currentUnitTurnIndex, enemyUnitIndex.first))
				{
					m_unitIndexToInteractWith = enemyUnitIndex.first; //attack
					m_attackFunction();
					didUnitMakeAMove = true;
				}
			}

			if (!didUnitMakeAMove)
			{
				//Determine which unit to attack to deal the most damage to the enemy
				int enemyIndexThatTakesMostDamage = 0;
				int maxNumberOfUnitsThatWillPerish = 0;

				for (auto& enemyInRangeIndex : enemyUnitsIndexInRange) //Loop through enemies in range
				{
					int tempMinimumDamageToDeal = minimumDamageToDeal;
					int numberOfUnitsThatWillPerish = 0;

					if (m_pCombatUnits[enemyInRangeIndex.first]->getCurrentHealth() - tempMinimumDamageToDeal < 1) //Check if at least 1 unit will be killed
					{
						tempMinimumDamageToDeal -= m_pCombatUnits[enemyInRangeIndex.first]->getCurrentHealth(); //Updates left over damage
						numberOfUnitsThatWillPerish++;
					}

					if (tempMinimumDamageToDeal > 0) //If there is still damage to deal
					{
						numberOfUnitsThatWillPerish += m_pCombatUnits[enemyInRangeIndex.first]->getBaseUnitData()->getIntData(UnitDataEnum::health) / tempMinimumDamageToDeal; //add number of units that would perish with remainder damage
					}

					if (m_pCombatUnits[enemyInRangeIndex.first]->getNumOfUnits() < numberOfUnitsThatWillPerish) //See how many units are actually there to kill and adjust number of units that will perish
					{
						numberOfUnitsThatWillPerish = m_pCombatUnits[enemyInRangeIndex.first]->getNumOfUnits();
					}

					if (numberOfUnitsThatWillPerish > maxNumberOfUnitsThatWillPerish) //Compare max units perished with currently analized unit
					{
						maxNumberOfUnitsThatWillPerish = numberOfUnitsThatWillPerish;
						enemyIndexThatTakesMostDamage = enemyInRangeIndex.first;
						m_tileIndexToInteractWith = enemyInRangeIndex.second;
					}
				}

				m_unitIndexToInteractWith = enemyIndexThatTakesMostDamage; //Once the loop is over set unit index to interact with

				//Check if units are next to eachother
				if (areUnitsNextToEachother(currentUnitTurnIndex, enemyIndexThatTakesMostDamage)) //Check if the units are next to eachother
				{
					m_attackFunction();
					didUnitMakeAMove = true;
				}
				else
				{
					//Check if unit can get to the one it wants to attack
					if (checkIfPathIsValid(m_tileIndexToInteractWith, currentUnit)) //Check if there is a valid path
					{
						m_moveFunction(m_tileIndexToInteractWith);
						didUnitMakeAMove = true;
					}
					else //If it cant, try other enemies that are within range
					{
						for (auto& enemyUnit : enemyUnitsIndexInRange)
						{
							if (checkIfPathIsValid(enemyUnit.second, currentUnit))
							{
								m_unitIndexToInteractWith = enemyUnit.first;
								m_moveFunction(enemyUnit.second);
								didUnitMakeAMove = true;
								break;
							}
						}
					}
				}
			}
			
		}
		else if(!currentUnit.getDidUnitSkipTurn())//If unit can't attack and hasn't skipped it's turn yet, Skip turn
		{
			m_waitFunction();
			didUnitMakeAMove = true;
		}
		else //Move
		{
			int closestEnemyUnitIndex = 0;
			int distanceToClosestUnit = 999;

			for (int& enemyUnitIndex : m_enemyUnitIndexes) //Find closest enemy
			{
				int xDistance = abs(currentUnit.getPosition().x - m_pCombatUnits[enemyUnitIndex]->getPosition().x) / m_tileSize;
				int yDistance = abs(currentUnit.getPosition().y - m_pCombatUnits[enemyUnitIndex]->getPosition().y) / m_tileSize;

				int distanceToCompare = xDistance + yDistance;

				if (distanceToCompare < distanceToClosestUnit)
				{
					distanceToClosestUnit = distanceToCompare;
					closestEnemyUnitIndex = enemyUnitIndex;
				}
			}

			//Find closest tile to target enemy that isn't an obstacle
			int closestDistanceTileIndex = 0;
			int distanceBetweenTileAndEnemyUnit = 999;
			bool wasTileFound = false;
			for (int& tileIndex : *m_pTilesWithinMovementRange)
			{
				if (!m_tileHandler.getTile(tileIndex)->getIsObstacle())
				{
					int xDistance = abs(m_pCombatUnits[closestEnemyUnitIndex]->getPosition().x - m_tileHandler.getTile(tileIndex)->getPosition().x) / m_tileSize;
					int yDistance = abs(m_pCombatUnits[closestEnemyUnitIndex]->getPosition().y - m_tileHandler.getTile(tileIndex)->getPosition().y) / m_tileSize;

					int distanceToCompare = xDistance + yDistance;

					if (distanceToCompare < distanceBetweenTileAndEnemyUnit)
					{
						closestDistanceTileIndex = tileIndex;
						distanceBetweenTileAndEnemyUnit = distanceToCompare;
						wasTileFound = true;
					}
				}
			}

			if (wasTileFound)
			{
				if (checkIfPathIsValid(closestDistanceTileIndex, currentUnit))
				{
					m_moveFunction(closestDistanceTileIndex);
					didUnitMakeAMove = true;
				}
			}
			else
			{
				int tileIndexToMoveTo = 0;
				//If a path can't be found, have 10 tries to move to a random tile (adds unpredictability and opens up different options after the move is made)
				for (int i = 0; i < 10; i++)
				{
					int rng = rand() % m_pTilesWithinMovementRange->size();
					tileIndexToMoveTo = m_pTilesWithinMovementRange->at(rng);

					if (m_tileHandler.getTile(tileIndexToMoveTo)->getIsObstacle() && checkIfPathIsValid(tileIndexToMoveTo, currentUnit))
					{
						m_moveFunction(tileIndexToMoveTo);
						didUnitMakeAMove = true;
						break;
					}
				}
			}
		}
	}

	if (!didUnitMakeAMove) //If no move was made, defend
	{
		m_defendFunction();
	}
}

const int& CombatAI::getUnitIndexToInteractWith() const
{
	return m_unitIndexToInteractWith;
}

const bool CombatAI::getCanUnitsInteract() const
{
	return m_canUnitsInteract;
}

const int& CombatAI::getTileIndexToInteractWith() const
{
	return m_tileIndexToInteractWith;
}

void CombatAI::defend()
{
	m_defendFunction();
}
