#include "BasicButton.h"

BasicButton::BasicButton(Textures& rTextures, Audio& rAudio, const bool state):
	m_audio(rAudio),
	m_SFXToPlay(SFXEnum::button)
{
	if (state)
	{
		setTexture(rTextures.m_acceptButton);
	}
	else
	{
		setTexture(rTextures.m_declineButton);
	}
	sf::Sprite::setOrigin(getGlobalBounds().width * 0.5f, getGlobalBounds().height * 0.5f);
	setCollisionBounds(getGlobalBounds().width, getGlobalBounds().height);
}

const bool BasicButton::checkIfButtonWasPressed(const sf::Vector2f& mousePosition)
{
	if (Global::g_isLMBPressed && CollidableObject::collisionCheck(mousePosition))
	{
		m_audio.playSFX(m_SFXToPlay);
		Global::objectPressed();
		return true;
	}

	return false;
}

BasicButton::~BasicButton()
{
}
