//Author: Maciej Dowbor
//Last Accessed: 30/03/2021
#ifndef BASICBUTTON_H
#define BASICBUTTON_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


#include "CollidableObject.h"
#include "Textures.h"


//===========================================================================================
//Description: Basic Accept/Decline button set in the constructor
//===========================================================================================
class BasicButton :virtual public CollidableObject, public sf::Sprite
{
private:

public:

	//===========================================================================================
	//Description: Class constructor, you define the button texture using the state bool.
	//			   true = Accept Button
	//			   false = Decline Button
	//===========================================================================================
	BasicButton(Textures* pTextures, const bool state);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~BasicButton();

};

#endif // !BASICBUTTON_H

