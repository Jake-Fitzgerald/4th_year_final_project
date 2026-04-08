#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include <iostream>
#include <string>

class BG_Scroll
{
public:
	BG_Scroll(/*std::string t_texturePath*/);

	void update(float t_deltaTime);
	void render(sf::RenderWindow& t_window);

private:
	sf::Texture m_bg_tex_1;
	sf::Sprite m_bg_sprite_1;
	sf::Texture m_bg_tex_2;
	sf::Sprite m_bg_sprite_2;
	sf::Texture m_bg_tex_3;
	sf::Sprite m_bg_sprite_3;
	sf::Texture m_bg_tex_4;
	sf::Sprite m_bg_sprite_4;
	sf::Texture m_bg_tex_5;
	sf::Sprite m_bg_sprite_5;

	sf::IntRect m_intRect_1;
	sf::IntRect m_intRect_2;
	sf::IntRect m_intRect_3;
	sf::IntRect m_intRect_4;
	sf::IntRect m_intRect_5;
	sf::Vector2f m_scrollSpeed_slowest{ 0.0f, -15.0f };
	sf::Vector2f m_scrollSpeed_slower{ 0.0f, -30.0f };
	sf::Vector2f m_scrollSpeed_slow{ 0.0f, -40.0f };
	sf::Vector2f m_scrollSpeed_medium{ 0.0f, -60.0f };
	sf::Vector2f m_scrollSpeed_fast{ 0.0f, -70.0f };
	sf::Vector2f m_rectOffset_1{ 0.0f,0.0f };
	sf::Vector2f m_rectOffset_2{ 0.0f,0.0f };
	sf::Vector2f m_rectOffset_3{ 0.0f,0.0f };
	sf::Vector2f m_rectOffset_4{ 0.0f,0.0f };
	sf::Vector2f m_rectOffset_5{ 0.0f,0.0f };
};

