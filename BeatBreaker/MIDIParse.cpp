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
	//uint32_t test_uint32 = read_uint32(file);
	//std::cerr << "32 uint is: " << test_uint32 << std::endl;
	// Shift 16 bit int
	//uint16_t test_uint16 = read_uint16(file);
	//std::cerr << "16 uint is: " << test_uint16 << std::endl;

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
	
	// Parse Header Chunk
	std::string header = readString(4);
	// Check if it is a MIDI file if it contains MThd at the start
	if (header != "MThd")
	{
		std::cerr << "Not a MIDI file" << std::endl;
		return false;
	}
	else
	{
		std::cerr << "It is a valid MIDI file" << std::endl;
		//parseHeader(file);
	}


	// Header Chunk Data
	std::cerr << "==================" << std::endl;
	std::cerr << "===== Header =====" << std::endl;
	std::cerr << "==================" << std::endl;
	m_headerLength = read_uint32(file); // should be 6
	std::cerr << "Header Length: " << m_headerLength << std::endl;

	m_midiFormat = read_uint16(file);
	std::cerr << "Format: " << m_midiFormat << std::endl;

	m_numTracks = read_uint16(file);
	std::cerr << "Number of tracks: " << m_numTracks << std::endl;

	// Ticks per quarter (delta time ticks within a quarter note)
	// delta time is the number of ticks since the last event, in this case the note.
	m_ticksPerQuarter = read_uint16(file);
	std::cerr << "Ticks per Quarter Note: " << m_ticksPerQuarter << std::endl;

	// Track Chunk Data (Time Signature)
	std::string trackHeader = readString(4);
	if (trackHeader != "MTrk")
	{
		std::cerr << "Invalid track header" << std::endl;
		return false;
	}
	else
	{
		std::cerr << "It is a valid Track" << std::endl;
	}

	std::cerr << "===================" << std::endl;
	//std::cerr << "===== Track 1 =====" << std::endl;
	std::cerr << "[ Time Signature ]" << std::endl;
	std::cerr << "===================" << std::endl;

	uint32_t trackLength = read_uint32(file); // number of bytes in this track
	std::cerr << "Time Signature Byte Length: " << trackLength << std::endl;

	// tellg() is like a bookmark for where in the file we are reading from
	// https://www.geeksforgeeks.org/cpp/tellg-function-c-example/
	std::streampos trackStart = file.tellg();  // current file position
	std::cerr << "Track Start: " << trackStart << std::endl;

	// Streamposition is where we are, streamoffset is where we move to

	std::streampos trackEnd = trackStart + static_cast<std::streamoff>(trackLength);
	std::cerr << "Track End: " << trackEnd << std::endl;

	// Meta Events
	// https://ccrma.stanford.edu/~craig/14q/midifile/MidiFileFormat.html#track_event

	// Look at everything within this Track Chunk
	while (file.tellg() < trackEnd)
	{
		// Read the deltatime (time between each event)
		uint32_t deltaTime = readVLQ(file);

		// Read status byte
		uint8_t status = readByte(file);

		// Meta event (start of where the Track's meta event is)
		if (status == EventType::metaEvent)
		{
			// The meta type is which byte we are looking at
			uint8_t metaType = readByte(file);
			
			// Tells us how many byte to read for the event
			uint32_t length = readVLQ(file);

			if (metaType == EventType::timeSignature && length == 4) // Time Signature
			{
				uint8_t nom = readByte(file);
				uint8_t denom = readByte(file);
				// Useless data for DAWs
				uint8_t clocksPerMetronomeClick = readByte(file); 
				uint8_t thirtyTwoSecsPerQuarter = readByte(file); // 32 seconds per crotchet (quarter note) 

				m_nominator = nom;
				m_denominator = 1 << denom;

				std::cerr << "Time Signature: " << m_nominator << "/" << m_denominator << std::endl;

				// Combine them to make a string we can display more easily in other scenes
				m_timeSignature = std::to_string(m_nominator) + "/" + std::to_string(m_denominator);

				break;
			}
			else
			{
				file.ignore(length); // skip other meta events
			}
		}
		else
		{
			// running status checks?
		}

	}
	// Put into our vector of Midi Tracks
	midiTracks.push_back(MidiTrack());

	// Track Chunk Data (Tempo)
	// to do...

	return false;
}

void MIDIParse::parseHeader()
{
	std::cerr << "=== Header ===" << std::endl;


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

	return (uint16_t(bytes[0]) << 8) | (uint16_t(bytes[1]));
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
		byte = readByte(t_file);

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