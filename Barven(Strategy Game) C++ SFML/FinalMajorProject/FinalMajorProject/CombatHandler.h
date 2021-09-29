//Author: Maciej Dowbor
//Last Accessed: 10/09/2021

#ifndef COMBATHANDLER_H
#define COMBATHANDLER_H

#include <iostream>
#include <functional>

#include "AnimatedObject.h"
#include "CombatAI.h"
#include "CombatCursor.h"
#include "CombatEndPopUp.h"
#include "CombatHandlerButtonsEnum.h"
#include "CombatHandlerSettings.h"
#include "CombatUnit.h"
#include "DataHandler.h"
#include "GlobalVariables.h"
#include "Hero.h"
#include "LogsConsole.h"
#include "TileHandler.h"
#include "UnitInformationCard.h"
#include "UnitMapObject.h"
#include "UnitTurnOrderBar.h"
#include "CombatTypeEnum.h"

//===========================================================================================
//Description: Handles combat logic, player input and player feedback
//===========================================================================================
class CombatHandler
{
private:
	sf::RenderWindow& m_window;
	Textures& m_textures;
	Fonts& m_fonts;
	DataHandler& m_dataHandler;
	TileHandler m_tileHandler;
	sf::Sprite m_combatBackground;
	UnitTurnOrderBar m_unitTurnOrderBar;
	CombatCursor m_combatCursor;
	UnitInformationCard m_unitInformationCard;
	UIElement m_background;
	UIElement m_combatBackgroundBorder;
	CombatEndPopUp m_combatEndPopUp;
	LogsConsole m_logsConsole;
	CombatAI m_attackerAI;
	CombatAI m_defenderAI;

	Hero* m_pAttackerHero;
	Hero* m_pDefenderHero;
	UnitMapObject* m_pDefenderMapUnit;
	std::vector<std::shared_ptr<Unit>>* m_pTownUnitsVectorPointer;

	std::function<void(const CombatTypeEnum, const bool)> m_functionToCallAfterCombatConcluded;

	//Buttons
	std::vector<std::unique_ptr<IconButton>> m_buttons;

	//Combat Units variables
	std::vector<std::unique_ptr<CombatUnit>> m_combatUnits;
	int m_numOfAttackerUnits;
	int m_numOfDefenderUnits;
	bool m_didUnitMakeAMove;

	//Combat logic variables
	int m_currentTurn;
	int m_currentUnitTurnIndex;
	int m_unitIndexToInteractWith;
	int m_tileIndexToInteractWith;
	std::vector<int> m_unitTurnOrder;
	std::vector<int> m_unitIndexesToDeleteFromTurnQue;
	std::vector<int> m_unitDrawOrder; //Stored units indexes based on their tile position. Order: Left -> Right, Bottom -> Top
	bool m_canCurrentlySelectedUnitsInteract;
	bool m_didUnitMove;
	bool m_isCombatActive;
	bool m_isAttackerAI;
	bool m_isDefenderAI;
	bool m_didAttackerWin;
	CombatTypeEnum m_combatType;

	//Player feedback variables
	bool m_isPlayerWatching;
	int m_selectedUnitAlpha;
	bool m_drawCurrentTurnUnitIndicator;

	sf::Sprite m_tileFill;
	sf::Sprite m_currentTurnUnitIndicator;

	AnimatedObject m_bloodSplash;

	std::vector<int> m_tileIndexesThatAreWithinUnitsMovementRange;

public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	CombatHandler(sf::RenderWindow& rWindow, Textures& rTextures, DataHandler& rDataHandler, Fonts& rFonts);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~CombatHandler();

	//===========================================================================================
	//Description: Sets up combat area, tiles and UI
	//===========================================================================================
	void setUpCombatAreaAndUI();

	//===========================================================================================
	//Description: Sets up player vs player combat
	//===========================================================================================
	void setUpPlayerVsPlayer(Hero* attackerHero, Hero* defenderHero, const bool isAttackerAI, const bool isDefenderAI);

