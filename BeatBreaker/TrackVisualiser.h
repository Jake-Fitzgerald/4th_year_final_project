#pragma once
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

class TrackVisualiser
{
public:

	void setupShapes();

	void renderTrackVis(sf::RenderWindow& t_window);
	void update(float t_deltaTime);

private:
	std::vector<sf::RectangleShape> trackShapes;

	// UI
	std::vector<sf::RectangleShape> trackLinesVertical;
	std::vector<sf::RectangleShape> trackLinesHorizontal;

	sf::RectangleShape bottomBorder;

	std::vector<sf::RectangleShape> trackNameBox;
	std::vector<sf::RectangleShape> trackNumberBox;
};

