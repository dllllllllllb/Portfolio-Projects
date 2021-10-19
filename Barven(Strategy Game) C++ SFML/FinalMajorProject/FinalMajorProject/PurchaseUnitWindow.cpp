#include "PurchaseUnitWindow.h"
namespace settings = PurchaseUnitSettings;

PurchaseUnitWindow::PurchaseUnitWindow(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts, Audio& rAudio, ConfirmationWindow& rConfirmationWindow) :
	UIElement(rWindow, rTextures),
	TextBoxTitle(rWindow, rTextures, rFonts),
	m_confirmationWindow(rConfirmationWindow),
	m_unitImageBackground(rWindow, rTextures, true),
	m_unitStats(rWindow, rTextures, rFonts, true),
	m_slider(rWindow, rTextures, true),
	m_unitsToRecruit(rWindow, rTextures, rFonts, true),
	m_costOfRecruiting(rWindow, rTextures, rFonts, true),
	m_numOfUnitsToRecruit(0),
	m_maxNumOfUnitsToRecruit(0),
	m_costPerUnit(0),
	m_purchaseButton(rWindow, rTextures, rFonts, rAudio)
{
}

PurchaseUnitWindow::~PurchaseUnitWindow()
{
}

void PurchaseUnitWindow::setUpPurchaseWindow()
{
	sf::Vector2f centre = m_window.getView().getCenter();

	//Background, border and title text
	UIElement::setPosition(centre.x + settings::c_purchaseWindowPositionXOffset, m_window.getSize().y * 0.5f);
	UIElement::setUpUIBorder(settings::c_borderWidth, settings::c_borderHeight);
	setUpTitleText(settings::c_title, settings::c_titleCharSize);

	//Background for displaing unit sprites
	m_unitImageBackground.setPosition(UIElement::getPosition().x - UIElement::getGlobalBounds().width * 0.5f + settings::c_recruitObjectsSpaceing + settings::c_recruitElementBackgroundWidth * 0.5f, centre.y - settings::c_recruitElementBackgroundHeight * 0.4f);
	m_unitImageBackground.setTexture(m_textures.m_unitBackground[0], true);
	m_unitImageBackground.setUpUIBorder(settings::c_recruitElementBackgroundWidth, settings::c_recruitElementBackgroundHeight);

	//Text box that displays units stats
	m_unitStats.setPosition(UIElement::getPosition().x + UIElement::getGlobalBounds().width * 0.5f - settings::c_recruitObjectsSpaceing - settings::c_recruitElementBackgroundWidth * 0.5f, centre.y - settings::c_recruitElementBackgroundHeight * 0.4f);
	m_unitStats.setUpUIBorder(settings::c_recruitElementBackgroundWidth, settings::c_recruitElementBackgroundHeight);
	m_unitStats.setHasMultipleLines(true);

	//Sets sprite position and scale
	m_unitSprite.setPosition(m_unitImageBackground.getPosition());
	m_unitSprite.setScale(1.2f, 1.2f);

	//Slider
	m_slider.setUpSlider(centre.x + settings::c_purchaseWindowPositionXOffset, m_unitImageBackground.getPosition().y + settings::c_recruitElementBackgroundHeight * 0.7f, settings::c_recruitElementBackgroundWidth * 2, settings::c_sliderHeight);
	m_slider.setFunctionToCallAfterResize(std::bind(&PurchaseUnitWindow::updatePlayerFeedbackTextBoxes, this));

	//Text box that displays selected units to recruit
	m_unitsToRecruit.setPosition(centre.x + settings::c_purchaseWindowPositionXOffset, m_slider.getPosition().y + m_slider.getGlobalBounds().height * 0.5f + settings::c_recruitObjectsSpaceing);
	m_unitsToRecruit.setUpUIBorder(settings::c_unitsToRecruitBoxWidth, settings::c_unitsToRecruitBoxHeight);
	m_unitsToRecruit.setUpText("14 / 14", settings::c_unitsToRecruitTextSize, TextAlignmentEnum::middleHorizontal, TextAlignmentEnum::middleVertical);

	//Text box that displays cost of recruitment
	m_costOfRecruiting.setPosition(centre.x + settings::c_purchaseWindowPositionXOffset, m_unitsToRecruit.UIElement::getPosition().y + settings::c_unitsToRecruitBoxHeight * 0.5f + settings::c_recruitObjectsSpaceing);
	m_costOfRecruiting.setUpUIBorder(settings::c_unitsToRecruitBoxWidth, settings::c_unitsToRecruitBoxHeight);
	m_costOfRecruiting.setUpText("100 gold", settings::c_unitsToRecruitTextSize, TextAlignmentEnum::middleHorizontal, TextAlignmentEnum::middleVertical);

	//Purchase button
	m_purchaseButton.setPosition(centre.x + settings::c_purchaseWindowPositionXOffset, m_costOfRecruiting.UIElement::getPosition().y + settings::c_unitsToRecruitBoxHeight + settings::c_purchaseButtonHeight * 0.5f);
	m_purchaseButton.setUpUIBorder(settings::c_purchaseButtonWidth, settings::c_purchaseButtonHeight);
	m_purchaseButton.setCollisionBounds(settings::c_purchaseButtonWidth, settings::c_purchaseButtonHeight);
	m_purchaseButton.setUpText(settings::c_title, settings::c_titleCharSize, TextAlignmentEnum::middleHorizontal, TextAlignmentEnum::middleVertical);
}

