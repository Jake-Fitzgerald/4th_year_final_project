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

*/

class MIDIParse
{
public:
	MIDIParse();

	MIDIParse(const std::string& t_fileName);

	bool parseFile(const std::string& t_fileName);

	// Shift bits
	uint32_t read_uint32(std::ifstream& t_file);
	uint16_t read_uint16(std::ifstream& t_file);

	// Save to a file
	//void saveToFile();

private:

};

