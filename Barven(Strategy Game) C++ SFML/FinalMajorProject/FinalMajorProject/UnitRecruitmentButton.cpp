#include "UnitRecruitmentButton.h"

namespace settings = TownRecruitmentSettings;

UnitRecruitmentButton::UnitRecruitmentButton(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts, Audio& rAudio) :
	Button(rWindow, rTextures, rFonts, rAudio),
	UIElement(rWindow, rTextures),
	TextBoxTitle(rWindow, rTextures, rFonts),
	m_index(0)
{
}

UnitRecruitmentButton::~UnitRecruitmentButton()
{
}

void UnitRecruitmentButton::reposition(const float& positionX, const float& positionY)
{
	Button::reposition(positionX, positionY);
	setTitlePosition(m_unitIcon.getTexture()->getSize().x * 0.5f, 0);

	float iconPosX = positionX - (settings::c_recruitButtonWidth * 0.5f) + m_unitIcon.getTexture()->getSize().x * 0.5f;
	m_unitIcon.setPosition(iconPosX, positionY);
}

void UnitRecruitmentButton::setUpButton(const int& unitIndex, const std::string& unitName, const sf::Texture& unitIcon, const int& posX, const int& posY)
{
	m_index = unitIndex;
	setPosition(posX, posY);
	setUpUIBorder(settings::c_recruitButtonWidth, settings::c_recruitButtonHeight);
	setCollisionBounds(settings::c_recruitButtonWidth, settings::c_recruitButtonHeight);
	setUpTitleText(unitName, settings::c_titleCharSize);
	setTitlePosition(unitIcon.getSize().x *0.5f, 0);

	float iconWidthHalf = unitIcon.getSize().x * 0.5f;

	sf::Text::setPosition(posX + iconWidthHalf * 2, posY + getTitleHeight());

	m_unitIcon.setTexture(unitIcon);
	m_unitIcon.setOrigin(iconWidthHalf, unitIcon.getSize().y * 0.5f);
	float iconPosX = posX - (settings::c_recruitButtonWidth * 0.5f) + iconWidthHalf;

	m_unitIcon.setPosition(iconPosX, posY);
}

void UnitRecruitmentButton::updateUnitNameAndIcon(const std::string& unitName, const sf::Texture& unitIcon)
{
	setUpTitleText(unitName, settings::c_titleCharSize);
	m_unitIcon.setTexture(unitIcon, true);
}

void UnitRecruitmentButton::draw()
{
	UIElement::drawUIBackground();
	if (m_isShaderActive)
	{
		UIElement::drawFillShader();
	}
	Button::drawButtonText();
	TextBoxTitle::draw();
	m_window.draw(m_unitIcon);
	UIElement::drawUIBorder();
}
