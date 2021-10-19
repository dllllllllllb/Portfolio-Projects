//Author: Maciej Dowbor
//Last Accessed: 30/03/2021

#ifndef COLLIDABLEOBJECT_H
#define COLLIDABLEOBJECT_H

#include <SFML/Graphics/Sprite.hpp>


//===========================================================================================
//Description: Gives the ability for the object to collide
//===========================================================================================
class CollidableObject : public virtual sf::Transformable
{
private:
	float m_horizontalCollisionBound;
	float m_verticalCollisionBound;

protected:

public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	CollidableObject();

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~CollidableObject();

	//===========================================================================================
	//Description: Returns a bool whether a collision happened
	//===========================================================================================
	const bool collisionCheck(const sf::Vector2f& otherObjectPosition);

	//===========================================================================================
	//Description: Sets collision bounds
	//===========================================================================================
	void setCollisionBounds(const int& width, const int& height);
};

#endif // !COLLIDABLEOBJECT_H

