#include "CombatHandler.h"

namespace settings = CombatHandlerSettings;

CombatHandler::CombatHandler(sf::RenderWindow& rWindow, Textures& rTextures, DataHandler& rDataHandler, Fonts& rFonts) :
	m_window(rWindow),
	m_textures(rTextures),
	m_fonts(rFonts),
	m_dataHandler(rDataHandler),
	m_tileHandler(rWindow, &rTextures),
	m_unitTurnOrderBar(rWindow, rTextures, rFonts),
	m_combatCursor(m_combatUnits, m_tileIndexesThatAreWithinUnitsMovementRange),
	m_unitInformationCard(rWindow, rTextures, rFonts),
	m_background(rWindow, &rTextures),
	m_combatBackgroundBorder(rWindow, &rTextures),
	m_combatEndPopUp(rWindow, rTextures, rFonts),
	m_logsConsole(rWindow, rTextures, rFonts),
	m_attackerAI(m_tileHandler, m_combatUnits),
	m_defenderAI(m_tileHandler, m_combatUnits),
	m_pAttackerHero(nullptr),
	m_pDefenderHero(nullptr),
	m_pDefenderMapUnit(nullptr),
	m_pTownUnitsVectorPointer(nullptr),
	m_numOfAttackerUnits(0),
	m_numOfDefenderUnits(0),
	m_didUnitMakeAMove(false),
	m_currentTurn(0),
	m_currentUnitTurnIndex(0),
	m_unitIndexToInteractWith(0),
	m_tileIndexToInteractWith(0),
	m_canCurrentlySelectedUnitsInteract(false),
	m_didUnitMove(false),
	m_isCombatActive(false),
	m_isAttackerAI(false),
	m_isDefenderAI(false),
	m_combatType(CombatTypeEnum::playerVsPlayer),
	m_didAttackerWin(false),
	m_isPlayerWatching(false),
	m_selectedUnitAlpha(255),
	m_drawCurrentTurnUnitIndicator(true),
	m_bloodSplash(rWindow)
{
}

CombatHandler::~CombatHandler()
{
}

void CombatHandler::setUpCombatAreaAndUI()
{
	int combatAreaStartPosX = (m_window.getSize().x - settings::c_numOfHorizontalTiles * settings::c_tileSize) * 0.5f;
	int combatAreaStartPosY = (m_window.getSize().y - settings::c_numOfVerticalTiles * settings::c_tileSize + settings::c_tileSize * 2) * 0.5f;

	//Background
	m_background.setPosition(m_window.getView().getCenter());
	m_background.setUpUIBorder(m_window.getSize().x - c_UIBorder, m_window.getSize().y - c_UIBorder);

	//Combat background
	m_combatBackground.setTexture(m_textures.m_battleBackgrounds[0], true);
	m_combatBackground.setOrigin(m_combatBackground.getGlobalBounds().width * 0.5f, m_combatBackground.getGlobalBounds().height * 0.5f);
	m_combatBackground.setPosition(m_window.getView().getCenter());

	//CombatBackground border
	m_combatBackgroundBorder.setPosition(m_window.getView().getCenter());
	m_combatBackgroundBorder.setUpUIBorder(m_textures.m_battleBackgrounds[0].getSize().x, m_textures.m_battleBackgrounds[0].getSize().y);

	//Tiles
	m_tileHandler.setsIsCombatTiles(true);
	m_tileHandler.setUpTiles(settings::c_numOfHorizontalTiles, settings::c_numOfVerticalTiles, settings::c_tileSize, combatAreaStartPosX, combatAreaStartPosY);

	//Unit Order Bar
	m_unitTurnOrderBar.setUp(m_combatBackground.getPosition().y + m_combatBackground.getTexture()->getSize().y * 0.5f);

	//Buttons
	for (int i = 0; i < settings::c_numOfButtons; i++)
	{
		m_buttons.push_back(std::unique_ptr<IconButton>(new IconButton(m_window, &m_textures, true)));
		m_buttons[i]->setUpAndResizeToSprite(m_combatBackground.getPosition().x + m_combatBackground.getGlobalBounds().width * 0.5f - UnitTurnOrderBarSettings::c_unitIconWidth * 1.25f - i * (UnitTurnOrderBarSettings::c_unitIconWidth + UnitTurnOrderBarSettings::c_unitIconBorder), m_combatBackground.getPosition().y + m_combatBackground.getTexture()->getSize().y * 0.5f, m_textures.m_battleButtonIcons[i]);
	}

	//Combat AI
	m_attackerAI.setUpCombatAIVariables(settings::c_tileSize, &m_tileIndexesThatAreWithinUnitsMovementRange, std::bind(&CombatHandler::attack, this), std::bind(&CombatHandler::defend, this), std::bind(&CombatHandler::wait, this), std::bind(&CombatHandler::moveUnit, this, std::placeholders::_1));
	m_defenderAI.setUpCombatAIVariables(settings::c_tileSize, &m_tileIndexesThatAreWithinUnitsMovementRange, std::bind(&CombatHandler::attack, this), std::bind(&CombatHandler::defend, this), std::bind(&CombatHandler::wait, this), std::bind(&CombatHandler::moveUnit, this, std::placeholders::_1));

	//Player feedback
	m_tileFill.setTexture(m_textures.m_combatTileFill);

	m_currentTurnUnitIndicator.setTexture(m_textures.m_currentUnitIndicator);

	m_bloodSplash.setUpAnimation(m_textures.m_bloodSplashSpriteSheet, settings::c_textureSize, settings::c_textureSize, settings::c_numOfFrames, false, true);

	m_combatCursor.setTileHandler(&m_tileHandler);
	m_combatCursor.setUpMouseCursor(m_textures.m_combatCursorTexture, settings::c_tileSize);

	m_unitInformationCard.initialize(m_window.getView().getCenter().x, settings::c_unitInformationCardYOffset);

	m_combatEndPopUp.setUp();

	int consolePosX = (m_background.getPosition().x - m_combatBackground.getGlobalBounds().width * 0.5f) * 0.5f;
	m_logsConsole.setUpLogConsole(consolePosX, m_window.getView().getCenter().y, settings::c_consoleWidth, m_combatBackground.getGlobalBounds().height, settings::c_consoleTextSize, settings::c_consoleTitleSize, settings::c_consoleTitle);
}


void CombatHandler::setUpPlayerVsPlayer(Hero* attackerHero, Hero* defenderHero, const bool isAttackerAI, const bool isDefenderAI)
{
	resetCombatHandlerVariables(); //Makes sure that everything is reset

	if (!isAttackerAI || !isDefenderAI)
	{
		m_isPlayerWatching = true;
	}
	else
	{
		m_isPlayerWatching = false;
	}

	m_combatType = CombatTypeEnum::playerVsPlayer;
	m_isAttackerAI = isAttackerAI;
	m_isDefenderAI = isDefenderAI;

	m_pAttackerHero = attackerHero;
	m_pDefenderHero = defenderHero;


	//Attacker
	setHeroUnits(attackerHero, attackerHero->getCurrentNumberOfUnits());
	m_numOfAttackerUnits = attackerHero->getCurrentNumberOfUnits(); //Number of units is set after settings units as number of attacker units is used to determine vector position of a unit that is being set (see setHeroUnits)

	//Defender
	setHeroUnits(defenderHero, defenderHero->getCurrentNumberOfUnits());
	m_numOfDefenderUnits = defenderHero->getCurrentNumberOfUnits();

	setUpCombatUnits();

	setUpAI();
}

