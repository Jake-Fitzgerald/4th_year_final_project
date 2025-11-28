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
	// Ground Hitbox
	m_groundHitbox.setSize(m_groundHitboxSize);
	m_groundHitbox.setOrigin(m_groundHitboxSize / 2.0f);
	m_groundHitbox.setFillColor(sf::Color::Blue);
}

void Player::moveLeft(float t_deltatime)
{
	m_previousPos = m_currentPos;
	m_currentPos.x -= m_currentMoveSpeed * t_deltatime;
	m_currentDirection = MovingDir::LEFT_MOVE;
	m_currentBreakDirection = BreakDir::LEFT;
}

void Player::moveRight(float t_deltatime)
{
	m_previousPos = m_currentPos;
	m_currentPos.x += m_currentMoveSpeed * t_deltatime;
	m_currentDirection = MovingDir::RIGHT_MOVE;
	m_currentBreakDirection = BreakDir::RIGHT;
}

void Player::revertPosition()
{
	m_currentPos = m_previousPos;
}

void Player::pointUp()
{
	m_currentBreakDirection = BreakDir::UP;
	//m_breakHitbox.setPosition(sf::Vector2f{ m_currentPos.x , m_currentPos.y - (m_hitboxSize.x / 2.0f) });
}

void Player::pointDown()
{
	m_currentBreakDirection = BreakDir::DOWN;
	//m_breakHitbox.setPosition(sf::Vector2f{ m_currentPos.x , m_currentPos.y - (m_hitboxSize.x / 2.0f) });
}

sf::FloatRect Player::getHitbox() const
{
	return m_hitbox.getGlobalBounds();
}

sf::FloatRect Player::getHurtbox() const
{
	return m_hurtbox.getGlobalBounds();
}

sf::FloatRect Player::getBreakHitbox() const
{
	return m_breakHitbox.getGlobalBounds();
}

sf::FloatRect Player::getGroundHitbox() const
{
	return m_groundHitbox.getGlobalBounds();
}

bool Player::checkCollisionWithShapes(const std::vector<sf::RectangleShape>& t_shapes)
{
	for (const auto& shape : t_shapes)
	{
		if (m_hitbox.getGlobalBounds().findIntersection(shape.getGlobalBounds()))
		{
			return true;
		}
	}
	return false; 
}

bool Player::breaking(const sf::RectangleShape& t_block)
{
	if (m_breakHitbox.getGlobalBounds().findIntersection(t_block.getGlobalBounds()))
	{
		std::cerr << "BREAKING!" << std::endl;
		return true; 
	}
	return false; 
}

void Player::updatePlayer(float t_deltatime)
{
	// Update all hitbox positions based on m_currentPos
	m_hitbox.setPosition(m_currentPos);

	// Position hurtbox at the top of the player 
	m_hurtbox.setPosition(sf::Vector2f{ m_currentPos.x, m_currentPos.y - (m_hitboxSize.y / 2.0f) });

	// Position ground hitbox at the bottom of the player 
	m_groundHitbox.setPosition(sf::Vector2f{ m_currentPos.x, m_currentPos.y + 40.0f });

	switch (m_currentBreakDirection)
	{
	case BreakDir::UP:
		m_breakHitbox.setPosition(sf::Vector2f{ m_currentPos.x, m_currentPos.y - (m_hitboxSize.y / 2.0f) });
		break;
	case BreakDir::DOWN:
		m_breakHitbox.setPosition(sf::Vector2f{ m_currentPos.x, m_currentPos.y + (m_hitboxSize.y / 2.0f) });
		break;
	case BreakDir::LEFT:
		m_breakHitbox.setPosition(sf::Vector2f{ m_currentPos.x - (m_hitboxSize.x / 2.0f), m_currentPos.y });
		break;
	case BreakDir::RIGHT:
		m_breakHitbox.setPosition(sf::Vector2f{ m_currentPos.x + (m_hitboxSize.x / 2.0f), m_currentPos.y });
		break;
	}
}

void Player::renderPlayer(sf::RenderWindow& t_window)
{
	t_window.draw(m_hitbox);
	t_window.draw(m_breakHitbox); 
	t_window.draw(m_hurtbox);
	t_window.draw(m_groundHitbox);
}

void Player::setSpawnPos(sf::Vector2f t_position)
{
	m_currentPos = t_position;
	m_hitbox.setPosition(m_currentPos);
}
