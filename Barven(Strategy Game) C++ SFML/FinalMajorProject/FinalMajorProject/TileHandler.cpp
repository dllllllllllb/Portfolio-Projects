#include "TileHandler.h"
TileHandler::TileHandler(sf::RenderWindow& window, Textures& rTextures) :
	m_window(window),
	m_textures(rTextures),
	m_isTestingTiles(false),
	m_isCombatTiles(false),
	m_numOfTiles(0),
	m_numOfHorizontalTiles(0),
	m_numOfVerticalTiles(0),
	m_tileSize(0),
	m_startPosX(0),
	m_startPosY(0),
	m_pStartTile(nullptr),
	m_pEndTile(nullptr),
	m_pTiles(nullptr)
{
}

TileHandler::~TileHandler()
{
	delete[] m_pTiles;
	m_pTiles = nullptr;
}

void TileHandler::setUpTiles(const int& horizontalTiles, const int& verticalTiles, const int& tileSize, const int& startPosX, const int& startPosY)
{
	//Makes sure that the pointer is empty
	delete[] m_pTiles;
	m_pTiles = nullptr;

	//Sets variables
	m_numOfTiles = horizontalTiles * verticalTiles;
	m_numOfHorizontalTiles = horizontalTiles;
	m_numOfVerticalTiles = verticalTiles;
	m_tileSize = tileSize;
	m_startPosX = startPosX;
	m_startPosY = startPosY;

	//Create array of tiles based on size of the grid
	m_pTiles = new Tile[m_numOfTiles];

	//Set tile positions
	int index = 0;
	for (int y = 0; y < m_numOfVerticalTiles; y++)
	{
		for (int x = 0; x < m_numOfHorizontalTiles; x++)
		{
			index = (y * m_numOfHorizontalTiles) + x;
			m_pTiles[index].setPosition(startPosX + (x * m_tileSize), startPosY + (y * m_tileSize));
			m_pTiles[index].setTileVectorIndex(index);
		}
	}

	//Set surrounding tiles
	for (int y = 0; y < m_numOfVerticalTiles; y++)
	{
		for (int x = 0; x < m_numOfHorizontalTiles; x++)
		{
			int index = (y * m_numOfHorizontalTiles) + x;

			setSurroundingTiles(index, x, y);
		}
	}

	//Sets default start and end tile
	m_pStartTile = &m_pTiles[m_numOfHorizontalTiles * 5 + 3];
	m_pEndTile = &m_pTiles[m_numOfHorizontalTiles * 6 - 4];

	if (m_isTestingTiles)
	{
		setTestingTileTexture();
	}
	else if (m_isCombatTiles)
	{
		setCombatTileTextures();
	}
	else
	{
		setMapTileTextures();
	}
}

