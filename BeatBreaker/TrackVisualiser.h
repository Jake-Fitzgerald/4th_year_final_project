#pragma once
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Globals.h"

class TrackVisualiser
{
public:
	TrackVisualiser(std::shared_ptr<const sf::Font> font);

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
	float horizontalLineHeight = 2.0f;
	float horizontalStartY = 100.0f;
	float horizontalSpacing = 100.0f;
	float horizontalXPos = paddingX;

	// Bottom UI
	float bottomBorderHeight = 10.0f;
	float bottomBorderStartY = 400.0f;

	// Track Name and Track Number boxes
	float boxWidth = 80.0f;
	float boxHeight = 30.0f;
	float boxYOffset = -85.0f;
	float boxRowSpace = 20.0f;


private:
	std::vector<sf::RectangleShape> trackShapes;

	// Track Dividers
	std::vector<sf::RectangleShape> trackLinesVertical;
	std::vector<sf::RectangleShape> trackLinesHorizontal;


	// Bottom UI
	std::vector<sf::RectangleShape> bottomBorders;
	std::vector<sf::RectangleShape> trackNameBox;
	std::vector<sf::RectangleShape> trackNumberBox;

	// Text
	std::shared_ptr<const sf::Font> m_font;
	std::vector<sf::Text> m_trackNameTexts;
	//std::vector<sf::Text> m_trackNumberTexts;

};