	//===========================================================================================
	//Description: Sets up player vs map unit combat
	//===========================================================================================
	void setUpPlayerVsMapUnit(Hero* attackerHero, UnitMapObject* mapUnit, const bool isAttackerAI);

	//===========================================================================================
	//Description: SEts up player vs town garrison combat
	//===========================================================================================
	void setUpPlayerVsTown(Hero* attackerHero, std::vector<std::shared_ptr<Unit>>* townUnits, const bool isAttackerAI, const bool isDefenderAI);

	//===========================================================================================
	//Description: Sets up units owned by a hero
	//===========================================================================================
	void setHeroUnits(Hero* hero, const int& m_numberOfUnitsToSet);

	//===========================================================================================
	//Description: Sets up units owned by a map unit
	//===========================================================================================
	void setMapUnitObjectUnits(UnitMapObject* mapUnit);

	//===========================================================================================
	//Description: Sets units in towns garrison
	//===========================================================================================
	void setTownUnits(std::vector<std::shared_ptr<Unit>>& townUnits);

	//===========================================================================================
	//Description: Splits map unit into multiple entities
	//===========================================================================================
	const int splitMapUnitIntoIndividualUnits(UnitMapObject* mapUnit);

	//===========================================================================================
	//Description: Sets appropriate parameters to combat units, sets up tile properties and	
	//			   all neccessary data for combat handler
	//===========================================================================================
	void setUpCombatUnits();

	//===========================================================================================
	//Description: Sets up AI parameters
	//===========================================================================================
	void setUpAI();

	//===========================================================================================
	//Description: Sets units turn order based on units speed
	//===========================================================================================
	void setTurnOrder();

	//===========================================================================================
	//Description: Resets combat handlers variables
	//===========================================================================================
	void resetCombatHandlerVariables();

	//===========================================================================================
	//Description: Updates mouse cursor, animations, checks if player interacted with the map,
	//			   updates player feedback and unit movement
	//===========================================================================================
	void update(const sf::Vector2f& mousePosition, const float& deltaTime);

	//===========================================================================================
	//Description: Updates AI vs AI logic, optimised to make combat shorter
	//===========================================================================================
	void updateAIvsAI();

	//===========================================================================================
	//Description: Updates combat if there is at least one human player involved
	//===========================================================================================
	void updateIfAtLeastOnePlayer(const sf::Vector2f& mousePosition, const float& deltaTime);

	//===========================================================================================
	//Description: Updates UI interaction
	//===========================================================================================
	void updateUI(const sf::Vector2f& mousePosition);

	//===========================================================================================
	//Description: Checks if an interaction between two units was initiated
	//===========================================================================================
	const bool checkIfInteractionWithEnemyUnitWasInitiated(const sf::Vector2f mousePosition);

	//===========================================================================================
	//Description: Checks if units are next to eachother
	//===========================================================================================
	const bool checkIfObjectsAreNextToEachother(const sf::Vector2f& unitA, const sf::Vector2f& unitB);

	//===========================================================================================
	//Description: Attack interaction between two rival units
	//===========================================================================================
	void attack();

	//===========================================================================================
	//Description: Defend action, increases units defence by 1 and ends its turn
	//===========================================================================================
	void defend();

	//===========================================================================================
	//Description: Wait action, puts unit at the end of current turns que and ends its turn
	//===========================================================================================
	void wait();

	//===========================================================================================
	//Description: Gives the controll of players units to the AI
	//===========================================================================================
	void setAutoCombat();

	//===========================================================================================
	//Description: Checks if the tile attempted to move on is valid and unoccupied, call moveUnit
	//			   if true
	//===========================================================================================
	void checkForUnitMovement(const sf::Vector2f& mousePosition);

	//===========================================================================================
	//Description: Makes multiple checks to make sure that the move is valid and sets a path
	//			   for the selected unit to move through
	//===========================================================================================
	void moveUnit(const int tileIndex);

