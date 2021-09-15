//Author: Maciej Dowbor
//Last Accessed: 21/07/2021

#ifndef TOWNTRADING_H
#define TOWNTRADING_H

#include "IconButton.h"
#include "Slider.h"
#include "TextBox.h"
#include "Button.h"
#include "Resources.h"
#include "ConfirmationWindow.h"
#include "RecourceTradingButton.h"
#include "TownTradingSettings.h"
#include "ResourcesBar.h"

//===========================================================================================
//Description: Handles logic and visuals that allows player to trade resources
//===========================================================================================
class TownTrading
{
private:
	sf::RenderWindow& m_window;
	Resources* m_pResources;
	ResourcesBar& m_resourcesBar;
	ConfirmationWindow& m_confirmationWindow;

	Slider m_slider;
	UIElement m_playerResourcesBackground;
	UIElement m_traderResourcesBackground;
	std::vector<std::unique_ptr<ResourceTradingButton>> m_playerResourceButtons;
	std::vector<std::unique_ptr<ResourceTradingButton>> m_traderResourceButtons;

	sf::Sprite m_tradeIcon;
	Button m_tradeButton;
	TextBox m_tradeInformation;

	int m_selectedPlayerResourceIndex;
	int m_selectedTraderResourceIndex;

	bool m_isPlayerResourceSelected;
	bool m_isTraderResourceSelected;

public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	TownTrading(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts, ConfirmationWindow& rConfirmationWindow, ResourcesBar& rResourceBar);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~TownTrading();

	//===========================================================================================
	//Description: Sets up elements of this class to their base values
	//===========================================================================================
	void setUp();

	//===========================================================================================
	//Description: Updates interactions with this class
	//===========================================================================================
	void update(const sf::Vector2f& mousePosition); 

	//===========================================================================================
	//Description: Sets pointer to players resources
	//===========================================================================================
	void setResourcesPointer(Resources* playerResources);

	//===========================================================================================
	//Description: Updates function pointer to call when accept button is pressed in the
	//			   confirmation window
	//===========================================================================================
	void updateConfirmationFunctionPointer();

	//===========================================================================================
	//Description: Updates selected resources to trade if and how many resources can player trade
	//===========================================================================================
	void updateNumberOfPlayerResourcesToTrade();

	//===========================================================================================
	//Description: Updates selected resources to trade if and how many resources the player will
	//			   get from the trader
	//===========================================================================================
	void updateNumberOfTraderResourcesToTrade();

	//===========================================================================================
	//Description: Updates trade resources values
	//===========================================================================================
	void updateTradeInformation();

	//===========================================================================================
	//Description: Resets players resource selection
	//===========================================================================================
	void resetSelectedPlayerResource();

	//===========================================================================================
	//Description: Resets trader resource selection
	//===========================================================================================
	void resetSelectedTraderResource();

	//===========================================================================================
	//Description: Trades resources
	//===========================================================================================
	void tradeResources();

	//===========================================================================================
	//Description: Draws contents of this class
	//===========================================================================================
	void draw();
};
#endif // !TOWNTRADING_H