void TileHandler::setSurroundingTiles(const int& tileIndex, const int& horizontalIndex, const int& verticalIndex)
{
	int tileIndexToAdd = 0;

	//Get north tile
	if (verticalIndex > 0)
	{
		tileIndexToAdd = tileIndex - m_numOfHorizontalTiles;
		m_pTiles[tileIndex].getSurroundingTilesVector().push_back(&m_pTiles[tileIndexToAdd]);
	}

	//Get south tile
	if (verticalIndex < m_numOfVerticalTiles - 1)
	{
		tileIndexToAdd = tileIndex + m_numOfHorizontalTiles;
		m_pTiles[tileIndex].getSurroundingTilesVector().push_back(&m_pTiles[tileIndexToAdd]);
	}

	//Get west tile
	if (horizontalIndex > 0)
	{
		tileIndexToAdd = tileIndex - 1;
		m_pTiles[tileIndex].getSurroundingTilesVector().push_back(&m_pTiles[tileIndexToAdd]);
	}

	//Get east tile
	if (horizontalIndex < m_numOfHorizontalTiles - 1)
	{
		tileIndexToAdd = tileIndex + 1;
		m_pTiles[tileIndex].getSurroundingTilesVector().push_back(&m_pTiles[tileIndexToAdd]);
	}

	//Get north east tile
	if (horizontalIndex < m_numOfHorizontalTiles - 1 && verticalIndex > 0)
	{
		tileIndexToAdd = tileIndex - m_numOfHorizontalTiles + 1;
		m_pTiles[tileIndex].getSurroundingTilesVector().push_back(&m_pTiles[tileIndexToAdd]);
	}

	//Get north west tile
	if (horizontalIndex > 0 && verticalIndex > 0)
	{
		tileIndexToAdd = tileIndex - m_numOfHorizontalTiles - 1;
		m_pTiles[tileIndex].getSurroundingTilesVector().push_back(&m_pTiles[tileIndexToAdd]);
	}

	//Get south east tile
	if (horizontalIndex < m_numOfHorizontalTiles - 1 && verticalIndex < m_numOfVerticalTiles - 1)
	{
		tileIndexToAdd = tileIndex + m_numOfHorizontalTiles + 1;
		m_pTiles[tileIndex].getSurroundingTilesVector().push_back(&m_pTiles[tileIndexToAdd]);
	}

	//Get south west tile
	if (horizontalIndex > 0 && verticalIndex < m_numOfVerticalTiles - 1)
	{
		tileIndexToAdd = tileIndex + m_numOfHorizontalTiles - 1;
		m_pTiles[tileIndex].getSurroundingTilesVector().push_back(&m_pTiles[tileIndexToAdd]);
	}
}

void TileHandler::findPath()
{
	resetNavigationGraph();

	m_pStartTile->setLocalGoal(0.0f);
	m_pStartTile->setGlobalGoal(calculateDistanceBetweenTiles(m_pStartTile, m_pEndTile)); //Used to bias the algorithm to move towards end tile

	//Sets current tile to check, algorithm should always start at the start tile
	Tile* currentTile = m_pStartTile;

	//List of tile pointers of not tested tiles that are next in que to test
	std::list<Tile*> notVisitedTiles;

	//First tile to be checked
	notVisitedTiles.push_back(m_pStartTile);

	//Loop while there are tiles to be visited and the current tile is not the end tile
	//If you don't check if the currentTile is the end tile, the algorithm will continue untill all remainding tiles have been visited
	while (!notVisitedTiles.empty() && currentTile != m_pEndTile)
	{
		//A lambda expression to sort the list in ascending order based on tiles global goal
		notVisitedTiles.sort(
			[](const Tile* a, const Tile* b)
			{
				return a->getGlobalGoal() < b->getGlobalGoal();
			}
		);

		//Remove tiles that have already been visisted
		while (!notVisitedTiles.empty() && notVisitedTiles.front()->getIsVisited())
		{
			notVisitedTiles.pop_front();
		}

		//Make sure that the list is not empty
		if (notVisitedTiles.empty())
		{
			break;
		}

		//Since the tiles are sorted in ascending order, the closes tile to the global goal is the first one in the list
		currentTile = notVisitedTiles.front();
		currentTile->setIsVisited(true);

		//For loop that loops through all tiles that surround current tile
		for (auto neighbourTile : currentTile->getSurroundingTilesVector())
		{
			//if the surrounding tile is not visited and it's not an obstacle, add it to the list of not visited tiles
			if (!neighbourTile->getIsVisited() && !neighbourTile->getIsObstacle())
			{
				notVisitedTiles.push_back(neighbourTile);
			}

			//Calculate neighbours possible lowest parent tile distance
			float possiblyLowerLocalGoal = currentTile->getLocalGoal() + calculateDistanceBetweenTiles(currentTile, neighbourTile);

			//This is the part of code that defines the path
			//if the local goal is lower than neighbourTile current goal, set its parent tile and update its goals
			if (possiblyLowerLocalGoal < neighbourTile->getLocalGoal())
			{
				neighbourTile->setParentTile(currentTile);
				neighbourTile->setLocalGoal(possiblyLowerLocalGoal);
				neighbourTile->setGlobalGoal(neighbourTile->getLocalGoal() + calculateDistanceBetweenTiles(neighbourTile, m_pEndTile));
			}
		}
	}
	//Once the loop is over, it means that the algorith has either found a path from start to end or that there is not a valid path.
	//If there is a valid path, the way the path is determined is by starting at the end tile and go backwards using it's parent tile
	//set in the for loop above. Essentially the parentTiles create a connection from endTile to startTile creating a path.

	if (m_isTestingTiles)
	{
		setTestingTileTexture();
	}
}

