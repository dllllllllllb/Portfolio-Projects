#include "Game.h"

Game::Game(sf::RenderWindow& rWindow, Textures* pTextures, Fonts* pFonts, DataHandler* pDataHandler, GameSetUpScreen* pGameSetUpScreen, sf::Mouse& rMouse) :
	m_window(rWindow),
	m_UIHandler(rWindow, *pTextures, *pFonts, m_confirmationWindow),
	m_playerHandler(rWindow, pDataHandler, m_UIHandler.getResourceBarReference(), m_turnHandler),
	m_combatHandler(rWindow, *pTextures, *pDataHandler, *pFonts),
	m_gameEnd(rWindow, *pTextures, *pFonts),
	m_mapHandler(rWindow, pTextures, pDataHandler, m_UIHandler, pGameSetUpScreen, m_viewManager, m_playerHandler, m_turnHandler, m_combatHandler, m_UIHandler.getMapUIReference(), m_gameEnd),
	m_viewManager(rWindow, rMouse),
	m_cursor(*pTextures, c_tileSize),
	m_confirmationWindow(rWindow, pTextures, pFonts),
	m_mapAI(*pDataHandler, m_playerHandler, m_turnHandler, m_combatHandler, m_mapHandler, m_UIHandler.getTownReference(), m_UIHandler.getSpecialBuildingsInteractionReference()),
	m_mouse(rMouse)
{
	m_cursor.setTileHandlerPointer(m_mapHandler.getTileHandlerPointer());
}

Game::~Game()
{

}

void Game::initialize()
{
	m_UIHandler.initialize();
	m_combatHandler.setUpCombatAreaAndUI();
}

void Game::update(sf::Vector2f& mousePosition, const float& deltaTime)
{
	m_UIHandler.update(mousePosition, deltaTime);

	if (Global::g_UILayer == UILayerEnum::gameEnd)
	{
		m_gameEnd.update(mousePosition);
	}

	updateCombatHandler(mousePosition, deltaTime);

	if (Global::g_updateGame)
	{
		m_viewManager.setGameView();
		m_viewManager.update(deltaTime);
		updateGame(deltaTime);
	}
}
	
void Game::updateGame(const float& deltaTime)
{
	//Game needs its own mouse position to make sure that it can properly interact with the map
	sf::Vector2f mousePositionGame = m_window.mapPixelToCoords(m_mouse.getPosition(m_window));

	if (Global::g_UILayer == UILayerEnum::map)
	{
		m_cursor.update(mousePositionGame);
		m_mapHandler.checkMapInteractions(mousePositionGame);
		m_mapHandler.checkIfKeyWasPressed();
		m_playerHandler.update(deltaTime);
	}
}

void Game::updateUI(sf::Vector2f& mousePosition, const float& deltaTime)
{
	if (Global::g_UILayer != UILayerEnum::combat)
	{
		m_UIHandler.update(mousePosition, deltaTime);
		m_cursor.update(mousePosition);
	}
}

void Game::updateCombatHandler(sf::Vector2f& mousePosition, const float& deltaTime)
{
	if (Global::g_UILayer == UILayerEnum::combat)
	{
		m_combatHandler.update(mousePosition, deltaTime);
	}
}

void Game::draw()
{
	if (Global::g_updateGame)
	{
		m_viewManager.setGameView();
		drawGame();
	}

	m_viewManager.setUIView();

	m_UIHandler.draw();

	if (Global::g_UILayer == UILayerEnum::combat)
	{
		m_combatHandler.draw();
	}
	else if (Global::g_UILayer == UILayerEnum::gameEnd)
	{
		m_viewManager.setGameView();
		drawGame();

		m_viewManager.setUIView();
		m_gameEnd.draw();
	}
}

void Game::drawGame()
{
	m_mapHandler.draw();
	m_playerHandler.draw();
	m_window.draw(m_cursor);
}