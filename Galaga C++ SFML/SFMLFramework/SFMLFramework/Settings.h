//Author: Maciej Dowbor
//Module: MED5149
//Date last accessed: 20/01/2021

#ifndef SETTINGS_H
#define SETTINGS_H

#include <SFML/Graphics.hpp>
#include <string>
#include "GameStateEnum.h"

//--------------------------------------------------------------------------
//Purpose of Settings.h is to store global and constant variables that
//need to be accessed by multiple scripts or kept in the same place to have
//quick access to variables that define the gameplay
//--------------------------------------------------------------------------

//Determines the state of the game
extern GameState g_gameState;

//------------------------------------------
//Window variables
//------------------------------------------
const int k_windowSizeX = 1920;
const int k_windowSizeY = 1080;
const int k_frameRateLimit = 144;
const std::string k_windowName = "PepeInvaders";
extern bool g_isWindowSelected; //Tracks if the player has the window selected to make sure that controlls won't work if they click off the window

//------------------------------------------
//player
//------------------------------------------
const sf::Vector2f k_playerStartPosition( 1000, 1000 );
const float k_playerSpeed = 1000.0f;
const float k_playerRotationSpeed = 100.0f;
const float k_playerRateOfFire = 0.5f;
const int k_bombDamage = 1;
const int k_maxPlayerHealth = 3;
const int k_maxPlayerShield = 3;
const float k_invulnerabilityTime = 1.0f;

//Bullets
const int k_numOfBullets = 100;
const float k_bulletSpeedY = -1000.0f;
const float k_bulletSpeedX = 500.0f;

//------------------------------------------
//Enemy handler
//------------------------------------------
const float k_enemyMinPosX = 96;
const float k_enemyMinPosY = 100;
const int k_enemiesPerRow = 28;
const float k_timeBetweenActivatingEnemies = 0.15f;

//-------------------------------------------
//Enemy Stats
//-------------------------------------------
const int k_enemyChanceToshootRange = 10000;
//Base stats
const float k_initialEnemySpeed = 500.f;
const float k_enemySpeed = 300.f;
const int k_enemyRateOfFire = 10; //Lower == shoots faster
const int k_enemyHealth = 1;
const float k_damageIndicatorTime = 0.1f;
const int k_enemyDamage = 1;

//Kamikaze enemy
const float k_enemyKamikazeSpeed = 400.0f;
const int k_enemyKamikazeHealth = 3;
const int k_enemyKamikazeRateOfFire = 10;

//Shooter enemy
//Uses base stats

//Tank enemy
const float k_enemyTankSpeed = 300.0f;
const int k_enemyTankHealth = 6;
const int k_enemyTankRateOfFire = 30;
const float k_enemyTankBehaviourSpeed = 100.0f;

//Elite enemy
//Uses base speed
const int k_enemyEliteHealth = 5;
const int k_enemyEliteRateOfFire = 6;

//Boss enemy
const float k_enemyBossSpeed = 100.0f;
const int k_enemyBossHealth = 50;
const int k_enemyBossRateOfFire = 5;

//-------------------------------------------
//Enemy Behaviour
//-------------------------------------------
const sf::Vector2f k_enemyStartPosition( k_windowSizeX * 0.5, -100 );
const sf::Vector2f k_enemyInitialManouver( k_windowSizeX * 0.5f, k_windowSizeY * 0.75f );

const float k_behaviourRNGInterval = 7.5f;
const int k_chanceToSwitchBehaviour = 10;

const int k_numOfBehavioursShooter = 1;
const int k_numOfBehavioursKamikaze = 2;
const int k_numOfBehavioursTank = 1;
const int k_numOfBehavioursElite = 1;
const int k_numOfBehavioursBoss = 1;

//Enemy behaviour chance ratios
const int k_enemyDiveChance = 2;
const int k_enemyKamikazeChance = 5;
const int k_enemyMoveRightChance = 1;

//Bullets
const int k_numOfEnemyBullets = 100;
const float k_enemyBulletSpeed = 1000.0f;

//Dive
const float k_diveManeuverDepth = 1000.0f;
const int k_diveOscillationInterval = 12;
const int k_diveOscilationDistanceX = 200;

