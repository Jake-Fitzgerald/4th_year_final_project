#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
// Random lib
#include <ctime>
#include <random>
// Block Compnent
#include "Block.h"

// Notes:
// Import the parsed MIDI data to generate a certain block section.
//
// Generic block sections that can be reused inbetween the MIDI 
// based sections and randomlygenerated sections.
//
// Generic: Health - plus shaped barries surrounding a health collectible
// [USED FREQUENTLY TO HELP PLAYER MANAGE THEIR LIFE AS IT DRAINS WHEN MOVING THROUGH THE MAP]
// Generic: Funnel Start - Barries create a small opening in the centre (2 coloured blocks)
// [USED AS THE START OF A LEVEL OR TRACK SECTION TO FORCE PLAYERS INTO THE CENTRE OF THE GRID]
// Generic: Funnel End - Barries create a small opening in the centre (2 coloured blocks)
// [USED AS THE END OF A LEVEL OR TRACK SECTION TO FORCE PLAYERS INTO THE CENTRE OF THE GRID]
// Generic: Huge coloured section - Every block is coloured the same colour and breaks it a single hit.
// [Transition/Bonus section to break up each part of a song (Verse, Chorus, etc), also gives a lot of points]
// 
// Randomised sections that are mostly random to add variety and break up
// the MIDI sections (since music is repetetive then a certain amount of the 
// MIDI block sections will be aswell).
//
// Mersenne Twister ref:
// https://www.geeksforgeeks.org/cpp/stdmt19937-class-in-cpp/



class BlockGenerator
{
public:
	void randomNum();

	void genMIDISection(/* JSONFile t_MIDIData*/);

	void genRandomSection(int t_randType);

	// Generic Sections
	void genHealthSection();
	void genFunnelTopSection();
	void genFunnelBottomSection();

private:
	// Total number of blocks in a given map (change based on difficulty)
	const int TOTAL_BLOCK_AMOUNT = 100; // leave it small for the time being


};

