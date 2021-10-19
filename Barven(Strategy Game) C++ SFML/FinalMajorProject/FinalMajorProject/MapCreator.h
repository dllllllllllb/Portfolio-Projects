//Author: Maciej Dowbor
//Last Accessed: 17/05/2021

#ifndef MAPCREATOR_H
#define MAPCREATOR_H

#include <SFML/System/Time.hpp>
#include <SFML/Window/Mouse.hpp>

#include <iostream> //Temporary for debugging

#include "DataHandler.h"
#include "IconButton.h"
#include "LandscapeMapObject.h"
#include "LandscapeTypeEnum.h"
#include "MapCreatorEnum.h"
#include "MapCreatorSettings.h"
#include "MapObjectsEnum.h"
#include "MapObjectEditorWindow.h"
#include "MapObjectEditorSettings.h"
#include "MapCreatorSaveWindow.h"
#include "ResourceMapObject.h"
#include "ResourceMineMapObject.h"
#include "SpecialBuildingMapObject.h"
#include "TextInputBox.h"
#include "TileHandler.h"
#include "TownMapObject.h"
#include "UnitMapObject.h"
#include "ViewManager.h"

//===========================================================================================
//Description: Map creator that allows the player to create their own playable map
//===========================================================================================
class MapCreator
{
private:
	sf::RenderWindow& m_window;
	Textures& m_textures;
	DataHandler& m_dataHandler;
	TileHandler				m_tileHandler;
	ViewManager				m_viewManager;
	MapObjectEditorWindow	m_editorWindow;
	MapCreatorSaveWindow	m_saveWindow;

	std::vector<std::unique_ptr<Button>>					m_primaryButtons;
	std::vector<std::vector<std::unique_ptr<Button>>>		m_secondaryButtons;
	std::vector<std::unique_ptr<TextInputBox>>				m_inputBoxes;
	std::vector<std::unique_ptr<IconButton>>				m_unitIconButtons;

	Button		m_applyMapSizeButton;
	UIElement	m_unitIconButtonsBackground;

	MapObjectsEnum m_selectedMapObjectToPlace;
	MapObjectsEnum m_selectedMapObjectToEdit;

	sf::Clock	m_clock;
	sf::Mouse& m_mouse;
	sf::Sprite	m_cursor;

	int m_selectedFaction;
	int m_dropDownIndex;
	int m_selectedUnitIndex;
	int m_selectedMapObjectIndexForEditorWindow;
	int m_randomFactionIndex;

	float m_deltaTime;

	bool m_isSetMapSizeActive;
	bool m_isEditorActive;
	bool m_isMapObjectSelected;
	bool m_drawTileOverlap;
	bool m_isSaveWindowActive;

	//==========================================================================================
	//Map Objects
	//==========================================================================================
	// 	Objects are stored as unique pointers in vectors because vectors create copies
	//	of themselves when moving in memory to find enough continuous space for themselves; this
	//	makes sure that only the address of the object is moved rather than the entire object.
	//	Unique pointers also manage deallocating memory when the data referenced by the pointer
	//	is out of scope.
	//==========================================================================================

	//Towns
	std::vector<std::unique_ptr<TownMapObject>> m_townMapObjects;
	int m_numOfTownMapObjects;

	//Units
	std::vector<std::unique_ptr<UnitMapObject>> m_unitMapObjects;
	int m_numOfUnitMapObjects;

	//Resource Mines
	std::vector<std::unique_ptr<ResourceMineMapObject>> m_resourceMinesMapObjects;
	int m_numOfResourceMinesMapObjects;
	ResourcesEnum m_selectedMineType;

	//Resources
	std::vector<std::unique_ptr<ResourceMapObject>> m_resourceMapObjects;
	int m_numOfResourceMapObjects;
	ResourcesEnum m_selectedResourceType;

	//Special Buildings
	std::vector<std::unique_ptr<SpecialBuildingMapObject>> m_specialBuildingsMapObjects;
	int m_numOfSpecialBuildingMapObjects;
	int m_selectedSpecialBuildingIndex;

	//Lanmdscapes
	sf::Sprite m_treeLandscapes[MapCreatorSettings::c_numOfTreeLandscapes]; //Landscape buttons use sprites instead of text to define what the button does
	sf::Sprite m_rockyLandscapes[MapCreatorSettings::c_numOfRockyLandscapes]; //IconButton class is not used as it it cleaner for the overall logic to have landscape buttons in "secondary buttons" vector
	sf::Sprite m_otherLandscapes[MapCreatorSettings::c_numOfOtherLandscapes];

	std::vector<std::unique_ptr<LandscapeMapObject>> m_landscapeMapObjects;
	int m_numOfLandscapeMapObjects;
	int m_selectedLandscapeIndex;
	LandscapeTypeEnum m_selectedLandscapeType;

	//======================================================================================
	//Vectors of tile properties
	//======================================================================================
	std::vector<int> m_obstacleTilesIndexes;
	std::vector<int> m_terrainObstacleTilesIndexes; //Seperate vector for landscape objects as they work slightly differently
	std::vector<int> m_occupiedTileIndexes;

	sf::Sprite m_tileOverlap; //Semi transparent sprite to visually represent tile properties
public:
	//===========================================================================================
	//Description: Class constructor, allocates memory for buttons and sets function pointers
	//===========================================================================================
	MapCreator(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts, Audio& rAudio, DataHandler& rDataHandler, sf::Mouse& rMouse);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~MapCreator();

