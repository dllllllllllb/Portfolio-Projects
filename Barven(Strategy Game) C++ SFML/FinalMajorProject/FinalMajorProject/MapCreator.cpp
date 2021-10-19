#include "MapCreator.h"

MapCreator::MapCreator(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts, Audio& rAudio, DataHandler& rDataHandler, sf::Mouse& rMouse) :
	m_window(rWindow),
	m_textures(rTextures),
	m_dataHandler(rDataHandler),
	m_tileHandler(rWindow, rTextures),
	m_viewManager(rWindow, rMouse),
	m_editorWindow(rWindow, rTextures, rFonts, rAudio),
	m_saveWindow(rWindow, rTextures, rFonts, rAudio),
	m_applyMapSizeButton(rWindow, rTextures, rFonts, rAudio, true),
	m_unitIconButtonsBackground(rWindow, rTextures, true),
	m_selectedMapObjectToPlace(MapObjectsEnum::none),
	m_selectedMapObjectToEdit(MapObjectsEnum::none),
	m_mouse(rMouse),
	m_selectedFaction(0),
	m_dropDownIndex(-1),
	m_selectedUnitIndex(0),
	m_selectedMapObjectIndexForEditorWindow(0),
	m_randomFactionIndex(MapCreatorSettings::c_numOfSecondaryButtonsPerSection[4] - 1),
	m_deltaTime(0),
	m_isSetMapSizeActive(false),
	m_isEditorActive(false),
	m_isMapObjectSelected(false),
	m_drawTileOverlap(false),
	m_isSaveWindowActive(false),
	m_numOfTownMapObjects(0),
	m_numOfUnitMapObjects(0),
	m_numOfResourceMinesMapObjects(0),
	m_selectedMineType(ResourcesEnum::gold),
	m_numOfResourceMapObjects(0),
	m_selectedResourceType(ResourcesEnum::gold),
	m_numOfSpecialBuildingMapObjects(0),
	m_selectedSpecialBuildingIndex(0),
	m_numOfLandscapeMapObjects(0),
	m_selectedLandscapeIndex(0),
	m_selectedLandscapeType(LandscapeTypeEnum::none)
{
	//=====================================
	//Allocates memory for buttons
	//=====================================

	//Primary Buttons
	for (int i = 0; i < MapCreatorSettings::c_numOfprimaryButtons; i++)
	{
		m_primaryButtons.push_back(std::unique_ptr<Button>(new Button(rWindow, rTextures, rFonts, rAudio, true)));
	}

	//Secondary Button
	m_secondaryButtons.resize(MapCreatorSettings::c_numOfSecondaryButtonsSections);
	for (int i = 0; i < MapCreatorSettings::c_numOfSecondaryButtonsSections; i++)
	{
		for (int j = 0; j < MapCreatorSettings::c_numOfSecondaryButtonsPerSection[i]; j++)
		{
			m_secondaryButtons[i].push_back(std::unique_ptr<Button>(new Button(rWindow, rTextures, rFonts, rAudio, true)));
		}
	}

	//Input Boxes
	for (int i = 0; i < MapCreatorSettings::c_numOfInputBoxes; i++)
	{
		m_inputBoxes.push_back(std::unique_ptr<TextInputBox>(new TextInputBox(rWindow, rTextures, rFonts, rAudio, true)));
	}

	//UnitIcon Buttons
	for (int i = 0; i < c_numOfUnitsPerFaction; i++)
	{
		m_unitIconButtons.push_back(std::unique_ptr<IconButton>(new IconButton(rWindow, rTextures, rAudio, true)));
	}

	//Set editor window function pointers
	m_editorWindow.setCloseWindowFunction(std::bind(&MapCreator::closeObjectEditor, this));
	m_editorWindow.setApplyValuesToObjectFunction(std::bind(&MapCreator::applyValuesToObject, this));

	//Set save window function pointers
	m_saveWindow.setSaveMapFunction(std::bind(&MapCreator::saveMap, this));
	m_saveWindow.setExitSaveWindowFunction(std::bind(&MapCreator::closeSaveMapWindow, this));

	m_tileOverlap.setTexture(rTextures.m_tileOverlap, true);
}

MapCreator::~MapCreator()
{
}

//===========================================================================================
// Map creator initialization
//===========================================================================================
void MapCreator::initialize()
{
	setUpButtons();
	m_tileHandler.setUpTiles(30, 10, 32, 0, 0);
	m_viewManager.setMapBoundaries(30 * 32, 10 * 32, 300);
	m_cursor.setColor(sf::Color(255, 255, 255, 90));
	m_saveWindow.initialize();
}

void MapCreator::setUpButtons()
{
	//Primary Buttons
	for (int i = 0; i < MapCreatorSettings::c_numOfprimaryButtons; i++)
	{
		m_primaryButtons[i]->setPosition(MapCreatorSettings::c_primaryButtonsPositionX[i], MapCreatorSettings::c_primaryButtonsPositionY);
		m_primaryButtons[i]->setUpUIBorder(MapCreatorSettings::c_buttonWidth, MapCreatorSettings::c_buttonHeight);
		m_primaryButtons[i]->setCollisionBounds(MapCreatorSettings::c_buttonWidth, MapCreatorSettings::c_buttonHeight);
		m_primaryButtons[i]->setUpText(MapCreatorSettings::c_primaryButtonName[i], MapCreatorSettings::c_charSize, TextAlignmentEnum::middleHorizontal, TextAlignmentEnum::middleVertical);
	}

	//Secondary Buttons
	for (int i = 0; i < MapCreatorSettings::c_numOfSecondaryButtonsSections; i++)
	{
		for (int j = 0; j < MapCreatorSettings::c_numOfSecondaryButtonsPerSection[i]; j++)
		{
			m_secondaryButtons[i][j]->setPosition(MapCreatorSettings::c_primaryButtonsPositionX[i], MapCreatorSettings::c_primaryButtonsPositionY + (MapCreatorSettings::c_buttonHeight * (j + 1) + 2));
			m_secondaryButtons[i][j]->setUpUIBorder(MapCreatorSettings::c_buttonWidth, MapCreatorSettings::c_buttonHeight);
			m_secondaryButtons[i][j]->setCollisionBounds(MapCreatorSettings::c_buttonWidth, MapCreatorSettings::c_buttonHeight);
			m_secondaryButtons[i][j]->setUpText(MapCreatorSettings::c_secondaryButtonNames[i][j], MapCreatorSettings::c_charSize, TextAlignmentEnum::middleHorizontal, TextAlignmentEnum::middleVertical);
		}
	}

	//Set up sprites for terrain types buttons
	for (int i = 5; i < MapCreatorSettings::c_numOfSecondaryButtonsSections; i++)
	{
		for (int j = 0; j < MapCreatorSettings::c_numOfSecondaryButtonsPerSection[i]; j++)
		{
			sf::Sprite* tempSprite = nullptr;
			switch (i)
			{
			case 5:
				tempSprite = &m_treeLandscapes[j];
				tempSprite->setTexture(m_textures.m_treeLandscapes[j]);
				break;

			case 6:
				tempSprite = &m_rockyLandscapes[j];
				tempSprite->setTexture(m_textures.m_rockyLandscapes[j]);
				break;

			case 7:
				tempSprite = &m_otherLandscapes[j];
				tempSprite->setTexture(m_textures.m_otherLandscapes[j]);
				break;

			default:
				tempSprite = &m_treeLandscapes[j];
				break;
			}
			int width = tempSprite->getGlobalBounds().width;
			int height = tempSprite->getGlobalBounds().height;

			float scale = (MapCreatorSettings::c_buttonHeight - MapCreatorSettings::c_buttonHeight * 0.2) / height;

			tempSprite->setScale(scale, scale);
			tempSprite->setOrigin(tempSprite->getLocalBounds().width * 0.5f, tempSprite->getLocalBounds().height * 0.5f);
			tempSprite->setPosition(MapCreatorSettings::c_primaryButtonsPositionX[i], MapCreatorSettings::c_primaryButtonsPositionY + (MapCreatorSettings::c_buttonHeight * (j + 1) + 2));
		}
	}

	//Input Boxes
	for (int i = 0; i < MapCreatorSettings::c_numOfInputBoxes; i++)
	{
		m_inputBoxes[i]->setPosition(MapCreatorSettings::c_inputBoxesPositionX, MapCreatorSettings::c_primaryButtonsPositionY + (MapCreatorSettings::c_buttonHeight * (i + 1)) + 2);
		m_inputBoxes[i]->setUpUIBorder(MapCreatorSettings::c_buttonWidth, MapCreatorSettings::c_buttonHeight);
		m_inputBoxes[i]->setCollisionBounds(MapCreatorSettings::c_buttonWidth, MapCreatorSettings::c_buttonHeight);
		m_inputBoxes[i]->setUpText(MapCreatorSettings::c_inputBoxText, MapCreatorSettings::c_inputBoxTextSize, TextAlignmentEnum::middleHorizontal, TextAlignmentEnum::middleVertical);
		m_inputBoxes[i]->setUpTitleText(MapCreatorSettings::c_inputBoxTitle[i], MapCreatorSettings::c_inputBoxTitleSize);
		m_inputBoxes[i]->setInputTextPosition();
	}

	//Apply Map Size Button
	m_applyMapSizeButton.setPosition(MapCreatorSettings::c_applyMapSizePositionX, MapCreatorSettings::c_applyMapSizePositionY);
	m_applyMapSizeButton.setUpUIBorder(MapCreatorSettings::c_buttonWidth, MapCreatorSettings::c_buttonHeight);
	m_applyMapSizeButton.setCollisionBounds(MapCreatorSettings::c_buttonWidth, MapCreatorSettings::c_buttonHeight);
	m_applyMapSizeButton.setUpText(MapCreatorSettings::c_applyMapSizeButtonName, MapCreatorSettings::c_charSize, TextAlignmentEnum::middleHorizontal, TextAlignmentEnum::middleVertical);

	////Unit Icons
	for (int i = 0; i < c_numOfUnitsPerFaction; i++)
	{
		m_unitIconButtons[i]->setUpAndResizeToSprite(MapCreatorSettings::c_unitIconButtonFirstXPosition + (MapCreatorSettings::c_unitIconButtonWidth * i), MapCreatorSettings::c_primaryButtonsPositionY, m_dataHandler.getFactionData(0).getUnitData(i).getUnitIcon());
	}

	m_unitIconButtonsBackground.setPosition(MapCreatorSettings::c_unitIconButtonFirstXPosition + (0.5f * (MapCreatorSettings::c_unitIconButtonWidth * (c_numOfUnitsPerFaction - 1))), MapCreatorSettings::c_primaryButtonsPositionY);
	m_unitIconButtonsBackground.setUpUIBorder(MapCreatorSettings::c_unitIconButtonWidth * c_numOfUnitsPerFaction, MapCreatorSettings::c_unitIconButtonHeight);
}

