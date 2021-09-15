#include "PlayerSettingsTable.h"
namespace settings = PlayerSettingsTableSettings;

PlayerSettingsTable::PlayerSettingsTable(sf::RenderWindow& rWindow, Textures* pTextures, Fonts* pFonts, DataHandler& rDataHandler) :
	m_window(rWindow),
	m_pTextures(pTextures),
	m_background(rWindow, pTextures),
	m_dataHandler(rDataHandler),
	m_numOfAvailablePlayers(0)
{
	//Allocate memory for table elements

	//Collumn Titles
	for (int i = 0; i < settings::c_numOfCollumns; i++)
	{
		m_pCollumnTitles.push_back(std::unique_ptr<TextBox>(new TextBox(rWindow, pTextures, pFonts, true)));
	}


	//Faction Selection Buttons && Player Name Input boxes && Bonus Selection Button
	for (int i = 0; i < settings::c_numOfMaxPlayers; i++)
	{
		m_pFactionSelectionButton.push_back(std::unique_ptr<IconButton>(new IconButton(rWindow, pTextures, true)));
		m_pPlayerNameInput.push_back(std::unique_ptr<TextInputBox>(new TextInputBox(rWindow, pTextures, pFonts, true)));
		m_pBonusSelectionButton.push_back(std::unique_ptr<IconButton>(new IconButton(rWindow, pTextures, true)));
		m_pIsAITickBox.push_back(std::unique_ptr<TickBox>(new TickBox(pTextures)));
	}

}

PlayerSettingsTable::~PlayerSettingsTable()
{
}

void PlayerSettingsTable::initialize()
{
	//Set up background
	int windowCentreX = m_window.getView().getCenter().x;
	int windowCentreY = m_window.getView().getCenter().y;

	int backgroundPosY = (settings::c_tableStartHeight + (((settings::c_numOfMaxPlayers) * settings::c_buttonOffsetY)) / 2);
	m_background.setPosition(windowCentreX, backgroundPosY);

	int backgroundWidth = settings::c_buttonWidth[0] + (settings::c_buttonWidth[1] * (settings::c_numOfCollumns - 1)) + settings::c_backgroundBorder;
	int backgroundHeight = ((settings::c_numOfMaxPlayers + 1) * settings::c_buttonOffsetY + settings::c_backgroundBorder);
	m_background.setUpUIBorder(backgroundWidth, backgroundHeight);

	//Set up the table
	// 
	//Set up collumn titles
	for (int i = 0; i < settings::c_numOfCollumns; i++)
	{
		if (i == 0) //Player name
		{
			m_pCollumnTitles[i]->setPosition(windowCentreX + settings::c_buttonXOffset[i], settings::c_tableStartHeight);
			m_pCollumnTitles[i]->setUpUIBorder(settings::c_buttonWidth[0], settings::c_buttonHeight);
			m_pCollumnTitles[i]->basicSetUp(settings::c_collumnTitles[i], settings::c_collumnTitleTextSize, windowCentreX + settings::c_buttonXOffset[i], settings::c_tableStartHeight);
		}
		else //Faction, start bonus and AI
		{	
			m_pCollumnTitles[i]->setPosition(windowCentreX + settings::c_buttonXOffset[i], settings::c_tableStartHeight);
			m_pCollumnTitles[i]->setUpUIBorder(settings::c_buttonWidth[1], settings::c_buttonHeight);
			m_pCollumnTitles[i]->basicSetUp(settings::c_collumnTitles[i], settings::c_collumnTitleTextSize, windowCentreX + settings::c_buttonXOffset[i], settings::c_tableStartHeight);
		}
	}

	for (int i = 0; i < settings::c_numOfMaxPlayers; i++)
	{
		//Player name input boxes
		m_pPlayerNameInput[i]->setPosition(windowCentreX + settings::c_buttonXOffset[0], settings::c_tableStartHeight + (settings::c_buttonOffsetY * (i + 1)));
		m_pPlayerNameInput[i]->setUpUIBorder(settings::c_buttonWidth[0], settings::c_buttonHeight);
		m_pPlayerNameInput[i]->setCollisionBounds(settings::c_buttonWidth[0], settings::c_buttonHeight);
		m_pPlayerNameInput[i]->setUpText(settings::c_defaultPlayerName, settings::c_playerNameTextSize, TextAlignmentEnum::middleHorizontal, TextAlignmentEnum::middleVertical);
		m_pPlayerNameInput[i]->setPlayerInput("Player");

		//Faction selection buttons
		m_pFactionSelectionButton[i]->setUpAndResizeToSprite(windowCentreX + settings::c_buttonXOffset[1], settings::c_tableStartHeight + (settings::c_buttonOffsetY * (i + 1)), m_pTextures->m_randomStartBonusIcon);

		//Start bonus buttons
		m_pBonusSelectionButton[i]->setUpAndResizeToSprite(windowCentreX + settings::c_buttonXOffset[2], settings::c_tableStartHeight + (settings::c_buttonOffsetY * (i + 1)), m_pTextures->m_randomStartBonusIcon);

		//AI tick boxes
		m_pIsAITickBox[i]->setPosition(windowCentreX + settings::c_buttonXOffset[3], settings::c_tableStartHeight + (settings::c_buttonOffsetY * (i + 1)));

	}

	updateInactiveRowsPlayerFeedback();
}

void PlayerSettingsTable::update(const sf::Vector2f& mousePosition)
{
	if (Global::g_isLMBPressed)
	{
		resetInputButtonFocus();
	}

	updateButtonClick(mousePosition);

	updateInputButtons();
}

