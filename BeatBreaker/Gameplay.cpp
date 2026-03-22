#include "Gameplay.h"

Gameplay::Gameplay(SoundManager& t_soundManager, std::shared_ptr<const sf::Font> font)
	: m_soundManager(&t_soundManager),
	  m_keyboard(t_soundManager),
	  m_statisticFrameText(*font),
	  m_scoreFrameText(*font),
	  // Score
	  m_currentScoreText(*font),
	  m_currentScoreValueText(*font),
	  m_pbScoreText(*font),
	  m_pbScoreValueText(*font),
	  // Statistics 1
	  m_missedNotesText(*font),
	  m_missedNotesValueText(*font),
	  m_earlyNotesText(*font),
	  m_earlyNotesValueText(*font),
	  m_perfectNotesText(*font),
	  m_perfectNotesValueText(*font),
	  m_lateNotesText(*font),
	  m_lateNotesValueText(*font),
	  m_wrongNotesText(*font),
	  m_wrongNotesValueText(*font),
	  // Statistics 2
	  m_hitpercentageText(*font),
	  m_hitpercentageValueText(*font),
	  m_hitNotesText(*font),
	  m_hitNotesValueText(*font),
	  m_anpsText(*font),
	  m_anpsValueText(*font)
{

}

void Gameplay::setup()
{
	setupKeyboard();
	setupUIFrames();

	// Text
	setupScoreText();
	setupStatisticText();

	// Update Text
	updateScore();
}

void Gameplay::setupKeyboard()
{
	m_keyboard.setupKeys();
	m_keyboard.setupSounds();
}

void Gameplay::setupUIFrames()
{
	m_scoreFrame.setSize(m_frameSize);
	m_scoreFrame.setPosition(sf::Vector2f{ paddingX - 25.0f, paddingY + 50.0f });
	m_scoreFrame.setFillColor(c_frameColour);
	m_scoreFrame.setOutlineThickness(2.0f);
	m_scoreFrame.setOutlineColor(sf::Color::Black);
	// Text
	m_scoreFrameText.setPosition(sf::Vector2f{ m_scoreFrame.getPosition().x + 25.0f, m_scoreFrame.getPosition().y - 60.0f });
	m_scoreFrameText.setString("SCORE");
	m_scoreFrameText.setFillColor(sf::Color::White);
	m_scoreFrameText.setOutlineColor(sf::Color::Black);
	m_scoreFrameText.setOutlineThickness(2.0f);
	m_scoreFrameText.setCharacterSize(50U);

	m_statisticFrame.setSize(m_frameSize);
	m_statisticFrame.setPosition(sf::Vector2f{ paddingX + 925.0f, paddingY + 50.0f });
	m_statisticFrame.setFillColor(c_frameColour);
	m_statisticFrame.setOutlineThickness(2.0f);
	m_statisticFrame.setOutlineColor(sf::Color::Black);
	// Text
	m_statisticFrameText.setPosition(sf::Vector2f{ m_statisticFrame.getPosition().x + 25.0f, m_statisticFrame.getPosition().y - 60.0f });
	m_statisticFrameText.setString("STATISTICS");
	m_statisticFrameText.setFillColor(sf::Color::White);
	m_statisticFrameText.setOutlineColor(sf::Color::Black);
	m_statisticFrameText.setOutlineThickness(2.0f);
	m_statisticFrameText.setCharacterSize(50U);
}

void Gameplay::setupScoreText()
{
	sf::Vector2f scoreTextPos{ m_scoreFrame.getPosition().x, m_scoreFrame.getPosition().y };

	m_currentScoreText.setPosition(sf::Vector2f{ scoreTextPos.x + 25.0f, scoreTextPos.y + 25.0f});
	m_currentScoreText.setString("Score: ");
	m_currentScoreText.setFillColor(sf::Color::White);
	m_currentScoreText.setOutlineColor(sf::Color::Black);
	m_currentScoreText.setOutlineThickness(2.0f);
	m_currentScoreText.setCharacterSize(30U);
	// Value
	m_currentScoreValueText.setPosition(sf::Vector2f{ scoreTextPos.x + 25.0f, scoreTextPos.y + 50.0f });
	m_currentScoreValueText.setString("0");
	m_currentScoreValueText.setFillColor(sf::Color::White);
	m_currentScoreValueText.setOutlineColor(sf::Color::Black);
	m_currentScoreValueText.setOutlineThickness(2.0f);
	m_currentScoreValueText.setCharacterSize(30U);

	// Personal Best
	m_pbScoreText.setPosition(sf::Vector2f{ scoreTextPos.x + 25.0f, scoreTextPos.y + 100.0f });
	m_pbScoreText.setString("Personal Best: ");
	m_pbScoreText.setFillColor(sf::Color::White);
	m_pbScoreText.setOutlineColor(sf::Color::Black);
	m_pbScoreText.setOutlineThickness(2.0f);
	m_pbScoreText.setCharacterSize(30U);
	// Value
	m_pbScoreValueText.setPosition(sf::Vector2f{ scoreTextPos.x + 25.0f, scoreTextPos.y + 125.0f });
	m_pbScoreValueText.setString("888");
	m_pbScoreValueText.setFillColor(sf::Color::White);
	m_pbScoreValueText.setOutlineColor(sf::Color::Black);
	m_pbScoreValueText.setOutlineThickness(2.0f);
	m_pbScoreValueText.setCharacterSize(30U);
}

