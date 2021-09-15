//Author: Maciej Dowbor
//Last Accessed: 18/08/2021

#ifndef COMBATENDPOPUP_H
#define COMBATENDPOPUP_H

#include "CombatEndPopUpSettings.h"
#include "TextBox.h"
#include "BasicButton.h"

//===========================================================================================
//Description: Pop up defining outcome of the combat
//===========================================================================================
class CombatEndPopUp
{
private:
	sf::RenderWindow& m_window;
	TextBox m_combatEndInformation;
	BasicButton m_acceptButton;
public:

	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	CombatEndPopUp(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~CombatEndPopUp();

	//===========================================================================================
	//Description: Set up combat pop up
	//===========================================================================================
	void setUp();

	//===========================================================================================
	//Description: Sets title text
	//===========================================================================================
	void setTitleText(const bool didAttackerWon);

	//===========================================================================================
	//Description: Checks if the button was clicked and returns appropriate bool
	//===========================================================================================
	const bool update(const sf::Vector2f& mousePosition);

	//===========================================================================================
	//Description: Draws contents of this class
	//===========================================================================================
	void draw();
};


#endif // !COMBATENDPOPUP_H

