#include "Textures.h"
Textures::Textures()
{
	load();
}

Textures::~Textures()
{
}

void Textures::load()
{
	//UI Elements
	ASSERT(m_UICorner.loadFromFile("Assets/Sprites/UI/Corner.png"));
	ASSERT(m_UIFill.loadFromFile("Assets/Sprites/UI/Fill.png"));
	ASSERT(m_UIfillShader.loadFromFile("Assets/Sprites/UI/fillShader.png"));
	ASSERT(m_UIHorizontalBorder.loadFromFile("Assets/Sprites/UI/HorizontalBorder.png"));
	ASSERT(m_UIVerticalBorder.loadFromFile("Assets/Sprites/UI/VerticalBorder.png"));
	ASSERT(m_tickBoxTrue.loadFromFile("Assets/Sprites/UI/tickBoxTrue.png"));
	ASSERT(m_tickBoxFalse.loadFromFile("Assets/Sprites/UI/tickBoxFalse.png"));
	ASSERT(m_acceptButton.loadFromFile("Assets/Sprites/UI/acceptButton.png"));
	ASSERT(m_declineButton.loadFromFile("Assets/Sprites/UI/declineButton.png"));
	ASSERT(m_UIThinHorizontalBorder.loadFromFile("Assets/Sprites/UI/thinHorizontalBorder.png"));
	ASSERT(m_UIThinVerticalBorder.loadFromFile("Assets/Sprites/UI/thinVerticalBorder.png"));
	ASSERT(m_UIThinCorner.loadFromFile("Assets/Sprites/UI/thinCorner.png"));
	ASSERT(m_thinBorder.loadFromFile("Assets/Sprites/UI/thinBorder.png"));
	ASSERT(m_unitBackground[0].loadFromFile("Assets/Sprites/UI/unitBackgroundCastle.png"));
	ASSERT(m_unitBackground[1].loadFromFile("Assets/Sprites/UI/unitBackgroundInferno.png"));
	ASSERT(m_sliderBar.loadFromFile("Assets/Sprites/UI/sliderBar.png"));
	ASSERT(m_sliderHandle.loadFromFile("Assets/Sprites/UI/sliderHandle.png"));
	ASSERT(m_UIBar.loadFromFile("Assets/Sprites/UI/UIBar.png"));
	ASSERT(m_UIBarEnding.loadFromFile("Assets/Sprites/UI/UIBarEnding.png"));
	ASSERT(m_resourceUIIcons[0].loadFromFile("Assets/Sprites/UI/goldUIIcon.png"));
	ASSERT(m_resourceUIIcons[1].loadFromFile("Assets/Sprites/UI/woodUIIcon.png"));
	ASSERT(m_resourceUIIcons[2].loadFromFile("Assets/Sprites/UI/stoneUIIcon.png"));
	ASSERT(m_refreshIcon.loadFromFile("Assets/Sprites/UI/refreshIcon.png"));
	ASSERT(m_tradeIcon.loadFromFile("Assets/Sprites/UI/TradeIcon.png"));
	ASSERT(m_baseMapUIButtonIcon.loadFromFile("Assets/Sprites/UI/baseMapUIButtonIcon.png"));
	ASSERT(m_upArrowIcon.loadFromFile("Assets/Sprites/UI/arrowButtonIcon.png"));
	ASSERT(m_downArrowIcon.loadFromFile("Assets/Sprites/UI/arrowDownButtonIcon.png"));
	ASSERT(m_mapUIIconButtons[0].loadFromFile("Assets/Sprites/UI/MapUIWaitIcon.png"));
	ASSERT(m_mapUIIconButtons[1].loadFromFile("Assets/Sprites/UI/MapUISaveIcon.png"));
	ASSERT(m_mapUIIconButtons[2].loadFromFile("Assets/Sprites/UI/MapUISettingsIcon.png"));
	ASSERT(m_mapUIIconButtons[3].loadFromFile("Assets/Sprites/UI/MapUIExitIcon.png"));
	ASSERT(m_defaultHeroButtonIcon.loadFromFile("Assets/Sprites/UI/defaultHeroButtonIcon.png"));
	ASSERT(m_plusButton.loadFromFile("Assets/Sprites/UI/plusButton.png"));
	ASSERT(m_logo.loadFromFile("Assets/Sprites/UI/Logo.png"));


	//Resource Map Textures
	ASSERT(m_resourceTextures[0].loadFromFile("Assets/Sprites/MapObjects/Resources/GoldMapTexture.png"));
	ASSERT(m_resourceTextures[1].loadFromFile("Assets/Sprites/MapObjects/Resources/WoodMapTexture.png"));
	ASSERT(m_resourceTextures[2].loadFromFile("Assets/Sprites/MapObjects/Resources/StoneMapTexture.png"));
	ASSERT(m_resourceTextures[3].loadFromFile("Assets/Sprites/MapObjects/Resources/RandomResourceMapTexture.png"));

	//Tiles
	ASSERT(m_tileStart.loadFromFile("Assets/Sprites/Tiles/startTile.png"));
	ASSERT(m_tileEnd.loadFromFile("Assets/Sprites/Tiles/endTile.png"));
	ASSERT(m_tileObstacle.loadFromFile("Assets/Sprites/Tiles/obstacleTile.png"));
	ASSERT(m_tileVisited.loadFromFile("Assets/Sprites/Tiles/visitedTile.png"));
	ASSERT(m_tileNotVisited.loadFromFile("Assets/Sprites/Tiles/notVisitedTile.png"));
	ASSERT(m_tilePath.loadFromFile("Assets/Sprites/Tiles/pathTile.png"));
	ASSERT(m_tileOverlap.loadFromFile("Assets/Sprites/Tiles/tileOverlap.png"));
	ASSERT(m_combatTile.loadFromFile("Assets/Sprites/Tiles/combatTile.png"));
	ASSERT(m_combatTileFill.loadFromFile("Assets/Sprites/Tiles/combatTileFill.png"));

	//Terrain
	ASSERT(m_grassTiles.loadFromFile("Assets/Sprites/Tiles/Terrain/grassTiles.png"));

	//Landscapes

	//Tree
	ASSERT(m_treeLandscapes[0].loadFromFile("Assets/Sprites/Landscapes/trees0.png"));
	ASSERT(m_treeLandscapes[1].loadFromFile("Assets/Sprites/Landscapes/trees1.png"));
	ASSERT(m_treeLandscapes[2].loadFromFile("Assets/Sprites/Landscapes/trees2.png"));
	ASSERT(m_treeLandscapes[3].loadFromFile("Assets/Sprites/Landscapes/trees3.png"));

	//Rocky
	ASSERT(m_rockyLandscapes[2].loadFromFile("Assets/Sprites/Landscapes/mountain0.png"));
	ASSERT(m_rockyLandscapes[3].loadFromFile("Assets/Sprites/Landscapes/mountain1.png"));
	ASSERT(m_rockyLandscapes[4].loadFromFile("Assets/Sprites/Landscapes/mountain2.png"));
	ASSERT(m_rockyLandscapes[0].loadFromFile("Assets/Sprites/Landscapes/cliff0.png"));
	ASSERT(m_rockyLandscapes[1].loadFromFile("Assets/Sprites/Landscapes/cliff1.png"));
	ASSERT(m_rockyLandscapes[5].loadFromFile("Assets/Sprites/Landscapes/rocks0.png"));

	//Other
	ASSERT(m_otherLandscapes[0].loadFromFile("Assets/Sprites/Landscapes/hill0.png"));
	ASSERT(m_otherLandscapes[1].loadFromFile("Assets/Sprites/Landscapes/lake0.png"));
	ASSERT(m_otherLandscapes[2].loadFromFile("Assets/Sprites/Landscapes/lake1.png"));
	ASSERT(m_otherLandscapes[3].loadFromFile("Assets/Sprites/Landscapes/terrain0.png"));
	ASSERT(m_otherLandscapes[4].loadFromFile("Assets/Sprites/Landscapes/terrain1.png"));
	ASSERT(m_otherLandscapes[5].loadFromFile("Assets/Sprites/Landscapes/terrain2.png"));

	//Town
	ASSERT(m_unasignedTown.loadFromFile("Assets/Sprites/MapObjects/Towns/unasignedTown.png"));
	ASSERT(m_baseBuildingUpgradeSprite.loadFromFile("Assets//Sprites//Towns//Castle//castleBuildingTownHall.png"));

	//Units
	ASSERT(m_randomUnitIcon.loadFromFile("Assets/Sprites/Units/RandomUnitIcon.png"));
	ASSERT(m_randomUnitMapSprite.loadFromFile("Assets/Sprites/Units/RandomUnitMapSprite.png"));
	ASSERT(m_emptyUnitIcon.loadFromFile("Assets/Sprites/Units/EmptyUnitIcon.png"));

	//Special Buildings
	ASSERT(m_specialBuildings[0].loadFromFile("Assets/Sprites/MapObjects/SpecialBuildings/Arena.png"));
	ASSERT(m_specialBuildings[1].loadFromFile("Assets/Sprites/MapObjects/SpecialBuildings/WatchTower.png"));

	//Play Screen
	ASSERT(m_randomStartBonusIcon.loadFromFile("Assets/Sprites/UI/randomIcon.png"));
	ASSERT(m_startBonusIcons[0].loadFromFile("Assets/Sprites/UI/bonusGoldIcon.png"));
	ASSERT(m_startBonusIcons[1].loadFromFile("Assets/Sprites/UI/bonusResourcesIcon.png"));
	ASSERT(m_startBonusIcons[2].loadFromFile("Assets/Sprites/UI/bonusArtefactIcon.png"));

	//Cursor
	ASSERT(m_cursorIcons.loadFromFile("Assets/Sprites/MouseCursors/MapMovementCursors.png"));

	//Hero Skills
	ASSERT(m_heroPrimarySkills[0].loadFromFile("Assets/Sprites/Skills/Hero Skills/primarySkillAttack.png"));
	ASSERT(m_heroPrimarySkills[1].loadFromFile("Assets/Sprites/Skills/Hero Skills/primarySkillDefence.png"));
	ASSERT(m_heroPrimarySkills[2].loadFromFile("Assets/Sprites/Skills/Hero Skills/primarySkillMagicPower.png"));
	ASSERT(m_heroPrimarySkills[3].loadFromFile("Assets/Sprites/Skills/Hero Skills/primarySkillWisdom.png"));

	//Battle Backgrounds
	ASSERT(m_battleBackgrounds[0].loadFromFile("Assets//Sprites//Backgrounds//BattleBackground//CmBkGrTr.png"));
	ASSERT(m_battleBackgrounds[1].loadFromFile("Assets//Sprites//Backgrounds//BattleBackground//infernoBG.png"));

	//Battle button icons
	ASSERT(m_battleButtonIcons[0].loadFromFile("Assets/Sprites/UI/waitIcon.png"));
	ASSERT(m_battleButtonIcons[1].loadFromFile("Assets/Sprites/UI/defendIcon.png"));
	ASSERT(m_battleButtonIcons[2].loadFromFile("Assets/Sprites/UI/autoBattleIcon.png"));

	//Battle Textures
	ASSERT(m_currentUnitIndicator.loadFromFile("Assets/Sprites/UI/currentUnitIndicator.png"));
	ASSERT(m_bloodSplashSpriteSheet.loadFromFile("Assets/Sprites/SFX/bloodSplash.png"));
	ASSERT(m_combatCursorTexture.loadFromFile("Assets/Sprites/MouseCursors/combatCursors.png"));

	//Hero Movement Feecback
	ASSERT(m_heroMovementFeedback[0].loadFromFile("Assets/Sprites/HeroMovement/movementDirection.png"));
	ASSERT(m_heroMovementFeedback[1].loadFromFile("Assets/Sprites/HeroMovement/movementDirectionOFF.png"));
	ASSERT(m_heroMovementFeedback[2].loadFromFile("Assets/Sprites/HeroMovement/movementDestination.png"));
	ASSERT(m_heroMovementFeedback[3].loadFromFile("Assets/Sprites/HeroMovement/movementDestinationOFF.png"));
}