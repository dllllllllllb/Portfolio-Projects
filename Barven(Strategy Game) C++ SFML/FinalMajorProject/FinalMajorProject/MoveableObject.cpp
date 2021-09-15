#include "MoveableObject.h"
MoveableObject::MoveableObject() :
	m_tilesToMove(0),
	m_percentageMoved(0),
	m_isMoving(false)
{
}

MoveableObject::~MoveableObject()
{
}

void MoveableObject::updateMovement(const float& deltaTime)
{
	if (m_isMoving)
	{
		m_percentageMoved += movementSpeed * deltaTime;

		setPosition(lerp(m_startPosition, m_movementPath[m_tilesToMove], m_percentageMoved));
		if (m_percentageMoved > 1.0f) //Checks if percentage exceeded 100% to round it down
		{
			m_percentageMoved = 0.0f;
			m_startPosition = getPosition(); //Resets start position
			if (m_tilesToMove > 0) //Checks if object has to move more tiles
			{
				m_tilesToMove--;
			}
			else //Object arrived at final destination
			{
				m_isMoving = false;
				m_functionToCallWhenObjectArrivesAtDestination();
			}
		}
	}
}

void MoveableObject::setMovementPath(const std::vector<sf::Vector2f>& movementPath)
{
	if (!movementPath.empty())
	{
		m_isMoving = true;
		m_movementPath.clear();
		m_movementPath = movementPath;
		m_tilesToMove = m_movementPath.size() - 1;
		m_percentageMoved = 0;
		m_startPosition = getPosition();
	}
}

void MoveableObject::toggleIsMoving()
{
	m_isMoving = !m_isMoving;
}

const bool MoveableObject::getIsMoving() const
{
	return m_isMoving;
}

const sf::Vector2f MoveableObject::lerp(const sf::Vector2f& startPosition, const sf::Vector2f& targetPosition, const float& percentageMoved)
{
	sf::Vector2f currentPosition = startPosition + (percentageMoved * (targetPosition - startPosition)); //Calculates new position based on movement percentage

	if (percentageMoved > 1.0f) //Makes sure the object doesn't go beyond target position
	{
		currentPosition = targetPosition;
	}
	return currentPosition;
}

void MoveableObject::setFunctionToCallWhenObjectArrivesAtDestination(std::function<void()> function)
{
	m_functionToCallWhenObjectArrivesAtDestination = function;
}