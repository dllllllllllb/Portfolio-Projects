//Author: Maciej Dowbor
//Last Accessed: 02/09/2021

#ifndef MAPHANDLER_H
#define MAPHANDLES_H

#include <cmath>

#include "GameSetUpScreen.h"
#include "TileHandler.h"
#include "DataHandler.h"
#include "TownMapObject.h"
#include "UnitMapObject.h"
#include "ResourceMapObject.h"
#include "ResourceMineMapObject.h"
#include "SpecialBuildingMapObject.h"
#include "LandscapeMapObject.h"
#include "MapQuadrantData.h"
#include "MapHandlerSettings.h"
#include "ViewManager.h"
#include "TurnHandler.h"
#include "PlayerHandler.h"
#include "UIHandler.h"
#include "CombatHandler.h"
#include "MapUI.h"
#include "HeroMovementFeedback.h"
#include "GameEnd.h"

//===========================================================================================
//Description: Handles map interactions, map data storage and drawing sprites
//===========================================================================================
class MapHandler
{
private:
	sf::RenderWindow& m_window;
	DataHandler* m_pDataHandler;
	UIHandler& m_UIHandler;
	TileHandler m_tileHandler;
	GameSetUpScreen* m_pGameSetUpScreen;
	Textures* m_pTextures;
	ViewManager& m_viewManager;
	PlayerHandler& m_playerHandler;
	TurnHandler& m_turnHandler;
	CombatHandler& m_combatHandler;
	MapUI& m_mapUI;
	GameEnd& m_gameEnd;
	HeroMovementFeedback m_heroMovementFeedback;

	//Map data
	int m_mapWidth;
	int m_mapHeight;
	int m_numOfPlayers;
	int m_tileSize;
	bool m_isMapLoaded;

	//Hero Movement
	bool m_isPathValid;
	int m_tileIndexToMoveTo;
	int m_numOfMovementPointsTheMoveWillConsume;
	int m_numOfPositionsWithinRange;


	//Map AI
	std::function<void(int)> m_makeNewAIPlayerDataFunction;
	std::function<void()> m_AITakeTurnFunction;
	std::function<void(int)> m_deletePlayerAIDataFunction;

	//==========================================================================================
	//Map Objects
	//==========================================================================================
	// 	Objects are stored as unique pointers in vectors because vectors create copies
	//	of themselves when moving in memory to find enough continuous space for themselves; this 
	//	makes sure that only the address of the object is moved rather than the entire object. 
	//	Unique pointers also manage deallocating memory when the data referenced by the pointer 
	//	is out of scope.
	//==========================================================================================

	//Towns
	std::vector<std::unique_ptr<TownMapObject>> m_townMapObjects;
	std::vector<std::unique_ptr<TownData>> m_townData;
	int m_numOfTownMapObjects;

	//Units
	std::vector<std::unique_ptr<UnitMapObject>> m_unitMapObjects;
	int m_numOfUnitMapObjects;

	//Resource Mines
	std::vector<std::unique_ptr<ResourceMineMapObject>> m_resourceMinesMapObjects;
	int m_numOfResourceMinesMapObjects;

	//Resources
	std::vector<std::unique_ptr<ResourceMapObject>> m_resourceMapObjects;
	int m_numOfResourceMapObjects;

	//Special Buildings
	std::vector<std::unique_ptr<SpecialBuildingMapObject>> m_specialBuildingsMapObjects;
	int m_numOfSpecialBuildingMapObjects;

	//Lanmdscapes
	std::vector<std::unique_ptr<LandscapeMapObject>> m_landscapeMapObjects;
	int m_numOfLandscapeMapObjects;

	//Map quadrants
	std::vector<std::unique_ptr<MapQuadrantData>> m_mapQuadrants;
	int m_horizontalQuadrantsToDisplay;
	int m_verticalQuadrantsToDisplay;
	int m_maxHorizontalQuadrants;
	int m_maxVerticalQuadrants;
	int m_lastValidStartQuadrant;

public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	MapHandler(sf::RenderWindow& rWindow, Textures* pTextures, DataHandler* pDataHandler, UIHandler& rUIHandler, GameSetUpScreen* pGameSetUpScreen, ViewManager& rViewManager, PlayerHandler& rPlayerHandler, TurnHandler& rTurnHandler, CombatHandler& rCombatHandler, MapUI& rMapUI, GameEnd& rGameEnd);
	
	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~MapHandler();

	//===========================================================================================
	//Description: Loads the map from JSON file to appropriate data types
	//===========================================================================================
	void loadTheMap();

	//===========================================================================================
	//Description: Splits the map into sections and stores data from each section in seperate 
	//			   containers to improve performance by not drawing objects that are not visible
	//			   on players screen
	//===========================================================================================
	void setUpMapQuadrants(const int& screenWidth, const int& screenHeight);

	//===========================================================================================
	//Description: Sets function to call when making a new AI player to make a new AI player data
	//			   (used in MapAI)
	//===========================================================================================
	void setMakeNewAIPlayerDataFunction(std::function<void(int)> function);

	//===========================================================================================
	//Description: Sets function to call when it is AIs turn (used in MapAI)
	//===========================================================================================
	void setAITakeTurnFunction(std::function<void()> function);

	//===========================================================================================
	//Description: Checks if the movement is valid and what interaction will happen based on tiles
	//			   properties
	//===========================================================================================
	void checkMapInteractions(sf::Vector2f& mousePosition);