void TileHandler::fintPathForALargeUnit(const bool isUnitAttacker)
{
	resetNavigationGraph();

	m_pStartTile->setLocalGoal(0.0f);
	m_pStartTile->setGlobalGoal(calculateDistanceBetweenTiles(m_pStartTile, m_pEndTile)); //Used to bias the algorithm to move towards end tile

	//Sets current tile to check, algorithm should always start at the start tile
	Tile* currentTile = m_pStartTile;

	//List of tile pointers of not tested tiles that are next in que to test
	std::list<Tile*> notVisitedTiles;

	//First tile to be checked
	notVisitedTiles.push_back(m_pStartTile);

	//Loop while there are tiles to be visited and the current tile is not the end tile
	//If you don't check if the currentTile is the end tile, the algorithm will continue untill all remainding tiles have been visited
	while (!notVisitedTiles.empty() && currentTile != m_pEndTile)
	{
		//A lambda expression to sort the list in ascending order based on tiles global goal
		notVisitedTiles.sort(
			[](const Tile* a, const Tile* b)
			{
				return a->getGlobalGoal() < b->getGlobalGoal();
			}
		);

		//Remove tiles that have already been visisted
		while (!notVisitedTiles.empty() && notVisitedTiles.front()->getIsVisited())
		{
			notVisitedTiles.pop_front();
		}

		//Make sure that the list is not empty
		if (notVisitedTiles.empty())
		{
			break;
		}

		//Since the tiles are sorted in ascending order, the closes tile to the global goal is the first one in the list
		currentTile = notVisitedTiles.front();
		currentTile->setIsVisited(true);

		//For loop that loops through all tiles that surround current tile
		for (auto neighbourTile : currentTile->getSurroundingTilesVector())
		{
			//if the surrounding tile is not visited and it's not an obstacle, add it to the list of not visited tiles
			if (!neighbourTile->getIsVisited() && !neighbourTile->getIsObstacle())
			{
				if (isUnitAttacker) //Check if tile next to the main tile is not occupied
				{
					if (!getTile(neighbourTile->getTileVectorIndex() - 1)->getIsObstacle())
					{
						notVisitedTiles.push_back(neighbourTile);
					}
				}
				else
				{
					if (!getTile(neighbourTile->getTileVectorIndex() + 1)->getIsObstacle())
					{
						notVisitedTiles.push_back(neighbourTile);
					}
				}
			}

			//Calculate neighbours possible lowest parent tile distance
			float possiblyLowerLocalGoal = currentTile->getLocalGoal() + calculateDistanceBetweenTiles(currentTile, neighbourTile);

			//This is the part of code that defines the path
			//if the local goal is lower than neighbourTile current goal, set its parent tile and update its goals
			if (possiblyLowerLocalGoal < neighbourTile->getLocalGoal())
			{
				neighbourTile->setParentTile(currentTile);
				neighbourTile->setLocalGoal(possiblyLowerLocalGoal);
				neighbourTile->setGlobalGoal(neighbourTile->getLocalGoal() + calculateDistanceBetweenTiles(neighbourTile, m_pEndTile));
			}
		}
	}
	//Once the loop is over, it means that the algorith has either found a path from start to end or that there is not a valid path.
	//If there is a valid path, the way the path is determined is by starting at the end tile and go backwards using it's parent tile
	//set in the for loop above. Essentially the parentTiles create a connection from endTile to startTile creating a path.

	if (m_isTestingTiles)
	{
		setTestingTileTexture();
	}
}