void PurchaseUnitWindow::reposition()
{
	sf::Vector2f centre = m_window.getView().getCenter();

	UIElement::moveUIElement(centre.x + settings::c_purchaseWindowPositionXOffset, m_window.getSize().y * 0.5f);
	m_unitImageBackground.moveUIElement(UIElement::getPosition().x - UIElement::getGlobalBounds().width * 0.5f + settings::c_recruitObjectsSpaceing + settings::c_recruitElementBackgroundWidth * 0.5f, centre.y - settings::c_recruitElementBackgroundHeight * 0.4f);
	m_unitStats.setPosition(UIElement::getPosition().x + UIElement::getGlobalBounds().width * 0.5f - settings::c_recruitObjectsSpaceing - settings::c_recruitElementBackgroundWidth * 0.5f, centre.y - settings::c_recruitElementBackgroundHeight * 0.4f);
	m_unitSprite.setPosition(m_unitImageBackground.getPosition());
	m_slider.reposition(centre.x + settings::c_purchaseWindowPositionXOffset, m_unitImageBackground.getPosition().y + settings::c_recruitElementBackgroundHeight * 0.52f);
	m_unitsToRecruit.setPosition(centre.x + settings::c_purchaseWindowPositionXOffset, m_slider.getPosition().y + m_slider.getGlobalBounds().height * 0.5f + settings::c_recruitObjectsSpaceing);
	m_purchaseButton.setPosition(centre.x + settings::c_purchaseWindowPositionXOffset, centre.y + settings::c_purchaseButtonPositionYOffset);
}

void PurchaseUnitWindow::update(const sf::Vector2f& mousePosition)
{
    m_slider.update(mousePosition);

	if (m_purchaseButton.checkIfButtonWasPressed(mousePosition))
	{
		m_confirmationWindow.changeUILayerToConfirmation();
	}
}

void PurchaseUnitWindow::updatePlayerFeedbackTextBoxes()
{
	m_unitsToRecruit.setTextAndUpdate(std::to_string(getNumberOfUnitsToRecruit()) + " / " + std::to_string(m_maxNumOfUnitsToRecruit), settings::c_unitsToRecruitTextSize);
	m_costOfRecruiting.setTextAndUpdate(std::to_string(getNumberOfUnitsToRecruit() * m_costPerUnit) + " gold");
}

void PurchaseUnitWindow::setWindowContent(const UnitData* unitData, const int& unitsAvailable)
{
	const UnitData& tempData = *unitData->getUnitData();
	m_unitStats.setUpTitleText(tempData.getStringData(UnitDataEnum::unitName), 24);

	//Sets contents of the text box
	std::string statsText = "Health: " + std::to_string(tempData.getIntData(UnitDataEnum::health)) + "\n" +
		"Attack: " + std::to_string(tempData.getIntData(UnitDataEnum::attack)) + "\n" +
		"Damage Range: " + std::to_string(tempData.getIntData(UnitDataEnum::minDamage)) + "-" + std::to_string(tempData.getIntData(UnitDataEnum::maxDamage)) + "\n" +
		"Defence: " + std::to_string(tempData.getIntData(UnitDataEnum::defence)) + "\n" +
		"Ammunition: " + std::to_string(tempData.getIntData(UnitDataEnum::ammunition)) + "\n" +
		"Range: " + std::to_string(tempData.getIntData(UnitDataEnum::range)) + "\n" +
		"Speed: " + std::to_string(tempData.getIntData(UnitDataEnum::speed)) + "\n" +
		"Cost: " + std::to_string(tempData.getIntData(UnitDataEnum::cost)) + " gold";

	m_unitStats.setUpText(statsText, 18, TextAlignmentEnum::left, TextAlignmentEnum::middleVertical);

	m_unitSprite.setTexture(unitData->getUnitSprite(), true);
	m_unitSprite.setOrigin(m_unitSprite.getLocalBounds().width * 0.5f, m_unitSprite.getLocalBounds().height * 0.5f);

	m_numOfUnitsToRecruit = unitsAvailable;
	m_maxNumOfUnitsToRecruit = unitsAvailable;
	m_costPerUnit = tempData.getIntData(UnitDataEnum::cost);

	m_slider.resetSlider();

	m_unitsToRecruit.setTextAndUpdate(std::to_string(unitsAvailable) + " / " + std::to_string(unitsAvailable), settings::c_unitsToRecruitTextSize);
	m_costOfRecruiting.setTextAndUpdate(std::to_string(getNumberOfUnitsToRecruit() * m_costPerUnit) + " gold");
}

void PurchaseUnitWindow::setUnitBackground(const int& factionIndex)
{
	m_unitImageBackground.setTexture(m_textures.m_unitBackground[factionIndex]);
}

void PurchaseUnitWindow::purchaseUnits()
{
	m_purchaseUnitsFunction();
	m_confirmationWindow.changeUILayerToTown();
}

void PurchaseUnitWindow::setPurchaseUnitFunction(std::function<void()> function)
{
	m_purchaseUnitsFunction = function;
}

const int PurchaseUnitWindow::getNumberOfUnitsToRecruit() const
{
	int unitsToRecruit = m_numOfUnitsToRecruit * m_slider.getSliderValue();
	if (m_slider.getSliderValue() > 0.98) //If slider value is close to 1, round it up
	{
		unitsToRecruit = m_maxNumOfUnitsToRecruit;
	}

	return unitsToRecruit;
}

void PurchaseUnitWindow::updateConfirmationFunctionPointer()
{
	m_confirmationWindow.setConfirmationFunctionPointer((std::bind(&PurchaseUnitWindow::purchaseUnits, this)));
}

void PurchaseUnitWindow::draw()
{
	drawUIBorderAndBackground();
	m_window.draw(m_titleText);
	m_unitImageBackground.drawUIBackground();
	m_window.draw(m_unitSprite);
	m_unitImageBackground.drawUIBorder();
	m_unitStats.draw();
	m_slider.draw();
	m_unitsToRecruit.draw();
	m_costOfRecruiting.draw();
	m_purchaseButton.draw();
}