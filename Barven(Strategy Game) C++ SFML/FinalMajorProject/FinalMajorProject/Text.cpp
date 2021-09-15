#include "Text.h"

Text::Text(sf::RenderWindow& window, Textures* textures, Fonts* pFonts) :
	UIElement(window, textures),
	m_horizontalAlignment(TextAlignmentEnum::middleHorizontal),
	m_verticalAlignment(TextAlignmentEnum::middleVertical),
	m_numOfCharactersPerLine(0),
	m_hasMultipleLines(false),
	m_hasBackground(true),
	m_titleOffset(0),
	m_pFonts(pFonts)
{
}

Text::~Text()
{
}

void Text::setAlignment(const TextAlignmentEnum& horizontalAlignment, const TextAlignmentEnum& verticalAlignment)
{
	m_horizontalAlignment = horizontalAlignment;
	m_verticalAlignment = verticalAlignment;
	updateAlignment();
}

void Text::setHorizontalAlignment(const TextAlignmentEnum& horizontalAlignment)
{
	m_horizontalAlignment = horizontalAlignment;
	updateHorizontalAlignment();
}

void Text::setVerticalAlignment(const TextAlignmentEnum& verticalAlignment)
{
	m_verticalAlignment = verticalAlignment;
	updateVerticalAlignment();
}

void Text::updateAlignment()
{
	updateHorizontalAlignment();
	updateVerticalAlignment();
}

void Text::updateHorizontalAlignment()
{
	switch (m_horizontalAlignment)
	{
	case TextAlignmentEnum::left:
	{
		sf::Text::setOrigin(0, sf::Text::getOrigin().y);
		if (m_hasBackground)
		{
			float posX = UIElement::getPosition().x - (UIElement::getGlobalBounds().width * 0.5f) + c_UIBorder * 2;
			sf::Text::setPosition(posX, sf::Text::getPosition().y);
		}
	}
	break;

	case TextAlignmentEnum::middleHorizontal:
	{
		sf::Text::setOrigin(sf::Text::getGlobalBounds().width * 0.5f, sf::Text::getOrigin().y);
		if (m_hasBackground)
		{
			sf::Text::setPosition(UIElement::getPosition().x, sf::Text::getPosition().y);
		}
	}
	break;

	case TextAlignmentEnum::right:
	{
		sf::Text::setOrigin(sf::Text::getGlobalBounds().width, sf::Text::getOrigin().y);
		if (m_hasBackground)
		{
			float posX = UIElement::getPosition().x + (UIElement::getGlobalBounds().width * 0.5f) - c_UIBorder * 2;
			sf::Text::setPosition(posX, sf::Text::getPosition().y);
		}
	}
	break;

	default:
		break;
	}
}

void Text::updateVerticalAlignment()
{
	//Makes sure that origin is consistent, if you have a string without any letters that go below text line (like j,p,q,y) the y origin will be skewed upwards
	std::string tempString = sf::Text::getString();
	if (!m_hasMultipleLines)
	{
		sf::Text::setString("Pp");
	}

	switch (m_verticalAlignment)
	{
	case TextAlignmentEnum::top:
	{
		sf::Text::setOrigin(sf::Text::getOrigin().x, 0);
		if (m_hasBackground)
		{
			float posY = UIElement::getPosition().y - UIElement::getGlobalBounds().height * 0.5f + c_UIBorder + m_titleOffset;
			sf::Text::setPosition(sf::Text::getPosition().x, posY);
		}
	}
	break;

	case TextAlignmentEnum::middleVertical:
	{
		if (m_hasMultipleLines)
		{
			sf::Text::setOrigin(sf::Text::getOrigin().x, sf::Text::getLocalBounds().height * 0.5f);
		}
		else
		{
			sf::Text::setOrigin(sf::Text::getOrigin().x, sf::Text::getLocalBounds().height * 0.75f); //sf::Text bounds are not accurate with text in a single line, middle of the text is about 75% from the top
		}

		if (m_hasBackground)
		{
			sf::Text::setPosition(sf::Text::getPosition().x, UIElement::getPosition().y + m_titleOffset);
		}
	}
	break;

	case TextAlignmentEnum::bottom:
	{
		sf::Text::setOrigin(sf::Text::getOrigin().x, 1);
		if (m_hasBackground)
		{
			sf::Text::setString(tempString);
			float posY = UIElement::getPosition().y + UIElement::getGlobalBounds().height * 0.5f - (2 * c_UIBorder) - sf::Text::getGlobalBounds().height;
			sf::Text::setPosition(sf::Text::getPosition().x, posY);
		}
	}
	break;

	default:
		break;
	}

	if (!m_hasMultipleLines)
	{
		sf::Text::setString(tempString);
	}
}