//===========================================================================================
// Map creator Update
//===========================================================================================

void MapCreator::update(const sf::Vector2f& mousePositionUI)
{
	checkForKeyPresses();

	if (Global::g_isLMBPressed)
	{
		resetInputBoxesFocus();
	}

	updateUI(mousePositionUI);

	updateGame();

	draw();
}

//===========================================================================================
// Update UI
//===========================================================================================

void MapCreator::updateUI(const sf::Vector2f& mousePosition)
{
	//Primary Buttons
	updatePrimaryButtons(mousePosition);

	//Secondary Buttons
	updateSecondaryButtons(mousePosition);

	//Input boxes
	updateInputBoxes(mousePosition);

	//Unit Icon Buttons
	updateUnitIconButtons(mousePosition);

	//Object editor window
	if (m_isEditorActive)
	{
		m_editorWindow.update(mousePosition);
	}

	//Map save window
	if (m_isSaveWindowActive)
	{
		m_saveWindow.update(mousePosition);
	}
}

//===========================================================================================
// Update Game
//===========================================================================================
void MapCreator::updateGame()
{
	m_viewManager.setGameView();

	//Game needs its own mouse position to make sure that it can properly interact with the map
	sf::Vector2f mousePositionGame = m_window.mapPixelToCoords(m_mouse.getPosition(m_window));

	m_deltaTime = m_clock.restart().asSeconds();
	m_viewManager.update(m_deltaTime);

	if (m_isMapObjectSelected)
	{
		updateCursor(mousePositionGame);
	}

	if (Global::g_isLMBPressed)
	{
		int tileIndex = m_tileHandler.checkTileCollision(mousePositionGame);
		if (tileIndex >= 0)
		{
			if (!updateMapObjectPlacement(tileIndex)) //Update Map Object Placement
			{
				selectMapObject(tileIndex); //Select Map Object
			}
		}
	}
}

//===========================================================================================
// Buttons and Input boxes update
//===========================================================================================
void MapCreator::updatePrimaryButtons(const sf::Vector2f& mousePosition)
{
	//Determines if and which drop down list to activate so its content can be interactable
	for (int i = 0; i < MapCreatorSettings::c_numOfprimaryButtons; i++)
	{
		if (m_primaryButtons[i]->checkIfButtonWasPressed(mousePosition))
		{
			if (m_dropDownIndex == i) //This allows for the drop down list to be hidden if player clicks twice on the same primary button that activates the drop down list
			{
				m_dropDownIndex = -1; //-1 is an off state
			}
			else if (i < MapCreatorSettings::c_numOfSecondaryButtonsSections)
			{
				m_dropDownIndex = i; //Sets drop down index correspoinding to the button pressed
			}
			else if (i == MapCreatorSettings::c_numOfprimaryButtons - 2) //Map resize input buttons have different interactions hence they need different logic to work properly
			{
				m_isSetMapSizeActive = !m_isSetMapSizeActive;
			}
			else if (i == MapCreatorSettings::c_numOfprimaryButtons - 1) //Save map button
			{
				m_isSaveWindowActive = true;
			}
		}
	}
}

void MapCreator::updateSecondaryButtons(const sf::Vector2f& mousePosition)
{
	//Secondary Buttons
	if (m_dropDownIndex > -1) //Makes sure that there is an active drop down list
	{
		for (int i = 0; i < MapCreatorSettings::c_numOfSecondaryButtonsPerSection[m_dropDownIndex]; i++) //Based on the drop down list, it will then check only for the buttons that live in the active drop down list
		{
			if (m_secondaryButtons[m_dropDownIndex][i]->checkIfButtonWasPressed(mousePosition)) //Checks for mouse collision
			{
				m_isMapObjectSelected = true;

				switch ((MapCreatorEnum)m_dropDownIndex) //Based on the active drop down list, it checks which button is pressed to select appropriate object
				{
					//TOWNS
				case MapCreatorEnum::towns:
				{
					m_selectedMapObjectToPlace = MapObjectsEnum::town;
					setCursor(m_textures.m_unasignedTown);

					switch ((MapCreatorTownsEnum)i)
					{
					case MapCreatorTownsEnum::player:
						break;

					case MapCreatorTownsEnum::enemyAI:
						break;

					case MapCreatorTownsEnum::neutral:
						break;

					default:
						break;
					}
				}
				break;

				//RESOURCE MINES
				case MapCreatorEnum::resourceMines:
				{
					m_selectedMapObjectToPlace = MapObjectsEnum::resourceMine;
					m_selectedMineType = (ResourcesEnum)i;
					setCursor(*m_dataHandler.getResourceMineData(m_selectedMineType).getMineMapTexture());
				}
				break;

				//RESOURCES
				case MapCreatorEnum::resources:
				{
					m_selectedMapObjectToPlace = MapObjectsEnum::resource;
					m_selectedResourceType = (ResourcesEnum)i;

					setCursor(m_textures.m_resourceTextures[i]);
				}
				break;

				//SPECIAL BUILDINGS
				case MapCreatorEnum::specialBuildings:
				{
					m_selectedMapObjectToPlace = MapObjectsEnum::specialBuilding;
					m_selectedSpecialBuildingIndex = i;

					setCursor(m_textures.m_specialBuildings[i]);
				}
				break;

				case MapCreatorEnum::unitFactionSelection:
				{
					m_selectedFaction = i;
					updateUnitIcons();
				}
				break;

				//LANSCAPE TREES
				case MapCreatorEnum::landscapeTree:
				{
					m_selectedMapObjectToPlace = MapObjectsEnum::landscape;
					m_selectedLandscapeType = LandscapeTypeEnum::tree;
					m_selectedLandscapeIndex = i;
					setCursor(m_textures.m_treeLandscapes[m_selectedLandscapeIndex]);
				}
				break;

				//LANDSCAPE ROCKY
				case MapCreatorEnum::landscapeRocky:
				{
					m_selectedMapObjectToPlace = MapObjectsEnum::landscape;
					m_selectedLandscapeType = LandscapeTypeEnum::rocky;
					m_selectedLandscapeIndex = i;
					setCursor(m_textures.m_rockyLandscapes[m_selectedLandscapeIndex]);
				}
				break;

				//LANSCAPE OTHER
				case MapCreatorEnum::landscapeOther:
				{
					m_selectedMapObjectToPlace = MapObjectsEnum::landscape;
					m_selectedLandscapeType = LandscapeTypeEnum::other;
					m_selectedLandscapeIndex = i;
					setCursor(m_textures.m_otherLandscapes[m_selectedLandscapeIndex]);
				}
				break;

				default:
					break;
				}
				m_dropDownIndex = -1; //Sets drop down to off state
				break;
			}
		}
	}
}

