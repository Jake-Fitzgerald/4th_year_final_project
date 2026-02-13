#pragma once
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "MIDIParse.h"
#include "SoundManager.h"

/*
* 
    This can be used both for displaying parsed midi data,
	but also for live midi through a keyboard syncing with the piano keys turning red in the visual when pressed.

	We wil make one octave (C note to C note) then repeat that four more times
	52 white keys, 36 black keys, 88 keys in total -> 5 octaves of C to C, 12 keys per octave, 5 extra keys?

	Pattern w,b,w,b,w,w,b,w,b,w,b,w
*/

struct PianoKey
{
	sf::RectangleShape shape; 
	std::string noteName;                         
	bool b_isSharpKey;               
	bool b_isPressed;             
	sf::Color originalColor;      
};

class PianoVisualiser
{
public:
	PianoVisualiser(SoundManager& t_soundManager);
	void setupPianoShapes();
	void setupWhiteKey(int t_index, std::string t_noteLetter, int t_octave);
	void setupBlackKey(int t_whiteKeyIndex, std::string t_noteLetter, int t_octave);

	void setupPianoSounds();

	void keysTurnOn(int t_KeyPos);
	void keysTurnOff(int t_KeyPos);

	void renderKeys(sf::RenderWindow& t_window);

	void handleClick(sf::Vector2f t_mousePos);
	bool checkIfKeyClicked(sf::Vector2f t_mousePos, const PianoKey& t_key);

private:
	SoundManager* m_soundManager;

	//std::vector<sf::RectangleShape> keyShapes;
	std::vector<PianoKey> m_keys;

	// Piano Position
	float pianoPosX = paddingX;
	float pianoPosY = paddingY + 200.0f;


	// Key sizes
	sf::Vector2f blackKeySize{ 15.0f, 60.0f };
	sf::Vector2f whiteKeySize{ 22.0f, 100.0f };
	
	float whiteSpacing = 2.0f;
	float blackSpacing = 3.0f;

	// Octave stuff
	int keysPerOctave = 12;
	int octavesAmount = 7;

	//std::string noteLetters[12];

	const int TOTAL_KEYS_AMOUNT = 88;

	// UI
	sf::RectangleShape m_keyboardBase;

	bool b_midiLiveMode = false;
};

