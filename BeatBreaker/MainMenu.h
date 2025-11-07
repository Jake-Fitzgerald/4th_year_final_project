#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>



class MainMenu
{
public:
	// Constructor
	MainMenu(sf::Font& t_font);
	// Destructor
	//~MainMenu();

	void render(sf::RenderWindow& t_window);

	// Selection
	void MoveUp();
	void MoveDown();
	// Returns the button we pressed as a number
	int MainMenuPressed();

	// Reatangle Buttons
	void setupRectangles();


private:
	int m_menuSelection = -1;

	// Have an array later, but for now just have one button
	sf::RectangleShape m_buttonShape;

	// Text
	sf::Text m_menuText;
};
