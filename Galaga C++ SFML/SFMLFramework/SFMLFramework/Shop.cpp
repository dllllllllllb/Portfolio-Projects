//Author: Maciej Dowbor
//Module: MED5149
//Date last accessed: 20/01/2021

#include "Shop.h"

Shop::Shop( sf::RenderWindow &window, Textures *textures, Player *player ) :
	m_isActive		( false ),
	m_pTextures		( textures ),
	m_window		( window ),
	m_pPlayer		( player ),
	m_health		( window ),
	m_shield		( window ),
	m_rateOfFire	( window ),
	m_speed			( window ),
	m_weaponDouble	( window ),
	m_weaponTriple	( window ),
	m_weaponQuadra	( window ),
	m_pQuitText		( nullptr ),
	m_isLMBPressed	( false )

{
	ASSERT( m_buffer.loadFromFile( "Assets/Audio/Purchase.wav" ) );
	m_sound.setBuffer( m_buffer );
	m_sound.setVolume( k_purchaseVolume );

	setUpButtons( );
}

Shop::~Shop( )
{
}

void Shop::update( )
{
	mouseControl( );
}

void Shop::draw( )
{
	//Draws the button
	m_window.draw( m_health );
	m_window.draw( m_shield );
	m_window.draw( m_rateOfFire );
	m_window.draw( m_speed );
	m_window.draw( m_weaponDouble );
	m_window.draw( m_weaponTriple );
	m_window.draw( m_weaponQuadra );

	//Draws the content of the button
	m_health		.draw( );
	m_shield		.draw( );
	m_rateOfFire	.draw( );
	m_speed			.draw( );
	m_weaponDouble	.draw( );
	m_weaponTriple	.draw( );
	m_weaponQuadra	.draw( );
	m_window		.draw( m_quit );
	m_window		.draw( *m_pQuitText );
}

void Shop::setUpButtons( )
{
	m_health		.shopButtonSetUp( "Health", "Adds one health", std::to_string( k_healthPrice ), m_pTextures->m_font, k_shopNameCharSize, k_shopDescriptionCharSize, m_pTextures->m_button, m_pTextures->m_healthShopIcon, k_shopButtonPositionX, k_shopButtonPositionY );
	m_shield		.shopButtonSetUp( "Shield", "Adds one shield", std::to_string( k_shieldPrice ), m_pTextures->m_font, k_shopNameCharSize, k_shopDescriptionCharSize, m_pTextures->m_button, m_pTextures->m_shieldShopIcon, k_shopButtonPositionX, k_shopButtonPositionY + k_posYIncrement );
	m_rateOfFire	.shopButtonSetUp( "Rate of Fire", "Improves fire rate", std::to_string( k_rateOfFirePrice ), m_pTextures->m_font, k_shopNameCharSize, k_shopDescriptionCharSize, m_pTextures->m_button, m_pTextures->m_rateOfFireShopIcon, k_shopButtonPositionX, k_shopButtonPositionY + k_posYIncrement * 2 );
	m_speed			.shopButtonSetUp( "Speed", "Increases speed", std::to_string( k_speedPrice ), m_pTextures->m_font, k_shopNameCharSize, k_shopDescriptionCharSize, m_pTextures->m_button, m_pTextures->m_speedShopIcon, k_shopButtonPositionX, k_shopButtonPositionY + k_posYIncrement * 3 );
	m_weaponDouble	.shopButtonSetUp( "Double shot", "Shoots 2 bullets", std::to_string( k_weaponDoublePrice ), m_pTextures->m_font, k_shopNameCharSize, k_shopDescriptionCharSize, m_pTextures->m_button, m_pTextures->m_doubleShotShopIcon, k_shopButtonPositionX, k_shopButtonPositionY + k_posYIncrement * 4 );
	m_weaponTriple	.shopButtonSetUp( "Triple shot", "Shoots 3 bullets", std::to_string( k_weaponTriplePrice ), m_pTextures->m_font, k_shopNameCharSize, k_shopDescriptionCharSize, m_pTextures->m_button, m_pTextures->m_TripleShotShopIcon, k_shopButtonPositionX, k_shopButtonPositionY + k_posYIncrement * 5 );
	m_weaponQuadra	.shopButtonSetUp( "Quadra shot", "Shoots 4 bullets", std::to_string( k_weaponQuadraPrice ), m_pTextures->m_font, k_shopNameCharSize, k_shopDescriptionCharSize, m_pTextures->m_button, m_pTextures->m_QuadraShotShopIcon, k_shopButtonPositionX, k_shopButtonPositionY + k_posYIncrement * 6 );

	m_quit.setUp( "Exit Shop", m_pTextures->m_font, k_shopNameCharSize, m_pTextures->m_button, k_shopButtonPositionX, k_shopButtonPositionY + k_posYIncrement * 7 );
	m_pQuitText = m_quit.getText( );
}