void MapCreator::updateInputBoxes(const sf::Vector2f& mousePosition)
{

	if (m_isSetMapSizeActive) //Checks if the map size drop down is active
	{
		for (int i = 0; i < MapCreatorSettings::c_numOfInputBoxes; i++) //Updates inpub boxes
		{
			if (m_inputBoxes[i]->checkIfButtonWasPressed(mousePosition)) //Checks if input box has been pressed
			{
				m_inputBoxes[i]->setButtonPressed(true);
			}
			m_inputBoxes[i]->update();
		}

		if (m_applyMapSizeButton.checkIfButtonWasPressed(mousePosition)) //Apply size button is here as its relevant to map size section
		{
			//Resizes the map
			m_tileHandler.setUpTiles(std::stoi(m_inputBoxes[0]->getPlayerInput()), std::stoi(m_inputBoxes[1]->getPlayerInput()), MapCreatorSettings::c_tileSize, MapCreatorSettings::c_tileStartPositionX, MapCreatorSettings::c_tileStartPositionY);
			m_viewManager.setMapBoundaries(32 * std::stoi(m_inputBoxes[0]->getPlayerInput()), 32 * std::stoi(m_inputBoxes[1]->getPlayerInput()), 300);
			m_isSetMapSizeActive = false;
			resetInputBoxesFocus();
		}
	}
}

void MapCreator::updateUnitIconButtons(const sf::Vector2f& mousePosition)
{

	for (int i = 0; i < c_numOfUnitsPerFaction; i++)
	{
		if (m_unitIconButtons[i]->checkIfButtonWasPressed(mousePosition)) //Checks if a unit has been selected
		{
			m_selectedMapObjectToPlace = MapObjectsEnum::unit;
			m_selectedUnitIndex = i;
			m_isMapObjectSelected = true;

			if (m_selectedFaction == m_randomFactionIndex)
			{
				setCursor(m_textures.m_randomUnitMapSprite);
			}
			else
			{
				setCursor(m_dataHandler.getFactionData(m_selectedFaction).getUnitData(m_selectedUnitIndex).getUnitMapSprite());
			}
		}
	}
}

