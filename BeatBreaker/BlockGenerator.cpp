#include "BlockGenerator.h"

void BlockGenerator::randomNum()
{
	//mt19937 mt(time(nullptr));
	m_rng.seed(static_cast<unsigned int>(time(nullptr)));
}

void BlockGenerator::genMIDISection()
{
	// bpm
	// bps
	// difficulty level
}

void BlockGenerator::genRandomPattern(int t_sectionLength)
{
	// Clear the vector
	m_blockGrid.clear();

	// Get the number of columns with section length
	m_cols = t_sectionLength;

    m_blockGrid.resize(m_cols);
    for (int col = 0; col < m_cols; ++col)
    {
        m_blockGrid[col].resize(m_rows);
    }

    // Fill grid with random blocks
    for (int col = 0; col < m_cols; ++col)
    {
        for (int row = 0; row < m_rows; ++row)
        {
            // Setup the block
            m_blockGrid[col][row].setupBlockRectangle();

            // Set random color
            //m_blockGrid[col][row].m_currentColourState = getRandomColour();
            m_blockGrid[col][row].setColour(getRandomColour());

            // Position for the block
            float xPos = m_startX + (row * m_blockSize);
            float yPos = m_startY + (col * m_blockSize);

            m_blockGrid[col][row].setPosition(sf::Vector2f{ xPos , yPos});
        }
    }
}

std::vector<std::vector<Block>>& BlockGenerator::getBlockGrid()
{
    return m_blockGrid;
}

void BlockGenerator::renderBlocks(sf::RenderWindow& t_window)
{
    for (int col = 0; col < m_cols; ++col)
    {
        for (int row = 0; row < m_rows; ++row)
        {
            m_blockGrid[col][row].renderBlock(t_window);
        }
    }
}

void BlockGenerator::updateBlocks(float t_deltaTime)
{
    for (int col = 0; col < m_cols; ++col)
    {
        for (int row = 0; row < m_rows; ++row)
        {
            m_blockGrid[col][row].updateBlock(t_deltaTime);
        }
    }
}

void BlockGenerator::genRandomSection(int t_randType)
{
}

ColourStates BlockGenerator::getRandomColour()
{
    static bool seeded = false;
    if (!seeded) 
    {
        // Seed random number generator
        std::srand(static_cast<unsigned int>(std::time(nullptr)));  
        seeded = true;
    }

    // Generate a random number between 0 and 5
    int randomNum = std::rand() % 7;  // rand() % 6 gives a number between 0 and 5

    // Return the corresponding ColourState
    switch (randomNum)
    {
    case 0: return ColourStates::Blue;
    case 1: return ColourStates::Red;
    case 2: return ColourStates::Green;
    case 3: return ColourStates::Yellow;
    case 4: return ColourStates::Health;
    case 5: return ColourStates::Barrier;
    default: return ColourStates::Blue;  
    }
}

void BlockGenerator::genHealthSection()
{
}

void BlockGenerator::genFunnelTopSection()
{
}

void BlockGenerator::genFunnelBottomSection()
{
}
