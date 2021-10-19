//Author: Maciej Dowbor
//Last Accessed: 29/04/2021

#ifndef TEXTINPUTBOX_H
#define TEXTINPUTBOX_H

#include "Button.h"
#include "TextBoxTitle.h"
#include "GlobalVariables.h"

//===========================================================================================
//Description: Allows the player to enter text inside this box when clicked on
//===========================================================================================
class TextInputBox : public virtual Button
{
private:
	std::string m_playerInput;
	bool m_isButtonPressed;
	bool m_canGetInput;

public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	TextInputBox( sf::RenderWindow& rWindow, Textures &rTextures, Fonts& rFonts, Audio& rAudio);

	//===========================================================================================
	//Description: Class constructor that sets border type
	//===========================================================================================
	TextInputBox(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts, Audio& rAudio, const bool setThinBorder);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~TextInputBox();

	//===========================================================================================
	//Description: Sets the position of the input text
	//===========================================================================================
	void setInputTextPosition();

	//===========================================================================================
	//Description: Registers key pressed and adds it to playerInput string
	//===========================================================================================
	void textInput();

	//===========================================================================================
	//Description: Sets drawable text to playerInput string
	//===========================================================================================
	void updateInputText();

	//===========================================================================================
	//Description: Checks if the button is selected and calls userFeedback()
	//===========================================================================================
	void update();

	//===========================================================================================
	//Description: Draws content of this class
	//===========================================================================================
	void draw();

	//===========================================================================================
	//Description: Toggles is the button is pressed bool
	//===========================================================================================
	void buttonPressedToggle();

	//===========================================================================================
	//Description: Sets button pressed bool
	//===========================================================================================
	void setButtonPressed(bool state);

	//===========================================================================================
	//Description: Returns button pressed bool
	//===========================================================================================
	const bool getIsButtonPressed() const;

	//===========================================================================================
	//Description: Changes colour of the input box based on if its selected
	//===========================================================================================
	void userFeedback();

	//===========================================================================================
	//Description: Sets player input
	//===========================================================================================
	void setPlayerInput(const std::string& string);

	//===========================================================================================
	//Description: Returns player input
	//===========================================================================================
	const std::string& getPlayerInput() const;
};

#endif // !TEXTINPUTBOX_H
