#include "TownRecruitment.h"

namespace settings = TownRecruitmentSettings;

TownRecruitment::TownRecruitment(sf::RenderWindow& rWindow, Textures* pTextures, Fonts* pFonts, ConfirmationWindow* pConfirmationWindow, UnitsPanel& rTownHeroesUnitsPanel, ResourcesBar& rResourcesBar) :
	m_window(rWindow),
	m_pTextures(pTextures),
	m_pConfirmationWindow(pConfirmationWindow),
	m_unitsPanel(rTownHeroesUnitsPanel),
	m_resourcesBar(rResourcesBar),
	m_purchaseUnitWindow(rWindow, pTextures, pFonts, pConfirmationWindow),
	m_purchaseErrorPopUpWindow(rWindow, pTextures, pFonts),
	m_purchaseHeroButton(rWindow, pTextures, pFonts),
	m_pPlayer(nullptr),
	m_pTownData(nullptr),
	m_selectedUnitIndex(0),
	m_purchaseErrorPopUpTimer(0),
	m_isHeroInTown(false)
{
	for (int i = 0; i < c_numOfUnitsPerFaction; i++)
	{
		m_recruitButtons.push_back(std::unique_ptr<UnitRecruitmentButton>(new UnitRecruitmentButton(rWindow, pTextures, pFonts)));
		m_unitsStationedInsideTheTown[i] = nullptr;
	}

	m_purchaseUnitWindow.setPurchaseUnitFunction(std::bind(&TownRecruitment::purchaseUnits, this));
}

TownRecruitment::~TownRecruitment()
{
}

void TownRecruitment::setUnitDataPointer(const int& index, UnitData* unitData)
{
	m_unitsStationedInsideTheTown[index] = unitData;
}

void TownRecruitment::reposition()
{
	sf::Vector2f centre = m_window.getView().getCenter();
	float firstYPos = centre.y + settings::c_recruitButtonFirstPosY;

	for (int i = 0; i < c_numOfUnitsPerFaction; i++)
	{
		m_recruitButtons[i]->reposition(centre.x + settings::c_recruitButtonXCentreOffset, firstYPos + (settings::c_recruitButtonSpaceing * i));
	}
}

void TownRecruitment::initialize()
{
	sf::Vector2f centre = m_window.getView().getCenter();
	float firstYPos = centre.y + settings::c_recruitButtonFirstPosY;

	for (int i = 0; i < c_numOfUnitsPerFaction; i++)
	{
		m_recruitButtons[i]->setUpButton(i, "Unit Name", m_pTextures->m_randomUnitIcon, centre.x + settings::c_recruitButtonXCentreOffset, firstYPos + (TownRecruitmentSettings::c_recruitButtonSpaceing * i));
	}
	m_purchaseUnitWindow.setUpPurchaseWindow();

	m_purchaseHeroButton.setPosition(centre.x + settings::c_purchaseHeroButtonXOffset, centre.y - settings::c_purchaseHeroButtonYOffset);
	m_purchaseHeroButton.setUpUIBorder(settings::c_recruitButtonWidth, settings::c_recruitButtonHeight);
	m_purchaseHeroButton.setCollisionBounds(settings::c_recruitButtonWidth, settings::c_recruitButtonHeight);
	m_purchaseHeroButton.setHasMultipleLines(true);
	m_purchaseHeroButton.setUpText(settings::c_purchaseHeroButtonText, settings::c_purchaseHeroButtonCharSize, TextAlignmentEnum::middleHorizontal, TextAlignmentEnum::middleVertical);
}

void TownRecruitment::updateRecruitmentButtonsNameAndIcons()
{
	for (int i = 0; i < c_numOfUnitsPerFaction; i++)
	{
		m_recruitButtons[i]->updateUnitNameAndIcon(m_unitsStationedInsideTheTown[i]->getUnitData()->getStringData(UnitDataEnum::unitName), m_unitsStationedInsideTheTown[i]->getUnitIcon());
	}
}

