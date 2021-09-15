//Author: Maciej Dowbor
//Last Accessed: 10/09/2021

#ifndef GAMEEND_H
#define GAMEEND_H

#include "GameEndSettings.h"
#include "TextBox.h"
#include "Player.h"
#include "TurnHandler.h"
#include "Button.h"
#include "GlobalVariables.h"

//===========================================================================================
//Description: End game screen that displays winners stats and allows the player to return to 
//			   the main menu
//===========================================================================================
class GameEnd
{
private:
	TextBox m_gameInformation;
	Button m_backToMenuButton;
public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	GameEnd(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~GameEnd();

	//===========================================================================================
	//Description: Sets end game winner stats
	//===========================================================================================
	void setEndGameInformation(Player& rPlayer, const bool didPlayerWin, TurnHandler& rTurnHandler);

	//===========================================================================================
	//Description: Updates elements of this class
	//===========================================================================================
	void update(const sf::Vector2f& mousePosition);

	//===========================================================================================
	//Description: Draws elements of this class
	//===========================================================================================
	void draw();
};

#endif // !GAMEEND_H

