#include "TownBuilding.h"

namespace settings = TownBuildingSettings;

TownBuilding::TownBuilding(sf::RenderWindow& window, Textures* pTextures, Fonts* pFonts, ConfirmationWindow* pConfirmationWindow, PopUpTextBox* pPopUpTextBox, ResourcesBar& rResourcesBar) :
	m_window(window),
	m_pTextures(pTextures),
	m_resourcesBar(rResourcesBar),
	m_pFactionBuildingData(nullptr),
	m_pTownBuildingData(nullptr),
	m_pResources(nullptr),
	m_pTownData(nullptr),
	m_pConfirmationWindow(pConfirmationWindow),
	m_pPopUpTextBox(pPopUpTextBox),
	m_selectedBuildingIndex(0)
{
	for (int i = 0; i < settings::c_numOfBuildings; i++)
	{
		m_upgradeButtons.push_back(std::unique_ptr<TownBuildingUpgrade>(new TownBuildingUpgrade(window, pTextures, pFonts)));
	}

	updateConfirmationFunctionPointer();
}

TownBuilding::~TownBuilding()
{
}

void TownBuilding::setUpUpgradeButtons()
{
	sf::Vector2f centre = m_window.getView().getCenter();

	for (int i = 0; i < settings::c_numOfBuildings; i++)
	{
		m_upgradeButtons[i]->baseSetUp(centre.x + settings::c_positionXOffset[i], centre.y + settings::c_positionYOffset[i]);
	}
}

void TownBuilding::updateUpgradeButtonNameAndTexture(const int& buttonIndex, const std::string& buildingName, const sf::Texture& buildingTexture)
{
	m_upgradeButtons[buttonIndex]->setNameAndTexture(buildingName, buildingTexture);
}

void TownBuilding::setBuildingDataPointers(TownBuildingData* townBuildingData, FactionBuildingData* factionBuildingData, Resources* resources, TownData* townData)
{
	m_pTownBuildingData = townBuildingData;
	m_pFactionBuildingData = factionBuildingData;
	m_pResources = resources;
	m_pTownData = townData;
	m_pConfirmationWindow->setConfirmationFunctionPointer(std::bind(&TownBuilding::incrementTownBuildingLevel, this));
}

void TownBuilding::setPopUpInformation(const int& buttonIndex)
{
	bool isBuildingMaxLevel = m_upgradeButtons[buttonIndex]->getCanBePurchased();
	std::string popUpText = "Building Level: ";

	//Show building level
	int buildingLevel = m_pTownBuildingData->getData(static_cast<TownBuildingEnum>(buttonIndex));

	if (buttonIndex < settings::c_numOfBasicBuildings)
	{
		isBuildingMaxLevel = buildingLevel == settings::c_basicBuildingsMaxLevel[buttonIndex];
	}
	else
	{
		isBuildingMaxLevel = buildingLevel;
	}

	m_pPopUpTextBox->setPopUpWidth(settings::c_popUpWidth[isBuildingMaxLevel]);

	if (isBuildingMaxLevel)
	{
		popUpText += "Max level\n\nCan't upgrade any further.";
	}
	else
	{
		popUpText += std::to_string(buildingLevel) + "\n\n" + "Purchase cost:\n";

		//Show upgrade cost
		if (buttonIndex < settings::c_numOfBasicBuildings)
		{
			int upgradeCostIndex = calculateUpgradeCostIndexForBasicBuildings(buttonIndex);

			//Gold Cost
			popUpText += "Gold: " + std::to_string(settings::c_buildingCostGold[upgradeCostIndex]) + "\n";

			//Wood Cost
			popUpText += "Wood: " + std::to_string(settings::c_buildingCostWood[upgradeCostIndex]) + "\n";

			//Stone Cost
			popUpText += "Stone: " + std::to_string(settings::c_buildingCostStone[upgradeCostIndex]);
		}
		else
		{
			int upgradeCostIndex = buttonIndex - settings::c_numOfBasicBuildings;
			//Gold Cost
			popUpText += "Gold: " + std::to_string(static_cast<int>(m_pFactionBuildingData->getData()["unitBuildingCostGold"][upgradeCostIndex]))+ "\n";

			//Wood Cost
			popUpText += "Wood: " + std::to_string(static_cast<int>(m_pFactionBuildingData->getData()["unitBuildingCostWood"][upgradeCostIndex])) + "\n";

			//Stone Cost
			popUpText += "Stone: " + std::to_string(static_cast<int>(m_pFactionBuildingData->getData()["unitBuildingCostStone"][upgradeCostIndex]));
		}
	}
	m_pPopUpTextBox->setUpPopUp(popUpText);
}