void TownRecruitment::updateConfirmationFunctionPointer()
{
	m_purchaseUnitWindow.updateConfirmationFunctionPointer();
}

void TownRecruitment::setDefaultPurchaseWindowContent()
{
	m_selectedUnitIndex = 0;
	m_purchaseUnitWindow.setWindowContent(m_unitsStationedInsideTheTown[0], m_pTownData->getAvailableUnitsToRecruit()[0]);
}

void TownRecruitment::setPlayerSpecificData(Player* player, TownData* pTownData, const int& factionIndex)
{
	m_pPlayer = player;
	m_pTownData = pTownData;
	m_purchaseUnitWindow.setUnitBackground(factionIndex);
}

void TownRecruitment::purchaseUnits()
{
	int unitCost = m_purchaseUnitWindow.getNumberOfUnitsToRecruit() * m_unitsStationedInsideTheTown[m_selectedUnitIndex]->getIntData(UnitDataEnum::cost);
	bool doesHeroAlreadyHasThatUnit = false;
	int unitPositionInVector = 0;
	int freeUnitVectorIndex = 0;

	//Check if player has enough resources
	if (m_purchaseUnitWindow.getNumberOfUnitsToRecruit() > 0)
	{
		if (unitCost <= m_pPlayer->getResources().getResource(ResourcesEnum::gold))
		{
			//Check if the town already has this unit
			for (auto& unitData : m_pTownData->getVectorOfUnitsStationedInsideTheTown())
			{
				if (unitData->getIsDataSet())
				{
					if (unitData->getBaseUnitData()->getStringData(UnitDataEnum::unitName) == m_unitsStationedInsideTheTown[m_selectedUnitIndex]->getStringData(UnitDataEnum::unitName))
					{
						doesHeroAlreadyHasThatUnit = true;
						break;
					}
				}
				unitPositionInVector++;
			}

			if (doesHeroAlreadyHasThatUnit)
			{
				m_pTownData->getVectorOfUnitsStationedInsideTheTown().at(unitPositionInVector)->incrementNumOfUnits(m_purchaseUnitWindow.getNumberOfUnitsToRecruit());
				m_pTownData->getAvailableUnitsToRecruit()[m_selectedUnitIndex] -= m_purchaseUnitWindow.getNumberOfUnitsToRecruit();

				m_unitsPanel.setUnitCards(m_pTownData->getVectorOfUnitsStationedInsideTheTown());
				m_pPlayer->getResources().incrementResourceValue(ResourcesEnum::gold, -unitCost);
				m_resourcesBar.updateResourcesBarValues(m_pPlayer->getResources());

				refreshPurchaseWindow();

				std::cout << "Number of units increased\nUnit index: " << std::to_string(m_selectedUnitIndex) << "\n";
			}
			else
			{
				//Check if the town has space to recruit this unit
				bool wasUnitPurchased = false;
				for (auto& unit : m_pTownData->getVectorOfUnitsStationedInsideTheTown())
				{
					if (!unit->getIsDataSet())
					{
						wasUnitPurchased = true;

						m_pTownData->addUnit(freeUnitVectorIndex, m_unitsStationedInsideTheTown[m_selectedUnitIndex]);
						m_pTownData->getVectorOfUnitsStationedInsideTheTown().at(freeUnitVectorIndex)->incrementNumOfUnits(m_purchaseUnitWindow.getNumberOfUnitsToRecruit());
						m_pTownData->getAvailableUnitsToRecruit()[m_selectedUnitIndex] -= m_purchaseUnitWindow.getNumberOfUnitsToRecruit();

						m_unitsPanel.setUnitCards(m_pTownData->getVectorOfUnitsStationedInsideTheTown());
						m_pPlayer->getResources().incrementResourceValue(ResourcesEnum::gold, -unitCost);
						m_resourcesBar.updateResourcesBarValues(m_pPlayer->getResources());

						refreshPurchaseWindow();
						break;
					}
					freeUnitVectorIndex++;
				}
				if (!wasUnitPurchased)
				{
					activateUnitPurchaseErrorPopUp(1);
				}
			}
		}
		else
		{
			activateUnitPurchaseErrorPopUp(0);
		}
	}
	else
	{
		activateUnitPurchaseErrorPopUp(2);
	}
}

