//Author: Maciej Dowbor
//Last Accessed: 30/08/2021

#ifndef PURCHASEUNITWINDOW_H
#define PURCHASEUNJITWINDOW_H

#include "Button.h"
#include "TextBox.h"
#include "UnitData.h"
#include "Slider.h"
#include "PurchaseUnitSettings.h"
#include "BasicButton.h"
#include "ConfirmationWindow.h"

//===========================================================================================
//Description: Window that allows to purchase units
//===========================================================================================
class PurchaseUnitWindow : public virtual UIElement, public TextBoxTitle
{
private:
	ConfirmationWindow* m_pConfirmationWindow;
	UIElement m_unitImageBackground;
	sf::Sprite m_unitSprite;
	TextBox m_unitStats;
	Slider m_slider;
	TextBox m_unitsToRecruit;
	TextBox m_costOfRecruiting;

	int m_numOfUnitsToRecruit;
	int m_maxNumOfUnitsToRecruit;
	int m_costPerUnit;

	Button m_purchaseButton;

	std::function<void()> m_purchaseUnitsFunction;

public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	PurchaseUnitWindow(sf::RenderWindow& rWindow, Textures* pTextures, Fonts* pFonts, ConfirmationWindow* pConfirmationWindow);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~PurchaseUnitWindow();

	//===========================================================================================
	//Description: Sets up windows elements
	//===========================================================================================
	void setUpPurchaseWindow();

	//===========================================================================================
	//Description: Repositions purchase window
	//===========================================================================================
	void reposition();

	//===========================================================================================
	//Description: Updates purchase window
	//===========================================================================================
	bool update(const sf::Vector2f& mousePosition);

	//===========================================================================================
	//Description: Updates text box that displays selected number of units to recruit
	//===========================================================================================
	void updatePlayerFeedbackTextBoxes();

	//===========================================================================================
	//Description: Displays data of currently selected unit to recruit
	//===========================================================================================
	void setWindowContent(const UnitData* unitData, const int& unitsAvailable);

	//===========================================================================================
	//Description: Sets appropriate unit background based on faction index
	//===========================================================================================
	void setUnitBackground(const int& factionIndex);

	//===========================================================================================
	//Description: Buys units
	//===========================================================================================
	void purchaseUnits();

	//===========================================================================================
	//Description: Sets which function to call a unit is purchased
	//===========================================================================================
	void setPurchaseUnitFunction(std::function<void()> function);

	//===========================================================================================
	//Description: Returns number of units selected to be recruited
	//===========================================================================================
	const int getNumberOfUnitsToRecruit() const;

	//===========================================================================================
	//Description: Sets function pointer to a function that will be called when purchase is
	//			   confirmed in the confirmation window
	//===========================================================================================
	void updateConfirmationFunctionPointer();

	//===========================================================================================
	//Description: Draws contents of this class
	//===========================================================================================
	void draw();
};

#endif // !PURCHASEUNITWINDOW_H