void Text::calcCharactersPerLine()
{
	//Store the actual string to be used
	std::string temp = sf::Text::getString();

	std::string tempAllignmentString = "";
	sf::Text::setString(tempAllignmentString);
	int numOfChars = 0;

	//Just like with the alignment, char size doesn't give the actual width of a char so you have to set the string to characters with various widths to estimate the num of chars that fit
	while (sf::Text::getGlobalBounds().width < UIElement::getGlobalBounds().width - (sf::Text::getCharacterSize() * 3) - 10)
	{
		tempAllignmentString += " iD "; //For some reason this combination of chars works best
		numOfChars += 4; //Num of chars in the string above
		sf::Text::setString(tempAllignmentString);
	}
	m_numOfCharactersPerLine = numOfChars;

	//Set the string back to its original string
	sf::Text::setString(temp);
}

void Text::divideTextToLines()
{
	calcCharactersPerLine();

	std::string tempString = getString();
	bool canHaveMultipleLines = true;
	int lineIndex = 1; //Current line the algorithm is on, has to start at 1
	float maxTextWidth = UIElement::getGlobalBounds().width - c_UIBorder - c_UIBorder; //Width where text can be written

	//Loop while the width of the text is bigger than maximum text width
	while (sf::Text::getGlobalBounds().width > maxTextWidth && canHaveMultipleLines)
	{
		size_t stringIndex = m_numOfCharactersPerLine * lineIndex;

		size_t stringPositiveIndex = stringIndex;
		int strPosCounter = 0;

		int stringNegativeIndex = stringIndex;
		int strNegCounter = 0;

		//Makes sure that the index is valid
		if (stringIndex < tempString.length())
		{
			//Loops back untill the char is an empty space and counts how many characters it had to move
			while (tempString[stringNegativeIndex] != ' ')
			{
				stringNegativeIndex--;
				strNegCounter++;

				//Makes sure that the index is valid
				if (stringNegativeIndex < 0)
				{
					canHaveMultipleLines = false;
					strNegCounter = 100;
					break;
				}
			}

			//Loops forward untill the char is an empty space and counts how many charactes it had to move
			while (tempString[stringPositiveIndex] != ' ')
			{
				stringPositiveIndex++;
				strPosCounter++;

				//Makes sure that the index is valid
				if (stringPositiveIndex >= tempString.length())
				{
					strPosCounter = 100;
					break;
				}
			}

			//Compares which way(backwards/forwards) is faster to reach an empty space
			if (strPosCounter > strNegCounter)
			{
				stringIndex = stringNegativeIndex;
			}
			else
			{
				stringIndex = stringPositiveIndex;
			}

			//Makes sure that text can have multiple lines
			if (canHaveMultipleLines)
			{
				tempString.erase(stringIndex, 1); //Deletes empty space

				tempString.insert(stringIndex, "\n"); //Inserts a new line
				setString(tempString);
				lineIndex++;
				m_hasMultipleLines = true;
			}
		}
		else
		{
			break;
		}
	}
}

void Text::setTextAndUpdate(const std::string& string, const int& charSize)
{
	setString(string);
	setCharacterSize(charSize);
	divideTextToLines();
	updateAlignment();
}

void Text::setTextAndUpdate(const std::string& string)
{
	setString(string);
	updateAlignment();
}

void Text::setUpText(const std::string& string, const int& charSize, const TextAlignmentEnum& horizontal, const TextAlignmentEnum& vertical)
{
	setFont(m_pFonts->m_fontBasic);
	setAlignment(horizontal, vertical);
	setTextAndUpdate(string, charSize);
}

void Text::setTitleOffset(const int& titleOffset)
{
	m_titleOffset = titleOffset + c_UIBorder;
	updateAlignment();
}

void Text::setHasMultipleLines(const bool state)
{
	m_hasMultipleLines = state;
}

void Text::basicSetUp(const std::string& string, const int& charSize, const int& positionX, const int& positionY)
{
	setFont(m_pFonts->m_fontBasic);
	setCharacterSize(charSize);
	setString(string);
	updateAlignment();
	sf::Text::setPosition(positionX, positionY);
}

void Text::setHasBackground(const bool hasBackground)
{
	m_hasBackground = hasBackground;
}

void Text::draw()
{
	m_window.draw((sf::Text)*this);
}