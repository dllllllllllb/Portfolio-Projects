#include "UnitsPanel.h"

namespace settings = TownHeroesUnitsPanelSettings;

UnitsPanel::UnitsPanel(sf::RenderWindow& rWindow, Textures* pTextures, Fonts* pFonts) :
	m_window(rWindow),
	m_textures(*pTextures),
	m_background(rWindow, pTextures),
	m_cardOutline(rWindow, pTextures, true),
	m_unitsUsedInThisPanel(nullptr),
	m_unitInformationCard(rWindow, *pTextures, *pFonts),
	m_isUnitCardSelected(false),
	m_selectedCardIndex(-1),
	m_unitCardInformationIndex(-1)
{
	for (int i = 0; i < c_numOfUnitsPerFaction; i++)
	{
		m_unitCards.push_back(std::unique_ptr<UnitCard>(new UnitCard(rWindow, pTextures, pFonts)));
		m_unitCards[i]->setUpAndResizeToSprite(0, 0, pTextures->m_emptyUnitIcon);
	}
}

UnitsPanel::~UnitsPanel()
{
}

void UnitsPanel::setUpPanel(const int& positionX, const int& positionY, const bool setUnitCardInfoOnTheRight)
{
	int panelWidth = settings::c_unitCardWidth + (2 * (settings::c_backgroundSpaceing + settings::c_unitCardBorderSize));
	int panelHeight = (settings::c_unitCardHeight + settings::c_unitCardBorderSize) * c_numOfUnitsPerFaction + (2 * settings::c_backgroundSpaceing) + settings::c_unitCardBorderSize;

	int firstUnitCardYPos = positionY - panelHeight * 0.5f + settings::c_unitCardHeight * 0.5f + settings::c_backgroundSpaceing + settings::c_unitCardBorderSize + settings::c_unitCardBorderSize;

	//Setup background
	m_background.setPosition(positionX, positionY);
	m_background.setUpUIBorder(panelWidth, panelHeight);

	//Set up empty unit cards
	for (int i = 0; i < c_numOfUnitsPerFaction; i++)
	{
		m_unitCards[i]->IconButton::setPosition(m_background.getPosition().x, firstUnitCardYPos + (i * settings::c_unitCardHeight) + settings::c_unitCardBorderSize + settings::c_unitCardBorderSize);
		m_unitCards[i]->setUpText("", settings::c_charSize, TextAlignmentEnum::left, TextAlignmentEnum::bottom);
		m_unitCards[i]->sf::Text::setPosition(m_unitCards[i]->getPosition().x - settings::c_textOffsetX, m_unitCards[i]->getPosition().y + settings::c_textOffsetY);
		m_unitCards[i]->sf::Text::setOutlineColor(sf::Color::Black);
		m_unitCards[i]->sf::Text::setOutlineThickness(settings::c_textOutlineThickness);
	}

	//Set up card outline (visual representation of selected unit card)
	m_cardOutline.setPosition(m_unitCards[0]->getPosition());
	m_cardOutline.setUpUIBorder(settings::c_unitCardWidth, settings::c_unitCardHeight);
	m_cardOutline.setBorderColor(sf::Color::Yellow);

	if (setUnitCardInfoOnTheRight)
	{
		m_unitInformationCard.initialize(m_background.getPosition().x + panelWidth* 0.5f + UnitInformationCardSettings::c_backgroundWidth * 0.5f, m_background.getPosition().y - UnitInformationCardSettings::c_backgroundHeight * 0.5f);
	}
	else
	{
		m_unitInformationCard.initialize(m_background.getPosition().x - panelWidth * 0.5f - UnitInformationCardSettings::c_backgroundWidth * 0.5f, m_background.getPosition().y - UnitInformationCardSettings::c_backgroundHeight * 0.5f);
	}
}

void UnitsPanel::setUnitCards(std::vector<std::shared_ptr<Unit>>& vectorOfUnits)
{
	resetUnitCards();
	resetSelectedIndexes();

	m_unitsUsedInThisPanel = &vectorOfUnits;
	int unitIndex = 0;
	for (auto& unit : *m_unitsUsedInThisPanel)
	{
		if (unit->getIsDataSet())
		{
			m_unitCards[unitIndex]->setButtonIcon(unit->getBaseUnitData()->getUnitIcon());
			m_unitCards[unitIndex]->setString(std::to_string(unit->getNumOfUnits()));
		}
		unitIndex++;
	}
}

