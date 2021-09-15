#include "ConfirmationWindow.h"

ConfirmationWindow::ConfirmationWindow(sf::RenderWindow& window, Textures* pTextures, Fonts* pFonts) :
	UIElement(window, pTextures),
	TextBoxTitle(window, pTextures, pFonts),
	m_acceptButton(pTextures, true),
	m_declineButton(pTextures, false),
	m_pFunction(nullptr),
	m_isActive(false)
{
	setUp();
}

ConfirmationWindow::~ConfirmationWindow()
{
}

void ConfirmationWindow::reposition()
{
	UIElement::moveUIElement(m_window.getSize().x * 0.5f, m_window.getSize().y * 0.5f);
	setDefaultTitlePosition();
	float buttonWidth = m_acceptButton.getGlobalBounds().width;
	float buttonSpaceing = ((UIElement::getGlobalBounds().width - (buttonWidth * 2)) / 3) * 0.5f;

	float buttonAPosX = UIElement::getPosition().x - (buttonWidth * 0.5f) - buttonSpaceing;
	float buttonBPosX = UIElement::getPosition().x + (buttonWidth * 0.5f) + buttonSpaceing;

	float buttonPosY = UIElement::getPosition().y + m_titleText.getGlobalBounds().height * 0.5f;

	m_acceptButton.sf::Sprite::setPosition(buttonAPosX, buttonPosY);
	m_acceptButton.CollidableObject::setPosition(buttonAPosX, buttonPosY);
	m_declineButton.sf::Sprite::setPosition(buttonBPosX, buttonPosY);
	m_declineButton.CollidableObject::setPosition(buttonBPosX, buttonPosY);
}

void ConfirmationWindow::setUp()
{
	UIElement::setPosition(m_window.getSize().x * 0.5f, m_window.getSize().y * 0.5f);
	setUpUIBorder(250, 80);
	setUpTitleText("Are you sure?", 24);

	float buttonWidth = m_acceptButton.getGlobalBounds().width;
	float buttonSpaceing = ((UIElement::getGlobalBounds().width - (buttonWidth * 2)) / 3) * 0.5f;

	float buttonAPosX = UIElement::getPosition().x - (buttonWidth * 0.5f) - buttonSpaceing;
	float buttonBPosX = UIElement::getPosition().x + (buttonWidth * 0.5f) + buttonSpaceing;

	float buttonPosY = UIElement::getPosition().y + m_titleText.getGlobalBounds().height * 0.5f;

	m_acceptButton.sf::Sprite::setPosition(buttonAPosX, buttonPosY);
	m_acceptButton.CollidableObject::setPosition(buttonAPosX, buttonPosY);
	m_declineButton.sf::Sprite::setPosition(buttonBPosX, buttonPosY);
	m_declineButton.CollidableObject::setPosition(buttonBPosX, buttonPosY);
}

bool ConfirmationWindow::update(const sf::Vector2f& mousePosition)
{
	bool toggleButtonPress = false;

	if (Global::g_isLMBPressed && m_acceptButton.collisionCheck(mousePosition))
	{
		toggleButtonPress = true;
		Global::objectPressed();
		m_pFunction(); //Calls set function
	}

	if (Global::g_isLMBPressed && m_declineButton.collisionCheck(mousePosition))
	{
		Global::objectPressed();
		toggleButtonPress = true;

		Global::g_UILayer = Global::g_previousUILayer;
	}

	return toggleButtonPress;
}

void ConfirmationWindow::setConfirmationFunctionPointer(std::function<void()> function)
{
	m_pFunction = function;
	toggleIsActive();
}

const bool ConfirmationWindow::getActiveState() const
{
	return m_isActive;
}

void ConfirmationWindow::toggleIsActive()
{
	m_isActive = !m_isActive;
}

void ConfirmationWindow::changeUILayerToConfirmation()
{
	Global::g_previousUILayer = Global::g_UILayer;
	Global::g_UILayer = UILayerEnum::confirmation;
}

void ConfirmationWindow::changeUILayerToTown()
{
	Global::g_previousUILayer = Global::g_UILayer;
	Global::g_UILayer = UILayerEnum::town;
}

void ConfirmationWindow::changeUILayerToMap()
{
	Global::g_previousUILayer = Global::g_UILayer;
	Global::g_UILayer = UILayerEnum::map;
}

void ConfirmationWindow::changeUILayerToMapObjectInteraction()
{
	Global::g_previousUILayer = Global::g_UILayer;
	Global::g_UILayer = UILayerEnum::mapObjectInteraction;
}

void ConfirmationWindow::draw()
{
	drawUIBorderAndBackground();
	TextBoxTitle::draw();
	m_window.draw(m_acceptButton);
	m_window.draw(m_declineButton);
}