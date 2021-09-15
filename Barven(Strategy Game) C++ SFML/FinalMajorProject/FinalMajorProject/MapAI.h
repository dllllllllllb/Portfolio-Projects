//Author: Maciej Dowbor
//Last Accessed: 10/09/2021

#ifndef MAPAI_H
#define MAPAI_H

#include "MapHandler.h" //Holds most header files
#include "MapAIPlayerData.h"
#include "MapAISettings.h"


//===========================================================================================
//Description: Determines AI's priority and executes coresponding behaviour on the map
//===========================================================================================
class MapAI
{
private:
	DataHandler& m_dataHandler;
	PlayerHandler& m_playerHandler;
	TurnHandler& m_turnHandler;
	CombatHandler& m_combatHandler;
	MapHandler& m_mapHandler;
	Town& m_town;
	SpecialBuildingInteractions& m_specialBuildingsInteractions;
	TileHandler* m_pTileHandler;

	int m_playerIndex;
	bool m_isCombatInitiated;
	bool m_wasPrioSetThisTurn;

	//Map objects vector pointers
	std::vector<std::unique_ptr<TownMapObject>>* m_pTownMapObjects;
	std::vector<std::unique_ptr<TownData>>* m_pTownData;
	std::vector<std::unique_ptr<UnitMapObject>>* m_pUnitMapObjects;
	std::vector<std::unique_ptr<ResourceMineMapObject>>* m_pResourceMinesMapObjects;
	std::vector<std::unique_ptr<ResourceMapObject>>* m_pResourceMapObjects;
	std::vector<std::unique_ptr<SpecialBuildingMapObject>>* m_pSpecialBuildingsMapObjects;

	std::vector<std::unique_ptr<MapAIPlayerData>> m_AIPlayerData;
public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	MapAI(DataHandler& rDataHandler, PlayerHandler& rPlayerHandler, TurnHandler& rTurnHandler, CombatHandler& rCombatHandler, MapHandler& rMapHandler, Town& rTown, SpecialBuildingInteractions& rSpecialBuildingInteractions);
	
	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~MapAI();

	//===========================================================================================
	//Description: Sets pointers to map objects in the map handler
	//===========================================================================================
	void setUpMapObjectsPointers();

	//===========================================================================================
	//Description: Creates new player AI data
	//===========================================================================================
	void makeNewAIPlayerData(const int& playerIndex);

	//===========================================================================================
	//Description: Executes AIs behaviour
	//===========================================================================================
	void takeTurn();

	//===========================================================================================
	//Description: Checks if AI has finished it's turn by checking if there are heroes left with
	//			   movement points
	//===========================================================================================
	const bool didAIFinishItsTurn();

	//===========================================================================================
	//Description: Calls appropriate functions to determine AIs priority
	//===========================================================================================
	void determinePriorities(MapAIPlayerData& playerAIData);

	//===========================================================================================
	//Description: Check critical conditions that outweight other priorities
	//===========================================================================================
	std::pair<MapAIPriorityEnum, int> determineOverallPlayerPriority(MapAIPlayerData& AIPlayerData, Player& player);
	
	//===========================================================================================
	//Description: Determines individual hero priority
	//===========================================================================================
	void determineIndividualHeroPriority(Hero& playerHero, const int& heroIndex, Player& player, MapAIPlayerData& AIPlayerData);

	//===========================================================================================
	//Description: Checks if hero is in one of their owned town and checks if there are
	//			   units available to recruit
	//===========================================================================================
	void checkIfHeroIsInTownToRecruitUnits(const int& occupiedTileIndex, Player& player, const int& heroIndex, MapAIPlayerData& AIPlayerData);

	//===========================================================================================
	//Description: Loops through enemy heroes, checks if they are close and checks if they have
	//			   weaker army
	//===========================================================================================
	const bool checkIfEnemyHeroWithWeakerArmyIsClose(Hero& playerHero, const int& playerHeroIndex, MapAIPlayerData& AIPlayerData);

	//===========================================================================================
	//Description: Loops through map objects, checks which one is the closest and if the hero
	//			   has stronger army than the unit protecting that object
	//===========================================================================================
	const bool findClosestMapObjectOfInterest(Hero& playerHero, const int& heroIndex, MapAIPlayerData& AIPlayerData);

	//===========================================================================================
	//Description: Based on heros priority, it will set the rest of needed variable and move the
	//			   hero to its priority. If the hero arrives at their destination, heroInteraction
	//			   is called. If hero has movement points left, it resets heros priority and calls
	//			   this function again.
	//===========================================================================================
	void makeAMove(const int& heroIndex, Hero& hero, MapAIPlayerData& playerAIData);

