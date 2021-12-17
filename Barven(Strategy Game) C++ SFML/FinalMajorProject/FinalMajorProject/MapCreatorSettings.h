//Author: Maciej Dowbor
//Last Accessed: 17/05/2021

#ifndef MAPCREATORSETTINGS_H
#define MAPCREATORSETTINGS_H

#include <string>
#include <vector>

namespace MapCreatorSettings
{
	//Landscapes
	static const int c_numOfTreeLandscapes = 4;
	static const int c_numOfRockyLandscapes = 6;
	static const int c_numOfOtherLandscapes = 6;

	//Primary Buttons
	static const int c_numOfprimaryButtons = 10;
	static const int c_primaryButtonsPositionX[c_numOfprimaryButtons]{ 77, 229, 381, 533, 685, 1231, 1383, 1535, 1689, 1843 };
	static const int c_primaryButtonsPositionY = 34;
	static const int c_buttonWidth = 150;
	static const int c_buttonHeight = 64;
	static const std::string c_primaryButtonName[c_numOfprimaryButtons]{ "Towns", "Resource Mines", "Resources", "Special Buildings", "Unit Faction Selection", "Trees", "Rocky", "Other", "Map Size", "Save Map" };
	static const int c_charSize = 16;

	//SecondaryButtons
	static const int c_numOfSecondaryButtonsSections = 8;
	static const int c_maxNumOfSecondaryButtonsPerSection = 6;
	static const int c_numOfSecondaryButtonsPerSection[c_numOfSecondaryButtonsSections]{ 3, 3, 4, 2, 3, c_numOfTreeLandscapes, c_numOfRockyLandscapes, c_numOfOtherLandscapes };
	static const std::string c_secondaryButtonNames[c_numOfSecondaryButtonsSections][c_maxNumOfSecondaryButtonsPerSection]{ {"Player", "Enemy AI", "Neutral"}, {"Gold", "Wood", "Stone"}, {"Gold", "Wood", "Stone", "Random"}, {"Arena", "Watch Tower"}, {"Castle", "Inferno", "Random"}, {"", "", "", ""}, {"", "", "", "", "", ""}, {"", "", "", "", "", ""}};

	//Input Boxes
	static const int c_numOfInputBoxes = 2;
	static const int c_inputBoxesPositionX = 1689;

	static const std::string c_inputBoxTitle[c_numOfInputBoxes]{ "Width", "Height" };
	static const std::string c_inputBoxText = "Type Here";

	static const int c_inputBoxTitleSize = 16;
	static const int c_inputBoxTextSize = 12;

	//Apply Map Size Button
	static const int c_applyMapSizePositionX = 1689;
	static const int c_applyMapSizePositionY = 224;
	static const std::string c_applyMapSizeButtonName = "Apply";

	//Tile Handler
	static const int c_tileStartPositionX = 0;
	static const int c_tileStartPositionY = 0;
	static const int c_tileSize = 32;

	//Unit Icon Buttons
	static const int c_unitIconButtonFirstXPosition = 789;
	static const int c_unitIconButtonWidth = 56;
	static const int c_unitIconButtonHeight = 64;

	//Landscapes tile occupation

	//MapObjectEditorWindow
	static const std::string c_editorWindowTitle = "Edit Object";
	static const std::string c_editorInpubButtonContent = "Type Here";
	static const int c_editorWindowTitleCharSize = 18;
	static const int c_editorInputButtonNameCharSize = 16;
	static const int c_editorInputButtonContentCharSize = 12;

	static const int c_editorWindowWidth = 200;
	static const int c_editorWindowInputBoxWidth = 180;
	static const int c_editorWindowInputBoxHeight = 50;
	static const int c_editorWindowSpaceing = 10;
}

#endif // !MAPCREATORSETTINGS_H
