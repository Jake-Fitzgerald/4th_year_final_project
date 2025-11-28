#include "Block.h"

Block::Block()
{
}

void Block::renderBlock(sf::RenderWindow& t_window)
{
	// Render collision
	t_window.draw(m_colliderShape);
	// Render hitbox
	t_window.draw(m_hitboxShape);
}

void Block::updateBlock(float t_deltaTime)
{
	// Place hitbox shape at the bottom of the collider shape 
	// (total y size is 50 and the hitbox is 10 so 40 is how far we move down)
	m_hitboxPos = sf::Vector2f{ m_colliderShape.getPosition().x, m_colliderShape.getPosition().y - 40.0f };

}

void Block::setupBlockRectangle()
{
	// Collider
	m_colliderShape.setFillColor(sf::Color::Magenta); // Debug colour
	m_colliderShape.setOutlineColor(sf::Color::Black);
	m_colliderShape.setOutlineThickness(1.f);
	m_colliderShape.setSize(m_colliderSize);

	// Hitbox
	m_hitboxShape.setFillColor(sf::Color::White); // Debug colour
	m_hitboxShape.setOutlineColor(sf::Color::Black);
	m_hitboxShape.setOutlineThickness(1.f);
	m_hitboxShape.setSize(m_colliderSize);
	m_hitboxShape.setPosition(m_hitboxPos);
}

void Block::setPosition(sf::Vector2f t_position)
{
	m_currentPosition = t_position;
	m_colliderShape.setPosition(m_currentPosition);
}

void Block::setColour(ColourStates t_colour)
{
	m_currentColourState = t_colour;
	m_colliderShape.setFillColor(colours[static_cast<int>(t_colour)]);
}

sf::Vector2f Block::getPosition() const
{
	return m_currentPosition;
}

sf::RectangleShape& Block::getColliderShape()
{
	return m_colliderShape;
}

sf::RectangleShape& Block::getHitboxShape()
{
	return m_hitboxShape;
}