void CombatHandler::setUpPlayerVsMapUnit(Hero* attackerHero, UnitMapObject* mapUnit, const bool isAttackerAI)
{
	resetCombatHandlerVariables();

	if (!isAttackerAI)
	{
		m_isPlayerWatching = true;
	}
	else
	{
		m_isPlayerWatching = false;
	}

	m_combatType = CombatTypeEnum::playerVsMapUnit;
	m_isAttackerAI = isAttackerAI;
	m_isDefenderAI = true;

	m_pAttackerHero = attackerHero;
	m_pDefenderMapUnit = mapUnit;

	//Attacker
	setHeroUnits(attackerHero, attackerHero->getCurrentNumberOfUnits());
	m_numOfAttackerUnits = attackerHero->getCurrentNumberOfUnits();

	//Defender
	setMapUnitObjectUnits(mapUnit);
	//num of defender units is set in function above

	setUpCombatUnits();

	setUpAI();
}

void CombatHandler::setUpPlayerVsTown(Hero* attackerHero, std::vector<std::shared_ptr<Unit>>* townUnits, const bool isAttackerAI, const bool isDefenderAI)
{
	resetCombatHandlerVariables();

	if (!isAttackerAI || !isDefenderAI)
	{
		m_isPlayerWatching = true;
	}
	else
	{
		m_isPlayerWatching = false;
	}

	m_combatType = CombatTypeEnum::playerVsTown;
	m_isAttackerAI = isAttackerAI;
	m_isDefenderAI = isDefenderAI;

	m_pAttackerHero = attackerHero;
	m_pTownUnitsVectorPointer = townUnits;

	//Attacker
	setHeroUnits(attackerHero, attackerHero->getCurrentNumberOfUnits());
	m_numOfAttackerUnits = attackerHero->getCurrentNumberOfUnits();

	setTownUnits(*townUnits);
	//num of defender units is set in function above

	setUpCombatUnits();

	setUpAI();
}

void CombatHandler::setHeroUnits(Hero* hero, const int& m_numberOfUnitsToSet)
{
	for (int i = m_numOfAttackerUnits; i < m_numOfAttackerUnits + m_numberOfUnitsToSet; i++)
	{
		m_combatUnits.push_back(std::unique_ptr<CombatUnit>(new CombatUnit(m_window, m_textures, m_fonts))); //Allocate memory for new units
		m_combatUnits[i]->setFunctionToCallWhenObjectArrivesAtDestination(std::bind(&CombatHandler::attack, this));
	}

	int setUnitIndex = m_numOfAttackerUnits; //Important to keep, used to determine vector position of new combat unit

	for (int i = 0; i < c_numOfUnitsPerFaction; i++)
	{
		if (hero->getUnit(i).getIsDataSet()) //Checks if unit data is allocated
		{
			m_combatUnits[setUnitIndex]->setUnit((hero->getUnit(i))); //Sets unit data
			setUnitIndex++;
		}
	}
}

void CombatHandler::setMapUnitObjectUnits(UnitMapObject* mapUnit)
{
	m_numOfDefenderUnits = splitMapUnitIntoIndividualUnits(mapUnit);

	int numberOfUnits = mapUnit->getNumberOfUnits();
	int unitRemainder = numberOfUnits % m_numOfDefenderUnits;
	int numOfUnitsPerDefender = numberOfUnits / m_numOfDefenderUnits;

	for (int i = 0; i < m_numOfDefenderUnits; i++)
	{
		m_combatUnits.push_back(std::unique_ptr<CombatUnit>(new CombatUnit(m_window, m_textures, m_fonts))); //Allocate memory for new units
		m_combatUnits[m_numOfAttackerUnits + i]->setFunctionToCallWhenObjectArrivesAtDestination(std::bind(&CombatHandler::attack, this));
	}

	int setUnitIndex = m_numOfAttackerUnits;  //Important to keep, used to determine vector position of defender combat unit

	for (int i = 0; i < m_numOfDefenderUnits; i++)
	{
		m_combatUnits[setUnitIndex]->setUnit(m_dataHandler.getFactionData(mapUnit->getFactionIndex()).getUnitData(mapUnit->getUnitIndex())); //Sets unit data
		m_combatUnits[setUnitIndex]->setNumOfUnits(numOfUnitsPerDefender); //Set number of units
		setUnitIndex++;
	}

	//Assign remainder of units to a random unit
	int randomDefenderUnitIndex = rand() % m_numOfDefenderUnits;
	if (randomDefenderUnitIndex >= m_numOfDefenderUnits)
	{
		randomDefenderUnitIndex--;
	}
	m_combatUnits[m_numOfAttackerUnits + randomDefenderUnitIndex]->incrementNumOfUnits(unitRemainder);
}

void CombatHandler::setTownUnits(std::vector<std::shared_ptr<Unit>>& townUnits)
{
	int numberOfUnits = 0;
	for (auto& unit : townUnits)
	{
		if (unit->getIsDataSet())
		{
			m_combatUnits.push_back(std::unique_ptr<CombatUnit>(new CombatUnit(m_window, m_textures, m_fonts))); //Allocate memory for new units
			m_combatUnits[m_numOfAttackerUnits + numberOfUnits]->setFunctionToCallWhenObjectArrivesAtDestination(std::bind(&CombatHandler::attack, this));
			m_combatUnits[m_numOfAttackerUnits + numberOfUnits]->setUnit(*unit);

			numberOfUnits++;
		}
	}
	m_numOfDefenderUnits = numberOfUnits;
}

const int CombatHandler::splitMapUnitIntoIndividualUnits(UnitMapObject* mapUnit)
{
	int numberOfUnits = mapUnit->getNumberOfUnits();
	int unitIndex = mapUnit->getUnitIndex();

	//Determine number of individual units
	int numberOfIndividualUnits = rand() % (c_numOfUnitsPerFaction - unitIndex) + 1;

	if (numberOfIndividualUnits > c_numOfUnitsPerFaction) //Makes sure that max number of individual units doesn't exceed the unit limit
	{
		numberOfIndividualUnits = c_numOfUnitsPerFaction;
	}

	while ( numberOfIndividualUnits && numberOfUnits / numberOfIndividualUnits < settings::c_minimumNumOfUnitsPerCombatUnits ) //Makes sure each unit is above minimal num of units threshold
	{
		numberOfIndividualUnits--;
	}

	if (numberOfIndividualUnits < 1) // Makes sure there is at least 1 individual unit
	{
		numberOfIndividualUnits = 1;
	}

	return numberOfIndividualUnits;
}