void TileHandler::resetNavigationGraph()
{
	//Loop through all tiles and reset essential variables for path finding without affecting tiles properties
	for (int y = 0; y < m_numOfVerticalTiles; y++)
	{
		for (int x = 0; x < m_numOfHorizontalTiles; x++)
		{
			int index = (y * m_numOfHorizontalTiles) + x;
			m_pTiles[index].setIsVisited(false);
			m_pTiles[index].resetParent();
			m_pTiles[index].setLocalGoal(INFINITY);
			m_pTiles[index].setGlobalGoal(INFINITY);
		}
	}
}

float& TileHandler::calculateDistanceBetweenTiles(Tile* a, Tile* b)
{
	float tileAPosX = a->getPosition().x;
	float tileAPosY = a->getPosition().y;

	float tileBPosX = b->getPosition().x;
	float tileBPosY = b->getPosition().y;

	//Pythagoras to calculate distance between TileA and TileB
	float distance = sqrtf((tileAPosX - tileBPosX) * (tileAPosX - tileBPosX) + (tileAPosY - tileBPosY) * (tileAPosY - tileBPosY));

	return distance;
}

void TileHandler::setTestingTileTexture()
{
	//Loops through all tiles and sets appropriate textures based on their properites
	for (int y = 0; y < m_numOfVerticalTiles; y++)
	{
		for (int x = 0; x < m_numOfHorizontalTiles; x++)
		{
			int index = (y * m_numOfHorizontalTiles) + x;

			if (m_pTiles[index].getIsObstacle())
			{
				m_pTiles[index].setTexture(m_textures.m_tileObstacle, true);
			}
			else if (m_pTiles[index].getIsVisited())
			{
				m_pTiles[index].setTexture(m_textures.m_tileVisited, true);
			}
			else
			{
				m_pTiles[index].setTexture(m_textures.m_tileNotVisited, true);
			}
		}
	}

	//Makes sure that end tile exists
	if (m_pEndTile != nullptr)
	{
		Tile* tilePath = m_pEndTile;

		//Gets the parent of the current tile and sets its texture to a path
		while (tilePath->getParentTile() != nullptr)
		{
			tilePath->setTexture(m_textures.m_tilePath, true);
			tilePath = tilePath->getParentTile();
		}
	}

	//Sets appropriate textures to start and end tiles
	m_pStartTile->setTexture(m_textures.m_tileStart, true);
	m_pEndTile->setTexture(m_textures.m_tileEnd, true);
}

void TileHandler::setMapTileTextures()
{
	for (int i = 0; i < m_numOfTiles; i++)
	{
		int RNG = rand() % 6;

		m_pTiles[i].setTexture(m_textures.m_grassTiles);
		switch (RNG)
		{
		case 0:
			m_pTiles[i].setTextureRect(sf::IntRect(0, 0, 32, 32));
			break;

		case 1:
			m_pTiles[i].setTextureRect(sf::IntRect(32, 0, 32, 32));
			break;

		case 2:
			m_pTiles[i].setTextureRect(sf::IntRect(64, 0, 32, 32));
			break;

		case 3:
			m_pTiles[i].setTextureRect(sf::IntRect(0, 32, 32, 32));
			break;

		case 4:
			m_pTiles[i].setTextureRect(sf::IntRect(32, 32, 32, 32));
			break;

		case 5:
			m_pTiles[i].setTextureRect(sf::IntRect(64, 32, 32, 32));
			break;

		default:

			break;
		}
	}
}

void TileHandler::setCombatTileTextures()
{
	for (int i = 0; i < m_numOfTiles; i++)
	{
		m_pTiles[i].setTexture(m_textures.m_combatTile, true);
	}
}