void UnitsPanel::updateUnitCardsContent()
{
	resetUnitCards();
	int unitIndex = 0;
	for (auto& unit : *m_unitsUsedInThisPanel)
	{
		if (unit->getIsDataSet())
		{
			m_unitCards[unitIndex]->setButtonIcon(unit->getBaseUnitData()->getUnitIcon());
			m_unitCards[unitIndex]->setString(std::to_string(unit->getNumOfUnits()));
		}
		unitIndex++;
	}
}

void UnitsPanel::resetUnitCards()
{
	for (auto& unitCard : m_unitCards)
	{
		unitCard->setButtonIcon(m_textures.m_emptyUnitIcon);
		unitCard->setString("");
	}
}

const bool UnitsPanel::update(const sf::Vector2f& mousePosition)
{
	bool wasUnitSelected = false;
	if (Global::g_isLMBPressed || Global::g_isRMBPressed)
	{
		for (int i = 0; i < c_numOfUnitsPerFaction; i++)
		{
			//Check if player selected a unit
			if (Global::g_isLMBPressed && m_unitCards[i]->collisionCheck(mousePosition))
			{
				Global::objectPressed();

				if (m_isUnitCardSelected && m_selectedCardIndex != i)
				{
					changeUnitsPositions(i);
					break;
				}

				if (m_selectedCardIndex == i)
				{
					toggleIsUnitCardSelected();
				}
				else
				{
					m_isUnitCardSelected = true;
				}
				m_selectedCardIndex = i;

				m_cardOutline.moveBorder(m_unitCards[i]->getPosition().x, m_unitCards[i]->getPosition().y);
				m_cardOutline.setPosition(m_unitCards[i]->getPosition());
				wasUnitSelected = true;
				break;
			}

			//Check if player activated unit information card
			if (Global::g_isRMBPressed && m_unitCards[i]->collisionCheck(mousePosition))
			{
				Global::RMBPressed();

				if (m_unitCardInformationIndex == i)
				{
					m_unitInformationCard.toggleIsActive();
				}
				else
				{
					if (m_unitsUsedInThisPanel->at(i)->getIsDataSet())
					{
						m_unitInformationCard.setIsActive(true);
						m_unitInformationCard.setUnitData(*m_unitsUsedInThisPanel->at(i));
					}
					else
					{
						m_unitInformationCard.resetUnitData();
						if (!m_unitInformationCard.getIsActive())
						{
							m_unitInformationCard.setIsActive(true);
						}
					}
				}
				m_unitCardInformationIndex = i;
				break;
			}
		}
	}

	return wasUnitSelected;
}

void UnitsPanel::changeUnitsPositions(const int& indexToSwapWith)
{
	//Try to implement std::move if you have time
	std::shared_ptr<Unit> tempUnit = m_unitsUsedInThisPanel->at(m_selectedCardIndex);

	m_unitsUsedInThisPanel->at(m_selectedCardIndex) = m_unitsUsedInThisPanel->at(indexToSwapWith);
	m_unitsUsedInThisPanel->at(indexToSwapWith) = tempUnit;

	toggleIsUnitCardSelected();
	updateUnitCardsContent();
	resetSelectedIndexes();
}

void UnitsPanel::resetSelectedIndexes()
{
	m_selectedCardIndex = -1;
	m_unitCardInformationIndex = -1;
}

void UnitsPanel::toggleIsUnitCardSelected()
{
	m_isUnitCardSelected = !m_isUnitCardSelected;
}

void UnitsPanel::setIsUnitCardSelected(const bool state)
{
	m_isUnitCardSelected = state;
}

void UnitsPanel::draw()
{
	m_background.drawUIBackground();

	for (int i = 0; i < c_numOfUnitsPerFaction; i++)
	{
		m_unitCards[i]->draw();
	}

	if (m_isUnitCardSelected)
	{
		m_cardOutline.drawUIBorder();
	}

	m_background.drawUIBorder();

	m_unitInformationCard.draw();
}

const int& UnitsPanel::getUnitPanelWidth()
{
	return m_background.getGlobalBounds().width + 2 * settings::c_unitCardBorderSize;
}

const bool UnitsPanel::getIsUnitCardSelected() const
{
	return m_isUnitCardSelected;
}

std::vector<std::shared_ptr<Unit>>* UnitsPanel::getVectorOfUnitsUsedByThisPanel()
{
	return m_unitsUsedInThisPanel;
}

const int& UnitsPanel::getSelectedCardIndex() const
{
	return m_selectedCardIndex;
}
