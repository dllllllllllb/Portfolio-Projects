#include "TownTrading.h"

namespace settings = TownTradingSettings;

TownTrading::TownTrading(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts, ConfirmationWindow& rConfirmationWindow, ResourcesBar& rResourceBar) :
	m_window(rWindow),
	m_pResources(nullptr),
	m_resourcesBar(rResourceBar),
	m_confirmationWindow(rConfirmationWindow),
	m_slider(rWindow, &rTextures, true),
	m_playerResourcesBackground(rWindow, &rTextures),
	m_traderResourcesBackground(rWindow, &rTextures),
	m_tradeButton(rWindow, &rTextures, &rFonts),
	m_tradeInformation(rWindow, &rTextures, &rFonts, true),
	m_selectedPlayerResourceIndex(-1),
	m_selectedTraderResourceIndex(-1),
	m_isPlayerResourceSelected(false),
	m_isTraderResourceSelected(false)
{
	for (int i = 0; i < settings::c_numOfResourceTypes; i++)
	{
		m_playerResourceButtons.push_back(std::unique_ptr<ResourceTradingButton>(new ResourceTradingButton(rWindow, &rTextures, &rFonts)));
		m_traderResourceButtons.push_back(std::unique_ptr<ResourceTradingButton>(new ResourceTradingButton(rWindow, &rTextures, &rFonts)));
	}

	m_tradeIcon.setTexture(rTextures.m_tradeIcon, true);

	m_slider.setFunctionToCallAfterResize(std::bind(&TownTrading::updateTradeInformation, this));
}

TownTrading::~TownTrading()
{
}

void TownTrading::setUp()
{
	int centreX = m_window.getView().getCenter().x;
	int backgroundWidth = settings::c_backgroundBorder * 2 + ResourceTradingButtonSettings::c_buttonWidth;
	int backgroundHeight = settings::c_backgroundBorder * 2 + (ResourceTradingButtonSettings::c_buttonHeight + settings::c_resourceButtonsSpaceing) * settings::c_numOfResourceTypes + settings::c_resourceButtonsSpaceing;
	int firstButtonYPosition = m_window.getView().getCenter().y - backgroundHeight * 0.5f + ResourceTradingButtonSettings::c_buttonHeight - settings::c_backgroundBorder + settings::c_resourceButtonsSpaceing * 0.5f;

	//Set up resource background
	m_playerResourcesBackground.setPosition(centreX - settings::c_resourceButtonsXOffset, m_window.getView().getCenter().y);
	m_playerResourcesBackground.setUpUIBorder(backgroundWidth, backgroundHeight);

	m_traderResourcesBackground.setPosition(centreX + settings::c_resourceButtonsXOffset, m_window.getView().getCenter().y);
	m_traderResourcesBackground.setUpUIBorder(backgroundWidth, backgroundHeight);

	//Set up resource buttons
	for (int i = 0; i < settings::c_numOfResourceTypes; i++)
	{
		m_playerResourceButtons[i]->setUp(centreX - settings::c_resourceButtonsXOffset, firstButtonYPosition + (ResourceTradingButtonSettings::c_buttonHeight + settings::c_resourceButtonsSpaceing) * i, static_cast<ResourcesEnum>(i), settings::c_baseResourceAmount);
		m_traderResourceButtons[i]->setUp(centreX + settings::c_resourceButtonsXOffset, firstButtonYPosition + (ResourceTradingButtonSettings::c_buttonHeight + settings::c_resourceButtonsSpaceing) * i, static_cast<ResourcesEnum>(i), settings::c_baseResourceAmount);
	}

	//Set up slider
	m_slider.setUpSlider(m_window.getView().getCenter().x, m_window.getView().getCenter().y + backgroundHeight * 0.5f + settings::c_sliderHeight, settings::c_sliderWidth, settings::c_sliderHeight);

	//Trade button
	m_tradeButton.setPosition(centreX, m_slider.getPosition().y + settings::c_sliderHeight + settings::c_buttonHeight * 0.5f);
	m_tradeButton.setUpUIBorder(settings::c_buttonWidth, settings::c_buttonHeight);
	m_tradeButton.setCollisionBounds(settings::c_buttonWidth, settings::c_buttonHeight);
	m_tradeButton.setUpText(settings::c_buttonText, settings::c_buttonCharSize, TextAlignmentEnum::middleHorizontal, TextAlignmentEnum::middleVertical);

	//Trade Icon
	m_tradeIcon.setOrigin(m_tradeIcon.getGlobalBounds().width * 0.5f, m_tradeIcon.getGlobalBounds().height * 0.5f);
	m_tradeIcon.setPosition(m_window.getView().getCenter());

	//Trade information text box
	m_tradeInformation.setPosition(centreX, m_window.getView().getCenter().y + m_tradeIcon.getGlobalBounds().height);
	m_tradeInformation.setUpUIBorder(settings::c_informationBoxWidth, settings::c_informationBoxHeight);
	m_tradeInformation.setUpText("Test", settings::c_textBoxCharSize, TextAlignmentEnum::middleHorizontal, TextAlignmentEnum::top);
}

