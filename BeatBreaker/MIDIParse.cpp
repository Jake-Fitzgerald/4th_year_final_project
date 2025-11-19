#include "MIDIParse.h"

MIDIParse::MIDIParse()
{
}

MIDIParse::MIDIParse(const std::string& t_fileName)
{
	parseFile(t_fileName);
}

bool MIDIParse::parseFile(const std::string& t_fileName)
{
	// Open the file
	std::ifstream file;

	// | is bitwise OR not logical OR to combine
	// the reading in the file and reading it in binary
	file.open(t_fileName, std::ifstream::in | std::ios::binary);

	// If we can't open the file then return false
	if (!file.is_open())
	{
		std::cerr << "Failed to open MIDI file" << std::endl;
		return false;
	}

	// Swaps byte order of 32 bit int
	auto Swap32 = [](uint32_t n)
	{

	};

	// Convert from old big endian (MIDI) to the modern one
	// Shift 32 bit int
	uint32_t test_uint32 = read_uint32(file);
	std::cerr << "32 uint is: " << test_uint32 << std::endl;
	// Shift 16 bit int
	uint16_t test_uint16 = read_uint16(file);
	std::cerr << "16 uint is: " << test_uint16 << std::endl;

	// Read strings
	// Gets the bytes from the file and construct a string from them
	auto readString = [&file](uint32_t nbyteLength)
	{
		std::string combinedString;
		for (uint32_t i = 0; i < nbyteLength; i++)
		{
			combinedString += file.get();
			return combinedString;
		}
		std::cerr << "Combined string is : " << combinedString << std::endl;
	};

	return false;
}

// t_file.get() reads a single byte
uint32_t MIDIParse::read_uint32(std::ifstream& t_file)
{
	// Shift the bits left
	uint32_t b1 = t_file.get();
	uint32_t b2 = t_file.get();
	uint32_t b3 = t_file.get();
	uint32_t b4 = t_file.get(); // stays in the lowest byte position

	// Combines the four bytes into a single 32 bit int using | bitwise OR
	return (b1 << 24) | (b2 << 16) | (b3 << 8) | b4;
}

uint32_t MIDIParse::read_uint16(std::ifstream& t_file)
{
	uint16_t b = 0;
	// First byte (most significant)
	// 0x1234 becomes 0x12
	uint8_t highByte = t_file.get();
	// Second byte (least significant)
	// 0x1234 becomes 0x34
	uint8_t lowByte = t_file.get();   
	
	// Combine to make a 16 bit int
	b = (highByte << 8) | lowByte;
	return b;
}

//uint16_t MIDIParse::read_uint16(std::ifstream& t_file)
//{

//}