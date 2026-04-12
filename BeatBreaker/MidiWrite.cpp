#include "MidiWrite.h"

MidiWrite::MidiWrite() 
{
    
}

bool MidiWrite::writeFile(std::string& t_fileName)
{
    std::ofstream file;

    //std::string pathWithFile = m_drectoryPath + t_fileName + ".midi";
    std::string pathWithFile = m_drectoryPath + t_fileName + ".mid";

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
    //calculateTrackLength();
    writeNoteTrack(file);

    file.close();

    return true;
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

    writeEndOfTrack(t_file);
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
    
    writeEndOfTrack(t_file);

}

void MidiWrite::writeNoteTrack(std::ofstream& t_file)
{
    m_trackBuffer.clear();

    writeCCToBuffer();

    // ------------------------------
    std::vector<MidiEvent> noteEvents;
    noteEvents.reserve(m_recordedNotes.size() * 2);

    for (auto& note : m_recordedNotes)
    {
        std::cerr << "Adding to events - pitch: " << (int)note.pitch
            << " startTick: " << note.startTick
            << " endTick: " << note.endTick << std::endl;

        noteEvents.push_back({ note.startTick, true, static_cast<uint8_t>(note.pitch), static_cast<uint8_t>(note.velocity) });
        noteEvents.push_back({ note.endTick, false, static_cast<uint8_t>(note.pitch), static_cast<uint8_t>(note.velocity) });
    }


    for (int i = 0; i < noteEvents.size(); i++)
    {
        for (int j = 0; j < noteEvents.size() - 1; j++)
        {
            bool b_inWrongOrder = false;

            if (noteEvents[j].tick > noteEvents[j + 1].tick)
            {
                b_inWrongOrder = true;
            }
            else if (noteEvents[j].tick == noteEvents[j + 1].tick)
            {
                // Note off must come before note on
                if (noteEvents[j].b_isNoteOn == true && noteEvents[j + 1].b_isNoteOn == false)
                {
                    b_inWrongOrder = true;
                }
            }

            if (b_inWrongOrder == true)
            {
                MidiEvent midiEventTemp = noteEvents[j];
                noteEvents[j] = noteEvents[j + 1];
                noteEvents[j + 1] = midiEventTemp;
            }
        }
    }

    // ------------------------------
    // Write even to buffer
    // ------------------------------

    uint32_t previousTick = 0;

    for (auto& event : noteEvents)
    {
        uint32_t delta = event.tick - previousTick;
        previousTick = event.tick;

        if (event.b_isNoteOn == true)
        {
            writeNoteOnToBuffer(event.pitch, event.velocity, delta);
        }
        else
        {
            writeNoteOffToBuffer(event.pitch, event.velocity, delta);
        }
    }

    writeCCToBuffer();

    // ------------------------------
    // Write track chunk
    // ------------------------------

    uint32_t noteDataSize = static_cast<uint32_t>(m_trackBuffer.size());

    std::string trackString = "MTrk";
    t_file.write(trackString.c_str(), 4);
    // 11 + 54 + notes + 4
    //write_uint32(t_file, m_noteTrackNameLength + m_ccLength + noteDataSize + m_endOfTrackLength); 
    write_uint32(t_file, m_noteTrackNameLength + noteDataSize + m_endOfTrackLength);

    writeByte(t_file, 0x00);
    writeByte(t_file, EventType::metaEvent);
    writeByte(t_file, EventType::trackName);

    writeByte(t_file, 0x07); // Meta length
    t_file.write("FL Keys", 7);

    //writeCC(t_file);

    // Note buffer
    for (uint8_t byte : m_trackBuffer)
    {
        writeByte(t_file, byte);
    }

    //writeCC(t_file);

    writeEndOfTrack(t_file);

    std::cerr << "Completed writing midi file" << std::endl;
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

void MidiWrite::writeByteToBuffer(uint8_t t_value)
{
    m_trackBuffer.push_back(t_value);
}

void MidiWrite::writeMicroSeconds(std::ofstream& t_file)
{
    std::cerr << "writeMicroSeconds using BPM: " << m_BPM << std::endl;

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

void MidiWrite::writeCC(std::ofstream& t_file)
{
    writeByte(t_file, 0x00);
    writeByte(t_file, EventType::controlChange);
    writeByte(t_file, EventType::pan);
    writeByte(t_file, 0x40);
    m_ccCounter += 4;

    writeByte(t_file, 0x00);
    writeByte(t_file, EventType::controlChange);
    writeByte(t_file, EventType::volume);
    writeByte(t_file, 0x64);
    m_ccCounter += 4;

    writeByte(t_file, 0x00);
    writeByte(t_file, EventType::pitchBend);
    writeByte(t_file, 0x00); // byte 1
    writeByte(t_file, 0x40); // byte 2
    m_ccCounter += 4;

    writeByte(t_file, 0x00);
    writeByte(t_file, EventType::controlChange);
    writeByte(t_file, EventType::regParamNum_MSB);
    writeByte(t_file, 0x00); // regParamNum Value
    m_ccCounter += 4;

    writeByte(t_file, 0x00);
    writeByte(t_file, EventType::controlChange);
    writeByte(t_file, EventType::regParamNum_LSB);
    writeByte(t_file, 0x00); // regParamNum Value
    m_ccCounter += 4;

    writeByte(t_file, 0x00);
    writeByte(t_file, EventType::controlChange);
    writeByte(t_file, EventType::dataEntry);
    writeByte(t_file, 0x0C);
    m_ccCounter += 4;

    writeProgamChange(t_file);
}

void MidiWrite::writeCCToBuffer()
{
writeByteToBuffer(0x00);
    writeByteToBuffer(EventType::controlChange);
    writeByteToBuffer(EventType::pan);
    writeByteToBuffer(0x40);

    writeByteToBuffer(0x00);
    writeByteToBuffer(EventType::controlChange);
    writeByteToBuffer(EventType::volume);
    writeByteToBuffer(0x64);

    writeByteToBuffer(0x00);
    writeByteToBuffer(EventType::pitchBend);
    writeByteToBuffer(0x00);
    writeByteToBuffer(0x40);

    writeByteToBuffer(0x00);
    writeByteToBuffer(EventType::controlChange);
    writeByteToBuffer(EventType::regParamNum_MSB);
    writeByteToBuffer(0x00);

    writeByteToBuffer(0x00);
    writeByteToBuffer(EventType::controlChange);
    writeByteToBuffer(EventType::regParamNum_LSB);
    writeByteToBuffer(0x00);

    writeByteToBuffer(0x00);
    writeByteToBuffer(EventType::controlChange);
    writeByteToBuffer(EventType::dataEntry);
    writeByteToBuffer(0x0C);

    writeProgramChangeToBuffer();
}

void MidiWrite::writeProgamChange(std::ofstream& t_file)
{
    writeByte(t_file, 0x00);
    writeByte(t_file, EventType::programChange);
    writeByte(t_file, 0x00); // Instrument
    m_ccCounter += 3;
}

void MidiWrite::writeProgramChangeToBuffer()
{
    writeByteToBuffer(0x00);
    writeByteToBuffer(EventType::programChange);
    writeByteToBuffer(0x00);
}

void MidiWrite::writeNoteOn(std::ofstream& t_file, uint8_t t_pitch, uint8_t t_velocity, uint32_t t_deltatime)
{
    writeVLQ(t_file, t_deltatime);
    writeByte(t_file, EventType::noteOn);
    writeByte(t_file, t_pitch);
    writeByte(t_file, t_velocity);
}

void MidiWrite::writeNoteOnToBuffer(uint8_t t_pitch, uint8_t t_velocity, uint32_t t_deltatime)
{
    writeVLQToBuffer(t_deltatime);
    writeByteToBuffer(EventType::noteOn);
    writeByteToBuffer(t_pitch);
    writeByteToBuffer(t_velocity);
}

void MidiWrite::writeNoteOff(std::ofstream& t_file, uint8_t t_pitch, uint8_t t_velocity, uint32_t t_deltatime)
{
    writeVLQ(t_file, t_deltatime);
    writeByte(t_file, EventType::noteOff);
    writeByte(t_file, t_pitch);
    writeByte(t_file, t_velocity);
}

void MidiWrite::writeNoteOffToBuffer(uint8_t t_pitch, uint8_t t_velocity, uint32_t t_deltatime)
{
    writeVLQToBuffer(t_deltatime);
    writeByteToBuffer(EventType::noteOff);
    writeByteToBuffer(t_pitch);
    writeByteToBuffer(t_velocity);
}

void MidiWrite::writeEndOfTrack(std::ofstream& t_file)
{
    writeByte(t_file, 0x00); // delta
    writeByte(t_file, EventType::metaEvent);
    writeByte(t_file, EventType::endOfTrack);
    writeByte(t_file, 0x00); // Meta length
}

void MidiWrite::writeVLQ(std::ofstream& t_file, uint32_t t_value)
{
    // VLQ value is always 4 bytes -> 28 bits
    uint8_t bytes[5];
    int count = 0;

    std::cerr << "Writing VLQ value: " << t_value << std::endl;

    do
    {
        bytes[count++] = t_value & 0x7F;
        t_value = t_value / 128;
    } while (t_value > 0);

    // Write reversed
    for (int i = count - 1; i >= 0; i--)
    {
        uint8_t byte = bytes[i];
        if (i > 0)
        {
            byte = byte | 0x80;
        }

        writeByte(t_file,byte);
    }
}

void MidiWrite::writeVLQToBuffer(uint32_t t_value)
{
    // VLQ value is always 4 bytes -> 28 bits
    uint8_t bytes[5];
    int count = 0;

    std::cerr << "Writing VLQ value: " << t_value << std::endl;

    do
    {
        bytes[count++] = t_value & 0x7F;
        t_value = t_value / 128;

        //uint8_t chunk = t_value & vlqSize;
        //t_value = t_value / 128;

        //if (t_value == 0)
        //{
        //    // The last byte
        //}
        //else
        //{
        //    bytes[count++] = t_value & 0x7F;
        //    t_value = t_value / 128;
        //}
    } while (t_value > 0);

    // Write reversed
    for (int i = count - 1; i >= 0; i--)
    {
        uint8_t byte = bytes[i];
        if (i > 0)
        {
            byte = byte | 0x80;
        }

        writeByteToBuffer(byte);
    }
}

void MidiWrite::setupRecordedNotes(std::vector<MidiNote>& t_notes)
{
    m_recordedNotes = t_notes;

    double ticksPerSecond = (m_BPM / 60.0f) * m_quarterNoteLength;

    std::cerr << "BPM: " << m_BPM << " ticksPerSecond: " << ticksPerSecond << std::endl;

    for (auto& note : m_recordedNotes)
    {
        note.startTick = static_cast<uint32_t>(note.startTime * ticksPerSecond);
        note.endTick = static_cast<uint32_t>(note.endTime * ticksPerSecond);


        std::cerr << note.noteName
            << " startTime: " << note.startTime
            << " -> startTick: " << note.startTick
            << std::endl;
    }

    for (int i = 0; i < m_recordedNotes.size(); i++)
    {
        for (int j = 0; j < m_recordedNotes.size() - 1; j++)
        {
            if (m_recordedNotes[j].startTick > m_recordedNotes[j + 1].startTick)
            {
                MidiNote midiNoteTemp = m_recordedNotes[j];
                m_recordedNotes[j] = m_recordedNotes[j + 1];
                m_recordedNotes[j + 1] = midiNoteTemp;
            }
        }
    }
}

void MidiWrite::setBPM(double t_BPM)
{
    m_BPM = t_BPM;
}
