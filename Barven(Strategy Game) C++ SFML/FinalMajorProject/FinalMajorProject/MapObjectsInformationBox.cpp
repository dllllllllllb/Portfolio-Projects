#include "MapObjectsInformationBox.h"

MapObjectsInformationBox::MapObjectsInformationBox(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts) : 
	m_mapObjectsInformationBox(rWindow, &rTextures, &rFonts),
	m_isActive(false)
{
	//Set up information box
	m_mapObjectsInformationBox.setPosition(0, 0);
	m_mapObjectsInformationBox.setPopUpWidth(300);
}

MapObjectsInformationBox::~MapObjectsInformationBox()
{
}

void MapObjectsInformationBox::setInformation(const sf::Vector2f& position, std::string& contentText)
{
	m_isActive = true;
	m_mapObjectsInformationBox.setPosition(position);
	m_mapObjectsInformationBox.setUpPopUp(contentText);
}

void MapObjectsInformationBox::update()
{
	if (m_isActive && !sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
	{
		m_isActive = false;
	}
}

void MapObjectsInformationBox::draw()
{
	if (m_isActive)
	{
		m_mapObjectsInformationBox.drawPopUpBox();
	}
}

const bool MapObjectsInformationBox::getIsActive() const
{
	return m_isActive;
}
