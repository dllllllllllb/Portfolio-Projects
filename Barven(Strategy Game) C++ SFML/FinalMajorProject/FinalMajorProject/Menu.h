#ifndef MENU_H
#define MENU_H

#include <SFML/Window/Mouse.hpp>
#include <functional>

#include "Button.h"
#include "Fonts.h"
#include "GlobalVariables.h"

//HEAVILY WORK IN PROGRESS

class Menu
{
private:
	sf::RenderWindow& m_window;
	Button m_playButton;
	Button m_optionsButton;
	Button m_devToolsButton;

	sf::Mouse m_mouse;

	std::function<void()> m_initializeDevTools;

public:
	Menu(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts, Audio& rAudio);
	~Menu();

	void setUpButtons();

	void update(const sf::Vector2f& mousePosition);

	void setInitializeDevTools(std::function<void()> initializeDevTools);

	void draw();
};

#endif // !MENU_H

