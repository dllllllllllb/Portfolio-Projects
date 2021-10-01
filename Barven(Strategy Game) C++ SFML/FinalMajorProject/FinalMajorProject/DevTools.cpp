#include "DevTools.h"

namespace settings = DevToolsSettings;

DevTools::DevTools(sf::RenderWindow& rWindow, Textures* pTextures, Fonts* pFonts, DataHandler* pDataHandler, sf::Mouse& mouse) :
	m_window(rWindow),
	m_DevToolsEnum(DevToolsEnum::devTools),
	m_dataHandler(*pDataHandler),
	m_confirmationWindow(rWindow, pTextures, pFonts),
	m_UITool(rWindow, pTextures, pFonts),
	m_pathFindingTool(rWindow, pTextures, pFonts),
	m_unitCreationTool(rWindow, pTextures, pFonts),
	m_mapCreator(rWindow, pTextures, pFonts, pDataHandler, mouse),
	m_commbatHandler(rWindow, *pTextures, *pDataHandler, *pFonts),
	m_testTextBox(rWindow, pTextures, pFonts),
	m_player(rWindow),
	m_resourcesBar(rWindow, pTextures, pFonts),
	m_townTool(rWindow, pTextures, pFonts, m_confirmationWindow, m_resourcesBar)
{
	for (int i = 0; i < settings::c_numOfButtons; i++)
	{
		m_buttons.push_back(std::unique_ptr<Button>(new Button(rWindow, pTextures, pFonts)));
	}
	m_player.setDataHandlerPointer(pDataHandler);
	m_player.setFunctionToCallWhenHeroArrivesAtDestination(std::bind(&DevTools::drawDevTools, this));
}

DevTools::~DevTools()
{
}

void DevTools::initialize()
{
	setUpButtons();
	m_player.makeNewHero(sf::Vector2f(0,0), 0, false);
	m_UITool.initialize();
	m_pathFindingTool.initialize();
	m_unitCreationTool.initialize();
	m_townTool.initialize();
	m_mapCreator.initialize();

	for (int i = 0; i < c_numOfUnitsPerFaction; i++)
	{
		m_townData.setUnitData(i, m_dataHandler.getFactionData(0).getUnitData(i));
		if (m_townData.getTownBuildingData().getData(static_cast<TownBuildingEnum>(5 + i))) //5 == first unit data position in enum , checks if town has building coresponding to the unit
		{
			m_townData.getAvailableUnitsToRecruit()[i] = m_dataHandler.getFactionData(0).getUnitData(i).getIntData(UnitDataEnum::growthPerWeek);
		}
	}

	m_townTool.setTownData(0, m_townData, m_dataHandler.getFactionData(0).getBuildingsData(), m_player, true);
	m_resourcesBar.setUp();
	m_resourcesBar.updateResourcesBarValues(m_player.getResources());

	m_commbatHandler.setUpCombatAreaAndUI();

	//////////////////////////////////////////////////////////////////////////////////////////
	// 	   TESTING COMBAT TOOL
	//////////////////////////////////////////////////////////////////////////////////////////

	//Set up player army for testing
	//
	//for (int i = 0; i < 7; i++) //Set the same unit
	//{
	//	m_player.getSelectedHero().addUnit(i, &m_dataHandler.getFactionData(0).getUnitData(0));
	//	m_player.getSelectedHero().getUnit(i).incrementNumOfUnits(14);
	//	m_player.getSelectedHero().getUnit(i).updateUnitSpecificData();
	//}

	//Set multiple units
	m_player.getSelectedHero().addUnit(0, &m_dataHandler.getFactionData(1).getUnitData(0));
	m_player.getSelectedHero().getUnit(0).incrementNumOfUnits(20);
	
	m_player.getSelectedHero().addUnit(1, &m_dataHandler.getFactionData(1).getUnitData(1));
	m_player.getSelectedHero().getUnit(1).incrementNumOfUnits(30);
	
	m_player.getSelectedHero().addUnit(2, &m_dataHandler.getFactionData(1).getUnitData(2));
	m_player.getSelectedHero().getUnit(2).incrementNumOfUnits(5);
	
	m_player.getSelectedHero().addUnit(3, &m_dataHandler.getFactionData(1).getUnitData(6));
	m_player.getSelectedHero().getUnit(3).incrementNumOfUnits(2);
	
	m_player.getSelectedHero().addUnit(4, &m_dataHandler.getFactionData(1).getUnitData(5));
	m_player.getSelectedHero().getUnit(4).incrementNumOfUnits(4);
	
	m_player.getSelectedHero().addUnit(5, &m_dataHandler.getFactionData(1).getUnitData(3));
	m_player.getSelectedHero().getUnit(5).incrementNumOfUnits(9);
	
	m_player.getSelectedHero().addUnit(6, &m_dataHandler.getFactionData(1).getUnitData(4));
	m_player.getSelectedHero().getUnit(6).incrementNumOfUnits(11);

	m_unitMapObject.setFactionIndex(0);
	m_unitMapObject.setUnitIndex(2);
	m_unitMapObject.setNumberOfUnits(80);

	m_player.getSelectedHero().updateUnitsStats();

	m_commbatHandler.setUpPlayerVsMapUnit(&m_player.getSelectedHero(), &m_unitMapObject, false);
	m_commbatHandler.setFunctionToCallWhenCombatIsWon(std::bind(&DevTools::drawDevTools, this));
}

