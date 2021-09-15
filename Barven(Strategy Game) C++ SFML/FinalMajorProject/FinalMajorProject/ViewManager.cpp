#include "ViewManager.h"

ViewManager::ViewManager(sf::RenderWindow& rWindow, sf::Mouse& rMouse) :
	m_window(rWindow),
	m_mouse(rMouse),
	m_windowWidth(0),
	m_windowHeight(0),
	m_halfWindowWidth(0),
	m_halfWindowHeight(0),
	m_horizontalDireciton(DirectionEnum::none),
	m_verticalDireciton(DirectionEnum::none),
	m_mapBoundaryNorth(0),
	m_mapBoundaryEast(0),
	m_mapBoundarySouth(0),
	m_mapBoundaryWest(0),
	m_tileSize(1),
	m_maxHorizontalMapSection(0),
	m_firstMapSectionIndexToDraw(0)
{
	setWindowBoundaries();
}

void ViewManager::setWindowBoundaries()
{
	m_windowWidth = m_window.getSize().x - 5;
	m_windowHeight = m_window.getSize().y - 5;
	m_halfWindowWidth = m_window.getSize().x * 0.5f;
	m_halfWindowHeight = m_window.getSize().y * 0.5f;
	m_gameView = m_window.getView();
	m_UIView = m_window.getView();
}

void ViewManager::update(const float& deltaTime)
{
	checkMouseDirection();

	if (Global::g_isWindowFocused) //Makes sure that the window is focused
	{
		if (m_horizontalDireciton != DirectionEnum::none)
		{
			moveViewHorizontally(deltaTime);
			calculateFirstMapSectionToDraw();

		}

		if (m_verticalDireciton != DirectionEnum::none)
		{
			moveViewVertically(deltaTime);
			calculateFirstMapSectionToDraw();
		}
	}
}

void ViewManager::moveViewHorizontally(const float& deltaTime)
{
	int distance =ViewManagerSettings::c_viewScrollSpeed * deltaTime; //Needs to be rounded to an int otherwise rendering is blury

	if (m_horizontalDireciton == DirectionEnum::east)
	{
		if (m_gameView.getCenter().x + m_halfWindowWidth < m_mapBoundaryEast)
		{
			m_gameView.move(distance, 0);
		}
	}
	else
	{
		if (m_gameView.getCenter().x - m_halfWindowWidth > m_mapBoundaryWest)
		{
			m_gameView.move(-distance, 0);
		}
	}
	setGameView();
}

void ViewManager::moveViewVertically(const float& deltaTime)
{
	int distance = ViewManagerSettings::c_viewScrollSpeed * deltaTime; //Needs to be rounded to an int otherwise rendering is blury

	if (m_verticalDireciton == DirectionEnum::south)
	{
		if (m_gameView.getCenter().y + m_halfWindowHeight < m_mapBoundarySouth)
		{
			m_gameView.move(0, distance);
		}
	}
	else
	{
		if (m_gameView.getCenter().y - m_halfWindowHeight > m_mapBoundaryNorth)
		{
			m_gameView.move(0, -distance);
		}
	}
	setGameView();
}

void ViewManager::setUIView()
{
	m_window.setView(m_UIView);
}

void ViewManager::setGameView()
{
	m_window.setView(m_gameView);
}

void ViewManager::setMapBoundaries(const int& mapWidth, const int& mapHeight, const int& mapBorderSize)
{
	m_mapBoundaryNorth =  -mapBorderSize;
	m_mapBoundaryEast = mapWidth + mapBorderSize + 32;
	m_mapBoundarySouth = mapHeight + mapBorderSize + 32;
	m_mapBoundaryWest = -mapBorderSize;
}

void ViewManager::setMapSectionVariables(const int& tileSize, const int& maxHorizontalMapSections)
{
	m_tileSize = tileSize;
	m_maxHorizontalMapSection = maxHorizontalMapSections;
}

void ViewManager::calculateFirstMapSectionToDraw()
{
	int topLeftCornerX = m_window.getView().getCenter().x - (m_window.getSize().x * 0.5f);
	int topLeftCornerY = m_window.getView().getCenter().y - (m_window.getSize().y * 0.5f);

	int mapSectionX = std::floor(((topLeftCornerX / m_tileSize) / MapHandlerSettings::c_drawQuadrantWidth));
	int mapSectionY = std::floor(((topLeftCornerY / m_tileSize) / MapHandlerSettings::c_drawQuadrantHeight));

	if (mapSectionX < 0) //Makes sure that the index is valid
	{
		mapSectionX = 0;
	}
	
	if (mapSectionY < 0) //Makes sure that the index is valid
	{
		mapSectionY = 0;
	}
	//Calculates map section index
	m_firstMapSectionIndexToDraw = (mapSectionY * m_maxHorizontalMapSection) + mapSectionX;

}

const int& ViewManager::getFirstMapSectionToDraw() const
{
	return m_firstMapSectionIndexToDraw;
}

void ViewManager::setGameViewPosition(const sf::Vector2f& newViewPosition)
{
	m_gameView.setCenter(newViewPosition);
	setGameView();
	calculateFirstMapSectionToDraw();
}

void ViewManager::checkMouseDirection()
{
	sf::Vector2i mousePosition = m_mouse.getPosition(m_window);

	//Check Horizontal Direction
	if (mousePosition.x > m_windowWidth)
	{
		m_horizontalDireciton = DirectionEnum::east;
	}
	else if (mousePosition.x < 2)
	{
		m_horizontalDireciton = DirectionEnum::west;
	}
	else
	{
		m_horizontalDireciton = DirectionEnum::none;
	}

	//Check Vertical Direction
	if (mousePosition.y > m_windowHeight)
	{
		m_verticalDireciton = DirectionEnum::south;
	}
	else if (mousePosition.y < 2)
	{
		m_verticalDireciton = DirectionEnum::north;
	}
	else
	{
		m_verticalDireciton = DirectionEnum::none;
	}

}

ViewManager::~ViewManager()
{
}
