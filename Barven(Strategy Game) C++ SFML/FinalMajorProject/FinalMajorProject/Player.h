//Author: Maciej Dowbor
//Last Accessed: 01/10/2021

#ifndef PLAYER_H
#define PLAYER_H

#include <functional>

#include "Hero.h"
#include "Resources.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "TownData.h"
#include "ResourcesPerTurnSettings.h"
#include "DataHandler.h"


//===========================================================================================
//Description: Data container for everything owned by the player. 
//			   Holds Heroes data, resources, owned towns and mines, faction and player index
//===========================================================================================
class Player
{
private:
	sf::RenderWindow& m_window;

	//Basic data
	int m_factionIndex;
	int m_playerIndex;
	int m_selectedHeroIndex;
	bool m_isPlayerAI;
	DataHandler* m_pDataHandler;
	std::function<void()> m_functionToCallWhenHeroArrivesAtDestination;
	std::function<void()> m_updateHeroesMapUI;
	std::vector<std::unique_ptr<Hero>> m_heroes;

	//Owned Towns
	std::vector<int> m_ownedTownIndexes;
	std::vector<std::unique_ptr<TownData>>* m_pTownDataVector;

	//Resources
	Resources m_resources;
	int m_numOfOwnedGoldMines;
	int m_numOfOwnedWoodMines;
	int m_numOfOwnedStoneMines;

	//Resources per turn
	int m_goldPerTurn;
	int m_woodPerTurn;
	int m_stonePerTurn;


public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	Player(sf::RenderWindow& rWindow);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~Player();

	//===========================================================================================
	//Description: Returns resources class
	//===========================================================================================
	Resources& getResources();

	//===========================================================================================
	//Description: Returns a hero class based on index passed
	//===========================================================================================
	Hero& getHero(const int& heroIndex);

	//===========================================================================================
	//Description: Returns currently selected hero
	//===========================================================================================
	Hero& getSelectedHero();

	//===========================================================================================
	//Description: Sets faction index
	//===========================================================================================
	void setFactionIndex(const int& factionIndex);

	//===========================================================================================
	//Description: Returns faction index
	//===========================================================================================
	const int& getFactionIndex() const;

	//===========================================================================================
	//Description: Sets player index
	//===========================================================================================
	void setPlayerIndex(const int& playerIndex);

	//===========================================================================================
	//Description: Returns player index
	//===========================================================================================
	const int& getPlayerIndex() const;

	//===========================================================================================
	//Description: Sets index of the hero that is currently selected
	//===========================================================================================
	void setSelectedHeroIndex(const int& heroIndex);

	//===========================================================================================
	//Description: Returns index of selected hero
	//===========================================================================================
	const int& getSelectedHeroIndex() const;

	//===========================================================================================
	//Description: Adds town index to owned towns vector
	//===========================================================================================
	void addOwnedTown(const int& townIndex);

	//===========================================================================================
	//Description: Removes town index from owned towns vector
	//===========================================================================================
	void removeOwnedTown(const int& townIndex);

	//===========================================================================================
	//Description: Returns vector of owned towns indexes
	//===========================================================================================
	std::vector<int>& getVectorOfOwnedTownsIndexes();

	//===========================================================================================
	//Description: Returns vector of heroes owned by this player
	//===========================================================================================
	std::vector<std::unique_ptr<Hero>>& getVectorOfOwnedHeroes();

	//===========================================================================================
	//Description: Sets town data vector pointer (takes town data vector from map handler)
	//===========================================================================================
	void setTownDataVectorPointer(std::vector<std::unique_ptr<TownData>>& rTownDataVector);

	//===========================================================================================
	//Description: Updates resources per turn
	//===========================================================================================
	void updateResourcesPerTurn();

	//===========================================================================================
	//Description: Adds recources gained per turn to players resources
	//===========================================================================================
	void addResourcesGainedPerTurnToPlayersResources();

	//===========================================================================================
	//Description: Increments owned mines based on mine type passed
	//===========================================================================================
	void incrementOwnedMines(const ResourcesEnum& mineType);

	//===========================================================================================
	//Description: Decrements owned mines based on mine type passed
	//===========================================================================================
	void decrementOwnedMines(const ResourcesEnum& mineType);

	//===========================================================================================
	//Description: Returns number of mines owned based on mine type passed
	//===========================================================================================
	const int& getNumberOfMines(const ResourcesEnum& mineType) const;

	//===========================================================================================
	//Description: Returns number of resources player gains per turn based on resource type
	//===========================================================================================
	const int& getNumberOfResourcesPerTurn(const ResourcesEnum& resourceType) const;

	//===========================================================================================
	//Description: Sets if player is AI
	//===========================================================================================
	void setIsPlayerAI(const bool state);

	//===========================================================================================
	//Description: Returns if player is AI
	//===========================================================================================
	const bool getIsPlayerAI() const;

	//===========================================================================================
	//Description: Creates a new hero
	//===========================================================================================
	void makeNewHero(const sf::Vector2f& startPosition, const int& occupiedTileIndex, const bool giveHeroBasicUnit);

	//===========================================================================================
	//Description: Sets a pointer to data handler
	//===========================================================================================
	void setDataHandlerPointer(DataHandler* pDataHandler);

	//===========================================================================================
	//Description: Sets a function to call when a hero arrives at their destination in map handler
	//===========================================================================================
	void setFunctionToCallWhenHeroArrivesAtDestination(std::function<void()> function);

	//===========================================================================================
	//Description: Sets a function to call when you want to update map ui related to heroes,
	//			   called when a new hero is made
	//===========================================================================================
	void setFunctionToUpdateHeroesMapUI(std::function<void()> function);

	//===========================================================================================
	//Description: Returns if player has at least one hero
	//===========================================================================================
	const bool getDoesPlayerHaveHeroes();

	//===========================================================================================
	//Description: Updates heroes
	//===========================================================================================
	void updateHeroes(const float& deltaTime);

	//===========================================================================================
	//Description: Draw heroes
	//===========================================================================================
	void drawHeros();


};

#endif // !PLAYER_H

