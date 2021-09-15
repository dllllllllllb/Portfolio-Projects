#include "CombatEndPopUp.h"

namespace settings = CombatEndPopUpSettings;

CombatEndPopUp::CombatEndPopUp(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts) :
	m_window(rWindow),
	m_combatEndInformation(rWindow, &rTextures, &rFonts, true),
	m_acceptButton(&rTextures, true)
{
}

CombatEndPopUp::~CombatEndPopUp()
{
}

void CombatEndPopUp::setUp()
{
	m_combatEndInformation.setPosition(m_window.getView().getCenter());
	m_combatEndInformation.setUpUIBorder(settings::c_textBoxWidth, settings::c_textBoxHeight);
	m_combatEndInformation.setUpTitleText(settings::c_textBoxTitle[0], settings::c_titleTextCharSize);
	m_combatEndInformation.setTitleOffset(m_combatEndInformation.getTitleHeight());

	m_acceptButton.sf::Sprite::setPosition(m_window.getView().getCenter().x, m_window.getView().getCenter().y + m_acceptButton.getTexture()->getSize().y * 0.5f);
	m_acceptButton.CollidableObject::setPosition(m_window.getView().getCenter().x, m_window.getView().getCenter().y + m_acceptButton.getTexture()->getSize().y * 0.5f);
}

void CombatEndPopUp::setTitleText(const bool didAttackerWon)
{
	m_combatEndInformation.setUpTitleText(settings::c_textBoxTitle[static_cast<int>(didAttackerWon)], settings::c_titleTextCharSize);
	m_combatEndInformation.setTitleOffset(m_combatEndInformation.getTitleHeight());
}

const bool CombatEndPopUp::update(const sf::Vector2f& mousePosition)
{
	return m_acceptButton.collisionCheck(mousePosition);
}

void CombatEndPopUp::draw()
{
	m_combatEndInformation.draw();
	m_window.draw(m_acceptButton);
}
