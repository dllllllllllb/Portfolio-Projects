//Author: Maciej Dowbor
//Last Accessed: 19/10/2021
#ifndef BASICBUTTON_H
#define BASICBUTTON_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Audio.h"
#include "CollidableObject.h"
#include "GlobalVariables.h"
#include "Textures.h"


//===========================================================================================
//Description: Basic Accept/Decline button set in the constructor
//===========================================================================================
class BasicButton :virtual public CollidableObject, public sf::Sprite
{
private:
	Audio& m_audio;
	SFXEnum m_SFXToPlay;
public:

	//===========================================================================================
	//Description: Class constructor, you define the button texture using the state bool.
	//			   true = Accept Button
	//			   false = Decline Button
	//===========================================================================================
	BasicButton(Textures& rTextures, Audio& rAudio, const bool state);

	//===========================================================================================
	//Description: Checks if button was pressed and plays a sound
	//===========================================================================================
	const bool checkIfButtonWasPressed(const sf::Vector2f& mousePosition);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~BasicButton();

};

#endif // !BASICBUTTON_H