void CombatHandler::setUpCombatUnits()
{
	//Attacker units
	for (int i = 0; i < m_numOfAttackerUnits; i++)
	{
		int tileIndex = settings::c_startUnitPositions[m_numOfAttackerUnits - 1][i] * settings::c_numOfHorizontalTiles;
		Tile* tile = m_tileHandler.getTile(tileIndex);

		//Set tile properties
		tile->setIsOccupied(true);
		tile->setIsObstacle(true);
		tile->setMapObjectVectorIndex(i);

		if (m_combatUnits[i]->getIsLargeUnit()) //Set additional tile properites if unit is large and occupies 2 tiles
		{
			tileIndex++; //Get tile to the right
			tile = m_tileHandler.getTile(tileIndex);
			tile->setIsOccupied(true);
			tile->setIsObstacle(true);
			tile->setMapObjectVectorIndex(i);
		}

		//Set unit properties
		m_combatUnits[i]->setIsAttacker(true);
		m_combatUnits[i]->MoveableObject::setPosition(tile->getPosition());
		m_combatUnits[i]->updateTextBoxPosition();
		m_combatUnits[i]->getNumberOfUnitsTextBox().setTextAndUpdate(std::to_string(m_combatUnits[i]->getNumOfUnits()));
		m_combatUnits[i]->setOccupiedTileIndex(tileIndex);
		m_combatUnits[i]->setVectorPositionIndex(i);
		m_combatUnits[i]->setIsUnitAI(m_isAttackerAI);
	}

	//Defender Units
	int setUpDefenderUnits = 0;
	for (int i = m_numOfAttackerUnits; i < m_combatUnits.size(); i++)
	{
		int tileIndex = settings::c_startUnitPositions[m_numOfDefenderUnits - 1][setUpDefenderUnits] * settings::c_numOfHorizontalTiles + settings::c_numOfHorizontalTiles - 1;
		Tile* tile = m_tileHandler.getTile(tileIndex);

		//Set tile properties
		tile->setIsOccupied(true);
		tile->setIsObstacle(true);
		tile->setMapObjectVectorIndex(i);

		if (m_combatUnits[i]->getIsLargeUnit()) //Set additional tile properites if unit is large and occupies 2 tiles
		{
			tileIndex--; //Get tile to the left
			tile = m_tileHandler.getTile(tileIndex);
			tile->setIsOccupied(true);
			tile->setIsObstacle(true);
			tile->setMapObjectVectorIndex(i);
		}

		//Set unit properties
		m_combatUnits[i]->setIsAttacker(false);
		m_combatUnits[i]->MoveableObject::setPosition(tile->getPosition());
		m_combatUnits[i]->MoveableObject::setScale(-1, 1);
		m_combatUnits[i]->setDefenderSpriteOrigin();
		m_combatUnits[i]->updateTextBoxPosition();
		m_combatUnits[i]->getNumberOfUnitsTextBox().setTextAndUpdate(std::to_string(m_combatUnits[i]->getNumOfUnits()));
		m_combatUnits[i]->setOccupiedTileIndex(tileIndex);
		m_combatUnits[i]->setVectorPositionIndex(i);
		m_combatUnits[i]->setIsUnitAI(m_isDefenderAI);

		setUpDefenderUnits++;
	}

	Global::g_UILayer = UILayerEnum::combat;
	Global::toggleUpdateGame();

	updateDrawingOrder();

	setTurnOrder();
	m_currentUnitTurnIndex = m_unitTurnOrder[0];

	setCurrentUnitTurnIndicator();

	showTileProperties();

	setTilesThatAreWithinUnitMovementRange();

	m_isCombatActive = true;
}

void CombatHandler::setUpAI()
{
	if (m_isAttackerAI)
	{
		m_attackerAI.setAIParameters(true);
	}

	if (m_isDefenderAI)
	{
		m_defenderAI.setAIParameters(false);
	}
}


void CombatHandler::setTurnOrder()
{
	m_unitTurnOrder.clear();

	int currentUnitIndex = 0;
	int unitTurnIndex = 0;
	bool wasUnitPlaced = false;

	for (auto& unit : m_combatUnits)
	{
		if (m_unitTurnOrder.empty()) //If the vector is empty, add it's first unit index
		{
			m_unitTurnOrder.push_back(currentUnitIndex);
		}
		else 
		{
			unitTurnIndex = 0;
			for (int& unitIndex : m_unitTurnOrder) //Check if units speed is greater than currently checked unit in the turn order vector
			{
				wasUnitPlaced = false;
				if (m_combatUnits[currentUnitIndex]->getUnitSpecificData(UnitBattleDataEnum::speed) > m_combatUnits[unitIndex]->getUnitSpecificData(UnitBattleDataEnum::speed))
				{
					m_unitTurnOrder.insert(m_unitTurnOrder.begin() + unitTurnIndex, currentUnitIndex); 
					wasUnitPlaced = true;
					break;
				}
				unitTurnIndex++;
			}

			if (!wasUnitPlaced) //If unit wasnt inserted, place it at the back of the que
			{
				m_unitTurnOrder.push_back(currentUnitIndex);
			}
		}
		currentUnitIndex++;
	}

	m_unitTurnOrderBar.setUnitCards(m_combatUnits, m_unitTurnOrder);
}


void CombatHandler::resetCombatHandlerVariables()
{
	srand(time(NULL)); //Set new pseudo-random sequence

	m_tileHandler.resetNavigationGraph();
	for (int i = 0; i < m_tileHandler.getNumOfHorizontalTiles() * m_tileHandler.getNumOfVerticalTiles(); i++)
	{
		m_tileHandler.getTile(i)->resetTileProperties();
	}

	m_combatUnits.clear();
	m_unitTurnOrder.clear();
	m_unitIndexesToDeleteFromTurnQue.clear();
	m_unitDrawOrder.clear();
	m_tileIndexesThatAreWithinUnitsMovementRange.clear();

	m_numOfAttackerUnits = 0;
	m_numOfDefenderUnits = 0;
	m_currentTurn = 0;
	m_selectedUnitAlpha = 255;

	m_didUnitMove = false;
	m_drawCurrentTurnUnitIndicator = true;
	m_canCurrentlySelectedUnitsInteract = false;
	m_didUnitMakeAMove = false;

	m_bloodSplash.stopAnimation();

	m_logsConsole.clearText();
}


void CombatHandler::update(const sf::Vector2f& mousePosition, const float& deltaTime)
{
	if (m_isPlayerWatching)
	{
		updateIfAtLeastOnePlayer(mousePosition, deltaTime);
	}
	else
	{
		updateAIvsAI();
	}
}

void CombatHandler::updateAIvsAI()
{
	while (m_isCombatActive)
	{
		if (m_combatUnits[m_currentUnitTurnIndex]->getIsAttacker())
		{
			m_attackerAI.takeTurn(m_currentUnitTurnIndex);
		}
		else
		{
			m_defenderAI.takeTurn(m_currentUnitTurnIndex);
		}
	}
}

void CombatHandler::updateIfAtLeastOnePlayer(const sf::Vector2f& mousePosition, const float& deltaTime)
{
	m_combatCursor.update(mousePosition, m_currentUnitTurnIndex);

	if (m_isCombatActive)
	{
		if (!m_combatUnits[m_currentUnitTurnIndex]->getIsUnitAI()) //Don't update for AI
		{
			if (Global::g_isLMBPressed)
			{
				updateUI(mousePosition);

				if (!m_didUnitMakeAMove)
				{
					if (!checkIfInteractionWithEnemyUnitWasInitiated(mousePosition))
					{
						checkForUnitMovement(mousePosition);
					}
				}
			}
		}
		else if (!m_didUnitMakeAMove)
		{
			if (m_combatUnits[m_currentUnitTurnIndex]->getIsAttacker())
			{
				m_attackerAI.takeTurn(m_currentUnitTurnIndex);
			}
			else
			{
				m_defenderAI.takeTurn(m_currentUnitTurnIndex);
			}
		}

		if (Global::g_isRMBPressed)
		{
			checkIfPlayerActivatedUnitCard(mousePosition);
			Global::RMBPressed();
		}

		m_bloodSplash.updateAnimation(deltaTime);

		updateCurrentUnitTurnFeedback();

		m_combatUnits[m_currentUnitTurnIndex]->update(deltaTime);
	}
	else
	{
		if (Global::g_isLMBPressed && m_combatEndPopUp.update(mousePosition))
		{
			Global::objectPressed();
			endCombat();
		}
	}
}

void CombatHandler::updateUI(const sf::Vector2f& mousePosition)
{
	if (m_isPlayerWatching)
	{
		for (int i = 0; i < settings::c_numOfButtons; i++)
		{
			if (m_buttons[i]->collisionCheck(mousePosition))
			{
				Global::objectPressed();

				switch (static_cast<CombatHandlerButtons>(i))
				{
				case CombatHandlerButtons::wait:
					wait();
					break;

				case CombatHandlerButtons::defend:
					defend();
					break;

				case CombatHandlerButtons::autoCombat:
					setAutoCombat();
					break;

				default:
					break;
				}
			}
		}
	}
}

