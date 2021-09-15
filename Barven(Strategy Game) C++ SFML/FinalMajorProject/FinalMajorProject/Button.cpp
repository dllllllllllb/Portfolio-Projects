#include "Button.h"

Button::Button(sf::RenderWindow& window, Textures* textures, Fonts* fonts) :
	UIElement(window, textures),
	Text(window, textures, fonts),
	TextBoxTitle(window, textures, fonts)
{
	m_setUpFillShader = true;
}

Button::Button(sf::RenderWindow& window, Textures* textures, Fonts* fonts, const bool setThinBorder) : 
	UIElement(window, textures, setThinBorder),
	Text(window, textures, fonts),
	TextBoxTitle(window, textures, fonts)
{
	m_setUpFillShader = true;
}

Button::~Button()
{
	
}

bool Button::checkMouseCollision(const sf::Vector2f& mousePosition)
{
	//Change fill colour of the button if hovered
	if (collisionCheck(mousePosition))
	{
		m_isShaderActive = true;
	}
	else
	{
		m_isShaderActive = false;
	}

	return m_isShaderActive;
}

void Button::setPosition(const float& x, const float& y)
{
	UIElement::setPosition(x, y);
	CollidableObject::setPosition(x, y);
	sf::Text::setPosition(x, y);
}

void Button::reposition(const float& positionX, const float& positionY)
{
	UIElement::moveUIElement(positionX, positionY);
	CollidableObject::setPosition(positionX, positionY);
	sf::Text::setPosition(positionX, positionY);
}

void Button::draw()
{
	drawUIBackground();
	if (m_isShaderActive)
	{
		drawFillShader();
	}
	drawUIBorder();

	drawButtonText();
}

void Button::drawButtonText()
{
	m_window.draw((sf::Text)*this);
}

const Button* Button::getSelf() const
{
	return this;
}

const sf::Vector2f& Button::getPosition() const
{
	return UIElement::getPosition();
}

