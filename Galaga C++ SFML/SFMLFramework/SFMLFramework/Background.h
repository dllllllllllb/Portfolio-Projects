//Author: Maciej Dowbor
//Module: MED5149
//Date last accessed: 20/01/2021

#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "BackgroundStar.h"
#include "Settings.h"
#include "Textures.h"

//=====================================================================================================	
//Class		: Background
//-----------------------------------------------------------------------------------------------------
//Purpose	: Application background. Generates, updates and draws stars in the background to make 
//			  an illusion of space
//=====================================================================================================	
class Background
{
private:

	sf::RenderWindow	&m_window;
	BackgroundStar		*m_pStars;
	Textures			*m_pTextures;

public:
	Background( sf::RenderWindow &window, Textures *textures );
	//=================================================================================================						
	//Purpose	: Constructor
	//-------------------------------------------------------------------------------------------------
	//Parameters: Reference to render window and pointer to textures class
	//=================================================================================================

	~Background( );
	//=================================================================================================						
	//Purpose	: Destructor
	//-------------------------------------------------------------------------------------------------
	//Parameters: -
	//=================================================================================================

	void update( const float &deltaTime );
	//=================================================================================================						
	//Purpose	: Update contents of this class
	//-------------------------------------------------------------------------------------------------
	//Parameters: Time passed since last frame
	//=================================================================================================

	void draw( );
	//=================================================================================================						
	//Purpose	: Draws contents of this class
	//-------------------------------------------------------------------------------------------------
	//Parameters: -
	//=================================================================================================
};

#endif // !BACKGROUND_H
