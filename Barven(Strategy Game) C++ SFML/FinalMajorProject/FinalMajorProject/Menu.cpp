#include "Menu.h"
Menu::Menu(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts, Audio& rAudio) :
	m_window(rWindow),
	m_playButton(rWindow, rTextures, rFonts, rAudio),
	m_optionsButton(rWindow, rTextures, rFonts, rAudio),
	m_devToolsButton(rWindow, rTextures, rFonts, rAudio)
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
	if (m_playButton.checkIfButtonWasPressed(mousePosition))
	{
		Global::g_gameState = GameState::gameSetUpScreen;
	}

	if (m_optionsButton.checkIfButtonWasPressed(mousePosition))
	{
		//Do stuff
	}

	if (m_devToolsButton.checkIfButtonWasPressed(mousePosition))
	{
		Global::g_gameState = GameState::devTools;
	}
}

void Menu::draw()
{
	m_playButton.draw();

	m_optionsButton.draw();

	m_devToolsButton.draw();
}