//Author: Maciej Dowbor
//Last Accessed: 21/07/2021

#ifndef TOWNTRADINGSETTINGS_H
#define TOWNTRADINGSETTINGS_H

namespace TownTradingSettings
{
	static const std::string c_baseResourceAmount = "0";
	static const int c_numOfResourceTypes = 3;
	static const int c_resourceButtonsSpaceing = 10;
	static const int c_backgroundBorder = 20;
	static const int c_resourceButtonsXOffset = 200;
	static const int c_resourceButtonsYOffset = 150;

	//Slider
	static const int c_sliderWidth = 1000;
	static const int c_sliderHeight = 40;

	//Trade button
	static const int c_buttonWidth = 300;
	static const int c_buttonHeight = 100;
	static const int c_buttonCharSize = 42;
	static const std::string c_buttonText = "Trade";

	//Trade information text box
	static const int c_informationBoxWidth = 250;
	static const int c_informationBoxHeight = 50;
	static const int c_textBoxCharSize = 16;

	//Exchange rates
	static const int c_exRateGoldToResource = 500; //500:1 == 500 gold for 1 resource
	static const int c_exRateResourceToGold = 100; //1:100 == 1 resource for 100 gold
	static const int c_exRateResourceToResource = 5; //5:1 == 5 wood for 1 stone and vice versa
	static const std::string c_sameResourceTradeError = "-";
}

#endif // !TOWNTRADINGSETTINGS_H
