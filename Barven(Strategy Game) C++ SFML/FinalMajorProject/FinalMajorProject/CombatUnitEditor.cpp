#include "CombatUnitEditor.h"

namespace settings = CombatUnitEditorSettings;

CombatUnitEditor::CombatUnitEditor(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts, Audio& rAudio, DataHandler& rDataHandler) :
	m_window(rWindow),
	m_textures(rTextures),
	m_dataHandler(rDataHandler),
	m_pAttackerHero(nullptr),
	m_pDefenderHero(nullptr),
	m_attackerUnits(rWindow, rTextures, rFonts, rAudio),
	m_defenderUnits(rWindow, rTextures, rFonts, rAudio),
	m_background(rWindow, rTextures),
	m_unitList(rWindow, rTextures, rAudio),
	m_unitListOutline(rWindow, rTextures, true),
	m_setNumberOfUnitsInputBox(rWindow, rTextures, rFonts, rAudio, true),
	m_applySettingsButton(rWindow, rTextures, rFonts, rAudio, true),
	m_isEditorActive(false),
	m_isAttackerSelected(false),
	m_selectedUnitPositionIndex(0)
{
	for (int i = 0; i < settings::c_numOfButtons; i++)
	{
		m_buttons.push_back(std::unique_ptr<Button>(new Button(rWindow, rTextures, rFonts, rAudio, true)));
	}
}

CombatUnitEditor::~CombatUnitEditor()
{
}

void CombatUnitEditor::initialize()
{
	int editorWidth = settings::c_buttonWidth + settings::c_unitIconWidth + 60;
	int editorHeight = settings::c_numOfUnitsToDisplay * (settings::c_unitIconHeight + 4) + settings::c_unitIconHeight;


	//Unit panels
	m_attackerUnits.setUpPanel(settings::c_borderGap + settings::c_unitPanelWidth * 0.5f, settings::c_borderGap + settings::c_unitIconHeight * 0.7f, true, false);
	m_defenderUnits.setUpPanel(m_window.getSize().x - settings::c_borderGap - settings::c_unitPanelWidth * 0.5f, settings::c_borderGap + settings::c_unitIconHeight * 0.7f, false, false);

	//Editor background
	m_background.setPosition(m_window.getView().getCenter().x, editorHeight * 0.5f + settings::c_unitIconHeight + settings::c_borderGap * 2);
	m_background.setUpUIBorder(editorWidth, editorHeight);

	//Unit list
	m_unitList.setUpIconButtonList(m_background.getPosition().x - editorWidth * 0.5f + settings::c_borderGap + settings::c_unitIconWidth * 0.5f,
								   m_background.getPosition().y - ((settings::c_unitIconHeight + settings::c_buttonBorder) * settings::c_numOfUnitsToDisplay) * 0.5f,
								   settings::c_unitIconWidth, settings::c_unitIconWidth, settings::c_numOfUnitsToDisplay);
	
	//Unit list outline
	m_unitListOutline.setPosition(m_unitList.getIconButton(0).getIconSprite().getPosition());
	m_unitListOutline.setUpUIBorder(settings::c_unitIconWidth + 4, settings::c_unitIconHeight + 4);
	m_unitListOutline.setBorderColor(sf::Color::Yellow);

	//Unit num input box
	int buttonsPositionX = m_background.getPosition().x + editorWidth * 0.5f - settings::c_borderGap - settings::c_buttonWidth * 0.5f;
	int buttonSpaceing = editorHeight / (settings::c_numOfButtons + 2);
	int firstButtonPositionY = m_background.getPosition().y - editorHeight * 0.5f + buttonSpaceing;

	m_setNumberOfUnitsInputBox.setPosition(buttonsPositionX, firstButtonPositionY);
	m_setNumberOfUnitsInputBox.setUpUIBorder(settings::c_buttonWidth, settings::c_buttonHeight);
	m_setNumberOfUnitsInputBox.setCollisionBounds(settings::c_buttonWidth, settings::c_buttonHeight);
	m_setNumberOfUnitsInputBox.setUpText("0", settings::c_textCharSize, TextAlignmentEnum::middleHorizontal, TextAlignmentEnum::middleVertical);
	m_setNumberOfUnitsInputBox.setUpTitleText(settings::c_inputButtonTitleText, settings::c_textCharSize);
	m_setNumberOfUnitsInputBox.updateInputTextPosition();

	//Buttons
	for (int i = 0; i < settings::c_numOfButtons; i++)
	{
		m_buttons[i]->setPosition(buttonsPositionX, firstButtonPositionY + (i + 1) * buttonSpaceing);
		m_buttons[i]->setUpUIBorder(settings::c_buttonWidth, settings::c_buttonHeight);
		m_buttons[i]->setCollisionBounds(settings::c_buttonWidth, settings::c_buttonHeight);
		m_buttons[i]->setUpText(settings::c_buttonText[i], settings::c_textCharSize, TextAlignmentEnum::middleHorizontal, TextAlignmentEnum::middleVertical);
	}

	m_applySettingsButton.setPosition(m_window.getView().getCenter().x, m_attackerUnits.getBackground().getPosition().y);
	m_applySettingsButton.setUpUIBorder(settings::c_buttonWidth, settings::c_buttonHeight);
	m_applySettingsButton.setCollisionBounds(settings::c_buttonWidth, settings::c_buttonHeight);
	m_applySettingsButton.setUpText(settings::c_applySettingsButtonText, settings::c_titleCharSize, TextAlignmentEnum::middleHorizontal, TextAlignmentEnum::middleVertical);

	for (int i = 0; i < c_numOfFactions; i++)
	{
		for (int k = 0; k < c_numOfUnitsPerFaction; k++)
		{
			m_unitList.addNewButtonIcon(m_dataHandler.getFactionData(i).getUnitData(k).getUnitIcon());
		}
	}
}

