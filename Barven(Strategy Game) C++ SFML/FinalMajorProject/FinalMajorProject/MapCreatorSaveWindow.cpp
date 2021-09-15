#include "MapCreatorSaveWindow.h"

MapCreatorSaveWindow::MapCreatorSaveWindow(sf::RenderWindow& rWindow, Textures* pTextures, Fonts* pFonts) :
	m_window(rWindow),
	m_background(rWindow, pTextures),
	m_mapNameInputBox(rWindow, pTextures, pFonts, true),
	m_numOfPlayersInputBox(rWindow, pTextures, pFonts, true),
	m_acceptButton(pTextures, true),
	m_declineButton(pTextures, false)
{
}

MapCreatorSaveWindow::~MapCreatorSaveWindow()
{
}

void MapCreatorSaveWindow::initialize()
{
	//Background
	m_background.setPosition(m_window.getView().getCenter());
	m_background.setUpUIBorder(MapCreatorSaveWindowSettings::c_backgroundWidth, MapCreatorSaveWindowSettings::c_backgroundHeight);

	//Map name input box
	m_mapNameInputBox.setPosition(m_background.getPosition().x, m_background.getPosition().y + MapCreatorSaveWindowSettings::c_mapNameInputButtonOffset);
	m_mapNameInputBox.setUpUIBorder(MapCreatorSaveWindowSettings::c_inputButtonWidth, MapCreatorSaveWindowSettings::c_inputButtonHeight);
	m_mapNameInputBox.setCollisionBounds(MapCreatorSaveWindowSettings::c_inputButtonWidth, MapCreatorSaveWindowSettings::c_inputButtonHeight);
	m_mapNameInputBox.setUpText(MapCreatorSaveWindowSettings::c_inputButtonContent, MapCreatorSaveWindowSettings::c_inputButtonContentCharSize, TextAlignmentEnum::middleHorizontal, TextAlignmentEnum::middleVertical);
	m_mapNameInputBox.setUpTitleText(MapCreatorSaveWindowSettings::c_mapNameInputBoxTitle, MapCreatorSaveWindowSettings::c_inputButtonTitleCharSize);
	m_mapNameInputBox.setInputTextPosition();

	//Number of players input box
	m_numOfPlayersInputBox.setPosition(m_background.getPosition().x, m_background.getPosition().y + MapCreatorSaveWindowSettings::c_numOfPlayersInputButtonOffset);
	m_numOfPlayersInputBox.setUpUIBorder(MapCreatorSaveWindowSettings::c_inputButtonWidth, MapCreatorSaveWindowSettings::c_inputButtonHeight);
	m_numOfPlayersInputBox.setCollisionBounds(MapCreatorSaveWindowSettings::c_inputButtonWidth, MapCreatorSaveWindowSettings::c_inputButtonHeight);
	m_numOfPlayersInputBox.setUpText(MapCreatorSaveWindowSettings::c_inputButtonContent, MapCreatorSaveWindowSettings::c_inputButtonContentCharSize, TextAlignmentEnum::middleHorizontal, TextAlignmentEnum::middleVertical);
	m_numOfPlayersInputBox.setUpTitleText(MapCreatorSaveWindowSettings::c_numOfPlayersInputBoxTitle, MapCreatorSaveWindowSettings::c_inputButtonTitleCharSize);
	m_numOfPlayersInputBox.setInputTextPosition();

	//Basic buttons
	m_acceptButton.sf::Sprite::setPosition(m_background.getPosition().x - MapCreatorSaveWindowSettings::c_basicButtonXOffset, m_background.getPosition().y + MapCreatorSaveWindowSettings::c_basicButtonYOffset);
	m_acceptButton.CollidableObject::setPosition(m_background.getPosition().x - MapCreatorSaveWindowSettings::c_basicButtonXOffset, m_background.getPosition().y + MapCreatorSaveWindowSettings::c_basicButtonYOffset);
	
	m_declineButton.sf::Sprite::setPosition(m_background.getPosition().x + MapCreatorSaveWindowSettings::c_basicButtonXOffset, m_background.getPosition().y + MapCreatorSaveWindowSettings::c_basicButtonYOffset);
	m_declineButton.CollidableObject::setPosition(m_background.getPosition().x + MapCreatorSaveWindowSettings::c_basicButtonXOffset, m_background.getPosition().y + MapCreatorSaveWindowSettings::c_basicButtonYOffset);
	
}

void MapCreatorSaveWindow::setSaveMapFunction(std::function<void()> function)
{
	m_saveMapFunction = function;
}

void MapCreatorSaveWindow::setExitSaveWindowFunction(std::function<void()> function)
{
	m_exitSaveWindowFunction = function;
}

void MapCreatorSaveWindow::resetInputButtonFocus()
{
	m_mapNameInputBox.setButtonPressed(false);
	m_numOfPlayersInputBox.setButtonPressed(false);
}

const bool MapCreatorSaveWindow::update(const bool isLMBPressed, const sf::Vector2f& mousePosition)
{
	bool toggleButtonPress = false;

	if (isLMBPressed)
	{
		resetInputButtonFocus();
	}

	if (isLMBPressed && m_mapNameInputBox.getIsButtonPressed())
	{
		m_mapNameInputBox.setButtonPressed(false);
	}


	if (m_mapNameInputBox.checkMouseCollision(mousePosition) && isLMBPressed)
	{
		m_mapNameInputBox.setButtonPressed(true);
		toggleButtonPress = true;
	}

	if (m_numOfPlayersInputBox.checkMouseCollision(mousePosition) && isLMBPressed)
	{
		m_numOfPlayersInputBox.setButtonPressed(true);
		toggleButtonPress = true;
	}

	if (m_acceptButton.collisionCheck(mousePosition) && isLMBPressed)
	{
		m_saveMapFunction();
		toggleButtonPress = true;
	}

	if (m_declineButton.collisionCheck(mousePosition) && isLMBPressed)
	{
		m_exitSaveWindowFunction();
		toggleButtonPress = true;
	}

	m_mapNameInputBox.update();
	m_numOfPlayersInputBox.update();

	return toggleButtonPress;
	
}

const std::string& MapCreatorSaveWindow::getMapName() const
{
	return m_mapNameInputBox.getPlayerInput();
}

const int MapCreatorSaveWindow::getNumberOfPlayers() const
{
	return std::stoi(m_numOfPlayersInputBox.getPlayerInput());
}

void MapCreatorSaveWindow::draw()
{
	m_background.drawUIBorderAndBackground();
	m_mapNameInputBox.draw();
	m_numOfPlayersInputBox.draw();
	m_window.draw(m_acceptButton);
	m_window.draw(m_declineButton);
}