const bool CombatHandler::checkIfInteractionWithEnemyUnitWasInitiated(const sf::Vector2f mousePosition)
{
	int tileIndex = m_tileHandler.checkTileCollision(mousePosition);
	bool isEnemyUnitNextToCurrentUnit = false;
	bool didCurrentUnitInteractWithEnemyUnit = false;
	m_canCurrentlySelectedUnitsInteract = false;

	Global::objectPressed();

	if (tileIndex > -1) //Makes sure the index is valid
	{
		Tile* tile = m_tileHandler.getTile(tileIndex);

		if (tile->getIsOccupied()) //True == unit is on this tile
		{
			int unitIndexToInteractWith = tile->getMapObjectVectorIndex();
			//Check if units are in the same army
			if (m_combatUnits[m_currentUnitTurnIndex]->getIsAttacker() != m_combatUnits[unitIndexToInteractWith]->getIsAttacker())
			{
				//Units aren't in the same army
				m_unitIndexToInteractWith = unitIndexToInteractWith;
				m_tileIndexToInteractWith = tileIndex;
				m_canCurrentlySelectedUnitsInteract = true;

				//Check if current unit is ranged
				if (m_combatUnits[m_currentUnitTurnIndex]->getBaseUnitData()->getIntData(UnitDataEnum::isRanged))
				{
					attack();
					didCurrentUnitInteractWithEnemyUnit = true;
				}
				else
				{
					//Check if units are next to each other
					if (checkIfObjectsAreNextToEachother(m_combatUnits[m_currentUnitTurnIndex]->getPosition(), tile->getPosition()))
					{
						isEnemyUnitNextToCurrentUnit = true;
					}
					else
					{
						if (m_combatUnits[unitIndexToInteractWith]->getIsLargeUnit()) //If unit is large, check if you can interact with the other tile its occuping
						{
							sf::Vector2f temp = m_combatUnits[unitIndexToInteractWith]->getPosition();

							if (m_combatUnits[unitIndexToInteractWith]->getIsAttacker()) //Attacker
							{
								//Get tile position on the left of the main tile
								temp.x -= settings::c_tileSize;
							}
							else //Defender
							{
								//Get tile position on the right of the main tile
								temp.x += settings::c_tileSize;
							}

							isEnemyUnitNextToCurrentUnit = checkIfObjectsAreNextToEachother(m_combatUnits[m_currentUnitTurnIndex]->getPosition(), temp);
						}
					}

					//Check if attacking unit is large and next to each other
					if (!isEnemyUnitNextToCurrentUnit && m_combatUnits[m_currentUnitTurnIndex]->getIsLargeUnit())
					{
						sf::Vector2f tempAttacker = m_combatUnits[m_currentUnitTurnIndex]->getPosition();

						if (m_combatUnits[m_currentUnitTurnIndex]->getIsAttacker()) //Attacker
						{
							//Get tile position on the left of the main tile
							tempAttacker.x -= settings::c_tileSize;
						}
						else //Defender
						{
							//Get tile position on the right of the main tile
							tempAttacker.x += settings::c_tileSize;
						}

						isEnemyUnitNextToCurrentUnit = checkIfObjectsAreNextToEachother(m_combatUnits[unitIndexToInteractWith]->getPosition(), tempAttacker);

						if (!isEnemyUnitNextToCurrentUnit && m_combatUnits[unitIndexToInteractWith]->getIsLargeUnit())
						{
							sf::Vector2f tempDefender = m_combatUnits[unitIndexToInteractWith]->getPosition();

							if (m_combatUnits[unitIndexToInteractWith]->getIsAttacker()) //Attacker
							{
								//Get tile position on the left of the main tile
								tempDefender.x -= settings::c_tileSize;
							}
							else //Defender
							{
								//Get tile position on the right of the main tile
								tempDefender.x += settings::c_tileSize;
							}

							isEnemyUnitNextToCurrentUnit = checkIfObjectsAreNextToEachother(tempAttacker, tempDefender);
						}
					}
				}
			}

			if (isEnemyUnitNextToCurrentUnit)
			{
				didCurrentUnitInteractWithEnemyUnit = true;
				m_didUnitMakeAMove = true;
				attack();
			}
			else if (!didCurrentUnitInteractWithEnemyUnit)
			{
				moveUnit(tileIndex);
				//Unit Interaction is called when unit arrives at the destination
			}
		}
	}

	return didCurrentUnitInteractWithEnemyUnit;
}

const bool CombatHandler::checkIfObjectsAreNextToEachother(const sf::Vector2f& unitA, const sf::Vector2f& unitB)
{
	//Check x and y distance between each position
	return (abs(unitA.x - unitB.x) <= settings::c_tileSize && abs(unitA.y - unitB.y) <= settings::c_tileSize); //If distance is smaller than tile size, units are next to eachother
}

void CombatHandler::attack()
{
	if (m_didUnitMove)
	{
		updateTilePropertiesAfterUnitMoved();
		m_didUnitMove = false;
	}

	updateDrawingOrder();

	if (m_combatUnits[m_currentUnitTurnIndex]->getIsUnitAI())
	{
		if (m_combatUnits[m_currentUnitTurnIndex]->getIsAttacker())
		{
			m_unitIndexToInteractWith = m_attackerAI.getUnitIndexToInteractWith();
			m_tileIndexToInteractWith = m_attackerAI.getTileIndexToInteractWith();
			m_canCurrentlySelectedUnitsInteract = m_attackerAI.getCanUnitsInteract();
		}
		else
		{
			m_unitIndexToInteractWith = m_defenderAI.getUnitIndexToInteractWith();
			m_tileIndexToInteractWith = m_defenderAI.getTileIndexToInteractWith();
			m_canCurrentlySelectedUnitsInteract = m_defenderAI.getCanUnitsInteract();
		}
	}

	bool areUnitsNextToEachother = false;
	if (m_canCurrentlySelectedUnitsInteract)
	{
		//Attack
		CombatUnit& attacker = *m_combatUnits[m_currentUnitTurnIndex];
		CombatUnit& defender = *m_combatUnits[m_unitIndexToInteractWith];

		areUnitsNextToEachother = checkIfObjectsAreNextToEachother(attacker.getPosition(), m_tileHandler.getTile(m_tileIndexToInteractWith)->getPosition());

		if (!areUnitsNextToEachother && attacker.getIsLargeUnit())
		{
			int largeUnitTileIndex = attacker.getOccupiedTileIndex();
			if (attacker.getIsAttacker())
			{
				largeUnitTileIndex--;
			}
			else
			{
				largeUnitTileIndex++;
			}
			areUnitsNextToEachother = checkIfObjectsAreNextToEachother(m_tileHandler.getTile(largeUnitTileIndex)->getPosition(), m_tileHandler.getTile(m_tileIndexToInteractWith)->getPosition());
		}

		if (attacker.getBaseUnitData()->getIntData(UnitDataEnum::isRanged) || areUnitsNextToEachother || m_combatUnits[m_currentUnitTurnIndex]->getIsUnitAI()) //Make sure units can interact with eachother
		{
			float bonusDamagePercentage = 1;
			bonusDamagePercentage += ((attacker.getUnitSpecificData(UnitBattleDataEnum::attack) - defender.getUnitSpecificData(UnitBattleDataEnum::attack)) * settings::c_bonusPercentagePerPointDifference) / 100; //Calculate bonus damage percentage

			//Get min and max damage
			int minDamage = attacker.getBaseUnitData()->getIntData(UnitDataEnum::minDamage);
			int maxDamage = attacker.getBaseUnitData()->getIntData(UnitDataEnum::maxDamage);

			int damage = 0;

			if (maxDamage - minDamage > 0) //If damage range is greater than 0, randomise damage value
			{
				damage = rand() % (maxDamage - minDamage) + minDamage;
			}
			else
			{
				damage = minDamage;
			}

			int damageToDeal = static_cast<int>((damage * attacker.getNumOfUnits()) * bonusDamagePercentage); //Calculate damage

			//Determine how many units perished
			int enemyUnitsPerished = std::floor(damageToDeal / defender.getUnitSpecificData(UnitBattleDataEnum::health));

			if (enemyUnitsPerished > defender.getNumOfUnits())
			{
				enemyUnitsPerished = defender.getNumOfUnits();
			}
			else
			{
				//Calculate remainder damage to deal
				int remainderDamageToDeal = damageToDeal - enemyUnitsPerished * defender.getUnitSpecificData(UnitBattleDataEnum::health);
				int defenderCurrentHealth = defender.getCurrentHealth();

				defenderCurrentHealth -= remainderDamageToDeal;

				if (defenderCurrentHealth < 1) //If health is below 1, unit has perished
				{
					defender.incrementNumOfUnits(-1);
					defender.resetCurrentHealth();
					//If current healt goes to negative it will equal to the damage the unit will take after a unit has perished
					defender.incrementCurrentHealth(defenderCurrentHealth);
					enemyUnitsPerished++;
				}
				else
				{
					defender.setCurrentHealth(defenderCurrentHealth);
				}
			}
			defender.incrementNumOfUnits(-enemyUnitsPerished);

			//Player feedback
			std::string consoleText = m_combatUnits[m_unitIndexToInteractWith]->getBaseUnitData()->getStringData(UnitDataEnum::unitName) + " took " + std::to_string(damageToDeal) + " damage\n" + std::to_string(enemyUnitsPerished) + " Units perished\n";
			m_logsConsole.addText(consoleText);
			m_canCurrentlySelectedUnitsInteract = false;

			//Update number of units displayed
			defender.getNumberOfUnitsTextBox().setTextAndUpdate(std::to_string(defender.getNumOfUnits()));

			//Play damage animation
			m_bloodSplash.setPosition(defender.getPosition());
			m_bloodSplash.move(settings::c_tileSize * 0.5f, 0); //Adjust to be in correct position
			m_bloodSplash.startAnimation();

			//Check if all units died
			if (defender.getNumOfUnits() <= 0) //If no units are left, delete it
			{
				deleteUnit(m_unitIndexToInteractWith);
			}
		}
	}

	if (m_isCombatActive)
	{
		nextTurn();
	}
}

