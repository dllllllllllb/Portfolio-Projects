#include "SpecialBuildingInteractions.h"

namespace settings = SpecialBuildingInteractionsSettings;

SpecialBuildingInteractions::SpecialBuildingInteractions(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts, Audio& rAudio, ConfirmationWindow& rConfirmationWindow) :
	m_window(rWindow),
	m_textures(rTextures),
	m_fonts(rFonts),
	m_audio(rAudio),
	m_confirmationWindow(rConfirmationWindow),
	m_pPlayer(nullptr),
	m_textBox(rWindow, rTextures, rFonts),
	m_isActive(false),
	m_activeIconButtons(0),
	m_interactionIndex(0)
{
	initialize();
}

SpecialBuildingInteractions::~SpecialBuildingInteractions()
{
}

void SpecialBuildingInteractions::initialize()
{
	for (int i = 0; i < settings::c_numOfIconButtons; i++)
	{
		m_iconButtons.push_back(std::unique_ptr<IconButton>(new IconButton(m_window, m_textures, m_audio, true)));
	}
}

void SpecialBuildingInteractions::specialInteraction(const SpecialBuildingEnum& buildingType, Player* pPlayer)
{
	//Set appropriate vars
	m_pPlayer = pPlayer; 
	m_activeIconButtons = settings::c_numberOfIconButtonsRequired[static_cast<int>(buildingType)];
	toggleIsActive();

	switch (buildingType)
	{
	case SpecialBuildingEnum::arena:
		arenaInteractionSetUp();
		break;

	case SpecialBuildingEnum::watchTower:
		//Not properly implemented yet
		toggleIsActive();
		Global::g_UILayer = UILayerEnum::map;
		std::cout << "Watch tower entered!\n";
		break;

	default:
		break;
	}
}

void SpecialBuildingInteractions::arenaInteractionSetUp()
{
	m_confirmationWindow.changeUILayerToMapObjectInteraction();
	sf::Vector2f windowCentre = sf::Vector2f(m_window.getSize().x * 0.5f, m_window.getSize().y * 0.5f);

	m_iconButtons[0]->setUpAndResizeToSprite(windowCentre.x - settings::c_heroPrimaryStatIconWidth * 0.5f - settings::c_iconButtonsSpaceing * 0.5f, windowCentre.y + 5, m_textures.m_heroPrimarySkills[static_cast<int>(HeroStatsEnum::attack)]);
	m_iconButtons[1]->setUpAndResizeToSprite(windowCentre.x + settings::c_heroPrimaryStatIconWidth * 0.5f + settings::c_iconButtonsSpaceing * 0.5f, windowCentre.y + 5, m_textures.m_heroPrimarySkills[static_cast<int>(HeroStatsEnum::defence)]);

	m_textBox.setPosition(windowCentre);
	m_textBox.setUpUIBorder(settings::c_heroPrimaryStatIconWidth * 2 + settings::c_iconButtonsSpaceing * 4, settings::c_heroPrimaryStatIconHeight + settings::c_iconButtonsSpaceing * 2);
	m_textBox.setUpText(settings::c_arenaText, settings::c_titleCharSize, TextAlignmentEnum::middleHorizontal, TextAlignmentEnum::top);

	m_confirmationWindow.setConfirmationFunctionPointer(std::bind(&SpecialBuildingInteractions::arenaInteraction, this));
}

void SpecialBuildingInteractions::arenaInteraction()
{
	m_pPlayer->getSelectedHero().incrementHeroStat(static_cast<HeroStatsEnum>(m_interactionIndex), settings::c_arenaStatIncrease);
	toggleIsActive();
	m_confirmationWindow.changeUILayerToMap();
	std::cout << "Hero stat upgraded!\n";
}

void SpecialBuildingInteractions::update(const sf::Vector2f& mousePosition)
{
	if (m_isActive)
	{
		if (Global::g_UILayer == UILayerEnum::mapObjectInteraction)
		{
			for (int i = 0; i < m_activeIconButtons; i++)
			{
				if (m_iconButtons[i]->checkIfButtonWasPressed(mousePosition))
				{
					m_interactionIndex = i;
					m_confirmationWindow.changeUILayerToConfirmation();
					break;
				}
			}
		}
		else if (Global::g_UILayer == UILayerEnum::confirmation)
		{
			m_confirmationWindow.update(mousePosition);
		}
	}
}

void SpecialBuildingInteractions::toggleIsActive()
{
	m_isActive = !m_isActive;
}

void SpecialBuildingInteractions::draw()
{
	if (m_isActive)
	{
		if (Global::g_UILayer == UILayerEnum::mapObjectInteraction || Global::g_UILayer == UILayerEnum::confirmation)
		{
			m_textBox.draw();

			for (int i = 0; i < m_activeIconButtons; i++)
			{
				m_iconButtons[i]->draw();
			}

			if (Global::g_UILayer == UILayerEnum::confirmation)
			{
				m_confirmationWindow.draw();
			}
		}
	}
}
