#include "MapUI.h"

namespace settings = MapUISettings;

MapUI::MapUI(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts, Audio& rAudio) :
	m_window(rWindow),
	m_textures(rTextures),
	m_audio(rAudio),
	m_background(rWindow, rTextures),
	m_turnInformation(rWindow, rTextures, rFonts, true),
	m_resourcesPerTurn(rWindow, rTextures, rFonts, true),
	m_heroesIconButtons(rWindow, rTextures, rAudio),
	m_townsIconButtons(rWindow, rTextures, rAudio),
	m_isActive(false)
{

}

MapUI::~MapUI()
{

}

void MapUI::setUpMapUI()
{
	int positionX = settings::c_mapUIWidth * 0.5f + settings::c_borderSize;
	//Background 
	m_background.setPosition(positionX, m_window.getView().getCenter().y);
	m_background.setUpUIBorder(settings::c_mapUIWidth, m_window.getSize().y);

	//Turn Information box
	m_turnInformation.setPosition(positionX, settings::c_informationTextBoxHeight * 0.5f + settings::c_borderSize);
	m_turnInformation.setUpUIBorder(settings::c_mapUIWidth, settings::c_informationTextBoxHeight);
	m_turnInformation.setUpText("Day: 0, Week: 0, Month: 0", settings::c_textSize, TextAlignmentEnum::middleHorizontal, TextAlignmentEnum::middleVertical);

	//Resources per turn information box
	m_resourcesPerTurn.setPosition(positionX, m_turnInformation.UIElement::getPosition().y + settings::c_informationTextBoxHeight + settings::c_borderSize);
	m_resourcesPerTurn.setUpUIBorder(settings::c_mapUIWidth, settings::c_informationTextBoxHeight);
	m_resourcesPerTurn.setUpText("Gold: 0, Wood: 0, Stone: 0", settings::c_textSize, TextAlignmentEnum::middleHorizontal, TextAlignmentEnum::middleVertical);

	//Town icon buttons
	m_townsIconButtons.setUpIconButtonList(positionX - settings::c_heroAndTownIconButtonsWidth * 0.5f - 5, m_resourcesPerTurn.UIElement::getPosition().y + settings::c_informationTextBoxHeight * 0.5f + settings::c_elementSpaceing, settings::c_heroAndTownIconButtonsWidth, settings::c_heroAndTownIconButtonsHeight, settings::c_numberOfButtonsToDisplay);
	
	//Heroes icon buttons
	m_heroesIconButtons.setUpIconButtonList(positionX + settings::c_heroAndTownIconButtonsWidth * 0.5f + 5, m_resourcesPerTurn.UIElement::getPosition().y + settings::c_informationTextBoxHeight * 0.5f + settings::c_elementSpaceing, settings::c_heroAndTownIconButtonsWidth, settings::c_heroAndTownIconButtonsHeight, settings::c_numberOfButtonsToDisplay);
	
	//Interaction Buttons
	int firstIconButtonPositionY = m_resourcesPerTurn.UIElement::getPosition().y + settings::c_informationTextBoxHeight * 0.5f + settings::c_arrowButtonHeight * 2 + settings::c_numberOfButtonsToDisplay * (settings::c_heroAndTownIconButtonsHeight + settings::c_borderSize) + settings::c_buttonIconHeight * 0.5f + settings::c_elementSpaceing * 2;
	for (int i = 0; i < settings::c_numberOfIconButtons; i++)
	{
		m_iconButtons.push_back(std::unique_ptr<IconButton>(new IconButton(m_window, m_textures, m_audio, true)));
		m_iconButtons[i]->setUpAndResizeToSprite(positionX, firstIconButtonPositionY + i * settings::c_buttonIconHeight + settings::c_borderSize, m_textures.m_mapUIIconButtons[i]);
	}
}

void MapUI::update(const sf::Vector2f& mousePosition)
{
	checkForTabPress();

	if (Global::g_isLMBPressed && m_isActive)
	{
		if (m_townsIconButtons.update(mousePosition))
		{
			m_townSelectedFunction(m_townsIconButtons.getIndexOfButtonClicked());
			toggleIsActive();
		}

		if (m_heroesIconButtons.update(mousePosition))
		{
			m_heroSelectedFunction(m_heroesIconButtons.getIndexOfButtonClicked());
			toggleIsActive();
		}


		for (int i = 0; i < m_iconButtons.size(); i++)
		{
			if (m_iconButtons[i]->checkIfButtonWasPressed(mousePosition))
			{
				switch (static_cast<MapUIButtonsEnum>(i))
				{
					case MapUIButtonsEnum::nextTurn:
					{
						m_nextTurnFunction();
					}
					break;

					case MapUIButtonsEnum::saveGame:
					{
						//m_saveGameFunction();
					}
					break;

					case MapUIButtonsEnum::option:
					{
						//m_optionsFunction();
					}
					break;

					case MapUIButtonsEnum::exit:
					{
						Global::g_gameState = GameState::menu;
						m_audio.playMusic(MusicEnum::menuMusic, 0);
					}
					break;

					default:
						break;
				}
			}
		}
		for (auto& button : m_iconButtons)
		{
			if (button->checkIfButtonWasPressed(mousePosition))
			{
				//Do stuff
			}
		}
	}
}

void MapUI::checkForTabPress()
{
	static bool canTabBePressed = false;
	if (Global::g_UILayer == UILayerEnum::map)
	{
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
		{
			canTabBePressed = true;
		}

		if (canTabBePressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
		{
			toggleIsActive();
			canTabBePressed = false;
		}
	}
}

void MapUI::toggleIsActive()
{
	m_isActive = !m_isActive;
	if (m_isActive)
	{
		m_updateResourcesPerTurnFunction(); //Updates resources per turn every time the map ui is opened
	}
}

void MapUI::setIsActive(const bool state)
{
	m_isActive = state;
}

void MapUI::draw()
{
	if (m_isActive)
	{
		m_background.drawUIBackground();
		m_turnInformation.draw();
		m_resourcesPerTurn.draw();
		m_townsIconButtons.draw();
		m_heroesIconButtons.draw();

		for (auto& button : m_iconButtons)
		{
			button->draw();
		}

		m_background.drawUIBorder();
	}
}

IconButtonList& MapUI::getTownButoonList()
{
	return m_townsIconButtons;
}

IconButtonList& MapUI::getHeroButoonList()
{
	return m_heroesIconButtons;
}

TextBox& MapUI::getTurnInformationTextBox()
{
	return m_turnInformation;
}

TextBox& MapUI::getResourcesPerTurnTextBox()
{
	return m_resourcesPerTurn;
}

void MapUI::setMapHandlerFunctionPointers(std::function<void(const int&)> townSelectedFunction, 
											std::function<void(const int&)> heroSelectedFunction, 
											std::function<void()> updateResourcesPerTurnFunction,
											std::function<void()> nextTurnFunction)
{
	m_townSelectedFunction = townSelectedFunction;
	m_heroSelectedFunction = heroSelectedFunction;
	m_updateResourcesPerTurnFunction = updateResourcesPerTurnFunction;
	m_nextTurnFunction = nextTurnFunction;
}
