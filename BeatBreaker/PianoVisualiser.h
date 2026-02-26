#pragma once
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "MIDIParse.h"
#include "SoundManager.h"
#include "CollisionManager.h"

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
	sf::Color originalColour;      
};

struct FallingNote
{
	sf::RectangleShape noteShape;
	sf::RectangleShape earlyTrigger;
	sf::RectangleShape lateTrigger;
	std::string targetNoteName; 
};

class PianoVisualiser
{
public:
	PianoVisualiser(SoundManager& t_soundManager, CollisionManager& t_collisionManager);
	void setupPianoShapes();
	void setupWhiteKey(int t_index, std::string t_noteLetter, int t_octave);
	void setupBlackKey(int t_whiteKeyIndex, std::string t_noteLetter, int t_octave);

	void setupPianoSounds();

	void keysTurnOn(int t_KeyPos);
	void keysTurnOff(int t_KeyPos);

	void renderKeys(sf::RenderWindow& t_window);

	void handleClick(sf::Vector2f t_mousePos);
	bool checkIfKeyClicked(sf::Vector2f t_mousePos, const PianoKey& t_key);

	// Midi Input
	void noteOn(const std::string& t_noteName);
	void noteOff(const std::string& t_noteName);

	// Note Test (temp)
	void spawnTestNote();
	void updateNotes(float t_deltaTime);

private:
	SoundManager* m_soundManager;
	CollisionManager* m_collisionManager;

	//std::vector<sf::RectangleShape> keyShapes;
	std::vector<PianoKey> m_keys;

	// Piano Position
	float pianoPosX = paddingX;
	float pianoPosY = paddingY + 400.0f;


	// Key sizes
	sf::Vector2f blackKeySize{ 22.0f, 70.0f };
	sf::Vector2f whiteKeySize{ 38.0f, 120.0f };
	
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

	// Note Test (temp)
	FallingNote m_testNote;
	float m_noteTestSpawnY = -100.0f;
	float m_noteSpeed = 300.0f;

	bool b_testNoteActive = false;
};

