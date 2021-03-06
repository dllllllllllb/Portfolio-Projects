//Author: Maciej Dowbor
//Last Accessed: 30/09/2021

#ifndef DEVTOOLS_H
#define DEVTOOLS_H

#include <SFML/Window/Mouse.hpp>

#include "DevToolsSettings.h"
#include "DevToolsEnum.h"
#include "MapCreator.h"
#include "PathFindingTool.h"
#include "UITool.h"
#include "UnitCreationTool.h"
#include "Town.h"
#include "CombatUnitEditor.h"
#include "CombatHandler.h"

//===========================================================================================
//Description: Interface for dev tools, used to navigate between various tools.
//===========================================================================================
class DevTools
{
private:
	sf::RenderWindow& m_window;
	Textures& m_textures;
	Fonts& m_fonts;
	Audio& m_audio;
	DevToolsEnum m_devToolsEnum;
	DataHandler& m_dataHandler;

	ConfirmationWindow m_confirmationWindow;

	std::vector<std::unique_ptr<Button>> m_buttons;

	UITool m_UITool;

	PathFindingTool m_pathFindingTool;

	UnitCreationTool m_unitCreationTool;

	MapCreator m_mapCreator;

	CombatUnitEditor m_combatUnitEditor;
	CombatHandler m_commbatHandler;
	Hero m_defenderHero;

	TextBox m_testTextBox;

	//TownTool data
	Player m_player;
	TownData m_townData;
	ResourcesBar m_resourcesBar;

	Town m_townTool;

	bool m_deleteSelf;

	std::function<void()> m_deleteDevTools;

public:

	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	DevTools(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts, Audio& rAudio, DataHandler& rDataHandler, sf::Mouse& mouse);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~DevTools();

	//===========================================================================================
	//Description: Initializes buttons and calls initializers of other tools
	//===========================================================================================
	void initialize();

	//===========================================================================================
	//Description: Sets up buttons
	//===========================================================================================
	void setUpButtons();

	//===========================================================================================
	//Description: Updates appropriate functions based on what tool is being used
	//===========================================================================================
	void update(const sf::Vector2f& mousePosition, const float& deltaTime);

	//===========================================================================================
	//Description: Updates dev tool
	//===========================================================================================
	void updateDevTools(const sf::Vector2f& mousePosition);

	//===========================================================================================
	//Description: Sets function outside of this class that deletes this object
	//===========================================================================================
	void setFunctionToDeleteDevTools(std::function<void()> deleteDevTools);

	//===========================================================================================
	//Description: Draws dev tool
	//===========================================================================================
	void drawDevTools();
};

#endif // !DEVTOOLS_H
