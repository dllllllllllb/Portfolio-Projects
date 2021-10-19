#include "CombatUnit.h"

namespace settings = CombatUnitSettings;

CombatUnit::CombatUnit(sf::RenderWindow& rWindow, Textures& rTextures, Audio& rAudio, Fonts& rFonts) :
	MoveableObject(rAudio),
	m_isLargeUnit(false),
	m_isAttacker(false),
	m_didUnitSkipTurn(false),
	m_isUnitAI(false),
	m_occupiedTileIndex(0),
	m_vectorPositionIndex(0),
	m_numberOfUnitsTextBox(rWindow, rTextures, rFonts, true)
{
	m_numberOfUnitsTextBox.setPosition(0, 0);
	m_numberOfUnitsTextBox.setUpUIBorder(settings::c_textBoxWidth, settings::c_textBoxHeight);
	m_numberOfUnitsTextBox.setUpText("0", settings::c_charSize, TextAlignmentEnum::middleHorizontal, TextAlignmentEnum::middleVertical);
}

CombatUnit::~CombatUnit()
{
}

void CombatUnit::setUnit(Unit& unit)
{
	for (int i = 0; i < settings::c_numOfAmendableVariables; i++)
	{
		setUnitSpecificData(static_cast<UnitBattleDataEnum>(i), unit.getUnitSpecificData(static_cast<UnitBattleDataEnum>(i)));
	}

	setBaseUnitData(unit.getBaseUnitData());
	setNumOfUnits(unit.getNumOfUnits());
	resetCurrentHealth();

	if (m_pBaseUnitData->getUnitSprite().getSize().x > settings::c_maxSingleTileUnitWidth)
	{
		m_isLargeUnit = true;
	}

	setTexture(m_pBaseUnitData->getUnitSprite(), true);

	int origin = 0;
	if (m_pBaseUnitData->getUnitSprite().getSize().x > settings::c_maxSingleTileUnitWidth)
	{
		origin = m_pBaseUnitData->getUnitSprite().getSize().x * 0.5f;
	}
	setOrigin(origin, getGlobalBounds().height - CombatHandlerSettings::c_tileSize + 6);

	m_numberOfUnitsTextBox.moveUIElement(getPosition().x, getPosition().y);
}

void CombatUnit::setUnit(UnitData& unitData)
{
	for (int i = 0; i < settings::c_numOfAmendableVariables; i++)
	{
		setUnitSpecificData(static_cast<UnitBattleDataEnum>(i), unitData.getBattleData(static_cast<UnitBattleDataEnum>(i)));
	}

	setBaseUnitData(&unitData);
	resetCurrentHealth();

	if (m_pBaseUnitData->getUnitSprite().getSize().x > settings::c_maxSingleTileUnitWidth)
	{
		m_isLargeUnit = true;
	}

	setTexture(m_pBaseUnitData->getUnitSprite(), true);

	m_numberOfUnitsTextBox.moveUIElement(getPosition().x, getPosition().y);
	updateTextBoxPosition();
}

void CombatUnit::update(const float& deltaTime)
{
	if (m_isMoving)
	{
		updateMovement(deltaTime);
		updateTextBoxPosition();
	}
}

void CombatUnit::setDefenderSpriteOrigin()
{
	setOrigin(m_pBaseUnitData->getUnitSprite().getSize().x, getGlobalBounds().height - CombatHandlerSettings::c_tileSize + 6);
}

void CombatUnit::setIsAttacker(const bool state)
{
	m_isAttacker = state;
}

void CombatUnit::updateTextBoxPosition()
{
	int textBoxPositionX = getPosition().x;

	if (m_isAttacker)
	{
		if (m_isLargeUnit)
		{
			textBoxPositionX += settings::c_largeAttackerTextBoxOffsetX;
		}
		else
		{
			textBoxPositionX += settings::c_smallAttackerTextBoxOffsetX;
		}
	}
	else
	{
		if (m_isLargeUnit)
		{
			textBoxPositionX += settings::c_largeDefenderTextBoxOffsetX;
		}
		else
		{
			textBoxPositionX += settings::c_smallDefenderTextBoxOffsetX;
		}
	}

	m_numberOfUnitsTextBox.moveUIElement(textBoxPositionX, getPosition().y + settings::c_textBoxOffsetY);
	m_numberOfUnitsTextBox.updateAlignment();
}

TextBox& CombatUnit::getNumberOfUnitsTextBox()
{
	return m_numberOfUnitsTextBox;
}

const bool CombatUnit::getIsAttacker() const
{
	return m_isAttacker;
}

const bool CombatUnit::getIsLargeUnit() const
{
	return m_isLargeUnit;
}

void CombatUnit::setOccupiedTileIndex(const int tileIndex)
{
	m_occupiedTileIndex = tileIndex;
}

const int& CombatUnit::getOccupiedTileIndex() const
{
	return m_occupiedTileIndex;
}

void CombatUnit::toggleDidUnitSkipTurn()
{
	m_didUnitSkipTurn = !m_didUnitSkipTurn;
}

const bool CombatUnit::getDidUnitSkipTurn() const
{
	return m_didUnitSkipTurn;
}

void CombatUnit::setVectorPositionIndex(const int& index)
{
	m_vectorPositionIndex = index;
}

const int& CombatUnit::getVectorPositionIndex() const
{
	return m_vectorPositionIndex;
}

void CombatUnit::setIsUnitAI(const bool state)
{
	m_isUnitAI = state;
}

const bool CombatUnit::getIsUnitAI() const
{
	return m_isUnitAI;
}
