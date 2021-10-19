//Author: Maciej Dowbor
//Last Accessed: 02/08/2021

#ifndef UNITTURNORDERBAR_H
#define UNITTURNORDERBAR_H

#include "UnitTurnOrderBarSettings.h"
#include "UIElement.h"
#include "UnitCard.h"
#include "CombatUnit.h"

//===========================================================================================
//Description: Displays unit cards in descending order based on their speed
//===========================================================================================
class UnitTurnOrderBar
{
private:
	sf::RenderWindow& m_window;
	UIElement m_background;
	std::vector<std::unique_ptr<UnitCard>> m_unitCards;
public:

	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	UnitTurnOrderBar(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts, Audio& rAudio);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~UnitTurnOrderBar();

	//===========================================================================================
	//Description: Set up turn order bar
	//===========================================================================================
	void setUp(const int& positionY);

	//===========================================================================================
	//Description: Fill up the bar with unit cards in descending order of their speed
	//===========================================================================================
	void setUnitCards(std::vector<std::unique_ptr<CombatUnit>>& combatUnitVector, std::vector<int>& unitOrder);

	//===========================================================================================
	//Description: Draw elements of this class
	//===========================================================================================
	void draw();
};
#endif // !UNITTURNORDERBAR_H