	//===========================================================================================
	//Description: Update tile properties after unit has moved
	//===========================================================================================
	void updateTilePropertiesAfterUnitMoved();

	//===========================================================================================
	//Description: Deletes defeated unit, resets tile properties it occupied and updates
	//			   appropriate variables
	//===========================================================================================
	void deleteUnit(const int& unitIndexToDelete);

	//===========================================================================================
	//Description: Resets visual feedback, determines current units turn, and calls appropriate
	//			   functions
	//===========================================================================================
	void nextTurn();

	//===========================================================================================
	//Description: Updates the order in which units are drawn, makes sure units are displayed
	//			   properly on the screen
	//===========================================================================================
	void updateDrawingOrder();

	//===========================================================================================
	//Description: Sets appropriate variables and calls appropriate functions
	//===========================================================================================
	void endCombat();

	//===========================================================================================
	//Description: Awards the winner with experience based on the enemies defeated
	//===========================================================================================
	void awardExperienceToTheWinner();

	//===========================================================================================
	//Description: Updates participating armies after the combat is over
	//===========================================================================================
	void updateCombatantsArmiesAfterCombat();

	//===========================================================================================
	//Description: Sets function pointer to call after the combat is won
	//===========================================================================================
	void setFunctionToCallWhenCombatIsWon(std::function<void(const CombatTypeEnum, const bool)> function);

	//===========================================================================================
	//Description: Return a bool based on if the attacker won the battle
	//===========================================================================================
	const bool getDidAttackerWin() const;

	//===========================================================================================
	//Description: Return pointer to attacking hero
	//===========================================================================================
	Hero* getAttackerHero();

	//===========================================================================================
	//Description: Return pointer to defending hero
	//===========================================================================================
	Hero* getDefenderHero();

	//===========================================================================================
	//Description: Return pointer to defending unit map object
	//===========================================================================================
	UnitMapObject* getUnitMapObject();

	//===========================================================================================
	//Description: Returns pointer to town garrison units
	//===========================================================================================
	std::vector<std::shared_ptr<Unit>>* getTownUnitsVectorPointer();

	//===========================================================================================
	//Description: Returns if combat is active
	//===========================================================================================
	const bool getIsCombatActive() const;



	/////////////////////////////////////////////////////////////////////////////////////////////
	//PlayerFeedback
	/////////////////////////////////////////////////////////////////////////////////////////////

	//===========================================================================================
	//Description: Visual representation of tiles that are occupied
	//===========================================================================================
	void showTileProperties();

	//===========================================================================================
	//Description: Visual representation of tiles that are within current units movment range
	//===========================================================================================
	void setTilesThatAreWithinUnitMovementRange();

	//===========================================================================================
	//Description: Player feedback to indicate which units turn it is
	//===========================================================================================
	void updateCurrentUnitTurnFeedback();

	//===========================================================================================
	//Description: Sets indicator above unit that is currently taking its turn
	//===========================================================================================
	void setCurrentUnitTurnIndicator();

	//===========================================================================================
	//Description: Checks if player activated unit card to see units details
	//===========================================================================================
	void checkIfPlayerActivatedUnitCard(const sf::Vector2f& mousePosition);



	/////////////////////////////////////////////////////////////////////////////////////////////
	//Drawing
	/////////////////////////////////////////////////////////////////////////////////////////////

	//===========================================================================================
	//Description: Draws elements of this class
	//===========================================================================================
	void draw();

	//===========================================================================================
	//Description: Draws game sprites
	//===========================================================================================
	void drawGame();

	//===========================================================================================
	//Description: Draws unit movement range feedback
	//===========================================================================================
	void drawUnitMovementRange();

	//===========================================================================================
	//Description: Draws UI elements
	//===========================================================================================
	void drawUI();
};
#endif // !COMBATHANDLER_H