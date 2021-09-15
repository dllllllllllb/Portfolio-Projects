//Author: Maciej Dowbor
//Last Accessed: 21/07/2021

#ifndef UNITCARD_H
#define UNITCARD_H

#include "IconButton.h"
#include "Text.h"

//===========================================================================================
//Description: Displays unit icon and number of units
//===========================================================================================
class UnitCard : public virtual IconButton, public virtual Text
{
private:
	sf::RenderWindow& m_window;
	bool m_hasUnit;
public:

	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	UnitCard(sf::RenderWindow& rWindow, Textures* pTextures, Fonts* pFonts);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~UnitCard();

	//===========================================================================================
	//Description: Toggles between true and false state to determine if this unit card has a unit
	//			   assigned to it
	//===========================================================================================
	void toggleHasUnit();

	//===========================================================================================
	//Description: Returns a bool if this unit card has a unit assigned to it
	//===========================================================================================
	const bool getHasUnit() const;

	//===========================================================================================
	//Description: Returns position of unit icon
	//===========================================================================================
	const sf::Vector2f& getPosition() const;

	//===========================================================================================
	//Description: Draw contents of this class
	//===========================================================================================
	void draw();
};

#endif // !UNITCARD_H