	//===========================================================================================
	//Description: Initializes buttons, save window, view manager and tile handler
	//===========================================================================================
	void initialize();

	//===========================================================================================
	//Description: Sets up positions and contents of all buttons
	//===========================================================================================
	void setUpButtons();

	//===========================================================================================
	//Description: General update functions that calls UI and Game update functions
	//===========================================================================================
	void update(const sf::Vector2f& mousePosition);

	//===========================================================================================
	//Description: Updates UI components of the scene, checks for mouse collisions and button
	//			   presses. Holds logic that determines what map object is selected
	//===========================================================================================
	void updateUI(const sf::Vector2f& mousePosition);

	//===========================================================================================
	//Description: Updates any interactions with the map. Responsible for placing objects, moving
	//			   the view and interactions with objects on the map
	//===========================================================================================
	void updateGame();

	//===========================================================================================
	//Description: Updates primary buttons, determines which drop down list to display
	//===========================================================================================
	void updatePrimaryButtons(const sf::Vector2f& mousePosition);

	//===========================================================================================
	//Description: Updates secondary buttons, determines which map object is selected
	//===========================================================================================
	void updateSecondaryButtons(const sf::Vector2f& mousePosition);

	//===========================================================================================
	//Description: Updates input boxes, these are used to determine map size
	//===========================================================================================
	void updateInputBoxes(const sf::Vector2f& mousePosition);

	//===========================================================================================
	//Description: Updates unit icon buttons. It determines which unit is selected to be placed
	//===========================================================================================
	void updateUnitIconButtons(const sf::Vector2f& mousePosition);

	//===========================================================================================
	//Description: Based on selected object, it will create an instance of the selected object
	//			   inside an appropriate vector, set its appropriate texture, place it on the
	//			   map and update tile properties the object occupies
	//===========================================================================================
	const bool updateMapObjectPlacement(const int& tileIndex);

	//===========================================================================================
	//Description: Resets focus of input boxes
	//===========================================================================================
	void resetInputBoxesFocus();

	//===========================================================================================
	//Description: Returns a vector of tile indexes that the object is occupying/will occupy
	//===========================================================================================
	std::vector<int> getVectorOfOverlappedTiles(const int& occupiedTileIndex, const int& objectWidth, const int& objectHeight, const sf::Vector2f& objectOrigin);

	//===========================================================================================
	//Description: Loops through a vector of tile indexes and checks if tiles have obstacle
	//			   property
	//===========================================================================================
	const bool checkIfSpaceIsObstacle(std::vector<int>& overlappedTilesVector);

	//===========================================================================================
	//Description: Sets appropriate tile properties based on selected map object
	//===========================================================================================
	void setTilesProperties(std::vector<int>& overlappedTilesVector);

	//===========================================================================================
	//Description: Resets properties of tiles in the vector
	//===========================================================================================
	void resetVectorOfTiles(std::vector<int>& overlappedTilesVector);

	//===========================================================================================
	//Description: Resets properties of a single tile
	//===========================================================================================
	void resetTile(const int& tileIndex);

	//===========================================================================================
	//Description: Checks if keyboard keys were pressed and calls appropriate functions based on
	//			   keys pressed
	//===========================================================================================
	void checkForKeyPresses();

	//===========================================================================================
	//Description: Selects an object on the map and opens up editor window with the objects
	//			   properties and values
	//===========================================================================================
	void selectMapObject(const int& tileIndex);

	//===========================================================================================
	//Description: Applies object editor values to the object selected
	//===========================================================================================
	void applyValuesToObject();

	//===========================================================================================
	//Description: Sets object editor to inactive
	//===========================================================================================
	void closeObjectEditor();

	//===========================================================================================
	//Description: Sets texture of the cursor and its origin based on selected object
	//===========================================================================================
	void setCursor(const sf::Texture& cursorTexture);

	//===========================================================================================
	//Description: Updates position of the cursor and snaps it to the neares tile position
	//===========================================================================================
	void updateCursor(const sf::Vector2f& mousePosition);

	//===========================================================================================
	//Description: Deletes selected object, resets tiles occupied by that object and deletes
	//			   tiles for visual representation of the tile property
	//===========================================================================================
	void deleteObject();

	//===========================================================================================
	//Description: Updates tile reference of vector positions of the object the tile holds.
	//			   This is called after an object has been deleted
	//===========================================================================================
	void updateTileObjectVectorIndexes();

	//===========================================================================================
	//Description: Updates tile properties, used after a landscape object is deleted
	//===========================================================================================
	void updateLandscapeObjectsTileProperties();

	//===========================================================================================
	//Description: Updates unit icons to display selected faction units
	//===========================================================================================
	void updateUnitIcons();

	//===========================================================================================
	//Description: Saves map as JSON file
	//===========================================================================================
	void saveMap();

	//===========================================================================================
	//Description: Sets save map window to inactive
	//===========================================================================================
	void closeSaveMapWindow();

	//===========================================================================================
	//Description: Draws contents of this class
	//===========================================================================================
	void draw();

	//===========================================================================================
	//Description: Draws overlap tiles that visualise tile properties
	//===========================================================================================
	void drawTileOverlap();

	//===========================================================================================
	//Description: Draws UI elements
	//===========================================================================================
	void drawUI();

	//===========================================================================================
	//Description: Draws game elements
	//===========================================================================================
	void drawGame();
};

#endif // !MAPCREATOR_H
