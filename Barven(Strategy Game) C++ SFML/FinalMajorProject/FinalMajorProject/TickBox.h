//Author: Maciej Dowbor
//Last Accessed: 30/03/2021

#ifndef TICKBOX_H
#define TICKBOX_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "CollidableObject.h"
#include "Textures.h"

//===========================================================================================
//Description: A tick box, holds and returns a bool and changes textures based on the bool
//===========================================================================================
class TickBox : public CollidableObject, public sf::Sprite
{
private:
	Textures* m_pTextures;
	bool m_state;


public:

	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	TickBox(Textures* pTextures);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~TickBox();

	void setPosition(const int& positionX, const int& positionY);

	//===========================================================================================
	//Description: Sets the bool to true/false
	//===========================================================================================
	void setState(const bool state);

	//===========================================================================================
	//Description: Toggles bool between true/false
	//===========================================================================================
	void toggleState();

	//===========================================================================================
	//Description: Returns state
	//===========================================================================================
	const bool getState() const;

	//===========================================================================================
	//Description: Changes texture based on state
	//===========================================================================================
	void swapTexture();
};
#endif // !TICKBOX_H

