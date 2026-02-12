#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include <iostream>
#include "MIDIParse.h"

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

	void loadMidiData(const std::vector<MidiTrack>& t_tracks, std::string t_timeSig, double t_bpm, std::string t_midiFileName);
	void updateMidiInfo();
	std::string removePathData(std::string t_midiPathName);

	void mouseClick(sf::Vector2f t_mousePos);
	bool returnClick(sf::Vector2f t_mousePos);
	bool playClick(sf::Vector2f t_mousePos);
	bool pauseClick(sf::Vector2f t_mousePos);
	bool stopClick(sf::Vector2f t_mousePos);
	bool skipToStart(sf::Vector2f t_mousePos);
	bool skipToEnd(sf::Vector2f t_mousePos);
	bool muteClick(sf::Vector2f t_mousePos);
	bool checkIfAreaClicked(sf::Vector2f t_mousePos, sf::Vector2f t_topLeft, sf::Vector2f t_size);

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
	sf::Vector2f m_beatMarkerLeftPos = sf::Vector2f{ 800.0f, 650.0f };
	sf::Vector2f m_beatMarkerRightPos = sf::Vector2f{ 1000.0f, 650.0f };

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

	sf::Texture m_returnTexture;
	sf::Sprite m_returnSprite{ m_returnTexture };

	// Midi Information
	sf::Vector2f m_midiTextPos{ paddingX, paddingY + 660.0f };
	std::string m_midiFileName;
	sf::Text m_midiFileNameText;

	std::string m_midiTimeSig;
	sf::Text m_midiTimeSigText;

	std::string m_midiBPM;
	sf::Text m_midiBPMText;

	bool b_isMidiInfoVisible;

	// UI Polish
	sf::RectangleShape m_bottomBorderBar;
	
};

