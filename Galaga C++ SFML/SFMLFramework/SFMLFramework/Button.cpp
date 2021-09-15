//Author: Maciej Dowbor
//Module: MED5149
//Date last accessed: 20/01/2021

#include "Button.h"

Button::Button( ) :
	m_upperCollisionBound	( 0 ),
	m_lowerCollisionBound	( 0 ),
	m_rightCollisionBound	( 0 ),
	m_leftCollisionBound	( 0 ),
	m_isHovered				( false )
{
}

Button::~Button( )
{
}

void Button::setUp( const std::string &buttonText, const sf::Font &textFont, const int &textSize, const sf::Texture &buttonTexture, const float &buttonPosX, const float &buttonPosY )
{
	//Button texture
	setTexture( buttonTexture, true );
	setOrigin( getLocalBounds( ).width * 0.5f, getLocalBounds( ).height * 0.5f );
	setPosition( buttonPosX, buttonPosY );

	//Button collision bounds, saves calculation when checking for collision
	m_upperCollisionBound	= buttonPosY - k_buttonHeightHalf;
	m_lowerCollisionBound	= buttonPosY + k_buttonHeightHalf;
	m_rightCollisionBound	= buttonPosX + k_buttonWidthHalf;
	m_leftCollisionBound	= buttonPosX - k_buttonWidthHalf;

	//Button text
	m_buttonText.setFont( textFont );
	m_buttonText.setString( buttonText );
	m_buttonText.setCharacterSize( textSize );
	m_buttonText.setOrigin( m_buttonText.getLocalBounds( ).width * 0.5f, m_buttonText.getLocalBounds( ).height * 0.7f ); //Sets origin to centre
	m_buttonText.setPosition( buttonPosX, buttonPosY );
	m_buttonText.setFillColor( sf::Color::Color( 43, 43, 43, 255 ) ); //Sets text colour to dark grey
}

bool Button::checkMouseCollision( const sf::Vector2i &mousePosition )
{
	//Checks if mouse position is within button bounds
	if( mousePosition.x > m_leftCollisionBound &&
		mousePosition.x < m_rightCollisionBound &&
		mousePosition.y > m_upperCollisionBound &&
		mousePosition.y < m_lowerCollisionBound )
	{
		if( !m_isHovered ) //If it's not hovered, the button changes colour to dark orange for player feedback
		{				   //Done this way to prevent setting the colour every update
			setColor( sf::Color::Color( 230, 130, 0, 255 ) );
		}
		m_isHovered = true;
		return true; //Returns that the button is not hovered
	}
	else
	{
		if( m_isHovered ) //Works the same as above, but resets the colour to buttons original colour
		{
			setColor( sf::Color::White );
		}
		m_isHovered = false;
		return false;
	}
}

sf::Text *Button::getText( )
{
	return &m_buttonText;
}