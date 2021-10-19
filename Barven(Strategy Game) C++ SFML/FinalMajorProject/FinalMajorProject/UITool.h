//Author: Maciej Dowbor
//Last Accessed: 30/03/2021

#ifndef UITOOL_H
#define UITOOL_H

#include "Button.h"
#include "TextInputBox.h"
#include "UIToolSettings.h"

//===========================================================================================
//Description: Dev tool used to help visualize UI element in an easy to edit environment to 
//			   make sure that it has the right dimentions and is in the correct position
//			   without the need to access this element in the game. Uses "UIToolSettings.h"
//			   to set up input buttons.
//===========================================================================================
class UITool
{
private:
	sf::RenderWindow& m_window;

	Button m_UIToolApplyButton;

	std::vector<std::unique_ptr<TextInputBox>> m_dataInputButton;

public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	UITool(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts, Audio& rAudio);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~UITool();


	//===========================================================================================
	//Description: Initializes class objecs. Initializes button and input boxes
	//===========================================================================================
	void initialize();

	//===========================================================================================
	//Description: Sets button focus to false, if true, player can type inside the button
	//===========================================================================================
	void resetInputFieldsFocus();

	//===========================================================================================
	//Description: Checks each button and input field for mouse collision, updates input boxes and
	//			   returns a bool whether or not a button has been pressed 
	//===========================================================================================
	void update(const sf::Vector2f& mousePosition );

	//===========================================================================================
	//Description: Draws drawable objects of this class
	//===========================================================================================
	void draw();
};

#endif // !UITOOL_H

