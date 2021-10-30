#include "TextInputBox.h"

TextInputBox::TextInputBox(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts, Audio& rAudio) :
	Button(rWindow, rTextures, rFonts, rAudio),
	TextBoxTitle(rWindow, rTextures, rFonts),
	UIElement(rWindow, rTextures),
	m_playerInput(""),
	m_isButtonPressed(false),
	m_canGetInput(true)
{
	
}

TextInputBox::TextInputBox(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts, Audio& rAudio, const bool setThinBorder) :
	Button(rWindow, rTextures, rFonts, rAudio),
	TextBoxTitle(rWindow, rTextures, rFonts),
	UIElement(rWindow, rTextures, setThinBorder),
	m_playerInput(""),
	m_isButtonPressed(false),
	m_canGetInput(true)
{
}

TextInputBox::~TextInputBox()
{

}

void TextInputBox::updateInputTextPosition()
{
	//Takes in account title text and UI Element to work out appropriate input text position 
	float tempY = ((UIElement::getGlobalBounds().height * 0.5f) + UIElement::getPosition().y) + (m_titleText.getPosition().y + (m_titleText.getLocalBounds().height * 0.5f)) - 6;
	
	sf::Text::setPosition(UIElement::getPosition().x, tempY * 0.5f);
}

void TextInputBox::textInput()
{
	if (Global::g_event.type == sf::Event::KeyReleased)
	{
		m_canGetInput = true;
	}

	if (m_canGetInput && Global::g_event.type == sf::Event::TextEntered)
	{
		if (Global::g_event.text.unicode == 8) //Backspace
		{
			//Make sure that there is something to delete
			if (m_playerInput.length() > 0)
			{
				m_playerInput.pop_back();
				updateInputText();
				m_canGetInput = false;
			}
		}
		else 
		{
			if (sf::Text::getGlobalBounds().width < UIElement::getGlobalBounds().width - (sf::Text::getCharacterSize() * 2))
			{
				m_playerInput += Global::g_event.text.unicode;
				updateInputText();
			}
			m_canGetInput = false;
		}
	}
}

void TextInputBox::updateInputText()
{
	sf::Text::setString(m_playerInput);
	Text::updateHorizontalAlignment();
}

void TextInputBox::update()
{
	if (m_isButtonPressed)
	{
		textInput();
	}
}

void TextInputBox::draw()
{
	Button::draw();
	TextBoxTitle::draw();
	
}

void TextInputBox::buttonPressedToggle()
{
	m_isButtonPressed = !m_isButtonPressed;
}

void TextInputBox::setButtonPressed(bool state)
{
	m_isButtonPressed = state;
	userFeedback();
	if (state)
	{
		m_playerInput = "";
		updateInputText();
	}
}

const bool TextInputBox::getIsButtonPressed() const
{
	return m_isButtonPressed;
}

void TextInputBox::userFeedback()
{
	if (m_isButtonPressed)
	{
		UIElement::setColor(sf::Color::Yellow);
	}
	else
	{
		UIElement::setColor(sf::Color::White);
	}
}

const std::string& TextInputBox::getPlayerInput() const
{
	return m_playerInput;
}

void TextInputBox::setPlayerInput(const std::string& string)
{
	m_playerInput = string;
}