void PlayerSettingsTable::updateButtonClick(const sf::Vector2f& mousePosition)
{
	for (int i = 0; i < m_numOfAvailablePlayers; i++) //Checks only active setting rows
	{
		//Name
		if (m_pPlayerNameInput[i]->checkMouseCollision(mousePosition) && Global::g_isLMBPressed)
		{
			Global::objectPressed();

			m_pPlayerNameInput[i]->setButtonPressed(true);
			break;
		}

		//Faction
		if (m_pFactionSelectionButton[i]->collisionCheck(mousePosition) && Global::g_isLMBPressed)
		{
			Global::objectPressed();

			m_selectedFactionID[i]++;

			if (m_selectedFactionID[i] > c_numOfFactions)
			{
				m_selectedFactionID[i] = 0;
			}

			if (m_selectedFactionID[i] < c_numOfFactions)
			{
				m_pFactionSelectionButton[i]->setButtonIcon(m_dataHandler.getFactionData(m_selectedFactionID[i]).getBuildingsData().getTownIconTexture());
			}
			else
			{
				m_pFactionSelectionButton[i]->setButtonIcon(m_pTextures->m_randomStartBonusIcon);
			}
			break;
		}

		//Start Bonus
		if (m_pBonusSelectionButton[i]->collisionCheck(mousePosition) && Global::g_isLMBPressed)
		{
			Global::objectPressed();


			m_selectedBonusID[i]++;
			if (m_selectedBonusID[i] > settings::c_numOfBonusOptions)
			{
				m_selectedBonusID[i] = 0;
			}

			if (m_selectedBonusID[i] < settings::c_numOfBonusOptions)
			{
				m_pBonusSelectionButton[i]->setButtonIcon(m_pTextures->m_startBonusIcons[m_selectedBonusID[i]]);
			}
			else
			{
				m_pBonusSelectionButton[i]->setButtonIcon(m_pTextures->m_randomStartBonusIcon);
			}
			break;
		}

		//Is AI Tick Box

		if (Global::g_isLMBPressed && m_pIsAITickBox[i]->collisionCheck(mousePosition))
		{
			Global::objectPressed();
			m_pIsAITickBox[i]->toggleState();
			break;
		}

	}
}

void PlayerSettingsTable::updateInputButtons()
{
	for (int i = 0; i < m_numOfAvailablePlayers; i++)
	{
		m_pPlayerNameInput[i]->update();
	}
}

void PlayerSettingsTable::resetInputButtonFocus()
{
	for (int i = 0; i < settings::c_numOfMaxPlayers; i++)
	{
		if (m_pPlayerNameInput[i]->getIsButtonPressed())
		{
			m_pPlayerNameInput[i]->setButtonPressed(false);
		}
	}
}

void PlayerSettingsTable::setNumberOfAvailablePlayers(const int& numOfAvailablePlayers)
{
	m_numOfAvailablePlayers = numOfAvailablePlayers;
	m_selectedFactionID.clear();
	m_selectedBonusID.clear();

	for (int i = 0; i < m_numOfAvailablePlayers; i++)
	{
		m_selectedFactionID.push_back(c_numOfFactions + 1);
		m_selectedBonusID.push_back(settings::c_numOfBonusOptions);

		m_pFactionSelectionButton[i]->setButtonIcon(m_pTextures->m_randomStartBonusIcon);
		m_pBonusSelectionButton[i]->setButtonIcon(m_pTextures->m_randomStartBonusIcon);

		m_pIsAITickBox[i]->setState(false);
	}

	updateInactiveRowsPlayerFeedback();
}

void PlayerSettingsTable::updateInactiveRowsPlayerFeedback()
{
	for (int i = 0; i < settings::c_numOfMaxPlayers; i++)
	{
		if (i < m_numOfAvailablePlayers) //Active row
		{
			m_pPlayerNameInput[i]->UIElement::setColor(sf::Color::White);
			m_pPlayerNameInput[i]->sf::Text::setFillColor(sf::Color::White);
			m_pFactionSelectionButton[i]->getIconSprite().setColor(sf::Color::White);
			m_pBonusSelectionButton[i]->getIconSprite().setColor(sf::Color::White);
			m_pIsAITickBox[i]->sf::Sprite::setColor(sf::Color::White);
		}
		else //Inactive row
		{
			m_pPlayerNameInput[i]->UIElement::setColor(sf::Color::Black);
			m_pPlayerNameInput[i]->sf::Text::setFillColor(sf::Color::Black);
			m_pFactionSelectionButton[i]->getIconSprite().setColor(sf::Color::Black);
			m_pBonusSelectionButton[i]->getIconSprite().setColor(sf::Color::Black);
			m_pIsAITickBox[i]->sf::Sprite::setColor(sf::Color::Black);
		}
	}
}

const std::string& PlayerSettingsTable::getPlayerName(const int& playerIndex)
{
	return m_pPlayerNameInput[playerIndex]->getPlayerInput();
}

const int& PlayerSettingsTable::getPlayersChosenFaction(const int& playerIndex)
{
	return m_selectedFactionID[playerIndex];
}

const bool PlayerSettingsTable::getIsPlayerAI(const int& playerIndex)
{
	return m_pIsAITickBox[playerIndex]->getState();
}

void PlayerSettingsTable::draw()
{
	m_background.drawUIBorderAndBackground();

	for (int i = 0; i < settings::c_numOfCollumns; i++)
	{
		m_pCollumnTitles[i]->draw();
	}

	for (int i = 0; i < settings::c_numOfMaxPlayers; i++)
	{
		m_pPlayerNameInput[i]->draw();
		m_pFactionSelectionButton[i]->draw();
		m_pBonusSelectionButton[i]->draw();
		m_window.draw(*m_pIsAITickBox[i]);
	}
}