void CombatUnitEditor::setHeroPointers(Hero* attackingHero, Hero* defenderHero)
{
	m_pAttackerHero = attackingHero;
	m_pDefenderHero = defenderHero;

	m_attackerUnits.setUnitCards(m_pAttackerHero->getVectorOfUnits());
	m_defenderUnits.setUnitCards(m_pDefenderHero->getVectorOfUnits());
}

void CombatUnitEditor::setEditorWindowVariables()
{
	int numOfUnits = 0;
	Unit* selectedUnit = getSelectedUnit();

	if (selectedUnit->getIsDataSet())
	{
		numOfUnits = selectedUnit->getNumOfUnits();
	}

	m_unitList.setIndexOfPressedButton(selectedUnit->getBaseUnitData()->getIntData(UnitDataEnum::faction)* c_numOfUnitsPerFaction + selectedUnit->getBaseUnitData()->getIntData(UnitDataEnum::index));
	m_setNumberOfUnitsInputBox.setPlayerInput(std::to_string(numOfUnits));
}

void CombatUnitEditor::applyUnitChanges()
{
	int factionIndex = m_unitList.getIndexOfButtonClicked() / c_numOfUnitsPerFaction;
	int unitIndex = m_unitList.getIndexOfButtonClicked() % c_numOfUnitsPerFaction;
	int numberOfUnits = std::stoi(m_setNumberOfUnitsInputBox.getPlayerInput());
	Unit* selectedUnit = getSelectedUnit();

	selectedUnit->resetUnitData();
	selectedUnit->setBaseUnitData(&m_dataHandler.getFactionData(factionIndex).getUnitData(unitIndex));
	selectedUnit->setIsUnitDataSet(true);
	selectedUnit->initializeUnitSpecificData();
	selectedUnit->setNumOfUnits(numberOfUnits);

	updateUnitCards();
	resetSelectedUnitCards();
}

