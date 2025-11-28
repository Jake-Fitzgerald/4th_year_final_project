#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
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

const int ROWS = 8;
const int COLS = 10;

class BlockGenerator
{
public:
	void randomNum();

	void genMIDISection(/* JSONFile t_MIDIData*/);

	void genRandomPattern(int t_sectionLength);

	std::vector<std::vector<Block>>& getBlockGrid();

	void renderBlocks(sf::RenderWindow& t_window);

	void updateBlocks(float t_deltaTime);
	
	// Randomise Patterns
	void genRandomSection(int t_randType);
	ColourStates getRandomColour();

	// Generation Settings
	void setDifficulty(const std::string& t_difficulty);
	int barrierCalculate();
	int healthCalculate();

	// Generic Sections
	void genHealthSection();
	void genFunnelTopSection();
	void genFunnelBottomSection();

private:
	// Total number of blocks in a given map (change based on difficulty)
	const int TOTAL_BLOCK_AMOUNT = 100; // leave it small for the time being

	
	const int SMALL_SECTION = ROWS * 10;
	const int MEDIUM_SECTION = ROWS * 20;
	const int LARGE_SECTION = ROWS * 30;

	// Grid dimensions
	int m_rows = ROWS;
	int m_cols = COLS;

	// Block spacing
	float m_blockSize = 50.0f;
	float m_startX = 100.0f;
	float m_startY = 100.0f;

	std::vector<std::vector<Block>> m_blockGrid;

	// Random Seed
	std::mt19937 m_rng;

	// Test MIDI values
	int m_bpm = 100;
	int m_bps = 200;
	std::string m_currentDifficulty = "EASY";
};

