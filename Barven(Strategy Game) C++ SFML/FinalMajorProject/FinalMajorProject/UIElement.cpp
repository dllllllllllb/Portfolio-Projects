#include "UIElement.h"

UIElement::UIElement(sf::RenderWindow& window, Textures* textures) :
	m_window(window),
	m_pTextures(textures),
	m_isShaderActive(false),
	m_setUpFillShader(false)

{
	setTexture(m_pTextures->m_UIFill, true);
	m_fillShader.setTexture(m_pTextures->m_UIfillShader, true);
	m_fillShader.setColor(sf::Color::Color(255, 255, 255, 96)); 
	setDefaultTextures();
}

UIElement::UIElement(sf::RenderWindow& window, Textures* textures, const bool useThinBorder) :
	m_window(window),
	m_pTextures(textures)
{
	setTexture(m_pTextures->m_UIFill, true);
	m_fillShader.setTexture(m_pTextures->m_UIfillShader, true);
	m_fillShader.setColor(sf::Color::Color(255, 255, 255, 96));
	if (useThinBorder)
	{
		setThinUIBorder();
	}
	else 
	{
		setDefaultTextures();
	}
}

UIElement::~UIElement()
{
}

void UIElement::setDefaultTextures()
{
	m_borderTop.setTexture(m_pTextures->m_UIHorizontalBorder);
	m_borderBottom.setTexture(m_pTextures->m_UIHorizontalBorder);
	m_borderLeft.setTexture(m_pTextures->m_UIVerticalBorder);
	m_borderRight.setTexture(m_pTextures->m_UIVerticalBorder);

	m_cornerTopLeft.setTexture(m_pTextures->m_UICorner);
	m_cornerTopRight.setTexture(m_pTextures->m_UICorner);
	m_cornerBottomLeft.setTexture(m_pTextures->m_UICorner);
	m_cornerBottomRight.setTexture(m_pTextures->m_UICorner);
}

void UIElement::setThinUIBorder()
{
	m_borderTop.setTexture(m_pTextures->m_UIThinHorizontalBorder);
	m_borderBottom.setTexture(m_pTextures->m_UIThinHorizontalBorder);
	m_borderLeft.setTexture(m_pTextures->m_UIThinVerticalBorder);
	m_borderRight.setTexture(m_pTextures->m_UIThinVerticalBorder);

	m_cornerTopLeft.setTexture(m_pTextures->m_UIThinCorner);
	m_cornerTopRight.setTexture(m_pTextures->m_UIThinCorner);
	m_cornerBottomLeft.setTexture(m_pTextures->m_UIThinCorner);
	m_cornerBottomRight.setTexture(m_pTextures->m_UIThinCorner);
}

void UIElement::setUpUIBorder(const float& width, const float& height)
{
	int horizontalOffset = m_borderRight.getTexture()->getSize().x * 0.5f;
	int verticalOffset = m_borderBottom.getTexture()->getSize().y * 0.5f;

	sf::Vector2f position = getPosition();

	//==============================================================================================
	//Fill
	//==============================================================================================
	float xScale = width / getTexture()->getSize().x;
	float yScale = height / getTexture()->getSize().y;
	setScale( xScale, yScale);

	float halfSizeX = getTexture()->getSize().x * 0.5f;
	float halfSizeY = getTexture()->getSize().y * 0.5f;

	setOrigin(halfSizeX, halfSizeY);
	setPosition(position.x, position.y);

	if (m_setUpFillShader) //Checks if fill shader is required
	{
		setUpFillShader();
	}

	//==============================================================================================
	//Border
	//==============================================================================================
	 
	float cornerWidth = m_cornerTopRight.getTexture()->getSize().x;
	float cornerHeight = m_cornerTopRight.getTexture()->getSize().y;
	float halfCornerWidth = cornerWidth * 0.5f;
	float halfCornerHeight = cornerHeight * 0.5f;

	//BorderTop
	m_borderTop.setScale((width - cornerWidth) / m_borderTop.getTexture()->getSize().x, 1);
	m_borderTop.setPosition(position.x - (halfSizeX * xScale) + halfCornerWidth, position.y - (halfSizeY * yScale) - verticalOffset);

	//BorderBottom
	m_borderBottom.setScale((width - cornerWidth) / m_borderBottom.getTexture()->getSize().x, -1);
	m_borderBottom.setPosition(position.x - (halfSizeX * xScale) + halfCornerWidth, position.y + (halfSizeY * yScale) + verticalOffset);

	//BorderLeft
	m_borderLeft.setScale(1, (height - cornerHeight) / m_borderLeft.getTexture()->getSize().y);
	m_borderLeft.setPosition(position.x - (halfSizeX * xScale) - horizontalOffset, position.y - (halfSizeY * yScale) + halfCornerHeight);

	//BorderRight
	m_borderRight.setScale(-1, (height - cornerHeight) / m_borderRight.getTexture()->getSize().y);
	m_borderRight.setPosition(position.x + (halfSizeX * xScale) + horizontalOffset, position.y - (halfSizeY * yScale) + halfCornerHeight);

	//==============================================================================================
	//Corners
	//==============================================================================================
	float tempCornerSizeX = m_cornerTopLeft.getTexture()->getSize().x;
	float tempCornerSizeY = m_cornerTopLeft.getTexture()->getSize().y;

	//CornerTopLeft
	m_cornerTopLeft.setScale(-1, 1);
	m_cornerTopLeft.setPosition(position.x + tempCornerSizeX - (halfSizeX * xScale) - horizontalOffset, position.y - (halfSizeY * yScale) - verticalOffset);

	//CornerTopRight
	m_cornerTopRight.setPosition(position.x - tempCornerSizeX + (halfSizeX * xScale) + horizontalOffset, position.y - (halfSizeY * yScale) - verticalOffset);

	//CornerBottomLeft
	m_cornerBottomLeft.setScale(-1, -1);
	m_cornerBottomLeft.setPosition(position.x + tempCornerSizeX - (halfSizeX * xScale) - horizontalOffset, position.y + (halfSizeY * yScale) + verticalOffset);

	//CornerBottomRight
	m_cornerBottomRight.setScale(1, -1);
	m_cornerBottomRight.setPosition(position.x - tempCornerSizeX + (halfSizeX * xScale) + horizontalOffset, position.y + (halfSizeY * yScale) + verticalOffset);
}

