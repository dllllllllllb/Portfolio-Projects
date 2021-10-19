//Author: Maciej Dowbor
//Last Accessed: 30/03/2021

#ifndef PATHFINDINGTOOL_H
#define PATHFINDINGTOOL_H
#include <SFML/Window/Keyboard.hpp>

#include "TileHandler.h"
#include "Button.h"
#include "GlobalVariables.h"

//===========================================================================================
//Description: Dev tool to test and demonstrate A* path finding algorithm.
//===========================================================================================
class PathFindingTool
{
private:
	sf::RenderWindow& m_window;

	TileHandler m_tileHandler;

	Button m_solveButton;

	sf::Keyboard m_keyboard;

	UIElement m_border;

public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	PathFindingTool(sf::RenderWindow& window, Textures& rTextures, Fonts& rFonts, Audio& rAudio);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~PathFindingTool();

	//===========================================================================================
	//Description: Sets up buttons, tiles used for path finding and calls a function to find
	//			   initial path.
	//===========================================================================================
	void initialize();

	//===========================================================================================
	//Description: Sets up border around path finding tiles and sets "Solve" button variables
	//===========================================================================================
	void setUpButtons();

	//===========================================================================================
	//Description: Checks if a tile has been pressed, then depending on pressed key combination,
	//			   changes properties of the tile. Checks if the "Solve" button has been pressed
	//			   that finds a path.
	//===========================================================================================
	void update(const sf::Vector2f& mousePosition);

	//===========================================================================================
	//Description: Draws border, "Solve" button and tiles.
	//===========================================================================================
	void draw();
};

#endif // !PATHFINDINGTOOL_H