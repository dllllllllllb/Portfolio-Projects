#include "GameSetUpScreen.h"

namespace settings = GameSetUpScreenSettings;

GameSetUpScreen::GameSetUpScreen(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts, Audio& rAudio, DataHandler& rDataHandler) :
	m_window(rWindow),
	m_dataHandler(rDataHandler),
	m_textures(rTextures),
	m_playerSettingsTable(rWindow, rTextures, rFonts, rAudio, rDataHandler),
	m_mapSelectionDropDown(rWindow, rTextures, rFonts, rAudio),
	m_startGameButton(rWindow, rTextures, rFonts, rAudio),
	m_backButton(rWindow, rTextures, rFonts, rAudio),
	m_refreshDropDownListButton(rWindow, rTextures, rAudio, true)
{
	m_mapSelectionDropDown.setConfirmationFunctionPointer(std::bind(&GameSetUpScreen::updateAvailablePlayers, this));
}

GameSetUpScreen::~GameSetUpScreen()
{
}

void GameSetUpScreen::initialize()
{
	m_playerSettingsTable.initialize();
	m_mapSelectionDropDown.setDropDownListSettings(settings::c_numOfOptionsToDisplay, settings::c_optionWidth, settings::c_optionHeight, m_window.getSize().x - settings::c_optionPositionXOffset, settings::c_optionPositionYOffset, settings::c_dropDownOptionsSpaceing, settings::c_primaryOptionTitle, settings::c_primaryOptionTitleCharSize, settings::c_primaryOptionContentText, settings::c_optionTextCharSize);
	for (std::string& mapName : m_dataHandler.getMapNames())
	{
		m_mapSelectionDropDown.addNewDropDownOptions(mapName);
	}
	m_mapSelectionDropDown.setOptionsPositions();
	m_mapSelectionDropDown.setUpSlider();

	setUpButtons();
}

void GameSetUpScreen::setUpButtons()
{
	m_startGameButton.setPosition(settings::c_buttonPosX[0], settings::c_buttonPosY);
	m_startGameButton.setUpUIBorder(settings::c_buttonWidth, settings::c_buttonHeight);
	m_startGameButton.setCollisionBounds(settings::c_buttonWidth, settings::c_buttonHeight);
	m_startGameButton.setUpText(settings::c_buttonName[0], settings::c_buttonCharSize, TextAlignmentEnum::middleHorizontal, TextAlignmentEnum::middleVertical);

	m_backButton.setPosition(settings::c_buttonPosX[1], settings::c_buttonPosY);
	m_backButton.setUpUIBorder(settings::c_buttonWidth, settings::c_buttonHeight);
	m_backButton.setCollisionBounds(settings::c_buttonWidth, settings::c_buttonHeight);
	m_backButton.setUpText(settings::c_buttonName[1], settings::c_buttonCharSize, TextAlignmentEnum::middleHorizontal, TextAlignmentEnum::middleVertical);

	m_refreshDropDownListButton.setUpAndResizeToSprite(m_window.getSize().x - settings::c_optionPositionXOffset + settings::c_refreshButtonPositionXOffset, settings::c_optionPositionYOffset + settings::c_refreshButtonPositionYOffset, m_textures.m_refreshIcon);

}

void GameSetUpScreen::update(const sf::Vector2f& mousePosition)
{
	m_playerSettingsTable.update(mousePosition);
	m_mapSelectionDropDown.update(mousePosition);
	updateButtons(mousePosition);
}

void GameSetUpScreen::updateButtons(const sf::Vector2f& mousePosition)
{
	if (m_startGameButton.checkIfButtonWasPressed(mousePosition))
	{
		m_pLoadMapFunction();
		Global::g_gameState = GameState::game;
	}

	if (m_backButton.checkIfButtonWasPressed(mousePosition))
	{
		Global::g_gameState = GameState::menu;
	}

	if (m_refreshDropDownListButton.checkIfButtonWasPressed(mousePosition))
	{
		m_mapSelectionDropDown.deleteOptions();

		m_dataHandler.loadCoreMapsData();
		for (std::string mapName : m_dataHandler.getMapNames())
		{
			m_mapSelectionDropDown.addNewDropDownOptions(mapName);
		}
		m_mapSelectionDropDown.setOptionsPositions();
		m_mapSelectionDropDown.resizeSlider();
	}
}

const int& GameSetUpScreen::getPlayerChosenFaction(const int& playerIndex)
{
	return m_playerSettingsTable.getPlayersChosenFaction(playerIndex);
}

const int& GameSetUpScreen::getChosenMapIndex()
{
	return m_mapSelectionDropDown.getSelectedOptionID();
}

const bool GameSetUpScreen::getIfPlayerIsAI(const int& playerIndex)
{
	return m_playerSettingsTable.getIsPlayerAI(playerIndex);
}

const std::string& GameSetUpScreen::getPlayerName(const int& playerIndex)
{
	return m_playerSettingsTable.getPlayerName(playerIndex);
}

void GameSetUpScreen::setConfirmationFunctionPointer(std::function<void()> function)
{
	m_pLoadMapFunction = function;
}

void GameSetUpScreen::updateAvailablePlayers()
{
	m_playerSettingsTable.setNumberOfAvailablePlayers(m_dataHandler.getMapMaxNumberOfPlayers(m_mapSelectionDropDown.getSelectedOptionID()));
}

void GameSetUpScreen::draw()
{
	m_startGameButton.draw();
	m_backButton.draw();
	m_refreshDropDownListButton.draw();
	m_playerSettingsTable.draw();
	m_mapSelectionDropDown.draw();
}