//Idle
const float k_idleAnimationSpeed = 20.0f;
const int k_idleAnimationXRange = 25;
const float k_idleAnimationXCoefficient = 0.0001f;

//------------------------------------------
//Wave Handler
//------------------------------------------
const int k_numOfWaves = 25;
const int k_numOfEnemyRows = 5;

//------------------------------------------
//Enemy Drops
//------------------------------------------
const int k_dropSpawnRNG = 10;
const int k_numOfDropTypes = 4;
const int k_numOfMoneyValues = 3;
const int k_numOfDrops = 10;
const float k_dropsSpeed = 200.0f;

//------------------------------------------
//User Interface
//------------------------------------------
const int k_UIPositionY = 5;
const int k_textHealthPositionX = 100;
const int k_textShieldPositionX = 400;
const int k_textCreditsPositionX = 700;
const int k_textWavePositionX = 1320;
const int k_textScorePositionX = 1620;

const int k_scoreIncrement = 20;
const int k_creditIncrementSmall = 10;
const int k_creditIncrementMedium = 20;
const int k_creditIncrementLarge = 50;
const int k_healthIncrement = 1;
const int k_shieldIncrement = 1;

//------------------------------------------
//Menu
//------------------------------------------
const int k_buttonPositionX = k_windowSizeX / 2;
const int k_buttonPositionY = 500;

const int k_characterSize = 40;

const int k_buttonWidthHalf = 150; //Used to check button collision
const int k_buttonHeightHalf = 50;

const sf::Vector2f k_exitButtonPosition( k_windowSizeX * 0.9f, k_windowSizeY * 0.9f );

//------------------------------------------
//Background
//------------------------------------------
const int k_backgroundStarSpeed = 100;
const int k_starSpawnY = -5;
const int k_starDespawnY = k_windowSizeY + 5;

const int k_numOfBackgroundStars = 100;

//------------------------------------------
//Shop
//------------------------------------------
const int k_shopButtonPositionX = k_buttonPositionX;
const int k_shopButtonPositionY = 200;
const int k_posYIncrement = 110;
const int k_shopNameCharSize = 32;
const int k_shopDescriptionCharSize = 20;

//Shop prices
const int k_healthPrice = 300;
const int k_shieldPrice = 100;
const int k_rateOfFirePrice = 100;
const int k_speedPrice = 100;
const int k_weaponDoublePrice = 300;
const int k_weaponTriplePrice = 500;
const int k_weaponQuadraPrice = 800;

//Upgrade values
const int k_healthShopIncrement = 1;
const int k_shieldShopIncrement = 1;
const float k_rateOfFireShopIncrement = -0.02f;
const int k_speedShopIncrement = 50;
//Weapons are enabled/disabled by using bools in player entity

//------------------------------------------
//High Score Table
//------------------------------------------
const int k_numOfHighScores = 20;
const std::string k_highScoreFileName = "HighScore.txt";

//High Score banner
const std::string k_highScoreBannerText = "High Scores";
const int k_highScoreBannerFontSize = 80;
const int k_highScoreBannerPositionY = 80;

//High Score text
const int k_highScoreFontSize = 40;
const int k_highScoreTextPositionX = k_windowSizeX / 2;
const int k_highScoreTextPositionY = 200;
const int k_highScoreTextSpacing = 40;

//------------------------------------------
//Defeat / Victory
//------------------------------------------
const int k_bannerTextSize = 100;
const int k_scoreAndInstructionsSize = 60;
const sf::Vector2f k_bannerTextPosition( k_windowSizeX / 2, 100 );
const sf::Vector2f k_finalScoreTextPosition( k_windowSizeX / 2, 300 );
const sf::Vector2f k_instructionsTextPosition( k_windowSizeX / 2, 900 );

//------------------------------------------
//Audio
//------------------------------------------
const int k_numOfBulletSoundBuffers = 20;
const int k_numOfExplosionBuffers = 5;

const int k_shootVolume = 10;
const int k_musicVolume = 10;
const int k_pickupVolume = 200;
const int k_coinPickupVolume = 60;
const int k_takingDamageVolume = 300;
const int k_explosionVolume = 10;
const int k_purchaseVolume = 10;

#endif // !SETTINGS_H