void CombatHandler::defend()
{
	//Increase units defence by 1 for this combat
	m_combatUnits[m_currentUnitTurnIndex]->setUnitSpecificData(UnitBattleDataEnum::defence, m_combatUnits[m_currentUnitTurnIndex]->getUnitSpecificData(UnitBattleDataEnum::defence) + 1);
	m_logsConsole.addText(m_combatUnits[m_currentUnitTurnIndex]->getBaseUnitData()->getStringData(UnitDataEnum::unitName) + " defended\n");
	nextTurn();
}

void CombatHandler::wait()
{
	int currentUnitTurn = m_currentUnitTurnIndex;

	if (!m_combatUnits[currentUnitTurn]->getDidUnitSkipTurn()) //Check if unit already skipped its turn this combat turn
	{
		m_logsConsole.addText(m_combatUnits[m_currentUnitTurnIndex]->getBaseUnitData()->getStringData(UnitDataEnum::unitName) + " waited\n");

		nextTurn();

		m_unitIndexesToDeleteFromTurnQue.push_back(currentUnitTurn); //Add unit index to delete from the que rather than push it to the back of the que

		bool wasUnitSet = false;
		int previousUnitSpeed = 99; //Set this high to make sure that any unit will have less speed than this
		for (int i = 0; i < m_unitTurnOrder.size(); i++) //Determine where to insert this unit in the turn que order based on its speed
		{
			if (previousUnitSpeed < m_combatUnits[m_unitTurnOrder[i]]->getBaseUnitData()->getIntData(UnitDataEnum::speed)) 
			{
				//insert this unit here
				m_unitTurnOrder.insert(m_unitTurnOrder.begin() + i, currentUnitTurn);
				wasUnitSet = true;
				break;
			}
			else
			{
				previousUnitSpeed = m_combatUnits[m_unitTurnOrder[i]]->getBaseUnitData()->getIntData(UnitDataEnum::speed);
			}
		}

		if (!wasUnitSet)
		{
			m_unitTurnOrder.push_back(currentUnitTurn);
		}

		m_combatUnits[currentUnitTurn]->toggleDidUnitSkipTurn();
		m_unitTurnOrderBar.setUnitCards(m_combatUnits, m_unitTurnOrder);
	}
	else
	{
		m_logsConsole.addText(m_combatUnits[m_currentUnitTurnIndex]->getBaseUnitData()->getStringData(UnitDataEnum::unitName) + " can't wait twice in a row\n");
	}
}

void CombatHandler::setAutoCombat()
{
	bool AIStateToChangeTo = !m_combatUnits[m_currentUnitTurnIndex]->getIsUnitAI();
	if (m_combatUnits[m_currentUnitTurnIndex]->getIsAttacker()) //Set attackers as AI
	{
		for (auto& unit : m_combatUnits)
		{
			if (unit->getIsAttacker())
			{
				unit->setIsUnitAI(AIStateToChangeTo);
			}
		}

		m_attackerAI.setAIParameters(AIStateToChangeTo);
		m_isAttackerAI = AIStateToChangeTo;
	}
	else //Set defenders as AI
	{
		for (auto& unit : m_combatUnits)
		{
			if (!unit->getIsAttacker())
			{
				unit->setIsUnitAI(AIStateToChangeTo);
			}
		}

		m_defenderAI.setAIParameters(AIStateToChangeTo);
		m_isDefenderAI = AIStateToChangeTo;
	}

	setUpAI();
}

void CombatHandler::checkForUnitMovement(const sf::Vector2f& mousePosition)
{
	int tileIndex = m_tileHandler.checkTileCollision(mousePosition);
	if (tileIndex > -1) //If there is no tile collision, function above returns -1, this makes sure that there was a collision between tile and mouse
	{
		Tile* pTile = m_tileHandler.getTile(tileIndex);

		//Move only to tiles that aren't obstacles and are not occupied
		if (!pTile->getIsObstacle() && !pTile->getIsOccupied())
		{
			moveUnit(tileIndex);
		}
	}
}

