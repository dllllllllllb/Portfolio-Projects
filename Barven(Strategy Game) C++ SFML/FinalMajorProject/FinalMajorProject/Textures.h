//Author: Maciej Dowbor
//Last Accessed: 24/08/2021

#ifndef TEXTURES_H
#define TEXTURES_H

#include <SFML/Graphics/Texture.hpp>

#include "Macros.h"

//===========================================================================================
//Description: Loads and store textures
//===========================================================================================
struct Textures
{
	//UI Element
	sf::Texture m_UICorner;
	sf::Texture m_UIFill;
	sf::Texture m_UIfillShader;
	sf::Texture m_UIHorizontalBorder;
	sf::Texture m_UIVerticalBorder;
	sf::Texture m_tickBoxTrue;
	sf::Texture m_tickBoxFalse;
	sf::Texture m_acceptButton;
	sf::Texture m_declineButton;
	sf::Texture m_UIThinHorizontalBorder;
	sf::Texture m_UIThinVerticalBorder;
	sf::Texture	m_UIThinCorner;
	sf::Texture m_thinBorder;
	sf::Texture m_unitBackground[2];
	sf::Texture m_sliderBar;
	sf::Texture m_sliderHandle;
	sf::Texture m_UIBar;
	sf::Texture m_UIBarEnding;
	sf::Texture m_resourceUIIcons[3];
	sf::Texture m_refreshIcon;
	sf::Texture m_tradeIcon;
	sf::Texture m_baseMapUIButtonIcon;
	sf::Texture m_upArrowIcon;
	sf::Texture m_downArrowIcon;
	sf::Texture m_mapUIIconButtons[4];
	sf::Texture m_defaultHeroButtonIcon;
	sf::Texture m_plusButton;
	sf::Texture m_logo;

	//Resource Map Textures
	sf::Texture m_resourceTextures[4];

	//Tiles
	sf::Texture m_tileStart;
	sf::Texture m_tileEnd;
	sf::Texture m_tileObstacle;
	sf::Texture m_tileVisited;
	sf::Texture m_tileNotVisited;
	sf::Texture m_tilePath;
	sf::Texture m_tileOverlap;
	sf::Texture m_combatTile;
	sf::Texture m_combatTileFill;

	//Grass terrain
	sf::Texture m_grassTiles;

	//Landscapes
	sf::Texture m_treeLandscapes[4];
	sf::Texture m_rockyLandscapes[6];
	sf::Texture m_otherLandscapes[6];

	//Town
	sf::Texture m_unasignedTown;
	sf::Texture m_baseBuildingUpgradeSprite;

	//Units
	sf::Texture m_randomUnitIcon;
	sf::Texture m_randomUnitMapSprite;
	sf::Texture m_emptyUnitIcon;

	//Special Buildings
	sf::Texture m_specialBuildings[2];

	//PlayScreen
	sf::Texture m_randomStartBonusIcon;
	sf::Texture m_startBonusIcons[3];

	//Cursor
	sf::Texture m_cursorIcons;

	//HeroSkills
	sf::Texture m_heroPrimarySkills[4];

	//Battle Backgrounds
	sf::Texture m_battleBackgrounds[2];

	//Battle button icons
	sf::Texture m_battleButtonIcons[3];

	//Battle textures
	sf::Texture m_currentUnitIndicator;
	sf::Texture m_bloodSplashSpriteSheet;
	sf::Texture m_combatCursorTexture;

	//Hero Movement Feedback
	sf::Texture m_heroMovementFeedback[4];

	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	Textures();

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~Textures();

	//===========================================================================================
	//Description: Loads textures from files
	//===========================================================================================
	void load();
};

#endif // !TEXTURES_H
