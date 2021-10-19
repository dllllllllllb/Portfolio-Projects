//Author: Maciej Dowbor
//Last Accessed: 24/08/2021

#ifndef ICONBUTTONLIST_H
#define ICONBUTTONLIST_H

#include "GlobalVariables.h"
#include "IconButton.h"
#include <iostream>

//===========================================================================================
//Description: Vertical list of icon buttons that can be scrolled up or down using arrow buttons
//===========================================================================================
class IconButtonList
{
private:
	sf::RenderWindow& m_window;
	Textures& m_textures;
	Audio& m_audio;

	IconButton m_upNavigationButton;
	IconButton m_downNavigationButton;
	std::vector<std::unique_ptr<IconButton>> m_iconButtons;
	const int m_borderSize;
	int m_numberOfButtons;
	int m_numberOfButtonsToDisplay;
	int m_firstButtonToDisplay;
	int m_numberOfButtonsInUse;
	int m_indexOfButtonClicked;
	int m_buttonHeight;
	int m_firstButtonPosX;
	int m_firstButtonPosY;

public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	IconButtonList(sf::RenderWindow& rWindow, Textures& rTextures, Audio& rAudio);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~IconButtonList();

	//===========================================================================================
	//Description: Sets icon button list parameters
	//===========================================================================================
	void setUpIconButtonList(const int& posX, const int& topPosY, const int& buttonWidth, const int& buttonHeight, const int& numOfButtonToDisplay);

	//===========================================================================================
	//Description: Updates icon button for existing buttons
	//===========================================================================================
	void updateButtonIcon(const int& buttonIndex, const sf::Texture& icon);

	//===========================================================================================
	//Description: Resets button icons to default
	//===========================================================================================
	void resetButtonIcons();

	//===========================================================================================
	//Description: Adds a new button icon
	//===========================================================================================
	void addNewButtonIcon(const sf::Texture& buttonIcon);

	//===========================================================================================
	//Description: Updates mouse interactions with buttons
	//===========================================================================================
	const bool update(const sf::Vector2f& mousePosition);

	//===========================================================================================
	//Description: Returns index of button clicked
	//===========================================================================================
	const int& getIndexOfButtonClicked() const;

	//===========================================================================================
	//Description: Returns numbers of buttons in use
	//===========================================================================================
	const int& getNumberOfButtonsInUse() const;

	//===========================================================================================
	//Description: Updates button positiions
	//===========================================================================================
	void updateButtonsPositions();

	//===========================================================================================
	//Description: Draws contents of this class
	//===========================================================================================
	void draw();
};

#endif // !ICONBUTTONLIST_H


