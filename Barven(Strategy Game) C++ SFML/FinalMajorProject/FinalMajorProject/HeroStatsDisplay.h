//Author: Maciej Dowbor
//Last Accessed: 30/08/2021

#ifndef HEROSTATSDISPLAY_H
#define HEROSTATSDISPLAY_H

#include "HeroStatsEnum.h"
#include "HeroStatsDisplaySettings.h"
#include "Text.h"

//===========================================================================================
//Description: Displays icons and their coresponding values based on hero stats
//===========================================================================================
class HeroStatsDisplay
{
private:
	sf::RenderWindow& m_window;
	Textures& m_textures;
	sf::Sprite m_heroStatIcons[HeroStatsDisplaySettings::c_numOfSkills];
	std::vector<std::unique_ptr<Text>> m_heroStatValues;

public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	HeroStatsDisplay(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~HeroStatsDisplay();

	//===========================================================================================
	//Description: Sets up elements of this class
	//===========================================================================================
	void setUpHeroStatsDisplay(const int& posX, const int& posY, const int& panelWidth, const float& iconScale, const int& charSize);
	
	//===========================================================================================
	//Description: Updates values displayer for specified hero stat
	//===========================================================================================
	void updateHeroStat(const int& heroStatIndex, const int& heroStatValue);
	
	//===========================================================================================
	//Description: Returns height of this element
	//===========================================================================================
	const int getDisplayHeight() const;

	//===========================================================================================
	//Description: Draws contents of this class
	//===========================================================================================
	void draw();
};

#endif // !HEROSTATSDISPLAY_H

