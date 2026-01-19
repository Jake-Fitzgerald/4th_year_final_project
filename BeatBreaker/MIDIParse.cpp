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
			combinedString.resize(nbyteLength); 

			if (!file.read(combinedString.data(), nbyteLength))
			{
				std::cerr << "Error reading string\n";
				return std::string{};
			}

			std::cerr << "Combined string is: " << combinedString << std::endl;
			return combinedString;
	};

	// String headers
	//std::string header = readString(4);
	//if (header != "MThd") 
	//{
	//	std::cerr << "Not a MIDI file\n";
	//}

	return false;
}


// t_file.get() reads a single byte
uint32_t MIDIParse::read_uint32(std::ifstream& t_file)
{
	uint8_t bytes[4];
	if (!t_file.read(reinterpret_cast<char*>(bytes), 4))
	{
		std::cerr << "Error: Unexpected EOF while reading uint32\n";
		return 0; // or throw
	}

	return (uint32_t(bytes[0]) << 24) |
		(uint32_t(bytes[1]) << 16) |
		(uint32_t(bytes[2]) << 8) |
		(uint32_t(bytes[3]));
	//// Shift the bits left
	//uint32_t b1 = t_file.get();
	//uint32_t b2 = t_file.get();
	//uint32_t b3 = t_file.get();
	//uint32_t b4 = t_file.get(); // stays in the lowest byte position

	//// Combines the four bytes into a single 32 bit int using | bitwise OR
	//return (b1 << 24) | (b2 << 16) | (b3 << 8) | b4;
}

uint16_t MIDIParse::read_uint16(std::ifstream& t_file)
{
	uint8_t bytes[2];
	if (!t_file.read(reinterpret_cast<char*>(bytes), 2))
	{
		std::cerr << "Error: Unexpected EOF while reading uint16\n";
		return 0; // or throw
	}

	return (uint16_t(bytes[0]) << 8) |
		(uint16_t(bytes[1]));
	//uint16_t b = 0;
	//// First byte (most significant)
	//// 0x1234 becomes 0x12
	//uint8_t highByte = t_file.get();
	//// Second byte (least significant)
	//// 0x1234 becomes 0x34
	//uint8_t lowByte = t_file.get();   
	//
	//// Combine to make a 16 bit int
	//b = (highByte << 8) | lowByte;
	//return b;
}

uint8_t MIDIParse::readByte(std::ifstream& t_file)
{
	char byte = 0;

	// std::ifstream::read only accepts char, and uint8_t is a typedef of char
	t_file.read(&byte, sizeof(byte));

	// Convert to unsigned 8-bit value (0–255)
	return static_cast<uint8_t>(byte);
}

// VLQ will be used as our delta time to keep track 
// of how long it takes for events to come after one another
uint32_t MIDIParse::readVLQ(std::ifstream& t_file)
{
	uint32_t value = 0;
	// Hold each byte read from file
	uint8_t byte = 0;

	do
	{
		uint8_t byte = readByte(t_file);

		// Mask out the most significant bit (MSB) to get the 7 data bits
		// MSB is used as a continuation flag to know if there are more bytes
		// to follow if it's a large number.
		// 0x7F = 0111 1111 (the first number is the continuation bit)
		const uint8_t dataBits = byte & 0x7F;

		// Shift existing value 7 bits to the left to make room for new bits
		// Then OR in the new 7-bit value
		value = (value << 7) | dataBits;
	} while (byte & 0x80);
	// Loop continues while MSB is set (byte & 0x80 != 0)
	// MSB == 1 means there is another byte in the VLQ

	return value;
}

//uint16_t MIDIParse::read_uint16(std::ifstream& t_file)
//{

//}