#include "BasicButton.h"

BasicButton::BasicButton(Textures* pTextures, const bool state)
{
	if (state)
	{
		setTexture(pTextures->m_acceptButton);
	}
	else
	{
		setTexture(pTextures->m_declineButton);
	}
	sf::Sprite::setOrigin(getGlobalBounds().width * 0.5f, getGlobalBounds().height * 0.5f);
	setCollisionBounds(getGlobalBounds().width, getGlobalBounds().height);
}

BasicButton::~BasicButton()
{
}
