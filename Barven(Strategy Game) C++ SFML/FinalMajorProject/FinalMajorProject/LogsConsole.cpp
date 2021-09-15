#include "LogsConsole.h"

LogsConsole::LogsConsole(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts):
	TextBox(rWindow, &rTextures, &rFonts),
	UIElement(rWindow, &rTextures),
	TextBoxTitle(rWindow, &rTextures, &rFonts)
{
}

LogsConsole::~LogsConsole()
{
	
}

void LogsConsole::setUpLogConsole(const int& posX, const int& posY, const int& consoleWidth, const int& consoleHeight, const int& textSize, const int& titleSize, const std::string& title)
{
	setPosition(posX, posY);
	setUpUIBorder(consoleWidth, consoleHeight);
	setUpText("", textSize, TextAlignmentEnum::left, TextAlignmentEnum::bottom);
	setUpTitleText(title, titleSize);
	setDefaultTitlePosition();
	setTitleOffset(getTitleHeight());
}

void LogsConsole::addText(const std::string& text)
{
	m_textToDisplay.push_back(text);
	updateTextToDisplay();
}

void LogsConsole::updateTextToDisplay()
{
	std::string textToDisplay = "";

	for (std::string& text : m_textToDisplay)
	{
		textToDisplay += "\n";
		textToDisplay += text;
	}

	setString(textToDisplay);
	divideTextToLines();
	updateAlignment();

	if (sf::Text::getGlobalBounds().height > UIElement::getGlobalBounds().height - getTitleHeight())
	{
		m_textToDisplay.erase(m_textToDisplay.begin());
		updateTextToDisplay();
	}
}

void LogsConsole::clearText()
{
	m_textToDisplay.clear();
	updateTextToDisplay();
}
