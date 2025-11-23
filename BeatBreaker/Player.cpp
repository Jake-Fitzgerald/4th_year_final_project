#include "Player.h"

Player::Player()
{
}

void Player::setupPlayer()
{
	// Hitbox
	m_hitbox.setSize(m_hitboxSize);
	m_hitbox.setOrigin(m_hitboxSize / 2.0f);
	m_hitbox.setFillColor(sf::Color::Green);
	// Hurtbox
	m_hurtbox.setSize(m_hurtboxSize);
	m_hurtbox.setOrigin(m_hurtboxSize / 2.0f);
	m_hurtbox.setFillColor(sf::Color::Yellow);
	// Break Hitbox
	m_breakHitbox.setSize(m_breakHitboxSize);
	m_breakHitbox.setOrigin(m_breakHitboxSize / 2.0f);
	m_breakHitbox.setFillColor(sf::Color::Magenta);
}

void Player::moveLeft(float t_deltatime)
{
	m_hitbox.move(sf::Vector2f{ -m_currentMoveSpeed * t_deltatime, 0.f });
	m_currentDirection = Directions::LEFT;
}

void Player::moveRight(float t_deltatime)
{
	m_hitbox.move(sf::Vector2f{ +m_currentMoveSpeed * t_deltatime, 0.f });
	m_currentDirection = Directions::RIGHT;
}

void Player::updatePlayer(float t_deltatime)
{

}

void Player::renderPlayer(sf::RenderWindow& t_window)
{
	t_window.draw(m_hitbox);
}

void Player::setSpawnPos(sf::Vector2f t_position)
{
	m_currentPos = t_position;
	m_hitbox.setPosition(m_currentPos);
}
