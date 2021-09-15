#include "PlayerHandler.h"
PlayerHandler::PlayerHandler(sf::RenderWindow& rWindow, DataHandler* pDataHandler, ResourcesBar& rResourceBar, TurnHandler& rTurnHandler) :
    m_window(rWindow),
    m_pDataHandler(pDataHandler),
    m_resourcesBar(rResourceBar),
    m_turnHandler(rTurnHandler)

{
}

PlayerHandler::~PlayerHandler()
{
}

Player& PlayerHandler::getPlayer(const int& playerIndex)
{
    return *m_players[playerIndex];
}

void PlayerHandler::makeNewPlayer(const int& factionIndex)
{
    m_players.push_back(std::unique_ptr<Player>(new Player(m_window)));
    m_players[m_players.size() - 1]->setFactionIndex(factionIndex);
    m_turnHandler.incrementNumberOfPlayers();

}

void PlayerHandler::deletePlayer(const int& playerVectorIndex)
{
    m_players.erase(m_players.begin() + playerVectorIndex);
}

void PlayerHandler::update(const float& deltaTime)
{
    for (auto& player : m_players)
    {
        player->updateHeroes(deltaTime);
    }
}

void PlayerHandler::updateResourcesBarValues(const int& playerIndex)
{
    Resources& resources = m_players[playerIndex]->getResources();

    for (int i = 0; i < ResourceBarSettings::c_numOfResources; i++)
    {
        m_resourcesBar.setResourceValue(static_cast<ResourcesEnum>(i), resources.getResource(static_cast<ResourcesEnum>(i)));
    }
}

void PlayerHandler::draw()
{
    for (auto& player : m_players)
    {
        player->drawHeros();
    }

}

const int& PlayerHandler::getNumberOfPlayers() const
{
    return m_players.size();
}

std::vector<std::unique_ptr<Player>>& PlayerHandler::getVectorOfPlayers()
{
    return m_players;
}