void CombatHandler::moveUnit(const int tileIndex)
{
	Global::objectPressed();

	int endTileIndex = tileIndex;
	int unitStartTile = m_tileHandler.checkTileCollision(m_combatUnits[m_currentUnitTurnIndex]->getPosition());
	bool isMoveValid = false;
	bool isMovementWithinRange = false;

	//If current unit is AI, check if units can interact
	if (m_combatUnits[m_currentUnitTurnIndex]->getIsUnitAI())
	{
		if (m_combatUnits[m_currentUnitTurnIndex]->getIsAttacker())
		{
			m_canCurrentlySelectedUnitsInteract = m_attackerAI.getCanUnitsInteract();
		}
		else
		{
			m_canCurrentlySelectedUnitsInteract = m_defenderAI.getCanUnitsInteract();
		}
	}

	//Check end tile neighbours if unit is large
	if (m_combatUnits[m_currentUnitTurnIndex]->getIsLargeUnit())
	{
		int checkTileIndex = tileIndex;
		if (m_combatUnits[m_currentUnitTurnIndex]->getIsAttacker())
		{
			checkTileIndex -= 1;
		}
		else
		{
			checkTileIndex += 1;
		}

		if (m_tileHandler.getTile(checkTileIndex)->getIsObstacle()) //Check if the other tile that the unit will occupy is an obstacle
		{
			//if true, check if the tile on the other side is occupied
			checkTileIndex = tileIndex;
			if (m_combatUnits[m_currentUnitTurnIndex]->getIsAttacker())
			{
				checkTileIndex += 1;
			}
			else
			{
				checkTileIndex -= 1;
			}

			if (!m_tileHandler.getTile(checkTileIndex)->getIsObstacle()) //If its not an obstacle, set it as destination tile
			{
				endTileIndex = checkTileIndex;
			}

			//Without these checks, units will not be able move when clicked on a tile that has valid movement because of their size as they would move on top of an obstacle, player could manually click on a tile next to it.. 
			// to accomodate size of the unit but these checks do it automatically for them and also allow the unit to move to a position where it could attack without moving to appropriate position first
		}
	}

	m_tileHandler.setTileProperty(unitStartTile, TilePropertiesEnum::start);
	m_tileHandler.setTileProperty(endTileIndex, TilePropertiesEnum::end);


	//When a large unit is moving, ignore tile collision with themselves for a smooth path finding
	if (m_combatUnits[m_currentUnitTurnIndex]->getIsLargeUnit())
	{
		int indexOfTileToIgnore = m_combatUnits[m_currentUnitTurnIndex]->getOccupiedTileIndex();
		if (m_combatUnits[m_currentUnitTurnIndex]->getIsAttacker())
		{
			indexOfTileToIgnore -= 1;
		}
		else
		{
			indexOfTileToIgnore += 1;
		}

		m_tileHandler.getTile(indexOfTileToIgnore)->setIsObstacle(false);
		m_tileHandler.getTile(unitStartTile)->setIsObstacle(false);

		m_tileHandler.fintPathForALargeUnit(m_combatUnits[m_currentUnitTurnIndex]->getIsAttacker());
	}
	else
	{
		m_tileHandler.findPath();
	}

	std::vector<sf::Vector2f>& movementPath = m_tileHandler.getTilePositionVectorForThePathFound();

	//Check if the move is valid

	//Check if tile is within movement range
	if (movementPath.size()) //Only check if a path was found
	{
		for (int& index : m_tileIndexesThatAreWithinUnitsMovementRange)
		{
			if (endTileIndex == index)
			{
				isMovementWithinRange = true;
				break;
			}

			if (m_canCurrentlySelectedUnitsInteract) //If attacking, check if attacking unit will be next to the defending unit
			{
				if (!m_tileHandler.getTile(index)->getIsOccupied() && checkIfObjectsAreNextToEachother(m_tileHandler.getTile(index)->getPosition(), m_tileHandler.getTile(endTileIndex)->getPosition())) //Checks if the atacker will be next to defender after the move
				{
					isMovementWithinRange = true;
					break;
				}
			}
		}
	}

	if (unitStartTile != endTileIndex && movementPath.size() && isMovementWithinRange) //Makes sure that unit doesn't move to the same tile its on, that the unit will move at least 1 tile and the tile is withing its movement range
	{
		int destinationTileIndex = 0;

		if (m_canCurrentlySelectedUnitsInteract)
		{
			destinationTileIndex = m_tileHandler.checkTileCollision(movementPath[1]); //Gets end tile - 1, because unit won't stop on another unit when interacting with it
		}
		else
		{
			destinationTileIndex = m_tileHandler.checkTileCollision(movementPath[0]); //Gets end tile
		}

		Tile* destinationTile = m_tileHandler.getTile(destinationTileIndex);

		if (m_combatUnits[m_currentUnitTurnIndex]->getIsLargeUnit()) //Special case for large units
		{
			Tile* largeUnitTile = nullptr;
			int largeTileIndex = 0;

			if (m_combatUnits[m_currentUnitTurnIndex]->getIsAttacker())
			{
				largeTileIndex = destinationTileIndex - 1;
			}
			else
			{
				largeTileIndex = destinationTileIndex + 1;
			}

			largeUnitTile = m_tileHandler.getTile(largeTileIndex);

			if (largeUnitTile->getMapObjectVectorIndex() == m_currentUnitTurnIndex) //Allows large units to move on top of themselves
			{
				if (!destinationTile->getIsObstacle())
				{
					isMoveValid = true;
				}
			}

			if (!destinationTile->getIsObstacle() && !largeUnitTile->getIsObstacle()) //Makes sure that unit has enough free tiles to accomodate its size
			{
				isMoveValid = true;
			}
			else
			{
				isMoveValid = false;
			}

			//Check if other tile of the large unit is on another row of tiles make the move invalid, doesn't allow large units to stand at the edge of combat area 
			if (destinationTileIndex / m_tileHandler.getNumOfHorizontalTiles() != largeTileIndex / m_tileHandler.getNumOfHorizontalTiles())
			{
				isMoveValid = false;
			}
		}
		else
		{
			if (!destinationTile->getIsObstacle() && !destinationTile->getIsOccupied()) //Checks if destination tile is free to move on to
			{
				isMoveValid = true;
			}
		}
	}

	//Set path
	if (isMoveValid && m_tileHandler.getTile(endTileIndex)->getParentTile() != nullptr) //Makes sure a valid path was found
	{
		m_didUnitMakeAMove = true;
		m_didUnitMove = true;
		m_drawCurrentTurnUnitIndicator = false;

		//Don't call when 1 tile away from desired tile
		if (m_canCurrentlySelectedUnitsInteract)
		{
			movementPath.erase(movementPath.begin(), movementPath.begin() + 1); //Deletes tile that the player clicked on from the movment path so currently selected unit will stand next to the unit its interacting with
		}

		if (m_isPlayerWatching)
		{
			m_combatUnits[m_currentUnitTurnIndex]->setMovementPath(movementPath);
		}
		else
		{
			m_combatUnits[m_currentUnitTurnIndex]->setPosition(movementPath[0]);
			attack();
		}
	}
	else if (m_combatUnits[m_currentUnitTurnIndex]->getIsUnitAI())
	{
		if (m_combatUnits[m_currentUnitTurnIndex]->getIsAttacker())
		{
			m_attackerAI.defend();
		}
		else
		{
			m_defenderAI.defend();
		}
	}
}

void CombatHandler::updateTilePropertiesAfterUnitMoved()
{
	int previousTileIndex = m_combatUnits[m_currentUnitTurnIndex]->getOccupiedTileIndex();
	int newTileIndex = m_tileHandler.checkTileCollision(m_combatUnits[m_currentUnitTurnIndex]->getPosition());

	Tile* previouslyOccupiedTile = m_tileHandler.getTile(previousTileIndex);
	Tile* newOccupiedTile = m_tileHandler.getTile(newTileIndex);
	Tile* previouslyOccupiedLargeTile = nullptr;
	Tile* newOccupiedLargeTile = nullptr;

	previouslyOccupiedTile->resetTileProperties();

	if (m_combatUnits[m_currentUnitTurnIndex]->getIsLargeUnit()) //Check if the unit is large
	{
		if (m_combatUnits[m_currentUnitTurnIndex]->getIsAttacker())
		{
			previouslyOccupiedLargeTile = m_tileHandler.getTile(previousTileIndex - 1);
			newOccupiedLargeTile = m_tileHandler.getTile(newTileIndex - 1);
		}
		else
		{
			previouslyOccupiedLargeTile = m_tileHandler.getTile(previousTileIndex + 1);
			newOccupiedLargeTile = m_tileHandler.getTile(newTileIndex + 1);
		}

		previouslyOccupiedLargeTile->resetTileProperties();

		newOccupiedLargeTile->setIsObstacle(true);
		newOccupiedLargeTile->setIsOccupied(true);
		newOccupiedLargeTile->setMapObjectVectorIndex(m_currentUnitTurnIndex);
	}

	newOccupiedTile->setIsObstacle(true);
	newOccupiedTile->setIsOccupied(true);
	newOccupiedTile->setMapObjectVectorIndex(m_currentUnitTurnIndex);
	m_combatUnits[m_currentUnitTurnIndex]->setOccupiedTileIndex(newTileIndex);

	showTileProperties();
}

