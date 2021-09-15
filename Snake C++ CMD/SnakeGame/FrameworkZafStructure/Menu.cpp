//Author: Maciej Dowbor
//Module: MED5148
//Date last accessed: 28/10/2020

#include "Menu.h"
#include <conio.h>
#include "Settings.h"

//Constructor
Menu::Menu()
{
	initialize(); //Initializes the menu
}

//Destructor
Menu::~Menu()
{
	delete m_bannerText;
	delete m_options;

}

//Detects players input
void Menu::detectInput()
{
	int temp = 0; //Temp variable to store and change menu option

	if( _kbhit() ) //Checks if a key is pressed
	{
		switch( _getch() ) //Checks which key is pressed and compares it to given options
		{
		case 'w': //Up
		case  72:
			m_menuID--; //Decrement menu ID
			checkIDValue(); //Check if ID value is valid
			break;
	
		case 's': //Down
		case  80:
			m_menuID++; //Increment menu ID
			checkIDValue(); //Check if ID value is valid
			break;
	
		case 'd': //Right
		case  77:
			temp = m_options[m_menuID].getCurrentOption(); //Stores current option for selected menu option
			temp++; //Increments it
			m_options[m_menuID].setCurrentOption( temp ); //Sets current menu option
			executeMenuOption(); //Executes menu option
			break;
	
		case 'a': //Left
		case  75:
			temp = m_options[m_menuID].getCurrentOption(); //Stores current option for selected menu option
			temp--; //Decrements it
			m_options[m_menuID].setCurrentOption( temp ); //Sets current menu option
			executeMenuOption(); //Executes menu option
			break;
	
		case 13: //Enter
			executeMenuOption(); //Executes menu option
			break;
	
		default:
			
			break;
		}
	}

}

//Executes menu option
void Menu::executeMenuOption()
{
	int option = m_options[m_menuID].getCurrentOption(); //Temp variable to store current menu option
	switch( m_menuID ) //Switches based on which menu option is selected
	{
	case 0: // Start
		g_gameState = GameState::game; //Sets game state to game
		break;

	case 1: // Game mode          not implemented yet, WIP

		switch( option )
		{
		case 0: //Classic
			
			break;

		case 1: 
			
			break;

		case 2:
			
			break;
		}
		break;

	case 2: // Difficulty

		switch( option )
		{
		case 0: //Normal
			difficulty = diffNormal; 
			m_difficultySettingString = "Normal"; 
			break;

		case 1: //Hard
			difficulty = diffHard;
			m_difficultySettingString = "Hard";
			break;

		case 2: //Easy
			difficulty = diffEasy;
			m_difficultySettingString = "Easy";
			break;
		}
		break;

	case 3: // High Score
		g_gameState = GameState::highscore;
		break;

	case 4: // Quit
		exit( 0 ); //Quits the application
		break;

	}
}

//Initializes the menu
void Menu::initialize()
{
	initializeOptions(); //Initializes the options
	drawOptions(); //Draws options
	initializeBanner(); //Initializes banner
	drawBanner(); //Draws banner
	difficulty = diffNormal; //Sets the difficulty to normal
	m_menuID = 0; //Sets menu ID to 0
	m_prevMenuID = 0; //Sets previous menu ID to 0
	m_difficultySettingString = "Normal"; //Sets difficulty name
	m_gamemodeSettingString = "Classic"; //Sets game mode name
}

//Gets difficulty string
std::string Menu::getDifficultyString()
{
	return m_difficultySettingString;
}

//Gets game mode string
std::string Menu::getGameModeString()
{
	return m_gamemodeSettingString;
}


//Changes color of option text
void Menu::selectMenuOption()
{
	m_options[m_prevMenuID].setTextAttribute( g_unselectedTextColour ); //Changes previous selected menu option color
	m_options[m_prevMenuID].setOptionSettingAttribute( g_unselectedTextColour );
	m_options[m_prevMenuID].draw(); //Draws it
	m_options[m_prevMenuID].drawOptionSetting();

	m_prevMenuID = m_menuID; //Sets previous menu ID to current ID

	m_options[m_menuID].setTextAttribute( g_selectedTextColour ); //Changes currently selected menu option color
	m_options[m_menuID].setOptionSettingAttribute( g_selectedTextColour );
	m_options[m_menuID].draw(); //Draws it
	m_options[m_menuID].drawOptionSetting();
}