void DevTools::setUpButtons()
{
	for (int i = 0; i < settings::c_numOfButtons; i++)
	{
		m_buttons[i]->setPosition(settings::c_positionX[i], settings::c_positionY[i]);
		m_buttons[i]->setUpUIBorder(settings::c_buttonWidth, settings::c_buttonHeight);
		m_buttons[i]->setCollisionBounds(settings::c_buttonWidth, settings::c_buttonHeight);
		m_buttons[i]->setUpText(settings::c_buttonName[i], settings::c_buttonCharSize, TextAlignmentEnum::middleHorizontal, TextAlignmentEnum::middleVertical);
	}

	//TextBox test
	//Controll text box to see if changes to any element of the textbox will have impact on existing text boxes
	std::string tempString = "This is a test to see if the text is nicely divided into lines and centered properly inside a text box. I totally have something interesting to write here so there is no reason why I would write a bunch of nonsense. I really hope this works and looks nice as I can't be arsed to spend any more time on polishing out the text class.";

	m_testTextBox.setPosition(1500, 250);
	m_testTextBox.setUpUIBorder(400, 0);
	m_testTextBox.setUpText(tempString, 14, TextAlignmentEnum::middleHorizontal, TextAlignmentEnum::top);
	m_testTextBox.setUpTitleText("Test Title", 24);
	m_testTextBox.setTitleOffset(m_testTextBox.getTitleHeight());
	m_testTextBox.resizeBorderToFitText();
}

void DevTools::update(const sf::Vector2f& mousePosition, const float& deltaTime)
{
	if (m_DevToolsEnum != DevToolsEnum::devTools)
	{
		//Each tool uses the same back button that lives inside this class
		if (m_buttons[0]->checkMouseCollision(mousePosition) && Global::g_isLMBPressed)
		{
			m_DevToolsEnum = DevToolsEnum::devTools;
			m_townTool.setIsTownActive(false);
			Global::objectPressed();
		}
	}

	switch (m_DevToolsEnum)
	{
	case DevToolsEnum::devTools:
	{
		updateDevTools(mousePosition);
		drawDevTools();
	}
	break;

	case DevToolsEnum::UITool:
	{
		m_UITool.update(mousePosition);
		m_UITool.draw();
	}
	break;

	case DevToolsEnum::pathFindingTool:
	{
		m_pathFindingTool.update(mousePosition);
		m_pathFindingTool.draw();
	}
	break;

	case DevToolsEnum::unitCreationTool:
	{
		m_unitCreationTool.update(mousePosition);
		m_unitCreationTool.draw();
	}
	break;

	case DevToolsEnum::townTool:
	{
		m_townTool.update(mousePosition, deltaTime);
		m_resourcesBar.draw();
	}
	break;

	case DevToolsEnum::mapCreator:
	{
		m_mapCreator.update(mousePosition);
	}
	break;

	case DevToolsEnum::combatTool:
	{
		m_commbatHandler.update(mousePosition, deltaTime);
		m_commbatHandler.draw();
	}
	break;
	}

	m_buttons[0]->draw(); //Back button, used in every tool hence always drawn
}

void DevTools::updateDevTools(const sf::Vector2f& mousePosition)
{
	for (int i = 0; i < settings::c_numOfButtons; i++)
	{
		if (m_buttons[i]->checkMouseCollision(mousePosition) && Global::g_isLMBPressed)
		{
			if (i == 0) //Back button
			{
				Global::g_gameState = GameState::menu; //Returns player to the main menu
				m_townTool.setIsTownActive(false);
				Global::objectPressed();
			}
			else
			{
				m_DevToolsEnum = static_cast<DevToolsEnum>(i);
				if (m_DevToolsEnum == DevToolsEnum::townTool)
				{
					m_townTool.setIsTownActive(true);
					Global::g_UILayer = UILayerEnum::town;
				}
				Global::objectPressed();
			}
			break;
		}
	}
}

void DevTools::drawDevTools()
{
	for (int i = 1; i < settings::c_numOfButtons; i++)
	{
		m_buttons[i]->draw();
	}
	m_testTextBox.draw();
}