#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include <iostream>

/*
Notes:
	- FPS counter at the top right corner

	Music Visuals
	- Beat Markers
		- Quarter Notes (1, 2, 3, ...)
		- Full Note	    (..., ..., ..., 4)
		The quarter note amounts should change depending on the time signature from the MIDI data
		(test with 4/4 for now)
*/

class HUD
{
public:
	HUD(const sf::Font& font);

	// Beat Markers
	void setupBeatMarkers();
	void setupButtonSprites();

	void updateFPSText(float &t_fpsNumber);
	void setFPSBool();
	bool getFPSBool();

	void drawHUD(sf::RenderWindow &t_window);

private:
	// FPS
	float m_fpsNumber;
	sf::Text m_fpsText;
	bool b_isFPSVisible;

	// Beat Visualiser
	// Left Quart Notes
	sf::RectangleShape m_beatMarkerLeftQuarter_1;
	sf::RectangleShape m_beatMarkerLeftQuarter_2;
	sf::RectangleShape m_beatMarkerLeftQuarter_3;
	std::vector<sf::RectangleShape> m_beatMarkersLeft;
	// Right Quarter Notes
	sf::RectangleShape m_beatMarkerRightQuarter_1;
	sf::RectangleShape m_beatMarkerRightQuarter_2;
	sf::RectangleShape m_beatMarkerRightQuarter_3;
	std::vector<sf::RectangleShape> m_beatMarkersRight;
	// Whole Note (Dead Centre)
	sf::RectangleShape m_beatMarkerWholeNote;

	sf::Vector2f m_beatMarkerSize = sf::Vector2f{ 10.0f, 30.0f };
	sf::Vector2f m_beatMarkerLeftPos = sf::Vector2f{ 100.0f, 600.0f };
	sf::Vector2f m_beatMarkerRightPos = sf::Vector2f{ 400.0f, 600.0f };

	sf::Color c_beatMarkerClear = sf::Color(255, 255, 255, 50);
	sf::Color c_beatMarkerSet = sf::Color(255, 0, 0, 150);
	sf::Color c_beatMarkerSetWholeNote = sf::Color(0, 255, 0, 200);

	// Buttons 
	sf::Texture m_playButtonTexture;
	sf::Sprite m_playButtonSprite;
	sf::Texture m_pauseButtonTexture;
	sf::Sprite m_pauseButtonSprite;
	sf::Texture m_skipEndButtonTexture;
	sf::Sprite m_skipEndButtonSprite;
	sf::Texture m_skipStartButtonTexture;
	sf::Sprite m_skipStartButtonSprite;
	sf::Texture m_stopButtonTexture;
	sf::Sprite m_stopButtonSprite;
	sf::Texture m_muteButtonTexture;
	sf::Sprite m_muteButtonSprite;
	sf::Texture m_unmuteButtonTexture;
	sf::Sprite m_unmuteButtonSprite;

	sf::Vector2f buttonsLeftPos{ paddingX, paddingY + 600.0f };
	float buttonSpacing = 50.0f;

	
};

