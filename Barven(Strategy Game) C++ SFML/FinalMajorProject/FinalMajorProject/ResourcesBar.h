//Author: Maciej Dowbor
//Last Accessed: 14/07/2021

#ifndef RESOURCESBAR_H
#define RESOURCESBAR_H

#include "Text.h"
#include "ResourcesBarSettings.h"
#include "ResourcesEnum.h"
#include "Bar.h"
#include "Resources.h"


//===========================================================================================
//Description: Displays users resources at the top of the screen
//===========================================================================================
class ResourcesBar
{
private:
	sf::RenderWindow& m_window;
	Bar m_bar;
	Text m_goldText;
	Text m_woodText;
	Text m_stoneText;

	sf::Sprite m_goldIcon;
	sf::Sprite m_woodIcon;
	sf::Sprite m_stoneIcon;

public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	ResourcesBar(sf::RenderWindow& rWindow, Textures* pTextures, Fonts* pFonts);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~ResourcesBar();

	//===========================================================================================
	//Description: Sets up resource bar
	//===========================================================================================
	void setUp();

	//===========================================================================================
	//Description: Updates resource bar values
	//===========================================================================================
	void updateResourcesBarValues(const Resources& resources);

	//===========================================================================================
	//Description: Sets resource value
	//===========================================================================================
	void setResourceValue(const ResourcesEnum& resource, const int& value);

	//===========================================================================================
	//Description: Draws contents of this class
	//===========================================================================================
	void draw();
};

#endif // !RESOURCESBAR_H

