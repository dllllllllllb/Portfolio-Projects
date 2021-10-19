#include "UnitTurnOrderBar.h"
namespace settings = UnitTurnOrderBarSettings;
UnitTurnOrderBar::UnitTurnOrderBar(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts, Audio& rAudio) :
	m_window(rWindow),
	m_background(rWindow, rTextures)
{
	for (int i = 0; i < settings::c_numOfUnitIconsToDisplay; i++)
	{
		m_unitCards.push_back(std::unique_ptr<UnitCard>(new UnitCard(rWindow, rTextures, rFonts, rAudio)));
	}
}

UnitTurnOrderBar::~UnitTurnOrderBar()
{
}

void UnitTurnOrderBar::setUp(const int& positionY)
{
	int borderWidth = settings::c_numOfUnitIconsToDisplay * (settings::c_unitIconWidth + settings::c_unitIconBorder * 3) + settings::c_unitIconBorder;
	m_background.setPosition(m_window.getView().getCenter().x, positionY);
	m_background.setUpUIBorder(borderWidth, settings::c_backgroundHeight);

	int iconStartPosX = m_background.getPosition().x - (borderWidth) * 0.5f + settings::c_unitIconWidth * 0.5f + settings::c_unitIconBorder;

	for (int i = 0; i < settings::c_numOfUnitIconsToDisplay; i++)
	{
		m_unitCards[i]->IconButton::setPosition(iconStartPosX + (i * (settings::c_unitIconWidth + settings::c_unitIconBorder * 3)), positionY);
		m_unitCards[i]->setUpText("", settings::c_charSize, TextAlignmentEnum::left, TextAlignmentEnum::bottom);
		m_unitCards[i]->sf::Text::setPosition(m_unitCards[i]->getPosition().x - settings::c_textOffsetX, m_unitCards[i]->getPosition().y + settings::c_textOffsetY);
		m_unitCards[i]->sf::Text::setOutlineColor(sf::Color::Black);
		m_unitCards[i]->sf::Text::setOutlineThickness(settings::c_textOutlineThickness);
		m_unitCards[i]->UIElement::setUpUIBorder(settings::c_unitIconWidth, settings::c_unitIconHeight);
	}
}

void UnitTurnOrderBar::setUnitCards(std::vector<std::unique_ptr<CombatUnit>>& combatUnitVector, std::vector<int>& unitOrder)
{
	int numberOfSetUnitCards = 0;

	while (numberOfSetUnitCards <= settings::c_numOfUnitIconsToDisplay - 1) //Loop for as long as it takes to fill up the turn order bar
	{
		for (int& combatUnitIndex : unitOrder) //Loop through unit order indexes
		{
			//Set appropriate icon and number of units
			m_unitCards[numberOfSetUnitCards]->setButtonIcon(combatUnitVector[combatUnitIndex]->getBaseUnitData()->getUnitIcon());
			m_unitCards[numberOfSetUnitCards]->setString(std::to_string(combatUnitVector[combatUnitIndex]->getNumOfUnits()));

			if (combatUnitVector[combatUnitIndex]->getIsAttacker()) //Set border color to indicate what side the unit is on
			{
				m_unitCards[numberOfSetUnitCards]->UIElement::setBorderColor(sf::Color::Cyan);
			}
			else
			{
				m_unitCards[numberOfSetUnitCards]->UIElement::setBorderColor(sf::Color::Red);
			}

			numberOfSetUnitCards++;

			if (numberOfSetUnitCards >= settings::c_numOfUnitIconsToDisplay) //Break if all slots in the bar have been filled
			{
				break;
			}
		}
	}
}

void UnitTurnOrderBar::draw()
{
	m_background.drawUIBackground();

	for (int i = 0; i < settings::c_numOfUnitIconsToDisplay; i++)
	{
		m_unitCards[i]->draw();
		m_unitCards[i]->UIElement::drawUIBorder();
	}

	m_background.drawUIBorder();
}