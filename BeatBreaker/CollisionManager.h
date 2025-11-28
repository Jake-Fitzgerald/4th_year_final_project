#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

/*
Notes:
Layer types
	Player
	- Player Hitbox
	- Player Hurtbox
	- Player BreakHitbox

	Blocks
	- Colours (Red, Green, Yellow, Blue)
	- Collectible (Health, Extra life)
	- Barrier

*/

class CollisionManager
{
public:
	void addCollidable(const sf::RectangleShape& t_shape, const std::string& t_layer);
	void removeCollidables(const sf::RectangleShape& t_shape);
	void clearCollidables();
	bool checkCollision(const sf::FloatRect& t_bounds, const std::string& t_layer);
	bool checkCollisionAllLayers(const sf::FloatRect& t_bounds, const std::string& t_layer);

	std::vector<sf::RectangleShape>& getCollidables(const std::string& t_layer);
	void setCollidables();

private:
	std::vector<sf::RectangleShape> m_collidablesVec;
	std::unordered_map<std::string, std::vector<sf::RectangleShape>> m_layeredCollidables;
};

