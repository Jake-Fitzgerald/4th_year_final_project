#include "MainMenu.h"

MainMenu::MainMenu(sf::Font& t_font) : m_menuText(t_font, sf::String("Play"), 40U)
{
	// Setup text
	m_menuText.setFillColor(sf::Color::White);
	m_menuText.setPosition(sf::Vector2f{ 100.0f, 100.0f });

	setupRectangles();
}

void MainMenu::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_buttonShape);
	t_window.draw(m_menuText);
}

void MainMenu::MoveUp()
{
}

void MainMenu::MoveDown()
{
}

void MainMenu::setupRectangles()
{
	std::cout << "Set up rectangle" << std::endl;
	m_buttonShape.setFillColor(sf::Color(200, 200, 100, 255));
	m_buttonShape.setOutlineColor(sf::Color::Black);
	m_buttonShape.setOutlineThickness(5.0f);
	m_buttonShape.setPosition(sf::Vector2f{ 100.0f, 100.0f });
	m_buttonShape.setSize(sf::Vector2f{ 100.0f, 100.0f });
}
