//Author: Maciej Dowbor
//Last Accessed: 29/04/2021

#ifndef BUTTON_H
#define BUTTON_H

#include "Fonts.h"
#include "UIElement.h"
#include "Text.h"
#include "CollidableObject.h"
#include "TextBoxTitle.h"


//===========================================================================================
//Description: Advanced button, can be any size and have custom text
//===========================================================================================
class Button : public CollidableObject, public Text, virtual public TextBoxTitle
{
private:

protected:

public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	Button(sf::RenderWindow& window, Textures* textures, Fonts* fonts );

	//===========================================================================================
	//Description: Class constructor that determines border type
	//===========================================================================================
	Button(sf::RenderWindow& window, Textures* textures, Fonts* fonts, const bool setThinBorder);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~Button();
	
	//===========================================================================================
	//Description: Checks if mouse collides with the button and changes it's colour if hovered
	//===========================================================================================
	bool checkMouseCollision(const sf::Vector2f& mousePosition);

	//===========================================================================================
	//Description: Sets position of all button elements
	//===========================================================================================
	void setPosition(const float& x, const float& y);

	//===========================================================================================
	//Description: Repositions the button
	//===========================================================================================
	void reposition(const float& positionX, const float& positionY);

	//===========================================================================================
	//Description: Draws content of this class
	//===========================================================================================
	void draw();

	//===========================================================================================
	//Description: Draws text inside the button
	//===========================================================================================
	void drawButtonText();

	//===========================================================================================
	//Description: Returns self
	//===========================================================================================
	const Button* getSelf() const;

	//===========================================================================================
	//Description: Returns buttons centre position
	//===========================================================================================
	const sf::Vector2f& getPosition() const;
};

#endif // !BUTTON_H