//===========================================================================================
// Map object placement update
//===========================================================================================
const bool MapCreator::updateMapObjectPlacement(const int& tileIndex)
{
	bool toggleButtonPress = false;

	if (m_selectedMapObjectToPlace != MapObjectsEnum::none) //Checks for mouse input and if a map object is selected
	{
		bool canTileBePlaced = false;

		if (!m_tileHandler.getTile(tileIndex)->getIsObstacle()) //Makes sure that the tile doen't already have an object on it
		{
			canTileBePlaced = true;
		}

		if (m_selectedMapObjectToPlace == MapObjectsEnum::landscape && m_tileHandler.getTile(tileIndex)->getMapObjectType() == MapObjectsEnum::landscape && !m_tileHandler.getTile(tileIndex)->getIsOccupied()) //Special case for lanscape objects, if landscape object is selected and it will only cover other landscape object, it is allowed to be placed (check for overlaping object later)
		{
			canTileBePlaced = true;
		}

		if (canTileBePlaced)
		{
			std::vector<int> vectorOfOverlappedTiles;
			switch (m_selectedMapObjectToPlace) //Based on selected map object, the algorithm will create a new instance of it in its appropriate vector and set its properties
			{
			case MapObjectsEnum::town:
				m_townMapObjects.push_back(std::unique_ptr<TownMapObject>(new TownMapObject())); //Allocate memory for new object
				m_townMapObjects[m_numOfTownMapObjects]->setUp(m_tileHandler.getTile(tileIndex)->getPosition(), m_textures.m_unasignedTown); //Set up the object

				//Make a vector of tile indexes that the object will overlap
				vectorOfOverlappedTiles = getVectorOfOverlappedTiles(tileIndex, m_townMapObjects[m_numOfTownMapObjects]->getGlobalBounds().width, m_townMapObjects[m_numOfTownMapObjects]->getGlobalBounds().height, m_townMapObjects[m_numOfTownMapObjects]->getOrigin());
				if (!checkIfSpaceIsObstacle(vectorOfOverlappedTiles)) //Check if a overlapped tile is an obstacle
				{
					toggleButtonPress = true;
					setTilesProperties(vectorOfOverlappedTiles); //Sets appropriate tile properties
					m_tileHandler.getTile(tileIndex)->setMapObjectType(MapObjectsEnum::town);
					m_tileHandler.getTile(tileIndex)->setMapObjectVectorIndex(m_numOfTownMapObjects);
					m_townMapObjects[m_numOfTownMapObjects]->setTileIndex(tileIndex);

					//Adds tile indexes to obstacle tile indexes for visual representation
					m_obstacleTilesIndexes.insert(m_obstacleTilesIndexes.end(), vectorOfOverlappedTiles.begin(), vectorOfOverlappedTiles.end());

					m_numOfTownMapObjects++;
				}
				else
				{
					m_townMapObjects.pop_back();
				}
				break;

			case MapObjectsEnum::unit:
				toggleButtonPress = true;
				m_unitMapObjects.push_back(std::unique_ptr<UnitMapObject>(new UnitMapObject())); //Allocate memory for new object and set appropriate data
				if (m_selectedFaction == m_randomFactionIndex)
				{
					m_unitMapObjects[m_numOfUnitMapObjects]->setUp(m_tileHandler.getTile(tileIndex)->getPosition(), m_textures.m_randomUnitMapSprite);
				}
				else
				{
					m_unitMapObjects[m_numOfUnitMapObjects]->setUp(m_tileHandler.getTile(tileIndex)->getPosition(), m_dataHandler.getFactionData(m_selectedFaction).getUnitData(m_selectedUnitIndex).getUnitMapSprite());
				}
				m_unitMapObjects[m_numOfUnitMapObjects]->setFactionIndex(m_selectedFaction);
				m_unitMapObjects[m_numOfUnitMapObjects]->setUnitIndex(m_selectedUnitIndex);
				m_unitMapObjects[m_numOfUnitMapObjects]->setTileIndex(tileIndex);

				//Set appropriate tile properties
				m_tileHandler.getTile(tileIndex)->setMapObjectType(MapObjectsEnum::unit);
				m_tileHandler.getTile(tileIndex)->setMapObjectVectorIndex(m_numOfUnitMapObjects);

				//Adds tile index to obstacle tile indexes for visual representation
				m_obstacleTilesIndexes.push_back(tileIndex);

				m_numOfUnitMapObjects++;
				break;

			case MapObjectsEnum::specialBuilding:
				m_specialBuildingsMapObjects.push_back(std::unique_ptr<SpecialBuildingMapObject>(new SpecialBuildingMapObject()));
				m_specialBuildingsMapObjects[m_numOfSpecialBuildingMapObjects]->setUp(m_tileHandler.getTile(tileIndex)->getPosition(), &m_textures.m_specialBuildings[m_selectedSpecialBuildingIndex]);

				vectorOfOverlappedTiles = getVectorOfOverlappedTiles(tileIndex, m_specialBuildingsMapObjects[m_numOfSpecialBuildingMapObjects]->getGlobalBounds().width, m_specialBuildingsMapObjects[m_numOfSpecialBuildingMapObjects]->getGlobalBounds().height, m_specialBuildingsMapObjects[m_numOfSpecialBuildingMapObjects]->getOrigin());
				if (!checkIfSpaceIsObstacle(vectorOfOverlappedTiles))
				{
					toggleButtonPress = true;
					setTilesProperties(vectorOfOverlappedTiles);
					m_specialBuildingsMapObjects[m_numOfSpecialBuildingMapObjects]->setBuildingType((SpecialBuildingEnum)m_selectedSpecialBuildingIndex);

					m_tileHandler.getTile(tileIndex)->setMapObjectType(MapObjectsEnum::specialBuilding);
					m_tileHandler.getTile(tileIndex)->setMapObjectVectorIndex(m_numOfSpecialBuildingMapObjects);

					m_specialBuildingsMapObjects[m_numOfSpecialBuildingMapObjects]->setTileIndex(tileIndex);

					m_obstacleTilesIndexes.insert(m_obstacleTilesIndexes.end(), vectorOfOverlappedTiles.begin(), vectorOfOverlappedTiles.end());

					m_numOfSpecialBuildingMapObjects++;
				}
				else
				{
					m_specialBuildingsMapObjects.pop_back();
				}
				break;

			case MapObjectsEnum::resourceMine:
				m_resourceMinesMapObjects.push_back(std::unique_ptr<ResourceMineMapObject>(new ResourceMineMapObject())); //Allocate memory for new object and set appropriate data
				m_resourceMinesMapObjects[m_numOfResourceMinesMapObjects]->setUp(m_tileHandler.getTile(tileIndex)->getPosition(), m_dataHandler.getResourceMineData(m_selectedMineType).getMineMapTexture());

				//Make a vector of tile indexes that the object will overlap
				vectorOfOverlappedTiles = getVectorOfOverlappedTiles(tileIndex, m_resourceMinesMapObjects[m_numOfResourceMinesMapObjects]->getGlobalBounds().width, m_resourceMinesMapObjects[m_numOfResourceMinesMapObjects]->getGlobalBounds().height, m_resourceMinesMapObjects[m_numOfResourceMinesMapObjects]->getOrigin());
				if (!checkIfSpaceIsObstacle(vectorOfOverlappedTiles)) //Check if a overlapped tile is an obstacle
				{
					toggleButtonPress = true;

					setTilesProperties(vectorOfOverlappedTiles);
					m_resourceMinesMapObjects[m_numOfResourceMinesMapObjects]->setMineTypeEnum(m_selectedMineType);

					//Sets appropriate tile properties
					m_tileHandler.getTile(tileIndex)->setMapObjectType(MapObjectsEnum::resourceMine);
					m_tileHandler.getTile(tileIndex)->setMapObjectVectorIndex(m_numOfResourceMinesMapObjects);

					m_resourceMinesMapObjects[m_numOfResourceMinesMapObjects]->setTileIndex(tileIndex); //Set tile reference

					//Adds tile indexes to obstacle tile indexes for visual representation
					m_obstacleTilesIndexes.insert(m_obstacleTilesIndexes.end(), vectorOfOverlappedTiles.begin(), vectorOfOverlappedTiles.end());

					m_numOfResourceMinesMapObjects++;
				}
				else
				{
					m_resourceMinesMapObjects.pop_back();
				}
				break;

			case MapObjectsEnum::resource:
				toggleButtonPress = true;
				m_resourceMapObjects.push_back(std::unique_ptr<ResourceMapObject>(new ResourceMapObject())); //Allocate memory for new object and set appropriate data

				m_resourceMapObjects[m_numOfResourceMapObjects]->setUp(m_tileHandler.getTile(tileIndex)->getPosition(), &m_textures.m_resourceTextures[(int)m_selectedResourceType]);
				m_resourceMapObjects[m_numOfResourceMapObjects]->setResourceType(m_selectedResourceType);

				//Sets appropriate tile properties
				m_tileHandler.getTile(tileIndex)->setMapObjectType(MapObjectsEnum::resource);
				m_tileHandler.getTile(tileIndex)->setMapObjectVectorIndex(m_numOfResourceMapObjects);

				m_resourceMapObjects[m_numOfResourceMapObjects]->setTileIndex(tileIndex); //Set tile reference

				//Adds tile index to obstacle tile indexes for visual representation
				m_obstacleTilesIndexes.push_back(tileIndex);

				m_numOfResourceMapObjects++;
				break;

			case MapObjectsEnum::landscape:

				m_landscapeMapObjects.push_back(std::unique_ptr<LandscapeMapObject>(new LandscapeMapObject())); //Allocate memory for new object and set appropriate data

				switch (m_selectedLandscapeType)
				{
					//Sets appropriate data based on selected landscape type
				case LandscapeTypeEnum::tree:
					m_landscapeMapObjects[m_numOfLandscapeMapObjects]->setUp(m_tileHandler.getTile(tileIndex)->getPosition(), &m_textures.m_treeLandscapes[m_selectedLandscapeIndex]);
					break;

				case LandscapeTypeEnum::rocky:
					m_landscapeMapObjects[m_numOfLandscapeMapObjects]->setUp(m_tileHandler.getTile(tileIndex)->getPosition(), &m_textures.m_rockyLandscapes[m_selectedLandscapeIndex]);
					break;

				case LandscapeTypeEnum::other:
					m_landscapeMapObjects[m_numOfLandscapeMapObjects]->setUp(m_tileHandler.getTile(tileIndex)->getPosition(), &m_textures.m_otherLandscapes[m_selectedLandscapeIndex]);
					break;

				default:
					break;
				}

				//Make a vector of tile indexes that the object will overlap
				vectorOfOverlappedTiles = getVectorOfOverlappedTiles(tileIndex, m_landscapeMapObjects[m_numOfLandscapeMapObjects]->getGlobalBounds().width, m_landscapeMapObjects[m_numOfLandscapeMapObjects]->getGlobalBounds().height, m_landscapeMapObjects[m_numOfLandscapeMapObjects]->getOrigin());
				if (!checkIfSpaceIsObstacle(vectorOfOverlappedTiles)) //Check if a overlapped tile is an obstacle
				{
					toggleButtonPress = true;

					//Set appropriate tile properties
					setTilesProperties(vectorOfOverlappedTiles);
					m_landscapeMapObjects[m_numOfLandscapeMapObjects]->setTileIndex(tileIndex); //Set reference to tile index
					m_landscapeMapObjects[m_numOfLandscapeMapObjects]->setObjectIndex(m_selectedLandscapeIndex); //Set reference to tile index
					m_landscapeMapObjects[m_numOfLandscapeMapObjects]->setLandscapeType(m_selectedLandscapeType); //Set reference to tile index
					m_tileHandler.getTile(tileIndex)->setMapObjectType(MapObjectsEnum::landscape);
					m_tileHandler.getTile(tileIndex)->setMapObjectVectorIndex(m_numOfLandscapeMapObjects);
					m_tileHandler.getTile(tileIndex)->setIsOccupied(true);

					//Adds tile index to occupied tile indexes for visual representation
					m_occupiedTileIndexes.push_back(tileIndex);

					//Adds tile indexes to obstacle tile indexes for visual representation
					m_terrainObstacleTilesIndexes.insert(m_terrainObstacleTilesIndexes.end(), vectorOfOverlappedTiles.begin(), vectorOfOverlappedTiles.end());

					m_numOfLandscapeMapObjects++;
				}
				else
				{
					m_landscapeMapObjects.pop_back();
				}
				break;

			default:
				break;
			}

			if (toggleButtonPress)
			{
				if (m_selectedMapObjectToPlace != MapObjectsEnum::landscape)
				{
					m_tileHandler.getTile(tileIndex)->setIsOccupied(true); //Sets tile to occupied
					m_occupiedTileIndexes.push_back(tileIndex);
				}
				m_tileHandler.getTile(tileIndex)->setIsObstacle(true); //Sets tile to obstacle
			}
		}
	}

	if (toggleButtonPress) { Global::objectPressed(); }

	return toggleButtonPress;
}

//===========================================================================================
// Map creator navigation and object placeing specific functions
//===========================================================================================
void MapCreator::resetInputBoxesFocus()
{
	for (int i = 0; i < MapCreatorSettings::c_numOfInputBoxes; i++)
	{
		m_inputBoxes[i]->setButtonPressed(false);
	}
}

