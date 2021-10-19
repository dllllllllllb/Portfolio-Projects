//Author: Maciej Dowbor
//Last Accessed: 21/07/2021

#ifndef UIELEMENT_H
#define UIELEMENT_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "CollidableObject.h"
#include "Textures.h"

//===========================================================================================
//Description: Resizeable border that acs as a background for all UI Elements
//===========================================================================================
class UIElement : public sf::Sprite
{
protected:
	sf::RenderWindow& m_window;
	Textures& m_textures;
	sf::Sprite m_fillShader;
	sf::Sprite m_borderTop;
	sf::Sprite m_borderBottom;
	sf::Sprite m_borderLeft;
	sf::Sprite m_borderRight;
	sf::Sprite m_cornerTopLeft;
	sf::Sprite m_cornerTopRight;
	sf::Sprite m_cornerBottomLeft;
	sf::Sprite m_cornerBottomRight;

	bool m_isShaderActive;
	bool m_setUpFillShader;

public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	UIElement(sf::RenderWindow& window, Textures& rTextures);

	//===========================================================================================
	//Description: Class constructor that sets border type
	//===========================================================================================
	UIElement(sf::RenderWindow& window, Textures& rTextures, const bool useThinBorder);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~UIElement();

	//===========================================================================================
	//Description: Sets default border textures
	//===========================================================================================
	void setDefaultTextures();

	//===========================================================================================
	//Description: Sets thin border textures
	//===========================================================================================
	void setThinUIBorder();

	//===========================================================================================
	//Description: Sets up border elements based on the given dimentions
	//===========================================================================================
	void setUpUIBorder(const float& width, const float& height);

	//===========================================================================================
	//Description: Sets up fill shader to match button dimentions and position
	//===========================================================================================
	void setUpFillShader();

	//===========================================================================================
	//Description: Changes colour of the border
	//===========================================================================================
	void setBorderColor(const sf::Color& color);

	//===========================================================================================
	//Description: Moves border by given values
	//===========================================================================================
	void moveUIElement(const float& posX, const float& posY);

	//===========================================================================================
	//Description: Moves border
	//===========================================================================================
	void moveBorder(const float& posX, const float& posY);

	//===========================================================================================
	//Description: Toggles fill shader between true and false state
	//===========================================================================================
	void toggleIsShaderActive();

	//===========================================================================================
	//Description: Draws border and background of UI element
	//===========================================================================================
	void drawUIBorderAndBackground();

	//===========================================================================================
	//Description: Draws background of UI element
	//===========================================================================================
	void drawUIBackground();

	//===========================================================================================
	//Description: Draws border of UI element
	//===========================================================================================
	void drawUIBorder();

	//===========================================================================================
	//Description: Draws fill shader
	//===========================================================================================
	void drawFillShader();
};

#endif // !UIELEMENT_H
