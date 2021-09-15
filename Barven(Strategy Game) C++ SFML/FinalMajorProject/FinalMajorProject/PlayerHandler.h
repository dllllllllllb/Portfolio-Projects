//Author: Maciej Dowbor
//Last Accessed: 30/08/2021

#ifndef PLAYERHANDLER_H
#define PLAYERHANDLER_H

#include "Player.h"
#include "DataHandler.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "ResourcesBar.h"
#include "TurnHandler.h"

//===========================================================================================
//Description: Handles and stores Players data
//===========================================================================================
class PlayerHandler
{
private:
	sf::RenderWindow& m_window;
	DataHandler* m_pDataHandler;
	ResourcesBar& m_resourcesBar;
	TurnHandler& m_turnHandler;

	std::vector<std::unique_ptr<Player>> m_players;
public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	PlayerHandler(sf::RenderWindow& rWindow, DataHandler* pDataHandler, ResourcesBar& rResourceBar, TurnHandler& rTurnHandler);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~PlayerHandler();

	//===========================================================================================
	//Description: Returns human player based on index passed
	//===========================================================================================
	Player& getPlayer(const int& playerIndex);

	//===========================================================================================
	//Description: Creates a new player based on parameters passed.
	//			   humanPlayer: True == Human player / False == AI player
	//===========================================================================================
	void makeNewPlayer(const int& factionIndex);

	//===========================================================================================
	//Description: Deletes player
	//===========================================================================================
	void deletePlayer(const int& playerVectorIndex);

	//===========================================================================================
	//Description: Updates players
	//===========================================================================================
	void update(const float& deltaTime);

	//===========================================================================================
	//Description: Updates resource bar values to display
	//===========================================================================================
	void updateResourcesBarValues(const int& playerIndex);

	//===========================================================================================
	//Description: Calls draw functions in the player class
	//===========================================================================================
	void draw();

	//===========================================================================================
	//Description: Returns number of players
	//===========================================================================================
	const int& getNumberOfPlayers() const;

	//===========================================================================================
	//Description: Return vector of players
	//===========================================================================================
	std::vector<std::unique_ptr<Player>>& getVectorOfPlayers();


};

#endif // !PLAYERHANDLER_H

