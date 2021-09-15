#include "IconButtonList.h"

IconButtonList::IconButtonList(sf::RenderWindow& rWindow, Textures& rTextures) :
	m_window(rWindow),
	m_textures(rTextures),
	m_upNavigationButton(rWindow, &rTextures, true),
	m_downNavigationButton(rWindow, &rTextures, true),
	m_borderSize(2),
	m_numberOfButtons(0),
	m_numberOfButtonsToDisplay(0),
	m_firstButtonToDisplay(0),
	m_numberOfButtonsInUse(0),
	m_indexOfButtonClicked(0),
	m_buttonHeight(0)
{

}

IconButtonList::~IconButtonList()
{

}

void IconButtonList::setUpIconButtonList(const int& posX, const int& topPosY, const int& buttonWidth, const int& buttonHeight, const int& numOfButtonToDisplay)
{
	m_numberOfButtonsToDisplay = numOfButtonToDisplay;
	m_numberOfButtons = numOfButtonToDisplay;
	m_firstButtonToDisplay = 0;
	m_numberOfButtonsInUse = 0;
	m_buttonHeight = buttonHeight;

	//Set up navigation button
	m_upNavigationButton.setUpAndResizeToSprite(posX, topPosY + m_textures.m_upArrowIcon.getSize().y * 0.5f, m_textures.m_upArrowIcon);

	//Set up icon buttons
	int buttonIconsStartPosY = m_upNavigationButton.getIconSprite().getPosition().y + m_upNavigationButton.getIconSprite().getGlobalBounds().height * 0.5f + buttonHeight * 0.5f;
	for (int i = 0; i < m_numberOfButtonsToDisplay; i++)
	{
		m_iconButtons.push_back(std::unique_ptr<IconButton>(new IconButton(m_window, &m_textures, true)));
		m_iconButtons[i]->setUp(posX, buttonIconsStartPosY + i * buttonHeight + m_borderSize, buttonWidth, buttonHeight, &m_textures.m_UIFill);
	}

	//Set up navigation button
	m_downNavigationButton.setUpAndResizeToSprite(posX, m_iconButtons[m_numberOfButtonsToDisplay - 1]->getIconSprite().getPosition().y + buttonHeight * 0.5f + m_textures.m_upArrowIcon.getSize().y * 0.5f + m_borderSize, m_textures.m_downArrowIcon);

	m_firstButtonPosX = posX;
	m_firstButtonPosY = buttonIconsStartPosY;
}

void IconButtonList::updateButtonIcon(const int& buttonIndex, const sf::Texture& icon)
{	
	m_iconButtons[buttonIndex]->setButtonIcon(icon);
	m_iconButtons[buttonIndex]->getIconSprite().setScale(1, 1);
	m_iconButtons[buttonIndex]->getIconSprite().setOrigin(icon.getSize().x *0.5f, icon.getSize().y * 0.5f);
}

void IconButtonList::resetButtonIcons()
{
	for (auto& button : m_iconButtons)
	{
		button->setButtonIcon(m_textures.m_baseMapUIButtonIcon);
	}
}

void IconButtonList::addNewButtonIcon(const sf::Texture& buttonIcon)
{
	m_numberOfButtonsInUse++;
	if (m_numberOfButtonsInUse > m_numberOfButtons) //Make new button
	{
		m_iconButtons.push_back(std::unique_ptr<IconButton>(new IconButton(m_window, &m_textures, true)));
		m_iconButtons[m_numberOfButtonsInUse - 1]->setUpAndResizeToSprite(0, 0, buttonIcon);
		m_numberOfButtons++;
	}
	else
	{
		m_iconButtons[m_numberOfButtonsInUse -1]->setButtonIcon(buttonIcon);
	}
}


const bool IconButtonList::update(const sf::Vector2f& mousePosition)
{
	bool wasButtonClicked = false;

	if (Global::g_isLMBPressed)
	{
		//Up navigation button
		if (m_upNavigationButton.collisionCheck(mousePosition)) 
		{
			Global::objectPressed();
			if (m_numberOfButtonsInUse > m_numberOfButtonsToDisplay)
			{
				m_firstButtonToDisplay--;
				if (m_firstButtonToDisplay < 0)
				{
					m_firstButtonToDisplay = m_numberOfButtonsInUse - m_numberOfButtonsToDisplay;
				}
				updateButtonsPositions();
			}

		}
		else if (m_downNavigationButton.collisionCheck(mousePosition)) //Down navigation button
		{
			Global::objectPressed();
			if (m_numberOfButtonsInUse > m_numberOfButtonsToDisplay)
			{
				m_firstButtonToDisplay++;
				if (m_firstButtonToDisplay + m_numberOfButtonsToDisplay > m_numberOfButtonsInUse)
				{
					m_firstButtonToDisplay = 0;
				}
				updateButtonsPositions();
			}
		}

		//Icon buttons
		for (int i = m_firstButtonToDisplay; i < m_firstButtonToDisplay + m_numberOfButtonsToDisplay; i++)
		{
			if (m_iconButtons[i]->collisionCheck(mousePosition))
			{
				Global::objectPressed();
				m_indexOfButtonClicked = i;
				wasButtonClicked = true;
				break;
			}
		}
		
	}

	return wasButtonClicked;
}

const int& IconButtonList::getIndexOfButtonClicked() const
{
	return m_indexOfButtonClicked;
}

const int& IconButtonList::getNumberOfButtonsInUse() const
{
	return m_numberOfButtonsInUse;
}

void IconButtonList::updateButtonsPositions()
{
	for (int i = m_firstButtonToDisplay; i < m_firstButtonToDisplay + m_numberOfButtonsToDisplay; i++)
	{
		m_iconButtons[i]->setPosition(m_firstButtonPosX, m_firstButtonPosY + ((i - m_firstButtonToDisplay) * m_buttonHeight));
	}
}

void IconButtonList::draw()
{
	m_upNavigationButton.draw();
	for (int i = m_firstButtonToDisplay; i < m_firstButtonToDisplay + m_numberOfButtonsToDisplay; i++)
	{
		m_iconButtons[i]->drawWithoutUIBackground();
	}
	m_downNavigationButton.draw();
}