void TownTrading::update(const sf::Vector2f& mousePosition)
{
	//Resource buttons
	for (int i = 0; i < settings::c_numOfResourceTypes; i++)
	{
		if (m_playerResourceButtons[i]->checkMouseCollision(mousePosition) && Global::g_isLMBPressed)
		{
			Global::objectPressed();

			//Player feedback, highlight selected resource in yellow
			if (m_selectedPlayerResourceIndex != i)
			{
				resetSelectedPlayerResource();
				m_playerResourceButtons[i]->Button::UIElement::setColor(sf::Color::Yellow);
				m_selectedPlayerResourceIndex = i;
				m_isPlayerResourceSelected = true;
				updateTradeInformation();
			}
			else
			{
				m_playerResourceButtons[i]->Button::UIElement::setColor(sf::Color::White);
				m_playerResourceButtons[i]->setResourceAmount(0);
				m_selectedPlayerResourceIndex = -1;
				m_isPlayerResourceSelected = false;
			}

			break;
		}

		if (m_traderResourceButtons[i]->checkMouseCollision(mousePosition) && Global::g_isLMBPressed)
		{
			Global::objectPressed();

			if (m_selectedTraderResourceIndex != i)
			{
				resetSelectedTraderResource();
				m_traderResourceButtons[i]->Button::UIElement::setColor(sf::Color::Yellow);
				m_selectedTraderResourceIndex = i;
				m_isTraderResourceSelected = true;
				updateTradeInformation();
			}
			else
			{
				m_traderResourceButtons[i]->Button::UIElement::setColor(sf::Color::White);
				m_selectedTraderResourceIndex = -1;
				m_isTraderResourceSelected = false;
				m_traderResourceButtons[i]->setResourceAmount(0);
			}

			break;
		}
	}

	//Slider
	m_slider.update(mousePosition);

	//Trade button
	if (m_tradeButton.checkMouseCollision(mousePosition) && Global::g_isLMBPressed)
	{
		if (m_selectedPlayerResourceIndex != m_selectedTraderResourceIndex)
		{
			Global::objectPressed();
			m_confirmationWindow.changeUILayerToConfirmation();
		}
	}
}

void TownTrading::setResourcesPointer(Resources* playerResources)
{
	m_pResources = playerResources;
}

void TownTrading::updateConfirmationFunctionPointer()
{
	m_confirmationWindow.setConfirmationFunctionPointer(std::bind(&TownTrading::tradeResources, this));
}

void TownTrading::updateNumberOfPlayerResourcesToTrade()
{
	int playerResourceValue = m_traderResourceButtons[m_selectedTraderResourceIndex]->getResourceAmount();

	if (m_selectedPlayerResourceIndex > 0) //This means player is trading wood/stone
	{
		if (m_selectedTraderResourceIndex > 0) //This means trader is trading wood/stone
		{
			playerResourceValue *= settings::c_exRateResourceToResource;
		}
		else //This mneans trader is trading gold
		{
			playerResourceValue /= settings::c_exRateResourceToGold;
		}
	}
	else //This means player is trading gold
	{
		//Player can only trade gold for resources
		playerResourceValue *= settings::c_exRateGoldToResource;
	}
	m_playerResourceButtons[m_selectedPlayerResourceIndex]->setResourceAmount(playerResourceValue);
}

