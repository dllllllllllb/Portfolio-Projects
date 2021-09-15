//Author: Maciej Dowbor
//Last Accessed: 14/07/2021

#ifndef BAR_H
#define BAR_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Textures.h"

//===========================================================================================
//Description: UI element to display a bar (for example - can be used for a banner)
//===========================================================================================
class Bar
{
private:
	sf::RenderWindow& m_window;
	sf::Sprite m_bar;
	sf::Sprite m_barEndLeft;
	sf::Sprite m_barEndRight;
public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	Bar(sf::RenderWindow& rWindow, Textures* pTextures);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~Bar();

	//===========================================================================================
	//Description: Sets bars width, height and position of all of its elements
	//===========================================================================================
	void setUp(const int& width, const int& height, const int& positionX, const int& positionY);

	//===========================================================================================
	//Description: Returns position of the bar
	//===========================================================================================
	const sf::Vector2f& getPosition();

	//===========================================================================================
	//Description: Draws bar elements
	//===========================================================================================
	void draw();
};
#endif // !BAR_H

