//Author: Zafar Qamar & Maciej Dowbor
//Module: MED5148
//Date last accessed: 28/10/2020

#include <iostream>
#include <Windows.h>

#include "Helpers.h"

//Goes to specific place in the console and sets console text attribute
void gotoXY( int x, int y, int i )
{
	HANDLE hStdout = GetStdHandle( STD_OUTPUT_HANDLE ); //Gets output handle
	COORD position = { ( SHORT )x, ( SHORT )y }; //Sets position based on given x and y coordinates
	SetConsoleTextAttribute( hStdout, i ); //Sets console text attribute
	SetConsoleCursorPosition( hStdout, position ); //Goes to set position
}

void drawChar( char c, Vector2 position, int textAttribute ) //Draws a character in the console at a specific position
{
	gotoXY( position.getX(), position.getY(), textAttribute ); //Goes to specific place in the console and sets console text attribute
	std::cout << c; //Prints the character
}