	//===========================================================================================
	//Description: Moves hero to its priority and check if it arrived at its destination
	//===========================================================================================
	bool moveHeroToPriority(const int& heroIndex, Hero& hero, MapAIPlayerData& playerAIData);

	//===========================================================================================
	//Description: Calls appropriate functions based on heros priority to interact with the map
	//===========================================================================================
	void heroMapInteraction(const int& heroIndex, Hero& hero, MapAIPlayerData& playerAIData);

	//===========================================================================================
	//Description: Check for building availability and purchases town buildings
	//===========================================================================================
	void upgradeTownBuildings();

	//===========================================================================================
	//Description: Checks for the closes mine that isn't protected by a unit that is stronger than
	//			   heros army
	//===========================================================================================
	void findClosestMine(const int& heroIndex, const ResourcesEnum& mineType, Hero& hero, MapAIPlayerData& AIPlayerData);

	//===========================================================================================
	//Description: Finds closes owned town that has units available to recruits
	//===========================================================================================
	void findClosestTownToRecruitUnits(const int& heroIndex, Hero& hero, MapAIPlayerData& AIPlayerData);

	//===========================================================================================
	//Description: Recruits units at passed town index
	//===========================================================================================
	void recruitUnitsAtTown(const int& townIndex);

	//===========================================================================================
	//Description: Returns distance in tiles between two positions
	//===========================================================================================
	const int getDistanceInTilesBetweenTwoPositions(const sf::Vector2f& posA, const sf::Vector2f& posB);

	//===========================================================================================
	//Description: Compares hero strength and returns if the AI hero has stronger army
	//===========================================================================================
	const bool checkIfOpponentHasStrongerArmy(Hero& playerHero, Hero& enemyHero);

	//===========================================================================================
	//Description: Calculates and returns army strength
	//===========================================================================================
	const int getArmyStrength(std::vector<std::shared_ptr<Unit>>& vectorOfUnits);

	//===========================================================================================
	//Description: Compares hero strength to map unit strenght and returns if the AI has stronger
	//			   army
	//===========================================================================================
	const bool checkIfOpponentHasStrongerArmy(Hero& playerHero, UnitMapObject& enemyUnits);

	//===========================================================================================
	//Description: Returns path distance in tiles between two tiles
	//===========================================================================================
	const int getPathDistanceInTiles(const int& startTileIndex, const int& endTileIndex);

	//===========================================================================================
	//Description: Loops through neighbouring tiles and checks if they have a unit protecting it
	//===========================================================================================
	const int checkIfNeighbouringTilesHaveAUnitProtectingAndReturnTheirArmyStrength(const int& tileIndex);

	//===========================================================================================
	//Description: Returns number of units that can be purchased with AIs current gold
	//===========================================================================================
	const int checkHowManyUnitsCanBePurchased(const int& gold, const int& factionIndex, const int& unitIndex);

	//===========================================================================================
	//Description: Adds a new unit to an army
	//===========================================================================================
	const bool addUnitToArmy(const int& numberOfUnits, UnitData& unitToAdd, std::vector<std::shared_ptr<Unit>>& army);

	//===========================================================================================
	//Description: Transfers units between two armies
	//===========================================================================================
	void transferUnitsBetweenTwoArmies(std::vector<std::shared_ptr<Unit>>& armyToTransferTo, std::vector<std::shared_ptr<Unit>>& armyToTransferFrom);

	//===========================================================================================
	//Description: Transfers units from town to hero
	//===========================================================================================
	void transferUnitsFromTownToHero(Hero& hero, TownData& townData);

	//===========================================================================================
	//Description: Moves hero to an appropriate tile
	//===========================================================================================
	void moveHeroToAppropriateTile(const int& startTile, const int& destinationTile, Hero& hero);

	//===========================================================================================
	//Description: Deletes AI data if AI loses
	//===========================================================================================
	void deleteAIPlayerData(int playerIndex);

	//===========================================================================================
	//Description: Heros interaction with arena map object
	//===========================================================================================
	void arenaInteraction(Hero& hero, const int& arenaIndex);

	//===========================================================================================
	//Description: Checks if resources are on the ground close by
	//===========================================================================================
	const bool areResourcesNearBy( Hero& hero, const int& heroIndex, MapAIPlayerData& AIPlayerData);

	//===========================================================================================
	//Description: Updates current player index
	//===========================================================================================
	void updatePlayerIndex();

	//===========================================================================================
	//Description: Returns total army strength of a player
	//===========================================================================================
	const int getPlayersTotalArmyStrength(const int& playerIndex);
};

#endif // !MAPAI_H