void CombatHandler::deleteUnit(const int& unitIndexToDelete)
{
	int iteratorIndex = 0;
	int occupiedTileIndex = 0;
	for (int unitIndex : m_unitTurnOrder)
	{
		if (unitIndex == unitIndexToDelete)
		{
			m_unitTurnOrder.erase(m_unitTurnOrder.begin() + iteratorIndex);
			break;
		}
		iteratorIndex++;
	}

	//Reset occupied tile properties
	occupiedTileIndex = m_combatUnits[unitIndexToDelete]->getOccupiedTileIndex();
	Tile* occupiedTile = m_tileHandler.getTile(occupiedTileIndex);
	occupiedTile->resetTileProperties();

	if (m_combatUnits[unitIndexToDelete]->getIsLargeUnit())
	{
		if (m_combatUnits[unitIndexToDelete]->getIsAttacker())
		{
			occupiedTileIndex--;
		}
		else
		{
			occupiedTileIndex++;
		}
		occupiedTile = m_tileHandler.getTile(occupiedTileIndex);
		occupiedTile->resetTileProperties();
	}

	bool didAllUnitsDie = true;
	if (m_combatUnits[unitIndexToDelete]->getIsAttacker())
	{
		for (int& index : m_unitTurnOrder)
		{
			if (m_combatUnits[index]->getIsAttacker())
			{
				didAllUnitsDie = false;
				break;
			}
		}

		if (didAllUnitsDie)
		{
			m_isCombatActive = false;
			m_didAttackerWin = false;
			m_combatEndPopUp.setTitleText(false);
			if (!m_isPlayerWatching)
			{
				endCombat();
			}
		}
	}
	else
	{
		for (int& index : m_unitTurnOrder)
		{
			if (!m_combatUnits[index]->getIsAttacker())
			{
				didAllUnitsDie = false;
				break;
			}
		}

		if (didAllUnitsDie)
		{
			m_isCombatActive = false;
			m_didAttackerWin = true;
			m_combatEndPopUp.setTitleText(true);
			if (!m_isPlayerWatching)
			{
				endCombat();
			}
		}
	}

	m_unitTurnOrderBar.setUnitCards(m_combatUnits, m_unitTurnOrder);
	updateDrawingOrder();
	showTileProperties();
}

void CombatHandler::nextTurn()
{
	int thisTurnUnitIndex = m_unitTurnOrder[0];
	bool addCurrentUnitToTheBackOfTheQue = true;

	//Reset visuals
	m_combatUnits[thisTurnUnitIndex]->setColor(sf::Color::White);
	m_selectedUnitAlpha = 255;

	if (m_unitIndexesToDeleteFromTurnQue.size()) //Delete units from que that have waited
	{
		for (int i = 0; i < m_unitIndexesToDeleteFromTurnQue.size(); i++)
		{
			if (m_unitIndexesToDeleteFromTurnQue[i] == thisTurnUnitIndex)
			{
				m_unitIndexesToDeleteFromTurnQue.erase(m_unitIndexesToDeleteFromTurnQue.begin() + i);
				m_combatUnits[thisTurnUnitIndex]->toggleDidUnitSkipTurn();
				addCurrentUnitToTheBackOfTheQue = false;
				break;
			}
		}
	}

	m_unitTurnOrder.erase(m_unitTurnOrder.begin(), m_unitTurnOrder.begin() + 1); //Delete 1st unit index from the que
	m_currentUnitTurnIndex = m_unitTurnOrder[0];

	if (addCurrentUnitToTheBackOfTheQue)
	{
		m_unitTurnOrder.push_back(thisTurnUnitIndex); //Add deleted unit index to the back of the que
	}

	m_unitTurnOrderBar.setUnitCards(m_combatUnits, m_unitTurnOrder); //Update unit cards

	setCurrentUnitTurnIndicator();

	m_drawCurrentTurnUnitIndicator = true;
	m_didUnitMakeAMove = false;

	setTilesThatAreWithinUnitMovementRange();

	m_combatCursor.updateCursor(m_combatCursor.getPreviousCursorPosition(), m_tileHandler.checkTileCollision(m_combatCursor.getPreviousCursorPosition()), m_currentUnitTurnIndex);
}

void CombatHandler::updateDrawingOrder()
{
	if (m_isPlayerWatching)
	{
		m_unitDrawOrder.clear();

		int tileIndex = 0;
		Tile* tile = nullptr;

		//Loops through all tiles, checks if they're occupied and adds the to the drawing order
		for (int rowIndex = 0; rowIndex < settings::c_numOfVerticalTiles; rowIndex++)
		{
			for (int collumnIndex = 0; collumnIndex < settings::c_numOfHorizontalTiles; collumnIndex++)
			{
				tileIndex = rowIndex * settings::c_numOfHorizontalTiles + collumnIndex;

				tile = m_tileHandler.getTile(tileIndex);

				if (tile->getIsOccupied())
				{
					m_unitDrawOrder.push_back(tile->getMapObjectVectorIndex());
				}
			}
		}
	}
}

void CombatHandler::endCombat()
{
	Global::g_UILayer = UILayerEnum::map;

	updateCombatantsArmiesAfterCombat();

	m_functionToCallAfterCombatConcluded(m_combatType, m_didAttackerWin);
}

void CombatHandler::awardExperienceToTheWinner()
{
	int experienceToAward = 0;
	if (m_didAttackerWin || m_combatType == CombatTypeEnum::playerVsPlayer)
	{
		for (auto& unit : m_combatUnits)
		{
			if (unit->getIsAttacker() != m_didAttackerWin) //Checks if unit is the opposite side of the winner
			{
				experienceToAward += unit->getBaseUnitData()->getIntData(UnitDataEnum::AIValue) * unit->getNumOfUnits();
			}
		}

		if (m_didAttackerWin)
		{
			m_pAttackerHero->addHeroExperience(experienceToAward);
		}
		else
		{
			m_pDefenderHero->addHeroExperience(experienceToAward);
		}
	}


}

void CombatHandler::updateCombatantsArmiesAfterCombat()
{
	int numOfAttackerUnits = 0;
	int numOfUnitsUpdated = 0;
	auto& attakHeroUnits = m_pAttackerHero->getVectorOfUnits();

	//Update Attacker units (there is always an attacker)
	for (int i = 0; i < c_numOfUnitsPerFaction; i++)
	{
		if (attakHeroUnits[i]->getIsDataSet())
		{
			if (m_combatUnits[numOfUnitsUpdated]->getNumOfUnits() <= 0)
			{
				m_pAttackerHero->deleteUnit(i);
			}
			else
			{
				attakHeroUnits[i]->setNumOfUnits(m_combatUnits[numOfUnitsUpdated]->getNumOfUnits());
			}
			numOfUnitsUpdated++;
		}

		if (numOfUnitsUpdated == numOfAttackerUnits)
		{
			break;
		}
	}


	//Update Defender
	switch (m_combatType)
	{
	case CombatTypeEnum::playerVsMapUnit:
		{
			//Update Defender Units
			int numberOfRemainingMapUnits = 0;

			for (int i = numOfUnitsUpdated; i < m_combatUnits.size(); i++)
			{
				if (m_combatUnits[i]->getNumOfUnits() > 0)
				{
					numberOfRemainingMapUnits += m_combatUnits[i]->getNumOfUnits();
				}
			}

			m_pDefenderMapUnit->setNumberOfUnits(numberOfRemainingMapUnits);
		}
		break;

	case CombatTypeEnum::playerVsPlayer:
		{
			//Update Defender units
			auto& defendHeroUnits = m_pDefenderHero->getVectorOfUnits();
			for (int i = 0; i < c_numOfUnitsPerFaction; i++)
			{
				if (defendHeroUnits[i]->getIsDataSet())
				{
					if (m_combatUnits[numOfUnitsUpdated]->getNumOfUnits() <= 0)
					{
						m_pDefenderHero->deleteUnit(i);
					}
					else
					{
						defendHeroUnits[i]->setNumOfUnits(m_combatUnits[numOfUnitsUpdated]->getNumOfUnits());
					}
					numOfUnitsUpdated++;
				}

				if (numOfUnitsUpdated == m_combatUnits.size())
				{
					break;
				}
			}
		}
		break;

	case CombatTypeEnum::playerVsTown:
		{
			for (int i = 0; i < c_numOfUnitsPerFaction; i++)
			{
				if (m_pTownUnitsVectorPointer->at(i)->getIsDataSet())
				{
					if (m_combatUnits[numOfUnitsUpdated]->getNumOfUnits() <= 0)
					{
						m_pTownUnitsVectorPointer->at(i)->resetUnitData(); //Equivalent to deleting the unit
					}
					else
					{
						m_pTownUnitsVectorPointer->at(i)->setNumOfUnits(m_combatUnits[numOfUnitsUpdated]->getNumOfUnits());
					}
					numOfUnitsUpdated++;
				}

				if (numOfUnitsUpdated == m_combatUnits.size())
				{
					break;
				}
			}
		}
		break;

	default:
		break;
	}
}