//Checks if menu ID is valid
void Menu::checkIDValue()
{
	if( m_menuID > m_numOfOptions )
	{
		m_menuID = 0;
	}

	if (m_menuID == -1)
	{
		m_menuID = m_numOfOptions;
	}

	selectMenuOption(); //Changes color of option text
}

//Initialize options
void Menu::initializeOptions() 
{
	//Sets menu options
	m_options[0].initialize( "S T A R T", Alignment::middle, 16, 0, g_selectedTextColour );

	m_options[1].initialize( "G A M E  M O D E", Alignment::middle, 18, 1, g_unselectedTextColour );
	m_options[1].setOptionSetting( "<<<  C L A S S I C  >>>", Alignment::middle, 19, g_unselectedTextColour );
	m_options[1].setOptionName( 0, "<<<  C L A S S I C  >>>" );

	m_options[2].initialize( "D I F F I C U L T Y", Alignment::middle, 21, 3, g_unselectedTextColour );
	m_options[2].setOptionSetting(  "<<<  N O R M A L  >>>", Alignment::middle, 22, g_unselectedTextColour );
	m_options[2].setOptionName( 0 , "<<<  N O R M A L  >>>" );
	m_options[2].setOptionName( 1 , "<<<  H A R D  >>>" );
	m_options[2].setOptionName( 2 , "<<<  E A S Y  >>>" );

	m_options[3].initialize( "H I G H  S C O R E S", Alignment::middle, 24, 0, g_unselectedTextColour );

	m_options[4].initialize( "Q U I T", Alignment::middle, 26, 0, g_unselectedTextColour );

	
}
//Initializes banner
void Menu::initializeBanner()
{
	m_bannerText[0].set ( "   _______  _______  __    _  _______  _______  ___      _______    _______  __    _  _______  ___   _  _______ ", Alignment::middle, 4 , 13);
	m_bannerText[1].set ( "  |       ||       ||  |  | ||       ||       ||   |    |       |  |       ||  |  | ||   _   ||   | | ||       |", Alignment::middle, 5 , 13);
	m_bannerText[2].set ( "  |       ||   _   ||   |_| ||  _____||   _   ||   |    |    ___|  |  _____||   |_| ||  |_|  ||   |_| ||    ___|", Alignment::middle, 6 , 13);
	m_bannerText[3].set ( "  |       ||  | |  ||       || |_____ |  | |  ||   |    |   |___   | |_____ |       ||       ||      _||   |___ ", Alignment::middle, 7 , 13);
	m_bannerText[4].set ( "  |      _||  |_|  ||  _    ||_____  ||  |_|  ||   |___ |    ___|  |_____  ||  _    ||       ||     |_ |    ___|", Alignment::middle, 8 , 13);
	m_bannerText[5].set ( "  |     |_ |       || | |   | _____| ||       ||       ||   |___    _____| || | |   ||   _   ||    _  ||   |___ ", Alignment::middle, 9 , 13);
	m_bannerText[6].set ( "  |_______||_______||_|  |__||_______||_______||_______||_______|  |_______||_|  |__||__| |__||___| |_||_______|", Alignment::middle, 10, 13);
}

//Draws options
void Menu::drawOptions()
{
	for( int i = 0; i < m_numOfOptions + 1; i++) //Loops based on number of options
	{
		m_options[i].draw(); //Draws the option
		m_options[i].drawOptionSetting(); //Draws option setting
	}
}

//Draws banner
void Menu::drawBanner()
{
	for( int i = 0; i < m_bannerRows; i++ ) //Loops based on number of banner rows
	{
		m_bannerText[i].draw(); //Draws a banner segment
	}
}
