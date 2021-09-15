//Author: Maciej Dowbor
//Module: MED5148
//Date last accessed: 28/10/2020

#ifndef MENUOPTION_H
#define  MENUOPTION_H

#include "Text.h"

//=============================================================
// Class Name   : MenuOption
//-------------------------------------------------------------
// Purpose      : Holds menu options and their settings
//-------------------------------------------------------------
// Used in      : Menu.h
//				  Menu.cpp
//=============================================================
class MenuOption : public Text
{
private:
	int m_numOfOptions; //Holds number of options
	int m_currentOption; //Holds current option

	Text m_optionSetting; //Holds the name of the option
	std::string* m_settingsString = NULL; //Holds names of options settings
	
	//========================================================
	// Function Name	: createOptionNames()
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: Creates num of strings based on the
	//					  number of options
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	void createOptionNames(); 


public:
	//========================================================
	// Function Name	: MenuOption()
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: Constructor
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	MenuOption();

	//========================================================
	// Function Name	: ~MenuOption()
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: Destructor
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	~MenuOption();

	//========================================================
	// Function Name	: initialize()
	//--------------------------------------------------------
	// Parameters		: Name of the option
	//					  Text alignment
	//					  Text position
	//					  Number of option settings
	//					  Text color
	//--------------------------------------------------------
	// Purpose			: Initialize the option
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	void initialize( std::string optionName, Alignment alignment, int positionY,  int numberOfOptions, int textAttribute );

	//========================================================
	// Function Name	: getCurrentOption()
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: Return currently selected option
	//--------------------------------------------------------
	// Returns			: Currently selected option as int
	//========================================================
	int getCurrentOption() const;

	//========================================================
	// Function Name	: setCurrentOption
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: Set currently selected option
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	void setCurrentOption( int value);

	//========================================================
	// Function Name	: getNumOfOptions()
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: Return number of options
	//--------------------------------------------------------
	// Returns			: Number of options as int
	//========================================================
	int getNumOfOptions() const;

	//========================================================
	// Function Name	: setNumOfOptions()
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: Set number of option settings
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	void setNumOfOptions(int value);

	//========================================================
	// Function Name	: drawOptionSetting()
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: Draws option setting
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	void drawOptionSetting();

	//========================================================
	// Function Name	: setOptionSetting()
	//--------------------------------------------------------
	// Parameters		: Option setting name
	//					  Text alignment
	//					  Text y position
	//					  Text color
	//--------------------------------------------------------
	// Purpose			: Set option setting
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	void setOptionSetting( std::string optionName, Alignment alignment, int positionY, int textAttribute );

	//========================================================
	// Function Name	: setOptionStringAttribute
	//--------------------------------------------------------
	// Parameters		: -
	//--------------------------------------------------------
	// Purpose			: Set text color
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	void setOptionSettingAttribute( int textAttribute );

	//========================================================
	// Function Name	: setOptionName
	//--------------------------------------------------------
	// Parameters		: Option setting id
	//					  Option setting name
	//--------------------------------------------------------
	// Purpose			: Default CharObject constructor
	//--------------------------------------------------------
	// Returns			: -
	//========================================================
	void setOptionName( int id, std::string optionName );
};

#endif