void CombatHandler::setFunctionToCallWhenCombatIsWon(std::function<void(const CombatTypeEnum, const bool)> function)
{
	m_functionToCallAfterCombatConcluded = function;
}

const bool CombatHandler::getDidAttackerWin() const
{
	return m_didAttackerWin;
}

Hero* CombatHandler::getAttackerHero()
{
	return m_pAttackerHero;
}

Hero* CombatHandler::getDefenderHero()
{
	return m_pDefenderHero;
}

UnitMapObject* CombatHandler::getUnitMapObject()
{
	return m_pDefenderMapUnit;
}

std::vector<std::shared_ptr<Unit>>* CombatHandler::getTownUnitsVectorPointer()
{
	return m_pTownUnitsVectorPointer;
}

const bool CombatHandler::getIsCombatActive() const
{
	return m_isCombatActive;
}

void CombatHandler::showTileProperties()
{
	if (m_isPlayerWatching)
	{
		for (int i = 0; i < m_tileHandler.getNumOfHorizontalTiles() * m_tileHandler.getNumOfVerticalTiles(); i++)
		{
			if (m_tileHandler.getTile(i)->getIsObstacle() || m_tileHandler.getTile(i)->getIsOccupied())
			{
				m_tileHandler.getTile(i)->setColor(sf::Color::Red);
			}
			else
			{
				m_tileHandler.getTile(i)->setColor(sf::Color::White);
			}
		}
	}
}

void CombatHandler::setTilesThatAreWithinUnitMovementRange()
{
	m_tileIndexesThatAreWithinUnitsMovementRange.clear();

	const int speed = m_combatUnits[m_currentUnitTurnIndex]->getUnitSpecificData(UnitBattleDataEnum::speed);
	const sf::Vector2f& unitPosition = m_combatUnits[m_currentUnitTurnIndex]->getPosition();

	int x = 0;
	int y = 0;
	//int pythagoras = 0;
	Tile* tile = nullptr;

	for (int i = 0; i < m_tileHandler.getNumOfHorizontalTiles() * m_tileHandler.getNumOfVerticalTiles(); i++)
	{
		tile = m_tileHandler.getTile(i);
		x = abs(tile->getPosition().x - unitPosition.x);
		y = abs(tile->getPosition().y - unitPosition.y);

		//More expensive and less accurate way to determine tiles in range
		//pythagoras = sqrt((x * x) + (y * y));
		//
		//if (floor(pythagoras / settings::c_tileSize) <= speed)
		//{
		//	m_tileIndexesThatAreWithinUnitsMovementRange.push_back(i);
		//}

		if ((x / settings::c_tileSize + y / settings::c_tileSize) <= speed)
		{
			m_tileIndexesThatAreWithinUnitsMovementRange.push_back(i);
		}
	}
}

void CombatHandler::updateCurrentUnitTurnFeedback()
{
	if (m_isPlayerWatching)
	{
		static float alphaChangeRate = settings::c_alphaChangeRate;

		m_selectedUnitAlpha += alphaChangeRate;

		if (m_selectedUnitAlpha > settings::c_selectedUnitMaxAlpha || m_selectedUnitAlpha < settings::c_selectedUnitMinAlpha)
		{
			if (m_selectedUnitAlpha > settings::c_selectedUnitMaxAlpha)
			{
				m_selectedUnitAlpha = settings::c_selectedUnitMaxAlpha;
			}

			alphaChangeRate *= -1;
		}
		m_combatUnits[m_currentUnitTurnIndex]->setColor(sf::Color::Color(255, 255, 255, m_selectedUnitAlpha));
		m_currentTurnUnitIndicator.setColor(sf::Color::Color(255, 255, 255, m_selectedUnitAlpha));
	}
}

void CombatHandler::setCurrentUnitTurnIndicator()
{
	if (m_isPlayerWatching)
	{
		int xOffset = 0;
		int yOffset = 0;
		m_currentTurnUnitIndicator.setPosition(m_tileHandler.getTile(m_combatUnits[m_currentUnitTurnIndex]->getOccupiedTileIndex())->getPosition());

		yOffset = m_combatUnits[m_currentUnitTurnIndex]->getGlobalBounds().height - settings::c_tileSize + m_currentTurnUnitIndicator.getGlobalBounds().height;

		if (m_combatUnits[m_currentUnitTurnIndex]->getIsLargeUnit())
		{
			xOffset = settings::c_tileSize * 0.5f;

			if (m_combatUnits[m_currentUnitTurnIndex]->getIsAttacker())
			{
				xOffset *= -1;
			}
		}
		m_currentTurnUnitIndicator.move(xOffset, -yOffset);
	}
}

void CombatHandler::checkIfPlayerActivatedUnitCard(const sf::Vector2f& mousePosition)
{
	if (m_isPlayerWatching)
	{
		if (!m_unitInformationCard.getIsActive())
		{
			int tileIndex = m_tileHandler.checkTileCollision(mousePosition);

			if (tileIndex >= 0)
			{
				Tile* tile = m_tileHandler.getTile(tileIndex);

				if (tile->getIsOccupied()) //Has a unit on it
				{
					m_unitInformationCard.toggleIsActive();
					m_unitInformationCard.setUnitData(*m_combatUnits[tile->getMapObjectVectorIndex()]);
				}
			}
		}
		else
		{
			m_unitInformationCard.toggleIsActive();
		}
	}
}

void CombatHandler::draw()
{
	if (m_isPlayerWatching)
	{
		drawGame();
		drawUI();
	}
}

void CombatHandler::drawGame()
{
	m_background.drawUIBorderAndBackground();
	m_window.draw(m_combatBackground);
	m_combatBackgroundBorder.drawUIBorder();

	m_tileHandler.draw();

	drawUnitMovementRange();

	for (int unitIndex : m_unitDrawOrder)
	{
		m_window.draw(*m_combatUnits[unitIndex]);
		m_combatUnits[unitIndex]->getNumberOfUnitsTextBox().draw();
	}
	m_bloodSplash.drawAnimation();

	m_unitTurnOrderBar.draw();
}

void CombatHandler::drawUnitMovementRange()
{
	m_tileFill.setColor(sf::Color::White);
	for (int i = 0; i < m_tileHandler.getNumOfHorizontalTiles() * m_tileHandler.getNumOfVerticalTiles(); i++)
	{
		m_tileFill.setPosition(m_tileHandler.getTile(i)->getPosition());
		m_window.draw(m_tileFill);
	}

	m_tileFill.setColor(sf::Color::Black);
	for (int& index : m_tileIndexesThatAreWithinUnitsMovementRange)
	{
		m_tileFill.setPosition(m_tileHandler.getTile(index)->getPosition());
		m_window.draw(m_tileFill);
	}
}

void CombatHandler::drawUI()
{
	if (m_drawCurrentTurnUnitIndicator)
	{
		m_window.draw(m_currentTurnUnitIndicator);
	}

	for (auto& button : m_buttons)
	{
		button->draw();
	}

	m_unitInformationCard.draw();

	m_logsConsole.draw();

	if (!m_isCombatActive)
	{
		m_combatEndPopUp.draw();
	}

	m_window.draw(m_combatCursor);
}