std::vector<int> MapCreator::getVectorOfOverlappedTiles(const int& occupiedTileIndex, const int& objectWidth, const int& objectHeight, const sf::Vector2f& objectOrigin)
{
	int numOfHorizontalTiles = m_tileHandler.getNumOfHorizontalTiles();

	int placementRow = occupiedTileIndex / numOfHorizontalTiles;

	std::vector<int> tileIndexes;

	tileIndexes.push_back(occupiedTileIndex);

	//Tiles to the right of the centre of the object
	int numOfTilesRight = (objectWidth - objectOrigin.x) / c_tileSize - 1;
	for (int i = 1; i < numOfTilesRight + 1; i++)
	{
		if (occupiedTileIndex + i <= (placementRow * numOfHorizontalTiles) + (numOfHorizontalTiles - 1))
		{
			tileIndexes.push_back(occupiedTileIndex + i);
		}
	}

	//Tiles to the left of the centre of the object
	int numOfTilesLeft = objectOrigin.x / c_tileSize;
	for (int i = 1; i < numOfTilesLeft + 1; i++)
	{
		if (occupiedTileIndex - i >= placementRow * numOfHorizontalTiles)
		{
			tileIndexes.push_back(occupiedTileIndex - i);
		}
	}

	//Tiles Above
	int numOfTilesUp = (objectHeight - c_tileSize) / c_tileSize;
	int vectorSize = tileIndexes.size();
	for (int i = 0; i < vectorSize; i++)
	{
		for (int j = 1; j < numOfTilesUp + 1; j++)
		{
			if (tileIndexes[i] - (numOfHorizontalTiles * j) >= 0) //Makes sure that tile indexes are valid
			{
				tileIndexes.push_back(tileIndexes[i] - (numOfHorizontalTiles * j));
			}
		}
	}

	//Special cases for landscape objects to place or edit
	//Landscape objects can be overlapped therefore they need to check if the tiles determined above are landscape objects and get rid of them from the vector
	if (m_selectedMapObjectToPlace == MapObjectsEnum::landscape)
	{
		int positionInVector = 0;
		std::vector<int> vectorPositionsToDelete;

		for (int tileIndex : tileIndexes)
		{
			if (m_tileHandler.getTile(tileIndex)->getMapObjectType() == MapObjectsEnum::landscape) //Makes sure to not override landscape tiles
			{
				vectorPositionsToDelete.insert(vectorPositionsToDelete.begin(), positionInVector); //Positions are inserted to the front because if I was to delete the first vector position, it will automatically decrease position of other elements and I would end up deleting wrong indexes
			}
			positionInVector++;
		}

		for (int vecPosition : vectorPositionsToDelete)
		{
			tileIndexes.erase(tileIndexes.begin() + vecPosition);
		}
	}
	else if (m_selectedMapObjectToEdit == MapObjectsEnum::landscape)
	{
		int positionInVector = 0;
		std::vector<int> vectorPositionsToDelete;

		for (int tileIndex : tileIndexes)
		{
			if (m_tileHandler.getTile(tileIndex)->getIsOccupied()) //Makes sure to not override occupied tiles
			{
				vectorPositionsToDelete.insert(vectorPositionsToDelete.begin(), positionInVector);
			}
			positionInVector++;
		}

		for (int vecPosition : vectorPositionsToDelete)
		{
			tileIndexes.erase(tileIndexes.begin() + vecPosition);
		}
	}

	//No need to check tiles below as the origin of the object is always on the bottom tile apart from terrain which doesn't matter as it's not interactable

	return tileIndexes;
}

const bool MapCreator::checkIfSpaceIsObstacle(std::vector<int>& overlappedTilesVector)
{
	bool isSpaceObstacle = false;

	for (size_t i = 0; i < overlappedTilesVector.size(); i++)
	{
		if (m_tileHandler.getTile(overlappedTilesVector[i])->getIsObstacle()) //Checks if the tile is an obstacle
		{
			isSpaceObstacle = true;
			break; //No need to check other tiles as one obstacle tile is enough to not allow the placement of the object
		}
	}
	return isSpaceObstacle;
}

void MapCreator::setTilesProperties(std::vector<int>& overlappedTilesVector)
{
	for (size_t i = 0; i < overlappedTilesVector.size(); i++)
	{
		m_tileHandler.getTile(overlappedTilesVector[i])->setIsObstacle(true);
	}

	if (m_selectedMapObjectToPlace == MapObjectsEnum::landscape)
	{
		for (size_t i = 0; i < overlappedTilesVector.size(); i++)
		{
			m_tileHandler.getTile(overlappedTilesVector[i])->setMapObjectType(MapObjectsEnum::landscape);
		}
	}
}

void MapCreator::resetVectorOfTiles(std::vector<int>& overlappedTilesVector)
{
	//Resets all tile properties passed in the vector
	for (size_t i = 0; i < overlappedTilesVector.size(); i++)
	{
		m_tileHandler.getTile(overlappedTilesVector[i])->setIsObstacle(false);
		m_tileHandler.getTile(overlappedTilesVector[i])->setMapObjectType(MapObjectsEnum::none);
		m_tileHandler.getTile(overlappedTilesVector[i])->setIsOccupied(false);
		m_tileHandler.getTile(overlappedTilesVector[i])->setMapObjectVectorIndex(0);
	}
}

void MapCreator::resetTile(const int& tileIndex)
{
	//Resets all tile properties of a single tile
	m_tileHandler.getTile(tileIndex)->setIsObstacle(false);
	m_tileHandler.getTile(tileIndex)->setMapObjectType(MapObjectsEnum::none);
	m_tileHandler.getTile(tileIndex)->setIsOccupied(false);
	m_tileHandler.getTile(tileIndex)->setMapObjectVectorIndex(0);
}

void MapCreator::checkForKeyPresses()
{
	static bool canKeyBePressed = false;
	if (Global::g_isWindowFocused) //Makes sure window is focused
	{
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) //SFML keyboard input is not reliable in my testing so I need to check manually if the key is not pressed to reset the bool that allows the key to be pressed
		{
			canKeyBePressed = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) //Resets everything the player selected
		{
			m_selectedMapObjectToPlace = MapObjectsEnum::none;
			m_selectedMapObjectToEdit = MapObjectsEnum::none;
			closeObjectEditor();
			m_isMapObjectSelected = false;
		}

		if (canKeyBePressed && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) //Toggles overlaping tiles that show tile properties
		{
			m_drawTileOverlap = !m_drawTileOverlap;
			canKeyBePressed = false;
		}

		if (m_selectedMapObjectToEdit != MapObjectsEnum::none && sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) //Deletes selected object
		{
			deleteObject();
		}
	}
}

//===========================================================================================
// Map object selection and editing
//===========================================================================================
void MapCreator::selectMapObject(const int& index)
{
	bool toggleButtonPress = false;
	m_isEditorActive = true;

	Tile* tile = m_tileHandler.getTile(index);
	if (tile->getIsOccupied()) //Checks if an object is on the selected tile
	{
		m_selectedMapObjectToEdit = tile->getMapObjectType();
		m_selectedMapObjectIndexForEditorWindow = tile->getMapObjectVectorIndex();
		m_editorWindow.resetButtonFocus();//Gets index of the selected object
	}

	int numOfVarsToChange = MapObjectEditorSettings::c_numOfvariablesToChange[(int)tile->getMapObjectType()];

	int buttonContent = 0;

	if (numOfVarsToChange > 0)
	{
		m_editorWindow.setUpWindow(numOfVarsToChange);
		for (int i = 0; i < numOfVarsToChange; i++)
		{
			switch (m_selectedMapObjectToEdit) //Sets button content based on the variable value that the object already has
			{
			case MapObjectsEnum::town:
				buttonContent = m_townMapObjects[m_selectedMapObjectIndexForEditorWindow]->getVariable((MapObjectDataEnum::Town)i);
				break;

			case MapObjectsEnum::unit:
				buttonContent = m_unitMapObjects[m_selectedMapObjectIndexForEditorWindow]->getVariable((MapObjectDataEnum::Units)i);
				break;

			case MapObjectsEnum::specialBuilding:
				//Nothing to edit so far
				break;

			case MapObjectsEnum::resourceMine:
				buttonContent = m_resourceMinesMapObjects[m_selectedMapObjectIndexForEditorWindow]->getVariable((MapObjectDataEnum::ResourceMine)i);
				break;

			case MapObjectsEnum::resource:
				buttonContent = m_resourceMapObjects[m_selectedMapObjectIndexForEditorWindow]->getVariable((MapObjectDataEnum::Resource)i);
				break;

			default:
				break;
			}
			//Sets editor window button name and variable value
			m_editorWindow.setUpButtons(i, MapObjectEditorSettings::c_variablesToChangeNames[(int)tile->getMapObjectType()][i], buttonContent);
			toggleButtonPress = true;
		}
	}
	else
	{
		closeObjectEditor(); //Deactivates editor if there are no variables to change
	}
	if (toggleButtonPress) { Global::objectPressed(); }
}

