#include "TrackVisualiser.h"

TrackVisualiser::TrackVisualiser(std::shared_ptr<const sf::Font> font) : m_font(font)
{

}

void TrackVisualiser::setupShapes()
{
    // Track Dividers
    for (int i = 0; i < lineCount; i++)
    {
        sf::RectangleShape line;
        line.setSize(sf::Vector2f(lineWidth, lineHeight));
        line.setFillColor(sf::Color::White);
        line.setPosition(sf::Vector2f{ visualiserOrigin.x + i * spacing, visualiserOrigin.y });

        trackLinesVertical.push_back(line);
    }

    // Horizontal Lines
    for (int i = 0; i < horizontalLineCount; i++)
    {
        sf::RectangleShape line;
        line.setSize({ visualiserWidth, horizontalLineHeight });
        line.setFillColor(sf::Color(50, 50, 150));
        line.setPosition(sf::Vector2f{ visualiserOrigin.x, visualiserOrigin.y + i * 110.0f });

        trackLinesHorizontal.push_back(line);
    }

    // Bottom UI
    for (int i = 0; i < 3; i++)
    {
        sf::RectangleShape borderLines;
        borderLines.setSize(sf::Vector2f(visualiserWidth, bottomBorderHeight));
        borderLines.setFillColor(sf::Color::White);
        borderLines.setPosition(sf::Vector2f{ visualiserOrigin.x, (visualiserOrigin.y + bottomBorderStartY) + i * 50.0f });

        bottomBorders.push_back(borderLines);
    }

    // Track Name Boxes
    for (int row = 0; row < 2; row++)  // 2 rows
    {

        for (int i = 0; i < lineCount; i++)
        {
            sf::RectangleShape box;
            box.setOrigin(sf::Vector2f{ boxWidth * 0.5f, 0.0f });
            box.setSize(sf::Vector2f{ boxWidth, boxHeight });
            box.setFillColor(sf::Color(50, 50, 50, 100));
            box.setOutlineThickness(1.0f);
            box.setOutlineColor(sf::Color::White);

            float boxX = visualiserOrigin.x + (i * spacing) + (spacing * 0.5f);

            float boxY = visualiserOrigin.y + visualiserYStart + boxYOffset + (row * (boxHeight + 20.f));

            box.setPosition(sf::Vector2f{ boxX , boxY });

            trackNameBox.push_back(box);


            // Text
            if (row == 0)
            {
                sf::Text text(*m_font);
                text.setString("Track " + std::to_string(i + 1));
                text.setCharacterSize(20U);
                text.setFillColor(sf::Color::White);
                text.setOutlineColor(sf::Color::Black);
                text.setOutlineThickness(2.0f);

                text.setPosition(sf::Vector2f{ 100.0f , 100.0f });

                m_trackNameTexts.push_back(text);
            }
        }
    }

    // Text
    //m_trackNameTexts.setPosition(sf::Vector2f{ SCREEN_CENTRE.x + 600.0f, SCREEN_CENTRE.y - 350.0f });
    //m_trackNameTexts.setFillColor(sf::Color::White);
    //m_trackNameTexts.setOutlineColor(sf::Color::Black);
    //m_trackNameTexts.setOutlineThickness(2.0f);
    //m_trackNameTexts.setCharacterSize(20U);
    //m_trackNameTexts.setString("???");


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

    // Track Boxes
    for (int i = 0; i < trackNameBox.size(); i++)
    {
        t_window.draw(trackNameBox[i]);
    }

    // Track Name Texts
    for (int i = 0; i < m_trackNameTexts.size(); i++)
    {
        t_window.draw(m_trackNameTexts[i]);
    }

    // TrackNumbers
}

void TrackVisualiser::update(float t_deltaTime)
{

}
