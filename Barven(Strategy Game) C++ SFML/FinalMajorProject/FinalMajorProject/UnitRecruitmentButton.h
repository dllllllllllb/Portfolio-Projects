//Author: Maciej Dowbor
//Last Accessed: 21/07/2021

#ifndef UNITRECRUITMENTBUTTON_H
#define UNITRECRUITMENTBUTTON_H

#include "Button.h"
#include "TownRecruitmentSettings.h"

//===========================================================================================
//Description: Side button for selecting which unit to recruit
//===========================================================================================
class UnitRecruitmentButton : public Button
{
private:
	sf::Sprite m_unitIcon;
	int m_index;

public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	UnitRecruitmentButton(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts, Audio& rAudio);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~UnitRecruitmentButton();
	
	//===========================================================================================
	//Description: Repositions unit recruitment button
	//===========================================================================================
	void reposition(const float& positionX, const float& positionY);

	//===========================================================================================
	//Description: Sets up the button
	//===========================================================================================
	void setUpButton(const int& unitIndex, const std::string& unitName, const sf::Texture& unitIcon, const int& posX, const int& posY);

	//===========================================================================================
	//Description: Updates unit name and icon
	//===========================================================================================
	void updateUnitNameAndIcon(const std::string& unitName, const sf::Texture& unitIcon);

	//===========================================================================================
	//Description: Draws contents of this class
	//===========================================================================================
	void draw();

};

#endif // !UNITRECRUITMENTBUTTON_H

