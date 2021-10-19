#include "UnitInformationCard.h"

namespace settings = UnitInformationCardSettings;

UnitInformationCard::UnitInformationCard(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts) :
	m_window(rWindow),
	m_textures(rTextures),
	m_background(rWindow, rTextures),
	m_unitBackground(rWindow, rTextures, true),
	m_unitInformation(rWindow, rTextures, rFonts, true),
	m_isActive(false)
{
	
}

UnitInformationCard::~UnitInformationCard()
{
}

void UnitInformationCard::initialize(const int& positionX, const int& positionY)
{
	//Background
	m_background.setPosition(positionX, settings::c_backgroundHeight * 0.5f + positionY);
	m_background.setUpUIBorder(settings::c_backgroundWidth, settings::c_backgroundHeight);

	//Unit information text box
	m_unitInformation.setPosition(m_background.getPosition().x + settings::c_elementXOffset - settings::c_unitInformationBoxWidth * 0.5f, m_background.getPosition().y);
	m_unitInformation.setUpUIBorder(settings::c_unitInformationBoxWidth, settings::c_unitInformationBoxHeight);
	m_unitInformation.setHasMultipleLines(true);

	//Unit background
	m_unitBackground.setPosition(m_background.getPosition().x - settings::c_elementXOffset + settings::c_unitSpriteBackgroundWidth * 0.5f, m_background.getPosition().y);
	m_unitBackground.setTexture(m_textures.m_unitBackground[0], true);
	m_unitBackground.setUpUIBorder(settings::c_unitSpriteBackgroundWidth, settings::c_unitSpriteBackgroundHeight);

	//Unit sprite
	m_unitSprite.setPosition(m_unitBackground.getPosition());
}

void UnitInformationCard::setUnitData(CombatUnit& combatUnit)
{
	//m_unitBackground.setUpUIBorder(settings::c_unitSpriteBackgroundWidth, settings::c_unitSpriteBackgroundHeight);

	m_unitInformation.setUpTitleText(combatUnit.getBaseUnitData()->getStringData(UnitDataEnum::unitName), settings::c_titleCharSize);

	std::string unitStats = "Health: " + std::to_string(combatUnit.getBaseUnitData()->getIntData(UnitDataEnum::health)) + "\n" +
							"Current Health: " + std::to_string(combatUnit.getCurrentHealth()) + "\n" +
							"Attack: " + std::to_string(combatUnit.getUnitSpecificData(UnitBattleDataEnum::attack)) + "\n" +
							"Damage Range: " + std::to_string(combatUnit.getBaseUnitData()->getIntData(UnitDataEnum::minDamage)) + "-" + std::to_string(combatUnit.getBaseUnitData()->getIntData(UnitDataEnum::maxDamage)) + "\n" +
							"Defence: " + std::to_string(combatUnit.getUnitSpecificData(UnitBattleDataEnum::defence)) + "\n" +
							"Ammunition: " + std::to_string(combatUnit.getBaseUnitData()->getIntData(UnitDataEnum::ammunition)) + "\n" +
							"Speed: " + std::to_string(combatUnit.getBaseUnitData()->getIntData(UnitDataEnum::speed)) + "\n" +
							"Num. of Units: " + std::to_string(combatUnit.getNumOfUnits());

	m_unitInformation.setUpText(unitStats, settings::c_textCharSize, TextAlignmentEnum::left, TextAlignmentEnum::middleVertical);

	m_unitSprite.setColor(sf::Color::White);
	m_unitSprite.setTexture(combatUnit.getBaseUnitData()->getUnitSprite(), true);
	m_unitSprite.setOrigin(m_unitSprite.getGlobalBounds().width * 0.5f, m_unitSprite.getGlobalBounds().height * 0.5f);
}

void UnitInformationCard::setUnitData(Unit& unit)
{
	//m_unitBackground.setUpUIBorder(settings::c_unitSpriteBackgroundWidth, settings::c_unitSpriteBackgroundHeight);

	m_unitInformation.setUpTitleText(unit.getBaseUnitData()->getStringData(UnitDataEnum::unitName), settings::c_titleCharSize);

	std::string unitStats = "Health: " + std::to_string(unit.getBaseUnitData()->getIntData(UnitDataEnum::health)) + "\n" +
							"Current Health: " + std::to_string(unit.getCurrentHealth()) + "\n" +
							"Attack: " + std::to_string(unit.getUnitSpecificData(UnitBattleDataEnum::attack)) + "\n" +
							"Damage Range: " + std::to_string(unit.getBaseUnitData()->getIntData(UnitDataEnum::minDamage)) + "-" + std::to_string(unit.getBaseUnitData()->getIntData(UnitDataEnum::maxDamage)) + "\n" +
							"Defence: " + std::to_string(unit.getUnitSpecificData(UnitBattleDataEnum::defence)) + "\n" +
							"Ammunition: " + std::to_string(unit.getBaseUnitData()->getIntData(UnitDataEnum::ammunition)) + "\n" +
							"Speed: " + std::to_string(unit.getBaseUnitData()->getIntData(UnitDataEnum::speed)) + "\n" +
							"Num. of Units: " + std::to_string(unit.getNumOfUnits());

	m_unitInformation.setUpText(unitStats, settings::c_textCharSize, TextAlignmentEnum::left, TextAlignmentEnum::middleVertical);

	m_unitSprite.setColor(sf::Color::White);
	m_unitSprite.setTexture(unit.getBaseUnitData()->getUnitSprite(), true);
	m_unitSprite.setOrigin(m_unitSprite.getGlobalBounds().width * 0.5f, m_unitSprite.getGlobalBounds().height * 0.5f);
}

void UnitInformationCard::resetUnitData()
{
	m_unitSprite.setColor(sf::Color::Transparent);
	m_unitInformation.setTextAndUpdate("");
	m_unitInformation.setUpTitleText("", 0);
}

void UnitInformationCard::toggleIsActive()
{
	m_isActive = !m_isActive;
}

void UnitInformationCard::setIsActive(const bool state)
{
	m_isActive = state;
}

const bool UnitInformationCard::getIsActive() const
{
	return m_isActive;
}

void UnitInformationCard::draw()
{
	if (m_isActive)
	{
		m_background.drawUIBackground();
		m_unitBackground.drawUIBackground();
		m_window.draw(m_unitSprite);
		m_unitBackground.drawUIBorder();
		m_unitInformation.draw();
		m_background.drawUIBorder();
	}
}