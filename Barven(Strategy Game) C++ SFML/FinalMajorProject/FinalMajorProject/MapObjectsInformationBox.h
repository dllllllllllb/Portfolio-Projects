//Author: Maciej Dowbor
//Last Accessed: 10/09/2021

#ifndef MAPOBJECTSINFORMATIONBOX_H
#define MAPOBJECTSINFORMATIONBOX_H

#include "PopUpTextBox.h"
#include "SFML/Window/Mouse.hpp"

//===========================================================================================
//Description: Displays map object information
//===========================================================================================
class MapObjectsInformationBox
{
private:
	PopUpTextBox m_mapObjectsInformationBox;

	bool m_isActive;
public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	MapObjectsInformationBox(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~MapObjectsInformationBox();

	//===========================================================================================
	//Description: Sets pop up information
	//===========================================================================================
	void setInformation(const sf::Vector2f& position, std::string& contentText);

	//===========================================================================================
	//Description: Checks if RMB is still pressed, disables popup if false
	//===========================================================================================
	void update();

	//===========================================================================================
	//Description: Draws elements of this class
	//===========================================================================================
	void draw();

	//===========================================================================================
	//Description: Returns if the popup is active
	//===========================================================================================
	const bool getIsActive() const;

};

#endif // !MAPOBJECTSINFORMATIONBOX_H

