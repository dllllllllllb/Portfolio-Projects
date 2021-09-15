//Author: Maciej Dowbor
//Module: MED5149
//Date last accessed: 20/01/2021

#include "BackgroundStar.h"

BackgroundStar::BackgroundStar( )
{
}

BackgroundStar::~BackgroundStar( )
{
}

void BackgroundStar::setUp( const sf::Texture &starTexture )
{
	setTexture( starTexture, true ); //Sets the texture and resets rectangle
	setOrigin( getLocalBounds( ).width * 0.5f, getLocalBounds( ).height * 0.5f ); //Sets origin to centre

	//Sets random position on the screen to the star
	float posX = rand( ) % k_windowSizeX;
	float posY = rand( ) % k_windowSizeY;
	setPosition( posX, posY );
}

void BackgroundStar::update( const float &deltaTime )
{
	//Moves the star down
	move( 0, k_backgroundStarSpeed * deltaTime );

	//Checks if the star is off the screen, makes a new random position and moves it to the top of the screen
	if( getPosition( ).y > k_starDespawnY )
	{
		float posX = rand( ) % k_windowSizeX;
		setPosition( posX, k_starSpawnY );
	}
}