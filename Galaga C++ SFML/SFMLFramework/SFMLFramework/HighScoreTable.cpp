//Author: Maciej Dowbor
//Module: MED5149
//Date last accessed: 20/01/2021

#include "HighScoreTable.h"

HighScoreTable::HighScoreTable( sf::RenderWindow &window, Textures *textures ) :
	m_fileName	( k_highScoreFileName ),
	m_window	( window ),
	m_pTextures	( textures )
{
	m_pHighScoreData	= new HighScoreData[k_numOfHighScores];
	m_pHighScores		= new sf::Text[k_numOfHighScores];

	readData( );
	setUpText( );

	m_exitButton.setUp( "Menu", m_pTextures->m_menuFont, k_characterSize, m_pTextures->m_button, k_exitButtonPosition.x, k_exitButtonPosition.y );
	m_exitButtonText = m_exitButton.getText( );
}

HighScoreTable::~HighScoreTable( )
{
	delete[] m_pHighScoreData;
	m_pHighScoreData = nullptr;

	delete[] m_pHighScores;
	m_pHighScores = nullptr;
}

void HighScoreTable::readData( )
{
	m_highScoreFileIn.open( m_fileName );

	if( m_highScoreFileIn.is_open( ) ) //Checks if the file is actually open
	{
		std::string wordBuffer; //Temp variable to store a word from the txt file
		int x = 0; //Temp variable to store ints from txt file

		for( int i = 0; i < k_numOfHighScores; i++ ) //Loops based on high score length
		{
			for( int z = 0; z < 2; z++ ) // z = 0 for players name, z = 1 for players score
			{
				if( z == 0 )
				{
					m_highScoreFileIn >> wordBuffer; //Gets a word from the txt file and stores it
					m_pHighScoreData[i].setName( wordBuffer ); //Sets players name in the high score variable
				}
				else
				{
					m_highScoreFileIn >> wordBuffer; //Gets a word from the txt file
					std::stringstream stringToInt( wordBuffer ); //Because the score is stored as a string in the txt file, it has to be converted to int
					stringToInt >> x; //Sets the int value to the x variable
					m_pHighScoreData[i].setScore( x ); //Sets score to the corresponding player name
				}
			}
		}
		m_highScoreFileIn.close( ); //Closes the file
	}

	updateText( );
}

void HighScoreTable::writeData( )
{
	m_highScoreFileOut.open( m_fileName, std::ios::trunc ); //Opens up the file and deletes its contents to write new data

	if( m_highScoreFileOut.is_open( ) ) //Checks if the file is open
	{
		for( int i = 0; i < k_numOfHighScores; i++ ) //Loops based on the high score length
		{
			for( int z = 0; z < 2; z++ ) // z = 0 for players name, z = 1 for players score
			{
				if( z == 0 )
				{
					m_highScoreFileOut << m_pHighScoreData[i].getName( ); //Writes players name into the txt file
					m_highScoreFileOut << " "; //Adds a space after writing it to make sure that each word in the text file can be read individually
				}
				else
				{
					m_highScoreFileOut << m_pHighScoreData[i].getScore( ); //Writes players score into the txt file
					m_highScoreFileOut << "\n"; //Makes a new line for the ease of reading it when opening the text file manually
				}
			}
		}

		m_highScoreFileOut.close( ); //Closes the file
	}
}

void HighScoreTable::sortTable( const std::string &name, const int &score )
{
	int tempScore = score;
	int tempScore2 = 0;

	std::string tempString = name;
	std::string tempString2 = "";


	//Loops through all high scores and compares them to new score
	for( int i = 0; i < k_numOfHighScores; i++ )
	{
		if( tempScore > m_pHighScoreData[i].getScore( ) )
		{
			tempScore2 = m_pHighScoreData[i].getScore( ); //Stores lower score and name in temp variables
			tempString2 = m_pHighScoreData[i].getName( );

			m_pHighScoreData[i].setScore( tempScore ); //Sets new score 
			m_pHighScoreData[i].setName( tempString ); //Sets new name 

			tempScore = tempScore2; //Sets old name and score to a variable that is compared every iteration
			tempString = tempString2;
		}
	}
	writeData( );
}

void HighScoreTable::setUpText( )
{
	m_HighScoreBanner.setFont( m_pTextures->m_font );
	m_HighScoreBanner.setCharacterSize( k_highScoreBannerFontSize );;
	m_HighScoreBanner.setString( k_highScoreBannerText );
	m_HighScoreBanner.setOrigin( m_HighScoreBanner.getLocalBounds( ).width * 0.5f, m_HighScoreBanner.getLocalBounds( ).height * 0.5f );
	m_HighScoreBanner.setPosition( k_highScoreTextPositionX, k_highScoreBannerPositionY );

	int tempPosY = k_highScoreTextPositionY;

	for( int i = 0; i < k_numOfHighScores; i++ )
	{
		m_pHighScores[i].setFont( m_pTextures->m_font );
		m_pHighScores[i].setCharacterSize( k_highScoreFontSize );
		m_pHighScores[i].setString( std::to_string( i + 1 ) + ". Name: " + m_pHighScoreData[i].getName( ) + "       Score: " + std::to_string( m_pHighScoreData[i].getScore( ) ) );
		m_pHighScores[i].setOrigin( m_pHighScores[i].getLocalBounds( ).width * 0.5f, m_pHighScores[i].getLocalBounds( ).height * 0.5f );
		m_pHighScores[i].setPosition( k_highScoreTextPositionX, tempPosY );
		tempPosY += k_highScoreTextSpacing;
	}
}

void HighScoreTable::updateText( )
{
	int tempPosY = k_highScoreTextPositionY;

	for( int i = 0; i < k_numOfHighScores; i++ )
	{
		m_pHighScores[i].setString( std::to_string( i + 1 ) + ". Name: " + m_pHighScoreData[i].getName( ) + "       Score: " + std::to_string( m_pHighScoreData[i].getScore( ) ) );
		m_pHighScores[i].setOrigin( m_pHighScores[i].getLocalBounds( ).width * 0.5f, m_pHighScores[i].getLocalBounds( ).height * 0.5f );
		m_pHighScores[i].setPosition( k_highScoreTextPositionX, tempPosY );
		tempPosY += k_highScoreTextSpacing;
	}
}

void HighScoreTable::draw( )
{
	m_window.draw( m_HighScoreBanner );

	for( int i = 0; i < k_numOfHighScores; i++ )
	{
		m_window.draw( m_pHighScores[i] );
	}

	m_window.draw( m_exitButton );
	m_window.draw( *m_exitButtonText );
}

void HighScoreTable::update( )
{
	if( m_exitButton.checkMouseCollision( m_mouse.getPosition( m_window ) ) && m_mouse.isButtonPressed( sf::Mouse::Button::Left ) )
	{
		g_gameState = GameState::menu;
	}
}