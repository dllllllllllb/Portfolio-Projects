//Author: Maciej Dowbor
//Last Accessed: 02/08/2021

#ifndef ANIMATEDOBJECT_H
#define ANIMATEDOBJECT_H

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

//===========================================================================================
//Description: Base class for objects that have simple animations
//===========================================================================================
class AnimatedObject : public virtual sf::Sprite
{
private:
	sf::RenderWindow& m_window;
	bool m_isAnimating;
	bool m_isLooping;

	int m_numberOfFrames;
	int m_frameCounter;
	int m_textureWidth;
	int m_textureHeight;

	double m_frameTimer;
	double m_timeBetweenEachFrame;

public:

	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	AnimatedObject(sf::RenderWindow& rWindow);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~AnimatedObject();

	//===========================================================================================
	//Description: Sets animation parameters and sets up first animation frame
	//===========================================================================================
	void setUpAnimation(sf::Texture& spriteSheet, const int& textureWidth, const int& textureHeight, const int& framesPerSecond, const bool isLooping, const bool setOriginToCentre);

	//===========================================================================================
	//Description: Sets animation parameters to first frame and starts animation
	//===========================================================================================
	void startAnimation();

	//===========================================================================================
	//Description: Stops animation
	//===========================================================================================
	void stopAnimation();

	//===========================================================================================
	//Description: Updates which animation frame to show based on time passed, once the animation
	//			   ends and is not set to loop, the animation will end. Only updates if animation
	//			   is active.
	//===========================================================================================
	void updateAnimation(const float& deltaTime);

	//===========================================================================================
	//Description: Draws current frame if animation is active
	//===========================================================================================
	void drawAnimation();
};

#endif // !ANIMATEDOBJECT_H
