//Author: Maciej Dowbor
//Last Accessed: 21/04/2021

#ifndef SLIDERHANDLE_H
#define SLIDERHANDLE_H

#include <SFML/Graphics/Sprite.hpp>

#include "CollidableObject.h"

//===========================================================================================
//Description: Slider handle
//===========================================================================================
class SliderHandle : public sf::Sprite, public CollidableObject
{
private:

public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	SliderHandle();

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~SliderHandle();

	//===========================================================================================
	//Description: Sets handle position
	//===========================================================================================
	void setPosition(const int& postionX, const int& positionY);

	//===========================================================================================
	//Description: Sets handle rotation
	//===========================================================================================
	void setRotation(const float& rotationAngle);
};

#endif // !SLIDERHANDLE_H
