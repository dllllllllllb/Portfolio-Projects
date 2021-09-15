//Author: Maciej Dowbor
//Last Accessed: 29/04/2021

#ifndef TEXT_H
#define TEXT_H

#include <SFML/Graphics/Text.hpp>

#include "ConstantVariables.h"
#include "Fonts.h"
#include "UIElement.h"
#include "TextAlignmentEnum.h"

//===========================================================================================
//Description: Improved sf::Text with options to set alignments and divide text to lines
//===========================================================================================
class Text : public sf::Text, public virtual UIElement
{
private:
	TextAlignmentEnum m_horizontalAlignment;
	TextAlignmentEnum m_verticalAlignment;
	int m_numOfCharactersPerLine;
	bool m_hasMultipleLines;
	bool m_hasBackground;

protected:
	int m_titleOffset;
	Fonts* m_pFonts;

public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	Text(sf::RenderWindow& window, Textures* textures, Fonts* pFonts);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~Text();

	//===========================================================================================
	//Description: Sets horizontal and vertical alignment
	//===========================================================================================
	void setAlignment(const TextAlignmentEnum& horizontalAlignment, const TextAlignmentEnum& verticalAlignment);

	//===========================================================================================
	//Description: Sets horizontal alignemnt
	//===========================================================================================
	void setHorizontalAlignment(const TextAlignmentEnum& horizontalAlignment);

	//===========================================================================================
	//Description: Sets vertical alignment
	//===========================================================================================
	void setVerticalAlignment(const TextAlignmentEnum& verticalAlignment);

	//===========================================================================================
	//Description: Updates horizontal and vertical alignment
	//===========================================================================================
	void updateAlignment();

	//===========================================================================================
	//Description: Updates horizontal alignment
	//===========================================================================================
	void updateHorizontalAlignment();

	//===========================================================================================
	//Description: Updates vertical alignment
	//===========================================================================================
	void updateVerticalAlignment();

	//===========================================================================================
	//Description: Calculates how many characters fit per line in its UI Element
	//===========================================================================================
	void calcCharactersPerLine();

	//===========================================================================================
	//Description: Divides a string into seperate lines to fit inside its UI Element
	//===========================================================================================
	void divideTextToLines();

	//===========================================================================================
	//Description: Sets text string and char size
	//===========================================================================================
	void setTextAndUpdate(const std::string& string, const int& charSize);

	//===========================================================================================
	//Description: Sets text string
	//===========================================================================================
	void setTextAndUpdate(const std::string& string);

	//===========================================================================================
	//Description: Sets text string, char size and alignment
	//===========================================================================================
	void setUpText(const std::string& string, const int& charSize, const TextAlignmentEnum& horizontal, const TextAlignmentEnum& vertical);

	//===========================================================================================
	//Description: Sets title offset
	//===========================================================================================
	void setTitleOffset(const int& titleOffset);

	//===========================================================================================
	//Description: Allows to set multiple line bool outside of the class
	//===========================================================================================
	void setHasMultipleLines(const bool state);

	//===========================================================================================
	//Description: Basic text set up
	//===========================================================================================
	void basicSetUp(const std::string& string, const int& charSize, const int& positionX, const int& positionY);

	//===========================================================================================
	//Description: Sets bool that determines if text has background attached to it
	//===========================================================================================
	void setHasBackground(const bool state);

	//===========================================================================================
	//Description: Draws text
	//===========================================================================================
	void draw();
};
#endif // !TEXT_H
