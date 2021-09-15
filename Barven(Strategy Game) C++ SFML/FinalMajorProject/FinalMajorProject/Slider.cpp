#include "Slider.h"

Slider::Slider(sf::RenderWindow& rWindow, Textures* pTextures, const bool isSliderHorizontal) :
	UIElement(rWindow, pTextures, true),
	m_isHorizontal(isSliderHorizontal),
	m_isActive(false),
	m_value(1),
	m_initialHandlePosX(0),
	m_initialHandlePosY(0),
	m_initialBarPosX(0),
	m_initialBarPosY(0),
	m_barWidth(0),
	m_barHeight(0),
	m_barTextureRectWidth(0),
	m_barTextureRectHeight(0)
{

}

Slider::~Slider()
{
}

void Slider::setUpSlider(const int& positionX, const int& positionY, const int& width, const int& height)
{
	UIElement::setPosition(positionX, positionY);
	setUpUIBorder(width, height);

	m_bar.setTexture(m_pTextures->m_sliderBar, true);
	m_bar.setOrigin(0, m_bar.getGlobalBounds().height * 0.5f);

	m_handle.setTexture(m_pTextures->m_sliderHandle, true);
	m_handle.sf::Sprite::setOrigin(m_handle.getGlobalBounds().width * 0.5f, m_handle.getGlobalBounds().height * 0.5f);

	resizeSliderElements(width, height);

	if (m_isHorizontal)
	{
		m_bar.setPosition(positionX - UIElement::getGlobalBounds().width * 0.5f, positionY);
		m_handle.setPosition(m_bar.getPosition().x + m_bar.getGlobalBounds().width, positionY);
		m_handle.setCollisionBounds(m_handle.sf::Sprite::getGlobalBounds().width, m_handle.sf::Sprite::getGlobalBounds().height);
	}
	else //Vertical
	{
		m_bar.setPosition(positionX, positionY + height * 0.5f);
		m_handle.setPosition(m_bar.getPosition().x, positionY - m_bar.getGlobalBounds().height * 0.5f);
		m_handle.setCollisionBounds(m_handle.sf::Sprite::getGlobalBounds().width, m_handle.sf::Sprite::getGlobalBounds().height);
		m_handle.setRotation(-90);
	}

	m_barWidth = m_bar.getGlobalBounds().width;
	m_barHeight = m_bar.getGlobalBounds().height;

	m_barTextureRectWidth = m_bar.getTextureRect().width;
	m_barTextureRectHeight = m_bar.getTextureRect().height;

	m_initialHandlePosX = m_handle.sf::Sprite::getPosition().x;
	m_initialHandlePosY = m_handle.sf::Sprite::getPosition().y;

	m_initialBarPosX = m_bar.getPosition().x;
	m_initialBarPosY = m_bar.getPosition().y;
}

void Slider::resetSlider()
{
	m_value = 1;
	m_bar.setTextureRect(sf::IntRect(0, 0, m_barTextureRectWidth * m_value, m_barTextureRectHeight));
	m_handle.setPosition(m_initialHandlePosX, m_handle.sf::Sprite::getPosition().y);
}

void Slider::reposition(const float& positionX, const float& positionY)
{
	UIElement::moveUIElement(positionX, positionY);
	m_bar.setPosition(positionX - UIElement::getGlobalBounds().width * 0.5f, positionY + m_bar.getGlobalBounds().height);
	m_handle.setPosition(m_bar.getPosition().x + m_bar.getGlobalBounds().width, positionY + m_bar.getGlobalBounds().height);
	m_initialHandlePosX = m_handle.sf::Sprite::getPosition().x;
	m_initialBarPosX = m_bar.getPosition().x;
}

void Slider::resizeSliderElements(const int& width, const int& height)
{
	if (m_isHorizontal)
	{
		float barWidth = m_bar.getTexture()->getSize().x;
		float barHeight = m_bar.getTexture()->getSize().y;

		float barYScale = height / barHeight;

		m_bar.setScale(width / barWidth, barYScale);

		m_handle.sf::Sprite::setScale(barYScale * 1.5f, barYScale * 1.5f); //Original texture is proportional to the bar height, this makes sure it stays that way
	}
	else
	{
		float barWidth = m_bar.getTexture()->getSize().x;
		float barHeight = m_bar.getTexture()->getSize().y;

		float barYScale = width / barHeight;

		m_bar.setScale(height / barWidth, barYScale);

		m_bar.setRotation(-90);

		m_handle.sf::Sprite::setScale(barYScale * 2, barYScale * 2);
	}
}

