#pragma once
#include <iostream>
#include <vector>
#include <fstream> // Loading file
#include <cstdint> // fixed int types we need (uint32)
#include <string>
#include <map>

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

	Running status is a byte that is included in multiple chunks in a track, however becuase of the way midi is optimised it only says
	it for that first part of the chunk and then we assume it is the same for the chunks following it. 
	We need to look at the left most bit to see if it is a 'status byte' (0) or a 'data byte' (1)

	Status bytes are things like Note On, Note Off,
	Status bytes = 80 -> EF
	System messages = F0 -> FF
	
	Real Time System Events are only used for Live Midi so we can ignore them in the parser.

	General Midi for which instruments are assigned a certain number:
	https://en.wikipedia.org/wiki/General_MIDI

	Tempo are how many microseconds are in a quarter note. We dived the tempo by 1 million to convert it to seconds.
	To get it as a'tick' we divide that new number in seconds by a large number (we can just use 24 for now and see what happens).
	The tick allows us to get an accurate delta time.

*/

struct MidiNote
{
	int pitch = 0;        // 0 - 127
	int velocity = 0;     // 0 - 127
	// Microseconds
	uint32_t startTick = 0;  
	uint32_t endTick = 0;    
	// Seconds
	double startTime = 0.0f; 
	double endTime = 0.0f;  
	bool b_hasPlayed = false;

};

struct MidiTrack
{
	std::string trackName = " ";
	std::string intrumentName = " ";
	std::vector<MidiNote> midiNotes; // Holds all the notes for this track

};

// Taken from the Expanded Messages Documentation in the references folder
enum EventType : uint8_t
{
	metaEvent = 0xFF,

	// Meta types:
	tempo = 0x51,
	timeSignature = 0x58,
	keySignature = 0x59,

	// Status bytes (higher than 80)
	statusByte = 0x80,

	// Message type mask 
	// Keep only the upper 4 bits (message type) and ignore lower 4 bits (channel)
	messageTypeMask = 0xF0,

	noteOff = 0x80,
	noteOn = 0x90,
	afterTouch = 0xA0,
	controlChange = 0xB0,
	programChange = 0xC0,
	channelAftertouch = 0xD0,
	pitchBend = 0xE0,
	systemExclusive = 0xF0
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

