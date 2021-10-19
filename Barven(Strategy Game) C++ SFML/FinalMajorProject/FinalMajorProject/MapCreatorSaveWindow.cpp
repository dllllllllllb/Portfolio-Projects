#include "MapCreatorSaveWindow.h"

MapCreatorSaveWindow::MapCreatorSaveWindow(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts, Audio& rAudio) :
	m_window(rWindow),
	m_background(rWindow, rTextures),
	m_mapNameInputBox(rWindow, rTextures, rFonts, rAudio, true),
	m_numOfPlayersInputBox(rWindow, rTextures, rFonts, rAudio, true),
	m_acceptButton(rTextures, rAudio, true),
	m_declineButton(rTextures, rAudio, false)
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

void MapCreatorSaveWindow::update(const sf::Vector2f& mousePosition)
{
	if (Global::g_isLMBPressed)
	{
		resetInputButtonFocus();
	}

	if (Global::g_isLMBPressed && m_mapNameInputBox.getIsButtonPressed())
	{
		m_mapNameInputBox.setButtonPressed(false);
	}


	if (m_mapNameInputBox.checkIfButtonWasPressed(mousePosition))
	{
		m_mapNameInputBox.setButtonPressed(true);
	}

	if (m_numOfPlayersInputBox.checkIfButtonWasPressed(mousePosition))
	{
		m_numOfPlayersInputBox.setButtonPressed(true);
	}

	if (m_acceptButton.checkIfButtonWasPressed(mousePosition))
	{
		m_saveMapFunction();
	}

	if (m_declineButton.checkIfButtonWasPressed(mousePosition))
	{
		m_exitSaveWindowFunction();
	}

	m_mapNameInputBox.update();
	m_numOfPlayersInputBox.update();	
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
