#include "DropDownList.h"

DropDownList::DropDownList(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts, Audio& rAudio) :
	m_window(rWindow),
	m_textures(rTextures),
	m_fonts(rFonts),
	m_audio(rAudio),
	m_slider(rWindow, rTextures, false),
	m_numberOfOptions(0),
	m_firstVisibleOption(0),
	m_selectedOptionID(0),
	m_isDropDownActive(false),
	m_numOfOptionsToDisplay(0),
	m_optionWidth(0),
	m_optionHeight(0),
	m_positionX(0),
	m_positionY(0),
	m_optionSpaceing(0),
	m_primaryButtonTitle(""),
	m_titleCharSize(0),
	m_primaryButtonContentText(""),
	m_buttonContentCharSize(0),
	m_primaryButton(rWindow, rTextures, rFonts, rAudio)
{
	m_slider.setFunctionToCallAfterResize(std::bind(&DropDownList::updateVisibleOptions, this));
}

DropDownList::~DropDownList()
{
}

void DropDownList::setDropDownListSettings(const int& numOfOptionsToDisplay, const int& optionWidth, const int& optionHeight, const int& positionX, const int& positionY, const int& optionSpaceing, const std::string& primaryButtonTitle, const int& titleCharSize, const std::string& primaryButtonContentText, const int& buttonContentCharSize)
{
	m_numOfOptionsToDisplay = numOfOptionsToDisplay;
	m_optionWidth = optionWidth;
	m_optionHeight = optionHeight;
	m_positionX = positionX;
	m_positionY = positionY;
	m_optionSpaceing = optionSpaceing;
	m_primaryButtonTitle = primaryButtonTitle;
	m_titleCharSize = titleCharSize;
	m_primaryButtonContentText = primaryButtonContentText;
	m_buttonContentCharSize = buttonContentCharSize;

	m_primaryButton.setPosition(positionX, m_positionY - 15);
	m_primaryButton.setUpUIBorder(m_optionWidth + 10, m_optionHeight + 30);
	m_primaryButton.setCollisionBounds(m_optionWidth + 10, m_optionHeight + 30);
	m_primaryButton.setUpTitleText(m_primaryButtonTitle, m_titleCharSize);
	m_primaryButton.setUpText(m_primaryButtonContentText, m_buttonContentCharSize, TextAlignmentEnum::middleHorizontal, TextAlignmentEnum::bottom);
}

void DropDownList::setConfirmationFunctionPointer(std::function<void()> function)
{
	m_functionToCallWhenItemSelected = function;
}

void DropDownList::addNewDropDownOptions(const std::string& optionName)
{
	m_pDropDownButtons.push_back(std::unique_ptr<Button>(new Button(m_window, m_textures, m_fonts, m_audio, true))); //Adds a new empty option to the vector
	m_pDropDownButtons[m_numberOfOptions]->setUpUIBorder(m_optionWidth, m_optionHeight); //Sets up option settings
	m_pDropDownButtons[m_numberOfOptions]->setCollisionBounds(m_optionWidth, m_optionHeight);
	m_pDropDownButtons[m_numberOfOptions]->setUpText(optionName, m_buttonContentCharSize, TextAlignmentEnum::middleHorizontal, TextAlignmentEnum::middleVertical);

	m_numberOfOptions++;
}

void DropDownList::setUpSlider()
{
	//Makes sure that the number of available options to display is smaller than the max number of options that can be displayed
	int numOfOptionsDisplayed = m_numberOfOptions;

	if (numOfOptionsDisplayed > m_numOfOptionsToDisplay)
	{
		numOfOptionsDisplayed = m_numOfOptionsToDisplay;
	}

	m_slider.setUpSlider(m_positionX + m_optionWidth * 0.5 + DropDownListSettings::c_sliderWidth - 6, m_positionY + ((numOfOptionsDisplayed * m_optionSpaceing) * 0.5f) + (m_optionHeight * 0.5f), DropDownListSettings::c_sliderWidth, (numOfOptionsDisplayed * m_optionSpaceing));
}

void DropDownList::setOptionsPositions()
{
	for (int i = m_firstVisibleOption; i < m_firstVisibleOption + m_numOfOptionsToDisplay; i++)
	{
		if (i < m_numberOfOptions)
		{
			m_pDropDownButtons[i]->reposition(m_positionX, m_positionY + (i - m_firstVisibleOption + 1) * m_optionSpaceing);
		}
	}
}

void DropDownList::updateVisibleOptions()
{
	int firstVisibleOption = (m_numberOfOptions - m_numOfOptionsToDisplay) - ((m_numberOfOptions - m_numOfOptionsToDisplay) * m_slider.getSliderValue());

	if (m_numberOfOptions - firstVisibleOption >= m_numOfOptionsToDisplay && firstVisibleOption >= 0)
	{
		m_firstVisibleOption = firstVisibleOption;
		setOptionsPositions();
	}
}

void DropDownList::update(const sf::Vector2f& mousePosition)
{
	if (m_isDropDownActive)
	{
		m_slider.update(mousePosition); //Update slider

		for (int index = m_firstVisibleOption; index < m_firstVisibleOption + m_numOfOptionsToDisplay; index++) //Only check currently visible options
		{
			if (index < m_numberOfOptions) //Makes sure that the index is valid
			{
				if (m_pDropDownButtons[index]->checkIfButtonWasPressed(mousePosition))
				{
					m_selectedOptionID = index;
					m_isDropDownActive = false;

					m_primaryButton.setString(m_pDropDownButtons[index]->getSelf()->getString());
					m_primaryButton.updateHorizontalAlignment();

					m_functionToCallWhenItemSelected();
					break;
				}
			}
		}
	}

	if (m_primaryButton.checkIfButtonWasPressed(mousePosition)) //Main drop down button
	{
		m_isDropDownActive = !m_isDropDownActive;
	}
}

const int& DropDownList::getSelectedOptionID() const
{
	return m_selectedOptionID;
}

void DropDownList::deleteOptions()
{
	m_pDropDownButtons.clear();
	m_numberOfOptions = 0;
}

void DropDownList::resizeSlider()
{
	int numOfOptionsDisplayed = m_numberOfOptions;

	if (numOfOptionsDisplayed > m_numOfOptionsToDisplay)
	{
		numOfOptionsDisplayed = m_numOfOptionsToDisplay;
	}

	m_slider.resizeSlider(m_positionX + m_optionWidth * 0.5 + DropDownListSettings::c_sliderWidth - 6, m_positionY + ((numOfOptionsDisplayed * m_optionSpaceing) * 0.5f) + (m_optionHeight * 0.5f), DropDownListSettings::c_sliderWidth, (numOfOptionsDisplayed * m_optionSpaceing));
}

void DropDownList::draw()
{
	if (m_isDropDownActive)
	{
		for (int index = m_firstVisibleOption; index < m_firstVisibleOption + m_numOfOptionsToDisplay; index++)
		{
			if (index < m_numberOfOptions)
			{
				m_pDropDownButtons[index]->draw();
			}
		}

		m_slider.draw();
	}

	m_primaryButton.draw();
	m_primaryButton.::TextBoxTitle::draw();
}
