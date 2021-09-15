//Author: Maciej Dowbor
//Module: MED5149
//Date last accessed: 20/01/2021

#include "Settings.h"
#include "Framework.h"
#include <SFML/Window.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include "vld.h"

int main( )
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 16;
	sf::RenderWindow window( sf::VideoMode( k_windowSizeX, k_windowSizeY ), k_windowName, sf::Style::Default, settings );
	Framework o_framework( window );
	o_framework.run( );
	return 0;
}