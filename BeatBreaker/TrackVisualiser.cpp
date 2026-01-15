#include "TrackVisualiser.h"

void TrackVisualiser::setupShapes()
{
    // Track Dividers
    for (int i = 0; i < lineCount; i++)
    {
        sf::RectangleShape line;
        line.setSize(sf::Vector2f(lineWidth, lineHeight));
        line.setFillColor(sf::Color::White);
        line.setPosition(sf::Vector2f{ startX + i * spacing, yPos });

        trackLinesVertical.push_back(line);
    }

    // Horizontal Lines
    for (int i = 0; i < horizontalLineCount; i++)
    {
        sf::RectangleShape line;
        line.setSize({ horizontalLineWidth, horizontalLineHeight });
        line.setFillColor(sf::Color(50, 50, 50));
        line.setPosition(sf::Vector2f{ horizontalXPos, horizontalStartY + i * horizontalSpacing });

        trackLinesHorizontal.push_back(line);
    }

    // Bottom UI
   // bottomBorder.setFillColor(sf::Color::White);
    //bottomBorder.setSize(sf::Vector2f(SCREEN_WIDTH, bottomBorderHeight));
    //bottomBorder.setPosition(sf::Vector2f{0.0f, lineHeight });
    for (int i = 0; i < 3; i++)
    {
        sf::RectangleShape borderLines;
        borderLines.setSize(sf::Vector2f(visualiserWidth, bottomBorderHeight));
        borderLines.setFillColor(sf::Color::White);
        borderLines.setPosition(sf::Vector2f{ visualiserPaddingX, visualiserYStart + i * 50.0f });

        bottomBorders.push_back(borderLines);
    }

    // Track Name Boxes
    for (int i = 0; i < 11; i++)
    {
        sf::RectangleShape box;
        box.setOrigin(sf::Vector2f{ boxWidth * 0.5f, 0.f });
        box.setSize(sf::Vector2f{ boxWidth, boxHeight });
        box.setFillColor(sf::Color(50, 50, 50, 100));
        box.setOutlineThickness(1.0f);
        box.setOutlineColor(sf::Color::White);

        float boxX = startX + i * spacing + lineWidth * 0.5f;

        float boxY = visualiserYStart + 10.0f;

        box.setPosition(sf::Vector2f{ boxX , boxY });

        trackNameBox.push_back(box);
    }
}

void TrackVisualiser::renderTrackVis(sf::RenderWindow& t_window)
{
    // Track Dividers
    for (int i = 0; i < trackLinesVertical.size(); i++)
    {
        t_window.draw(trackLinesVertical[i]);
    }

    // Horizontal Lines
    for (int i = 0; i < trackLinesHorizontal.size(); i++)
    {
        t_window.draw(trackLinesHorizontal[i]);
    }

    // Bottom UI
    // Bottom Borders
    for (int i = 0; i < bottomBorders.size(); i++)
    {
        t_window.draw(bottomBorders[i]);
    }

    // Track Names
    for (int i = 0; i < trackNameBox.size(); i++)
    {
        t_window.draw(trackNameBox[i]);
    }

    // TrackNumbers
}

void TrackVisualiser::update(float t_deltaTime)
{

}
