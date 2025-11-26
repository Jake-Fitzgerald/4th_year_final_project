#include "Options.h"

Options::Options(const sf::Font& font) : m_OptionsText(font), m_musicText(font), m_sfxText(font), m_fpsText(font), m_returnText(font)
{
	setupOptionsTexts();
	setupOptionsButtons();
}

void Options::setupOptionsTexts()
{
	// Options (title)
	m_OptionsText.setString("OPTIONS");
	m_OptionsText.setPosition(m_optionsPos);
	m_OptionsText.setFillColor(sf::Color::White);
	m_OptionsText.setOutlineColor(sf::Color::Black);
	m_OptionsText.setOutlineThickness(2.0f);
	m_OptionsText.setCharacterSize(50U);
	// Music Text
	m_musicText.setString("Music");
	m_musicText.setPosition(m_musicPos);
	m_musicText.setFillColor(sf::Color::White);
	m_musicText.setOutlineColor(sf::Color::Black);
	m_musicText.setOutlineThickness(2.0f);
	m_musicText.setCharacterSize(30U);
	// SFX Text
	m_sfxText.setString("SFX");
	m_sfxText.setPosition(m_sfxPos);
	m_sfxText.setFillColor(sf::Color::White);
	m_sfxText.setOutlineColor(sf::Color::Black);
	m_sfxText.setOutlineThickness(2.0f);
	m_sfxText.setCharacterSize(30U);
	// FPS Text
	m_fpsText.setString("FPS Display");
	m_fpsText.setPosition(m_fpsPos);
	m_fpsText.setFillColor(sf::Color::White);
	m_fpsText.setOutlineColor(sf::Color::Black);
	m_fpsText.setOutlineThickness(2.0f);
	m_fpsText.setCharacterSize(30U);
	// Return Text
	m_returnText.setString("RETURN");
	m_returnText.setPosition(m_returnPos);
	m_returnText.setFillColor(sf::Color::White);
	m_returnText.setOutlineColor(sf::Color::Black);
	m_returnText.setOutlineThickness(2.0f);
	m_returnText.setCharacterSize(30U);
}

void Options::setupOptionsButtons()
{
	// Music
	m_musicButton.setFillColor(sf::Color::Blue);
	m_musicButton.setSize(m_buttonScale);
	m_musicButton.setPosition(m_musicPos);
	// SFX
	m_sfxButton.setFillColor(sf::Color::Blue);
	m_sfxButton.setSize(m_buttonScale);
	m_sfxButton.setPosition(m_sfxPos);
	// FPS
	m_fpsButton.setFillColor(sf::Color::Blue);
	m_fpsButton.setSize(m_buttonScale);
	m_fpsButton.setPosition(m_fpsPos);
	// Return
	m_returnButton.setFillColor(sf::Color::Blue);
	m_returnButton.setSize(m_buttonScale);
	m_returnButton.setPosition(m_returnPos);

}

void Options::renderOptions(sf::RenderWindow& t_window)
{
	// BUTTONS
	t_window.draw(m_musicButton);
	t_window.draw(m_sfxButton);
	t_window.draw(m_fpsButton);
	t_window.draw(m_returnButton);

	// TEXTS
	// Title
	t_window.draw(m_OptionsText);
	// Audio
	t_window.draw(m_musicText);
	t_window.draw(m_sfxText);
	// Utilities
	t_window.draw(m_fpsText);
	t_window.draw(m_returnText);

}

bool Options::handleMouseClick(sf::Vector2f t_mousePos, HUD& t_hud)
{
	// Music
	if (m_musicButton.getGlobalBounds().contains(t_mousePos))
	{
		std::cerr << "Music button clicked" << std::endl;
	}
	// SFX
	if (m_sfxButton.getGlobalBounds().contains(t_mousePos))
	{
		std::cerr << "SFX button clicked" << std::endl;
	}
	// FPS
	if (m_fpsButton.getGlobalBounds().contains(t_mousePos))
	{
		t_hud.setFPSBool();
	}
	if (m_returnButton.getGlobalBounds().contains(t_mousePos))
	{
		std::cerr << "Return button clicked" << std::endl;
		// Go back to the main menu bool
		return true;
	}

	return false;
}
