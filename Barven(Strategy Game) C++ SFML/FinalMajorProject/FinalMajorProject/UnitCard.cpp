#include "UnitCard.h"

UnitCard::UnitCard(sf::RenderWindow& rWindow, Textures* pTextures, Fonts* pFonts) :
	IconButton(rWindow, pTextures, true),
	Text(rWindow, pTextures, pFonts),
	IconButton::UIElement(rWindow, pTextures, true),
	m_window(rWindow),
	m_hasUnit(false)
{
	setUpAndResizeToSprite(0, 0, pTextures->m_emptyUnitIcon);
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