void UIElement::setUpFillShader()
{
	float shaderScaleX = getGlobalBounds().width / m_fillShader.getTexture()->getSize().x;
	float shaderScaleY = getGlobalBounds().height / m_fillShader.getTexture()->getSize().y;
	m_fillShader.setScale(shaderScaleX, shaderScaleY);
	m_fillShader.setOrigin(m_fillShader.getTexture()->getSize().x * 0.5f, m_fillShader.getTexture()->getSize().y * 0.5f);
	m_fillShader.setPosition(getPosition());
}

void UIElement::setBorderColor(const sf::Color& color)
{
	m_borderTop.setColor(color);
	m_borderBottom.setColor(color);
	m_borderLeft.setColor(color);
	m_borderRight.setColor(color);
	m_cornerTopLeft.setColor(color);
	m_cornerTopRight.setColor(color);
	m_cornerBottomLeft.setColor(color);
	m_cornerBottomRight.setColor(color);
}

void UIElement::moveUIElement(const float& posX, const float& posY)
{
	sf::Vector2f pos = getPosition();
	float xDelta = posX - pos.x;
	float yDelta = posY - pos.y;

	m_fillShader.move(xDelta, yDelta);
	moveBorder(posX, posY);
	move(xDelta, yDelta);
}

void UIElement::moveBorder(const float& posX, const float& posY)
{
	sf::Vector2f pos = getPosition();
	float xDelta = posX - pos.x;
	float yDelta = posY - pos.y;

	m_borderTop.move(xDelta, yDelta);
	m_borderBottom.move(xDelta, yDelta);
	m_borderLeft.move(xDelta, yDelta);
	m_borderRight.move(xDelta, yDelta);
	m_cornerTopLeft.move(xDelta, yDelta);
	m_cornerTopRight.move(xDelta, yDelta);
	m_cornerBottomLeft.move(xDelta, yDelta);
	m_cornerBottomRight.move(xDelta, yDelta);
}

void UIElement::toggleIsShaderActive()
{
	m_isShaderActive = !m_isShaderActive;
}

void UIElement::drawUIBorderAndBackground()
{
	drawUIBackground();
	drawUIBorder();
}

void UIElement::drawUIBackground()
{
	m_window.draw(*this);
}

void UIElement::drawUIBorder()
{
	m_window.draw(m_borderTop);
	m_window.draw(m_borderBottom);
	m_window.draw(m_borderLeft);
	m_window.draw(m_borderRight);

	m_window.draw(m_cornerTopLeft);
	m_window.draw(m_cornerTopRight);
	m_window.draw(m_cornerBottomLeft);
	m_window.draw(m_cornerBottomRight);
}

void UIElement::drawFillShader()
{
	m_window.draw(m_fillShader);
}