void TownBuilding::updateBuildingAvailability()
{
	//Check basic buildings
	for (int i = 0; i < settings::c_numOfBasicBuildings; i++)
	{
		checkIfBaseBuildingCanBePurchased(i, calculateUpgradeCostIndexForBasicBuildings(i));
	}

	//Check Unit buildings
	for (int i = 0; i < c_numOfUnitsPerFaction; i++)
	{
		checkIfUnitBuildingCanBePurchased(i);
	}
}

void TownBuilding::checkIfBaseBuildingCanBePurchased(const int& buttonIndex, const int& upgradeCostIndex)
{
	if (settings::c_basicBuildingsMaxLevel[buttonIndex] == m_pTownBuildingData->getData(static_cast<TownBuildingEnum>(buttonIndex)))
	{
		m_upgradeButtons[buttonIndex]->UIElement::setColor(sf::Color::Yellow);
		m_upgradeButtons[buttonIndex]->setCanBePurchased(false);
	}
	else
	{
		if (m_pTownBuildingData->getCanBuildingBePurchased())
		{

			if (settings::c_buildingCostGold[upgradeCostIndex] <= m_pResources->getResource(ResourcesEnum::gold) &&
				settings::c_buildingCostWood[upgradeCostIndex] <= m_pResources->getResource(ResourcesEnum::wood) &&
				settings::c_buildingCostStone[upgradeCostIndex] <= m_pResources->getResource(ResourcesEnum::stone))
			{
				m_upgradeButtons[buttonIndex]->UIElement::setColor(sf::Color::Green); //Player can purchase this building
				m_upgradeButtons[buttonIndex]->setCanBePurchased(true);
			}
			else
			{
				m_upgradeButtons[buttonIndex]->UIElement::setColor(sf::Color::Red); //Player can't purchase this building
				m_upgradeButtons[buttonIndex]->setCanBePurchased(false);
			}
		}
		else
		{
			m_upgradeButtons[buttonIndex]->UIElement::setColor(sf::Color::Black);
			m_upgradeButtons[buttonIndex]->setCanBePurchased(false);
		}
	}
}

void TownBuilding::checkIfUnitBuildingCanBePurchased(const int& unitIndex)
{
	int buttonIndex = unitIndex + settings::c_numOfBasicBuildings;

	if (m_pTownBuildingData->getData(static_cast<TownBuildingEnum>(buttonIndex)) == 0)
	{
		if (m_pTownBuildingData->getCanBuildingBePurchased())
		{
			if (m_pFactionBuildingData->getData()["unitBuildingCostGold"][unitIndex] <= m_pResources->getResource(ResourcesEnum::gold) &&
				m_pFactionBuildingData->getData()["unitBuildingCostWood"][unitIndex] <= m_pResources->getResource(ResourcesEnum::wood) &&
				m_pFactionBuildingData->getData()["unitBuildingCostStone"][unitIndex] <= m_pResources->getResource(ResourcesEnum::stone))
			{
				m_upgradeButtons[buttonIndex]->UIElement::setColor(sf::Color::Green); //Player can purchase this building
				m_upgradeButtons[buttonIndex]->setCanBePurchased(true);
			}
			else
			{
				m_upgradeButtons[buttonIndex]->UIElement::setColor(sf::Color::Red); //Player can't purchase this building
				m_upgradeButtons[buttonIndex]->setCanBePurchased(false);
			}
		}
		else
		{
			m_upgradeButtons[buttonIndex]->UIElement::setColor(sf::Color::Black);
			m_upgradeButtons[buttonIndex]->setCanBePurchased(false);
		}
	}
	else
	{
		m_upgradeButtons[buttonIndex]->UIElement::setColor(sf::Color::Yellow);
		m_upgradeButtons[buttonIndex]->setCanBePurchased(false);
	}
}

void TownBuilding::updateConfirmationFunctionPointer()
{
	m_pConfirmationWindow->setConfirmationFunctionPointer(std::bind(&TownBuilding::incrementTownBuildingLevel, this));
}

void TownBuilding::chargePlayerForPurchase()
{
	if (m_selectedBuildingIndex < settings::c_numOfBasicBuildings)
	{
		chargeForBasicBuildings(calculateUpgradeCostIndexForBasicBuildings(m_selectedBuildingIndex));
	}
	else
	{
		chargeForUnitBuildings();
	}
}

