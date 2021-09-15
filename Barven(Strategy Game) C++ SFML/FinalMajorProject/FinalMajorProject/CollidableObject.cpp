#include "CollidableObject.h"

CollidableObject::CollidableObject():
	m_horizontalCollisionBound(0),
	m_verticalCollisionBound(0)
{
}

CollidableObject::~CollidableObject()
{
}

bool CollidableObject::collisionCheck(const sf::Vector2f& otherObjectPosition)
{
	float positionX = getPosition().x;
	float positionY = getPosition().y;

	return (otherObjectPosition.x <= positionX + m_horizontalCollisionBound && 
			otherObjectPosition.x >= positionX - m_horizontalCollisionBound && 
			otherObjectPosition.y >= positionY - m_verticalCollisionBound	&& 
			otherObjectPosition.y <= positionY + m_verticalCollisionBound	);
}

void CollidableObject::setCollisionBounds(const int& width, const int& height)
{
	m_horizontalCollisionBound = width * 0.5f;
	m_verticalCollisionBound = height * 0.5f;
}
