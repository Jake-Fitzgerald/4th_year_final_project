#pragma once
#include <SFML//Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Globals.h"
#include <iostream>
#include "CollisionManager.h"

enum MovingDir
{
	LEFT_MOVE,
	RIGHT_MOVE
};

enum BreakDir
{
	LEFT,
	RIGHT,
	UP,
	DOWN
};

enum States
{
	Idle,
	Walk,
	Fall,
	Break,
	Jump,
	Death
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
	void revertPosition();


	// Pointing
	void pointUp();
	void pointDown();

	// Collision
	sf::FloatRect getHitbox() const;
	sf::FloatRect getHurtbox() const;
	sf::FloatRect getBreakHitbox() const;
	bool checkCollisionWithShapes(const std::vector<sf::RectangleShape>& t_shapes);
	

	// Speed
	void increaseSpeed(float t_deltatime);
	void decreaseSpeed(float t_deltatime);

	// Breaking
	bool breaking(const sf::RectangleShape& t_block);

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
	MovingDir m_currentDirection = MovingDir::LEFT_MOVE;
	BreakDir m_currentBreakDirection = BreakDir::LEFT;

	sf::Vector2f m_currentPos;

	bool b_isGrounded;

	// Colliders
	sf::RectangleShape m_hitbox;
	sf::Vector2f m_hitboxSize{ 80.0f, 80.0f };
	sf::RectangleShape m_hurtbox;
	sf::Vector2f m_hurtboxSize{ 80.0f, 10.0f };
	sf::RectangleShape m_breakHitbox;
	sf::Vector2f m_breakHitboxSize{ 50.0f, 50.0f };
	sf::RectangleShape m_groundHitbox;
	sf::Vector2f m_groundHitboxSize{ 80.0f, 10.0f };

	sf::Vector2f m_previousPos;
};

