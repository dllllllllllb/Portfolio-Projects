#include "PopUpTextBox.h"

PopUpTextBox::PopUpTextBox(sf::RenderWindow& window, Textures& rTextures, Fonts& rFonts) :
	m_window(window),
	m_textBox(window, rTextures, rFonts, true),
	m_isActive(false)
{
	m_textBox.setThinUIBorder();
}

PopUpTextBox::~PopUpTextBox()
{
}

void PopUpTextBox::setUpPopUp(const std::string& text)
{
	m_textBox.setUpText(text, c_popUpCharSize, TextAlignmentEnum::middleHorizontal, TextAlignmentEnum::top);
	m_textBox.resizeBorderToFitText();
}

void PopUpTextBox::setPopUpWidth(const int& popUpWidth)
{
	m_textBox.setUpUIBorder(popUpWidth, 0);
}

void PopUpTextBox::setPosition(const sf::Vector2f& mousePosition)
{
	m_textBox.setPosition(mousePosition.x, mousePosition.y);
	m_textBox.updateAlignment();
}

void PopUpTextBox::setPosition(const int& positionX, const int& positionY)
{
	m_textBox.setPosition(positionX, positionY);
	m_textBox.updateAlignment();
}

void PopUpTextBox::toggleIsActive()
{
	m_isActive = !m_isActive;
}

void PopUpTextBox::setIsActive(const bool state)
{
	m_isActive = state;
}

const bool PopUpTextBox::getActiveState() const
{
	return m_isActive;
}

void PopUpTextBox::drawPopUpBox()
{
	m_textBox.draw();
}
