#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include "Globals.h"

struct MenuButtonData
{
	std::string m_label = " ";
	sf::Vector2f m_position;
	sf::Color m_colour;
};

struct MenuButton
{
	sf::RectangleShape m_buttonShape;

	sf::Text m_buttonText;
	std::string m_label = " ";

	sf::Vector2f m_position;
	sf::Color m_colour;

	MenuButton(std::shared_ptr<const sf::Font> font)
		: m_buttonText(*font)
	{

	}
};

class MainMenu
{
public:
	// Constructor
	MainMenu(std::shared_ptr<const sf::Font> t_font);
	
	void setupMainMenu();


	void render(sf::RenderWindow& t_window);

	// Selection
	void MoveUp();
	void MoveDown();
	// Returns the button we pressed as a number
	int MainMenuPressed();

	std::string mouseClick(sf::Vector2f t_mousePos);
	bool checkIfAreaClicked(sf::Vector2f t_mousePos, sf::Vector2f t_topLeft, sf::Vector2f t_size);

private:
	int m_menuSelection = -1;

	std::vector<MenuButton> m_buttons;
	std::vector<MenuButtonData> m_buttonData;

	// Have an array later, but for now just have one button
	sf::RectangleShape m_buttonShape;

	// Text
	std::shared_ptr<const sf::Font> m_font;
	sf::Text m_titleText;

	sf::Vector2f m_topLeftStart;
	float m_buttonSpacing = 100.0f;
	sf::Vector2f m_buttonSize = { 300.0f, 50.0f };
};