bool Slider::update(const sf::Vector2f& mousePosition)
{
	bool toggleButtonPress = false;

	if (Global::g_isLMBPressed && m_handle.collisionCheck(mousePosition))
	{
		toggleButtonPress = true;
		m_isActive = true;
	}

	if (m_isActive && m_mouse.isButtonPressed(sf::Mouse::Button::Left))
	{
		if (m_isHorizontal)
		{
			if (mousePosition.x < m_initialHandlePosX && m_initialHandlePosX - mousePosition.x < m_barWidth)
			{
				m_value = (mousePosition.x - m_initialBarPosX) / m_barWidth; //Updates slider value 

				m_handle.setPosition(mousePosition.x, m_handle.sf::Sprite::getPosition().y);
			}
		}
		else
		{
			if (mousePosition.y > m_initialHandlePosY && mousePosition.y - m_initialHandlePosY < m_barHeight)
			{
				m_value = abs((mousePosition.y - m_initialBarPosY) / m_barHeight);

				m_handle.setPosition(m_handle.sf::Sprite::getPosition().x, mousePosition.y);	
			}
		}

		if (m_value < 0.03f) //Round down when value is close to 0
		{
			m_value = 0;
		}
		else if (m_value > 0.997f) //Round down when value is bigger than 1
		{
			m_value = 1;
		}

		m_bar.setTextureRect(sf::IntRect(0, 0, m_barTextureRectWidth * m_value, m_barTextureRectHeight));

		m_functionToCallAfterResize();

		Global::objectPressed();
	}
	else
	{
		m_isActive = false;
	}

	return toggleButtonPress;
}

void Slider::setFunctionToCallAfterResize(std::function<void()> function)
{
	m_functionToCallAfterResize = function;
}

void Slider::resizeSlider(const int& positionX, const int& positionY, const int& width, const int& height)
{
	m_bar.setTextureRect(sf::IntRect(0, 0, m_barTextureRectWidth, m_barTextureRectHeight));

	UIElement::setPosition(positionX, positionY);
	setUpUIBorder(width, height);
	resizeSliderElements(width, height);

	if (m_isHorizontal)
	{
		m_bar.setPosition(positionX - UIElement::getGlobalBounds().width * 0.5f, positionY);
		m_handle.setPosition(m_bar.getPosition().x + m_bar.getGlobalBounds().width, positionY);
		m_handle.setCollisionBounds(m_handle.sf::Sprite::getGlobalBounds().width, m_handle.sf::Sprite::getGlobalBounds().height);
	}
	else
	{
		m_bar.setPosition(positionX, positionY + height * 0.5f);
		m_handle.setPosition(m_bar.getPosition().x, positionY - m_bar.getGlobalBounds().height * 0.5f);
		m_handle.setCollisionBounds(m_handle.sf::Sprite::getGlobalBounds().width, m_handle.sf::Sprite::getGlobalBounds().height);
		m_handle.setRotation(-90);
	}
	m_barTextureRectWidth = m_bar.getTextureRect().width;
	m_barTextureRectHeight = m_bar.getTextureRect().height;

	m_bar.setTextureRect(sf::IntRect(0, 0, m_barTextureRectWidth, m_barTextureRectHeight));

	m_barWidth = m_bar.getGlobalBounds().width;
	m_barHeight = m_bar.getGlobalBounds().height;

	//Save initial bar and handle positions
	m_initialHandlePosX = m_handle.sf::Sprite::getPosition().x;
	m_initialHandlePosY = m_handle.sf::Sprite::getPosition().y;
	m_initialBarPosX = m_bar.getPosition().x;
	m_initialBarPosY = m_bar.getPosition().y;

}

const float& Slider::getSliderValue() const
{
	return m_value;
}

const bool Slider::getActiveState() const
{
	return m_isActive;
}

void Slider::draw()
{
	UIElement::drawUIBorderAndBackground();
	m_window.draw(m_bar);
	m_window.draw(m_handle);
}