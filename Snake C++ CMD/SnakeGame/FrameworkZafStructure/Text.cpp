//Author: Maciej Dowbor
//Module: MED5148
//Date last accessed: 28/10/2020

#include "Text.h"

//Updates text length
void Text::updateTextLength()
{
	m_length = int( m_text.length() );
}

//Constructor
Text::Text()
	:m_text(""),
	 m_posX(0),
	 m_posY(0),
	 m_alignment(Alignment::middle)
{
	m_position.setPosition( m_posX, m_posY );
	updateTextLength();
}

//Constructor
Text::Text( std::string text, Alignment alignment, int posY )
	:m_text(text),
	 m_alignment(alignment),
	 m_posY(posY)
{
	updateTextLength();
}

//Destructor
Text::~Text()
{

}

//Sets text variables
void Text::set( std::string text, Alignment alignment, int posY, int textAttribute )
{
	m_text = "";
	m_text = text;
	m_alignment = alignment;
	m_posY = posY;
	m_textAttribute = textAttribute;
	updateTextLength();
}

//Aligns text
void Text::alignText()
{
	switch( m_alignment )
	{
	case Alignment::left:
		m_posX = g_borderOriginX;
		m_position.setPosition( m_posX, m_posY );
		break;

	case Alignment::middle:
		m_posX = m_boardMiddle - int( trunc( m_length / 2 ) );
		m_position.setPosition( m_posX, m_posY );
		break;

	case Alignment::right:
		m_posX = g_borderOriginX + g_borderSizeX - m_length;
		m_position.setPosition( m_posX, m_posY );
		break;

	case Alignment::highScore:
		m_posX = g_borderOriginX + ( ( g_borderSizeX / 2 ) - 6 );
		m_position.setPosition( m_posX, m_posY );
		break;
	}
}

//Draws text on the screen
void Text::draw()
{
	alignText();

	for( int i = 0; i < m_length; i++ ) //Loops based on text length
	{
		drawChar( m_text[i], m_position, m_textAttribute ); //Draws a character every loop
		m_position.x++; //Increments x position
	}
}

//Updates text with ints
void Text::updateText( int value )
{
	m_text += std::to_string( value ); //Adds int to the string
	updateTextLength();
}

//Updates text with string
void Text::updateText( std::string text )
{
	m_text += text;
	updateTextLength();
}

//Deletes text and erases it
void Text::deleteText()
{
	for( int i = 0; i <= m_length; i++) //Loops based on text length
	{
		drawChar( ' ', m_position, m_textAttribute ); //Draws an empty space over every char in the string
		m_position.x--;
	}

	m_text = ""; //Deletes the text
	m_length = 0; //Resets length to 0
}

//Delete char
void Text::deleteLastChar( int charsToDelete )
{
	if( charsToDelete < m_length ) //If there is no text to delete, it will still try to delete it and throw an error, makes sure that doesn't happen
	{			   
		//Deletes text
		for( int i = 0; i <= m_length; i++ )
		{
			drawChar( ' ', m_position, m_textAttribute );
			m_position.x--;
		}

		for( int i = 0; i < charsToDelete; i++ ) //Removes last chars from the string
		{
			m_text.pop_back();
		}
		m_length -= charsToDelete; //Decrements string length
	}
}

//Changes text color
void Text::setTextAttribute( int textAttribute )
{
	m_textAttribute = textAttribute;
}

//Sets y coordinate
void Text::setPositionY( int value )
{
	m_posY = value;
}

//Deletes text
void Text::clearText()
{
	m_text = "";
}
