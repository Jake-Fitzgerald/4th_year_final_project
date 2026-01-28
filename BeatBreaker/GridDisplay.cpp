#include "GridDisplay.h"

void GridDisplay::setupGrid()
{
    int columns = SCREEN_WIDTH / m_gridSpaceSize;
    int rows = SCREEN_HEIGHT / m_gridSpaceSize;

    float gridWidth = columns * m_gridSpaceSize;
    float gridHeight = rows * m_gridSpaceSize;

    // Padding
    float startX = (SCREEN_WIDTH - gridWidth) / 2.0f;  //40
    float startY = (SCREEN_HEIGHT - gridHeight) / 2.0f; //10



    // Vertical lines
    for (int i = 0; i <= columns; ++i)
    {
        sf::RectangleShape line;
        line.setSize({ m_lineThickness, gridHeight });
        line.setFillColor(gridColour);
        line.setPosition(sf::Vector2f{ startX + i * m_gridSpaceSize, startY });
        m_lineShapesVertical.push_back(line);
    }

    // Horizontal lines
    for (int i = 0; i <= rows; ++i)
    {
        sf::RectangleShape line;
        line.setSize({ gridWidth, m_lineThickness });
        line.setFillColor(gridColour);
        line.setPosition(sf::Vector2f{ startX, startY + i * m_gridSpaceSize });
        m_lineShapesHorizontal.push_back(line);
    }

    b_isGridVisible = true;
}

void GridDisplay::renderGrid(sf::RenderWindow& t_window)
{
    if (b_isGridVisible == true)
    {
        for (auto& line : m_lineShapesVertical)
        {
            t_window.draw(line);
        }

        for (auto& line : m_lineShapesHorizontal)
        {
            t_window.draw(line);
        }
    } 
}

void GridDisplay::toggleGridVisible()
{
    if (b_isGridVisible == true)
    {
        b_isGridVisible = false;
    }
    else
    {
        b_isGridVisible = true;
    }
}
