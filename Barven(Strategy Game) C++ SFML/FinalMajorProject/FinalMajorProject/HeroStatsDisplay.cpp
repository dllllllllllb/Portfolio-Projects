#include "HeroStatsDisplay.h"

namespace settings = HeroStatsDisplaySettings;

HeroStatsDisplay::HeroStatsDisplay(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts) : 
	m_window(rWindow),
	m_textures(rTextures)
{
	for (int i = 0; i < settings::c_numOfSkills; i++)
	{
		m_heroStatValues.push_back(std::unique_ptr<Text>(new Text(rWindow, &rTextures, &rFonts)));
		m_heroStatValues[i]->setFont(rFonts.m_fontBasic);
		m_heroStatValues[i]->setOutlineThickness(1);
		m_heroStatValues[i]->setOutlineColor(sf::Color::Black);
	}
}

HeroStatsDisplay::~HeroStatsDisplay()
{
}

void HeroStatsDisplay::setUpHeroStatsDisplay(const int& posX, const int& posY, const int& panelWidth, const float& iconScale, const int& charSize)
{
	int iconWidth = m_textures.m_heroPrimarySkills[0].getSize().x * iconScale;
	int iconHeight = m_textures.m_heroPrimarySkills[0].getSize().y * iconScale;
	int iconSpacing = (panelWidth - (settings::c_numOfSkills * iconWidth)) / (settings::c_numOfSkills + 1);
	int firstIconPositionX = posX - panelWidth * 0.5f + iconWidth * 0.5f - iconSpacing * 0.25f;

	for (int i = 0; i < settings::c_numOfSkills; i++)
	{
		m_heroStatIcons[i].setTexture(m_textures.m_heroPrimarySkills[i], true);
		m_heroStatIcons[i].setScale(iconScale, iconScale);
		m_heroStatIcons[i].setOrigin(iconWidth * 0.5f, iconHeight * 0.5f);
		m_heroStatIcons[i].setPosition(firstIconPositionX + (iconWidth + iconSpacing) * i, posY);

		m_heroStatValues[i]->basicSetUp("0", charSize, m_heroStatIcons[i].getPosition().x + iconWidth * 0.25f, m_heroStatIcons[i].getPosition().y + iconHeight * 0.9);
	}
}

void HeroStatsDisplay::updateHeroStat(const int& heroStatIndex, const int& heroStatValue)
{
	m_heroStatValues[heroStatIndex]->setString(std::to_string(heroStatValue));
	m_heroStatValues[heroStatIndex]->sf::Text::setOrigin(m_heroStatValues[heroStatIndex]->sf::Text::getGlobalBounds().width * 0.5f, 1);
}

const int HeroStatsDisplay::getDisplayHeight() const
{
	return (m_heroStatValues[0]->sf::Text::getPosition().y + m_heroStatValues[0]->sf::Text::getGlobalBounds().height * 0.5f) - (m_heroStatIcons[0].getPosition().y - m_heroStatIcons[0].getGlobalBounds().height * 0.5f);
}

void HeroStatsDisplay::draw()
{
	for (int i = 0; i < settings::c_numOfSkills; i++)
	{
		m_window.draw(m_heroStatIcons[i]);
		m_heroStatValues[i]->draw();
	}
}
