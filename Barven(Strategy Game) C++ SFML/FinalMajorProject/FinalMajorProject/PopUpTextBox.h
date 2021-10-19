//Author: Maciej Dowbor
//Last Accessed: 18/08/2021

#ifndef POPUPTEXTBOX_H
#define POPUPTEXTBOX_H

#include "ConstantVariables.h"
#include "TextBox.h"

//===========================================================================================
//Description: Text box that takes in a string, divides it to lines, centres it and resizes 
//			   text box to fit text size.
//===========================================================================================
class PopUpTextBox
{
private:
	sf::RenderWindow& m_window;
	TextBox m_textBox;
	bool m_isActive;
public:

	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	PopUpTextBox(sf::RenderWindow& window, Textures& rTextures, Fonts& rFonts);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~PopUpTextBox();

	//===========================================================================================
	//Description: Resets UI border, sets text and resizes the box to fit text
	//===========================================================================================
	void setUpPopUp(const std::string& text);

	//===========================================================================================
	//Description: Sets the width of the pop up box
	//===========================================================================================
	void setPopUpWidth(const int& popUpWidth);

	//===========================================================================================
	//Description: Sets position of the text box and updates text alignment
	//===========================================================================================
	void setPosition(const sf::Vector2f& mousePosition);

	//===========================================================================================
	//Description: Sets position of the text box and updates text alignment
	//===========================================================================================
	void setPosition(const int& positionX, const int& positionY);

	//===========================================================================================
	//Description: Toggles is active bool
	//===========================================================================================
	void toggleIsActive();

	//===========================================================================================
	//Description: Sets is active bool
	//===========================================================================================
	void setIsActive(const bool state);

	//===========================================================================================
	//Description: Returns is active bool
	//===========================================================================================
	const bool getActiveState() const;

	//===========================================================================================
	//Description: Draws content of this class
	//===========================================================================================
	void drawPopUpBox();


};

#endif // !POPUPTEXTBOX_H

