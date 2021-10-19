#include "TownBuildingUpgrade.h"

namespace settings = TownBuildingSettings;

TownBuildingUpgrade::TownBuildingUpgrade(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts, Audio& rAudio) :
	Button(rWindow, rTextures, rFonts, rAudio),
	TextBoxTitle(rWindow, rTextures, rFonts),
	UIElement(rWindow, rTextures),
	m_canBePurchased(false)
{
}

TownBuildingUpgrade::~TownBuildingUpgrade()
{
}

void TownBuildingUpgrade::reposition(const float& positionX, const float& positionY)
{
	Button::reposition(positionX, positionY);
	m_buildingUpgradeSprite.setPosition(positionX, positionY - ((settings::c_townBuildingUpgradeButtonSizeY - m_buildingUpgradeSprite.getTexture()->getSize().y) * 0.5f));
	m_imageTextBorder.setPosition(positionX, m_buildingUpgradeSprite.getPosition().y + m_buildingUpgradeSprite.getGlobalBounds().height * 0.5f);
}

void TownBuildingUpgrade::baseSetUp(const int& positionX, const int& positionY)
{
	Button::setPosition(positionX, positionY);
	setUpUIBorder(settings::c_townBuildingUpgradeButtonSizeX, settings::c_townBuildingUpgradeButtonSizeY);
	setCollisionBounds(settings::c_townBuildingUpgradeButtonSizeX, settings::c_townBuildingUpgradeButtonSizeY);
	setUpText("Upg. Building", 24, TextAlignmentEnum::middleHorizontal, TextAlignmentEnum::bottom);

	//Building sprite
	m_buildingUpgradeSprite.setTexture(m_textures.m_baseBuildingUpgradeSprite, true);
	m_buildingUpgradeSprite.setOrigin(m_buildingUpgradeSprite.getGlobalBounds().width * 0.5f, m_buildingUpgradeSprite.getGlobalBounds().height * 0.5f);
	m_buildingUpgradeSprite.setPosition(positionX, positionY - ((settings::c_townBuildingUpgradeButtonSizeY - m_buildingUpgradeSprite.getTexture()->getSize().y) * 0.5f));

	//Image text border
	m_imageTextBorder.setTexture(m_textures.m_thinBorder);
	float borderWidthScale = settings::c_townBuildingUpgradeButtonSizeX / m_imageTextBorder.getGlobalBounds().width;
	m_imageTextBorder.scale(borderWidthScale, 1);
	m_imageTextBorder.setOrigin(m_imageTextBorder.getLocalBounds().width * 0.5f, m_imageTextBorder.getGlobalBounds().height * 0.5f);
	m_imageTextBorder.setPosition(positionX, m_buildingUpgradeSprite.getPosition().y + m_buildingUpgradeSprite.getGlobalBounds().height * 0.5f);
}

void TownBuildingUpgrade::setCanBePurchased(const bool state)
{
	m_canBePurchased = state;
}

void TownBuildingUpgrade::toggleCanBePurchased()
{
	m_canBePurchased = !m_canBePurchased;
}

const bool TownBuildingUpgrade::getCanBePurchased() const
{
	return m_canBePurchased;
}

void TownBuildingUpgrade::setNameAndTexture(const std::string& buildingName,const sf::Texture& texture)
{
	setUpText(buildingName, 24, TextAlignmentEnum::middleHorizontal, TextAlignmentEnum::bottom);

	m_buildingUpgradeSprite.setTexture(texture, true);
}

void TownBuildingUpgrade::draw()
{
	drawUIBackground();
	if (m_isShaderActive)
	{
		drawFillShader();
	}
	m_window.draw(m_buildingUpgradeSprite);
	m_window.draw((sf::Text)*this);
	m_window.draw(m_imageTextBorder);
	drawUIBorder();
}
