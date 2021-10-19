//Author: Maciej Dowbor
//Last Accessed: 21/07/2021

#ifndef RESOURCETRADINGBUTTON_H
#define RESOURCETRADINGBUTTON_H

#include "Button.h"
#include "Text.h"
#include "ResourcesEnum.h"
#include "ResourceTradingButtonSettings.h"

//===========================================================================================
//Description: Special button for trading resources, displays resource icon and amount of
//			   resource selected
//===========================================================================================
class ResourceTradingButton : public Button
{
private:
	Textures& m_textures;
	sf::Sprite m_resourceSprite;
	sf::Sprite m_imageTextBorder;
	int m_resourceAmount;
public:

	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	ResourceTradingButton(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts, Audio& rAudio);


	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	~ResourceTradingButton();

	//===========================================================================================
	//Description: Sets up button using giver position coordinates, type of resource and base
	//			   amount of resources to display
	//===========================================================================================
	void setUp(const int& positionX, const int& positionY, const ResourcesEnum& resourceType, const std::string& resourceAmount);

	//===========================================================================================
	//Description: Sets resource amount
	//===========================================================================================
	void setResourceAmount(const int& resourceAmount);

	//===========================================================================================
	//Description: Returns resource amount
	//===========================================================================================
	const int& getResourceAmount();

	//===========================================================================================
	//Description: Draws contents of this class
	//===========================================================================================
	void draw();
};


#endif // !RESOURCETRADINGBUTTON_H

