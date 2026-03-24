#pragma once
#include <iostream>
#include <vector>
#include <fstream> // Loading file
#include <cstdint> // fixed int types we need (uint32)
#include <string>
#include <map>
#include "MIDIParse.h"

//enum EventType : uint8_t
//{
//	metaEvent = 0xFF,
//
//	// Meta types:
//	tempo = 0x51,
//	timeSignature = 0x58,
//	keySignature = 0x59,
//	trackName = 0x03,
//	instrumentName = 0x04, // TO DO - MIGHT BE BROKEN SINCE IT CAN'T FIND ONE FROM OUR CURRENT MIDI?
//
//	// Status bytes (higher than 80)
//	statusByte = 0x80,
//
//	// Message type mask 
//	// Keep only the upper 4 bits (message type) and ignore lower 4 bits (channel)
//	messageTypeMask = 0xF0,
//
//	noteOff = 0x80,
//	noteOn = 0x90,
//	afterTouch = 0xA0,
//	controlChange = 0xB0,
//	programChange = 0xC0,
//	channelAftertouch = 0xD0,
//	pitchBend = 0xE0,
//	systemExclusive = 0xF0
//};

class MidiWrite
{
public:
	MidiWrite();
	//MidiWrite(std::string& t_fileName/*, std::vector<MidiNote> t_notes*/);

	bool writeFile(std::string& t_fileName);

	void writeHeader(std::ofstream& t_file);
	void writeTimeSigTrack(std::ofstream& t_file);
	void writeTempoTrack(std::ofstream& t_file);
	void writeNoteTrack(std::ofstream& t_file);

	void write_uint32(std::ofstream& t_file, uint32_t t_value);
	void write_uint16(std::ofstream& t_file, uint16_t t_value);
	void writeByte(std::ofstream& t_file, uint8_t t_value);

	void writeMicroSeconds(std::ofstream& t_file);

	void writeNoteOn(std::ofstream& t_file, uint8_t t_pitch, uint8_t t_velocity, uint8_t t_deltatime);
	void writeNoteOff(std::ofstream& t_file, uint8_t t_pitch, uint8_t t_velocity, uint8_t t_deltatime);

	void setupNotes();

private:

	std::string m_drectoryPath = "ASSETS\\AUDIO\\MUSIC\\SavedMidi\\";
	
	double m_BPM = 120.0;

	int m_noteTrackLength = 0;


	std::vector<MidiNote> m_testNotes;
	int m_quarterNoteLength = 96;
};