void MapCreator::applyValuesToObject()
{
	int playerInput;

	//Sets all values entered by the player to the selected object
	for (int i = 0; i < MapObjectEditorSettings::c_numOfvariablesToChange[(int)m_selectedMapObjectToEdit]; i++)
	{
		playerInput = m_editorWindow.getPlayerInput(i);
		switch (m_selectedMapObjectToEdit)
		{
		case MapObjectsEnum::town:
			m_townMapObjects[m_selectedMapObjectIndexForEditorWindow]->setVariable((MapObjectDataEnum::Town)i, playerInput);
			break;

		case MapObjectsEnum::unit:
			m_unitMapObjects[m_selectedMapObjectIndexForEditorWindow]->setVariable((MapObjectDataEnum::Units)i, playerInput);
			break;

		case MapObjectsEnum::specialBuilding:
			//Nothing to edit so far
			break;

		case MapObjectsEnum::resourceMine:
			m_resourceMinesMapObjects[m_selectedMapObjectIndexForEditorWindow]->setVariable((MapObjectDataEnum::ResourceMine)i, playerInput);
			break;

		case MapObjectsEnum::resource:
			m_resourceMapObjects[m_selectedMapObjectIndexForEditorWindow]->setVariable((MapObjectDataEnum::Resource)i, playerInput);
			break;

		default:
			break;
		}
	}
}

void MapCreator::closeObjectEditor()
{
	m_editorWindow.resetButtonFocus();
	m_isEditorActive = false;
}

//===========================================================================================
// Map creator cursor
//===========================================================================================
void MapCreator::setCursor(const sf::Texture& cursorTexture)
{
	m_cursor.setTexture(cursorTexture, true);

	//Sets origin based on type of object selected
	switch (m_selectedMapObjectToPlace)
	{
	case MapObjectsEnum::none:
		break;

	case MapObjectsEnum::town:
		m_cursor.setOrigin(m_cursor.getGlobalBounds().width * 0.5f, m_cursor.getGlobalBounds().height - 32);
		break;

	case MapObjectsEnum::unit:
		m_cursor.setOrigin(0, m_cursor.getGlobalBounds().height - 32);
		break;

	case MapObjectsEnum::specialBuilding:
		m_cursor.setOrigin(m_cursor.getGlobalBounds().width * 0.5f - 16, m_cursor.getGlobalBounds().height - 32);
		break;

	case MapObjectsEnum::resourceMine:
		m_cursor.setOrigin(m_cursor.getGlobalBounds().width - 64, 32);
		break;

	case MapObjectsEnum::resource:
		m_cursor.setOrigin(0, m_cursor.getGlobalBounds().height - 32);
		break;

	case MapObjectsEnum::landscape:
		m_cursor.setOrigin(m_cursor.getGlobalBounds().width * 0.5f, m_cursor.getGlobalBounds().height - 32);
		break;

	default:
		break;
	}
}

void MapCreator::updateCursor(const sf::Vector2f& mousePosition)
{
	//Sets mouse position to the neares tile position to snap the cursor to the tile grid
	int x = mousePosition.x / c_tileSize;
	int y = mousePosition.y / c_tileSize;

	m_cursor.setPosition(x * c_tileSize, y * c_tileSize);
}

//===========================================================================================
// Map object deletion
//===========================================================================================
void MapCreator::deleteObject()
{
	std::vector<int> tileIndexesToDelete;
	int occupiedTileIndex = 0;

	if (m_selectedMapObjectToEdit != MapObjectsEnum::none)
	{
		switch (m_selectedMapObjectToEdit)
		{
		case MapObjectsEnum::town:
			occupiedTileIndex = m_townMapObjects[m_selectedMapObjectIndexForEditorWindow]->getTileIndex(); //Gets tile index of where te object was placed
			tileIndexesToDelete = getVectorOfOverlappedTiles(occupiedTileIndex, m_townMapObjects[m_selectedMapObjectIndexForEditorWindow]->getGlobalBounds().width, m_townMapObjects[m_selectedMapObjectIndexForEditorWindow]->getGlobalBounds().height, m_townMapObjects[m_selectedMapObjectIndexForEditorWindow]->getOrigin());
			resetVectorOfTiles(tileIndexesToDelete); //Rets tile properties of tiles occupied by the object to be deleted
			m_townMapObjects.erase(m_townMapObjects.begin() + m_selectedMapObjectIndexForEditorWindow); //Deletes object from array
			m_numOfTownMapObjects--;
			break;

		case MapObjectsEnum::unit:
			occupiedTileIndex = m_unitMapObjects[m_selectedMapObjectIndexForEditorWindow]->getTileIndex();//Gets tile index of where te object was placed
			tileIndexesToDelete = getVectorOfOverlappedTiles(occupiedTileIndex, m_unitMapObjects[m_selectedMapObjectIndexForEditorWindow]->getGlobalBounds().width, m_unitMapObjects[m_selectedMapObjectIndexForEditorWindow]->getGlobalBounds().height, m_unitMapObjects[m_selectedMapObjectIndexForEditorWindow]->getOrigin());
			resetVectorOfTiles(tileIndexesToDelete);//Rets tile properties of tiles occupied by the object to be deleted
			m_unitMapObjects.erase(m_unitMapObjects.begin() + m_selectedMapObjectIndexForEditorWindow);//Deletes object from array
			m_numOfUnitMapObjects--;
			break;

		case MapObjectsEnum::specialBuilding:
			occupiedTileIndex = m_specialBuildingsMapObjects[m_selectedMapObjectIndexForEditorWindow]->getTileIndex();//Gets tile index of where te object was placed
			tileIndexesToDelete = getVectorOfOverlappedTiles(occupiedTileIndex, m_specialBuildingsMapObjects[m_selectedMapObjectIndexForEditorWindow]->getGlobalBounds().width, m_specialBuildingsMapObjects[m_selectedMapObjectIndexForEditorWindow]->getGlobalBounds().height, m_specialBuildingsMapObjects[m_selectedMapObjectIndexForEditorWindow]->getOrigin());
			resetVectorOfTiles(tileIndexesToDelete);//Rets tile properties of tiles occupied by the object to be deleted
			m_specialBuildingsMapObjects.erase(m_specialBuildingsMapObjects.begin() + m_selectedMapObjectIndexForEditorWindow); //Deletes object from array
			m_numOfSpecialBuildingMapObjects--;
			break;

		case MapObjectsEnum::resourceMine:
			occupiedTileIndex = m_resourceMinesMapObjects[m_selectedMapObjectIndexForEditorWindow]->getTileIndex();//Gets tile index of where te object was placed
			tileIndexesToDelete = getVectorOfOverlappedTiles(occupiedTileIndex, m_resourceMinesMapObjects[m_selectedMapObjectIndexForEditorWindow]->getGlobalBounds().width, m_resourceMinesMapObjects[m_selectedMapObjectIndexForEditorWindow]->getGlobalBounds().height, m_resourceMinesMapObjects[m_selectedMapObjectIndexForEditorWindow]->getOrigin());
			resetVectorOfTiles(tileIndexesToDelete);//Rets tile properties of tiles occupied by the object to be deleted
			m_resourceMinesMapObjects.erase(m_resourceMinesMapObjects.begin() + m_selectedMapObjectIndexForEditorWindow);//Deletes object from array
			m_numOfResourceMinesMapObjects--;
			break;

		case MapObjectsEnum::resource:
			occupiedTileIndex = m_resourceMapObjects[m_selectedMapObjectIndexForEditorWindow]->getTileIndex();//Gets tile index of where te object was placed
			tileIndexesToDelete = getVectorOfOverlappedTiles(occupiedTileIndex, m_resourceMapObjects[m_selectedMapObjectIndexForEditorWindow]->getGlobalBounds().width, m_resourceMapObjects[m_selectedMapObjectIndexForEditorWindow]->getGlobalBounds().height, m_resourceMapObjects[m_selectedMapObjectIndexForEditorWindow]->getOrigin());
			resetVectorOfTiles(tileIndexesToDelete);//Rets tile properties of tiles occupied by the object to be deleted
			m_resourceMapObjects.erase(m_resourceMapObjects.begin() + m_selectedMapObjectIndexForEditorWindow);//Deletes object from array
			m_numOfResourceMapObjects--;
			break;

		case MapObjectsEnum::landscape: //Special case
			occupiedTileIndex = m_landscapeMapObjects[m_selectedMapObjectIndexForEditorWindow]->getTileIndex();//Gets tile index of where te object was placed
			tileIndexesToDelete = getVectorOfOverlappedTiles(occupiedTileIndex, m_landscapeMapObjects[m_selectedMapObjectIndexForEditorWindow]->getGlobalBounds().width, m_landscapeMapObjects[m_selectedMapObjectIndexForEditorWindow]->getGlobalBounds().height, m_landscapeMapObjects[m_selectedMapObjectIndexForEditorWindow]->getOrigin());
			resetTile(occupiedTileIndex);
			resetVectorOfTiles(tileIndexesToDelete);//Rets tile properties of tiles occupied by the object to be deleted
			m_landscapeMapObjects.erase(m_landscapeMapObjects.begin() + m_selectedMapObjectIndexForEditorWindow);//Deletes object from array
			m_numOfLandscapeMapObjects--;
			tileIndexesToDelete.push_back(occupiedTileIndex);
			break;

		default:
			break;
		}

		//Delete overlapping tiles

		//Obstacle tiles
		int positionInVector = 0;
		std::vector<int> overlapingTilesToDelete;
		if (m_selectedMapObjectToEdit == MapObjectsEnum::landscape) //Special case for landscape objects
		{
			for (int tileIndex : m_terrainObstacleTilesIndexes)
			{
				for (int tileIndexToDelete : tileIndexesToDelete)
				{
					if (tileIndex == tileIndexToDelete)
					{
						overlapingTilesToDelete.insert(overlapingTilesToDelete.begin(), positionInVector);
					}
				}
				positionInVector++;
			}

			for (int vectorPosition : overlapingTilesToDelete)
			{
				m_terrainObstacleTilesIndexes.erase(m_terrainObstacleTilesIndexes.begin() + vectorPosition);
			}
		}
		else
		{
			for (int tileIndex : m_obstacleTilesIndexes)
			{
				for (int tileIndexToDelete : tileIndexesToDelete)
				{
					if (tileIndex == tileIndexToDelete)
					{
						overlapingTilesToDelete.insert(overlapingTilesToDelete.begin(), positionInVector);
					}
				}
				positionInVector++;
			}

			for (int vectorPosition : overlapingTilesToDelete)
			{
				m_obstacleTilesIndexes.erase(m_obstacleTilesIndexes.begin() + vectorPosition);
			}
		}

		//Occupied tiles
		positionInVector = 0;
		for (int vectorPosition : m_occupiedTileIndexes)
		{
			if (vectorPosition == occupiedTileIndex)
			{
				m_occupiedTileIndexes.erase(m_occupiedTileIndexes.begin() + positionInVector);
				break;
			}
			positionInVector++;
		}

		updateTileObjectVectorIndexes();
		m_selectedMapObjectToEdit = MapObjectsEnum::none;
		closeObjectEditor();
	}
}

