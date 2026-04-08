#include "BG_Scroll.h"

BG_Scroll::BG_Scroll(/*std::string t_texturePath*/) 
	: m_bg_tex_1(),
	  m_bg_sprite_1(m_bg_tex_1),
	  m_bg_tex_2(),
	  m_bg_sprite_2(m_bg_tex_2),
	  m_bg_tex_3(),
	  m_bg_sprite_3(m_bg_tex_3),
	  m_bg_tex_4(),
	  m_bg_sprite_4(m_bg_tex_4),
	  m_bg_tex_5(),
	  m_bg_sprite_5(m_bg_tex_5)
{
	// Texture 1
	if (!m_bg_tex_1.loadFromFile("ASSETS\\IMAGES\\Backgrounds\\MainMenu_BG_Scroll_1.png"))
	{
		std::cout << "problem loading bg scroll 1" << std::endl;
	}
	m_bg_tex_1.setRepeated(true);
	m_intRect_1 = sf::IntRect({ 0,0 }, sf::Vector2i(m_bg_tex_1.getSize()));

	m_bg_sprite_1.setTexture(m_bg_tex_1, true);
	m_bg_sprite_1.setPosition(sf::Vector2f{ 0.0f, 0.0f });

	// Texture 2
	if (!m_bg_tex_2.loadFromFile("ASSETS\\IMAGES\\Backgrounds\\MainMenu_BG_Scroll_2.png"))
	{
		std::cout << "problem loading bg scroll 2" << std::endl;
	}
	m_bg_tex_2.setRepeated(true);
	m_intRect_2 = sf::IntRect({ 0,0 }, sf::Vector2i(m_bg_tex_2.getSize()));

	m_bg_sprite_2.setTexture(m_bg_tex_2, true);
	m_bg_sprite_2.setPosition(sf::Vector2f{ 0.0f, 0.0f });

	// Texture 3
	if (!m_bg_tex_3.loadFromFile("ASSETS\\IMAGES\\Backgrounds\\MainMenu_BG_Scroll_3.png"))
	{
		std::cout << "problem loading bg scroll 3" << std::endl;
	}
	m_bg_tex_3.setRepeated(true);
	m_intRect_3 = sf::IntRect({ 0,0 }, sf::Vector2i(m_bg_tex_3.getSize()));

	m_bg_sprite_3.setTexture(m_bg_tex_3, true);
	m_bg_sprite_3.setPosition(sf::Vector2f{ 0.0f, 0.0f });

	// Texture 4
	if (!m_bg_tex_4.loadFromFile("ASSETS\\IMAGES\\Backgrounds\\MainMenu_BG_Scroll_4.png"))
	{
		std::cout << "problem loading bg scroll 4" << std::endl;
	}
	m_bg_tex_4.setRepeated(true);
	m_intRect_4 = sf::IntRect({ 0,0 }, sf::Vector2i(m_bg_tex_4.getSize()));

	m_bg_sprite_4.setTexture(m_bg_tex_4, true);
	m_bg_sprite_4.setPosition(sf::Vector2f{ 0.0f, 0.0f });

	// Texture 5
	if (!m_bg_tex_5.loadFromFile("ASSETS\\IMAGES\\Backgrounds\\MainMenu_BG_Scroll_5.png"))
	{
		std::cout << "problem loading bg scroll 5" << std::endl;
	}
	m_bg_tex_5.setRepeated(true);
	m_intRect_5 = sf::IntRect({ 0,0 }, sf::Vector2i(m_bg_tex_5.getSize()));

	m_bg_sprite_5.setTexture(m_bg_tex_5, true);
	m_bg_sprite_5.setPosition(sf::Vector2f{ 0.0f, 0.0f });
}

void BG_Scroll::update(float t_deltaTime)
{
	m_rectOffset_1.y += m_scrollSpeed_slow.y * t_deltaTime;
	m_intRect_1.position.y = static_cast<int>(m_rectOffset_1.y);
	m_bg_sprite_1.setTextureRect(m_intRect_1);

	m_rectOffset_2.y += m_scrollSpeed_fast.y * t_deltaTime;
	m_intRect_2.position.y = static_cast<int>(m_rectOffset_2.y);
	m_bg_sprite_2.setTextureRect(m_intRect_2);

	m_rectOffset_3.y += m_scrollSpeed_medium.y * t_deltaTime;
	m_intRect_3.position.y = static_cast<int>(m_rectOffset_3.y);
	m_bg_sprite_3.setTextureRect(m_intRect_3);

	m_rectOffset_4.y += m_scrollSpeed_slower.y * t_deltaTime;
	m_intRect_4.position.y = static_cast<int>(m_rectOffset_4.y);
	m_bg_sprite_4.setTextureRect(m_intRect_4);

	m_rectOffset_5.y += m_scrollSpeed_slowest.y * t_deltaTime;
	m_intRect_5.position.y = static_cast<int>(m_rectOffset_5.y);
	m_bg_sprite_5.setTextureRect(m_intRect_5);
}

void BG_Scroll::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_bg_sprite_1);
	t_window.draw(m_bg_sprite_2);
	t_window.draw(m_bg_sprite_3);
	t_window.draw(m_bg_sprite_4);
	t_window.draw(m_bg_sprite_5);
}
