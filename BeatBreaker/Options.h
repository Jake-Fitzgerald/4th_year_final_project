#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Globals.h"
#include <iostream>
#include "HUD.h"
#include "SoundManager.h"


class Options
{
public:
	Options(const sf::Font& font);

	void setupOptionsTexts();
	void setupOptionsButtons();

	void renderOptions(sf::RenderWindow& t_window);

	bool handleMouseClick(sf::Vector2f t_mousePos, HUD& t_hud, SoundManager &t_soundManager);

	void getSoundTypes();

private:
	sf::Text m_OptionsText;
	sf::Text m_musicText;
	sf::Text m_sfxText;
	sf::Text m_fpsText;
	sf::Text m_returnText;

	sf::RectangleShape m_musicButton;
	sf::RectangleShape m_sfxButton;
	sf::RectangleShape m_fpsButton;
	sf::RectangleShape m_returnButton;

	// Positions
	sf::Vector2f m_screenCentre = SCREEN_CENTRE;
	sf::Vector2f m_optionsPos = sf::Vector2f{ m_screenCentre.x - 100.0f, m_screenCentre.y - 300.0f };
	sf::Vector2f m_musicPos = sf::Vector2f{ m_screenCentre.x - 100.0f, m_screenCentre.y - 100.0f };
	sf::Vector2f m_sfxPos = sf::Vector2f{ m_screenCentre.x - 100.0f, m_screenCentre.y };
	sf::Vector2f m_fpsPos = sf::Vector2f{ m_screenCentre.x - 100.0f, m_screenCentre.y + 100.0f};
	sf::Vector2f m_returnPos = sf::Vector2f{ m_screenCentre.x - 100.0f, m_screenCentre.y + 200.0f };

	sf::Vector2f m_buttonScale = sf::Vector2f{ 200.0f, 50.0f };

	// Keep track of the sound types (assume they are already at full volume)
	float m_currentMusicVolume = 100.0f;
	float m_currentSFXVolume = 100.0f;
};

