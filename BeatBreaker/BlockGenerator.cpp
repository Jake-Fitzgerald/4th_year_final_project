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

    //////////////////////
    int barrierChance = barrierCalculate();

    // Generate random numb 0-99
    int randBarrierPercent = std::rand() % 100;
    
    // Check if we should spawn a barrier
    if (randBarrierPercent < barrierChance)
    {
        return ColourStates::Barrier;
    }
    //////////////////////
    int healthChance = healthCalculate();

    // Generate random numb 0-99
    int randHealthPercent = std::rand() % 100;

    // Check if we should spawn a barrier
    if (randHealthPercent < healthChance)
    {
        return ColourStates::Health;
    }
    //////////////////////

    // Generate a random number between 0 and 5
    int randomNum = std::rand() % 7;  

    // Return the corresponding ColourState
    switch (randomNum)
    {
    case 0: return ColourStates::Blue;
    case 1: return ColourStates::Red;
    case 2: return ColourStates::Green;
    case 3: return ColourStates::Yellow;
    //case 4: return ColourStates::Health;
    //case 5: return ColourStates::Barrier;
    default: return ColourStates::Blue;  
    }
}

void BlockGenerator::setDifficulty(const std::string& t_difficulty)
{
    m_currentDifficulty = t_difficulty;
}

int BlockGenerator::barrierCalculate()
{
    // Adjust barrier chance
    int barrierChance = 0;

    if (m_currentDifficulty == "EASY")
    {
        barrierChance = 5;
        //std::cerr << "[GEN] Barrier chance is EASY" << std::endl;
    }
    else if (m_currentDifficulty == "MEDIUM")
    {
        barrierChance = 10;
    }
    else if (m_currentDifficulty == "HARD")
    {
        barrierChance = 15;
    }

    return barrierChance;
}

int BlockGenerator::healthCalculate()
{
    // Adjust barrier chance
    int healthChance = 0;

    if (m_currentDifficulty == "EASY")
    {
        healthChance = 3;
    }
    else if (m_currentDifficulty == "MEDIUM")
    {
        healthChance = 2;
    }
    else if (m_currentDifficulty == "HARD")
    {
        healthChance = 1;
    }

    return healthChance;
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