void TownTrading::updateNumberOfTraderResourcesToTrade()
{
	int traderValue = 0;
	int playerValue = static_cast<int>(m_slider.getSliderValue() * m_pResources->getResource(static_cast<ResourcesEnum>(m_selectedPlayerResourceIndex)));

	if (m_selectedPlayerResourceIndex > 0) //This means player is trading wood/stone
	{
		if (m_selectedTraderResourceIndex > 0) //This means trader is trading wood/stone
		{
			traderValue = std::floor(playerValue / settings::c_exRateResourceToResource);
		}
		else //This mneans trader is trading gold
		{
			traderValue = std::floor(playerValue * settings::c_exRateResourceToGold);
		}
	}
	else //This means player is trading gold
	{
		//Player can only trade gold for resources
		traderValue = std::floor(playerValue / settings::c_exRateGoldToResource);
	}

	m_traderResourceButtons[m_selectedTraderResourceIndex]->setResourceAmount(traderValue);
}

void TownTrading::updateTradeInformation()
{
	if (m_selectedPlayerResourceIndex != m_selectedTraderResourceIndex) //Can't trade the same resources
	{
		if (m_selectedPlayerResourceIndex >= 0 && m_selectedTraderResourceIndex >= 0) //Makes sure resource index is valid
		{
			updateNumberOfTraderResourcesToTrade();
			updateNumberOfPlayerResourcesToTrade();
		}
	}
	else
	{
		if (m_selectedPlayerResourceIndex >= 0 && m_selectedTraderResourceIndex >= 0) //Makes sure resource index is valid
		{
			m_playerResourceButtons[m_selectedPlayerResourceIndex]->Button::Text::setString(settings::c_sameResourceTradeError);
			m_playerResourceButtons[m_selectedPlayerResourceIndex]->Button::Text::updateAlignment();

			m_traderResourceButtons[m_selectedTraderResourceIndex]->Button::Text::setString(settings::c_sameResourceTradeError);
			m_traderResourceButtons[m_selectedTraderResourceIndex]->Button::Text::updateAlignment();
		}
	}
}

void TownTrading::resetSelectedPlayerResource()
{
	for (int i = 0; i < settings::c_numOfResourceTypes; i++)
	{
		m_playerResourceButtons[i]->UIElement::setColor(sf::Color::White);
		m_playerResourceButtons[i]->setResourceAmount(0);
	}
	m_slider.resetSlider();
}

void TownTrading::resetSelectedTraderResource()
{
	for (int i = 0; i < settings::c_numOfResourceTypes; i++)
	{
		m_traderResourceButtons[i]->UIElement::setColor(sf::Color::White);
		m_traderResourceButtons[i]->setResourceAmount(0);
	}

	m_slider.resetSlider();
}

void TownTrading::tradeResources()
{
	//Take away player resource (MAKE SURE VALUE IS NEGATIVE)
	m_pResources->incrementResourceValue(static_cast<ResourcesEnum>(m_selectedPlayerResourceIndex), -m_playerResourceButtons[m_selectedPlayerResourceIndex]->getResourceAmount());

	//Add trader resource
	m_pResources->incrementResourceValue(static_cast<ResourcesEnum>(m_selectedTraderResourceIndex), m_traderResourceButtons[m_selectedTraderResourceIndex]->getResourceAmount());

	m_resourcesBar.updateResourcesBarValues(*m_pResources);

	updateTradeInformation();

	m_confirmationWindow.changeUILayerToTown();
}

void TownTrading::draw()
{
	m_playerResourcesBackground.drawUIBorderAndBackground();
	m_traderResourcesBackground.drawUIBorderAndBackground();

	for (auto& resourceButton : m_playerResourceButtons)
	{
		resourceButton->draw();
	}

	for (auto& resourceButton : m_traderResourceButtons)
	{
		resourceButton->draw();
	}

	m_window.draw(m_tradeIcon);

	m_slider.draw();
	m_tradeButton.draw();
	//m_tradeInformation.draw();
}