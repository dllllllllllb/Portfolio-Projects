//Author: Maciej Dowbor
//Module: MED5148
//Date last accessed: 28/10/2020

#include "MenuOption.h"

//Constructor
MenuOption::MenuOption()
	:m_numOfOptions(0),
	 m_currentOption(0)
{
	
}


//Destructor
MenuOption::~MenuOption()
{
	delete m_settingsString;
}

//Get current setting option
int MenuOption::getCurrentOption() const
{
	return m_currentOption;
}

//Set current setting option
void MenuOption::setCurrentOption( int value )
{
	if( m_numOfOptions ) //Checks if this option has any settings
	{
		if( value >= m_numOfOptions ) { value = 0; } //Checks if option setting id is valid
		if( value < 0 ) { value = m_numOfOptions - 1; }
		m_currentOption = value; //Sets current option
		m_optionSetting.deleteText(); //Deletes option setting name
		m_optionSetting.updateText( m_settingsString[value] ); //Sets new setting name
		m_optionSetting.draw(); //Draws it on the screen
	}
}

//Get num of option settings
int MenuOption::getNumOfOptions() const
{
	return m_numOfOptions;
}

//Set number of option settings
void MenuOption::setNumOfOptions( int value )
{
	m_numOfOptions = value;
}

 //Initialize option
void MenuOption::initialize( std::string optionName, Alignment alignment, int positionY, int numberOfOptions, int textAttribute )
{
	set( optionName, alignment, positionY, textAttribute ); //Sets option text
	m_numOfOptions = numberOfOptions;
	createOptionNames(); //Creates strings for option setting names
}

//Draws option setting
void MenuOption::drawOptionSetting()
{
	m_optionSetting.draw(); 
}

void MenuOption::setOptionSetting( std::string optionName, Alignment alignment, int positionY, int textAttribute )
{
	m_optionSetting.set( optionName,alignment, positionY, textAttribute );
}

void MenuOption::setOptionSettingAttribute( int textAttribute )
{
	m_optionSetting.setTextAttribute( textAttribute );
}

void MenuOption::setOptionName( int id , std::string optionName )
{
	if( id > -1 && id < m_numOfOptions ) //Makes sure that the option setting id is valid
	{
		m_settingsString[id] = optionName;
	}
}


void MenuOption::createOptionNames()
{
	if( m_numOfOptions ) //Makes sure that this option has at least one setting
	{
		m_settingsString = new std::string[m_numOfOptions];
	}
}


