#pragma once
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Globals.h"

class GridDisplay
{
public:
	void setupGrid();

	void renderGrid(sf::RenderWindow& t_window);


private:
	std::vector<sf::RectangleShape> m_lineShapesVertical;
	std::vector<sf::RectangleShape> m_lineShapesHorizontal;

	float m_gridSpaceSize = 100.0f;
	float m_lineThickness = 2.0f;
	sf::Color gridColour = sf::Color(200, 10, 10, 100);


};

