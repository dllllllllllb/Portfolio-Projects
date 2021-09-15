//Author: Maciej Dowbor
//Last Accessed: 24/08/2021

#ifndef ICONBUTTON_H
#define ICONBUTTON_H

#include "UIElement.h"
#include "CollidableObject.h"

//===========================================================================================
//Description: A button with no text that displays an Icon at its centre
//===========================================================================================
class IconButton : public UIElement, public CollidableObject
{
private:

protected:
	sf::Sprite m_buttonIcon;

public:

	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	IconButton(sf::RenderWindow& rWindow, Textures* pTextures);

	//===========================================================================================
	//Description: Class constructor that sets border type
	//===========================================================================================
	IconButton(sf::RenderWindow& rWindow, Textures* pTextures, const bool setThinBorder);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~IconButton();

	//===========================================================================================
	//Description: Sets position of all class elements
	//===========================================================================================
	void setPosition(const int& positionX, const int& positionY);

	//===========================================================================================
	//Description: Sets up contents of the button, icon is resized to fit inside the button
	//===========================================================================================
	void setUp(const float& positionX, const float& positionY, const float& width, const float& height, const sf::Texture* iconTexture);

	//===========================================================================================
	//Description: Sets up contents of the button, the button is resized to the size of the icon
	//===========================================================================================
	void setUpAndResizeToSprite(const float& positionX, const float& positionY, const sf::Texture& pIconTexture);

	//===========================================================================================
	//Description: Sets button icon
	//===========================================================================================
	void setButtonIcon(const sf::Texture& iconTexture);

	//===========================================================================================
	//Description: Returns button icon
	//===========================================================================================
	sf::Sprite& getIconSprite();

	//===========================================================================================
	//Description: Draws contents of this class
	//===========================================================================================
	void draw();

	//===========================================================================================
	//Description: Draws contents of this class without the border
	//===========================================================================================
	void drawWithoutUIBackground();
};

#endif // !ICONBUTTON_H

