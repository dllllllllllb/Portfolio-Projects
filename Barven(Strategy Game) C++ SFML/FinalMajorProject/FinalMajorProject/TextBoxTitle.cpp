#include "TextBoxTitle.h"

TextBoxTitle::TextBoxTitle(sf::RenderWindow& window, Textures& rTextures, Fonts& rFonts) :
	UIElement(window, rTextures),
	m_fonts(rFonts)
{
}

TextBoxTitle::~TextBoxTitle()
{
}

void TextBoxTitle::setDefaultTitlePosition()
{
	float x = UIElement::getPosition().x;
	float y = UIElement::getPosition().y;

	float titlePositionY = y - (UIElement::getGlobalBounds().height * 0.5f) + (m_titleText.getLocalBounds().height * 0.5) + 8;

	m_titleText.setPosition(x, titlePositionY);
}

void TextBoxTitle::setTitlePosition(const float& x, const float& y)
{
	float posX = UIElement::getPosition().x;
	float posY = UIElement::getPosition().y;

	float titlePositionY = posY - (UIElement::getGlobalBounds().height * 0.5f) + (m_titleText.getLocalBounds().height * 0.5) + 8;
	titlePositionY += y;

	m_titleText.setPosition(posX += x, titlePositionY);
}

void TextBoxTitle::setUpTitleText(const sf::String& titleText, const int& charSize)
{
	m_titleText.setFont(m_fonts.m_fontBasic);
	m_titleText.setCharacterSize(charSize);
	m_titleText.setStyle(1);

	m_titleText.setString("Pp"); //Have to do this for consistent origin/text height 
	float yOrigin = m_titleText.getLocalBounds().height * 0.8f;

	setDefaultTitlePosition();

	m_titleText.setString(titleText);
	m_titleText.setOrigin(m_titleText.getLocalBounds().width * 0.5f, yOrigin);
}

void TextBoxTitle::draw()
{
	m_window.draw(m_titleText);
}

sf::Text& TextBoxTitle::getTitleText()
{
	return m_titleText;
}

const float& TextBoxTitle::getTitleHeight() const
{
	return m_titleText.getLocalBounds().height;
}
