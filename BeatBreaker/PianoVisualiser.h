#pragma once
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "MIDIParse.h"

/*
* 
    This can be used both for displaying parsed midi data,
	but also for live midi through a keyboard syncing with the piano keys turning red in the visual when pressed.

	We wil make one octave (C note to C note) then repeat that four more times
	52 white keys, 36 black keys, 88 keys in total -> 5 octaves of C to C, 12 keys per octave, 5 extra keys?

	Pattern w,b,w,b,w,w,b,w,b,w,b,w
*/

class PianoVisualiser
{
public:
	void setupPianoShapes();
	void setupWhiteKey(int t_index);
	void setupBlackKey(int t_whiteKeyIndex);

	void keysTurnOn();
	void keysTurnOff();

	void renderKeys(sf::RenderWindow& t_window);

private:
	std::vector<sf::RectangleShape> keyShapes;

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

	const int TOTAL_KEYS_AMOUNT = 88;

	bool b_midiLiveMode = false;
};

