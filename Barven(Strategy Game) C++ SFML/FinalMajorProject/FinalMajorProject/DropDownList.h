//Author: Maciej Dowbor
//Last Accessed: 17/06/2021

#ifndef DROPDOWNLIST_H
#define DROPDOWNLIST_H

#include <functional>

#include "Button.h"
#include "GlobalVariables.h"
#include "Slider.h"
#include "DropDownListSettings.h"

//===========================================================================================
//Description: Fully customizable drop down list
//===========================================================================================
class DropDownList
{
private:
	sf::RenderWindow& m_window;
	Textures* m_pTextures;
	Fonts* m_pFonts;
	Slider m_slider;

	int m_numberOfOptions;
	int m_firstVisibleOption;
	int m_selectedOptionID;
	bool m_isDropDownActive;

	//Drop down settings
	int m_numOfOptionsToDisplay;
	int m_optionWidth;
	int m_optionHeight;
	int m_positionX;
	int m_positionY;
	int m_optionSpaceing;
	std::string m_primaryButtonTitle;
	int m_titleCharSize;
	std::string m_primaryButtonContentText;
	int m_buttonContentCharSize;


	Button m_primaryButton;
	std::vector<std::unique_ptr<Button>> m_pDropDownButtons;
	std::function<void()> m_functionToCallWhenItemSelected;
public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	DropDownList(sf::RenderWindow& rWindow, Textures* pTextures, Fonts* pFonts);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~DropDownList();

	//===========================================================================================
	//Description: Sets drop down settings and adjusts the drop down list to fit these settings
	//===========================================================================================
	void setDropDownListSettings(const int& numOfOptionsToDisplay, const int& optionWidth, const int& optionHeight, const int& positionX, const int& positionY, const int& optionSpaceing, const std::string& primaryButtonTitle, const int& titleCharSize, const std::string& primartButtonContentText, const int& buttonContentCharSize);

	//===========================================================================================
	//Description: Sets a pointer to a function that will be called when an option is selected
	//===========================================================================================
	void setConfirmationFunctionPointer(std::function<void()> function);

	//===========================================================================================
	//Description: Adds new options to the drop down list
	//===========================================================================================
	void addNewDropDownOptions(const std::string& optionName);

	//===========================================================================================
	//Description: Sets up slider that allows to scroll through drop down options
	//===========================================================================================
	void setUpSlider();

	//===========================================================================================
	//Description: Sets positions of the displayed options
	//===========================================================================================
	void setOptionsPositions();

	//===========================================================================================
	//Description: Updates which options are visible based on slider position
	//===========================================================================================
	void updateVisibleOptions();

	//===========================================================================================
	//Description: Updates slider and checks if option is selected
	//===========================================================================================
	void update(const sf::Vector2f& mousePosition);

	//===========================================================================================
	//Description: Returns index of the selected option
	//===========================================================================================
	const int& getSelectedOptionID() const;

	//===========================================================================================
	//Description: Deletes options
	//===========================================================================================
	void deleteOptions();

	//===========================================================================================
	//Description: Resizes the slider to fit the drop down list
	//===========================================================================================
	void resizeSlider();

	//===========================================================================================
	//Description: Draws content of this class
	//===========================================================================================
	void draw();
};


#endif // !DROPDOWNLIST_H

