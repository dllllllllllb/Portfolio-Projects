//Author: Maciej Dowbor
//Last Accessed: 17/05/2021

#ifndef UNITCREATIONTOOL_H
#define UNITCREATIONTOOL_H

#include "TextInputBox.h"
#include "DataHandler.h"
#include "UnitCreationSettings.h"
#include "DataHandlerSettings.h"

//===========================================================================================
//Description: Dev tool used to create and save Units that can be used in the game.
//			   *NOT UP TO DATE, WILL NOT WORK*
//===========================================================================================
class UnitCreationTool
{
private:
	sf::RenderWindow& m_window;

	UIElement m_unitImageBackground;

	std::vector<std::unique_ptr<TextInputBox>> m_dataInputButton;

	Button m_createUnitButton;

	DataHandler m_dataHandler;

public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	UnitCreationTool(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts, Audio& rAudio);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~UnitCreationTool();

	//===========================================================================================
	//Description: Initigalizes object of this class. Sets up Unit image background, input fields
	//			   and "Crate Unit" button;
	//===========================================================================================
	void initialize();

	//===========================================================================================
	//Description: Sets button focus to false, if true, player can type inside the button
	//===========================================================================================
	void resetInputFieldsFocus();

	//===========================================================================================
	//Description: Checks for mouse collision with input fields/buttons and updates input fields.
	//			   Returns if a button/input field has been pressed.
	//===========================================================================================
	void update(const sf::Vector2f& mousePosition);

	//===========================================================================================
	//Description: Saves unit data entered by the player
	//===========================================================================================
	void saveUnitData();

	//===========================================================================================
	//Description: Draws objects of this class
	//===========================================================================================
	void draw();
};

#endif // !UNITCREATIONTOOL_H
