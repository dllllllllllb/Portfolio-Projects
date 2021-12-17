#include "Town.h"

namespace settings = TownSettings;

Town::Town(sf::RenderWindow& window, Textures& rTextures, Fonts& rFonts, Audio& rAudio, ConfirmationWindow& rConfirmationWindow, ResourcesBar& rResourcesBar) :
	m_window(window),
	m_background(window, rTextures),
	m_sectionBackground(window, rTextures),
	m_townEnum(TownEnum::townCentre),
	m_textures(rTextures),
	m_audio(rAudio),
	m_confirmationWindow(rConfirmationWindow),
	m_popUpTextBox(window, rTextures, rFonts),
	m_townBuilding(window, rTextures, rFonts, rAudio, m_confirmationWindow, m_popUpTextBox, rResourcesBar),
	m_recruitment(window, rTextures, rFonts, rAudio, m_confirmationWindow, m_townsUnitsPannel, rResourcesBar),
	m_townsUnitsPannel(window, rTextures, rFonts, rAudio),
	m_visitingHeroUnitsPannel(window, rTextures, rFonts, rAudio),
	m_townTrading(window, rTextures, rFonts, rAudio, rConfirmationWindow, rResourcesBar),
	m_isTownActive(false),
	m_isHeroVisiting(false),
	m_isLastSelectedUnitInHerosPanel(false),
	m_pVisitingHero(nullptr)
{
	for (int i = 0; i < settings::c_numOfButtons; i++)
	{
		m_buttons.push_back(std::unique_ptr<Button>(new Button(window, rTextures, rFonts, rAudio)));
	}
}

Town::~Town()
{
}

void Town::initialize()
{
	//Background
	m_background.setPosition(m_window.getSize().x * 0.5f, m_window.getSize().y * 0.5f);
	m_background.setUpUIBorder(m_window.getSize().x - c_UIBorder, m_window.getSize().y - c_UIBorder);

	//Section background
	m_sectionBackground.setPosition(m_window.getSize().x * 0.5f, m_window.getSize().y * 0.5f);
	m_sectionBackground.setUpUIBorder(1150, 850);

	setUpButtons();

	m_townBuilding.setUpUpgradeButtons();

	m_townsUnitsPannel.setUpPanel(settings::c_unitPanelPosition, m_window.getView().getCenter().y, true, true);
	m_visitingHeroUnitsPannel.setUpPanel(settings::c_unitPanelPosition + m_townsUnitsPannel.getUnitPanelWidth(), m_window.getView().getCenter().y, true, true);

	m_recruitment.initialize();
	m_recruitment.setFunctionToCallAfterPurchasingAHero(std::bind(&Town::setVisitingHeroData, this, std::placeholders::_1));

	m_confirmationWindow.reposition();

	m_townTrading.setUp();
}

void Town::setUpButtons()
{
	sf::Vector2f centre = m_window.getView().getCenter();
	sf::Vector2u windowSize = m_window.getSize();
	float navButtonsX = centre.x + (windowSize.x * 0.5f) - (settings::c_buttonWidth * 0.5f) - settings::c_screenBorderOffset;

	float allButtonsSizeY = (settings::c_numOfButtons * settings::c_buttonHeight) + ((settings::c_numOfButtons - 1) * settings::c_gapBetweenButtons);
	float firstButtonPosY = centre.y - (0.5f * allButtonsSizeY) + settings::c_buttonHeight * 0.5f;

	for (int i = 0; i < settings::c_numOfButtons; i++)
	{
		m_buttons[i]->setPosition(navButtonsX, firstButtonPosY + (i * (settings::c_buttonHeight + settings::c_gapBetweenButtons)));
		m_buttons[i]->setUpUIBorder(settings::c_buttonWidth, settings::c_buttonHeight);
		m_buttons[i]->setCollisionBounds(settings::c_buttonWidth, settings::c_buttonHeight);
		m_buttons[i]->setUpText(settings::c_buttonText[i], settings::c_charSize, TextAlignmentEnum::middleHorizontal, TextAlignmentEnum::middleVertical);
	}
}

