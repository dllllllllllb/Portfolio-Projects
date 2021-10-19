//Author: Maciej Dowbor
//Last Accessed: 02/09/2021

#ifndef TOWNHEROESUNITSPANEL_H
#define TOWNHEROESUNITSPANEL_H

#include <vector>

#include "UnitCard.h"
#include "TownHeroesUnitsPanelSettings.h"
#include "GlobalVariables.h"
#include "Hero.h"
#include "TownData.h"
#include "UnitInformationCard.h"

//===========================================================================================
//Description: Displays units owned by the selected hero
//===========================================================================================
class UnitsPanel
{
private:
	sf::RenderWindow& m_window;
	Textures& m_textures;
	UIElement m_background;
	UIElement m_cardOutline;
	std::vector<std::shared_ptr<Unit>>* m_unitsUsedInThisPanel;
	UnitInformationCard m_unitInformationCard;

	std::vector<std::unique_ptr<UnitCard>> m_unitCards;
	bool m_isUnitCardSelected;
	int m_selectedCardIndex;
	int m_unitCardInformationIndex;

public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	UnitsPanel(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts, Audio& rAudio);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~UnitsPanel();

	//===========================================================================================
	//Description: Sets up empty unit panel
	//===========================================================================================
	void setUpPanel(const int& positionX, const int& positionY, const bool setUnitCardInfoOnTheRight);

	//===========================================================================================
	//Description: Sets unit cards based on units in selected heroes army
	//===========================================================================================
	void setUnitCards(std::vector<std::shared_ptr<Unit>>& vectorOfUnits);

	//===========================================================================================
	//Description: Updates cards content based on units used
	//===========================================================================================
	void updateUnitCardsContent();

	//===========================================================================================
	//Description: Resets unit cards to be empty
	//===========================================================================================
	void resetUnitCards();

	//===========================================================================================
	//Description: Updates unit card interaction
	//===========================================================================================
	const bool update(const sf::Vector2f& mousePosition);

	//===========================================================================================
	//Description: Swaps units position in their vector
	//===========================================================================================
	void changeUnitsPositions(const int& indexToSwapWith);

	//===========================================================================================
	//Description: Resets selected card indexes
	//===========================================================================================
	void resetSelectedIndexes();

	//===========================================================================================
	//Description: Toggles if unit card is selected state between true and false
	//===========================================================================================
	void toggleIsUnitCardSelected();

	//===========================================================================================
	//Description: Sets isUnitCardSelected state
	//===========================================================================================
	void setIsUnitCardSelected(const bool state);

	//===========================================================================================
	//Description: Draws contents of this class
	//===========================================================================================
	void draw();

	//===========================================================================================
	//Description: Returns width of the panel
	//===========================================================================================
	const int& getUnitPanelWidth();

	//===========================================================================================
	//Description: Returns a bool that determines if a unit card is selected
	//===========================================================================================
	const bool getIsUnitCardSelected() const;

	//===========================================================================================
	//Description: Returns a vector of units used by this panel
	//===========================================================================================
	std::vector<std::shared_ptr<Unit>>* getVectorOfUnitsUsedByThisPanel();

	//===========================================================================================
	//Description: Returns index of selected unit card
	//===========================================================================================
	const int& getSelectedCardIndex() const;
};

#endif // !TOWNHEROESUNITSPANEL_H
