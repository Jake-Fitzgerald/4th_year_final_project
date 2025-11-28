#pragma once
#include <iostream>
#include <vector>
#include <fstream> // Loading file
#include <cstdint> // fixed int types we need (uint32)

// Notes:
/*
	MIDI is old and has a different byte order than modern PCs
	so we have to swap the byte orders around when importing them
	(big endian)

	The data we want in MIDI in in the 7 bits after the first bit

	Links:
	http://www.petesqbsite.com/sections/express/issue18/midifilespart1.html

	First parse the header to find the BPM, Time signature

*/

class MIDIParse
{
public:
	MIDIParse();

	MIDIParse(const std::string& t_fileName);

	bool parseFile(const std::string& t_fileName);


	// Shift bits
	// Reads 4 bytes then converts them into 32
	uint32_t read_uint32(std::ifstream& t_file);
	// Reads 2 bytes then converts them into 16
	uint16_t read_uint16(std::ifstream& t_file);

	// Save the parsed data
	void saveToFile();
	// Load the parsed data
	void LoadFromFile();

private:
	// Header Data
	double m_BPM;
	int m_timeSigBeat; // 3 from 3/4
	int m_timeSigMeasure; // 4 from 3/4

	// std::vector<> m_tracks; // Unsure how to store these when reading them
	std::string m_trackName;

};