void Gameplay::setupStatisticText()
{
	sf::Vector2f statisticTextPos{ m_statisticFrame.getPosition().x, m_statisticFrame.getPosition().y };

	// Missed
	m_missedNotesText.setPosition(sf::Vector2f{ statisticTextPos.x + 25.0f, statisticTextPos.y + 25.0f });
	m_missedNotesText.setString("Missed Notes: ");
	m_missedNotesText.setFillColor(sf::Color::White);
	m_missedNotesText.setOutlineColor(sf::Color::Black);
	m_missedNotesText.setOutlineThickness(2.0f);
	m_missedNotesText.setCharacterSize(30U);
	// Value
	m_missedNotesValueText.setPosition(sf::Vector2f{ statisticTextPos.x + 25.0f, statisticTextPos.y + 50.0f });
	m_missedNotesValueText.setString("???");
	m_missedNotesValueText.setFillColor(sf::Color::White);
	m_missedNotesValueText.setOutlineColor(sf::Color::Black);
	m_missedNotesValueText.setOutlineThickness(2.0f);
	m_missedNotesValueText.setCharacterSize(30U);

	// Early
	m_earlyNotesText.setPosition(sf::Vector2f{ statisticTextPos.x + 25.0f, statisticTextPos.y + 100.0f });
	m_earlyNotesText.setString("Early Notes: ");
	m_earlyNotesText.setFillColor(sf::Color::White);
	m_earlyNotesText.setOutlineColor(sf::Color::Black);
	m_earlyNotesText.setOutlineThickness(2.0f);
	m_earlyNotesText.setCharacterSize(30U);
	// Value
	m_earlyNotesValueText.setPosition(sf::Vector2f{ statisticTextPos.x + 25.0f, statisticTextPos.y + 125.0f });
	m_earlyNotesValueText.setString("???");
	m_earlyNotesValueText.setFillColor(sf::Color::White);
	m_earlyNotesValueText.setOutlineColor(sf::Color::Black);
	m_earlyNotesValueText.setOutlineThickness(2.0f);
	m_earlyNotesValueText.setCharacterSize(30U);

	// Late
	m_lateNotesText.setPosition(sf::Vector2f{ statisticTextPos.x + 25.0f, statisticTextPos.y + 175.0f });
	m_lateNotesText.setString("Late Notes: ");
	m_lateNotesText.setFillColor(sf::Color::White);
	m_lateNotesText.setOutlineColor(sf::Color::Black);
	m_lateNotesText.setOutlineThickness(2.0f);
	m_lateNotesText.setCharacterSize(30U);
	// Value
	m_lateNotesValueText.setPosition(sf::Vector2f{ statisticTextPos.x + 25.0f, statisticTextPos.y + 200.0f });
	m_lateNotesValueText.setString("???");
	m_lateNotesValueText.setFillColor(sf::Color::White);
	m_lateNotesValueText.setOutlineColor(sf::Color::Black);
	m_lateNotesValueText.setOutlineThickness(2.0f);
	m_lateNotesValueText.setCharacterSize(30U);

	// Wrong
	m_wrongNotesText.setPosition(sf::Vector2f{ statisticTextPos.x + 25.0f, statisticTextPos.y + 250.0f });
	m_wrongNotesText.setString("Wrong Notes: ");
	m_wrongNotesText.setFillColor(sf::Color::White);
	m_wrongNotesText.setOutlineColor(sf::Color::Black);
	m_wrongNotesText.setOutlineThickness(2.0f);
	m_wrongNotesText.setCharacterSize(30U);
	// Value
	m_wrongNotesValueText.setPosition(sf::Vector2f{ statisticTextPos.x + 25.0f, statisticTextPos.y + 275.0f });
	m_wrongNotesValueText.setString("???");
	m_wrongNotesValueText.setFillColor(sf::Color::White);
	m_wrongNotesValueText.setOutlineColor(sf::Color::Black);
	m_wrongNotesValueText.setOutlineThickness(2.0f);
	m_wrongNotesValueText.setCharacterSize(30U);

	// --------------------------------------------------------------------------------------------------------------

	// Hit Percentage
	m_hitpercentageText.setPosition(sf::Vector2f{ statisticTextPos.x + 25.0f, statisticTextPos.y + 325.0f });
	m_hitpercentageText.setString("Hit Percentage: %");
	m_hitpercentageText.setFillColor(sf::Color::White);
	m_hitpercentageText.setOutlineColor(sf::Color::Black);
	m_hitpercentageText.setOutlineThickness(2.0f);
	m_hitpercentageText.setCharacterSize(30U);
	// Value
	m_hitpercentageValueText.setPosition(sf::Vector2f{ statisticTextPos.x + 25.0f, statisticTextPos.y + 350.0f });
	m_hitpercentageValueText.setString("??%");
	m_hitpercentageValueText.setFillColor(sf::Color::White);
	m_hitpercentageValueText.setOutlineColor(sf::Color::Black);
	m_hitpercentageValueText.setOutlineThickness(2.0f);
	m_hitpercentageValueText.setCharacterSize(30U);

	// Hit Notes
	m_hitNotesText.setPosition(sf::Vector2f{ statisticTextPos.x + 25.0f, statisticTextPos.y + 375.0f });
	m_hitNotesText.setString("Hit Notes:");
	m_hitNotesText.setFillColor(sf::Color::White);
	m_hitNotesText.setOutlineColor(sf::Color::Black);
	m_hitNotesText.setOutlineThickness(2.0f);
	m_hitNotesText.setCharacterSize(30U);
	// Value
	m_hitNotesValueText.setPosition(sf::Vector2f{ statisticTextPos.x + 25.0f, statisticTextPos.y + 400.0f });
	m_hitNotesValueText.setString("? / ?");
	m_hitNotesValueText.setFillColor(sf::Color::White);
	m_hitNotesValueText.setOutlineColor(sf::Color::Black);
	m_hitNotesValueText.setOutlineThickness(2.0f);
	m_hitNotesValueText.setCharacterSize(30U);

	// Average Notes Per Second
	m_anpsText.setPosition(sf::Vector2f{ statisticTextPos.x + 25.0f, statisticTextPos.y + 425.0f });
	m_anpsText.setString("Avg Notes Per Second:");
	m_anpsText.setFillColor(sf::Color::White);
	m_anpsText.setOutlineColor(sf::Color::Black);
	m_anpsText.setOutlineThickness(2.0f);
	m_anpsText.setCharacterSize(30U);
	// Value
	m_anpsValueText.setPosition(sf::Vector2f{ statisticTextPos.x + 25.0f, statisticTextPos.y + 450.0f });
	m_anpsValueText.setString("?");
	m_anpsValueText.setFillColor(sf::Color::White);
	m_anpsValueText.setOutlineColor(sf::Color::Black);
	m_anpsValueText.setOutlineThickness(2.0f);
	m_anpsValueText.setCharacterSize(30U);
}