	//===========================================================================================
	//Description: Checks if a keyboard key was pressed and calls appropriate instructions
	//===========================================================================================
	void checkIfKeyWasPressed();

	//===========================================================================================
	//Description: Updates map object feedback and enables it
	//===========================================================================================
	void updateMapObjInfoFeedback(const sf::Vector2f& mousePosition, const int& tileIndex);

	//===========================================================================================
	//Description: Sets appropriate variables for path finding and attempts to find a valid path.
	//			   If a valid path is found, the path is set to the currently selected hero and 
	//			   the hero begins to move along the path
	//===========================================================================================
	void movePlayer(const int& tileIndex);

	//===========================================================================================
	//Description: Sets a path between selected hero and the tile player clicked on
	//===========================================================================================
	void setOutAPath(const int& tileIndex);

	//===========================================================================================
	//Description: Calls appropriate functions based on which object current hero interacted with
	//===========================================================================================
	void objectInteraction();

	//===========================================================================================
	//Description: Increments turn changing which players turn it is
	//===========================================================================================
	void nextTurn();

	//===========================================================================================
	//Description: Updates entire map UI
	//===========================================================================================
	void updateEntireMapUI();

	//===========================================================================================
	//Description: Updates players owned towns to the map UI
	//===========================================================================================
	void updateTownsMapUI();

	//===========================================================================================
	//Description: Updates players owned heroes to the map UI
	//===========================================================================================
	void updateHeroesMapUI();

	//===========================================================================================
	//Description: Updates current turn information
	//===========================================================================================
	void updateCurrentTurnMapUI();

	//===========================================================================================
	//Description: Updates players resources per turn gain
	//===========================================================================================
	void updateResourcesPerTurnMapUI();

	//===========================================================================================
	//Description: Player enters town without the need to have a hero in it
	//===========================================================================================
	void enterTown(const int& townIndex);

	//===========================================================================================
	//Description: Focuses game view on the hero and opens up hero panel
	//===========================================================================================
	void selectHero(const int& heroIndex);

	//===========================================================================================
	//Description: Checks if player clicked on a hero
	//===========================================================================================
	const bool checkIfAHeroWasPressed(const int& tilePressed);

	//===========================================================================================
	//Description: Returns a pointer to the tile handler
	//===========================================================================================
	TileHandler* getTileHandlerPointer();

	//===========================================================================================
	//Description: Deletes appropriate map object from map section vector
	//===========================================================================================
	void deleteMapObjectFromMapSection(const sf::Vector2f& objectPosition);

	//===========================================================================================
	//Description: Adds town index to current players owned towns 
	//===========================================================================================
	void addNewTownToCurrentPlayer(const int& townIndex);

	//===========================================================================================
	//Description: Removes town index from the owner of this town
	//===========================================================================================
	void removeTownFromCurrentOwner(const int& townIndex);

	//===========================================================================================
	//Description: Checks if player has no heroes and towns (checks for lose condition)
	//===========================================================================================
	void checkIfPlayerHasNoHeroesAndTownsLeft(const int& playerIndex);

	//===========================================================================================
	//Description: Deletes hero from player
	//===========================================================================================
	void deleteHero(const int playerIndex, const int heroIndex);

	//===========================================================================================
	//Description: Deletes player
	//===========================================================================================
	void deletePlayer(const int playerIndex);

	//===========================================================================================
	//Description: Function to call after a battle is won
	//===========================================================================================
	void functionToCallAfterBattleConcluded(const CombatTypeEnum playerVsPlayerCombat, const bool didAttackerWin);

	//===========================================================================================
	//Description: Checks if determined path is within heros movement range
	//===========================================================================================
	const bool checkIfPathIsWithinMovementRange();

	//===========================================================================================
	//Description: Returns the cost of movement between two points
	//===========================================================================================
	const int calculateHowManyMovementPointsTheMoveConsumes(const sf::Vector2f& posA, const sf::Vector2f& posB);

	//===========================================================================================
	//Description: Draws contents of this class
	//===========================================================================================
	void draw();

	//===========================================================================================
	//Description: Sets a function that deletes AI players data
	//===========================================================================================
	void setFunctionToCallWhenDeletingAIPlayer(std::function<void(int)> function);

	//===========================================================================================
	//Description: Return a vector reference of town map objects
	//===========================================================================================
	std::vector<std::unique_ptr<TownMapObject>>& getVectorOfTownMapObjects();

	//===========================================================================================
	//Description: Return a vector reference of town data
	//===========================================================================================
	std::vector<std::unique_ptr<TownData>>& getVectorOfTownDatas();

	//===========================================================================================
	//Description: Return a vector reference of unit map objects
	//===========================================================================================
	std::vector<std::unique_ptr<UnitMapObject>>& getVectorOfUnitMapObjects();

	//===========================================================================================
	//Description: Return a vector reference of resource mine map objects
	//===========================================================================================
	std::vector<std::unique_ptr<ResourceMineMapObject>>& getVectorOfResourceMineObjects();

	//===========================================================================================
	//Description: Return a vector reference of resource map objects
	//===========================================================================================
	std::vector<std::unique_ptr<ResourceMapObject>>& getVectorOfResourceObjects();

	//===========================================================================================
	//Description: Return a vector reference of special building map objects
	//===========================================================================================
	std::vector<std::unique_ptr<SpecialBuildingMapObject>>& getVectorOfSpecialBuildingMapObjects();
};

#endif // !MAPHANDLER_H