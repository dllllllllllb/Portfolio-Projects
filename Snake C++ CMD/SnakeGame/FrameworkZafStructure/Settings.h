//Author: Maciej Dowbor
//Module: MED5148
//Date last accessed: 28/10/2020

#ifndef SETTINGS_H
#define SETTINGS_H

//Menu options
const int g_selectedTextColour = 15;
const int g_unselectedTextColour = 8;

//Characters
const char g_snakeChar = 'O';
const char g_borderChar = -2; //Border char  *Solid block: (char)254u || -2
const char g_fruitChar = 'X';

//Border origin
const int g_borderOriginX = 20;
const int g_borderOriginY = 5;

//Border size
const int g_borderSizeX = 80;
const int borderSizeY = 25;

//Border collision
const int g_borderCollRight = g_borderOriginX + g_borderSizeX;
const int g_borderCollBottom = g_borderOriginY + borderSizeY;

//Player start position
const int g_snakeStartX = 59;
const int g_snakeStartY = 18;

//Game state
enum class GameState { menu, game, defeat, highscore };
extern GameState g_gameState;

//Difficulty
extern int difficulty;
const int diffEasy = 225;
const int diffNormal = 150;
const int diffHard = 75;

//Score
const int m_scoreIncrement = 10;
#endif
