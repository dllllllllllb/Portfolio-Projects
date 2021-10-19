#include "HeroPanel.h"

namespace settings = HeroPanelSettings;

HeroPanel::HeroPanel(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts, Audio& rAudio) :
	m_window(rWindow),
	m_textures(rTextures),
	m_fonts(rFonts),
	m_background(rWindow, rTextures),
	m_heroLevel(rWindow, rTextures, rFonts, true),
	m_heroStatsDisplay(rWindow, rTextures, rFonts),
	m_unitsPanel(rWindow, rTextures, rFonts, rAudio),
	m_closeButton(rTextures, rAudio, false),
	m_addStatsButton(rWindow, rTextures, rAudio, true),
	m_upgradeHeroStatsPanel(rWindow, rTextures, rFonts,rAudio),
	m_isActive(false),
	m_canHeroInteractWithUnits(false),
	m_canHeroUpgradeStats(false),
	m_pSelectedHero(nullptr)
{

}

HeroPanel::~HeroPanel()
{

}

void HeroPanel::setUpHeroPanel()
{
	int posX = m_window.getSize().x - settings::c_panelWidth * 0.5f - settings::c_borderWidth;
	int posY = m_window.getView().getCenter().y;

	//Background
	m_background.setPosition(posX, posY);
	m_background.setUpUIBorder(settings::c_panelWidth, settings::c_panelHeight);

	//Hero level text box
	m_heroLevel.setPosition(posX, posY - settings::c_panelHeight * 0.5f + settings::c_heroLevelTextBoxHeight * 0.5f + settings::c_borderWidth);
	m_heroLevel.setUpUIBorder(settings::c_panelWidth - settings::c_borderWidth * 2, settings::c_heroLevelTextBoxHeight);
	m_heroLevel.setUpText("Level: 1", settings::c_textCharSize, TextAlignmentEnum::middleHorizontal, TextAlignmentEnum::middleVertical);

	//Hero stats display
	m_heroStatsDisplay.setUpHeroStatsDisplay(posX, m_heroLevel.UIElement::getPosition().y + settings::c_heroLevelTextBoxHeight, settings::c_panelWidth, settings::c_iconScale, settings::c_textCharSize);

	//Units Panel
	m_unitsPanel.setUpPanel(posX, settings::c_unitPanelPositionY, false);

	//Close button
	int closeButtonHeight = m_closeButton.getGlobalBounds().height;
	m_closeButton.sf::Sprite::setPosition(posX, posY + settings::c_panelHeight * 0.5f - closeButtonHeight);
	m_closeButton.CollidableObject::setPosition(posX, posY + settings::c_panelHeight * 0.5f - closeButtonHeight);

	//Add stats button
	m_addStatsButton.setUpAndResizeToSprite(posX + settings::c_panelWidth * 0.5f - m_textures.m_plusButton.getSize().x, m_heroLevel.UIElement::getPosition().y, m_textures.m_plusButton);
	m_upgradeHeroStatsPanel.setUpUpgradeHeroStatsPanel();
}

void HeroPanel::setHeroData(Hero* hero, const bool canHeroInteractWithUnits)
{
	m_pSelectedHero = hero;
	m_canHeroInteractWithUnits = canHeroInteractWithUnits;

	//Set hero level
	m_heroLevel.setTextAndUpdate("Level: " + std::to_string(hero->getHeroLevel()));

	setHeroStats();

	//Set units
	m_unitsPanel.setUnitCards(hero->getVectorOfUnits());

	//Check if hero can upgrade their stats
	m_canHeroUpgradeStats = hero->getStatUpgradePoints() > 0;
}

void HeroPanel::setHeroStats()
{
	//Set Hero stats
	for (int i = 0; i < HeroStatsDisplaySettings::c_numOfSkills; i++)
	{
		m_heroStatsDisplay.updateHeroStat(i, m_pSelectedHero->getHeroStat(static_cast<HeroStatsEnum>(i)));
	}
}

void HeroPanel::update(const sf::Vector2f& mousePosition)
{
	if (m_isActive)
	{
		if (m_canHeroInteractWithUnits)
		{
			m_unitsPanel.update(mousePosition);
		}

		if (Global::g_isLMBPressed)
		{
			if (m_canHeroUpgradeStats)
			{
				if (m_addStatsButton.checkIfButtonWasPressed(mousePosition))
				{
					m_upgradeHeroStatsPanel.setHeroAndUpdatePanel(*m_pSelectedHero);
					m_upgradeHeroStatsPanel.toggleIsActive();
				}
			}

			if (m_closeButton.checkIfButtonWasPressed(mousePosition))
			{
				toggleIsActive();
			}
		}
		if (m_upgradeHeroStatsPanel.update(mousePosition))
		{
			setHeroStats();
			m_canHeroUpgradeStats = m_pSelectedHero->getStatUpgradePoints() > 0;
		}
	}
}

void HeroPanel::toggleIsActive()
{
	m_isActive = !m_isActive;
}

void HeroPanel::setIsActive(const bool state)
{
	m_isActive = state;
}

void HeroPanel::draw()
{
	if (m_isActive)
	{
		m_background.drawUIBackground();
		m_heroLevel.draw();
		m_heroStatsDisplay.draw();
		m_background.drawUIBorder();
		m_unitsPanel.draw();

		if (m_canHeroUpgradeStats)
		{
			m_addStatsButton.draw();
		}

		m_window.draw(m_closeButton);

		m_upgradeHeroStatsPanel.draw();
	}
}

UnitsPanel& HeroPanel::getUnitsPanel()
{
	return m_unitsPanel;
}

TextBox& HeroPanel::getHeroLevelTextBox()
{
	return m_heroLevel;
}

HeroStatsDisplay& HeroPanel::getHeroStatsDisplay()
{
	return m_heroStatsDisplay;
}