void CombatUnitEditor::deleteUnit()
{
	getSelectedUnit()->resetUnitData();

	updateUnitCards();
	resetSelectedUnitCards();
}

void CombatUnitEditor::updateUnitCards()
{
	if (m_isAttackerSelected)
	{
		m_attackerUnits.updateUnitCardsContent();
	}
	else
	{
		m_defenderUnits.updateUnitCardsContent();
	}
}

void CombatUnitEditor::resetSelectedUnitCards()
{
	m_attackerUnits.setIsUnitCardSelected(false);
	m_defenderUnits.setIsUnitCardSelected(false);
}

const bool CombatUnitEditor::update(const sf::Vector2f& mousePosition)
{
	//Apply settings button
	if (m_applySettingsButton.checkIfButtonWasPressed(mousePosition))
	{
		updateUnitCards();
		return true;
	}

	//Attacker units panel
	if (m_attackerUnits.update(mousePosition))
	{
		m_isEditorActive = true;
		m_isAttackerSelected = true;
		m_selectedUnitPositionIndex = m_attackerUnits.getSelectedCardIndex();
		return false;
	}

	//Defender units panel
	if (m_defenderUnits.update(mousePosition))
	{
		m_isEditorActive = true;
		m_isAttackerSelected = false;
		m_selectedUnitPositionIndex = m_defenderUnits.getSelectedCardIndex();
		return false;
	}

	//Unit editor
	if (m_isEditorActive)
	{
		if (Global::g_isLMBPressed) //Resets input button focus
		{
			m_setNumberOfUnitsInputBox.setButtonPressed(false);
		}

		if (m_setNumberOfUnitsInputBox.checkIfButtonWasPressed(mousePosition))
		{
			m_setNumberOfUnitsInputBox.buttonPressedToggle();
			return false;
		}

		for (int i =0; i < settings::c_numOfButtons; i++)
		{
			if (m_buttons[i]->checkIfButtonWasPressed(mousePosition))
			{
				switch (static_cast<CombatUnitEditorEnum>(i))
				{
				case CombatUnitEditorEnum::apply:
					applyUnitChanges();
					break;

				case CombatUnitEditorEnum::deleteUnit:
					deleteUnit();
					break;

				case CombatUnitEditorEnum::close:
					resetSelectedUnitCards();
					m_isEditorActive = false;
					break;

				default:
					break;
				}

				return false;
			}
		}
		m_setNumberOfUnitsInputBox.update();

		m_unitList.update(mousePosition);
		updateUnitListOutline();

	}
	return false;
}

void CombatUnitEditor::updateUnitListOutline()
{
	const sf::Vector2f& iconPos = m_unitList.getIconButton(m_unitList.getIndexOfButtonClicked()).getIconSprite().getPosition();
	m_unitListOutline.moveBorder(iconPos.x, iconPos.y);
	m_unitListOutline.setPosition(iconPos);
}

void CombatUnitEditor::draw()
{
	m_attackerUnits.draw();
	m_defenderUnits.draw();

	m_applySettingsButton.draw();

	if (m_isEditorActive)
	{
		m_background.drawUIBackground();
		m_unitList.draw();
		m_unitListOutline.drawUIBorder();
		m_setNumberOfUnitsInputBox.draw();
		for (auto& button : m_buttons)
		{
			button->draw();
		}
		m_background.drawUIBorder();
	}
}

const bool CombatUnitEditor::getIsEditorActive() const
{
	return m_isEditorActive;
}

Unit* CombatUnitEditor::getSelectedUnit()
{
	if (m_isAttackerSelected)
	{
		return &*m_attackerUnits.getVectorOfUnitsUsedByThisPanel()->at(m_selectedUnitPositionIndex);
	}
	else
	{
		return &*m_defenderUnits.getVectorOfUnitsUsedByThisPanel()->at(m_selectedUnitPositionIndex);
	}
}