void TownBuilding::chargeForBasicBuildings(const int& upgradeCostIndex)
{
	//Make sure the values are negative
	m_pResources->incrementResourceValue(ResourcesEnum::gold, - settings::c_buildingCostGold[upgradeCostIndex]);
	m_pResources->incrementResourceValue(ResourcesEnum::wood, - settings::c_buildingCostWood[upgradeCostIndex]);
	m_pResources->incrementResourceValue(ResourcesEnum::stone, - settings::c_buildingCostStone[upgradeCostIndex]);
}

void TownBuilding::chargeForUnitBuildings()
{
	int unitIndex = m_selectedBuildingIndex - settings::c_numOfBasicBuildings;

	//Make sure the values are negative
	m_pResources->incrementResourceValue(ResourcesEnum::gold, - static_cast<int>(m_pFactionBuildingData->getData()["unitBuildingCostGold"][unitIndex])); //When accessing int data from a json file it doesn't allow for - operator so I have to cast it to an int
	m_pResources->incrementResourceValue(ResourcesEnum::wood, - static_cast<int>(m_pFactionBuildingData->getData()["unitBuildingCostWood"][unitIndex]));
	m_pResources->incrementResourceValue(ResourcesEnum::stone, - static_cast<int>(m_pFactionBuildingData->getData()["unitBuildingCostStone"][unitIndex]));

	m_pTownData->getAvailableUnitsToRecruit()[unitIndex] = m_pTownData->getUnitData(unitIndex)->getIntData(UnitDataEnum::growthPerWeek); //Update available units once unit building is purchased
}

const int TownBuilding::calculateUpgradeCostIndexForBasicBuildings(const int& buildingIndex)
{
	int buildingLevel = m_pTownBuildingData->getData(static_cast<TownBuildingEnum>(buildingIndex));
	int upgradeCostIndex = 0;
	if (buildingIndex > 0)
	{
		for (int i = 0; i < buildingIndex; i++)
		{
			upgradeCostIndex += settings::c_basicBuildingsMaxLevel[i];
		}
	}
	upgradeCostIndex += buildingLevel;

	return upgradeCostIndex;
}

void TownBuilding::repositionUpgradeButtons()
{
	sf::Vector2f centre = m_window.getView().getCenter();

	for (int i = 0; i < settings::c_numOfBuildings; i++)
	{
		m_upgradeButtons[i]->reposition(centre.x + settings::c_positionXOffset[i], centre.y + settings::c_positionYOffset[i]);
	}
}

bool TownBuilding::update(const sf::Vector2f& mousePosition)
{
	bool toggleButtonPress = false;
	bool isButtonHovered = false;

	//Check Button press

	for (int i = 0; i < settings::c_numOfBuildings; i++)
	{
		if (m_upgradeButtons[i]->checkMouseCollision(mousePosition))
		{
			isButtonHovered = true;
			if (!m_pPopUpTextBox->getActiveState())
			{
				m_pPopUpTextBox->toggleIsActive();
				m_pPopUpTextBox->setPosition(mousePosition);
				setPopUpInformation(i);
			}

			if (Global::g_isLMBPressed && m_upgradeButtons[i]->getCanBePurchased())
			{
				toggleButtonPress = true;
				Global::objectPressed();
				m_selectedBuildingIndex = i;
				m_pConfirmationWindow->changeUILayerToConfirmation();
				break;
			}
		}
	}


	if (!isButtonHovered && m_pPopUpTextBox->getActiveState())
	{
		m_pPopUpTextBox->toggleIsActive();
	}

	return toggleButtonPress;
}

void TownBuilding::incrementTownBuildingLevel()
{
	m_pTownBuildingData->setCanBuildingBePurchased(false);
	chargePlayerForPurchase();
	m_pTownBuildingData->incrementData(static_cast<TownBuildingEnum>(m_selectedBuildingIndex));
	m_pConfirmationWindow->changeUILayerToTown();
	updateBuildingAvailability();
	m_resourcesBar.updateResourcesBarValues(*m_pResources);
}

void TownBuilding::draw()
{
	for (int i = 0; i < settings::c_numOfBuildings; i++)
	{
		m_upgradeButtons[i]->draw();
	}
}

FactionBuildingData& TownBuilding::getBaseFactionBuildingData()
{
	return *m_pFactionBuildingData;
}

std::vector<std::unique_ptr<TownBuildingUpgrade>>& TownBuilding::getUpgradeButtonsVectorReference()
{
	return m_upgradeButtons;
}

void TownBuilding::setSelectedBuildingIndex(const int& buildingIndex)
{
	m_selectedBuildingIndex = buildingIndex;
}

