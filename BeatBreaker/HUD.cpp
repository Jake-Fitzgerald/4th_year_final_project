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

	// Beat Markers
	setupBeatMarkers();
}

void HUD::setupBeatMarkers()
{
	// Fill Left Vectors
	m_beatMarkersLeft.push_back(m_beatMarkerLeftQuarter_1);
	m_beatMarkersLeft.push_back(m_beatMarkerLeftQuarter_2);
	m_beatMarkersLeft.push_back(m_beatMarkerLeftQuarter_3);

	for (int i = 0; i < m_beatMarkersLeft.size(); i++)
	{
		m_beatMarkersLeft[i].setFillColor(c_beatMarkerClear);
		m_beatMarkersLeft[i].setOutlineColor(sf::Color::Black);
		m_beatMarkersLeft[i].setOutlineThickness(2.0f);
		m_beatMarkersLeft[i].setSize(m_beatMarkerSize);
		m_beatMarkersLeft[i].setPosition(sf::Vector2f{ m_beatMarkerLeftPos.x + (50.0f * i), m_beatMarkerLeftPos.y });
	}

	// Fill Right Vectors
	m_beatMarkersRight.push_back(m_beatMarkerRightQuarter_1);
	m_beatMarkersRight.push_back(m_beatMarkerRightQuarter_1);
	m_beatMarkersRight.push_back(m_beatMarkerRightQuarter_1);

	for (int i = 0; i < m_beatMarkersRight.size(); i++)
	{
		m_beatMarkersRight[i].setFillColor(c_beatMarkerClear);
		m_beatMarkersRight[i].setOutlineColor(sf::Color::Black);
		m_beatMarkersRight[i].setOutlineThickness(2.0f);
		m_beatMarkersRight[i].setSize(m_beatMarkerSize);
		m_beatMarkersRight[i].setPosition(sf::Vector2f{ m_beatMarkerRightPos.x - (50.0f * i), m_beatMarkerRightPos.y });
	}

	// Full Note Marker
	m_beatMarkerWholeNote.setFillColor(c_beatMarkerSetWholeNote);
	m_beatMarkerWholeNote.setOutlineColor(sf::Color::Black);
	m_beatMarkerWholeNote.setOutlineThickness(2.0f);
	m_beatMarkerWholeNote.setSize(m_beatMarkerSize);

	sf::Vector2f midpoint;
	midpoint.x = (m_beatMarkerLeftPos.x + m_beatMarkerRightPos.x) / 2.0f;
	midpoint.y = (m_beatMarkerLeftPos.y + m_beatMarkerRightPos.y) / 2.0f;

	m_beatMarkerWholeNote.setPosition(midpoint);
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
	
	// Beat Markers
	for (int i = 0; i < m_beatMarkersLeft.size(); i++)
	{
		t_window.draw(m_beatMarkersLeft[i]);
	}
	for (int i = 0; i < m_beatMarkersRight.size(); i++)
	{
		t_window.draw(m_beatMarkersRight[i]);
	}
	t_window.draw(m_beatMarkerWholeNote);
}
