#include "MidiWrite.h"

MidiWrite::MidiWrite()
{

}

//MidiWrite::MidiWrite(std::string& t_fileName)
//{
//	writeFile(t_fileName);
//}


bool MidiWrite::writeFile(std::string& t_fileName)
{
    std::ofstream file;

    std::string pathWithFile = m_drectoryPath + t_fileName + ".midi";

    file.open(pathWithFile, std::ofstream::out | std::ofstream::binary);

    if (!file.is_open())
    {
        std::cerr << "Failed to open MIDI file [CREATED]" << std::endl;
        return false;
    }
    std::cerr << "Created a midi file" << std::endl;

    writeHeader(file);
    writeTimeSigTrack(file);
    writeTempoTrack(file);


    file.close();

    return false;
}

void MidiWrite::writeHeader(std::ofstream& t_file)
{
    std::string headerString = "MThd";
    t_file.write(headerString.c_str(), 4);

    write_uint32(t_file, 6); // Header Length
    write_uint16(t_file, 1); // Version
    write_uint16(t_file, 3); // Track count
    write_uint16(t_file, 96); // Ticks per quarter note
}

void MidiWrite::writeTimeSigTrack(std::ofstream& t_file)
{
    std::string trackString = "MTrk";
    t_file.write(trackString.c_str(), 4);

    write_uint32(t_file, 12); // Time Sig Length

    writeByte(t_file, 0x00); // delta
    writeByte(t_file, EventType::metaEvent);
    writeByte(t_file, EventType::timeSignature);

    writeByte(t_file, 0x04); // Meta length
    writeByte(t_file, 0x04); // Numerator
    writeByte(t_file, 0x02); // Denominator
    writeByte(t_file, 0x18); // Ticks per click
    writeByte(t_file, 0x08); // Thirty seconds per crotchet

    writeByte(t_file, 0x00); // delta
    writeByte(t_file, EventType::metaEvent);
    writeByte(t_file, EventType::endOfTrack); 
    writeByte(t_file, 0x00); // Meta length
}

void MidiWrite::writeTempoTrack(std::ofstream& t_file)
{
    std::string trackString = "MTrk";
    t_file.write(trackString.c_str(), 4);

    write_uint32(t_file, 11); // Tempo Length

    writeByte(t_file, 0x00);
    writeByte(t_file, EventType::metaEvent);
    writeByte(t_file, EventType::tempo);
    writeByte(t_file, 0x03); // Meta length
    
    writeMicroSeconds(t_file); // uint24
    writeByte(t_file, 0x00);
    writeByte(t_file, EventType::metaEvent);
    writeByte(t_file, EventType::endOfTrack);
    writeByte(t_file, 0x00); // Meta length

}

void MidiWrite::write_uint32(std::ofstream& t_file, uint32_t t_value)
{
    uint8_t bytes[4];

    (bytes[0] = t_value >> 24);
    (bytes[1] = t_value >> 16);
    (bytes[2] = t_value >> 8);
    (bytes[3] = t_value );

    if (!t_file.write(reinterpret_cast<char*>(bytes), 4))
    {
        std::cerr << "Error: can't write uint32" << std::endl;
    }
}

void MidiWrite::write_uint16(std::ofstream& t_file, uint16_t t_value)
{
    uint8_t bytes[2];

    (bytes[0] = t_value >> 8);
    (bytes[1] = t_value);

    if (!t_file.write(reinterpret_cast<char*>(bytes), 2))
    {
        std::cerr << "Error: can't write uint16" << std::endl;
    }
}

void MidiWrite::writeByte(std::ofstream& t_file, uint8_t t_value)
{
    char byte = static_cast<char>(t_value);

    t_file.write(&byte, sizeof(byte));
}

void MidiWrite::writeMicroSeconds(std::ofstream& t_file)
{
    uint32_t microsecondsPerClick = 60000000.0 / m_BPM;

    uint8_t firstByte = (microsecondsPerClick >> 16);
    uint8_t secondByte = (microsecondsPerClick >> 8);
    uint8_t thirdByte = (microsecondsPerClick);

    writeByte(t_file, firstByte);
    writeByte(t_file, secondByte);
    writeByte(t_file, thirdByte);

    std::cerr << "===================" << std::endl;
    std::cerr << "[ Tempo ]" << std::endl;
    std::cerr << "===================" << std::endl;
    std::cerr << "Tempo: " << m_BPM << ", BPM :" << microsecondsPerClick << " (microseconds)" << std::endl;
}
