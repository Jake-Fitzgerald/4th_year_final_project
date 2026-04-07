#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Globals.h"
#include <iostream>
#include <string>


class InputField
{
public:
	InputField(std::shared_ptr<const sf::Font> font, sf::Vector2f t_pos, sf::Vector2f t_size, int t_charSize);

	void setupInputField();

	void handleEvent(sf::Event& t_event);
	bool checkIfAreaClicked(sf::Vector2f t_mousePos, sf::Vector2f t_topLeft, sf::Vector2f t_size);

	void update(float t_deltaTime);
	void updateBox();
	void render(sf::RenderWindow& t_window);

	void setPos(sf::Vector2f t_pos);
	void setIsActive(bool t_bool);
	void setMaxLength(int t_maxLength);
	void setPlaceholderString(std::string t_placeholderString);
	void clearString();

	std::string getString();
	bool getIsActive();

private:
	std::string m_storedString = "";
	std::string m_placeholderString = "Enter text...";

	sf::Text m_inputText;
	sf::Text m_placeholderText;

	int m_maxLength = 32;
	bool b_isActive = false;

	sf::RectangleShape m_textBoxFrame;
	sf::RectangleShape m_cursorShape;

	sf::Color c_inactiveColour = sf::Color(100, 80, 100, 240);
	sf::Color c_activeColour = sf::Color(0, 200, 20, 240);
	sf::Color c_outlineColour = sf::Color(0, 0, 0, 150);
	sf::Color c_textColour = sf::Color::White;
	sf::Color c_textPlaceholderColour = sf::Color(100, 100, 100, 200);
	sf::Color c_textErrorColour = sf::Color::Red;

	// Unicode
	int u_backspace = 8;
	int u_letterStart = 65;
	int u_letterEnd = 90;
};

