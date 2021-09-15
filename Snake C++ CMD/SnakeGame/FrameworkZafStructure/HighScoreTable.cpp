#include "HighScoreTable.h"

//Constructor
HighScoreTable::HighScoreTable()
	:m_playerName(""), //Sets players name to nothing
	 m_score(0), //Sets score to 0
	 m_HighScoreFile("HighScore.txt") //Sets the name of the txt file to which data will be written to and read from
{
	initializeBanner(); //Initializes the banner
}


//Destructor
HighScoreTable::~HighScoreTable()
{

}

//Read data from the txt file and store it in m_highScores
void HighScoreTable::readData()
{
	m_highScoreFileIn.open( m_HighScoreFile); //Opens txt file

	if( m_highScoreFileIn.is_open() ) //Checks if the file is actually open
	{
		std::string wordBuffer; //Temp variable to store a word from the txt file
		int x = 0; //Temp variable to store ints from txt file

		for( int i = 0; i < m_highScoreLength; i++ ) //Loops based on high score length
		{
			for( int z = 0; z < 2; z++ ) // z = 0 for players name, z = 1 for players score
			{
				if( z == 0 )
				{
					m_highScoreFileIn >> wordBuffer; //Gets a word from the txt file and stores it
					m_highScores[i].setName( wordBuffer ); //Sets players name in the high score variable
				}
				else
				{
					m_highScoreFileIn >> wordBuffer; //Gets a word from the txt file
					std::stringstream stringToInt( wordBuffer ); //Because the score is stored as a string in the txt file, it has to be converted to int
					stringToInt >> x; //Sets the int value to the x variable
					m_highScores[i].setScore( x ); //Sets score to the corresponding player name
				}

			}

		}
		m_highScoreFileIn.close(); //Closes the file

	}
}
// Writes stored data to a text document
void HighScoreTable::writeData() 
{
	m_highScoreFileOut.open( m_HighScoreFile, std::ios::trunc ); //Opens up the file and deletes its contents to write new data

	if( m_highScoreFileOut.is_open() ) //Checks if the file is open
	{
		for( int i = 0; i < m_highScoreLength; i++ ) //Loops based on the high score length
		{
			for (int z = 0; z < 2; z++ ) // z = 0 for players name, z = 1 for players score
			{
				if( z == 0 )
				{
					m_highScoreFileOut << m_highScores[i].getName(); //Writes players name into the txt file
				    m_highScoreFileOut << " "; //Adds a space after writing it to make sure that each word in the text file can be read individually
				}
				else
				{
					m_highScoreFileOut << m_highScores[i].getScore(); //Writes players score into the txt file
					m_highScoreFileOut << "\n"; //Makes a new line for the ease of reading it when opening the text file manually
				}
			}
		}

		m_highScoreFileOut.close(); //Closes the file
	}
}

//Sets up banner text
void HighScoreTable::initializeBanner()
{
	//Sets banners "graphic", aligns it to the middle of the screen, sets its Y coordinate and sets its color
	m_banner[0].set( " __   __  ___   _______  __   __    _______  _______  _______  ______    _______  _______ ", Alignment::middle, 4, 13 );
	m_banner[1].set( "|  | |  ||   | |       ||  | |  |  |       ||       ||       ||    _ |  |       ||       |", Alignment::middle, 5, 13 );
	m_banner[2].set( "|  |_|  ||   | |    ___||  |_|  |  |  _____||       ||   _   ||   | ||  |    ___||  _____|", Alignment::middle, 6, 13 );
	m_banner[3].set( "|       ||   | |   | __ |       |  | |_____ |       ||  | |  ||   |_||_ |   |___ | |_____ ", Alignment::middle, 7, 13 );
	m_banner[4].set( "|       ||   | |   ||  ||       |  |_____  ||      _||  |_|  ||    __  ||    ___||_____  |", Alignment::middle, 8, 13 );
	m_banner[5].set( "|   _   ||   | |   |_| ||   _   |   _____| ||     |_ |       ||   |  | ||   |___  _____| |", Alignment::middle, 9, 13 );
	m_banner[6].set( "|__| |__||___| |_______||__| |__|  |_______||_______||_______||___|  |_||_______||_______|", Alignment::middle, 10, 13 );
}

