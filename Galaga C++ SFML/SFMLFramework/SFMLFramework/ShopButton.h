//Author: Maciej Dowbor
//Module: MED5149
//Date last accessed: 20/01/2021

#ifndef SHOPBUTTON_H
#define SHOPBUTTON_H

#include "Button.h"
#include <SFML/Graphics/RenderWindow.hpp>

//=====================================================================================================	
//Class		: Shop button
//-----------------------------------------------------------------------------------------------------
//Purpose	: To display information about upgrade and allow player to purchase it
//=====================================================================================================
class ShopButton : public Button
{
private:

	sf::RenderWindow	&m_window;
	sf::Sprite			m_itemIcon;
	sf::Text			m_description;
	sf::Text			m_price;

public:

	ShopButton( sf::RenderWindow &window );
	//=================================================================================================
	//Purpose	: Constructor
	//-------------------------------------------------------------------------------------------------
	//Parameters: Render window reference
	//-------------------------------------------------------------------------------------------------
	//Returns	: -
	//=================================================================================================

	~ShopButton( );
	//=================================================================================================
	//Purpose	: Destructor
	//-------------------------------------------------------------------------------------------------
	//Parameters: -
	//-------------------------------------------------------------------------------------------------
	//Returns	: -
	//=================================================================================================

	void shopButtonSetUp( const std::string &buttonName, const std::string &description, const std::string &price, const sf::Font &textFont, const int &nameTextSize, const int &descriptionTextSize, const sf::Texture &buttonTexture, const sf::Texture &iconTexture, const float &posX, const float &posY );
	//=================================================================================================
	//Purpose	: Set up shop button
	//-------------------------------------------------------------------------------------------------
	//Parameters: Name, description, price, font, Name text size, description text size, button texture,
	//			  item icon texture, position X and position Y 
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
};

#endif // !SHOPBUTTON_H
