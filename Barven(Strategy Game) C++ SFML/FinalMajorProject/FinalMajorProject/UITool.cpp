#include "UITool.h"

UITool::UITool(sf::RenderWindow& rWindow, Textures* pTextures, Fonts* pFonts):
	m_window(rWindow),
	m_UIToolApplyButton(rWindow, pTextures, pFonts)
{
	//Create input boxes
	for (int i = 0; i < UIToolSettings::c_numOfButtons; i++)
	{
		m_dataInputButton.push_back(std::unique_ptr<TextInputBox>(new TextInputBox(rWindow, pTextures, pFonts)));
	}
}

UITool::~UITool()
{
}

void UITool::initialize()
{
	//UIElement Apply Button
	m_UIToolApplyButton.setPosition(1700, 835);
	m_UIToolApplyButton.setUpUIBorder(300, 100);
	m_UIToolApplyButton.setCollisionBounds(300, 100);
	m_UIToolApplyButton.setUpText("Apply", 72, TextAlignmentEnum::middleHorizontal, TextAlignmentEnum::middleVertical);


	for (int i = 0; i < UIToolSettings::c_numOfButtons; i++)
	{
		m_dataInputButton[i]->setPosition(UIToolSettings::c_positionX[i], UIToolSettings::c_positionY[i]);
		m_dataInputButton[i]->setUpUIBorder(UIToolSettings::c_buttonWidth, UIToolSettings::c_buttonHeight);
		m_dataInputButton[i]->setCollisionBounds(UIToolSettings::c_buttonWidth, UIToolSettings::c_buttonHeight);
		m_dataInputButton[i]->setUpText(UIToolSettings::c_buttonContentText, UIToolSettings::c_contentCharSize, TextAlignmentEnum::middleHorizontal, TextAlignmentEnum::middleVertical);
		m_dataInputButton[i]->setUpTitleText(UIToolSettings::c_buttonTitle[i], 24);
		m_dataInputButton[i]->setInputTextPosition();
	}
}

void UITool::resetInputFieldsFocus()
{
	for (int i = 0; i < UIToolSettings::c_numOfButtons; i++)
	{
		m_dataInputButton[i]->setButtonPressed(false);
	}
}

void UITool::update(const sf::Vector2f& mousePosition)
{
	if (Global::g_isLMBPressed)
	{
		resetInputFieldsFocus();
	}

	if (m_UIToolApplyButton.checkMouseCollision(mousePosition) && Global::g_isLMBPressed)
	{
		Global::objectPressed();

		//Gets values the player typed inside input fields and casts them to floats
		float tempSizeX = std::stoi(m_dataInputButton[0]->getPlayerInput());
		float tempSizeY = std::stoi(m_dataInputButton[1]->getPlayerInput());

		float tempPosX = std::stof(m_dataInputButton[2]->getPlayerInput());
		float tempPosy = std::stof(m_dataInputButton[3]->getPlayerInput());


		//Uses these values to set position and dimentions of the UI element
		m_dataInputButton[4]->setPosition(tempPosX, tempPosy);
		m_dataInputButton[4]->setUpUIBorder(tempSizeX, tempSizeY);
		m_dataInputButton[4]->setCollisionBounds(tempSizeX, tempSizeY);

	}

	for (int i = 0; i < UIToolSettings::c_numOfButtons; i++)
	{
		if (m_dataInputButton[i]->checkMouseCollision(mousePosition) && Global::g_isLMBPressed)
		{
			Global::objectPressed();
			m_dataInputButton[i]->setButtonPressed(true);
		}
	}

	for (int i = 0; i < UIToolSettings::c_numOfButtons; i++)
	{
		m_dataInputButton[i]->update();
	}
}

void UITool::draw()
{
	for (int i = 0; i < UIToolSettings::c_numOfButtons; i++)
	{
		m_dataInputButton[i]->draw();
	}
	m_UIToolApplyButton.draw();
}