void Shop::mouseControl( )
{
	if( !m_mouse.isButtonPressed( sf::Mouse::Button::Left ) )
	{
		m_isLMBPressed = false;
	}

	if( m_health.checkMouseCollision( m_mouse.getPosition( m_window ) ) && m_mouse.isButtonPressed( sf::Mouse::Button::Left ) ) //Checks if mouse is hovered over button and if left mouse button is pressed
	{
		if( m_pPlayer->getValue( PlayerValues::health ) < k_maxPlayerHealth ) //Checks if player can purchase this
		{
			if( checkForCredits( k_healthPrice, m_pPlayer->getValue( PlayerValues::credits ) ) ) //Checks if player has enough credits to purchase this
			{
				m_pPlayer->changeValueInt( PlayerValues::health, k_healthShopIncrement );
			}
		}
		else
		{
			m_health.setColor( sf::Color::Red ); //Changes button colour to red if player cant purchase it
		}
	}

	if( m_shield.checkMouseCollision( m_mouse.getPosition( m_window ) ) && m_mouse.isButtonPressed( sf::Mouse::Button::Left ) )
	{
		if( m_pPlayer->getValue( PlayerValues::shield ) < k_maxPlayerShield )
		{
			if( checkForCredits( k_shieldPrice, m_pPlayer->getValue( PlayerValues::credits ) ) )
			{
				m_pPlayer->changeValueInt( PlayerValues::shield, k_shieldShopIncrement );
			}
		}
		else
		{
			m_shield.setColor( sf::Color::Red );
		}
	}

	if( m_rateOfFire.checkMouseCollision( m_mouse.getPosition( m_window ) ) && m_mouse.isButtonPressed( sf::Mouse::Button::Left ) )
	{
		if( checkForCredits( k_rateOfFirePrice, m_pPlayer->getValue( PlayerValues::credits ) ) )
		{
			m_pPlayer->changeValueFloat( PlayerValues::rateOfFire, k_rateOfFireShopIncrement );
		}
	}

	if( m_speed.checkMouseCollision( m_mouse.getPosition( m_window ) ) && m_mouse.isButtonPressed( sf::Mouse::Button::Left ) )
	{
		if( checkForCredits( k_speedPrice, m_pPlayer->getValue( PlayerValues::credits ) ) )
		{
			m_pPlayer->changeValueFloat( PlayerValues::speed, k_speedShopIncrement );
		}
	}

	if( m_weaponDouble.checkMouseCollision( m_mouse.getPosition( m_window ) ) && m_mouse.isButtonPressed( sf::Mouse::Button::Left ) )
	{
		if( m_pPlayer->getWeaponType( ) != PlayerWeapons::doubleShot )
		{
			if( checkForCredits( k_weaponDoublePrice, m_pPlayer->getValue( PlayerValues::credits ) ) )
			{
				m_pPlayer->setWeaponType( PlayerWeapons::doubleShot );
			}
		}
	}

	if( m_weaponTriple.checkMouseCollision( m_mouse.getPosition( m_window ) ) && m_mouse.isButtonPressed( sf::Mouse::Button::Left ) )
	{
		if( m_pPlayer->getWeaponType( ) != PlayerWeapons::tripleShot )
		{
			if( checkForCredits( k_weaponTriplePrice, m_pPlayer->getValue( PlayerValues::credits ) ) )
			{
				m_pPlayer->setWeaponType( PlayerWeapons::tripleShot );
			}
		}
	}

	if( m_weaponQuadra.checkMouseCollision( m_mouse.getPosition( m_window ) ) && m_mouse.isButtonPressed( sf::Mouse::Button::Left ) )
	{
		if( m_pPlayer->getWeaponType( ) != PlayerWeapons::quadraShot )
		{
			if( checkForCredits( k_weaponQuadraPrice, m_pPlayer->getValue( PlayerValues::credits ) ) )
			{
				m_pPlayer->setWeaponType( PlayerWeapons::quadraShot );
			}
		}
	}

	if( m_quit.checkMouseCollision( m_mouse.getPosition( m_window ) ) && m_mouse.isButtonPressed( sf::Mouse::Button::Left ) )
	{
		toggleActiveState( );
	}
}

bool Shop::checkForCredits( const int &price, const int &playerCredits )
{
	if( playerCredits >= price && !m_isLMBPressed )
	{
		m_isLMBPressed = true;
		m_pPlayer->changeValueInt( PlayerValues::credits, -price );
		playSound( );
		return true;
	}
	else
	{
		return false;
	}
}

bool Shop::getAcviteState( )
{
	return m_isActive;
}

void Shop::toggleActiveState( )
{
	m_isActive = !m_isActive;
}

void Shop::playSound( )
{
	m_sound.play( );
}