void TownRecruitment::purchaseNewHero()
{
	if (m_pPlayer->getResources().getResource(ResourcesEnum::gold) >= settings::c_purchaseHeroPrice)
	{
		m_pPlayer->makeNewHero(m_pTownData->getTownMapPosition(), m_pTownData->getOccupiedTileIndex(), true);
		m_pPlayer->getResources().incrementResourceValue(ResourcesEnum::gold, -settings::c_purchaseHeroPrice);
		m_functionToCallAfterPurchasingHero(&m_pPlayer->getHero(m_pPlayer->getVectorOfOwnedHeroes().size() - 1));
		m_isHeroInTown = true;
	}
}

void TownRecruitment::refreshPurchaseWindow()
{
	m_purchaseUnitWindow.setWindowContent(m_unitsStationedInsideTheTown[m_selectedUnitIndex], m_pTownData->getAvailableUnitsToRecruit()[m_selectedUnitIndex]);
}

void TownRecruitment::updatePurchaseErrorPopUpWindow(const float& deltaTime)
{
	if (m_purchaseErrorPopUpWindow.getActiveState())
	{
		m_purchaseErrorPopUpTimer += deltaTime;

		if (m_purchaseErrorPopUpTimer > settings::c_purchaseErrorPopUpDuration)
		{
			m_purchaseErrorPopUpTimer = 0;
			m_purchaseErrorPopUpWindow.toggleIsActive();
		}
	}
}

void TownRecruitment::activateUnitPurchaseErrorPopUp(const int& messageIndex)
{
	m_purchaseErrorPopUpWindow.setIsActive(true);
	m_purchaseErrorPopUpWindow.setPosition(m_window.getView().getCenter().x + settings::c_popUpPositionXOffset, m_window.getView().getCenter().y + settings::c_popUpPositionYOffset);
	m_purchaseErrorPopUpWindow.setUpPopUp(settings::c_purchaseErrorMessages[messageIndex]);
}

bool TownRecruitment::update(const sf::Vector2f& mousePosition, const float& deltaTime)
{
	bool toggleButtonPress = false;

	for (int i = 0; i < c_numOfUnitsPerFaction; i++)
	{
		if (m_recruitButtons[i]->checkMouseCollision(mousePosition) && Global::g_isLMBPressed)
		{
			toggleButtonPress = true;
			m_purchaseUnitWindow.setWindowContent(m_unitsStationedInsideTheTown[i], m_pTownData->getAvailableUnitsToRecruit()[i]); //Change 10, 10 to its appropriate values later
			m_selectedUnitIndex = i;
			break;
		}
	}

	if (!m_isHeroInTown && m_purchaseHeroButton.checkMouseCollision(mousePosition) && Global::g_isLMBPressed)
	{
		toggleButtonPress = true;
		Global::objectPressed();
		purchaseNewHero();
	}

	updatePurchaseErrorPopUpWindow(deltaTime);

	toggleButtonPress = m_purchaseUnitWindow.update(mousePosition);

	return toggleButtonPress;
}

void TownRecruitment::setIsHeroInTown(const bool state)
{
	m_isHeroInTown = state;
}

void TownRecruitment::setFunctionToCallAfterPurchasingAHero(std::function<void(Hero*)> function)
{
	m_functionToCallAfterPurchasingHero = function;
}

void TownRecruitment::draw()
{
	for (int i = 0; i < c_numOfUnitsPerFaction; i++)
	{
		m_recruitButtons[i]->draw();
	}

	m_purchaseUnitWindow.draw();

	if (m_purchaseErrorPopUpWindow.getActiveState())
	{
		m_purchaseErrorPopUpWindow.drawPopUpBox();
	}

	m_purchaseHeroButton.draw();
}