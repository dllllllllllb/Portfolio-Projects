#include "AnimatedObject.h"
AnimatedObject::AnimatedObject(sf::RenderWindow& rWindow) :
	m_window(rWindow),
	m_isAnimating(false),
	m_isLooping(false),
	m_numberOfFrames(0),
	m_frameCounter(0),
	m_textureWidth(0),
	m_textureHeight(0),
	m_frameTimer(0),
	m_timeBetweenEachFrame(0)
{
}

AnimatedObject::~AnimatedObject()
{
}

void AnimatedObject::setUpAnimation(sf::Texture& spriteSheet, const int& textureWidth, const int& textureHeight, const int& framesPerSecond, const bool isLooping, const bool setOriginToCentre)
{
	m_textureWidth = textureWidth;
	m_textureHeight = textureHeight;
	m_isLooping = isLooping;
	float tempFramesPerSecond = framesPerSecond;
	m_timeBetweenEachFrame = 1 / tempFramesPerSecond;
	setTexture(spriteSheet);
	m_numberOfFrames = getGlobalBounds().width / textureWidth;
	setTextureRect(sf::IntRect(0, 0, textureWidth, textureHeight));

	if (setOriginToCentre)
	{
		setOrigin(textureWidth * 0.5f, textureHeight * 0.5f);
	}
}

void AnimatedObject::startAnimation()
{
	m_isAnimating = true;
	setTextureRect(sf::IntRect(0, 0, m_textureWidth, m_textureHeight));
	m_frameCounter = 0;
	m_frameTimer = 0;
}

void AnimatedObject::stopAnimation()
{
	m_isAnimating = false;
}

void AnimatedObject::updateAnimation(const float& deltaTime)
{
	if (m_isAnimating)
	{
		m_frameTimer += deltaTime;

		if (m_frameTimer >= m_timeBetweenEachFrame)
		{
			m_frameTimer = 0; //Reset frame timer
			m_frameCounter++; 

			if (m_frameCounter >= m_numberOfFrames) //Checks if animation is complete
			{
				m_frameCounter = 0; //Resets frame counter

				if (!m_isLooping) //If animation is not set to loop, end it
				{
					stopAnimation();
				}
			}

			int rectLeft = 0 + m_frameCounter * m_textureWidth; //Calculate texture rectangle to show appropriate frame

			setTextureRect(sf::IntRect(rectLeft, 0, m_textureWidth, m_textureHeight));
		}
	}
}

void AnimatedObject::drawAnimation()
{
	if (m_isAnimating)
	{
		m_window.draw(*this);
	}
}