//Author: Maciej Dowbor
//Last Accessed: 02/08/2021

#ifndef CURSOR_H
#define CURSOR_H

#include "SFML/Graphics/Sprite.hpp"
#include "TileHandler.h"

//===========================================================================================
//Description: Mouse cursor that changes sprite based on interaction with the game
//===========================================================================================
class Cursor : public sf::Sprite
{
private:
	TileHandler* m_pTileHandler;
	sf::Vector2f m_previousMousePosition; //By default coordinates are 0, 0

	int m_tileSize;
	int m_halfTileSize;

public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	Cursor(Textures& rTextures, const int& tileSize);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~Cursor();

	//===========================================================================================
	//Description: Checks if the cursor icon should be updated
	//===========================================================================================
	void update(const sf::Vector2f& mousePosition);

	//===========================================================================================
	//Description: Updates cursor icon based on properties of the tile it hovers
	//===========================================================================================
	void updateMapCursor(const int& tileIndex);

	//===========================================================================================
	//Description: Sets a pointer to the tile handler
	//===========================================================================================
	void setTileHandlerPointer(TileHandler* pTileHandler);
};

#endif // !CURSOR_H
