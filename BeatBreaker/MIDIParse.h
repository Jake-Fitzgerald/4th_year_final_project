#pragma once
#include <iostream>
#include <vector>
#include <fstream> // Loading file
#include <cstdint> // fixed int types we need (uint32)
#include <string>

// Notes:
/*
	MIDI is old and has a different byte order than modern PCs
	so we have to swap the byte orders around when importing them
	(big endian)

	The data we want in MIDI in in the 7 bits after the first bit

	Links:
	http://www.petesqbsite.com/sections/express/issue18/midifilespart1.html

	First parse the header to find if it's a valid MIDI file, then the next two tracks will always be the Time Signature and BPM.

	We have to read everything in the stream sequentially or else it will get corrupted.
	So even if we get loads of useless data, we won't be using we still need to parse it.

*/

struct MidiNote
{
	int pitch = 0;        // 0 - 127
	int velocity = 0;     // 0 - 127
	double startTime = 0.0f; // in seconds
	double endTime = 0.0f;   // in seconds
	bool b_hasPlayed = false;

};

struct MidiTrack
{
	std::string trackName = " ";
	std::string intrumentName = " ";
	std::vector<MidiNote> midiNotes; // Holds all the notes for this track

};

enum EventType : uint8_t
{
	metaEvent = 0xFF,

	// Meta types:
	timeSignature = 0x58
};

class MIDIParse
{
public:
	MIDIParse();

	MIDIParse(const std::string& t_fileName);

	bool parseFile(const std::string& t_fileName);

	void parseHeader();

	// Shift bits
	// Reads 4 bytes then converts them into 32
	uint32_t read_uint32(std::ifstream& t_file);
	// Reads 2 bytes then converts them into 16
	uint16_t read_uint16(std::ifstream& t_file);

	uint8_t readByte(std::ifstream& t_file);
	uint32_t readVLQ(std::ifstream& t_file);


	// Save the parsed data
	void saveToFile();
	// Load the parsed data
	void LoadFromFile();

private:
	// Header Data
	uint32_t m_headerLength = -1; // should be 6
	uint16_t m_midiFormat = -1; // Can be 0, 1, 2
	uint16_t m_numTracks = -1;
	uint16_t m_ticksPerQuarter = -1;



	double m_BPM;
	int m_nominator; // 3 from 3/4
	int m_denominator; // 4 from 3/4
	std::string m_timeSignature = " ";

	// std::vector<> m_tracks; // Unsure how to store these when reading them
	//std::string m_trackName;

	// Stores every track
	std::vector<MidiTrack> midiTracks;

};

