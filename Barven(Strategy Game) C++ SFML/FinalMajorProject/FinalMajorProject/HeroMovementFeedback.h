#ifndef HEROMOVEMENTFEEDBACK_H
#define HEROMOVEMENTFEEDBACK_H

#include <vector>

#include "ConstantVariables.h"
#include "Textures.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class HeroMovementFeedback
{
private:
	sf::RenderWindow& m_window;

	sf::Sprite m_inRangeMovementIndicator;
	sf::Sprite m_outOfRangeMovementIndicator;

	sf::Sprite m_inRangeDestinationIndicator;
	sf::Sprite m_outOfRangeDestinationIndicator;

	int m_numOfPositionsInRange;
	std::vector<float> m_movementIndicatorRotations;
	std::vector<sf::Vector2f>* m_pMovementPositions;

	bool m_isActive;
	const int m_halfTileSize;
	int m_firstMovementIndicatorInRange;
public:

	HeroMovementFeedback(sf::RenderWindow& rWindow, Textures& rTextures);
	~HeroMovementFeedback();

	void setMovementPathFeedback(const int& numOfPositionsWithinRange, std::vector<sf::Vector2f>* pMovementPositionsVector);
	void calculateMovementIndicatorRotations();
	const float calculateRotationBetweenTwoPositions(const sf::Vector2f& posA, const sf::Vector2f& posB);

	void draw();

	void setIsActive(const bool state);
	void toggleIsActive();
	const bool getIsActive() const;

};

#endif // !HEROMOVEMENTFEEDBACK_H

