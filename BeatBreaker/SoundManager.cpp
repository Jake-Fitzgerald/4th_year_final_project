#include "SoundManager.h"

SoundManager::SoundManager(int t_poolSize)
{
	m_soundsPool.reserve(t_poolSize);
    setDefaultVolumes();
}

void SoundManager::loadBuffer(const std::string& t_name, const std::string& t_filename, SoundType t_soundType)
{
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(t_filename)) 
    {
        std::cerr << "[SoundManager] failed to load: " << t_filename << std::endl;
        return;
    }

    // Put the buffer into the map
    m_buffersMap[t_name] = std::move(buffer);
    // Assign type
    m_soundTypes[t_name] = t_soundType;
}

sf::Sound* SoundManager::getFreeSound(const sf::SoundBuffer &t_buffer)
{
    // Check if our pool is too big
    if (m_soundsPool.size() >= MAX_POOL_AMOUNT)
    {
        return nullptr; 
    }

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

void SoundManager::play(const std::string& t_name)
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
    // Second is the buffer in the map, first is the name
    sf::Sound* currentSound = getFreeSound(it->second);
    // Check is there any sounds free
    if (!currentSound)
    {
        std::cerr << "No free sounds left!" << std::endl;
        return;
    }

    // Check what type it is
    SoundType currentType = m_soundTypes[t_name];
    float volume = m_typeVolumes[static_cast<int>( currentType)];
    currentSound->setVolume(volume);

    currentSound->play();
}

void SoundManager::setTypeVolume(SoundType t_type, float t_volume)
{
    m_typeVolumes[static_cast<int>(t_type)] = t_volume;
}

void SoundManager::setDefaultVolumes()
{
    setTypeVolume(SoundType::SFX, 100.0f);
    setTypeVolume(SoundType::MUSIC, 100.0f);
}

void SoundManager::randomisePitch()
{
    // to do for Block breaking sound
}
