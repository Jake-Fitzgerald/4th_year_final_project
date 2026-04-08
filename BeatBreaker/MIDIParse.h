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
	int pitch = 0; 
	int velocity = 0;
	std::string noteName = "";

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
	std::vector<MidiNote> midiNotes; 
};

// Taken from the Expanded Messages Documentation in the references folder
enum EventType : uint8_t
{
	metaEvent = 0xFF,

	// Meta types:
	endOfTrack = 0x2F,
	tempo = 0x51,
	timeSignature = 0x58,
	keySignature = 0x59,
	trackName = 0x03,
	instrumentName = 0x04, // TO DO - MIGHT BE BROKEN SINCE IT CAN'T FIND ONE FROM OUR CURRENT MIDI?

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
	pan = 0x0A,
	volume = 0x07,
	regParamNum_MSB = 0x65,
	regParamNum_LSB = 0x64, // 0x65
	dataEntry = 0x06, // 0x05
	systemExclusive = 0xF0,

	vlqSize = 0x7F
};

class MIDIParse
{
public:
	MIDIParse();

	MIDIParse(std::string& t_fileName);

	bool parseFile(std::string& t_fileName);

	std::string readString(std::ifstream &t_file, uint32_t nbyteLength);

	void parseHeader(std::ifstream& t_file);
	void parseTimeSig(std::ifstream& t_file);
	void parseTempo(std::ifstream& t_file);

	// Channel Parsing
	void noteOff(std::ifstream& t_file, uint8_t firstDataByte);
	void noteOn(std::ifstream& t_file, uint8_t firstDataByte);

	void resetTrack();

	// Shift bits
	// Reads 4 bytes then converts them into 32
	uint32_t read_uint32(std::ifstream& t_file);
	// Reads 2 bytes then converts them into 16
	uint16_t read_uint16(std::ifstream& t_file);

	uint8_t readByte(std::ifstream& t_file);
	uint32_t readVLQ(std::ifstream& t_file);

	// Getter functions
	std::vector<MidiTrack>& getMidiTracks();
	uint16_t getTicksPerQuarter();
	double getBPM();
	std::string getTimeSignature();
	int getNominator();
	int getDenominator();
	std::string getMidiFileName();

	std::string pitchToNoteName(int t_pitch);

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

	std::string m_midifileName = " ";

	// Time Signature
	int m_nominator; // 3 from 3/4
	int m_denominator; // 4 from 3/4
	std::string m_timeSignature = " ";
	// Tempo
	double m_BPM = 120.0f;

	// Timing
	uint32_t currentTick;
	// Dictionary (note, velocity)
	std::map<int, MidiNote> activeNotes;

	// Stores every track
	std::vector<MidiTrack> midiTracks;
	// Temp track when parsing NoteOn
	MidiTrack currentTrack;

};