const int TileHandler::checkTileCollision(const sf::Vector2f& mousePosition)
{
	int collidedTileIndex = -1;
	if (m_tileSize) //Makes sure tile size is > 0
	{
		int x = (mousePosition.x - m_startPosX) / m_tileSize; //Converts mouse coordinates to tile array coordinates
		int y = (mousePosition.y - m_startPosY) / m_tileSize;
		if (x < m_numOfHorizontalTiles && y < m_numOfVerticalTiles)
		{
			if (x >= 0 && x < m_numOfHorizontalTiles && y >= 0 && y < m_numOfVerticalTiles) //Makes sure that the x and y coordinates are valid
			{
				int tileIndex = y * m_numOfHorizontalTiles + x;
				if (tileIndex < m_numOfTiles)
				{
					collidedTileIndex = tileIndex; //sets tile index
				}
			}
		}
	}

	return collidedTileIndex;
}

void TileHandler::draw()
{
	for (int i = 0; i < m_numOfTiles; i++)
	{
		m_window.draw(m_pTiles[i]);
	}
}

void TileHandler::drawSpecificTiles(const std::vector<int>& tilesToDraw)
{
	for (int tileID : tilesToDraw)
	{
		m_window.draw(m_pTiles[tileID]);
	}
}

void TileHandler::setTileProperty(const int& index, const TilePropertiesEnum& prop)
{
	switch (prop)
	{
	case TilePropertiesEnum::empty:
	{
	}
	break;

	case TilePropertiesEnum::start:
	{
		//Removes current start tile property and sets it to a normal tile
		m_pStartTile->setIsVisited(false);
		if (m_isTestingTiles)
		{
			m_pStartTile->setTexture(m_textures.m_tileNotVisited, true);
		}

		//Sets new start tile
		m_pStartTile = &m_pTiles[index];
		if (m_isTestingTiles)
		{
			m_pStartTile->setTexture(m_textures.m_tileStart, true);
		}
	}
	break;

	case TilePropertiesEnum::end:
	{
		//Removes current end tile property and sets it to a normal tile
		m_pEndTile->setIsVisited(false);
		if (m_isTestingTiles)
		{
			m_pEndTile->setTexture(m_textures.m_tileNotVisited, true);
		}

		//Sets new end tile
		m_pEndTile = &m_pTiles[index];
		if (m_isTestingTiles)
		{
			m_pEndTile->setTexture(m_textures.m_tileEnd, true);
		}
	}
	break;

	case TilePropertiesEnum::obstacle:
	{
		//Change texture based on if the tile is an obstacle
		if (m_pTiles[index].getIsObstacle())
		{
			m_pTiles[index].setTexture(m_textures.m_tileNotVisited, true);
		}
		else
		{
			m_pTiles[index].setTexture(m_textures.m_tileObstacle, true);
		}

		//Toggle obstacle
		m_pTiles[index].toggleIsObstacle();
	}
	break;

	default:
		break;
	}
}

Tile* TileHandler::getTile(const int& index)
{
	return &m_pTiles[index];
}

const int& TileHandler::getNumOfHorizontalTiles() const
{
	return m_numOfHorizontalTiles;
}

const int& TileHandler::getNumOfVerticalTiles() const
{
	return m_numOfVerticalTiles;
}

const int& TileHandler::getTileSize() const
{
	return m_tileSize;
}

const int& TileHandler::getStartPosX() const
{
	return m_startPosX;
}

const int& TileHandler::getStartPosY() const
{
	return m_startPosY;
}

void TileHandler::setIsTesting(const bool state)
{
	m_isTestingTiles = state;
}

void TileHandler::setsIsCombatTiles(const bool state)
{
	m_isCombatTiles = state;
}

std::vector<sf::Vector2f>& TileHandler::getTilePositionVectorForThePathFound()
{
	m_tilePositionsOfFoundPath.clear(); //Makes sure that the vector is empty

	Tile* tilePath = m_pEndTile;

	while (tilePath->getParentTile() != nullptr) //Loop through the path if one is found, if  first parentTile == nullptr, there is no valid path
	{
		m_tilePositionsOfFoundPath.push_back(tilePath->getPosition());
		tilePath = tilePath->getParentTile();
	}

	m_tilePositionsOfFoundPath.push_back(tilePath->getPosition());

	return m_tilePositionsOfFoundPath;
}