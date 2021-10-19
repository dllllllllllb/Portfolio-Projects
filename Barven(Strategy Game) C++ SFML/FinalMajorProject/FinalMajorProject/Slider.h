//Author: Maciej Dowbor
//Last Accessed: 17/06/2021

#ifndef SLIDER_H
#define SLIDER_H

#include <SFML/Window/Mouse.hpp>
#include <functional>
#include <iostream>

#include "SliderHandle.h"
#include "UIElement.h"
#include "GlobalVariables.h"

//===========================================================================================
//Description: Simple slider that returns a value between 0 - 1 based on handle position
//===========================================================================================
class Slider : virtual public UIElement
{
private:
	bool m_isHorizontal;
	bool m_isActive;
	float m_value;
	float m_initialHandlePosX;
	float m_initialHandlePosY;
	float m_initialBarPosX;
	float m_initialBarPosY;
	float m_barWidth;
	float m_barHeight;
	int m_barTextureRectWidth;
	int m_barTextureRectHeight;

	sf::Sprite m_bar;
	SliderHandle m_handle;

	sf::Mouse m_mouse;

	std::function<void()> m_functionToCallAfterResize;

	//===========================================================================================
	//Description: Resize elements of this class
	//===========================================================================================
	void resizeSliderElements(const int& width, const int& height);

public:
	//===========================================================================================
	//Description: Class constructor, isSliderHorizontal determines if the sliter is horizontal 
	//			   or vertical
	//===========================================================================================
	Slider(sf::RenderWindow& rWindow, Textures& rTextures, const bool isSliderHorizontal);

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~Slider();

	//===========================================================================================
	//Description: Sets up slider position and dimentions
	//===========================================================================================
	void setUpSlider(const int& positionX, const int& positionY, const int& width, const int& height );

	//===========================================================================================
	//Description: Resets slider values to defaults
	//===========================================================================================
	void resetSlider();

	//===========================================================================================
	//Description: Repositions contents of this class
	//===========================================================================================
	void reposition(const float& positionX, const float& positionY);

	//===========================================================================================
	//Description: Updates handle position and return value
	//===========================================================================================
	bool update(const sf::Vector2f& mousePosition);

	//===========================================================================================
	//Description: Sets a function to call after the handle is moved
	//===========================================================================================
	void setFunctionToCallAfterResize(std::function<void()> function);

	//===========================================================================================
	//Description: Changes slider dimentions
	//===========================================================================================
	void resizeSlider(const int& positionX, const int& positionY, const int& width, const int& height);

	//===========================================================================================
	//Description: Returns slider value
	//===========================================================================================
	const float& getSliderValue() const;

	//===========================================================================================
	//Description: Returns active state
	//===========================================================================================
	const bool getActiveState() const;

	//===========================================================================================
	//Description: Draws contents of this class
	//===========================================================================================
	void draw();

};
#endif // !SLIDER_H