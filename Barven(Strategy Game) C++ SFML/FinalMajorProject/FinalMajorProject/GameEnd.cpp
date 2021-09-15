#include "GameEnd.h"

namespace settings = GameEndSettings;

GameEnd::GameEnd(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts) :
	m_gameInformation(rWindow, &rTextures, &rFonts),
	m_backToMenuButton(rWindow, &rTextures, &rFonts)
{
	//Set up textbox
	m_gameInformation.setPosition(rWindow.getView().getCenter());
	m_gameInformation.setUpUIBorder(settings::c_textBoxWidth, settings::c_textBoxWidth);

	m_backToMenuButton.setPosition(settings::c_menuButtonPositionX, settings::c_menuButtonPositionY);
	m_backToMenuButton.setUpUIBorder(settings::c_menuButtonWidth, settings::c_menuButtonHeight);
	m_backToMenuButton.setCollisionBounds(settings::c_menuButtonWidth, settings::c_menuButtonHeight);
	m_backToMenuButton.setUpText("Menu", settings::c_menuButtonCharSize, TextAlignmentEnum::middleHorizontal, TextAlignmentEnum::middleVertical);
}

GameEnd::~GameEnd()
{

}

void GameEnd::setEndGameInformation(Player& rPlayer, const bool didPlayerWin, TurnHandler& rTurnHandler)
{
	rPlayer.updateResourcesPerTurn();
	std::string textToSet = "";

	if (didPlayerWin)
	{
		m_gameInformation.setUpTitleText("Victory", settings::c_titleCharSize);
	}
	else
	{
		m_gameInformation.setUpTitleText("Defeat", settings::c_titleCharSize);
	}

	//TurnsTaken
	textToSet += "Turns played: " + std::to_string(rTurnHandler.getCurrentTurn());

	//Towns
	textToSet += "\nTotal Owned Towns: " + std::to_string(rPlayer.getVectorOfOwnedTownsIndexes().size());

	//Gold
	textToSet += "\nGold: " + std::to_string(rPlayer.getResources().getResource(ResourcesEnum::gold));

	//Wood
	textToSet += "\nWood: " + std::to_string(rPlayer.getResources().getResource(ResourcesEnum::wood));

	//Stone
	textToSet += "\nStone: " + std::to_string(rPlayer.getResources().getResource(ResourcesEnum::stone));

	//Gold mines
	textToSet += "\nGold Mines: " + std::to_string(rPlayer.getNumberOfMines(ResourcesEnum::gold));

	//Lumber mills
	textToSet += "\nLumber Mills : " + std::to_string(rPlayer.getNumberOfMines(ResourcesEnum::wood));

	//Stone quarry
	textToSet += "\nStone Quarries: " + std::to_string(rPlayer.getNumberOfMines(ResourcesEnum::stone));

	//Gold per turn
	textToSet += "\nGold Per Turn: " + std::to_string(rPlayer.getNumberOfResourcesPerTurn(ResourcesEnum::gold));

	//Wood per turn
	textToSet += "\nWood Per Turn: " + std::to_string(rPlayer.getNumberOfResourcesPerTurn(ResourcesEnum::wood));

	//Stone per turn
	textToSet += "\nStone Per Turn: " + std::to_string(rPlayer.getNumberOfResourcesPerTurn(ResourcesEnum::stone));

	m_gameInformation.setUpText(textToSet, settings::c_textCharSize, TextAlignmentEnum::middleHorizontal, TextAlignmentEnum::top);
	m_gameInformation.setTitleOffset(m_gameInformation.getTitleHeight());
	m_gameInformation.resizeBorderToFitText();

	int textBoxHeight = m_gameInformation.UIElement::getGlobalBounds().height;

	m_gameInformation.setPosition(m_gameInformation.UIElement::getPosition().x, m_gameInformation.UIElement::getPosition().y - textBoxHeight * 0.5f);
	m_gameInformation.resizeBorderToFitText();
	m_gameInformation.setDefaultTitlePosition();

}

void GameEnd::update(const sf::Vector2f& mousePosition)
{
	if (m_backToMenuButton.checkMouseCollision(mousePosition) && Global::g_isLMBPressed)
	{
		Global::g_gameState = GameState::menu;
		Global::objectPressed();
	}
}

void GameEnd::draw()
{
	m_gameInformation.draw();
	m_backToMenuButton.draw();
}
