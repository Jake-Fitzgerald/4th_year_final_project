#pragma once
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include <windows.h>

/*
Notes:
	Assign each song a specific difficulty, then change that text's colour to correspond to that difficulty.

*/

struct SongButton
{
	sf::RectangleShape m_buttonShape;
	sf::RectangleShape m_previewButtonShape;

	//sf::Sprite m_previewSprite;
	sf::Text m_songNameText;
	sf::Text m_songDifficultyText;
	sf::Text m_difficultyText; 
	sf::Text m_pbScoreText;
	sf::Text m_pbScore;
	std::string midiPath = " ";

	// Music Note
	//sf::Texture m_musicNoteTex;
	std::shared_ptr<sf::Texture> m_musicNoteTex;
	sf::Sprite m_musicNoteSprite;

	SongButton(std::shared_ptr<const sf::Font> font)
				: m_songNameText(*font),
				m_songDifficultyText(*font),
				m_difficultyText(*font),
				m_pbScoreText(*font),
				m_pbScore(*font),
				m_musicNoteTex(std::make_shared<sf::Texture>()),
				m_musicNoteSprite(*m_musicNoteTex)
	{

	}
};

enum SONGDIFFICULTIES
{
	EASY,
	MEDIUM,
	HARD,
	UNKNOWN
};

enum class SongClickResult
{
	None,
	SongSelected,
	PreviewClicked,
	BeginClicked
};

struct SongPaths
{
	std::string name = " ";
	std::string path = " ";
	SONGDIFFICULTIES difficulty = SONGDIFFICULTIES::UNKNOWN;
};

class SongSelect
{
public:
	SongSelect(std::shared_ptr<const sf::Font> font);

	void setupPathStrings();
	void setupButtons();
	void setupBeginButton();
	
	void render(sf::RenderWindow& t_window);

	SongClickResult mouseClick(sf::Vector2f t_mousePos);
	bool returnClick(sf::Vector2f t_mousePos);
	bool checkIfAreaClicked(sf::Vector2f t_mousePos, sf::Vector2f t_topLeft, sf::Vector2f t_size);

	std::string getMidiPathString();
	std::string getPreviewPathString();

	std::string DifficultyToString(SONGDIFFICULTIES t_difficulty);

private:
	std::vector<SongButton> m_buttons;
	std::shared_ptr<const sf::Font> m_font;
	std::string m_selectedPath = "ASSETS\\AUDIO\\MUSIC\\C_Scale.mid"; // Default midi file
	std::string m_previewPath = " ";

	sf::RectangleShape m_returnButton;
	sf::Texture m_returnTexture;
	sf::Sprite m_returnSprite{ m_returnTexture };

	// Button 
	float m_posX = paddingX;
	float m_poY = paddingY;
	float m_spacing = 60.0f;
	sf::Vector2f m_buttonSize = { 600.0f, 40.0f };
	float m_difficultyTextSpacing = 200.0f;

	int m_pathsCount = 4; // Change this in setup paths function to be consistent

	bool b_isPreviewPlaying = false;

	// Begin button
	sf::RectangleShape m_beginButton;
	sf::Text m_beginText;
	bool b_isSongChosen = false;

	// File Paths
	// EASY
	std::string m_cScale = "ASSETS\\AUDIO\\MUSIC\\C_Scale.mid";

	// MEDIUM
	std::string m_majorAndMinorChords = "ASSETS\\AUDIO\\MUSIC\\Major_and_Minor_Chords.mid";

	// HARD 
	std::string m_hardSong = "ASSETS\\AUDIO\\MUSIC\\Full_MIDI_Range.mid"; // temp since it has too many instruments
	std::string m_thousandMiles = "ASSETS\\AUDIO\\MUSIC\\ThousandMilesRiff.mid";

	std::vector<SongPaths> m_pathVector;

	sf::Color c_Easy = sf::Color::Green;
	sf::Color c_Medium = sf::Color::Yellow;
	sf::Color c_Hard = sf::Color::Red;
	sf::Color c_Unknown = sf::Color::White;
};

