#pragma once
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "MIDIParse.h"

/*
*   To do:
	Get each midi track's name by string.
	Display track sf::rectangle shape when the note is played and dissapears when note if off.
	Have the colour of each track be unique to make it obvious which one is which.

	Move the song playback into the game.cpp and reference it's current time and other variables there,
	otherwise we would have to repeat the same code in every visualiser. Also it's easier for the HUD to display the data that way also.
*/

class TrackVisualiser
{
public:
	TrackVisualiser(std::shared_ptr<const sf::Font> font);

	void setupShapes();
	void setupColours();

	void renderTrackVis(sf::RenderWindow& t_window);
	void update(float t_deltaTime);

	void loadMidiTracks(const std::vector<MidiTrack>& t_tracks, int t_ticksPerQuarter, double t_bpm);

	// Playback
	void playSong();
	void pauseSong();
	void stopSong();

private:
	std::vector<sf::RectangleShape> trackShapes;

	// Track Dividers
	std::vector<sf::RectangleShape> trackLinesVertical;
	std::vector<sf::RectangleShape> trackLinesHorizontal;


	// Bottom UI
	std::vector<sf::RectangleShape> bottomBorders;
	std::vector<sf::RectangleShape> trackNameBox;
	std::vector<sf::RectangleShape> trackNumberBox;

	// Text
	std::shared_ptr<const sf::Font> m_font;
	std::vector<sf::Text> m_trackNameTexts;
	std::vector<sf::Text> m_trackNumberTexts;

	// Padding
	sf::Vector2f visualiserOrigin{ paddingX, paddingY };

	// Track Visualiser Sizes
	float visualiserWidth = TRACK_SIZE_X;
	float visualiserPaddingX = paddingX;
	float visualiserYStart = 500.0f;

	// Track Dividers
	int lineCount = 12;
	float lineWidth = 2.0f;
	float lineHeight = 500.0f;
	float spacing = 100.0f;


	// Horizontal lines
	int horizontalLineCount = 4;
	float horizontalLineHeight = 2.0f;
	float horizontalStartY = 100.0f;
	float horizontalSpacing = 100.0f;
	float horizontalXPos = paddingX;

	// Bottom UI
	float bottomBorderHeight = 10.0f;
	float bottomBorderStartY = 400.0f;

	// Track Name and Track Number boxes
	float boxWidth = 80.0f;
	float boxHeight = 30.0f;
	float boxYOffset = -85.0f;
	float boxRowSpace = 20.0f;

	// Track colours
	sf::Color trackCol1 = sf::Color::Blue;
	sf::Color trackCol2 = sf::Color::Green;
	sf::Color trackCol3 = sf::Color::Red;
	sf::Color trackCol4 = sf::Color::Magenta;
	sf::Color trackCol5 = sf::Color::Yellow;
	sf::Color trackCol6 = sf::Color::Cyan;
	sf::Color trackCol7 = sf::Color::White;
	sf::Color trackCol8 = sf::Color(10.0f, 150.0f, 50.0f);
	std::vector<sf::Color> trackColours;

	// Midi Data
	std::vector<MidiTrack> m_midiTracks;
	int m_ticksPerQuarter = 0;
	double m_bpm = 0.0f;

	// Song stuff
	bool b_isSongPlaying = true;
	double m_songCurrentTime = 0.0f;
};
