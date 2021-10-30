//Author: Maciej Dowbor
//Last Accessed: 30/09/2021

#ifndef COMBATUNITEDITOR_H
#define COMBATUNITEDITOR_H

#include "CombatUnitEditorEnum.h"
#include "CombatUnitEditorSettings.h"
#include "DataHandler.h"
#include "IconButtonList.h"
#include "TextInputBox.h"
#include "Hero.h"
#include "UnitsPanel.h"

//===========================================================================================
//Description: Interface to edit battling armies in combat tool
//===========================================================================================
class CombatUnitEditor
{
private:
	sf::RenderWindow& m_window;
	Textures& m_textures;
	DataHandler& m_dataHandler;

	Hero* m_pAttackerHero;
	Hero* m_pDefenderHero;

	UnitsPanel m_attackerUnits;
	UnitsPanel m_defenderUnits;

	UIElement m_background;
	IconButtonList m_unitList;
	UIElement m_unitListOutline;
	TextInputBox m_setNumberOfUnitsInputBox;
	Button m_applySettingsButton;
	std::vector<std::unique_ptr<Button>> m_buttons;

	bool m_isEditorActive;
	bool m_isAttackerSelected;
	int m_selectedUnitPositionIndex;

public:

	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	CombatUnitEditor(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts, Audio& rAudio, DataHandler& rDataHandler);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~CombatUnitEditor();

	//===========================================================================================
	//Description: Initializes elements of this class. Sets up bottons, pannels etc.
	//===========================================================================================
	void initialize();

	//===========================================================================================
	//Description: Sets pointers to combating heroes
	//===========================================================================================
	void setHeroPointers(Hero* attackingHero, Hero* defenderHero);

	//===========================================================================================
	//Description: Sets editor window variables
	//===========================================================================================
	void setEditorWindowVariables();

	//===========================================================================================
	//Description: Applies changes made to the selected unit in unit editor
	//===========================================================================================
	void applyUnitChanges();

	//===========================================================================================
	//Description: Deletes selected unit from heroes army
	//===========================================================================================
	void deleteUnit();

	//===========================================================================================
	//Description: Updates unit cards to display appropriate information
	//===========================================================================================
	void updateUnitCards();

	//===========================================================================================
	//Description: Resets selected unit cards in each unit panel
	//===========================================================================================
	void resetSelectedUnitCards();

	//===========================================================================================
	//Description: Updates elements of this class
	//===========================================================================================
	const bool update(const sf::Vector2f& mousePosition);

	//===========================================================================================
	//Description: Updates position of selected unit in unit icon list
	//===========================================================================================
	void updateUnitListOutline();

	//===========================================================================================
	//Description: Draws elements of this class
	//===========================================================================================
	void draw();

	//===========================================================================================
	//Description: Returns if the editor is active
	//===========================================================================================
	const bool getIsEditorActive() const;

	//===========================================================================================
	//Description: Returns selected unit pointer
	//===========================================================================================
	Unit* getSelectedUnit();
};

#endif // !COMBATUNITEDITOR_H

