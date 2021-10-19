//Author: Maciej Dowbor
//Last Accessed: 02/08/2021

#ifndef TILEHANDLER_H
#define TILEHANDLER_H

#include <math.h>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Macros.h"
#include "Textures.h"
#include "Tile.h"
#include "TilePropertiesEnum.h"
//===========================================================================================
//Description: Handles tiles and path finding
//===========================================================================================
class TileHandler
{
private:
	sf::RenderWindow& m_window;
	Textures& m_textures;

	bool m_isTestingTiles;
	bool m_isCombatTiles;
	int m_numOfTiles;
	int m_numOfHorizontalTiles;
	int m_numOfVerticalTiles;
	int m_tileSize;
	int m_startPosX;
	int m_startPosY;

	Tile* m_pStartTile;
	Tile* m_pEndTile;
	Tile* m_pTiles;

	std::vector<sf::Vector2f> m_tilePositionsOfFoundPath;

public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	TileHandler(sf::RenderWindow& window, Textures& rTextures);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~TileHandler();

	//===========================================================================================
	//Description: Sets up tile grid, tile size and top left position of the grid.
	//			   Sets surrounding tiles for each tile.
	//			   Sets default start and end tile.
	//===========================================================================================
	void setUpTiles(const int& horizontalTiles, const int& verticalTiles, const int& tileSize, const int& startPosX, const int& startPosY);

	//===========================================================================================
	//Description: Adds pointers of surrounding tiles based on tile index, horizontal and
	//			   vertical index
	//===========================================================================================
	void setSurroundingTiles(const int& tileIndex, const int& horizontalIndex, const int& verticalIndex);

	//===========================================================================================
	//Description: Finds shortest path from point A to point B while avoiding obstacles
	//===========================================================================================
	void findPath();

	//===========================================================================================
	//Description: Finds shortest path from point A to point B while avoiding obstacles.
	//			   Special case for combat units that are two tiles wide
	//===========================================================================================
	void fintPathForALargeUnit(const bool isUnitAttacker);

	//===========================================================================================
	//Description: Resets every tile to default values to make sure it's set up to find path
	//===========================================================================================
	void resetNavigationGraph();

	//===========================================================================================
	//Description: Rerurns distance between two tiles
	//===========================================================================================
	float& calculateDistanceBetweenTiles(Tile* a, Tile* b);

	//===========================================================================================
	//Description: Sets appropriate testing textures to every tile based on its properties
	//===========================================================================================
	void setTestingTileTexture();

	//===========================================================================================
	//Description: Sets appropriate game textures to every tile
	//===========================================================================================
	void setMapTileTextures();

	//===========================================================================================
	//Description: Sets combat tile textures
	//===========================================================================================
	void setCombatTileTextures();

	//===========================================================================================
	//Description: Returns -1 if there is no tile collision, make sure that you check if return
	//			   value is negative when you call this function
	//===========================================================================================
	const int checkTileCollision(const sf::Vector2f& mousePosition);

	//===========================================================================================
	//Description: Draws tiles
	//===========================================================================================
	void draw();

	//===========================================================================================
	//Description: Draw tiles based on indexes passed in the int vector parameter
	//===========================================================================================
	void drawSpecificTiles(const std::vector<int>& tilesToDraw);

	//===========================================================================================
	//Description: Sets tile properties
	//===========================================================================================
	void setTileProperty(const int& index, const TilePropertiesEnum& prop);

	//===========================================================================================
	//Description: Returns pointer to a tile
	//===========================================================================================
	Tile* getTile(const int& index);

	//===========================================================================================
	//Description: Returns number of horizontal tiles
	//===========================================================================================
	const int& getNumOfHorizontalTiles() const;

	//===========================================================================================
	//Description: Returns number of vertical tiles
	//===========================================================================================
	const int& getNumOfVerticalTiles() const;

	//===========================================================================================
	//Description: Returns tile size
	//===========================================================================================
	const int& getTileSize() const;

	//===========================================================================================
	//Description: Returns start position X
	//===========================================================================================
	const int& getStartPosX() const;

	//===========================================================================================
	//Description: Returns start position Y
	//===========================================================================================
	const int& getStartPosY() const;

	//===========================================================================================
	//Description: Sets its testing status
	//===========================================================================================
	void setIsTesting(const bool state);

	//===========================================================================================
	//Description: Sets its combat status
	//===========================================================================================
	void setsIsCombatTiles(const bool state);

	//===========================================================================================
	//Description: Returns a vector of position vectors of a found path
	//===========================================================================================
	std::vector<sf::Vector2f>& getTilePositionVectorForThePathFound();
};

#endif // !TILEHANDLER_H
