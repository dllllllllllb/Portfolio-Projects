//Author: Maciej Dowbor
//Last Accessed: 14/07/2021

#ifndef MOVEABLEOBJECT_H
#define MOVEABLEOBJECT_H
#include <vector>
#include <functional>

#include "SFML/Graphics/Sprite.hpp"

//===========================================================================================
//Description: Object that is able to move
//===========================================================================================
class MoveableObject : virtual public sf::Sprite
{
private:
	int m_tilesToMove;
	float m_percentageMoved;

	sf::Vector2f m_startPosition;
	std::vector<sf::Vector2f> m_movementPath;

	std::function<void()> m_functionToCallWhenObjectArrivesAtDestination;

	//Think how to better set this up
	float movementSpeed = 15.0f;

protected:
	bool m_isMoving;

public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	MoveableObject();

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~MoveableObject();

	//===========================================================================================
	//Description: Moves the object across the set path in intervals based on movement speed.
	//			   Once the object arrives at its final destination, m_isMoving will be set to
	//			   false and a set function will be called
	//===========================================================================================
	void updateMovement(const float& deltaTime);

	//===========================================================================================
	//Description: Sets the coordinates of each tile on the path into a vector and resets
	//			   appropriate variables
	//===========================================================================================
	void setMovementPath(const std::vector<sf::Vector2f>& movementPath);

	//===========================================================================================
	//Description: Toggles m_isMoving between true and false state
	//===========================================================================================
	void toggleIsMoving();

	//===========================================================================================
	//Description: Returns m_isMoving bool
	//===========================================================================================
	const bool getIsMoving() const;

	//===========================================================================================
	//Description: Lerp function to move the object towards target position
	//===========================================================================================
	const sf::Vector2f lerp(const sf::Vector2f& startPosition, const sf::Vector2f& targetPosition, const float& percentageMoved);

	//===========================================================================================
	//Description: Sets a function reference to call when the object arrives at its destination
	//===========================================================================================
	void setFunctionToCallWhenObjectArrivesAtDestination(std::function<void()> function);
};

#endif // !MOVEABLEOBJECT_H