void MapCreator::updateTileObjectVectorIndexes()
{
	switch (m_selectedMapObjectToEdit)
	{
	case MapObjectsEnum::town:
		for (int i = m_selectedMapObjectIndexForEditorWindow; i < m_numOfTownMapObjects; i++)
		{
			m_tileHandler.getTile(m_townMapObjects[i]->getTileIndex())->decrementMapObjectVectorIndex();
		}
		break;

	case MapObjectsEnum::unit:
		for (int i = m_selectedMapObjectIndexForEditorWindow; i < m_numOfUnitMapObjects; i++)
		{
			m_tileHandler.getTile(m_unitMapObjects[i]->getTileIndex())->decrementMapObjectVectorIndex();
		}
		break;

	case MapObjectsEnum::specialBuilding:
		for (int i = m_selectedMapObjectIndexForEditorWindow; i < m_numOfSpecialBuildingMapObjects; i++)
		{
			m_tileHandler.getTile(m_specialBuildingsMapObjects[i]->getTileIndex())->decrementMapObjectVectorIndex();
		}
		break;

	case MapObjectsEnum::resourceMine:
		for (int i = m_selectedMapObjectIndexForEditorWindow; i < m_numOfResourceMinesMapObjects; i++)
		{
			m_tileHandler.getTile(m_resourceMinesMapObjects[i]->getTileIndex())->decrementMapObjectVectorIndex();
		}
		break;

	case MapObjectsEnum::resource:
		for (int i = m_selectedMapObjectIndexForEditorWindow; i < m_numOfResourceMapObjects; i++)
		{
			m_tileHandler.getTile(m_resourceMapObjects[i]->getTileIndex())->decrementMapObjectVectorIndex();
		}
		break;

	case MapObjectsEnum::landscape:
		for (int i = m_selectedMapObjectIndexForEditorWindow; i < m_numOfLandscapeMapObjects; i++)
		{
			m_tileHandler.getTile(m_landscapeMapObjects[i]->getTileIndex())->decrementMapObjectVectorIndex();
		}
		updateLandscapeObjectsTileProperties();
		break;

	default:
		break;
	}
}

void MapCreator::updateLandscapeObjectsTileProperties()
{
	m_terrainObstacleTilesIndexes.clear();

	for (int i = 0; i < m_numOfLandscapeMapObjects; i++)
	{
		std::vector<int> vectorOfOverlappedTiles = getVectorOfOverlappedTiles(m_landscapeMapObjects[i]->getTileIndex(), m_landscapeMapObjects[i]->getGlobalBounds().width, m_landscapeMapObjects[i]->getGlobalBounds().height, m_landscapeMapObjects[i]->getOrigin());
		m_terrainObstacleTilesIndexes.insert(m_terrainObstacleTilesIndexes.end(), vectorOfOverlappedTiles.begin(), vectorOfOverlappedTiles.end());
	}

	for (int tileIndex : m_terrainObstacleTilesIndexes)
	{
		m_tileHandler.getTile(tileIndex)->setIsObstacle(true);
	}
}

//===========================================================================================
// Faction selection
//===========================================================================================
void MapCreator::updateUnitIcons()
{
	for (int i = 0; i < c_numOfUnitsPerFaction; i++)
	{
		if (m_selectedFaction == m_randomFactionIndex)
		{
			m_unitIconButtons[i]->setButtonIcon(m_textures.m_randomUnitIcon);
		}
		else
		{
			m_unitIconButtons[i]->setButtonIcon(m_dataHandler.getFactionData(m_selectedFaction).getUnitData(i).getUnitIcon());
		}
	}
}

