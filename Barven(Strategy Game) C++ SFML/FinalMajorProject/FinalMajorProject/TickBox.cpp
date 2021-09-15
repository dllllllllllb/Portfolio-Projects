#include "TickBox.h"
TickBox::TickBox(Textures* pTextures) :
	m_pTextures(pTextures),
	m_state(false)
{
	setTexture(pTextures->m_tickBoxFalse);
	sf::Sprite::setOrigin(getGlobalBounds().width * 0.5f, getGlobalBounds().height * 0.5f);
	CollidableObject::setOrigin(getGlobalBounds().width * 0.5f, getGlobalBounds().height * 0.5f);
	setCollisionBounds(pTextures->m_tickBoxFalse.getSize().x, pTextures->m_tickBoxFalse.getSize().y);
}

TickBox::~TickBox()
{
}

void TickBox::setPosition(const int& positionX, const int& positionY)
{
	sf::Sprite::setPosition(positionX, positionY);
	CollidableObject::setPosition(positionX, positionY);
}

void TickBox::setState(const bool state)
{
	m_state = state;
	swapTexture();
}

void TickBox::toggleState()
{
	m_state = !m_state;
	swapTexture();
}

const bool TickBox::getState() const
{
	return m_state;
}

void TickBox::swapTexture()
{
	if (m_state)
	{
		setTexture(m_pTextures->m_tickBoxTrue);
	}
	else
	{
		setTexture(m_pTextures->m_tickBoxFalse);
	}
}
