//Author: Maciej Dowbor
//Module: MED5149
//Date last accessed: 20/01/2021

#include "ShopButton.h"

ShopButton::ShopButton( sf::RenderWindow &window ) :
	m_window( window )
{
}

ShopButton::~ShopButton( )
{
}

void ShopButton::shopButtonSetUp( const std::string &buttonName, const std::string &description, const std::string &price, const sf::Font &textFont, const int &nameTextSize, const int &descriptionTextSize, const sf::Texture &buttonTexture, const sf::Texture &iconTexture, const float &posX, const float &posY )
{
	//Button texture
	setTexture( buttonTexture, true );
	setOrigin( getLocalBounds( ).width * 0.5f, getLocalBounds( ).height * 0.5f );
	setPosition( posX, posY );

	//Icon
	m_itemIcon.setTexture( iconTexture, true );
	m_itemIcon.scale( 2, 2 );
	m_itemIcon.setOrigin( m_itemIcon.getLocalBounds( ).width * 0.5f, m_itemIcon.getLocalBounds( ).height * 0.5f );
	float itemIconPosX = posX - ( getLocalBounds( ).width * 0.5f ) + ( m_itemIcon.getLocalBounds( ).width * 0.5f ) + 15;
	m_itemIcon.setPosition( itemIconPosX + 16, posY );

	//Button collision bounds
	m_upperCollisionBound = posY - k_buttonHeightHalf;
	m_lowerCollisionBound = posY + k_buttonHeightHalf;
	m_rightCollisionBound = posX + k_buttonWidthHalf;
	m_leftCollisionBound  = posX - k_buttonWidthHalf;

	//Set font
	m_buttonText	.setFont( textFont );
	m_description	.setFont( textFont );
	m_price			.setFont( textFont );

	//Set font color
	m_buttonText	.setFillColor( sf::Color::Color( 43, 43, 43, 255 ) );
	m_description	.setFillColor( sf::Color::Color( 43, 43, 43, 255 ) );
	m_price			.setFillColor( sf::Color::Color( 43, 43, 43, 255 ) );

	//Set font size
	m_buttonText	.setCharacterSize( nameTextSize );
	m_description	.setCharacterSize( descriptionTextSize );
	m_price			.setCharacterSize( descriptionTextSize );

	//Set text
	m_buttonText	.setString( buttonName );
	m_description	.setString( description );
	m_price			.setString( price );

	//Set up text origin
	m_buttonText	.setOrigin( m_buttonText.getLocalBounds( ).width * 0.5f, m_buttonText.getLocalBounds( ).height * 0.5f );
	m_description	.setOrigin( 0, m_description.getLocalBounds( ).height * 0.5f );
	m_price			.setOrigin( m_price.getLocalBounds( ).width, m_price.getLocalBounds( ).height * 0.5f );

	//Set text position
	m_buttonText	.setPosition( posX + m_itemIcon.getLocalBounds( ).width * 0.5f, posY - getLocalBounds( ).height * 0.3f );
	m_description	.setPosition( itemIconPosX + m_itemIcon.getLocalBounds( ).width * 0.5f + 37, posY + getLocalBounds( ).height * 0.1f );
	m_price			.setPosition( posX + getLocalBounds( ).width * 0.5f - 15, posY + getLocalBounds( ).height * 0.1f );
}

void ShopButton::draw( )
{
	m_window.draw( m_itemIcon );
	m_window.draw( m_buttonText );
	m_window.draw( m_description );
	m_window.draw( m_price );
}