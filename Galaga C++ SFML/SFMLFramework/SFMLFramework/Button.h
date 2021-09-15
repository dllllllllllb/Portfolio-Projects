//Author: Maciej Dowbor
//Module: MED5149
//Date last accessed: 20/01/2021

#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <string>

#include "Settings.h"

//=====================================================================================================
//Class		: Button
//-----------------------------------------------------------------------------------------------------
//Purpose	: Basic button for UI
//=====================================================================================================
class Button : public sf::Sprite
{
protected:
	sf::Text m_buttonText;

	//Button collision bounds
	float m_upperCollisionBound;
	float m_lowerCollisionBound;
	float m_rightCollisionBound;
	float m_leftCollisionBound;

	bool m_isHovered;

public:
	Button( );
	//=================================================================================================						
	//Purpose	: Constructor
	//-------------------------------------------------------------------------------------------------
	//Parameters: -
	//=================================================================================================

	~Button( );
	//=================================================================================================						
	//Purpose	: Destructor
	//-------------------------------------------------------------------------------------------------
	//Parameters: -
	//=================================================================================================

	void setUp( const std::string &buttonText, const sf::Font &textFont, const int &textSize, const sf::Texture &buttonTexture, const float &buttonPosX, const float &buttonPosY );
	//=================================================================================================					
	//Purpose	: Set button texture, origin, position, collision bounds and text
	//-------------------------------------------------------------------------------------------------
	//Parameters: Button text, font, text size, button texture, position X and position Y
	//=================================================================================================

	bool checkMouseCollision( const sf::Vector2i &mousePosition );
	///=================================================================================================			
	//Purpose	: Check if the mouse intersects the button and change it's colour based on collision
	//-------------------------------------------------------------------------------------------------
	//Parameters: Mouse position
	//-------------------------------------------------------------------------------------------------
	//Returns	: Bool if the mouse intersects the button
	//=================================================================================================

	sf::Text *getText( );
	//=================================================================================================						
	//Purpose	: Return pointer to the button text
	//-------------------------------------------------------------------------------------------------
	//Parameters: -
	//-------------------------------------------------------------------------------------------------
	//Returns	: Pointer to button text
	//=================================================================================================
};

#endif // !BUTTON_H
