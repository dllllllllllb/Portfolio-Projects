//Author: Maciej Dowbor
//Last Accessed: 17/06/2021

#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

#include "GameStateEnum.h"
#include "GlobalVariables.h"
#include "Menu.h"
#include "DevTools.h"
#include "GameSetUpScreen.h"
#include "Game.h"

//===========================================================================================
//Description: Heavily WIP, framework might change a lot hence it's not commented properly
//===========================================================================================
class Framework
{
private:
	sf::RenderWindow& m_window;
	sf::Clock m_clock;

	float m_deltaTime;

	//Mouse and Keyboard control
	sf::Mouse m_mouse;
	sf::Vector2f m_mousePosition;
	bool m_canObjectBePressed;
	bool m_canRMBBePressed;

	//Data
	DataHandler* m_pDataHandler;
	Textures* m_pTextures;
	Fonts* m_pFonts;

	void checkWindowEvents();

	//Game Sections
	Menu* m_pMenu;
	void menu();

	GameSetUpScreen* m_pGameSetUpScreen;
	void gameSetUpScreen();

	DevTools* m_pDevTools;
	void devTools();

	Game* m_pGame;
	void game();

	void mouseControl();

public:
	Framework(sf::RenderWindow& window);
	~Framework();

	void run();
};

#endif // !FRAMEWORK_H
