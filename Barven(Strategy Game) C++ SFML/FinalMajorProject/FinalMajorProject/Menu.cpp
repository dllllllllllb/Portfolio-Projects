#include "Menu.h"
Menu::Menu(sf::RenderWindow& window, Textures* textures, Fonts* fonts) :
	m_window(window),
	m_playButton(window, textures, fonts),
	m_optionsButton(window, textures, fonts),
	m_devToolsButton(window, textures, fonts)
{
	setUpButtons();
}

Menu::~Menu()
{
}

void Menu::setUpButtons()
{
	//Play Button
	m_playButton.setPosition(m_window.getSize().x * 0.5f, 500);
	m_playButton.setUpUIBorder(300, 100);
	m_playButton.setCollisionBounds(300, 100);
	m_playButton.setUpText("Play", 72, TextAlignmentEnum::middleHorizontal, TextAlignmentEnum::middleVertical);

	//Options Buton
	m_optionsButton.setPosition(m_window.getSize().x * 0.5f, 650);
	m_optionsButton.setUpUIBorder(300, 100);
	m_optionsButton.setCollisionBounds(300, 100);
	m_optionsButton.setUpText("Options", 72, TextAlignmentEnum::middleHorizontal, TextAlignmentEnum::middleVertical);

	//DevTools Button
	m_devToolsButton.setPosition(m_window.getSize().x * 0.5f, 800);
	m_devToolsButton.setUpUIBorder(300, 100);
	m_devToolsButton.setCollisionBounds(300, 100);
	m_devToolsButton.setUpText("Dev Tools", 56, TextAlignmentEnum::middleHorizontal, TextAlignmentEnum::middleVertical);
}

void Menu::update(const sf::Vector2f& mousePosition)
{
	if (m_playButton.checkMouseCollision(mousePosition) && Global::g_isLMBPressed)
	{
		Global::objectPressed();
		Global::g_gameState = GameState::gameSetUpScreen;
	}

	if (m_optionsButton.checkMouseCollision(mousePosition) && Global::g_isLMBPressed)
	{
		Global::objectPressed();
		//Do stuff
	}

	if (m_devToolsButton.checkMouseCollision(mousePosition) && Global::g_isLMBPressed)
	{
		Global::g_gameState = GameState::devTools;
		Global::objectPressed();
	}
}

void Menu::draw()
{
	m_playButton.draw();

	m_optionsButton.draw();

	m_devToolsButton.draw();
}