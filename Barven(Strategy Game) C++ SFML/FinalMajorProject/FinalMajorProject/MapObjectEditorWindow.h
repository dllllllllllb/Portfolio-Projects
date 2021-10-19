//Author: Maciej Dowbor
//Last Accessed: 17/05/2021

#ifndef MAPOBJECTEDITORWINDOW_H
#define MAPOBJECTEDITORWINDOW_H

#include <functional>
#include <vector>

#include "TextInputBox.h"
#include "TextBoxTitle.h"
#include "MapCreatorSettings.h"
#include "BasicButton.h"

//===========================================================================================
//Description: Editor window for map objects, allows to edit variable values of selected
//			   object
//===========================================================================================
class MapObjectEditorWindow : public TextBoxTitle, virtual public UIElement
{
private:
	Audio& m_audio;
	int			m_numOfInputButtons;
	BasicButton m_acceptButton;
	BasicButton m_declineButton;

	std::vector<std::unique_ptr<TextInputBox>> m_inputButtons;

	std::function<void()> m_pApplyValuesToObjectFunction;
	std::function<void()> m_pCloseWindow;

public:
	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	MapObjectEditorWindow(sf::RenderWindow& rWindow, Textures& rTextures, Fonts& rFonts, Audio& rAudio);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~MapObjectEditorWindow();

	//===========================================================================================
	//Description: Configures the window based on selected objects number of editable variables
	//===========================================================================================
	void setUpWindow(const int& numOfButtons);

	//===========================================================================================
	//Description: Resizes the background of the window
	//===========================================================================================
	void resizeWindow();

	//===========================================================================================
	//Description: Sets up buttons for editable variables and displays their values
	//===========================================================================================
	void setUpButtons(const int& buttonIndex, const std::string& buttonName, const int& contentValue);

	//===========================================================================================
	//Description: Set apply values to object function pointer
	//===========================================================================================
	void setApplyValuesToObjectFunction(std::function<void()> function);

	//===========================================================================================
	//Description: Set close window function pointer
	//===========================================================================================
	void setCloseWindowFunction(std::function<void()> function);

	//===========================================================================================
	//Description: Checks for button presses and updates input boxes
	//===========================================================================================
	void update(const sf::Vector2f& mousePosition);

	//===========================================================================================
	//Description: Draws contents of this class
	//===========================================================================================
	void draw();

	//===========================================================================================
	//Description: Retuirns values of input buttons based on button index
	//===========================================================================================
	const int getPlayerInput(const int& buttonIndex) const;

	//===========================================================================================
	//Description: Resets button focus
	//===========================================================================================
	void resetButtonFocus();

};

#endif // !MAPOBJECTEDITORWINDOW_H

