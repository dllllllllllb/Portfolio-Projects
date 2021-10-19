#include "RecourceTradingButton.h"

namespace settings = ResourceTradingButtonSettings;

ResourceTradingButton::ResourceTradingButton(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts, Audio& rAudio) :
	UIElement(rWindow, rTextures, true),
	Button(rWindow, rTextures, rFonts, rAudio, true),
	TextBoxTitle(rWindow, rTextures, rFonts),
	m_textures(rTextures),
	m_resourceAmount(0)
{
}

ResourceTradingButton::~ResourceTradingButton()
{
}

void ResourceTradingButton::setUp(const int& positionX, const int& positionY, const ResourcesEnum& resourceType, const std::string& resourceAmount)
{
	//Set up button background and border
	Button::setPosition(positionX, positionY);
	setUpUIBorder(settings::c_buttonHeight, settings::c_buttonHeight);
	setCollisionBounds(settings::c_buttonHeight, settings::c_buttonHeight);

	//Set base text variables
	setUpText(resourceAmount, settings::c_charSize, TextAlignmentEnum::middleHorizontal, TextAlignmentEnum::bottom);

	//Set up resource sprite icon
	m_resourceSprite.setTexture(m_textures.m_resourceUIIcons[static_cast<int>(resourceType)], true);
	m_resourceSprite.setScale(settings::c_resourceSpriteScale, settings::c_resourceSpriteScale);
	m_resourceSprite.setOrigin(m_resourceSprite.getLocalBounds().width * 0.5f, m_resourceSprite.getLocalBounds().height * 0.5f);
	m_resourceSprite.setPosition(positionX, positionY - settings::c_buttonHeight * 0.5f + m_resourceSprite.getGlobalBounds().height * 0.5f + settings::c_iconYOffset);

	//Set up border between resource icon and resource amount
	m_imageTextBorder.setTexture(m_textures.m_thinBorder);
	float borderWidthScale = Button::UIElement::getGlobalBounds().width / m_imageTextBorder.getGlobalBounds().width;
	m_imageTextBorder.scale(borderWidthScale, 1);
	m_imageTextBorder.setOrigin(m_imageTextBorder.getLocalBounds().width * 0.5f, m_imageTextBorder.getGlobalBounds().height * 0.5f);
	m_imageTextBorder.setPosition(positionX, m_resourceSprite.getPosition().y + settings::c_textBorderOffset);

}

void ResourceTradingButton::setResourceAmount(const int& resourceAmount)
{
	Button::setString(std::to_string(resourceAmount));
	Button::updateAlignment();
	m_resourceAmount = resourceAmount;
}

const int& ResourceTradingButton::getResourceAmount()
{
	return m_resourceAmount;
}

void ResourceTradingButton::draw()
{
	drawUIBackground();
	if (m_isShaderActive)
	{
		drawFillShader();
	}
	m_window.draw(m_resourceSprite);
	m_window.draw((sf::Text)*this);
	m_window.draw(m_imageTextBorder);
	drawUIBorder();
}
