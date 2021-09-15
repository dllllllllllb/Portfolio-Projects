//Author: Maciej Dowbor
//Module: MED5149
//Date last accessed: 20/01/2021

#ifndef TEXTURES_H
#define TEXTURES_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

#include "Helpers.h"

//=====================================================================================================	
//Class		: Textures
//-----------------------------------------------------------------------------------------------------
//Purpose	: Loads and holds textures and fonts for easy access by other classes
//=====================================================================================================
struct Textures
{
	sf::Texture m_enemyShooter;
	sf::Texture m_enemyKamikaze;
	sf::Texture m_enemyTank;
	sf::Texture m_enemyElite;
	sf::Texture m_enemyBoss;
	sf::Texture m_player;
	sf::Texture m_bullet;
	sf::Texture m_healthDrop;
	sf::Texture m_shieldDrop;
	sf::Texture m_creditDrop;
	sf::Texture m_bombDrop;
	sf::Texture m_healthShopIcon;
	sf::Texture m_shieldShopIcon;
	sf::Texture m_speedShopIcon;
	sf::Texture m_rateOfFireShopIcon;
	sf::Texture m_doubleShotShopIcon;
	sf::Texture m_TripleShotShopIcon;
	sf::Texture m_QuadraShotShopIcon;
	sf::Texture m_button;
	sf::Texture m_tutorial;
	sf::Texture m_star;

	sf::Font m_font;
	sf::Font m_menuFont;

	Textures( );
	//=================================================================================================						
	//Purpose	: Constructor
	//-------------------------------------------------------------------------------------------------
	//Parameters: -
	//-------------------------------------------------------------------------------------------------
	//Returns	: -
	//=================================================================================================

	~Textures( );
	//=================================================================================================						
	//Purpose	: Destructor
	//-------------------------------------------------------------------------------------------------
	//Parameters: -
	//-------------------------------------------------------------------------------------------------
	//Returns	: -
	//=================================================================================================

	void loadTextures( );
	//=================================================================================================						
	//Purpose	: Loads textures and sets them to smooth
	//-------------------------------------------------------------------------------------------------
	//Parameters: -
	//-------------------------------------------------------------------------------------------------
	//Returns	: -
	//=================================================================================================

	void createTextures( );
	//=================================================================================================						
	//Purpose	: Creates star textures using an array of pixels
	//-------------------------------------------------------------------------------------------------
	//Parameters: -
	//-------------------------------------------------------------------------------------------------
	//Returns	: -
	//=================================================================================================

};

#endif // !TEXTURES_H