void Gameplay::setupStatistics()
{
	m_noteCountTotal = m_fallingNotes.size();
	m_currentNotesHit = m_fallingNotes.size();
	std::cerr << "Note amount: " << m_noteCountTotal << std::endl;
	m_hitNotesValueText.setString(std::to_string(m_currentNotesHit) + " / " + std::to_string(m_noteCountTotal));
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
		//note.shape.move(sf::Vector2f{ 0.0f, m_noteSpeed * t_deltaTime });
		sf::Vector2f movement{ 0.0f, m_noteSpeed * t_deltaTime };
		note.shape.move(movement);
		note.earlyTrigger.move(movement);
		note.perfectTrigger.move(movement);
		note.lateTrigger.move(movement);

		if (b_playNotesNoInput)
		{
			// Play note when entering the input collider
			if (note.b_isActive && m_keyboard.checkInputCollision(note.shape))
			{
				m_keyboard.noteOn(note.noteName);
				note.b_isActive = false;
			}
		}
	}

	// Kill notes
	for (int i = static_cast<int>(m_fallingNotes.size()) - 1; i >= 0; i--)
	{
		if (m_fallingNotes[i].shape.getPosition().y > m_keyboard.getKillTriggerY())
		{
			if (m_fallingNotes[i].b_isActive == true)
			{
				std::cerr << "MISS: " << std::endl;
				m_score -= m_scoreMiss;
				updateScore();
				m_missedNotes++;
				updateStatistics();
			}
			else
			{
				m_keyboard.noteOff(m_fallingNotes[i].noteName);
			}
			//std::cerr << "MISS: " << m_fallingNotes[i].noteName << std::endl;
			m_fallingNotes.erase(m_fallingNotes.begin() + i);
		}
	}
}

