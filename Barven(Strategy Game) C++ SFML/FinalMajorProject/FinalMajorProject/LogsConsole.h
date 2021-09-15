//Author: Maciej Dowbor
//Last Accessed: 18/08/2021

#ifndef LOGSCONSOLE_H
#define LOGSCONSOLE_H

#include "TextBox.h"

//===========================================================================================
//Description: Log console, keeps and displays logs on the screen in a text box
//===========================================================================================
class LogsConsole : public TextBox
{
private:
	std::vector<std::string> m_textToDisplay;

public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	LogsConsole(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~LogsConsole();

	//===========================================================================================
	//Description: Set up log console variables
	//===========================================================================================
	void setUpLogConsole(const int& posX, const int& posY, const int& consoleWidth, const int& consoleHeight, const int& textSize, const int& titleSize, const std::string& title);

	//===========================================================================================
	//Description: Add text
	//===========================================================================================
	void addText(const std::string& text);

	//===========================================================================================
	//Description: Updates displayed text and makes sure it fits inside the text box
	//===========================================================================================
	void updateTextToDisplay();

	//===========================================================================================
	//Description: Clears the text box 
	//===========================================================================================
	void clearText();
};

#endif // !LOGSCONSOLE_H

