#include "CombatCursor.h"

CombatCursor::CombatCursor(std::vector<std::unique_ptr<CombatUnit>>& rCombatUnitsVector, std::vector<int>& rTileIndexesWithinMovementRange) :
	m_combatUnitsVector(rCombatUnitsVector),
	m_tileIndexesThatAreWithinUnitsMovementRange(rTileIndexesWithinMovementRange),
	m_pTileHandler(nullptr),
	m_tileSize(0),
	m_halfTileSize(0),
	m_cursorSize(0)
{
}

CombatCursor::~CombatCursor()
{
}

void CombatCursor::setUpMouseCursor(const sf::Texture& texture, const int& tileSize)
{
	m_tileSize = tileSize;
	m_halfTileSize = m_tileSize * 0.5f;
	setScale(1.5f, 1.5f);
	setTexture(texture, true);
	m_cursorSize = texture.getSize().y;
	setOrigin(m_cursorSize * 0.5f, m_cursorSize * 0.5f);
	setTextureRect(sf::IntRect(0, 0, m_cursorSize, m_cursorSize));
}

void CombatCursor::update(const sf::Vector2f& mousePosition, const int& currentUnitTurnIndex)
{
	setPosition(mousePosition);

	if (abs(mousePosition.x - m_previousCursorPosition.x) > m_halfTileSize || abs(mousePosition.y - m_previousCursorPosition.y) > m_halfTileSize) //Checks if mouse was moved to a different tile
	{
		int tileIndex = m_pTileHandler->checkTileCollision(mousePosition); //Returns tile index, if invalid it will return -1

		if (tileIndex > -1) //Makes sure that the index is valid
		{
			updateCursor(mousePosition, tileIndex, currentUnitTurnIndex);
		}
		else
		{
			setTextureRect(sf::IntRect(0, 0, m_cursorSize, m_cursorSize)); //If tile index is invalid, change to inaccessible cursor sprite
		}
	}
}

void CombatCursor::updateCursor(const sf::Vector2f& mousePosition, const int& tileIndex, const int& currentUnitTurnIndex)
{
	Tile* tile = m_pTileHandler->getTile(tileIndex);

	bool isTileWithinMovementRange = false;

	m_previousCursorPosition = tile->getPosition();
	m_previousCursorPosition.x += m_halfTileSize;
	m_previousCursorPosition.y += m_halfTileSize;

	//Check if tile is within movement range
	for (int& tileRangeIndex : m_tileIndexesThatAreWithinUnitsMovementRange)
	{
		if (tileRangeIndex == tileIndex)
		{
			isTileWithinMovementRange = true;
			break;
		}
	}

	//Check if there is a unit on this tile
	if (tile->getIsOccupied())
	{
		//Check if unit is an enemy
		if (m_combatUnitsVector[tile->getMapObjectVectorIndex()]->getIsAttacker() != m_combatUnitsVector[currentUnitTurnIndex]->getIsAttacker())
		{
			if (!isTileWithinMovementRange && !m_combatUnitsVector[currentUnitTurnIndex]->getBaseUnitData()->getIntData(UnitDataEnum::isRanged))
			{
				for (int& tileRangeIndex : m_tileIndexesThatAreWithinUnitsMovementRange)
				{
					if (checkIfTilesAreNextToEachother(tile->getPosition(), m_pTileHandler->getTile(tileRangeIndex)->getPosition()))
					{
						isTileWithinMovementRange = true;
						break;
					}
				}
			}

			//Set cursor to arrow
			if (m_combatUnitsVector[currentUnitTurnIndex]->getBaseUnitData()->getIntData(UnitDataEnum::isRanged))
			{
				setCursor(CombatCursorEnum::rangedAttack);
			}
			else if (isTileWithinMovementRange)
			{
				setCursor(CombatCursorEnum::attack);
			}
			else
			{
				setCursor(CombatCursorEnum::none);
			}
		}
		else if (isTileWithinMovementRange && tileIndex != m_combatUnitsVector[currentUnitTurnIndex]->getOccupiedTileIndex() && tile->getMapObjectVectorIndex() == currentUnitTurnIndex)
		{
			setCursor(CombatCursorEnum::move);
		}
		else
		{
			setCursor(CombatCursorEnum::none);
		}
	}
	else if (isTileWithinMovementRange)
	{
		setCursor(CombatCursorEnum::move);
	}
	else
	{
		setCursor(CombatCursorEnum::none);
	}
}

void CombatCursor::setCursor(const CombatCursorEnum& cursorType)
{
	setTextureRect(sf::IntRect(static_cast<int>(cursorType) * m_cursorSize, 0, m_cursorSize, m_cursorSize));
}

const bool CombatCursor::checkIfTilesAreNextToEachother(const sf::Vector2f& positionA, const sf::Vector2f& positionB)
{
	return (abs(positionA.x - positionB.x) <= m_tileSize && abs(positionA.y - positionB.y) <= m_tileSize);
}

void CombatCursor::setTileHandler(TileHandler* pTileHandler)
{
	m_pTileHandler = pTileHandler;
}

const sf::Vector2f& CombatCursor::getPreviousCursorPosition() const
{
	return m_previousCursorPosition;
}