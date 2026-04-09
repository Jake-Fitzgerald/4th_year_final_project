#pragma once
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Globals.h"

class GridDisplay
{
public:
	GridDisplay();

	void setupGrid();
	void setupSprites();

	void renderGrid(sf::RenderWindow& t_window);

	void toggleGridVisible();

private:
	std::vector<sf::RectangleShape> m_lineShapesVertical;
	std::vector<sf::RectangleShape> m_lineShapesHorizontal;

	float m_gridSpaceSize = 100.0f;
	float m_lineThickness = 2.0f;
	sf::Color gridColour = sf::Color(200, 10, 10, 100);

	bool b_isGridVisible = false;


	// Vignette
	sf::Texture m_vignetteTexture;
	sf::Sprite m_vignetteSprite;
};