//Draws the table
void HighScoreTable::drawTable()
{
	int posY = m_tablePositionY; //Temp var to store Y coordinate
	m_textToDraw.set( "1. " + m_highScores[0].getName() + " " + std::to_string( m_highScores[0].getScore() ), Alignment::highScore, posY, 15 ); //Sets the first line of text
	m_textToDraw.draw(); //Draws the text onto the screen                                                                                       //Its outside of the loop below because it also sets the text allignment and color which needs to be set only once

	for( int i = 1; i < m_highScoreLength; i++ ) //Loops based on high score length
	{
		m_textToDraw.clearText(); //Deletes the previous text
		m_textToDraw.updateText( std::to_string( i + 1 ) + ". " + m_highScores[i].getName() + " " + std::to_string( m_highScores[i].getScore() ) ); //Sets new text
		posY ++; //Increases the position by 1 to draw the text new text below the prior
		m_textToDraw.setPositionY( posY ); //Sets new position
		m_textToDraw.draw(); //Draws the text onto the screen
	}
}

//Draws banner
void HighScoreTable::drawBanner()
{
	for( int i = 0; i < 7; i++ ) //Loops based on banner height
	{
		m_banner[i].draw(); //Draws banner segment
	}
}

//Player enters their name
void HighScoreTable::enterName()
{
	m_textToDraw.clearText(); //Clears previous text
	m_textToDraw.updateText( "Player name: " ); //Sets the new text
	m_textToDraw.setPositionY( m_nameInputPosY ); //Sets new y position
	m_textToDraw.draw(); //Draws it on the screen
	std::cin >> m_playerName; //Waits for player input and stores it
	sortTable(); //Sorts the table
	writeData(); //Writes data in the txt file
	g_gameState = GameState::menu; //Changes the game state to menu taking the player to the menu
} 


//Sorts high scores in descending order
void HighScoreTable::sortTable()
{
	for( int i = 9; i >= 0; i-- ) //Loops based on high score length -1
	{
		if( m_score <= m_highScores[i].getScore() ) //If the score is lower than the lowest score, it won't be saved
		{
			break; //Breaks the loop
		}
		else
		{
			if( i == 9 ) //If the current score is compared to the last place in the high score table and its higher, old score is replaced by the new score
			{
				
				m_highScores[i].setName( m_playerName ); //Sets players name
				m_highScores[i].setScore( m_score ); //Sets players score
			}
			else //If the current score is not compared to the last place in the table and its higher, the old score is stored in a temp variable, new score is written in its place and the old score is moved down in the table
			{
				std::string tempName = m_highScores[i].getName(); //Stores players name in temp variable
				int tempScore = m_highScores[i].getScore(); //Stores players score in temp variable

				m_highScores[i].setName( m_playerName ); //Sets players name to the high score place its comparing to
				m_highScores[i].setScore( m_score ); //Sets players score to the high score place its comparing to

				int x = i + 1;
				m_highScores[x].setName( tempName ); //Moves previous player name down the table
				m_highScores[x].setScore( tempScore ); //Moves previous player score down the table
			}
		}
	}
}

//Gets players score
void HighScoreTable::getScore( int score )
{
	m_score = score; //Sets players score to local variable
}

//Detects input
void HighScoreTable::detectInput()
{
	if( _kbhit() ) //Checks if a key is pressed
	{
		if( _getch() == 13 ) //Compares if the key pressed is enter
		{
			g_gameState = GameState::menu; //Sets the game state to menu
		}
	}
}

//Initializes the high score table
void HighScoreTable::initialize()
{
	readData();
	initializeBanner();
	drawBanner();
	drawTable();
}

