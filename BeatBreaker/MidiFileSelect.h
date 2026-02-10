#pragma once
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Globals.h"

class MidiFileSelect
{
public:
	MidiFileSelect(std::shared_ptr<const sf::Font> font);

	void setupButtons();
	void render(sf::RenderWindow& t_window);


private:
	std::vector<sf::RectangleShape> m_buttonShapes;

	std::shared_ptr<const sf::Font> m_font;
	std::vector<sf::Text> m_buttonTexts;
};

