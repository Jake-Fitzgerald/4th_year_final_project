#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Globals.h"
#include <iostream>
#include "HUD.h"
#include "SoundManager.h"
#include <iostream>
#include <fstream> 


class Options
{
public:
	Options(const sf::Font& font);

	void setupOptionsTexts();
	void setupOptionsButtons();

	void renderOptions(sf::RenderWindow& t_window);

	bool handleMouseClick(sf::Vector2f t_mousePos, HUD& t_hud, SoundManager &t_soundManager);

	void getSoundTypes();

	void savePreferences();
	void loadPreferences(SoundManager& t_soundManager);

	void changeButtonColours();

	void setupOptionsTextures();

private:
	sf::Text m_OptionsText;
	sf::Text m_musicText;
	sf::Text m_sfxText;
	sf::Text m_fpsText;
	sf::Text m_returnText;
	sf::Text m_saveText;
	sf::Text m_loadText;

	sf::RectangleShape m_musicButton;
	sf::RectangleShape m_musicTestButton;
	sf::RectangleShape m_sfxButton;
	sf::RectangleShape m_sfxTestButton;
	sf::RectangleShape m_fpsButton;
	sf::RectangleShape m_returnButton;
	sf::RectangleShape m_saveButton;
	sf::RectangleShape m_loadButton;

	// Positions
	sf::Vector2f m_screenCentre = SCREEN_CENTRE;
	sf::Vector2f m_optionsPos = sf::Vector2f{ m_screenCentre.x - 100.0f, m_screenCentre.y - 300.0f };
	sf::Vector2f m_musicPos = sf::Vector2f{ m_screenCentre.x - 100.0f, m_screenCentre.y - 100.0f };
	sf::Vector2f m_musicTestPos = sf::Vector2f{ m_musicPos.x + 250.0f, m_musicPos.y };
	sf::Vector2f m_sfxPos = sf::Vector2f{ m_screenCentre.x - 100.0f, m_screenCentre.y };
	sf::Vector2f m_sfxTestPos = sf::Vector2f{ m_sfxPos.x + 250.0f, m_sfxPos.y };
	sf::Vector2f m_fpsPos = sf::Vector2f{ m_screenCentre.x - 100.0f, m_screenCentre.y + 100.0f};
	sf::Vector2f m_returnPos = sf::Vector2f{ m_screenCentre.x - 400.0f, m_screenCentre.y + 200.0f };
	sf::Vector2f m_savePos = sf::Vector2f{ m_screenCentre.x - 100.0f, m_screenCentre.y + 200.0f };
	sf::Vector2f m_loadPos = sf::Vector2f{ m_screenCentre.x + 100.0f, m_screenCentre.y + 200.0f };

	sf::Vector2f m_buttonScale = sf::Vector2f{ 200.0f, 50.0f };
	sf::Vector2f m_buttonSmallScale = sf::Vector2f{ 100.0f, 50.0f };
	sf::Vector2f m_buttonTestScale = sf::Vector2f{ 50.0f, 50.0f };

	// Keep track of the sound types (assume they are already at full volume)
	float m_currentMusicVolume = 100.0f;
	float m_currentSFXVolume = 100.0f;

	// Textures/Sprites
	// Music Note
	sf::Texture m_musicNoteTex;
	sf::Sprite m_musicNoteSprite{ m_musicNoteTex };
	// SFX Note 
	sf::Texture m_sfxNoteTex;
	sf::Sprite m_sfxNoteSprite{ m_sfxNoteTex };
	// Background
	sf::Texture m_bgTex;
	sf::Sprite m_bgSprite{ m_bgTex };
};

