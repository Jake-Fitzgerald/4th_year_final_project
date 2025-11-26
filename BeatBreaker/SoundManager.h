#pragma once
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>

// Sound
enum class SoundType
{
	SFX,
	MUSIC
};

class SoundManager
{
public:
	SoundManager(int t_poolSize = 10);

	void loadBuffer(const std::string& t_name, const std::string& t_filename);

	// We dynamically create sound with this
	sf::Sound* getFreeSound(const sf::SoundBuffer &t_buffer);

	void play(const std::string& t_name, SoundType t_soundType);

private:
	// Put all of our sounds in this vector and reuse them
	//std::vector<sf::Sound> m_soundsPool;
	std::vector<std::unique_ptr<sf::Sound>> m_soundsPool;

	// Unordered is faster than ordered
	std::unordered_map<std::string, sf::SoundBuffer> m_buffersMap;

	const int TOTAL_SOUNDS = 10;

	
};

