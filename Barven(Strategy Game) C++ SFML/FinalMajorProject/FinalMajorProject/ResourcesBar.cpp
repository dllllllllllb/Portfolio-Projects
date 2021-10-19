#include "ResourcesBar.h"

namespace settings = ResourceBarSettings;

ResourcesBar::ResourcesBar(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts) :
	m_window(rWindow),
	m_bar(rWindow, rTextures),
	m_goldText(rWindow, rTextures, rFonts),
	m_woodText(rWindow, rTextures, rFonts),
	m_stoneText(rWindow, rTextures, rFonts)
{
	m_goldIcon.setTexture(rTextures.m_resourceUIIcons[0], true);
	m_woodIcon.setTexture(rTextures.m_resourceUIIcons[1], true);
	m_stoneIcon.setTexture(rTextures.m_resourceUIIcons[2], true);

	m_goldIcon.setOrigin(m_goldIcon.getTexture()->getSize().x * 0.5f, m_goldIcon.getTexture()->getSize().y * 0.5f);
	m_woodIcon.setOrigin(m_woodIcon.getTexture()->getSize().x * 0.5f, m_woodIcon.getTexture()->getSize().y * 0.5f);
	m_stoneIcon.setOrigin(m_stoneIcon.getTexture()->getSize().x * 0.5f, m_stoneIcon.getTexture()->getSize().y * 0.5f);
}

ResourcesBar::~ResourcesBar()
{
}

void ResourcesBar::setUp()
{

	sf::Vector2f centre = m_window.getView().getCenter();

	m_bar.setUp(settings::c_barWidth, settings::c_barHeight, centre.x, settings::c_barHeight + 5);

	int spaceing = static_cast<int> (settings::c_barWidth / (settings::c_numOfResources));
	int yo = static_cast<int> (settings::c_barWidth / (settings::c_numOfResources + 1));
	int firstResourcePosition = static_cast<int> ((centre.x - settings::c_barWidth * 0.5f) + yo * 0.5f);

	m_goldIcon.setPosition(firstResourcePosition, m_bar.getPosition().y);
	m_goldText.setHasBackground(false);
	m_goldText.sf::Text::setPosition(m_goldIcon.getPosition().x + m_goldIcon.getGlobalBounds().width, m_bar.getPosition().y);
	m_goldText.setUpText("100000", settings::c_charSize, TextAlignmentEnum::left, TextAlignmentEnum::middleVertical);

	m_woodIcon.setPosition(firstResourcePosition + spaceing, m_bar.getPosition().y);
	m_woodText.setHasBackground(false);
	m_woodText.sf::Text::setPosition(m_woodIcon.getPosition().x + m_woodIcon.getGlobalBounds().width, m_bar.getPosition().y);
	m_woodText.setUpText("1000", settings::c_charSize, TextAlignmentEnum::left, TextAlignmentEnum::middleVertical);

	m_stoneIcon.setPosition(firstResourcePosition + spaceing * 2, m_bar.getPosition().y);
	m_stoneText.setHasBackground(false);
	m_stoneText.sf::Text::setPosition(m_stoneIcon.getPosition().x + m_stoneIcon.getGlobalBounds().width, m_bar.getPosition().y);
	m_stoneText.setUpText("1000", settings::c_charSize, TextAlignmentEnum::left, TextAlignmentEnum::middleVertical);
}

void ResourcesBar::updateResourcesBarValues(const Resources& resources)
{
	for (int i = 0; i < ResourceBarSettings::c_numOfResources; i++)
	{
		setResourceValue(static_cast<ResourcesEnum>(i), resources.getResource(static_cast<ResourcesEnum>(i)));
	}
}

void ResourcesBar::setResourceValue(const ResourcesEnum& resource, const int& value)
{
	switch (resource)
	{
	case ResourcesEnum::gold:
		m_goldText.setString(std::to_string(value));
		break;

	case ResourcesEnum::wood:
		m_woodText.setString(std::to_string(value));
		break;

	case ResourcesEnum::stone:
		m_stoneText.setString(std::to_string(value));
		break;

	default:
		break;
	}
}

void ResourcesBar::draw()
{
	m_bar.draw();

	m_goldText.draw();
	m_woodText.draw();
	m_stoneText.draw();

	m_window.draw(m_goldIcon);
	m_window.draw(m_woodIcon);
	m_window.draw(m_stoneIcon);
}
