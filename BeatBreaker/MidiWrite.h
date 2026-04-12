#pragma once
#include <SFML//Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include <vector>
#include <fstream> // Loading file
#include <cstdint> // fixed int types we need (uint32)
#include <string>
#include <map>
#include "MIDIParse.h"

struct MidiEvent
{
	uint32_t tick;
	bool b_isNoteOn;
	uint8_t pitch;
	uint8_t velocity;
};

class MidiWrite
{
public:
	MidiWrite();

	bool writeFile(std::string& t_fileName);

	void writeHeader(std::ofstream& t_file);
	void writeTimeSigTrack(std::ofstream& t_file);
	void writeTempoTrack(std::ofstream& t_file);
	void writeNoteTrack(std::ofstream& t_file);

	void write_uint32(std::ofstream& t_file, uint32_t t_value);
	void write_uint16(std::ofstream& t_file, uint16_t t_value);
	void writeByte(std::ofstream& t_file, uint8_t t_value);
	void writeByteToBuffer(uint8_t t_value);

	void writeMicroSeconds(std::ofstream& t_file);

	//void calculateTrackLength();

	void writeCC(std::ofstream& t_file);
	void writeCCToBuffer();
	void writeProgamChange(std::ofstream& t_file);
	void writeProgramChangeToBuffer();

	void writeNoteOn(std::ofstream& t_file, uint8_t t_pitch, uint8_t t_velocity, uint32_t t_deltatime);
	void writeNoteOnToBuffer(uint8_t t_pitch, uint8_t t_velocity, uint32_t t_deltatime);
	void writeNoteOff(std::ofstream& t_file, uint8_t t_pitch, uint8_t t_velocity, uint32_t t_deltatime);
	void writeNoteOffToBuffer(uint8_t t_pitch, uint8_t t_velocity, uint32_t t_deltatime);

	void writeEndOfTrack(std::ofstream& t_file);
	void writeVLQ(std::ofstream& t_file, uint32_t t_value);
	void writeVLQToBuffer(uint32_t t_value);

	void setupRecordedNotes(std::vector<MidiNote>& t_notes);
	void setBPM(double t_BPM);

private:

	std::string m_drectoryPath = "ASSETS\\AUDIO\\MUSIC\\SavedMidi\\";

	int m_noteTrackNameLength = 11;
	int m_ccLength = 54; // 27 by 2
	int m_ccCounter = 0;
	int m_noteLength = 0;
	int m_endOfTrackLength = 4;

	double m_BPM = 120.0;

	std::vector<uint8_t> m_trackBuffer;
	int m_noteTrackLength = 0;

	std::vector<MidiNote> m_recordedNotes;
	int m_quarterNoteLength = 96;

};