void Gameplay::updateScore()
{
	m_currentScoreValueText.setString(std::to_string(m_score));
}

void Gameplay::updateStatistics()
{
	// Statistics 1
	m_earlyNotesValueText.setString(std::to_string(m_earlyNotes));
	m_perfectNotesValueText.setString(std::to_string(m_perfectNotes));
	m_lateNotesValueText.setString(std::to_string(m_lateNotes));
	m_missedNotesValueText.setString(std::to_string(m_missedNotes));
	m_wrongNotesValueText.setString(std::to_string(m_wrongNotes));
	
	// Statistics 2
	m_hitNotesValueText.setString(std::to_string(m_currentNotesHit) + " / " + std::to_string(m_noteCountTotal));

	// Note Percentage
	if (m_noteCountTotal > 0)
	{
		float hitPercentage = (static_cast<float>(m_currentNotesHit) / static_cast<float>(m_noteCountTotal)) * 100.0f;
		m_hitpercentageValueText.setString(std::to_string(static_cast<int>(hitPercentage)) + "%");
	}
}

void Gameplay::resetSession()
{
	resetScore();
	resetStatistics();
}

void Gameplay::resetScore()
{
	m_score = 0;
}

void Gameplay::resetStatistics()
{
	m_earlyNotes = 0;
	m_perfectNotes = 0;
	m_lateNotes = 0;
	m_missedNotes = 0;
	m_wrongNotes = 0;

	m_noteCountTotal = 0;
	m_currentNotesHit = 0;
}

void Gameplay::render(sf::RenderWindow& t_window)
{
	// UI
	t_window.draw(m_scoreFrame);
	t_window.draw(m_statisticFrame);
	t_window.draw(m_scoreFrameText);
	t_window.draw(m_statisticFrameText);

	// Score Text
	t_window.draw(m_currentScoreText);
	t_window.draw(m_currentScoreValueText);
	t_window.draw(m_pbScoreText);
	t_window.draw(m_pbScoreValueText);

	// Statistic Text 1
	t_window.draw(m_missedNotesText);
	t_window.draw(m_missedNotesValueText);
	t_window.draw(m_earlyNotesText);
	t_window.draw(m_earlyNotesValueText);
	t_window.draw(m_lateNotesText);
	t_window.draw(m_lateNotesValueText);
	t_window.draw(m_wrongNotesText);
	t_window.draw(m_wrongNotesValueText);
	// Statistic Text 2
	t_window.draw(m_hitpercentageText);
	t_window.draw(m_hitpercentageValueText);
	t_window.draw(m_hitNotesText);
	t_window.draw(m_hitNotesValueText);
	t_window.draw(m_anpsText);
	t_window.draw(m_anpsValueText);

	for (auto& note : m_fallingNotes)
	{
		t_window.draw(note.shape);
	}

	m_keyboard.render(t_window);

	// Triggers
	if (b_displayTriggers == true)
	{
		for (auto& note : m_fallingNotes)
		{
			t_window.draw(note.earlyTrigger);
			t_window.draw(note.perfectTrigger);
			t_window.draw(note.lateTrigger);
		}
	}

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
		if (m_fallingNotes[i].b_isActive == false)
		{
			continue;
		}

		bool b_nameMatches = m_fallingNotes[i].noteName == t_noteName;
		//bool b_inHitZone = m_keyboard.checkInputCollision(m_fallingNotes[i].shape);

		if (b_nameMatches)
		{
			if (m_keyboard.checkInputCollision(m_fallingNotes[i].earlyTrigger))
			{
				std::cerr << "EARLY: " << t_noteName << std::endl;
				// Score
				m_score += m_scoreEarly;
				updateScore();
				// Statistics
				m_currentNotesHit++;
				m_earlyNotes++;
				updateStatistics();

				m_fallingNotes[i].shape.setFillColor(c_earlyNoteColour);
				m_fallingNotes[i].b_isActive = false;
				return;
			}
			if (m_keyboard.checkInputCollision(m_fallingNotes[i].perfectTrigger))
			{
				std::cerr << "PERFECT: " << t_noteName << std::endl;
				// Score
				m_score += m_scorePerfect;
				updateScore();
				// Statistics
				m_currentNotesHit++;
				m_perfectNotes++;
				updateStatistics();

				m_fallingNotes[i].shape.setFillColor(c_perfectNoteColour);
				m_fallingNotes[i].b_isActive = false;
				return;
			}
			if (m_keyboard.checkInputCollision(m_fallingNotes[i].lateTrigger))
			{
				std::cerr << "LATE: " << t_noteName << std::endl;
				// Score
				m_score += m_scoreLate;
				updateScore();
				// Statistics
				m_currentNotesHit++;
				m_lateNotes++;
				updateStatistics();

				m_fallingNotes[i].shape.setFillColor(c_lateNoteColour);
				m_fallingNotes[i].b_isActive = false;
				return;
			}

			//std::cerr << "MISS: " << t_noteName << std::endl;
			//m_score -= m_scoreMiss;
			//updateScore();
		}
	}

	std::cerr << "WRONG KEY: " << t_noteName << std::endl;
	m_score -= m_scoreWrong;
	updateScore();
	m_wrongNotes++;
	updateStatistics();

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

	m_noteSpeed = t_BPM /** m_noteSpeedMultiplier*/;
	std::cerr << "Note speed is: " << m_noteSpeed << std::endl;

	for (MidiNote note : t_track.midiNotes)
	{
		spawnNote(note);
	}

	setupStatistics();
}

