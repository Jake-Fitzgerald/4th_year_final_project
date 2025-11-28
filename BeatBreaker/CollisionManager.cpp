#include "CollisionManager.h"

void CollisionManager::addCollidable(const sf::RectangleShape& t_shape, const std::string& t_layer)
{
    //m_collidablesVec.push_back(t_shape);
    m_layeredCollidables[t_layer].push_back(t_shape);
}

void CollisionManager::removeCollidables(const sf::RectangleShape& t_shape)
{
    // Remove the shape from the vector if it exists
    //auto it = std::remove_if(m_collidablesVec.begin(), m_collidablesVec.end(),
    //[&t_shape](const sf::RectangleShape& shape) 
    //{
    //    return shape.getGlobalBounds() == t_shape.getGlobalBounds();
    //});

    //m_collidablesVec.erase(it, m_collidablesVec.end());
    for (auto& [layer, shapes] : m_layeredCollidables)
    {
        auto it = std::remove_if(shapes.begin(), shapes.end(),
            [&t_shape](const sf::RectangleShape& shape)
            {
                return shape.getGlobalBounds() == t_shape.getGlobalBounds();
            });

        shapes.erase(it, shapes.end());
    }
}

void CollisionManager::clearCollidables()
{
	// Remove every collider in the vector
    m_layeredCollidables.clear();
}


bool CollisionManager::checkCollision(const sf::FloatRect& t_bounds, const std::string& t_layer)
{
    // Check if the layer exists
    auto it = m_layeredCollidables.find(t_layer);
    if (it == m_layeredCollidables.end())
    {
        return false;
    }

    for (const auto& shape : it->second)
    {
        if (t_bounds.findIntersection(shape.getGlobalBounds()))
        {
            std::cerr << "[COLLISION] with layer: " << t_layer << std::endl;
            return true;
        }
    }
    return false;

    //for (const auto& shape : m_collidablesVec)
    //{
    //    if (t_bounds.findIntersection(shape.getGlobalBounds()))
    //    {
    //        std::cerr << "[COLLISION]" << std::endl;
    //        return true;
    //    }
    //}
    //return false;
}

bool CollisionManager::checkCollisionAllLayers(const sf::FloatRect& t_bounds, const std::string& t_layer)
{
    // Check collision against all layers
    for (const auto& [layer, shapes] : m_layeredCollidables)
    {
        for (const auto& shape : shapes)
        {
            if (t_bounds.findIntersection(shape.getGlobalBounds()))
            {
                std::cerr << "[COLLISION] with layer: " << layer << std::endl;
                return true;
            }
        }
    }
    return false;
}

std::vector<sf::RectangleShape>& CollisionManager::getCollidables(const std::string& t_layer)
{
    //return m_collidablesVec;
    return m_layeredCollidables[t_layer];
}
