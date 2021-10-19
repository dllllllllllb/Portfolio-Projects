#include "TextBox.h"
TextBox::TextBox(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts) :
	TextBoxTitle(rWindow, rTextures, rFonts),
	Text(rWindow, rTextures, rFonts),
	UIElement(rWindow, rTextures)
{
}

TextBox::TextBox(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts, const bool setThinUIBorder) :
	TextBoxTitle(rWindow, rTextures, rFonts),
	Text(rWindow, rTextures, rFonts),
	UIElement(rWindow, rTextures, setThinUIBorder)
{
}

TextBox::~TextBox()
{
}

void TextBox::setPosition(const float& x, const float& y)
{
	UIElement::setPosition(x, y);
	sf::Text::setPosition(x, y);
}

void TextBox::setPosition(const sf::Vector2f& position)
{
	UIElement::setPosition(position);
	sf::Text::setPosition(position);
}

void TextBox::resizeBorderToFitText()
{
	float textHeight = sf::Text::getGlobalBounds().height;

	float tempY = UIElement::getPosition().y - (UIElement::getGlobalBounds().height * 0.5f); //Y position of the top of the box

	setUpUIBorder(UIElement::getGlobalBounds().width, textHeight + (c_UIBorder * 4) + m_titleOffset ); //Resizes UI border

	tempY += UIElement::getGlobalBounds().height * 0.5f; //Adds half of the newly resized UI border

	moveUIElement(UIElement::getPosition().x, tempY);
	updateAlignment();
}

void TextBox::draw()
{
	drawUIBorderAndBackground();
	TextBoxTitle::draw();
	m_window.draw((sf::Text)*this);
}