void Town::setTownData(const int& factionIndex, TownData& townData, FactionBuildingData& factionBuildingData, Player& player, const bool isHeroVisiting)
{
	m_townBuilding.setBuildingDataPointers(&townData.getTownBuildingData(), &factionBuildingData, &player.getResources(), &townData);
	m_townEnum = TownEnum::townCentre;
	Global::g_UILayer = UILayerEnum::town;
	Global::toggleUpdateGame();

	if (isHeroVisiting)
	{
		setVisitingHeroData(&player.getSelectedHero());
	}
	else
	{
		clearVisitingHeroData();
	}

	toggleIsTownActive();
	m_visitingHeroUnitsPannel.setIsUnitCardSelected(false);

	for (int i = 0; i < c_numOfUnitsPerFaction; i++)
	{
		m_recruitment.setUnitDataPointer(i, townData.getUnitData(i));
	}
	m_recruitment.setPlayerSpecificData(&player, &townData, factionIndex);
	m_recruitment.setIsHeroInTown(m_isHeroVisiting);
	m_recruitment.updateRecruitmentButtonsNameAndIcons();
	m_recruitment.setDefaultPurchaseWindowContent();

	for (int i = 0; i < TownBuildingSettings::c_numOfBuildings; i++)
	{
		m_townBuilding.updateUpgradeButtonNameAndTexture(i, factionBuildingData.getData()["unitBuildingsNames"][i], factionBuildingData.getBuildingTexture(static_cast<TownBuildingEnum>(i)));
	}

	m_townBuilding.updateBuildingAvailability();

	m_townsUnitsPannel.setUnitCards(townData.getVectorOfUnitsStationedInsideTheTown());

	if (!m_isHeroVisiting)
	{
		m_visitingHeroUnitsPannel.resetUnitCards();
		m_visitingHeroUnitsPannel.resetSelectedIndexes();
	}

	m_townTrading.setResourcesPointer(&player.getResources());

	m_audio.playMusic(MusicEnum::townMusic, factionIndex);
}

void Town::clearVisitingHeroData()
{
	m_isHeroVisiting = false;
	m_pVisitingHero = nullptr;
	m_visitingHeroUnitsPannel.resetUnitCards();
	m_visitingHeroUnitsPannel.resetSelectedIndexes();
}

void Town::setVisitingHeroData(Hero* hero)
{
	m_isHeroVisiting = true;
	m_pVisitingHero = hero;
	m_visitingHeroUnitsPannel.setUnitCards(hero->getVectorOfUnits());
}

void Town::reposition()
{
	sf::Vector2f centre = m_window.getView().getCenter();
	sf::Vector2u windowSize = m_window.getSize();

	m_background.moveUIElement(centre.x, centre.y);
	m_sectionBackground.moveUIElement(centre.x, centre.y);

	float navButtonsX = centre.x + (windowSize.x * 0.5f) - (settings::c_buttonWidth * 0.5f) - settings::c_screenBorderOffset;

	float allButtonsSizeY = (settings::c_numOfButtons * settings::c_buttonHeight) + ((settings::c_numOfButtons - 1) * settings::c_gapBetweenButtons);
	float firstButtonPosY = centre.y - (0.5f * allButtonsSizeY) + settings::c_buttonHeight * 0.5f;

	for (int i = 0; i < settings::c_numOfButtons; i++)
	{
		m_buttons[i]->reposition(navButtonsX, firstButtonPosY + (i * (settings::c_buttonHeight + settings::c_gapBetweenButtons)));
	}
}

void Town::update(const sf::Vector2f& mousePosition, const float& deltaTime)
{
	if (m_isTownActive)
	{
		if (Global::g_UILayer == UILayerEnum::town)
		{
			for (int i = 0; i < settings::c_numOfButtons; i++)
			{
				if (m_buttons[i]->checkIfButtonWasPressed(mousePosition))
				{
					m_townEnum = static_cast<TownEnum>(++i);

					switch (m_townEnum)
					{
					case TownEnum::townCentre:
						break;

					case TownEnum::build:
						m_townBuilding.updateConfirmationFunctionPointer();
						m_townBuilding.updateBuildingAvailability();
						break;

					case TownEnum::recruitUnits:
						m_recruitment.updateConfirmationFunctionPointer();
						break;

					case TownEnum::trade:
						m_townTrading.updateConfirmationFunctionPointer();
						break;

					case TownEnum::spells:
						break;

					case TownEnum::buyArtefacts:
						break;

					case TownEnum::exit:
						break;

					default:
						break;
					}
				}
			}

			updateUnitPanels(mousePosition);

		}
		draw();

		switch (m_townEnum)
		{
		case TownEnum::townCentre:
		{
		}
		break;

		case TownEnum::build:
		{
			if (Global::g_UILayer == UILayerEnum::town)
			{
				m_townBuilding.update(mousePosition);
			}
			m_townBuilding.draw();
		}
		break;

		case TownEnum::recruitUnits:
		{
			if (Global::g_UILayer == UILayerEnum::town)
			{
				m_recruitment.update(mousePosition, deltaTime);
			}
			m_recruitment.draw();
		}
		break;

		case TownEnum::trade:
		{
			if (Global::g_UILayer == UILayerEnum::town)
			{
				m_townTrading.update(mousePosition);
			}

			m_townTrading.draw();
		}
		break;

		case TownEnum::spells:
		{
		}
		break;

		case TownEnum::buyArtefacts:
		{
		}
		break;

		case TownEnum::exit:
		{
			Global::g_UILayer = UILayerEnum::map;
			m_audio.playMusic(MusicEnum::mapMusic, 0);
			Global::toggleUpdateGame();
			toggleIsTownActive();
		}
		break;

		default:
			break;
		}

		if (m_popUpTextBox.getActiveState())
		{
			m_popUpTextBox.drawPopUpBox();
		}

		if (Global::g_UILayer == UILayerEnum::confirmation)
		{
			if (m_confirmationWindow.update(mousePosition))
			{
				Global::g_UILayer = UILayerEnum::town;
			}
			m_confirmationWindow.draw();
		}

		m_visitingHeroUnitsPannel.draw();
		m_townsUnitsPannel.draw();
	}
}

