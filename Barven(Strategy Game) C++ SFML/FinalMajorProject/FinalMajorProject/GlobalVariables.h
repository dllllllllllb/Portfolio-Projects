//Author: Maciej Dowbor
//Last Accessed: 18/08/2021

#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H

#include <SFML/Window.hpp>
#include "GameStateEnum.h"
#include "UILayerEnum.h"

//Global variables initial values are declared at the top of framework.cpp file
namespace Global
{
	extern sf::Event g_event;
	extern GameState g_gameState;
	extern UILayerEnum g_UILayer;
	extern UILayerEnum g_previousUILayer;
	extern bool g_isWindowFocused;
	extern bool g_wasObjectPressed;
	extern bool g_isLMBPressed;
	extern bool g_isRMBPressed;
	extern bool g_wasRMBPressed;
	extern bool g_updateGame;

	inline void objectPressed() {
		g_isLMBPressed = false;
		g_wasObjectPressed = true;
	}

	inline void RMBPressed() {
		g_isRMBPressed = false;
		g_wasRMBPressed = true;
	}

	inline void toggleUpdateGame() {
		g_updateGame = !g_updateGame;
	}
}
#endif // !GLOBALVARIABLES_H
