#include "Gameplay.h"

Gameplay::Gameplay(SoundManager& t_soundManager) : m_soundManager(&t_soundManager), m_keyboard(t_soundManager)
{

}

void Gameplay::setup()
{
	setupKeyboard();
}

void Gameplay::setupKeyboard()
{
	m_keyboard.setupKeys();
	m_keyboard.setupSounds();
}

void Gameplay::update(float t_deltaTime)
{
	if (b_isPlaying == false)
	{
		return;
	}

	m_playbackTime += t_deltaTime;

	for (auto& note : m_fallingNotes)
	{
		note.shape.move(sf::Vector2f{ 0.0f, m_noteSpeed * t_deltaTime });
	}

	// Kill notes
	for (int i = static_cast<int>(m_fallingNotes.size()) - 1; i >= 0; i--)
	{
		if (m_fallingNotes[i].shape.getPosition().y > m_keyboard.getKillTriggerY())
		{
			std::cerr << "MISS: " << m_fallingNotes[i].noteName << std::endl;
			m_fallingNotes.erase(m_fallingNotes.begin() + i);
		}
	}
}

void Gameplay::render(sf::RenderWindow& t_window)
{
	for (auto& note : m_fallingNotes)
	{
		t_window.draw(note.shape);
	}

	m_keyboard.render(t_window);
}

void Gameplay::handleClick(sf::Vector2f t_mousePos)
{
	m_keyboard.handleClick(t_mousePos);
}

void Gameplay::handleRelease(sf::Vector2f t_mousePos)
{
	m_keyboard.handleRelease(t_mousePos);
}

void Gameplay::noteOn(std::string& t_noteName)
{
	m_keyboard.noteOn(t_noteName);

	for (int i = 0; i < m_fallingNotes.size(); i++)
	{
		bool b_nameMatches = m_fallingNotes[i].noteName == t_noteName;
		bool b_inHitZone = m_keyboard.checkInputCollision(m_fallingNotes[i].shape);

		if (b_nameMatches && b_inHitZone)
		{
			std::cerr << "HIT: " << t_noteName << std::endl;
			m_score += 100;
			m_fallingNotes.erase(m_fallingNotes.begin() + i);
			return;
		}
	}

	std::cerr << "WRONG KEY: " << t_noteName << std::endl;
}

void Gameplay::noteOff(std::string& t_noteName)
{
	m_keyboard.noteOff(t_noteName);
}

void Gameplay::loadTrack(MidiTrack& t_track, double t_BPM)
{
	m_currentTrack = &t_track;
	m_playbackTime = 0.0;
	m_spawnIndex = 0;
	m_fallingNotes.clear();

	m_noteSpeed = t_BPM   * m_noteSpeedMultiplier;
	std::cerr << "Note speed is: " << m_noteSpeed << std::endl;

	for (MidiNote note : t_track.midiNotes)
	{
		spawnNote(note);
	}

	std::cerr << "Gameplay loaded track: " << t_track.trackName << " | Notes: " << t_track.midiNotes.size() << std::endl;
}

void Gameplay::spawnNote(MidiNote& t_note)
{
	float keyPosX = m_keyboard.getKeyPosX(t_note.noteName);
	float timeToHit = t_note.startTime - m_playbackTime;
	float noteSpawnY = -(timeToHit * m_noteSpeed);

	bool b_isSharp = false;
	for (char c : t_note.noteName)
	{
		if (c == '#')
		{
			b_isSharp = true;
		}
	}

	FallingNote currentNote;

	currentNote.noteName = t_note.noteName;
	currentNote.b_isActive = true;

	if (b_isSharp == true)
	{
		currentNote.shape.setSize(m_sharpNoteSize);
	}
	else
	{
		currentNote.shape.setSize(m_flatNoteSize);
	}
	currentNote.shape.setFillColor(c_activeNoteColour);
	currentNote.shape.setPosition(sf::Vector2f{ keyPosX, noteSpawnY });

	m_fallingNotes.push_back(currentNote);

	std::cerr << "Spawned note: " << t_note.noteName << " at x =" << keyPosX << " y =" << noteSpawnY << std::endl;
}

void Gameplay::startSong()
{
	b_isPlaying = true;
	m_playbackTime = 0.0f;
	std::cerr << "Song started" << std::endl;
}
