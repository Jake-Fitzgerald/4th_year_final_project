#pragma once
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>

/*
Notes:
	Block Breaking pitch randomise
	Can set a randomised pitch and use currentSound->setPitch(random float) to change it

*/

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

	void loadBuffer(const std::string& t_name, const std::string& t_filename, SoundType t_soundType);

	// We dynamically create sound with this
	sf::Sound* getFreeSound(const sf::SoundBuffer &t_buffer);

	void play(const std::string& t_name);

	void setTypeVolume(SoundType t_type, float t_volume);
	void setDefaultVolumes();

	void randomisePitch();

private:
	// Put all of our sounds in this vector and reuse them
	//std::vector<sf::Sound> m_soundsPool;
	std::vector<std::unique_ptr<sf::Sound>> m_soundsPool;

	// Unordered is faster than ordered
	std::unordered_map<std::string, sf::SoundBuffer> m_buffersMap;

	// Sound Type
	std::unordered_map<std::string, SoundType> m_soundTypes;
	float m_typeVolumes[2];

	const int MAX_POOL_AMOUNT = 20;
};

