#include "HeroMovementFeedback.h"

HeroMovementFeedback::HeroMovementFeedback(sf::RenderWindow& rWindow, Textures& rTextures) :
	m_window(rWindow),
	m_numOfPositionsInRange(0),
	m_pMovementPositions(nullptr),
	m_isActive(false),
	m_halfTileSize(c_tileSize * 0.5f)
{
	m_inRangeMovementIndicator.setTexture(rTextures.m_heroMovementFeedback[0], true);
	m_outOfRangeMovementIndicator.setTexture(rTextures.m_heroMovementFeedback[1], true);

	m_inRangeDestinationIndicator.setTexture(rTextures.m_heroMovementFeedback[2], true);
	m_outOfRangeDestinationIndicator.setTexture(rTextures.m_heroMovementFeedback[3], true);

	m_inRangeMovementIndicator.setOrigin(m_halfTileSize, m_halfTileSize); //Indicators are 32x32 just like tiles
	m_outOfRangeMovementIndicator.setOrigin(m_halfTileSize, m_halfTileSize);
}

HeroMovementFeedback::~HeroMovementFeedback()
{

}

void HeroMovementFeedback::setMovementPathFeedback(const int& numOfPositionsWithinRange, std::vector<sf::Vector2f>* pMovementPositionsVector)
{
	m_isActive = true;
	m_numOfPositionsInRange = numOfPositionsWithinRange;
	m_pMovementPositions = pMovementPositionsVector;
	calculateMovementIndicatorRotations();
	m_firstMovementIndicatorInRange = pMovementPositionsVector->size() - numOfPositionsWithinRange;

	if (m_firstMovementIndicatorInRange < 0)
	{
		m_firstMovementIndicatorInRange = 0;
	}
}

void HeroMovementFeedback::calculateMovementIndicatorRotations()
{
	int vectorSize = m_pMovementPositions->size();
	m_movementIndicatorRotations.clear();
	m_movementIndicatorRotations.push_back(0); //Destination tile rotation

	for (int i = 1; i < vectorSize - 1; i++) //Last one needs to be calculated using heroPosition
	{
		//PosA is start tile, PosB is destination tile
		m_movementIndicatorRotations.push_back(calculateRotationBetweenTwoPositions(m_pMovementPositions->at(i), m_pMovementPositions->at(i - 1)));
	}
	m_movementIndicatorRotations.push_back(0);
}

const float HeroMovementFeedback::calculateRotationBetweenTwoPositions(const sf::Vector2f& posA, const sf::Vector2f& posB)
{
	int differenceX = static_cast<int>(posB.x - posA.x);
	int differenceY = static_cast<int>(posB.y - posA.y);
	float rotation = 0.0f;

	if (differenceX == -c_tileSize && differenceY == -c_tileSize) //North west
	{
		rotation = -45;
	}
	else if (differenceX == -c_tileSize && differenceY == 0) //West
	{
		rotation = -90;
	}
	else if (differenceX == -c_tileSize && differenceY == c_tileSize) //South west
	{
		rotation = -135;
	}
	else if (differenceX == 0 && differenceY == -c_tileSize) //North
	{
		rotation = 0;
	}
	else if (differenceX == 0 && differenceY == c_tileSize) //South
	{
		rotation = 180;
	}
	else if (differenceX == c_tileSize && differenceY == -c_tileSize) //North east
	{
		rotation = 45;
	}
	else if (differenceX == c_tileSize && differenceY == 0) //east
	{
		rotation = 90;
	}
	else if (differenceX == c_tileSize && differenceY == c_tileSize) //South east
	{
		rotation = 135;
	}

	return rotation;
}

void HeroMovementFeedback::draw()
{
	if (m_isActive)
	{
		int vectorSize = m_pMovementPositions->size() - 1;
		if (0 >= m_firstMovementIndicatorInRange)
		{
			m_inRangeDestinationIndicator.setPosition(m_pMovementPositions->at(0));
			m_window.draw(m_inRangeDestinationIndicator);
		}
		else
		{
			m_outOfRangeDestinationIndicator.setPosition(m_pMovementPositions->at(0));
			m_window.draw(m_outOfRangeDestinationIndicator);
		}

		for (int i = 1; i < vectorSize; i++)
		{
			if (i >= m_firstMovementIndicatorInRange)
			{
				m_inRangeMovementIndicator.setPosition(m_pMovementPositions->at(i).x + m_halfTileSize, m_pMovementPositions->at(i).y + m_halfTileSize);
				m_inRangeMovementIndicator.setRotation(m_movementIndicatorRotations[i]);
				m_window.draw(m_inRangeMovementIndicator);
			}
			else
			{
				m_outOfRangeMovementIndicator.setPosition(m_pMovementPositions->at(i).x + m_halfTileSize, m_pMovementPositions->at(i).y + m_halfTileSize);
				m_outOfRangeMovementIndicator.setRotation(m_movementIndicatorRotations[i]);
				m_window.draw(m_outOfRangeMovementIndicator);
			}
		}
	}
}

void HeroMovementFeedback::setIsActive(const bool state)
{
	m_isActive = state;
}

void HeroMovementFeedback::toggleIsActive()
{
	m_isActive = !m_isActive;
}

const bool HeroMovementFeedback::getIsActive() const
{
	return m_isActive;
}
