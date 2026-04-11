#include "VisualiserSelect.h"

VisualiserSelect::VisualiserSelect(std::shared_ptr<const sf::Font> font) : m_font(font)
{
}

void VisualiserSelect::setupButtonsVisSelect()
{
	// Shapes
	for (int i = 0; i < m_visualiserCounts; i++)
	{
		VisButton button(m_font);

		button.m_buttonShape.setSize(m_buttonSize);
		button.m_buttonShape.setPosition(sf::Vector2f{ paddingX , paddingY + i * m_spacing });
		button.m_buttonShape.setFillColor(sf::Color::Blue);
		button.m_buttonShape.setOutlineThickness(2.0f);
		button.m_buttonShape.setOutlineColor(sf::Color::Black);

		button.m_buttonText.setFont(*m_font);
		if (i == 0)
		{

			button.m_buttonText.setString("Piano Visualiser");
		}
		else if (i == 1)
		{
			button.m_buttonText.setString("Drum Visualiser");
		}
		
		button.m_buttonText.setCharacterSize(20);
		button.m_buttonText.setFillColor(sf::Color::White);
		button.m_buttonText.setPosition(sf::Vector2f{ button.m_buttonShape.getPosition().x + 10.f, button.m_buttonShape.getPosition().y + 10.f });

		m_buttons.push_back(button);
	}
}

void VisualiserSelect::renderVisSelect(sf::RenderWindow& t_window)
{
	for (auto& button : m_buttons)
	{
		t_window.draw(button.m_buttonShape);
		t_window.draw(button.m_buttonText);
	}

	t_window.draw(m_returnSprite);
}


void VisualiserSelect::setupSprites()
{
	if (!m_returnTexture.loadFromFile("ASSETS\\IMAGES\\UI\\Return_Button.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading Return button in Midi File Selector" << std::endl;
	}

	m_returnSprite.setTexture(m_returnTexture, true);
	m_returnSprite.setPosition(sf::Vector2f{ 1120.0f, 0.0f });

}

int VisualiserSelect::mouseClick(sf::Vector2f t_mousePos)
{
	for (int i = 0; i < m_buttons.size(); i++)
	{
		VisButton& button = m_buttons[i];

		button.m_buttonShape.setFillColor(sf::Color::Blue);


		sf::Vector2f topLeft = button.m_buttonShape.getPosition();
		sf::Vector2f size = button.m_buttonShape.getSize();

		if (checkIfAreaClicked(t_mousePos, topLeft, size) == true)
		{
			button.m_buttonShape.setFillColor(sf::Color::Red);

			return static_cast<int>(i);
		}
		
	}
	return -1;
	
}

bool VisualiserSelect::returnClick(sf::Vector2f t_mousePos)
{
	sf::Vector2f spriteTopLeft = m_returnSprite.getPosition();
	sf::Vector2f spriteSize = sf::Vector2f{ m_returnSprite.getGlobalBounds().size.x, m_returnSprite.getGlobalBounds().size.y };

	if (checkIfAreaClicked(t_mousePos, spriteTopLeft, spriteSize) == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool VisualiserSelect::checkIfAreaClicked(sf::Vector2f t_mousePos, sf::Vector2f t_topLeft, sf::Vector2f t_size)
{
	if (t_mousePos.x >= t_topLeft.x &&
		t_mousePos.x <= t_topLeft.x + t_size.x &&
		t_mousePos.y >= t_topLeft.y &&
		t_mousePos.y <= t_topLeft.y + t_size.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void VisualiserSelect::resetButtons()
{
	for (auto& button : m_buttons)
	{
		button.m_buttonShape.setFillColor(sf::Color::Blue);
	}
}
