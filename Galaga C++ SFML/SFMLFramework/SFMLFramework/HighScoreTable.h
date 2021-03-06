//Author: Maciej Dowbor
//Module: MED5149
//Date last accessed: 20/01/2021

#ifndef HIGHSCORETABLE_H
#define HIGHSCORETABLE_H

#include <fstream>
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/MemoryInputStream.hpp>
#include <sstream>

#include "Background.h"
#include "Button.h"
#include "HighScoreData.h"
#include "Textures.h"

//=====================================================================================================	
//Class		: High score table
//-----------------------------------------------------------------------------------------------------
//Purpose	: Load, save and display high score table
//=====================================================================================================
class HighScoreTable
{
private:

	std::string			m_fileName;
	sf::RenderWindow	&m_window;
	Textures			*m_pTextures;

	std::ifstream		m_highScoreFileIn; //Used to read data from a txt file
	std::ofstream		m_highScoreFileOut; //Used to write data to a txt file

	HighScoreData		*m_pHighScoreData;
	sf::Text			*m_pHighScores;
	sf::Text			m_HighScoreBanner;

	Button				m_exitButton;
	sf::Text			*m_exitButtonText;
	sf::Mouse			m_mouse;

public:

	HighScoreTable( sf::RenderWindow &window, Textures *textures );
	//=================================================================================================
	//Purpose	: Constructor
	//-------------------------------------------------------------------------------------------------
	//Parameters: Render window reference and textures pointer
	//-------------------------------------------------------------------------------------------------
	//Returns	: -
	//=================================================================================================

	~HighScoreTable( );
	//=================================================================================================
	//Purpose	: Destructor
	//-------------------------------------------------------------------------------------------------
	//Parameters: -
	//-------------------------------------------------------------------------------------------------
	//Returns	: -
	//=================================================================================================

	void readData( );
	//=================================================================================================
	//Purpose	: Reads data from txt file
	//-------------------------------------------------------------------------------------------------
	//Parameters: -
	//-------------------------------------------------------------------------------------------------
	//Returns	: -
	//=================================================================================================

	void writeData( );
	//=================================================================================================
	//Purpose	: Writes data to a txt file
	//-------------------------------------------------------------------------------------------------
	//Parameters: -
	//-------------------------------------------------------------------------------------------------
	//Returns	: -
	//=================================================================================================

	void sortTable( const std::string &name, const int &score );
	//=================================================================================================
	//Purpose	: Sorts table in descending order
	//-------------------------------------------------------------------------------------------------
	//Parameters: Player name and player score
	//-------------------------------------------------------------------------------------------------
	//Returns	: -
	//=================================================================================================

	void setUpText( );
	//=================================================================================================
	//Purpose	: Sets up text
	//-------------------------------------------------------------------------------------------------
	//Parameters: -
	//-------------------------------------------------------------------------------------------------
	//Returns	: -
	//=================================================================================================

	void updateText( );
	//=================================================================================================
	//Purpose	: Updates text
	//-------------------------------------------------------------------------------------------------
	//Parameters: -
	//-------------------------------------------------------------------------------------------------
	//Returns	: -
	//=================================================================================================

	void draw( );
	//=================================================================================================
	//Purpose	: Draws contents of this class
	//-------------------------------------------------------------------------------------------------
	//Parameters: -
	//-------------------------------------------------------------------------------------------------
	//Returns	: -
	//=================================================================================================

	void update( );
	//=================================================================================================
	//Purpose	: Chekcs for mouse collision
	//-------------------------------------------------------------------------------------------------
	//Parameters: -
	//-------------------------------------------------------------------------------------------------
	//Returns	: -
	//=================================================================================================

};

#endif // !HIGHSCORETABLE_H