//===========================================================================================
// Map Saving
//===========================================================================================
void MapCreator::saveMap()
{
	json mapData;

	int numOfTiles = m_tileHandler.getNumOfHorizontalTiles() * m_tileHandler.getNumOfVerticalTiles();

	//Core map data
	mapData["mapName"] = m_saveWindow.getMapName();
	mapData["numOfPlayers"] = m_saveWindow.getNumberOfPlayers();
	mapData["tileSize"] = m_tileHandler.getTileSize();
	mapData["mapWidth"] = m_tileHandler.getNumOfHorizontalTiles();
	mapData["mapHeight"] = m_tileHandler.getNumOfVerticalTiles();

	//Tile data
	mapData["numberOfTiles"] = numOfTiles;
	for (int i = 0; i < numOfTiles; i++)
	{
		json tileData;
		Tile* pTile = m_tileHandler.getTile(i);
		tileData["isObstacle"] = pTile->getIsObstacle();
		tileData["isOccupied"] = pTile->getIsOccupied();
		tileData["mapObjectType"] = (int)pTile->getMapObjectType();
		tileData["mapObjectVectorIndex"] = pTile->getMapObjectVectorIndex();

		mapData["tiles"].push_back(tileData);
	}

	//Town Objects data
	mapData["numberOfTownObjects"] = m_numOfTownMapObjects;
	for (int i = 0; i < m_numOfTownMapObjects; i++)
	{
		json townData;

		townData["tileIndex"] = m_townMapObjects[i]->getTileIndex();
		townData["ownerIndex"] = m_townMapObjects[i]->getOwnerIndex();
		if (m_townMapObjects[i]->getOwnerIndex() == -1)
		{
			townData["factionIndex"] = rand() % c_numOfFactions;
		}
		else
		{
			townData["factionIndex"] = m_townMapObjects[i]->getFactionIndex();
		}

		mapData["townObjects"].push_back(townData);
	}

	//Unit objects data
	mapData["numberOfUnitObjects"] = m_numOfUnitMapObjects;
	for (int i = 0; i < m_numOfUnitMapObjects; i++)
	{
		json unitData;

		unitData["tileIndex"] = m_unitMapObjects[i]->getTileIndex();

		if (m_unitMapObjects[i]->getFactionIndex() == m_randomFactionIndex)
		{
			unitData["factionIndex"] = rand() % c_numOfFactions;
		}
		else
		{
			unitData["factionIndex"] = m_unitMapObjects[i]->getFactionIndex();
		}

		unitData["unitIndex"] = m_unitMapObjects[i]->getUnitIndex();

		if (m_unitMapObjects[i]->getNumberOfUnits() <= 0)
		{
			unitData["numberOfUnits"] = (int)round((rand() % 50) / (m_unitMapObjects[i]->getUnitIndex() + 1)) + 1;
		}
		else
		{
			unitData["numberOfUnits"] = m_unitMapObjects[i]->getNumberOfUnits();
		}

		mapData["unitObjects"].push_back(unitData);
	}

	//Resource mines objects data
	mapData["numberOfResourceMines"] = m_numOfResourceMinesMapObjects;
	for (int i = 0; i < m_numOfResourceMinesMapObjects; i++)
	{
		json resourceMineData;

		resourceMineData["tileIndex"] = m_resourceMinesMapObjects[i]->getTileIndex();
		resourceMineData["ownerIndex"] = m_resourceMinesMapObjects[i]->getOwnerIndex();
		resourceMineData["mineType"] = (int)m_resourceMinesMapObjects[i]->getMineType();

		mapData["resourceMineObjects"].push_back(resourceMineData);
	}

	//Resource objects data
	mapData["numberOfResources"] = m_numOfResourceMapObjects;
	for (int i = 0; i < m_numOfResourceMapObjects; i++)
	{
		json resourceData;
		resourceData["tileIndex"] = m_resourceMapObjects[i]->getTileIndex();

		if (m_resourceMapObjects[i]->getResourceType() == ResourcesEnum::random)
		{
			resourceData["resourceType"] = rand() % c_numOfResourceMines; //There is a mine for every resource
		}
		else
		{
			resourceData["resourceType"] = (int)m_resourceMapObjects[i]->getResourceType();
		}

		if (m_resourceMapObjects[i]->getResourceAmount() == 0)
		{
			int value = 1;
			switch ((ResourcesEnum)resourceData["resourceType"])
			{
			case ResourcesEnum::gold:
				value = 250;
				break;

			case ResourcesEnum::wood:
			case ResourcesEnum::stone:
				value = 3;
				break;

			default:
				break;
			}

			resourceData["resourceAmount"] = ((rand() % 4) + 1) * value;
		}
		else
		{
			resourceData["resourceAmount"] = m_resourceMapObjects[i]->getResourceAmount();
		}

		mapData["resourceObjects"].push_back(resourceData);
	}

	//Special building objects data
	mapData["numberOfSpecialBuildings"] = m_numOfSpecialBuildingMapObjects;
	for (int i = 0; i < m_numOfSpecialBuildingMapObjects; i++)
	{
		json specialBuildingData;

		specialBuildingData["tileIndex"] = m_specialBuildingsMapObjects[i]->getTileIndex();
		specialBuildingData["isVisited"] = m_specialBuildingsMapObjects[i]->getIsVisited();
		specialBuildingData["buildingType"] = (int)m_specialBuildingsMapObjects[i]->getBuildingType();

		mapData["specialBuildingObjects"].push_back(specialBuildingData);
	}

	//Landscape objects
	mapData["numberOfLandscapeObjects"] = m_numOfLandscapeMapObjects;
	for (int i = 0; i < m_numOfLandscapeMapObjects; i++)
	{
		json landscapeData;

		landscapeData["tileIndex"] = m_landscapeMapObjects[i]->getTileIndex();
		landscapeData["objectType"] = (int)m_landscapeMapObjects[i]->getLandscapeType();
		landscapeData["objectIndex"] = m_landscapeMapObjects[i]->getObjectIndex();

		mapData["landscapeObjects"].push_back(landscapeData);
	}

	m_dataHandler.saveMapData(m_saveWindow.getMapName(), mapData);

	std::cout << "Map '" << m_saveWindow.getMapName() << "' has been saved\n";

	closeSaveMapWindow();
}

void MapCreator::closeSaveMapWindow()
{
	m_isSaveWindowActive = false;
}

//===========================================================================================
// Drawing
//===========================================================================================

void MapCreator::draw()
{
	m_viewManager.setGameView();
	drawGame();

	m_viewManager.setUIView();
	drawUI();
}

void MapCreator::drawTileOverlap()
{
	m_tileOverlap.setColor(sf::Color(255, 0, 0, 90)); //Red colour

	for (int tileIndex : m_obstacleTilesIndexes)
	{
		m_tileOverlap.setPosition(m_tileHandler.getTile(tileIndex)->getPosition());
		m_window.draw(m_tileOverlap);
	}

	for (int tileIndex : m_terrainObstacleTilesIndexes)
	{
		m_tileOverlap.setPosition(m_tileHandler.getTile(tileIndex)->getPosition());
		m_window.draw(m_tileOverlap);
	}

	m_tileOverlap.setColor(sf::Color(255, 255, 0, 128));

	for (int tileIndex : m_occupiedTileIndexes)
	{
		m_tileOverlap.setPosition(m_tileHandler.getTile(tileIndex)->getPosition());
		m_window.draw(m_tileOverlap);
	}
}

void MapCreator::drawUI()
{
	for (int i = 0; i < MapCreatorSettings::c_numOfprimaryButtons; i++)
	{
		m_primaryButtons[i]->draw();
	}

	if (m_dropDownIndex > -1)
	{
		for (int i = 0; i < MapCreatorSettings::c_numOfSecondaryButtonsPerSection[m_dropDownIndex]; i++)
		{
			m_secondaryButtons[m_dropDownIndex][i]->draw();
		}
	}

	//Draw drop down landscape icons
	switch (m_dropDownIndex)
	{
	case 5: //Trees
		for (int i = 0; i < MapCreatorSettings::c_numOfTreeLandscapes; i++)
		{
			m_window.draw(m_treeLandscapes[i]);
		}
		break;

	case 6: //Rocky
		for (int i = 0; i < MapCreatorSettings::c_numOfRockyLandscapes; i++)
		{
			m_window.draw(m_rockyLandscapes[i]);
		}
		break;

	case 7: //Other
		for (int i = 0; i < MapCreatorSettings::c_numOfOtherLandscapes; i++)
		{
			m_window.draw(m_otherLandscapes[i]);
		}
		break;

	default:
		break;
	}

	if (m_isSetMapSizeActive)
	{
		for (int i = 0; i < MapCreatorSettings::c_numOfInputBoxes; i++)
		{
			m_inputBoxes[i]->draw();
		}

		m_applyMapSizeButton.draw();
	}

	for (int i = 0; i < c_numOfUnitsPerFaction; i++)
	{
		m_unitIconButtons[i]->draw();
	}
	m_unitIconButtonsBackground.drawUIBorder();

	if (m_isEditorActive)
	{
		m_editorWindow.draw();
	}

	if (m_isSaveWindowActive)
	{
		m_saveWindow.draw();
	}
}

void MapCreator::drawGame()
{
	m_tileHandler.draw();

	if (m_numOfLandscapeMapObjects > 0)
	{
		for (int i = 0; i < m_numOfLandscapeMapObjects; i++)
		{
			m_window.draw(*m_landscapeMapObjects[i]);
		}
	}

	if (m_numOfResourceMapObjects > 0)
	{
		for (int i = 0; i < m_numOfResourceMapObjects; i++)
		{
			m_window.draw(*m_resourceMapObjects[i]);
		}
	}

	if (m_numOfResourceMinesMapObjects > 0)
	{
		for (int i = 0; i < m_numOfResourceMinesMapObjects; i++)
		{
			m_window.draw(*m_resourceMinesMapObjects[i]);
		}
	}

	if (m_numOfSpecialBuildingMapObjects > 0)
	{
		for (int i = 0; i < m_numOfSpecialBuildingMapObjects; i++)
		{
			m_window.draw(*m_specialBuildingsMapObjects[i]);
		}
	}

	if (m_numOfUnitMapObjects > 0)
	{
		for (int i = 0; i < m_numOfUnitMapObjects; i++)
		{
			m_window.draw(*m_unitMapObjects[i]);
		}
	}

	if (m_numOfTownMapObjects > 0)
	{
		for (int i = 0; i < m_numOfTownMapObjects; i++)
		{
			m_window.draw(*m_townMapObjects[i]);
		}
	}

	if (m_isMapObjectSelected)
	{
		m_window.draw(m_cursor);
	}

	if (m_drawTileOverlap)
	{
		drawTileOverlap();
	}
}