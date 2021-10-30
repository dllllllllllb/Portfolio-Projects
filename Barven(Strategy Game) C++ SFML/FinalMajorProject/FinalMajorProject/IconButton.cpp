#include "IconButton.h"

IconButton::IconButton(sf::RenderWindow& rWindow, Textures& rTextures, Audio& rAudio) :
	UIElement(rWindow, rTextures),
	m_audio(rAudio),
	m_SFXToPlay(SFXEnum::button)
{
}

IconButton::IconButton(sf::RenderWindow& rWindow, Textures& rTextures, Audio& rAudio, const bool setThinBorder) :
	UIElement(rWindow, rTextures, setThinBorder),
	m_audio(rAudio),
	m_SFXToPlay(SFXEnum::button)
{
}

IconButton::~IconButton()
{
}

void IconButton::setPosition(const int& positionX, const int& positionY)
{
	m_buttonIcon.setPosition(static_cast<float>(positionX), static_cast<float>(positionY));
	UIElement::moveUIElement(positionX, positionY);
	CollidableObject::setPosition(positionX, positionY);
}

const bool IconButton::checkIfButtonWasPressed(const sf::Vector2f& otherObjectPosition)
{
	if (Global::g_isLMBPressed && CollidableObject::collisionCheck(otherObjectPosition))
	{
		m_audio.playSFX(m_SFXToPlay);
		Global::objectPressed();
		return true;
	}
	return false;
}

void IconButton::setUp(const float& positionX, const float& positionY, const float& width, const float& height, const sf::Texture* pIconTexture)
{
	UIElement::setPosition(positionX, positionY);
	CollidableObject::setPosition(positionX, positionY);
	setUpUIBorder(width, height);
	setCollisionBounds(width, height);
	m_buttonIcon.setTexture(*pIconTexture, true);

	float iconScale = 1.0f;
	if (height < width) //Determines most effective way to scale the icon to fit inside the button
	{
		iconScale = height / m_buttonIcon.getGlobalBounds().height;
	}
	else
	{
		iconScale = width / m_buttonIcon.getGlobalBounds().width;
	}
	iconScale *= 0.9f;

	m_buttonIcon.setScale(iconScale, iconScale);
	m_buttonIcon.setOrigin(m_buttonIcon.getLocalBounds().width * 0.5f, m_buttonIcon.getLocalBounds().height * 0.5f);
	m_buttonIcon.setPosition(positionX, positionY);
}

void IconButton::setUpAndResizeToSprite(const float& positionX, const float& positionY, const sf::Texture& iconTexture)
{
	int iconWidth = iconTexture.getSize().x;
	int iconHeight = iconTexture.getSize().y;

	UIElement::setPosition(positionX, positionY);
	CollidableObject::setPosition(positionX, positionY);

	setUpUIBorder(iconWidth, iconHeight);
	setCollisionBounds(iconWidth, iconHeight);

	m_buttonIcon.setTexture(iconTexture, true);
	m_buttonIcon.setOrigin(m_buttonIcon.getGlobalBounds().width * 0.5f, m_buttonIcon.getGlobalBounds().height * 0.5f);
	m_buttonIcon.setPosition(positionX, positionY);
}

void IconButton::setButtonIcon(const sf::Texture& iconTexture)
{
	m_buttonIcon.setTexture(iconTexture, true);
}

sf::Sprite& IconButton::getIconSprite()
{
	return m_buttonIcon;
}

void IconButton::draw()
{
	drawUIBackground();
	m_window.draw(m_buttonIcon);
	drawUIBorder();
}

void IconButton::drawWithoutUIBackground()
{
	m_window.draw(m_buttonIcon);
	drawUIBorder();
}
