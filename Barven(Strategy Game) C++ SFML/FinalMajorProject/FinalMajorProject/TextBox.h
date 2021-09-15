//Author: Maciej Dowbor
//Last Accessed: 14/07/2021

#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "TextBoxTitle.h"
#include "Text.h"
#include "UIElement.h"

//===========================================================================================
//Description: UI Element containing text with an option of having a title
//===========================================================================================
class TextBox : virtual public TextBoxTitle, public Text, public virtual UIElement
{
private:

public:
	
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	TextBox(sf::RenderWindow& window, Textures* pTextures, Fonts* pFonts);

	//===========================================================================================
	//Description: Class constructor, set last paramater to true to use thin border textures for
	//			   UI Element
	//===========================================================================================
	TextBox(sf::RenderWindow& window, Textures* pTextures, Fonts* pFonts, const bool setThinUIBorder);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~TextBox();

	//===========================================================================================
	//Description: Sets positions of class components using x and y coordinates
	//===========================================================================================
	void setPosition(const float& x, const float& y);

	//===========================================================================================
	//Description: Sets positions of class components using sf::Vector2f
	//===========================================================================================
	void setPosition(const sf::Vector2f& position);

	//===========================================================================================
	//Description: Resizes the UI Element to fit the height of the text
	//===========================================================================================
	void resizeBorderToFitText();

	//===========================================================================================
	//Description: Draws class components
	//===========================================================================================
	void draw();

};

#endif // !TEXTBOX_H

