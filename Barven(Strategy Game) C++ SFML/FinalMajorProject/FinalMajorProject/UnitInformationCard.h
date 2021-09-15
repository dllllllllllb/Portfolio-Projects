//Author: Maciej Dowbor
//Last Accessed: 02/08/2021

#ifndef UNITINFORMATIONCARD_H
#define UNITINFORMATIONCARD_H

#include "TextBox.h"
#include "CombatUnit.h"
#include "IconButton.h"
#include "UnitInformationCardSettings.h"

//===========================================================================================
//Description: Displays units stats
//===========================================================================================
class UnitInformationCard
{
private:
	sf::RenderWindow& m_window;
	Textures& m_textures;

	UIElement m_background;
	UIElement m_unitBackground;
	TextBox m_unitInformation;
	sf::Sprite m_unitSprite;

	bool m_isActive;

public:

	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	UnitInformationCard(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~UnitInformationCard();

	//===========================================================================================
	//Description: Set up elements of this class
	//===========================================================================================
	void initialize(const int& positionX, const int& positionY);

	//===========================================================================================
	//Description: Set unit data to display
	//===========================================================================================
	void setUnitData(CombatUnit& combatUnit);

	//===========================================================================================
	//Description: SEts unit data to display
	//===========================================================================================
	void setUnitData(Unit& unit);

	//===========================================================================================
	//Description: Resets unit data to display
	//===========================================================================================
	void resetUnitData();

	//===========================================================================================
	//Description: Toggles between isActive between true and false state
	//===========================================================================================
	void toggleIsActive();

	//===========================================================================================
	//Description: Sets isActive bool
	//===========================================================================================
	void setIsActive(const bool state);

	//===========================================================================================
	//Description: Return isActive bool
	//===========================================================================================
	const bool getIsActive() const;

	//===========================================================================================
	//Description: Draw elements of this class
	//===========================================================================================
	void draw();
};
#endif // !UNITINFORMATIONCARD_H
