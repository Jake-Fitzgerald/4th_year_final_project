#pragma once
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Globals.h"

class TrackVisualiser
{
public:

	void setupShapes();

	void renderTrackVis(sf::RenderWindow& t_window);
	void update(float t_deltaTime);

	// Padding
	sf::Vector2f visualiserOrigin{ paddingX, paddingY };

	// Track Visualiser Sizes
	float visualiserWidth = TRACK_SIZE_X;
	float visualiserPaddingX = paddingX;
	float visualiserYStart = 500.0f;

	// Track Dividers
	int lineCount = 12;
	float lineWidth = 2.0f;
	float lineHeight = 500.0f;
	float spacing = 100.0f;


	// Horizontal lines
	int horizontalLineCount = 4;
	float horizontalLineHeight = 2.f;
	float horizontalStartY = 100.f;
	float horizontalSpacing = 100.f;
	float horizontalXPos = paddingX;

	// Bottom UI
	float bottomBorderHeight = 10.0f;
	float bottomBorderStartY = 400.0f;

	// Track Name and Track Number boxes
	float boxWidth = 80.f;
	float boxHeight = 40.f;
	float boxYOffset = 20.f;


private:
	std::vector<sf::RectangleShape> trackShapes;

	// Track Dividers
	std::vector<sf::RectangleShape> trackLinesVertical;
	std::vector<sf::RectangleShape> trackLinesHorizontal;


	// Bottom UI
	std::vector<sf::RectangleShape> bottomBorders;
	std::vector<sf::RectangleShape> trackNameBox;
	std::vector<sf::RectangleShape> trackNumberBox;

};

