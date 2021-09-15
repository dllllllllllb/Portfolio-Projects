#include "PathFindingTool.h"

PathFindingTool::PathFindingTool(sf::RenderWindow& window, Textures* textures, Fonts* fonts) :
	m_window(window),
	m_tileHandler(window, textures),
	m_solveButton(window, textures, fonts),
	m_border(window, textures)
{
	m_tileHandler.setIsTesting(true);
}

PathFindingTool::~PathFindingTool()
{
}

void PathFindingTool::update(const sf::Vector2f& mousePosition)
{
	static int tileSize = m_tileHandler.getTileSize();
	static int horizontalTiles = m_tileHandler.getNumOfHorizontalTiles();
	static int verticalTiles = m_tileHandler.getNumOfVerticalTiles();

	if (Global::g_isLMBPressed)
	{

		//Tiles are stored in an array. Instead of checking each tile for collision, I use mouse coordinates 
		//and fixed tile dimentions to calculate the index of the tile pressed.
		int x = (mousePosition.x - m_tileHandler.getStartPosX()) / tileSize;
		int y = (mousePosition.y - m_tileHandler.getStartPosY()) / tileSize;

		if (x >= 0 && x < horizontalTiles && y >= 0 && y < verticalTiles) //Makes sure that the values are within the dimentions of the tile grid
		{
			int index = y * horizontalTiles + x;

			if (m_keyboard.isKeyPressed(sf::Keyboard::LShift))
			{
				m_tileHandler.setTileProperty(index, TilePropertiesEnum::start);
			}
			else if (m_keyboard.isKeyPressed(sf::Keyboard::LControl))
			{
				m_tileHandler.setTileProperty(index, TilePropertiesEnum::end);
			}
			else
			{
				m_tileHandler.setTileProperty(index, TilePropertiesEnum::obstacle);
			}
			Global::objectPressed();
		}
	}

	//Solve button collision
	if (m_solveButton.checkMouseCollision(mousePosition) && Global::g_isLMBPressed)
	{
		m_tileHandler.findPath();
		Global::objectPressed();
	}
}

void PathFindingTool::initialize()
{
	setUpButtons();
	m_tileHandler.setUpTiles(14, 11, 64, 64, 64);
	m_tileHandler.findPath();
}

void PathFindingTool::setUpButtons()
{
	//Border
	int tempX = 14 * 64 + 64 + 12;
	int tempY = 11 * 64 + 64 + 12;
	m_border.setPosition(tempX * 0.5f + 24, tempY * 0.5f + 28);
	m_border.setUpUIBorder(tempX, tempY);


	//Solve button
	m_solveButton.setPosition(1700, 835);
	m_solveButton.setUpUIBorder(300, 100);
	m_solveButton.setCollisionBounds(300, 100);
	m_solveButton.setUpText("Solve", 72, TextAlignmentEnum::middleHorizontal, TextAlignmentEnum::middleVertical);
}

void PathFindingTool::draw()
{
	m_border.drawUIBorderAndBackground();

	m_solveButton.draw();

	m_tileHandler.draw();
}
