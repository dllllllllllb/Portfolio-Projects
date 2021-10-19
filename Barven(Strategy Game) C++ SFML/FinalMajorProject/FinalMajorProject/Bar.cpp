#include "Bar.h"

Bar::Bar(sf::RenderWindow& rWindow, Textures& rTextures) :
	m_window(rWindow)
{
	m_bar.setTexture(rTextures.m_UIBar, true);
	m_barEndLeft.setTexture(rTextures.m_UIBarEnding, true);
	m_barEndRight.setTexture(rTextures.m_UIBarEnding, true);
}

Bar::~Bar()
{
}

void Bar::setUp(const int& width, const int& height, const int& positionX, const int& positionY)
{
	float barTextureWidth = static_cast<float>( m_bar.getTexture()->getSize().x);
	float barTextureHeight = m_bar.getTexture()->getSize().y;

	float widthScale = width / barTextureWidth;
	float heightScale = height / barTextureHeight;
	
	//Sets scale
	m_bar.setScale(widthScale, -heightScale);
	m_barEndLeft.setScale(heightScale, -heightScale);
	m_barEndRight.setScale(-heightScale, -heightScale);

	//Sets origin
	m_bar.setOrigin(m_bar.getLocalBounds().width * 0.5f, m_bar.getLocalBounds().height * 0.5f);
	m_barEndLeft.setOrigin(m_barEndLeft.getLocalBounds().width * 0.5f, m_barEndLeft.getLocalBounds().height * 0.5f);
	m_barEndRight.setOrigin(m_barEndRight.getLocalBounds().width * 0.5f, m_barEndRight.getLocalBounds().height * 0.5f);

	//Sets position
	m_bar.setPosition(positionX, positionY);
	float halfBarWidth = m_bar.getLocalBounds().width * 0.5f;
	float halfBarEndingWidth = m_barEndLeft.getGlobalBounds().width * 0.3f;

	m_barEndLeft.setPosition(positionX - halfBarWidth + halfBarEndingWidth, positionY - 1);
	m_barEndRight.setPosition(positionX + halfBarWidth - halfBarEndingWidth, positionY - 1);
}

const sf::Vector2f& Bar::getPosition()
{
	return m_bar.getPosition();
}

void Bar::draw()
{
	m_window.draw(m_bar);
	m_window.draw(m_barEndLeft);
	m_window.draw(m_barEndRight);
}
