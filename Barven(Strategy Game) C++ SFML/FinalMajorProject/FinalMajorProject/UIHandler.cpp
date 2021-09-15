#include "UIHandler.h"

UIHandler::UIHandler(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts, ConfirmationWindow& rConfirmationWindow) :
	m_resourceBar(rWindow, &rTextures, &rFonts),
	m_specialBuildingInteractions(rWindow, rTextures, rFonts, rConfirmationWindow),
	m_townInteraction(rWindow, &rTextures, &rFonts, rConfirmationWindow, m_resourceBar),
	m_mapUI(rWindow, rTextures, rFonts),
	m_heroPanel(rWindow, rTextures, rFonts),
	m_mapObjInfoBox(rWindow, rTextures, rFonts)
{
	m_resourceBar.setUp();
}

UIHandler::~UIHandler()
{
}

void UIHandler::initialize()
{
	m_townInteraction.initialize();
	m_mapUI.setUpMapUI();
	m_heroPanel.setUpHeroPanel();
}

void UIHandler::update(sf::Vector2f& mousePosition, const float& deltaTime)
{
	m_specialBuildingInteractions.update(mousePosition);

	m_townInteraction.update(mousePosition, deltaTime);

	m_mapUI.update(mousePosition);

	m_heroPanel.update(mousePosition);

	m_mapObjInfoBox.update();
}

ResourcesBar& UIHandler::getResourceBarReference()
{
	return m_resourceBar;
}

SpecialBuildingInteractions& UIHandler::getSpecialBuildingsInteractionReference()
{
	return m_specialBuildingInteractions;
}

Town& UIHandler::getTownReference()
{
	return m_townInteraction;
}

MapUI& UIHandler::getMapUIReference()
{
	return m_mapUI;
}

HeroPanel& UIHandler::getHeroPanelReference()
{
	return m_heroPanel;
}

MapObjectsInformationBox& UIHandler::getMapObjectsInformationBoxReference()
{
	return m_mapObjInfoBox;
}

void UIHandler::draw()
{
	if (Global::g_UILayer != UILayerEnum::combat)
	{
		m_resourceBar.draw();
		m_mapUI.draw();
		m_heroPanel.draw();
		m_mapObjInfoBox.draw();
		m_specialBuildingInteractions.draw();
	}

}