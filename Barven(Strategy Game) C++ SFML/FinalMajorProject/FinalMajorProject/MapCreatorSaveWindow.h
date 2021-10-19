//Author: Maciej Dowbor
//Last Accessed: 17/05/2021

#ifndef MAPCREATORSAVEWINDOW_H
#define MAPCREATORSAVEWINDOW_H

#include <functional>

#include "TextInputBox.h"
#include "BasicButton.h"
#include "MapCreatorSaveWindowSettings.h"

//===========================================================================================
//Description: Acts as a confirmation for map saveing and allows the player to set map name
//===========================================================================================
class MapCreatorSaveWindow
{
private:
	sf::RenderWindow&	m_window;
	UIElement			m_background;
	TextInputBox		m_mapNameInputBox;
	TextInputBox		m_numOfPlayersInputBox;
	BasicButton			m_acceptButton;
	BasicButton			m_declineButton;

	std::function<void()> m_saveMapFunction;
	std::function<void()> m_exitSaveWindowFunction;

public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	MapCreatorSaveWindow(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts, Audio& rAudio);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~MapCreatorSaveWindow();

	//===========================================================================================
	//Description: Initializes the background, input bos and basic buttons
	//===========================================================================================
	void initialize();

	//===========================================================================================
	//Description: Sets map save function
	//===========================================================================================
	void setSaveMapFunction(std::function<void()> function);

	//===========================================================================================
	//Description: Sets exit save window function
	//===========================================================================================
	void setExitSaveWindowFunction(std::function<void()> function);

	//===========================================================================================
	//Description: Sets input boxes to inactive, disabling player input
	//===========================================================================================
	void resetInputButtonFocus();

	//===========================================================================================
	//Description: Checks for button presses and updates input box
	//===========================================================================================
	void update(const sf::Vector2f& mousePosition);

	//===========================================================================================
	//Description: Returns map name typed by the player in the input box
	//===========================================================================================
	const std::string& getMapName() const;

	//===========================================================================================
	//Description: Returns number of players typed by the player in the input box
	//===========================================================================================
	const int getNumberOfPlayers() const;

	//===========================================================================================
	//Description: Draws contents of this class
	//===========================================================================================
	void draw();


};

#endif // !MAPCREATORSAVEWINDOW_H

