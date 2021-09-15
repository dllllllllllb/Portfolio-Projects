#include "UnitCreationTool.h"

UnitCreationTool::UnitCreationTool(sf::RenderWindow& window, Textures* pTextures, Fonts* pFonts) :
	m_window(window),
	m_unitImageBackground(window, pTextures),
	m_createUnitButton(window, pTextures, pFonts),
	m_dataHandler()

{
	for (int i = 0; i < UnitCreator::c_numOfButtons; i++)
	{
		m_dataInputButton.push_back(std::unique_ptr<TextInputBox>(new TextInputBox(window, pTextures, pFonts)));
	}
}

UnitCreationTool::~UnitCreationTool()
{
}

void UnitCreationTool::initialize()
{
	//Unit Image Background
	m_unitImageBackground.setPosition(m_window.getSize().x * 0.5f, 500);
	m_unitImageBackground.setUpUIBorder(350, 460);

	// See "UnitCreationSettings.h" to see button order in the array and their parameters
	//Data input buttons
	for (int i = 0; i < UnitCreator::c_numOfButtons; i++)
	{
		m_dataInputButton[i]->setPosition(UnitCreator::c_buttonPosX[i], UnitCreator::c_buttonPosY[i]);

		switch (static_cast<UnitDataEnum>(i))
		{
		case UnitDataEnum::sprite:
		case UnitDataEnum::unitIcon:
		case UnitDataEnum::faction:
		case UnitDataEnum::mapSprite:
			m_dataInputButton[i]->setUpUIBorder(UnitCreator::c_widerButtonWidth, UnitCreator::c_buttonHeight);
			m_dataInputButton[i]->setCollisionBounds(UnitCreator::c_widerButtonWidth, UnitCreator::c_buttonHeight);
			break;

		default:
			m_dataInputButton[i]->setUpUIBorder(UnitCreator::c_buttonWidth, UnitCreator::c_buttonHeight);
			m_dataInputButton[i]->setCollisionBounds(UnitCreator::c_buttonWidth, UnitCreator::c_buttonHeight);
			break;
		}

		m_dataInputButton[i]->setUpText(UnitCreator::c_buttonContent, UnitCreator::c_buttonContentCharSize, TextAlignmentEnum::middleHorizontal, TextAlignmentEnum::middleVertical);
		m_dataInputButton[i]->setUpTitleText(UnitCreator::c_buttonName[i], UnitCreator::c_buttonNameCharSize);
		m_dataInputButton[i]->setInputTextPosition();
	}

	//Create Unit Button
	m_createUnitButton.setPosition(1700, 835);
	m_createUnitButton.setUpUIBorder(300, 100);
	m_createUnitButton.setCollisionBounds(300, 100);
	m_createUnitButton.setUpText("Create Unit", 48, TextAlignmentEnum::middleHorizontal, TextAlignmentEnum::middleVertical);
}

void UnitCreationTool::resetInputFieldsFocus()
{
	for (int i = 0; i < UnitCreator::c_numOfButtons; i++)
	{
		m_dataInputButton[i]->setButtonPressed(false);
	}
}

void UnitCreationTool::update(const sf::Vector2f& mousePosition)
{
	if (Global::g_isLMBPressed)
	{
		resetInputFieldsFocus();
	}

	for (int i = 0; i < UnitCreator::c_numOfButtons; i++)
	{
		if (m_dataInputButton[i]->checkMouseCollision(mousePosition) && Global::g_isLMBPressed)
		{
			Global::objectPressed();
			m_dataInputButton[i]->setButtonPressed(true);
		}
	}

	if (m_createUnitButton.checkMouseCollision(mousePosition) && Global::g_isLMBPressed)
	{
		Global::objectPressed();
		saveUnitData();
	}

	for (int i = 0; i < UnitCreator::c_numOfButtons; i++)
	{
		m_dataInputButton[i]->update();
	}
}

void UnitCreationTool::saveUnitData()
{
	json tempJSON;

	for (int i = 0; i < UnitCreator::c_numOfButtons; i++)
	{
		switch (static_cast<UnitDataEnum>(i))
		{
		case UnitDataEnum::sprite: //String variables with directory
		case UnitDataEnum::unitIcon:
		case UnitDataEnum::mapSprite:
			tempJSON[c_unitDataEnumStrings[i]] = DataHandlerSettings::c_unitTexturesDirectory + "\\" + m_dataInputButton[i]->getPlayerInput();
			break;

		case UnitDataEnum::unitName: //String variables
		case UnitDataEnum::faction:
			tempJSON[c_unitDataEnumStrings[i]] = m_dataInputButton[i]->getPlayerInput();
			break;

		default: //Int variables
			tempJSON[c_unitDataEnumStrings[i]] = std::stoi(m_dataInputButton[i]->getPlayerInput());
			break;
		}
	}
	//Saves unit data under the set faction name
	m_dataHandler.saveUnitData("\\" + tempJSON.value("faction", "yo"), tempJSON);
}

void UnitCreationTool::draw()
{
	m_unitImageBackground.drawUIBorderAndBackground();

	for (int i = 0; i < UnitCreator::c_numOfButtons; i++)
	{
		m_dataInputButton[i]->draw();
	}

	m_createUnitButton.draw();
}