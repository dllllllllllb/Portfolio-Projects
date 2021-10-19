#include "UpgradeHeroStatsPanel.h"

namespace settings = UpgradeHeroStatsPanelSettings;

UpgradeHeroStatsPanel::UpgradeHeroStatsPanel(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts, Audio& rAudio) :
	m_window(rWindow),
	m_textures(rTextures),
	m_basePanel(rWindow, rTextures, rFonts),
	m_exitButton(rWindow, rTextures, rAudio, true),
	m_isActive(false),
	m_pHeroPointer(nullptr)
{
	//Create hero stats button and text
	for (int i = 0; i < settings::c_numOfSkills; i++)
	{
		m_heroStatsUpgradeButtons.push_back(std::unique_ptr<IconButton>(new IconButton(rWindow, rTextures, rAudio, true)));
	}
	setUpUpgradeHeroStatsPanel();
}

UpgradeHeroStatsPanel::~UpgradeHeroStatsPanel()
{
}

void UpgradeHeroStatsPanel::setUpUpgradeHeroStatsPanel()
{
	//Background
	m_basePanel.setPosition(m_window.getView().getCenter());
	m_basePanel.setUpUIBorder(settings::c_basePanelWidth, settings::c_basePanelHeight);
	m_basePanel.setUpTitleText(settings::c_panelTitle, settings::c_titleCharSize);
	m_basePanel.setTitleOffset(m_basePanel.getTitleHeight());
	m_basePanel.setUpText(settings::c_panelText, settings::c_textCharSize, TextAlignmentEnum::middleHorizontal, TextAlignmentEnum::top);

	//Stats Icons / Stats Value Text
	int firstStatIconPositionX = m_basePanel.::UIElement::getPosition().x - ((settings::c_numOfSkills * (settings::c_skillIconWidth + settings::c_skillIconSpaceing) + settings::c_skillIconSpaceing) * 0.5f) + settings::c_skillIconSpaceing + settings::c_skillIconWidth * 0.5f;
	int statIconPositionY = m_basePanel.::UIElement::getPosition().y + settings::c_skillIconHeight * 0.3f;

	for (int i = 0; i < settings::c_numOfSkills; i++)
	{
		//Stat Icon Button
		m_heroStatsUpgradeButtons[i]->setUpAndResizeToSprite(firstStatIconPositionX + i * (settings::c_skillIconWidth + settings::c_skillIconSpaceing), statIconPositionY, m_textures.m_heroPrimarySkills[i]);
	}

	//Exit Button
	m_exitButton.setUpAndResizeToSprite(m_basePanel.UIElement::getPosition().x + settings::c_basePanelWidth * 0.5f - m_textures.m_declineButton.getSize().x * 0.8f, 
										m_basePanel.UIElement::getPosition().y + settings::c_basePanelHeight * 0.5f - m_textures.m_declineButton.getSize().y, m_textures.m_declineButton);
}

void UpgradeHeroStatsPanel::setHeroAndUpdatePanel(Hero& hero)
{
	m_pHeroPointer = &hero;

	updatePanelText();
}

void UpgradeHeroStatsPanel::toggleIsActive()
{
	m_isActive = !m_isActive;
}

void UpgradeHeroStatsPanel::updatePanelText()
{
	m_basePanel.setTextAndUpdate(settings::c_panelText + std::to_string(m_pHeroPointer->getStatUpgradePoints()));
}

const bool UpgradeHeroStatsPanel::update(const sf::Vector2f& mousePosition)
{
	bool wasStatUpgraded = false;

	if (m_isActive)
	{
		if (Global::g_isLMBPressed)
		{
			if (m_pHeroPointer->getStatUpgradePoints() > 0)
			{
				for (int i = 0; i < settings::c_numOfSkills; i++)
				{
					if (m_heroStatsUpgradeButtons[i]->checkIfButtonWasPressed(mousePosition))
					{
						m_pHeroPointer->incrementHeroStat(static_cast<HeroStatsEnum>(i), 1);
						m_pHeroPointer->decrementStatUpgradePoints();
						updatePanelText();
						wasStatUpgraded = true;
						break;
					}
				}
			}

			if (m_exitButton.checkIfButtonWasPressed(mousePosition))
			{
				toggleIsActive();
			}
		}
	}

	return wasStatUpgraded;
}

void UpgradeHeroStatsPanel::draw()
{
	if (m_isActive)
	{
		m_basePanel.draw();
		for (int i = 0; i < settings::c_numOfSkills; i++)
		{
			m_heroStatsUpgradeButtons[i]->draw();
		}
		m_exitButton.draw();
	}
}