void Town::updateUnitPanels(const sf::Vector2f& mousePosition)
{
	if (m_isHeroVisiting)
	{
		if (m_visitingHeroUnitsPannel.update(mousePosition))
		{
			m_isLastSelectedUnitInHerosPanel = true;
		}
	}

	if (m_townsUnitsPannel.update(mousePosition))
	{
		m_isLastSelectedUnitInHerosPanel = false;
	}

	if (m_visitingHeroUnitsPannel.getIsUnitCardSelected() && m_townsUnitsPannel.getIsUnitCardSelected())
	{
		transferUnitsBetweenTownAndHero();
	}
}

void Town::transferUnitsBetweenTownAndHero()
{
		auto* visitingUnits = m_visitingHeroUnitsPannel.getVectorOfUnitsUsedByThisPanel();
		auto* townUnits = m_townsUnitsPannel.getVectorOfUnitsUsedByThisPanel();

		//Check if player wants to combine units
		if (visitingUnits->at(m_visitingHeroUnitsPannel.getSelectedCardIndex())->getIsDataSet() && townUnits->at(m_townsUnitsPannel.getSelectedCardIndex())->getIsDataSet() &&
			visitingUnits->at(m_visitingHeroUnitsPannel.getSelectedCardIndex())->getBaseUnitData()->getStringData(UnitDataEnum::unitName) == townUnits->at(m_townsUnitsPannel.getSelectedCardIndex())->getBaseUnitData()->getStringData(UnitDataEnum::unitName))
		{
			if (m_isLastSelectedUnitInHerosPanel)
			{
				visitingUnits->at(m_visitingHeroUnitsPannel.getSelectedCardIndex())->incrementNumOfUnits(townUnits->at(m_townsUnitsPannel.getSelectedCardIndex())->getNumOfUnits());
				townUnits->at(m_townsUnitsPannel.getSelectedCardIndex())->resetUnitData();
			}
			else
			{
				townUnits->at(m_townsUnitsPannel.getSelectedCardIndex())->incrementNumOfUnits(visitingUnits->at(m_visitingHeroUnitsPannel.getSelectedCardIndex())->getNumOfUnits());
				visitingUnits->at(m_visitingHeroUnitsPannel.getSelectedCardIndex())->resetUnitData();
			}
		}
		else
		{
			std::shared_ptr<Unit> tempUnit = visitingUnits->at(m_visitingHeroUnitsPannel.getSelectedCardIndex());
			visitingUnits->at(m_visitingHeroUnitsPannel.getSelectedCardIndex()) = townUnits->at(m_townsUnitsPannel.getSelectedCardIndex());
			townUnits->at(m_townsUnitsPannel.getSelectedCardIndex()) = tempUnit;
		}

		m_visitingHeroUnitsPannel.setIsUnitCardSelected(false);
		m_townsUnitsPannel.setIsUnitCardSelected(false);

		m_visitingHeroUnitsPannel.updateUnitCardsContent();
		m_townsUnitsPannel.updateUnitCardsContent();

		m_visitingHeroUnitsPannel.resetSelectedIndexes();
		m_townsUnitsPannel.resetSelectedIndexes();

		m_pVisitingHero->updateNumberOfUnits();
		m_pVisitingHero->updateUnitsStats();
}

void Town::toggleIsTownActive()
{
	m_isTownActive = !m_isTownActive;
}

void Town::setIsTownActive(const bool state)
{
	m_isTownActive = state;
}

void Town::draw()
{
	m_background.drawUIBorderAndBackground();
	m_sectionBackground.drawUIBorderAndBackground();

	for (int i = 0; i < settings::c_numOfButtons; i++)
	{
		m_buttons[i]->draw();
	}
}

void Town::changeUILayerToConfirmation()
{
	Global::g_previousUILayer = Global::g_UILayer;
	Global::g_UILayer = UILayerEnum::confirmation;
}

void Town::changeUILayerToTown()
{
	Global::g_previousUILayer = Global::g_UILayer;
	Global::g_UILayer = UILayerEnum::town;
}

FactionBuildingData& Town::getBaseFactionBuildingData()
{
	return m_townBuilding.getBaseFactionBuildingData();
}

TownBuilding& Town::getTownBuildingReference()
{
	return m_townBuilding;
}
