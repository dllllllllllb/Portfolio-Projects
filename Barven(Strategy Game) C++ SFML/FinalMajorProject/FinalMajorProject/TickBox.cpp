#include "TickBox.h"
TickBox::TickBox(Textures& rTextures, Audio& rAudio) :
	m_textures(rTextures),
	m_state(false),
	m_audio(rAudio),
	m_SFXToPlay(SFXEnum::button)
{
	setTexture(m_textures.m_tickBoxFalse);
	sf::Sprite::setOrigin(getGlobalBounds().width * 0.5f, getGlobalBounds().height * 0.5f);
	CollidableObject::setOrigin(getGlobalBounds().width * 0.5f, getGlobalBounds().height * 0.5f);
	setCollisionBounds(m_textures.m_tickBoxFalse.getSize().x, m_textures.m_tickBoxFalse.getSize().y);
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

const bool TickBox::checkIfTickBoxWasPressed(const sf::Vector2f& mousePosition)
{
	if (Global::g_isLMBPressed && collisionCheck(mousePosition))
	{
		Global::objectPressed();
		toggleState();
		m_audio.playSFX(m_SFXToPlay);
		return true;
	}
	return false;
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
		setTexture(m_textures.m_tickBoxTrue);
	}
	else
	{
		setTexture(m_textures.m_tickBoxFalse);
	}
}
