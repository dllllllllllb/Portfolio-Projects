//Author: Maciej Dowbor
//Last Accessed: 24/08/2021

#ifndef VIEWMANAGER_H
#define VIEWMANAGER_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>

#include "DirectionEnum.h"
#include "GlobalVariables.h"
#include "ViewManagerSettings.h"
#include "MapHandlerSettings.h"

//===========================================================================================
//Description: Manages view
//===========================================================================================
class ViewManager
{
private:
	sf::RenderWindow& m_window;
	sf::Mouse& m_mouse;
	int m_windowWidth;
	int m_windowHeight;
	int m_halfWindowWidth;
	int m_halfWindowHeight;
	sf::View m_gameView;
	sf::View m_UIView;

	int m_mapBoundaryNorth;
	int m_mapBoundaryEast;
	int m_mapBoundarySouth;
	int m_mapBoundaryWest;

	DirectionEnum m_horizontalDireciton;
	DirectionEnum m_verticalDireciton;

	//Map sections data
	int m_tileSize;
	int m_maxHorizontalMapSection;
	int m_firstMapSectionIndexToDraw;
	
public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	ViewManager(sf::RenderWindow& rWindow, sf::Mouse& rMouse);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~ViewManager();

	//===========================================================================================
	//Description: Sets windows boundaries
	//===========================================================================================
	void setWindowBoundaries();

	//===========================================================================================
	//Description: Updates view manager
	//===========================================================================================
	void update(const float& deltaTime);

	//===========================================================================================
	//Description: Checks mouse position against window boundries to determine which side of the
	//			   screen the mouse is positioned
	//===========================================================================================
	void checkMouseDirection();

	//===========================================================================================
	//Description: Moves view based on horizonal direction of the mouse
	//===========================================================================================
	void moveViewHorizontally(const float& deltaTime);

	//===========================================================================================
	//Description: Moves view based on vertical direction of the mouse
	//===========================================================================================
	void moveViewVertically(const float& deltaTime);

	//===========================================================================================
	//Description: Sets UI view for rendering and mouse collisions
	//===========================================================================================
	void setUIView();

	//===========================================================================================
	//Description: Sets game view for rendering and mouse collisions
	//===========================================================================================
	void setGameView();

	//===========================================================================================
	//Description: Sets map boundaries used to determine if the player can move the view.
	//			   Makes sure that the player can not move the view bayond map boundaties
	//===========================================================================================
	void setMapBoundaries(const int& mapWidth, const int& mapHeight, const int& mapBorderSize);

	//===========================================================================================
	//Description: Sets variables neccessary for selecting map sections to draw
	//===========================================================================================
	void setMapSectionVariables(const int& tileSize, const int& maxNumOfHorizontalMapSections);

	//===========================================================================================
	//Description: Determines the first map section to draw by calculating which map section
	//			   is in the top left corner of the screen
	//===========================================================================================
	void calculateFirstMapSectionToDraw();

	//===========================================================================================
	//Description: Returns index of the top left map section visible on the screen
	//===========================================================================================
	const int& getFirstMapSectionToDraw()const;

	//===========================================================================================
	//Description: Sets the position of the game view
	//===========================================================================================
	void setGameViewPosition(const sf::Vector2f& newViewPosition);
};

#endif // !VIEWMANAGER_H

