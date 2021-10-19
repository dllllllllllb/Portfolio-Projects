#include "UnitCard.h"

UnitCard::UnitCard(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts, Audio& rAudio) :
	IconButton(rWindow, rTextures, rAudio, true),
	IconButton::UIElement(rWindow, rTextures, true),
	Text(rWindow, rTextures, rFonts),
	m_window(rWindow),
	m_hasUnit(false)
{
	setUpAndResizeToSprite(0, 0, rTextures.m_emptyUnitIcon);
}

UnitCard::~UnitCard()
{
}

void UnitCard::toggleHasUnit()
{
	m_hasUnit = !m_hasUnit;
}

const bool UnitCard::getHasUnit() const
{
	return m_hasUnit;
}

const sf::Vector2f& UnitCard::getPosition() const
{
	return m_buttonIcon.getPosition();
}

void UnitCard::draw()
{
	m_window.draw(m_buttonIcon);
	Text::draw();
}