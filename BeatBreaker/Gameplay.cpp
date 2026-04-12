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
	  m_anpsValueText(*font),
	  // Playback
	  m_songTimeText(*font),
	  m_songEndTimeText(*font),
	  m_previewModeText(*font),
	  m_ghostModeText(*font)
{

}

void Gameplay::setup()
{
	resetSession();

	setupKeyboard();
	setupUIFrames();

	setupScoreText();
	setupStatisticText();

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

void Gameplay::setupPlaybackText()
{
	m_songTimeText.setPosition(sf::Vector2f{ m_playbackTextPos.x, m_playbackTextPos.y });
	m_songTimeText.setString(std::to_string(m_playbackTime));
	m_songTimeText.setFillColor(sf::Color::Yellow);
	m_songTimeText.setOutlineColor(sf::Color::Black);
	m_songTimeText.setOutlineThickness(2.0f);
	m_songTimeText.setCharacterSize(30U);

	m_songEndTimeText.setPosition(sf::Vector2f{ m_playbackTextPos.x, m_playbackTextPos.y + 50.0f});
	m_songEndTimeText.setString(std::to_string(m_songEndTime));
	m_songEndTimeText.setFillColor(sf::Color::White);
	m_songEndTimeText.setOutlineColor(sf::Color::Black);
	m_songEndTimeText.setOutlineThickness(2.0f);
	m_songEndTimeText.setCharacterSize(30U);
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


	m_previewModeText.setPosition(sf::Vector2f{ scoreTextPos.x + 30.0f, scoreTextPos.y + 200.0f });
	m_previewModeText.setString("PREVIEW MODE");
	m_previewModeText.setFillColor(sf::Color::Green);
	m_previewModeText.setOutlineColor(sf::Color::Black);
	m_previewModeText.setOutlineThickness(2.0f);
	m_previewModeText.setCharacterSize(40U);

	m_ghostModeText.setPosition(sf::Vector2f{ scoreTextPos.x + 30.0f, scoreTextPos.y + 300.0f });
	m_ghostModeText.setString("GHOST MODE");
	m_ghostModeText.setFillColor(sf::Color::Magenta);
	m_ghostModeText.setOutlineColor(sf::Color::Black);
	m_ghostModeText.setOutlineThickness(2.0f);
	m_ghostModeText.setCharacterSize(40U);
}

void Gameplay::setupStatisticText()
{
	sf::Vector2f statisticTextPos{ m_statisticFrame.getPosition().x, m_statisticFrame.getPosition().y };
	float xPos = statisticTextPos.x + 25.0f;
	float yPos = statisticTextPos.y + 25.0f;
	float valueDist = 20.0f;
	float typeDist = 60.0f;

	// Missed
	m_missedNotesText.setPosition(sf::Vector2f{ xPos, yPos });
	m_missedNotesText.setString("Missed Notes: ");
	m_missedNotesText.setFillColor(sf::Color::White);
	m_missedNotesText.setOutlineColor(sf::Color::Black);
	m_missedNotesText.setOutlineThickness(2.0f);
	m_missedNotesText.setCharacterSize(20U);
	// Value
	m_missedNotesValueText.setPosition(sf::Vector2f{ xPos, yPos + valueDist });
	m_missedNotesValueText.setString("???");
	m_missedNotesValueText.setFillColor(sf::Color::White);
	m_missedNotesValueText.setOutlineColor(sf::Color::Black);
	m_missedNotesValueText.setOutlineThickness(2.0f);
	m_missedNotesValueText.setCharacterSize(20U);
	yPos += typeDist;

	// Early
	m_earlyNotesText.setPosition(sf::Vector2f{ xPos, yPos });
	m_earlyNotesText.setString("Early Notes: ");
	m_earlyNotesText.setFillColor(sf::Color::White);
	m_earlyNotesText.setOutlineColor(sf::Color::Black);
	m_earlyNotesText.setOutlineThickness(2.0f);
	m_earlyNotesText.setCharacterSize(20U);
	// Value
	m_earlyNotesValueText.setPosition(sf::Vector2f{ xPos, yPos + valueDist });
	m_earlyNotesValueText.setString("???");
	m_earlyNotesValueText.setFillColor(sf::Color::White);
	m_earlyNotesValueText.setOutlineColor(sf::Color::Black);
	m_earlyNotesValueText.setOutlineThickness(2.0f);
	m_earlyNotesValueText.setCharacterSize(20U);
	yPos += typeDist;

	// Perfect
	m_perfectNotesText.setPosition(sf::Vector2f{ xPos, yPos });
	m_perfectNotesText.setString("Perfect Notes: ");
	m_perfectNotesText.setFillColor(sf::Color::White);
	m_perfectNotesText.setOutlineColor(sf::Color::Black);
	m_perfectNotesText.setOutlineThickness(2.0f);
	m_perfectNotesText.setCharacterSize(20U);
	// Value
	m_perfectNotesValueText.setPosition(sf::Vector2f{ xPos, yPos + valueDist });
	m_perfectNotesValueText.setString("???");
	m_perfectNotesValueText.setFillColor(sf::Color::White);
	m_perfectNotesValueText.setOutlineColor(sf::Color::Black);
	m_perfectNotesValueText.setOutlineThickness(2.0f);
	m_perfectNotesValueText.setCharacterSize(20U);
	yPos += typeDist;

	// Late
	m_lateNotesText.setPosition(sf::Vector2f{ xPos, yPos });
	m_lateNotesText.setString("Late Notes: ");
	m_lateNotesText.setFillColor(sf::Color::White);
	m_lateNotesText.setOutlineColor(sf::Color::Black);
	m_lateNotesText.setOutlineThickness(2.0f);
	m_lateNotesText.setCharacterSize(20U);
	// Value
	m_lateNotesValueText.setPosition(sf::Vector2f{ xPos, yPos + valueDist });
	m_lateNotesValueText.setString("???");
	m_lateNotesValueText.setFillColor(sf::Color::White);
	m_lateNotesValueText.setOutlineColor(sf::Color::Black);
	m_lateNotesValueText.setOutlineThickness(2.0f);
	m_lateNotesValueText.setCharacterSize(20U);
	yPos += typeDist;

	// Wrong
	m_wrongNotesText.setPosition(sf::Vector2f{ xPos, yPos });
	m_wrongNotesText.setString("Wrong Notes: ");
	m_wrongNotesText.setFillColor(sf::Color::White);
	m_wrongNotesText.setOutlineColor(sf::Color::Black);
	m_wrongNotesText.setOutlineThickness(2.0f);
	m_wrongNotesText.setCharacterSize(20U);
	// Value
	m_wrongNotesValueText.setPosition(sf::Vector2f{ xPos, yPos + valueDist });
	m_wrongNotesValueText.setString("???");
	m_wrongNotesValueText.setFillColor(sf::Color::White);
	m_wrongNotesValueText.setOutlineColor(sf::Color::Black);
	m_wrongNotesValueText.setOutlineThickness(2.0f);
	m_wrongNotesValueText.setCharacterSize(20U);
	yPos += typeDist;

	// --------------------------------------------------------------------------------------------------------------

	// Hit Percentage
	m_hitpercentageText.setPosition(sf::Vector2f{ xPos, yPos });
	m_hitpercentageText.setString("Hit Percentage: ");
	m_hitpercentageText.setFillColor(sf::Color::White);
	m_hitpercentageText.setOutlineColor(sf::Color::Black);
	m_hitpercentageText.setOutlineThickness(2.0f);
	m_hitpercentageText.setCharacterSize(20U);
	// Value
	m_hitpercentageValueText.setPosition(sf::Vector2f{ xPos, yPos + valueDist });
	m_hitpercentageValueText.setString("??%");
	m_hitpercentageValueText.setFillColor(sf::Color::White);
	m_hitpercentageValueText.setOutlineColor(sf::Color::Black);
	m_hitpercentageValueText.setOutlineThickness(2.0f);
	m_hitpercentageValueText.setCharacterSize(20U);
	yPos += typeDist;

	// Hit Notes
	m_hitNotesText.setPosition(sf::Vector2f{ xPos, yPos });
	m_hitNotesText.setString("Hit Notes:");
	m_hitNotesText.setFillColor(sf::Color::White);
	m_hitNotesText.setOutlineColor(sf::Color::Black);
	m_hitNotesText.setOutlineThickness(2.0f);
	m_hitNotesText.setCharacterSize(20U);
	// Value
	m_hitNotesValueText.setPosition(sf::Vector2f{ xPos, yPos + valueDist });
	m_hitNotesValueText.setString("? / ?");
	m_hitNotesValueText.setFillColor(sf::Color::White);
	m_hitNotesValueText.setOutlineColor(sf::Color::Black);
	m_hitNotesValueText.setOutlineThickness(2.0f);
	m_hitNotesValueText.setCharacterSize(20U);
	yPos += typeDist;

	// Average Notes Per Second
	m_anpsText.setPosition(sf::Vector2f{ xPos, yPos });
	m_anpsText.setString("Avg Notes Per Second:");
	m_anpsText.setFillColor(sf::Color::White);
	m_anpsText.setOutlineColor(sf::Color::Black);
	m_anpsText.setOutlineThickness(2.0f);
	m_anpsText.setCharacterSize(20U);
	// Value
	m_anpsValueText.setPosition(sf::Vector2f{ xPos, yPos + valueDist });
	m_anpsValueText.setString("?");
	m_anpsValueText.setFillColor(sf::Color::White);
	m_anpsValueText.setOutlineColor(sf::Color::Black);
	m_anpsValueText.setOutlineThickness(2.0f);
	m_anpsValueText.setCharacterSize(20U);
}

void Gameplay::setupStatistics()
{
	m_noteCountTotal = m_fallingNotes.size();
	m_currentNotesHit = 0;
	std::cerr << "Note amount: " << m_noteCountTotal << std::endl;
	m_hitNotesValueText.setString(std::to_string(m_currentNotesHit) + " / " + std::to_string(m_noteCountTotal));
}

void Gameplay::update(float t_deltaTime)
{
	if (b_isPlaying == false)
	{
		return;
	}

	if (b_isPaused == false && b_isPracticePaused == false)
	{
		m_playbackTime += t_deltaTime;
		m_songTimeText.setString(std::to_string(m_playbackTime));

		if (b_isPlaying == true && m_playbackTime >= m_songEndTime)
		{
			b_isPlaying = false;
			b_isSongFinished = true;
			std::cerr << "Song finished" << std::endl;
		}

		for (auto& note : m_fallingNotes)
		{
			sf::Vector2f movement{ 0.0f, m_noteSpeed * t_deltaTime };
			note.shape.move(movement);
			note.earlyTrigger.move(movement);
			note.perfectTrigger.move(movement);
			note.lateTrigger.move(movement);

			if (b_isPracticeMode && note.b_isActive && m_keyboard.checkSoundCollision(note.perfectTrigger))
			{
				if (b_isPracticePaused == false)
				{
					b_isPracticePaused = true;
					m_practiceWaitForNotes.clear();

					for (auto& nextNote : m_fallingNotes)
					{
						if (nextNote.b_isActive && m_keyboard.checkSoundCollision(nextNote.perfectTrigger))
						{
							m_practiceWaitForNotes.push_back(nextNote.noteName);
						}
					}
				}
				break;
			}

			if (b_playNotesNoInput == true && b_isPracticeMode == false && b_isPreviewMode == true)
			{
				// Play note when entering the input collider
				if (note.b_isActive && m_keyboard.checkSoundCollision(note.perfectTrigger))
				{
					m_keyboard.noteOn(note.noteName);
					note.b_isActive = false;
				}
			}
		}

		m_expectedNotes.clear();
		for (auto& note : m_fallingNotes)
		{
			if (
				note.b_isActive &&
				m_keyboard.checkInputCollision(note.earlyTrigger) ||
				m_keyboard.checkInputCollision(note.perfectTrigger) ||
				m_keyboard.checkInputCollision(note.lateTrigger)
				)
			{
				m_expectedNotes.push_back(note.noteName);
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
					if (b_isPreviewMode == false)
					{
						m_score -= m_scoreMiss;
						updateScore();
						m_missedNotes++;
						updateStatistics();
					}
				}
				else
				{
					m_keyboard.noteOff(m_fallingNotes[i].noteName);
				}
				m_fallingNotes.erase(m_fallingNotes.begin() + i);
			}
		}

		// Ghost
		if (b_isGhostMode == true)
		{
			for (auto& ghostNote : m_ghostNotes)
			{
				sf::Vector2f movement{ 0.0f, m_noteSpeed * t_deltaTime };
				ghostNote.shape.move(movement);
			}
		}

		for (int i = static_cast<int>(m_ghostNotes.size()) - 1; i >= 0; i--)
		{
			if (m_ghostNotes[i].shape.getPosition().y > m_keyboard.getKillTriggerY())
			{
				m_ghostNotes.erase(m_ghostNotes.begin() + i);
			}
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
	else
	{
		m_hitpercentageValueText.setString("0%");
	}

	if (m_playbackTime > 0)
	{
		float avgNotePerSec = static_cast<float>(m_currentNotesHit) / static_cast<float>(m_playbackTime);
		m_anps = avgNotePerSec;
		//m_anpsValueText.setString(std::to_string(static_cast<int>(m_anps)));
		m_anpsValueText.setString(std::to_string(std::roundf(m_anps * 100) / 100));
	}
}

void Gameplay::resetSession()
{
	m_playbackTime = 0.0;
	//m_songEndTime = 0.0f;
	b_isSongFinished = false;
	b_isPlaying = false;
	m_fallingNotes.clear();
	m_ghostNotes.clear();
	b_isPaused = false;
	b_isPracticePaused = false;
	m_practiceWaitForNotes.clear();
	m_recordedNotes.clear();

	if (m_currentTrack != nullptr)
	{
		for (MidiNote note : m_currentTrack->midiNotes)
		{
			spawnNote(note);
		}
	}

	resetScore();
	resetStatistics();
	updateStatistics();
}

void Gameplay::resetScore()
{
	m_score = 0;
	m_currentScoreValueText.setString(std::to_string(m_score));

	//m_pbScoreValueText.setString(std::to_string(...));
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

int Gameplay::getScore()
{
	return m_score;
}

SessionStats Gameplay::getSessionStats()
{
	return SessionStats
	{
		m_score,
		m_earlyNotes,
		m_perfectNotes,
		m_lateNotes,
		m_missedNotes,
		m_wrongNotes,
		m_noteCountTotal,
		m_currentNotesHit,
		m_anps
	};
}

void Gameplay::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_scoreFrame);
	
	if (b_isPreviewMode == false)
	{
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
		t_window.draw(m_perfectNotesText);
		t_window.draw(m_perfectNotesValueText);
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
	}
	else
	{
		t_window.draw(m_previewModeText);
	}

	for (auto& note : m_fallingNotes)
	{
		t_window.draw(note.shape);
	}

	if (b_isGhostMode == true)
	{
		for (auto& ghostNote : m_ghostNotes)
		{
			t_window.draw(ghostNote.shape);
		}

		t_window.draw(m_ghostModeText);
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

		// Playback Text
		t_window.draw(m_songTimeText);
		t_window.draw(m_songEndTimeText);
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

void Gameplay::noteOn(std::string& t_noteName, int t_pitch, int t_velocity)
{
	if (b_isPaused == true)
	{
		return;
	}

	if (b_isRecording == true && b_isPlaying == true && b_isPracticePaused == false && b_isPreviewMode == false)
	{
		MidiNote note;
		note.noteName = t_noteName;
		note.pitch = t_pitch;
		note.velocity = t_velocity;
		note.startTime = m_playbackTime;

		std::cerr << "Recording note: " << t_noteName << " at playbackTime: " << m_playbackTime << std::endl;

		m_recordedNotes.push_back(note);
	}

	m_keyboard.noteOn(t_noteName);

	bool b_isNoteInSong = false;
	bool b_wasTriggered = false;

	for (int i = 0; i < m_fallingNotes.size(); i++)
	{
		if (m_fallingNotes[i].noteName == t_noteName)
		{
			b_isNoteInSong = true;
		}

		if (m_fallingNotes[i].b_isActive == false)
		{
			continue;
		}

		bool b_nameMatches = m_fallingNotes[i].noteName == t_noteName;

		if (b_nameMatches)
		{
			if (m_keyboard.checkInputCollision(m_fallingNotes[i].lateTrigger))						   // LATE
			{
				std::cerr << "LATE: " << t_noteName << std::endl;
				if (b_isPreviewMode == false)
				{
					// Score
					m_score += m_scoreLate;
					updateScore();
					// Statistics
					m_currentNotesHit++;
					m_lateNotes++;
					updateStatistics();
				}

				m_fallingNotes[i].shape.setFillColor(c_lateNoteColour);
				m_fallingNotes[i].b_isActive = false;

				for (int j = 0; j < m_practiceWaitForNotes.size(); j++)
				{
					if (m_practiceWaitForNotes[j] == t_noteName)
					{
						m_practiceWaitForNotes.erase(m_practiceWaitForNotes.begin() + j);
						break;
					}
				}
				if (m_practiceWaitForNotes.empty())
				{
					b_isPracticePaused = false;
				}

				return;
			}
			else if (m_keyboard.checkInputCollision(m_fallingNotes[i].perfectTrigger))						// PERFECT
			{
				std::cerr << "PERFECT: " << t_noteName << std::endl;
				if (b_isPreviewMode == false)
				{
					// Score
					m_score += m_scorePerfect;
					updateScore();
					// Statistics
					m_currentNotesHit++;
					m_perfectNotes++;
					updateStatistics();
				}

				m_fallingNotes[i].shape.setFillColor(c_perfectNoteColour);
				m_fallingNotes[i].b_isActive = false;

				for (int j = 0; j < m_practiceWaitForNotes.size(); j++)
				{
					if (m_practiceWaitForNotes[j] == t_noteName)
					{
						m_practiceWaitForNotes.erase(m_practiceWaitForNotes.begin() + j);
						break;
					}
				}
				if (m_practiceWaitForNotes.empty())
				{
					b_isPracticePaused = false;
				}
				return;
			}
			else if (m_keyboard.checkInputCollision(m_fallingNotes[i].earlyTrigger))						       // EARLY
			{
				std::cerr << "EARLY: " << t_noteName << std::endl;
				if (b_isPreviewMode == false)
				{
					// Score
					m_score += m_scoreEarly;
					updateScore();
					// Statistics
					m_currentNotesHit++;
					m_earlyNotes++;
					updateStatistics();
				}

				m_fallingNotes[i].shape.setFillColor(c_earlyNoteColour);
				m_fallingNotes[i].b_isActive = false;

				for (int j = 0; j < m_practiceWaitForNotes.size(); j++)
				{
					if (m_practiceWaitForNotes[j] == t_noteName)
					{
						m_practiceWaitForNotes.erase(m_practiceWaitForNotes.begin() + j);
						break;
					}
				}
				if (m_practiceWaitForNotes.empty())
				{
					b_isPracticePaused = false;
				}
				return;
			}

			bool b_isExpected = std::find(m_expectedNotes.begin(), m_expectedNotes.end(), t_noteName) != m_expectedNotes.end();

			if (!b_isExpected && b_isPreviewMode == false)
			{
				m_score -= m_scoreWrong;
				updateScore();
				m_wrongNotes++;
				updateStatistics();
			}
			// Stop looking for other notes that are the same value
			break;
		}
	}

	if (b_isNoteInSong == false && b_isPreviewMode == false)
	{
		m_score -= m_scoreWrong;
		updateScore();
		m_wrongNotes++;
		updateStatistics();
	}
}

void Gameplay::noteOff(std::string& t_noteName, int t_pitch, int t_velocity)
{
	//if (b_isPaused == true && b_isPracticePaused == true)
	if (b_isPaused == true || b_isPracticePaused == true)
	{
		return;
	}

	m_keyboard.noteOff(t_noteName);

	if (b_isRecording == true && b_isPlaying == true && b_isPracticePaused == false && b_isPreviewMode == false)
	{
		for (int i = m_recordedNotes.size() - 1; i >= 0; i--)
		{
			if (m_recordedNotes[i].noteName == t_noteName && m_recordedNotes[i].endTime == 0.0)
			{
				m_recordedNotes[i].endTime = m_playbackTime;
				break;
			}
		}
	}
}

void Gameplay::loadTrack(MidiTrack& t_track, double t_BPM)
{
	m_currentTrack = &t_track;
	m_playbackTime = 0.0;
	m_fallingNotes.clear();
	b_isSongFinished = false;

	m_noteSpeed = t_BPM /** m_noteSpeedMultiplier*/;
	std::cerr << "Note speed is: " << m_noteSpeed << std::endl;

	if (!t_track.midiNotes.empty())
	{
		MidiNote finalNote = t_track.midiNotes.back();

		double soundTriggerY = static_cast<double>(m_keyboard.getSoundNoteTriggerY());
		double travelTime = soundTriggerY / m_noteSpeed;

		m_songEndTime = finalNote.endTime + travelTime /*+ m_songEndWaitTime*/;
		std::cerr << "Song End Time is: " << m_songEndTime << std::endl;
	}

	for (MidiNote note : t_track.midiNotes)
	{
		spawnNote(note);
	}

	setupStatistics();
	setupPlaybackText();
}

void Gameplay::loadGhostTrack(MidiTrack& t_track, double t_BPM)						
{
	m_ghostNotes.clear();

	if (t_track.midiNotes.empty())
	{
		std::cerr << "Ghost track is empty" << std::endl;
		return;
	}

	double travelTime = static_cast<double>(m_keyboard.getSoundNoteTriggerY()) / m_noteSpeed;
	std::cerr << "Ghost travelTime offset: " << travelTime << std::endl;

	for (auto ghostNote : t_track.midiNotes)
	{
		ghostNote.startTime -= travelTime;
		ghostNote.endTime -= travelTime;
		spawnGhostNote(ghostNote);
	}

	std::cerr << "Ghost notes loaded with size: " << m_ghostNotes.size() << std::endl;
	std::cerr << "Ghost BPM: " << t_BPM << std::endl;
}

void Gameplay::spawnNote(MidiNote& t_note)
{
	float keyPosX = m_keyboard.getKeyPosX(t_note.noteName);
	float timeToHit = t_note.startTime - m_playbackTime;
	
	// Note length
	float noteDuration = t_note.endTime - t_note.startTime;
	float noteHeight = noteDuration * m_noteSpeed;

	float noteSpawnY = -(timeToHit * m_noteSpeed) - noteHeight;

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

	float keyboardY = m_keyboard.getSoundNoteTriggerY();
	std::cerr << "Note: " << t_note.noteName
		<< " startTime: " << t_note.startTime
		<< " spawnY: " << noteSpawnY
		<< " keyboardY: " << keyboardY
		<< " travelTime: " << keyboardY / m_noteSpeed
		<< " difference: " << t_note.startTime - (keyboardY / m_noteSpeed) << std::endl;

	m_fallingNotes.push_back(currentNote);
}

void Gameplay::spawnGhostNote(MidiNote& t_note)
{
	float keyPosX = m_keyboard.getKeyPosX(t_note.noteName);
	float timeToHit = t_note.startTime - m_playbackTime;

	// Note length
	float noteDuration = t_note.endTime - t_note.startTime;
	float noteHeight = noteDuration * m_noteSpeed;

	float noteSpawnY = -(timeToHit * m_noteSpeed) - noteHeight;

	std::cerr << "Ghost note: " << t_note.noteName
		<< " startTime: " << t_note.startTime
		<< " timeToHit: " << timeToHit
		<< " noteHeight: " << noteHeight
		<< " spawnY: " << noteSpawnY
		<< " speed: " << m_noteSpeed << std::endl;

	bool b_isSharp = false;
	for (char c : t_note.noteName)
	{
		if (c == '#')
		{
			b_isSharp = true;
		}
	}

	FallingNote ghostNote;

	ghostNote.noteName = t_note.noteName;
	ghostNote.b_isActive = true;

	if (b_isSharp == true)
	{
		ghostNote.shape.setSize(sf::Vector2f{ m_sharpNoteSize.x, noteHeight });
	}
	else
	{
		ghostNote.shape.setSize(sf::Vector2f{ m_flatNoteSize.x, noteHeight });
	}
	ghostNote.shape.setFillColor(c_ghostNoteColour);
	ghostNote.shape.setPosition(sf::Vector2f{ keyPosX, noteSpawnY });
	ghostNote.shape.setOutlineColor(sf::Color::White);
	ghostNote.shape.setOutlineThickness(5.0f);

	m_ghostNotes.push_back(ghostNote);
}

void Gameplay::startSong()
{
	b_isPlaying = true;
	m_playbackTime = 0.0f;
	std::cerr << "Song started" << std::endl;
}

void Gameplay::togglePause()
{
	if (b_isPaused == true)
	{
		b_isPaused = false;
	}
	else
	{
		b_isPaused = true;
	}
}

bool Gameplay::getPausedFlag()
{
	return b_isPaused;
}

void Gameplay::setPracticeModeFlag(bool t_bool)
{
	b_isPracticeMode = t_bool;
}

bool Gameplay::getPracticeModeFlag()
{
	return b_isPracticeMode;
}

void Gameplay::setRecordingFlag(bool t_bool)
{
	b_isRecording = t_bool;
}

bool Gameplay::getRecordingFlag()
{
	return b_isRecording;
}

void Gameplay::setPreviewModeFlag(bool t_bool)
{
	b_isPreviewMode = t_bool;
}

bool Gameplay::getPreviewModeFlag()
{
	return b_isPreviewMode;
}

void Gameplay::setGhostModeFlag(bool t_bool)
{
	b_isGhostMode = t_bool;
}

bool Gameplay::getGhostModeFlag()
{
	return b_isGhostMode;
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
	m_keyboard.setEasyInputFlag(b_easyInputMode);
}

bool Gameplay::getTriggerDisplayFlag()
{
	return b_displayTriggers;
}

void Gameplay::setTriggerDisplayFlag(bool t_bool)
{
	b_displayTriggers = t_bool;
	m_keyboard.setDebug(b_displayTriggers);
}

bool Gameplay::getSongFinishedFlag()
{
	return b_isSongFinished;
}

std::vector<MidiNote> Gameplay::getRecordedNotes()
{
	return m_recordedNotes;
}

void Gameplay::setSongName(std::string t_name)
{
	m_songName = t_name;
}

std::string Gameplay::getSongName()
{
	return m_songName;
}
