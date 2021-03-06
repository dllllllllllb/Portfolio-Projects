//Author: Maciej Dowbor
//Last Accessed: 30/08/2021

#ifndef TURNHANDLER_H
#define TURNHANDLER_H


//===========================================================================================
//Description: Handles what and whos turn it is
//===========================================================================================
class TurnHandler
{
private:
	int m_numberOfPlayers;
	int m_currentTurn;
	int m_currentPlayerIndex;

public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	TurnHandler();

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~TurnHandler();

	//===========================================================================================
	//Description: Increments current turn
	//===========================================================================================
	void incrementTurn();

	//===========================================================================================
	//Description: Returns current turn
	//===========================================================================================
	const int& getCurrentTurn() const;

	//===========================================================================================
	//Description: Incremenrts which players turn it is
	//===========================================================================================
	const bool incrementCurrentPlayer();

	//===========================================================================================
	//Description: Increments number of players
	//===========================================================================================
	void incrementNumberOfPlayers();

	//===========================================================================================
	//Description: Sets current player index
	//===========================================================================================
	void setCurrentPlayerIndex(const int& playerIndex);

	//===========================================================================================
	//Description: Returns index of player that is currently taking a turn
	//===========================================================================================
	const int getCurrentPlayerIndex() const;
};

#endif // !TURNHANDLER_H

