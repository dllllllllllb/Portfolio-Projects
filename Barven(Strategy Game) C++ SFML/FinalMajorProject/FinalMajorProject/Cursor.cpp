#include "Cursor.h"
Cursor::Cursor(Textures& rTextures, const int& tileSize) :
	m_pTileHandler(nullptr),
	m_tileSize(tileSize),
	m_halfTileSize(m_tileSize / 2)
{
	setTexture(rTextures.m_cursorIcons, true);
	setOrigin(m_halfTileSize, m_halfTileSize);
	setTextureRect(sf::IntRect(0, 0, m_tileSize, m_tileSize));
}

Cursor::~Cursor()
{
}

void Cursor::update(const sf::Vector2f& mousePosition)
{
	setPosition(mousePosition);

	if (abs(mousePosition.x - m_previousMousePosition.x) > m_halfTileSize || abs(mousePosition.y - m_previousMousePosition.y) > m_halfTileSize) //Checks if mouse was moved to a different tile
	{
		int tileIndex = m_pTileHandler->checkTileCollision(mousePosition); //Returns tile index, if invalid it will return -1

		if (tileIndex > -1) //Makes sure that the index is valid
		{
			updateMapCursor(tileIndex);
		}
		else
		{
			setTextureRect(sf::IntRect(0, 0, m_tileSize, m_tileSize)); //If tile index is invalid, change to inaccessible cursor sprite
		}
	}
}

void Cursor::updateMapCursor(const int& tileIndex)
{
	Tile* tile = m_pTileHandler->getTile(tileIndex);
	bool checkTiles = true;

	//Set mouse position to center of hovered tile
	m_previousMousePosition = tile->getPosition();
	m_previousMousePosition.x += m_halfTileSize; //Tile origin == top left corner, add half size of the tile to each coordinate to get center position
	m_previousMousePosition.y += m_halfTileSize;

	//Check if the tile is protected by a unit

	for (auto& tileNeighbour : tile->getSurroundingTilesVector())
	{
		if (tileNeighbour->getMapObjectType() == MapObjectsEnum::unit)
		{
			if (tileNeighbour->getTileVectorIndex() >= tileIndex - 1) //Makes sure to not check tiles below the unit
			{
				setTextureRect(sf::IntRect(96, 0, m_tileSize, m_tileSize));
				checkTiles = false;

				if (tile->getMapObjectType() == MapObjectsEnum::landscape)
				{
					setTextureRect(sf::IntRect(0, 0, m_tileSize, m_tileSize));
				}
				break;
			}
		}
	}

	if (checkTiles)
	{
		if (tile->getIsOccupied() && tile->getMapObjectType() != MapObjectsEnum::landscape) //Checks if the tile has an interactable object that isn't a landscape on it
		{
			if (tile->getMapObjectType() == MapObjectsEnum::unit)
			{
				setTextureRect(sf::IntRect(96, 0, m_tileSize, m_tileSize));
			}
			else
			{
				setTextureRect(sf::IntRect(64, 0, m_tileSize, m_tileSize));
			}
		}
		else if (tile->getIsObstacle()) //Checks if the tile is an obstacle
		{
			setTextureRect(sf::IntRect(0, 0, m_tileSize, m_tileSize));
		}
		else
		{
			setTextureRect(sf::IntRect(32, 0, m_tileSize, m_tileSize));
		}
	}
}

void Cursor::setTileHandlerPointer(TileHandler* pTileHandler)
{
	m_pTileHandler = pTileHandler;
}