void Gameplay::spawnNote(MidiNote& t_note)
{
	float keyPosX = m_keyboard.getKeyPosX(t_note.noteName);
	float timeToHit = t_note.startTime - m_playbackTime;
	float noteSpawnY = -(timeToHit * m_noteSpeed);

	// Note length
	float noteDuration = t_note.endTime - t_note.startTime;
	float noteHeight = noteDuration * m_noteSpeed;

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
		currentNote.shape.setSize(sf::Vector2f{ m_sharpNoteSize.x, noteHeight });
	}
	else
	{
		currentNote.shape.setSize(sf::Vector2f{ m_flatNoteSize.x, noteHeight });
	}
	currentNote.shape.setFillColor(c_activeNoteColour);
	currentNote.shape.setPosition(sf::Vector2f{ keyPosX, noteSpawnY });
	currentNote.shape.setOutlineColor(sf::Color::Black);
	currentNote.shape.setOutlineThickness(2.0f);

	// --------------------------------------------------------------------------------
	// Triggers
	
	
	//float triggerHeight = 40.0f;
	float triggerHeight = noteHeight / 3.0f;
	float noteWidth = m_flatNoteSize.x - 15.0f;

	if (b_isSharp == true)
	{
		noteWidth = m_sharpNoteSize.x - 15.0f;
	}

	sf::Vector2f triggerSize{ noteWidth, triggerHeight };
	sf::Vector2f notePos{ currentNote.shape.getPosition() };
	sf::Vector2f noteBottomLeft{ notePos.x, notePos.y + noteHeight };

	// Early
	currentNote.earlyTrigger.setSize(triggerSize);
	currentNote.earlyTrigger.setFillColor(c_earlyTriggerColour);
	currentNote.earlyTrigger.setPosition(sf::Vector2f{ notePos.x, noteBottomLeft.y });

	// Perfect
	currentNote.perfectTrigger.setSize(triggerSize);
	currentNote.perfectTrigger.setFillColor(c_perfectTriggerColour);
	currentNote.perfectTrigger.setPosition(sf::Vector2f{ notePos.x, noteBottomLeft.y - triggerHeight});

	// Late
	currentNote.lateTrigger.setSize(triggerSize);
	currentNote.lateTrigger.setFillColor(c_lateTriggerColour);
	currentNote.lateTrigger.setPosition(sf::Vector2f{ notePos.x, noteBottomLeft.y - triggerHeight * 2});

	m_fallingNotes.push_back(currentNote);
	//std::cerr << "Spawned note: " << t_note.noteName << " at x =" << keyPosX << " y =" << noteSpawnY << std::endl;
}

void Gameplay::startSong()
{
	b_isPlaying = true;
	m_playbackTime = 0.0f;
	std::cerr << "Song started" << std::endl;
}

bool Gameplay::getNoteOnColliderFlag()
{
	return b_playNotesNoInput;
}

void Gameplay::setNoteOnColliderFlag(bool t_bool)
{
	b_playNotesNoInput = t_bool;
}

bool Gameplay::getEasyInputFlag()
{
	return b_easyInputMode;
}

void Gameplay::setEasyInputFlag(bool t_bool)
{
	b_easyInputMode = t_bool;
}

bool Gameplay::getTriggerDisplayFlag()
{
	return b_displayTriggers;
}

void Gameplay::setTriggerDisplayFlag(bool t_bool)
{
	b_displayTriggers = t_bool;
}
