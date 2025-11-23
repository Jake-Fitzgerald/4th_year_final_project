#pragma once
#include <SFML//Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Globals.h"
#include <iostream>

enum Directions
{
	LEFT,
	RIGHT
};

class Player
{
public:
	Player();
	// Setup
	void setupPlayer();

	// Movement
	void moveLeft(float t_deltatime);
	void moveRight(float t_deltatime);

	// Speed
	void increaseSpeed(float t_deltatime);
	void decreaseSpeed(float t_deltatime);

	// Breaking

	void updatePlayer(float t_deltatime);
	void renderPlayer(sf::RenderWindow &t_window);

	// Setters and Getters
	void setSpawnPos(sf::Vector2f t_position);
	void getCurrentHP();
	void setCurrentHP(int t_hpAmount);
	void getCurrentSpeed();
	void setCurrentSpeed(int t_speedAmount);
	

private:
	// Health
	int m_currentHP;
	int m_maxHP = 5;
	// Speed
	float m_currentMoveSpeed = 200.0f;
	float m_maxMoveSpeed = 200.0f;
	float m_currentFallSpeed;
	float m_maxFallSpeed;

	// Directions
	Directions m_currentDirection = Directions::LEFT;

	sf::Vector2f m_currentPos;

	// Colliders
	sf::RectangleShape m_hitbox;
	sf::Vector2f m_hitboxSize{ 80.0f, 80.0f };
	sf::RectangleShape m_hurtbox;
	sf::Vector2f m_hurtboxSize{ 80.0f, 10.0f };
	sf::RectangleShape m_breakHitbox;
	sf::Vector2f m_breakHitboxSize{ 50.0f, 50.0f };
};

