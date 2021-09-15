//Author: Maciej Dowbor
//Last Accessed: 21/07/2021

#ifndef TOWNBUILDINGUPGRADE_H
#define TOWNBUILDINGUPGRADE_H

#include "Button.h"
#include "TownBuildingSettings.h"
//===========================================================================================
//Description: Special upgrade button for town buildings.
//===========================================================================================
class TownBuildingUpgrade : public Button
{
private:
	sf::Sprite m_buildingUpgradeSprite;
	sf::Sprite m_imageTextBorder;
	bool m_canBePurchased;

public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	TownBuildingUpgrade(sf::RenderWindow& rWindow, Textures* pTextures, Fonts* pFonts);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~TownBuildingUpgrade();

	//===========================================================================================
	//Description: Repositions town building buttons
	//===========================================================================================
	void reposition(const float& positionX, const float& positionY);

	//===========================================================================================
	//Description: Basic setup using placeholders
	//===========================================================================================
	void baseSetUp(const int& positionX, const int& positionY);

	//===========================================================================================
	//Description: Determines if the building can be purchased
	//===========================================================================================
	void setCanBePurchased(const bool state);

	//===========================================================================================
	//Description: Toggles between true and false state
	//===========================================================================================
	void toggleCanBePurchased();

	//===========================================================================================
	//Description: Returns if the building can be purchased
	//===========================================================================================
	const bool getCanBePurchased() const;

	//===========================================================================================
	//Description: Sets up button with appropriate name and texture
	//===========================================================================================
	void setNameAndTexture(const std::string& buildingName, const sf::Texture& texture);

	//===========================================================================================
	//Description: Draws contents of this class
	//===========================================================================================
	void draw();

};

#endif // !TOWNBUILDINGUPGRADE_H

