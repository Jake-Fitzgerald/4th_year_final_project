#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Notes:
// 4 colours: BLUE, PINK, GREEN, YELLOW
// 2 types: coloured (1 hit), barriers (3 hits + health drain)
// Use a damage amount to calculate when a block will break (1 for coloured, 3 for barrier)
// States: 
	// Placed, 
	// Breaking (timer for removing collision, play dissapear anim, 
	// Broken (waiting for timeline collision),
	// Falling

enum BlockStates
{
	Placed,
	Breaking,
	Broken,
	Falling
};

enum ColourStates
{
	Blue,
	Red,
	Green,
	Yellow,
	Health
};

class Block
{
public:
	// Constructor
	Block();
	
	void renderBlock(sf::RenderWindow &t_window);

	void updateBlock(float t_deltaTime);

	void setupBlockRectangle();

	BlockStates m_currentBlockState = BlockStates::Placed;
	ColourStates m_currentColourState = ColourStates::Blue;

private:
	// Overall collision shape
	sf::RectangleShape m_colliderShape;
	sf::Vector2f m_colliderSize = { 50.0f, 50.0f };
	// Damage hitbox
	sf::RectangleShape m_hitboxShape;
	sf::Vector2f m_hitboxSize = { 50.0f, 10.0f };
	sf::Vector2f m_hitboxPos = { 0.0f, 0.0f };

	// Global position in the play area (not grid)
	sf::Vector2f m_currentPosition;
	
	// Block colours (ref to fill in collider colours)
	sf::Color BLUE = sf::Color::Blue;
	sf::Color PINK = sf::Color::Magenta;
	sf::Color GREEN = sf::Color::Green;
	sf::Color YELLOW = sf::Color::Yellow;
	sf::Color HEALTH = sf::Color(100, 50, 200);
	// Colour vector
	std::vector<sf::Color> colours = { BLUE, PINK, GREEN, YELLOW, HEALTH };
	
};

