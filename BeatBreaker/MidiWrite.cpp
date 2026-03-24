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



    file.close();

    return false;
}

void MidiWrite::writeHeader(std::ofstream& t_file)
{
    std::string headerString = "MThd";

    t_file.write(headerString.c_str(), 4);
}
