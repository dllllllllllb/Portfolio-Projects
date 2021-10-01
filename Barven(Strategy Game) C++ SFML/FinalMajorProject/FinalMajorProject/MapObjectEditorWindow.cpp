#include "MapObjectEditorWindow.h"

MapObjectEditorWindow::MapObjectEditorWindow(sf::RenderWindow& rWindow, Textures* pTextures, Fonts* pFonts) :
	TextBoxTitle(rWindow,pTextures,pFonts),
	UIElement(rWindow, pTextures, true),
	m_numOfInputButtons(0),
	m_acceptButton(pTextures, true),
	m_declineButton(pTextures, false)
{
	setUpTitleText(MapCreatorSettings::c_editorWindowTitle, MapCreatorSettings::c_editorWindowTitleCharSize);
	setPosition(m_window.getSize().x - (MapCreatorSettings::c_editorWindowWidth * 0.5f) - 6, m_window.getView().getCenter().y);
}

MapObjectEditorWindow::~MapObjectEditorWindow()
{
}

void MapObjectEditorWindow::setUpWindow(const int& numOfButtons)
{
	//Makes sure that the number of buttons is sufficient
	if (numOfButtons != m_numOfInputButtons)
	{
		for (int i = 0; i < numOfButtons - m_numOfInputButtons; i++) //Create new buttons if current number of buttons is not enough,
		{
			m_inputButtons.push_back(std::unique_ptr<TextInputBox>(new TextInputBox(m_window, m_pTextures, m_pFonts, true)));
		}

		m_numOfInputButtons = numOfButtons;

		resizeWindow(); //Resizes the window based on number of buttons
		int firstPosY = UIElement::getPosition().y - UIElement::getGlobalBounds().height * 0.5f + MapCreatorSettings::c_editorWindowInputBoxHeight * 0.5f + MapCreatorSettings::c_editorWindowSpaceing + getTitleHeight();

		//Set positions and collision bounds of buttons
		for (int i = 0; i < m_numOfInputButtons; i++)
		{
			m_inputButtons[i]->setPosition(UIElement::getPosition().x, firstPosY + ((MapCreatorSettings::c_editorWindowInputBoxHeight + MapCreatorSettings::c_editorWindowSpaceing) * i));
			m_inputButtons[i]->setUpUIBorder(MapCreatorSettings::c_editorWindowInputBoxWidth, MapCreatorSettings::c_editorWindowInputBoxHeight);
			m_inputButtons[i]->setCollisionBounds(MapCreatorSettings::c_editorWindowInputBoxWidth, MapCreatorSettings::c_editorWindowInputBoxHeight);
		}

		int basicButtonYPos = m_inputButtons[m_numOfInputButtons - 1]->sf::Sprite::getPosition().y + MapCreatorSettings::c_editorWindowSpaceing * 2 + m_acceptButton.getGlobalBounds().height;

		m_acceptButton.sf::Sprite::setPosition(getPosition().x - m_acceptButton.getGlobalBounds().width, basicButtonYPos);
		m_acceptButton.CollidableObject::setPosition(getPosition().x - m_acceptButton.getGlobalBounds().width, basicButtonYPos);
		m_declineButton.sf::Sprite::setPosition(getPosition().x + m_declineButton.getGlobalBounds().width, basicButtonYPos);
		m_declineButton.CollidableObject::setPosition(getPosition().x + m_declineButton.getGlobalBounds().width, basicButtonYPos);
	}
}

void MapObjectEditorWindow::resizeWindow()
{
	int newHeight = (m_numOfInputButtons + 1) * ((MapCreatorSettings::c_editorWindowInputBoxHeight) + MapCreatorSettings::c_editorWindowSpaceing) + MapCreatorSettings::c_editorWindowSpaceing;
	setUpUIBorder(MapCreatorSettings::c_editorWindowWidth, newHeight);
	setDefaultTitlePosition();
}

void MapObjectEditorWindow::setUpButtons(const int& buttonIndex, const std::string& buttonName, const int& contentValue)
{
	m_inputButtons[buttonIndex]->setUpTitleText(buttonName, MapCreatorSettings::c_editorInputButtonNameCharSize);
	m_inputButtons[buttonIndex]->setUpText(std::to_string(contentValue), MapCreatorSettings::c_editorInputButtonContentCharSize, TextAlignmentEnum::middleHorizontal, TextAlignmentEnum::middleVertical);
	m_inputButtons[buttonIndex]->setPlayerInput(std::to_string(contentValue));
	m_inputButtons[buttonIndex]->setInputTextPosition();
}

void MapObjectEditorWindow::setApplyValuesToObjectFunction(std::function<void()> function)
{
	m_pApplyValuesToObjectFunction = function;
}

void MapObjectEditorWindow::setCloseWindowFunction(std::function<void()> function)
{
	m_pCloseWindow = function;
}

const bool MapObjectEditorWindow::update(const bool isLMBPressed, const sf::Vector2f& mousePosition)
{
	bool toggleButtonPress = false;

	//Update input buttons
	for (int i = 0; i < m_numOfInputButtons; i++)
	{
		if (m_inputButtons[i]->checkMouseCollision(mousePosition) && isLMBPressed)
		{
			toggleButtonPress = true;
			m_inputButtons[i]->setButtonPressed(true);
		}
		m_inputButtons[i]->update();
	}

	//Update basic buttons
	if (isLMBPressed && m_acceptButton.collisionCheck(mousePosition))
	{
		toggleButtonPress = true;
		resetButtonFocus();
		m_pApplyValuesToObjectFunction();
	}

	if (isLMBPressed && m_declineButton.collisionCheck(mousePosition))
	{
		toggleButtonPress = true;
		m_pCloseWindow();
	}

	return toggleButtonPress;
}

void MapObjectEditorWindow::draw()
{
	UIElement::drawUIBorderAndBackground();
	for (int i = 0; i < m_numOfInputButtons; i++)
	{
		m_inputButtons[i]->draw();
	}
	m_window.draw(m_acceptButton);
	m_window.draw(m_declineButton);
	TextBoxTitle::draw();
}

const int MapObjectEditorWindow::getPlayerInput(const int& buttonIndex) const
{
	int value = 0;
	if (m_inputButtons[buttonIndex]->getPlayerInput() != "")
	{
		value = std::stoi(m_inputButtons[buttonIndex]->getPlayerInput());
	}

	return value;
}

void MapObjectEditorWindow::resetButtonFocus()
{
	for (int i = 0; i < m_numOfInputButtons; i++)
	{
		m_inputButtons[i]->setButtonPressed(false);
	}
}
