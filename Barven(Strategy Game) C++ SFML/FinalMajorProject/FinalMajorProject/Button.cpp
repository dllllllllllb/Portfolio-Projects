#include "Button.h"

Button::Button(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts, Audio& rAudio) :
	UIElement(rWindow, rTextures),
	Text(rWindow, rTextures, rFonts),
	TextBoxTitle(rWindow, rTextures, rFonts),
	m_audio(rAudio),
	m_SFXToPlay(SFXEnum::button)
{
	m_setUpFillShader = true;
}

Button::Button(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts, Audio& rAudio, const bool setThinBorder) :
	UIElement(rWindow, rTextures, setThinBorder),
	Text(rWindow, rTextures, rFonts),
	TextBoxTitle(rWindow, rTextures, rFonts),
	m_audio(rAudio),
	m_SFXToPlay(SFXEnum::button)
{
	m_setUpFillShader = true;
}

Button::~Button()
{
	
}

bool Button::checkIfButtonWasPressed(const sf::Vector2f& mousePosition)
{
	//Change fill colour of the button if hovered
	if (collisionCheck(mousePosition))
	{
		m_isShaderActive = true;

		if (Global::g_isLMBPressed)
		{
			m_audio.playSFX(m_SFXToPlay);
			Global::objectPressed();
			return true;
		}
	}
	else
	{
		m_isShaderActive = false;
	}

	return false;
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

