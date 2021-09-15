//Author: Maciej Dowbor
//Module: MED5149
//Date last accessed: 20/01/2021

#include "Object.h"

Object::Object( ) :
	m_collisionOffSet	( 0 ),
	m_isActive			( true )
{
}

Object::~Object( )
{
}

void Object::load( const sf::Texture &texture )
{
	//Set the texture
	setTexture( texture, true );

	//Set textures origin to centre
	setOrigin( getLocalBounds( ).width * 0.5f, getLocalBounds( ).height * 0.5f );

	//Set position offset
	m_collisionOffSet = getTexture( )->getSize( ).x * 0.5f + 8;
}

bool Object::collisionCheck( const sf::Vector2f &otherObjectPosition )
{
	//Temporary stores x and y position to not call it multiple times
	float thisX = getPosition( ).x;
	float thisY = getPosition( ).y; 

	//Checks if the other object position is within this objects collision boundries and returns the result 
	return ( otherObjectPosition.x <= thisX + m_collisionOffSet &&
			 otherObjectPosition.x >= thisX - m_collisionOffSet &&
			 otherObjectPosition.y >= thisY - m_collisionOffSet &&
			 otherObjectPosition.y <= thisY + m_collisionOffSet );
}

void Object::toggleState( )
{
	m_isActive = !m_isActive; //Toggles bool state to the opposite to what it is
}

const bool Object::getActiveState( ) const
{
	return m_isActive;
}