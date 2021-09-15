#include "TurnHandler.h"
TurnHandler::TurnHandler() :
	m_numberOfPlayers(0),
	m_currentTurn(0),
	m_currentPlayerIndex(0)
{
}

TurnHandler::~TurnHandler()
{
}

void TurnHandler::incrementTurn()
{
	m_currentTurn++;
}

const int& TurnHandler::getCurrentTurn() const
{
	return m_currentTurn;
}

const bool TurnHandler::incrementCurrentPlayer()
{
	bool wasTurnIncremented = false;

	m_currentPlayerIndex++;

	if (m_currentPlayerIndex >= m_numberOfPlayers)
	{
		m_currentPlayerIndex = 0;
		wasTurnIncremented = true;
		incrementTurn();
	}

	return wasTurnIncremented;
}

void TurnHandler::incrementNumberOfPlayers()
{
	m_numberOfPlayers++;
}

void TurnHandler::setCurrentPlayerIndex(const int& playerIndex)
{
	m_currentPlayerIndex = playerIndex;
}

const int TurnHandler::getCurrentPlayerIndex() const
{
	return m_currentPlayerIndex;
}
