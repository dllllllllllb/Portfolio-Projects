#include "SliderHandle.h"
SliderHandle::SliderHandle()
{
}

SliderHandle::~SliderHandle()
{
}

void SliderHandle::setPosition(const int& postionX, const int& positionY)
{
	sf::Sprite::setPosition(postionX, positionY);
	CollidableObject::setPosition(postionX, positionY);
}

void SliderHandle::setRotation(const float& rotationAngle)
{
	sf::Transformable::setRotation(rotationAngle);
}
