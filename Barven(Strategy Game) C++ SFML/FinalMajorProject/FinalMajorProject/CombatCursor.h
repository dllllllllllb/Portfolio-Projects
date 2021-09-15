//Author: Maciej Dowbor
//Last Accessed: 02/08/2021

#ifndef COMBATCURSOR_H
#define COMBATCURSOR_H

#include "SFML/Graphics/Sprite.hpp"
#include "TileHandler.h"
#include "CombatUnit.h"
#include "CombatCursorEnum.h"

//===========================================================================================
//Description: Cursor for player feedback to show what action is available
//===========================================================================================
class CombatCursor : public sf::Sprite
{
private:
	TileHandler* m_pTileHandler;
	sf::Vector2f m_previousCursorPosition; // 0,0 by default

	std::vector<std::unique_ptr<CombatUnit>>& m_combatUnitsVector;
	std::vector<int>& m_tileIndexesThatAreWithinUnitsMovementRange;

	int m_tileSize;
	int m_halfTileSize;
	int m_cursorSize;

public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	CombatCursor(std::vector<std::unique_ptr<CombatUnit>>& rCombatUnitsVector, std::vector<int>& rTileIndexesWithinMovementRange);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~CombatCursor();

	//===========================================================================================
	//Description: Sets up default cursor parameters and texture
	//===========================================================================================
	void setUpMouseCursor(const sf::Texture& texture, const int& tileSize);

	//===========================================================================================
	//Description: Checks if mouse cursor moved to a different tile to determine if it needs to
	//			   be updated
	//===========================================================================================
	void update(const sf::Vector2f& mousePosition, const int& currentUnitTurnIndex);

	//===========================================================================================
	//Description: Updates mouse cursor based on tile properties that the mouse hovers
	//===========================================================================================
	void updateCursor(const sf::Vector2f& mousePosition, const int& tileIndex, const int& currentUnitTurnIndex);

	//===========================================================================================
	//Description: Sets cursors texture rectangle to display appropriate icon
	//===========================================================================================
	void setCursor(const CombatCursorEnum& cursorType);

	//===========================================================================================
	//Description: Checks if tiles are next to eachother
	//===========================================================================================
	const bool checkIfTilesAreNextToEachother(const sf::Vector2f& positionA, const sf::Vector2f& positionB);

	//===========================================================================================
	//Description: Sets a pointer to a tile handler
	//===========================================================================================
	void setTileHandler(TileHandler* pTileHandler);

	//===========================================================================================
	//Description: Returns previous cursor position
	//===========================================================================================
	const sf::Vector2f& getPreviousCursorPosition() const;
};

#endif // !COMBATCURSOR_H
