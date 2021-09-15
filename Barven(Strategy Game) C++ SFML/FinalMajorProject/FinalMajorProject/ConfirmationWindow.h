//Author: Maciej Dowbor
//Last Accessed: 21/07/2021

#ifndef CONFIRMATIONWINDOW_H
#define CONFIRMATIONWINDOW_H

#include <functional>

#include "BasicButton.h"
#include "GlobalVariables.h"
#include "TextBoxTitle.h"

//===========================================================================================
//Description: Confirmation window. Allows to set a memory pointer to any function and call
//			   it from this class using m_pFunction. Confirms player input.
//===========================================================================================
class ConfirmationWindow : public TextBoxTitle
{
private:
	BasicButton m_acceptButton;
	BasicButton m_declineButton;

	std::function<void()> m_pFunction;
	bool m_isActive;

	//===========================================================================================
	//Description: Sets up background, border, text and accept/decline buttons
	//===========================================================================================
	void setUp();

public:

	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	ConfirmationWindow(sf::RenderWindow& window, Textures* pTextures, Fonts* pFonts);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~ConfirmationWindow();

	//===========================================================================================
	//Description: Repositions contents of this class
	//===========================================================================================
	void reposition();

	//===========================================================================================
	//Description: Checks for button press
	//===========================================================================================
	bool update(const sf::Vector2f& mousePosition);

	//===========================================================================================
	//Description: Sets pointer to a function to call if accept button is pressed
	//===========================================================================================
	void setConfirmationFunctionPointer(std::function<void()> function);

	//===========================================================================================
	//Description: Returns active state bool
	//===========================================================================================
	const bool getActiveState() const;

	//===========================================================================================
	//Description: Toggles is active state bool
	//===========================================================================================
	void toggleIsActive();

	//===========================================================================================
	//Description: Changes global UI layer to confirmation
	//===========================================================================================
	void changeUILayerToConfirmation();

	//===========================================================================================
	//Description: Changes global UI layer to town
	//===========================================================================================
	void changeUILayerToTown();

	//===========================================================================================
	//Description: Changes global UI layer to map
	//===========================================================================================
	void changeUILayerToMap();

	//===========================================================================================
	//Description: Changes global UI layer to map object interaction
	//===========================================================================================
	void changeUILayerToMapObjectInteraction();

	//===========================================================================================
	//Description: Draws contents of this class
	//===========================================================================================
	void draw();
};
#endif // !CONFIRMATIONWINDOW_H