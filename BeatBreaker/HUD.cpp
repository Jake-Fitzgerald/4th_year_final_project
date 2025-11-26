#include "HUD.h"

HUD::HUD(const sf::Font& font) : m_fpsText(font)
{
	m_fpsText.setPosition(sf::Vector2f{ SCREEN_CENTRE.x + 600.0f, SCREEN_CENTRE.y - 350.0f });
	m_fpsText.setFillColor(sf::Color::White);
	m_fpsText.setOutlineColor(sf::Color::Black);
	m_fpsText.setOutlineThickness(2.0f);
	m_fpsText.setCharacterSize(20U);
	m_fpsText.setString("???");

	b_isFPSVisible = true;
}

void HUD::updateFPSText(float & t_fpsNumber)
{
	m_fpsNumber = t_fpsNumber;
	m_fpsText.setString(std::to_string(static_cast<int>(m_fpsNumber)));
}

void HUD::setFPSBool()
{
	if (b_isFPSVisible == true)
	{
		b_isFPSVisible = false;
	}
	else
	{
		b_isFPSVisible = true;
	}
}

bool HUD::getFPSBool()
{
	return b_isFPSVisible;
}

void HUD::drawHUD(sf::RenderWindow &t_window)
{
	if (b_isFPSVisible)
	{
		t_window.draw(m_fpsText);
	}
	
}
