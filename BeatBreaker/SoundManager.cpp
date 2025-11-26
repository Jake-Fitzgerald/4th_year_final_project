#include "SoundManager.h"

SoundManager::SoundManager(int t_poolSize)
{
	m_soundsPool.reserve(t_poolSize);
}

void SoundManager::loadBuffer(const std::string& t_name, const std::string& t_filename)
{
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(t_filename)) 
    {
        std::cerr << "[SoundManager] failed to load: " << t_filename << std::endl;
        return;
    }

    // Put the buffer into the map
    m_buffersMap[t_name] = std::move(buffer);
}

sf::Sound* SoundManager::getFreeSound(const sf::SoundBuffer &t_buffer)
{
    // Loop through all of the sounds
    for (std::size_t i = 0; i < m_soundsPool.size(); ++i) 
    {
        // Find if there's one there and if that one after stopping
        if (m_soundsPool[i] && m_soundsPool[i]->getStatus() == sf::Sound::Status::Stopped)
        {
            // Stop playing
            m_soundsPool[i]->stop();
            // Assign it to the new buffer
            m_soundsPool[i]->setBuffer(t_buffer);
            // Return the pointer to free sound
            return m_soundsPool[i].get();
        }
    }

    std::unique_ptr<sf::Sound> newSound = std::make_unique<sf::Sound>(t_buffer);
    sf::Sound* pointer = newSound.get();
    // Put it into the pool
    m_soundsPool.push_back(std::move(newSound));

    // Return the new sound
    return pointer;
}

void SoundManager::play(const std::string& t_name, SoundType t_soundType)
{
    // Look through and find the sound buffer's name in the map
    auto it = m_buffersMap.find(t_name);
    // If it's not found (.end after the end of the map)
    if (it == m_buffersMap.end())
    {
        std::cerr << "[SoundManager] don't know the name of this sound: " << t_name << "\n";
        return;
    }

    // Grab a free sound
    sf::Sound* currentSound = getFreeSound(it->second);
    // Check is there any sounds free
    if (!currentSound)
    {
        std::cerr << "No free sounds left!" << std::endl;
        return;
    }

    // Make sure it's not playing incase the check above is buggy
   // currentSound->stop();
    // Second is the buffer in the map, first is the name
   // currentSound->setBuffer(it->second);
    currentSound->setVolume(100.0f);

    currentSound->play();
    std::cerr << "SOUND played" << std::endl;
}
