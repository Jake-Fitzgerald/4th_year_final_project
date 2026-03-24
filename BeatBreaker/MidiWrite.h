#pragma once
#include <iostream>
#include <vector>
#include <fstream> // Loading file
#include <cstdint> // fixed int types we need (uint32)
#include <string>
#include <map>
#include "MIDIParse.h"

class MidiWrite
{
public:
	MidiWrite();
	//MidiWrite(std::string& t_fileName/*, std::vector<MidiNote> t_notes*/);

	bool writeFile(std::string& t_fileName);

	void writeHeader(std::ofstream& t_file);

private:

	std::string m_drectoryPath = "ASSETS\\AUDIO\\MUSIC\\SavedMidi\\";
	
};

