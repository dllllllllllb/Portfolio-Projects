//Author: Maciej Dowbor
//Last Accessed: 10/09/2021

#ifndef MAPUI_H
#define MAPUI_H

#include <functional>

#include "IconButton.h"
#include "TextBox.h"
#include "Button.h"
#include "IconButtonList.h"
#include "MapUISettings.h"
#include "MapUIButtonsEnum.h"

//===========================================================================================
//Description: Table for setting players/AI names, factions and bonuses 
//===========================================================================================
class MapUI
{
private:
	sf::RenderWindow& m_window;
	Textures& m_textures;
	Audio& m_audio;
	UIElement m_background;
	TextBox m_turnInformation;
	TextBox m_resourcesPerTurn;
	IconButtonList m_townsIconButtons;
	IconButtonList m_heroesIconButtons;
	std::vector<std::unique_ptr<IconButton>> m_iconButtons;

	bool m_isActive;

	std::function<void()> m_updateResourcesPerTurnFunction;
	std::function<void(const int&)> m_townSelectedFunction;
	std::function<void(const int&)> m_heroSelectedFunction;
	std::function<void()> m_nextTurnFunction;
	std::function<void()> m_saveGameFunction;
	std::function<void()> m_optionsFunction;
	std::function<void()> m_exitFunction;

public:

	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	MapUI(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts, Audio& rAudio);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~MapUI();

	//===========================================================================================
	//Description: Sets up map UI elements
	//===========================================================================================
	void setUpMapUI();

	//===========================================================================================
	//Description: Updates mouse interactions
	//===========================================================================================
	void update(const sf::Vector2f& mousePosition);

	//===========================================================================================
	//Description: Checks if player pressed TAB
	//===========================================================================================
	void checkForTabPress();

	//===========================================================================================
	//Description: Toggles between true and false state if map UI is active
	//===========================================================================================
	void toggleIsActive();

	//===========================================================================================
	//Description: Sets active state of this class
	//===========================================================================================
	void setIsActive(const bool state);

	//===========================================================================================
	//Description: Draws elements of this class
	//===========================================================================================
	void draw();

	//===========================================================================================
	//Description: Returns a reference to town button list
	//===========================================================================================
	IconButtonList& getTownButoonList();

	//===========================================================================================
	//Description: Returns a reference to hero button list
	//===========================================================================================
	IconButtonList& getHeroButoonList();

	//===========================================================================================
	//Description: Returns a reference to turn information text box
	//===========================================================================================
	TextBox& getTurnInformationTextBox();

	//===========================================================================================
	//Description: Returns a reference to resources per turn text box
	//===========================================================================================
	TextBox& getResourcesPerTurnTextBox();

	//===========================================================================================
	//Description: Sets function pointers (used in MapHandler.cpp)
	//===========================================================================================
	void setMapHandlerFunctionPointers(std::function<void(const int&)> townSelectedFunction, std::function<void(const int&)> heroSelectedFunction, std::function<void()> updateResourcesPerTurnFunction, std::function<void()> nextTurnFunction);

};

#endif // !MAPUI_H

