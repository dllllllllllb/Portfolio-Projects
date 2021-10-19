//Author: Maciej Dowbor
//Last Accessed: 19/10/2021

#ifndef BUTTON_H
#define BUTTON_H

#include "Audio.h"
#include "Fonts.h"
#include "GlobalVariables.h"
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
	Audio& m_audio;
	SFXEnum m_SFXToPlay;

public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	Button(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts, Audio& rAudio );

	//===========================================================================================
	//Description: Class constructor that determines border type
	//===========================================================================================
	Button(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts, Audio& rAudio, const bool setThinBorder);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~Button();
	
	//===========================================================================================
	//Description: Checks if mouse collides with the button and changes it's colour if hovered
	//===========================================================================================
	bool checkIfButtonWasPressed(const sf::Vector2f& mousePosition);

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

