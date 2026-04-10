#include "GameOver.h"

GameOver::GameOver(std::shared_ptr<const sf::Font> font, Database& t_database)
	: m_titleText(*font),
	  m_scoreText(*font),
	  m_scoreValueText(*font),
	  m_pbScoreText(*font),
	  m_pbScoreValueText(*font),
	  m_saveMidiButtonText(*font),
	  m_saveServerButtonText(*font),
	  m_songNameText(*font),
	  m_saveServerField(font, m_serverFieldPos, m_fieldSize, m_characterSize),
	  m_saveMidiField(font, m_midiFieldPos, m_fieldSize, m_characterSize),
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
	  // Database
	  m_database(&t_database)
{
	resetSessionStats();

	m_saveServerField.setPlaceholderString("Write to server...");
	m_saveMidiField.setPlaceholderString("Write to midi...");

	m_saveServerField.setMaxLength(m_maxLength);
	m_saveMidiField.setMaxLength(m_maxLength);

	setupFieldButtons();
}

void GameOver::setupGameOver()
{
	setupUIFrames();
	setupText();
	setupStatisticText();
}

void GameOver::setupUIFrames()
{
	m_scoreUIFrame.setSize(m_frameScoreSize);
	m_scoreUIFrame.setPosition(sf::Vector2f{ paddingX + 100.0f, paddingY + 100.0f });
	m_scoreUIFrame.setFillColor(c_scoreFrameColour);
	m_scoreUIFrame.setOutlineThickness(4.0f);
	m_scoreUIFrame.setOutlineColor(sf::Color::Black);

	m_statisticUIFrame.setSize(m_frameStatsSize);
	m_statisticUIFrame.setPosition(sf::Vector2f{ paddingX + 500.0f, paddingY + 100.0f });
	m_statisticUIFrame.setFillColor(c_statisticFrameColour);
	m_statisticUIFrame.setOutlineThickness(4.0f);
	m_statisticUIFrame.setOutlineColor(sf::Color::Black);

	m_statisticFrameBorder.setSize(sf::Vector2f{ 5.0f, 325.0f });
	m_statisticFrameBorder.setPosition(sf::Vector2f{ m_statisticUIFrame.getPosition().x + 205.0f, m_statisticUIFrame.getPosition().y + 30.0f });
	m_statisticFrameBorder.setFillColor(c_statisticBorderColour);
}

void GameOver::setupText()
{
	m_titleText.setPosition(m_titlePos);
	m_titleText.setString("RESULTS");
	m_titleText.setFillColor(sf::Color::White);
	m_titleText.setOutlineColor(sf::Color::Black);
	m_titleText.setOutlineThickness(2.0f);
	m_titleText.setCharacterSize(50U);

	sf::Vector2f scoreTextPos{ m_scoreUIFrame.getPosition().x, m_scoreUIFrame.getPosition().y };

	m_scoreText.setPosition(sf::Vector2f{ scoreTextPos.x + 25.0f, scoreTextPos.y + 25.0f });
	m_scoreText.setString("Score: ");
	m_scoreText.setFillColor(sf::Color::White);
	m_scoreText.setOutlineColor(sf::Color::Black);
	m_scoreText.setOutlineThickness(2.0f);
	m_scoreText.setCharacterSize(30U);
	// Value
	m_scoreValueText.setPosition(sf::Vector2f{ scoreTextPos.x + 25.0f, scoreTextPos.y + 50.0f });
	m_scoreValueText.setString("0");
	m_scoreValueText.setFillColor(sf::Color::White);
	m_scoreValueText.setOutlineColor(sf::Color::Black);
	m_scoreValueText.setOutlineThickness(2.0f);
	m_scoreValueText.setCharacterSize(30U);

	m_pbScoreText.setPosition(sf::Vector2f{ scoreTextPos.x + 25.0f, scoreTextPos.y + 100.0f });
	m_pbScoreText.setString("Personal Best: ");
	m_pbScoreText.setFillColor(sf::Color::White);
	m_pbScoreText.setOutlineColor(sf::Color::Black);
	m_pbScoreText.setOutlineThickness(2.0f);
	m_pbScoreText.setCharacterSize(30U);
	// Value
	m_pbScoreValueText.setPosition(sf::Vector2f{ scoreTextPos.x + 25.0f, scoreTextPos.y + 125.0f });
	m_pbScoreValueText.setString("0");
	m_pbScoreValueText.setFillColor(sf::Color::White);
	m_pbScoreValueText.setOutlineColor(sf::Color::Black);
	m_pbScoreValueText.setOutlineThickness(2.0f);
	m_pbScoreValueText.setCharacterSize(30U);

	// Song Name
	m_songNameText.setPosition(sf::Vector2f{ scoreTextPos.x + 25.0f, scoreTextPos.y + 0.0f });
	m_songNameText.setString(m_songName);
	m_songNameText.setFillColor(sf::Color(200, 250, 200, 220));
	m_songNameText.setOutlineColor(sf::Color::Black);
	m_songNameText.setOutlineThickness(2.0f);
	m_songNameText.setCharacterSize(30U);
}

void GameOver::setupServerField()
{
	
}

void GameOver::setupMidiField()
{

}

void GameOver::setupFieldButtons()
{
	m_saveServerButton.setPosition({ m_serverFieldPos.x + 400, m_serverFieldPos.y });
	m_saveServerButton.setSize(m_buttonSize);
	m_saveServerButton.setFillColor(c_inactiveColour);
	m_saveServerButton.setOutlineColor(sf::Color::Black);
	m_saveServerButton.setOutlineThickness(2.0f);
	m_saveServerButtonText.setString("SAVE");
	m_saveServerButtonText.setPosition({ m_saveServerButton.getPosition().x + 20.0f, m_saveServerButton.getPosition().y - 12.0f });
	m_saveServerButtonText.setFillColor(sf::Color::White);
	m_saveServerButtonText.setOutlineColor(sf::Color::Black);
	m_saveServerButtonText.setOutlineThickness(2.0f);
	m_saveServerButtonText.setCharacterSize(50U);

	m_saveMidiButton.setPosition({ m_midiFieldPos.x + 400, m_midiFieldPos.y });
	m_saveMidiButton.setSize(m_buttonSize);
	m_saveMidiButton.setFillColor(c_inactiveColour);
	m_saveMidiButton.setOutlineColor(sf::Color::Black);
	m_saveMidiButton.setOutlineThickness(2.0f);
	m_saveMidiButtonText.setString("SAVE");
	m_saveMidiButtonText.setPosition({ m_saveMidiButton.getPosition().x + 20.0f, m_saveMidiButton.getPosition().y - 12.0f });
	m_saveMidiButtonText.setFillColor(sf::Color::White);
	m_saveMidiButtonText.setOutlineColor(sf::Color::Black);
	m_saveMidiButtonText.setOutlineThickness(2.0f);
	m_saveMidiButtonText.setCharacterSize(50U);
}

void GameOver::setSongName(std::string t_name)
{
	m_songName = t_name;
	m_songNameText.setString(m_songName);
	m_saveMidiField.setPlaceholderString(m_songName);
}

void GameOver::updateScore()
{

}

void GameOver::updatePBScore()
{
	if (m_score > m_pbScore)
	{
		m_pbScore = m_score;
		m_pbScoreValueText.setString(std::to_string(m_pbScore));
	}
}

void GameOver::saveScore()
{
}

void GameOver::setRecordedNotes(std::vector<MidiNote> t_notes)
{
	m_midiWrite.setupRecordedNotes(t_notes);
}

void GameOver::setupStatisticText()
{
	sf::Vector2f statisticTextPos{ m_statisticUIFrame.getPosition().x, m_statisticUIFrame.getPosition().y };
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
	m_missedNotesText.setCharacterSize(26U);
	// Value
	m_missedNotesValueText.setPosition(sf::Vector2f{ xPos, yPos + valueDist });
	m_missedNotesValueText.setString("???");
	m_missedNotesValueText.setFillColor(sf::Color::White);
	m_missedNotesValueText.setOutlineColor(sf::Color::Black);
	m_missedNotesValueText.setOutlineThickness(2.0f);
	m_missedNotesValueText.setCharacterSize(26U);
	yPos += typeDist;

	// Early
	m_earlyNotesText.setPosition(sf::Vector2f{ xPos, yPos });
	m_earlyNotesText.setString("Early Notes: ");
	m_earlyNotesText.setFillColor(sf::Color::White);
	m_earlyNotesText.setOutlineColor(sf::Color::Black);
	m_earlyNotesText.setOutlineThickness(2.0f);
	m_earlyNotesText.setCharacterSize(26U);
	// Value
	m_earlyNotesValueText.setPosition(sf::Vector2f{ xPos, yPos + valueDist });
	m_earlyNotesValueText.setString("???");
	m_earlyNotesValueText.setFillColor(sf::Color::White);
	m_earlyNotesValueText.setOutlineColor(sf::Color::Black);
	m_earlyNotesValueText.setOutlineThickness(2.0f);
	m_earlyNotesValueText.setCharacterSize(26U);
	yPos += typeDist;

	// Perfect
	m_perfectNotesText.setPosition(sf::Vector2f{ xPos, yPos });
	m_perfectNotesText.setString("Perfect Notes: ");
	m_perfectNotesText.setFillColor(sf::Color::White);
	m_perfectNotesText.setOutlineColor(sf::Color::Black);
	m_perfectNotesText.setOutlineThickness(2.0f);
	m_perfectNotesText.setCharacterSize(26U);
	// Value
	m_perfectNotesValueText.setPosition(sf::Vector2f{ xPos, yPos + valueDist });
	m_perfectNotesValueText.setString("???");
	m_perfectNotesValueText.setFillColor(sf::Color::White);
	m_perfectNotesValueText.setOutlineColor(sf::Color::Black);
	m_perfectNotesValueText.setOutlineThickness(2.0f);
	m_perfectNotesValueText.setCharacterSize(26U);
	yPos += typeDist;

	// Late
	m_lateNotesText.setPosition(sf::Vector2f{ xPos, yPos });
	m_lateNotesText.setString("Late Notes: ");
	m_lateNotesText.setFillColor(sf::Color::White);
	m_lateNotesText.setOutlineColor(sf::Color::Black);
	m_lateNotesText.setOutlineThickness(2.0f);
	m_lateNotesText.setCharacterSize(26U);
	// Value
	m_lateNotesValueText.setPosition(sf::Vector2f{ xPos, yPos + valueDist });
	m_lateNotesValueText.setString("???");
	m_lateNotesValueText.setFillColor(sf::Color::White);
	m_lateNotesValueText.setOutlineColor(sf::Color::Black);
	m_lateNotesValueText.setOutlineThickness(2.0f);
	m_lateNotesValueText.setCharacterSize(26U);
	yPos += typeDist;

	// Wrong
	m_wrongNotesText.setPosition(sf::Vector2f{ xPos, yPos });
	m_wrongNotesText.setString("Wrong Notes: ");
	m_wrongNotesText.setFillColor(sf::Color::White);
	m_wrongNotesText.setOutlineColor(sf::Color::Black);
	m_wrongNotesText.setOutlineThickness(2.0f);
	m_wrongNotesText.setCharacterSize(26U);
	// Value
	m_wrongNotesValueText.setPosition(sf::Vector2f{ xPos, yPos + valueDist });
	m_wrongNotesValueText.setString("???");
	m_wrongNotesValueText.setFillColor(sf::Color::White);
	m_wrongNotesValueText.setOutlineColor(sf::Color::Black);
	m_wrongNotesValueText.setOutlineThickness(2.0f);
	m_wrongNotesValueText.setCharacterSize(26U);
	yPos += typeDist;

	// --------------------------------------------------------------------------------------------------------------

	float secondStatColDist = 220.0f;
	float yPos2 = statisticTextPos.y + 25.0f;

	// Hit Percentage
	m_hitpercentageText.setPosition(sf::Vector2f{ xPos + secondStatColDist, yPos2 });
	m_hitpercentageText.setString("Hit Percentage: ");
	m_hitpercentageText.setFillColor(sf::Color::White);
	m_hitpercentageText.setOutlineColor(sf::Color::Black);
	m_hitpercentageText.setOutlineThickness(2.0f);
	m_hitpercentageText.setCharacterSize(24U);
	// Value
	m_hitpercentageValueText.setPosition(sf::Vector2f{ xPos + secondStatColDist, yPos2 + valueDist });
	m_hitpercentageValueText.setString("??%");
	m_hitpercentageValueText.setFillColor(sf::Color::White);
	m_hitpercentageValueText.setOutlineColor(sf::Color::Black);
	m_hitpercentageValueText.setOutlineThickness(2.0f);
	m_hitpercentageValueText.setCharacterSize(24U);
	yPos2 += typeDist;

	// Hit Notes
	m_hitNotesText.setPosition(sf::Vector2f{ xPos + secondStatColDist, yPos2 });
	m_hitNotesText.setString("Hit Notes:");
	m_hitNotesText.setFillColor(sf::Color::White);
	m_hitNotesText.setOutlineColor(sf::Color::Black);
	m_hitNotesText.setOutlineThickness(2.0f);
	m_hitNotesText.setCharacterSize(24U);
	// Value
	m_hitNotesValueText.setPosition(sf::Vector2f{ xPos + secondStatColDist, yPos2 + valueDist });
	m_hitNotesValueText.setString("? / ?");
	m_hitNotesValueText.setFillColor(sf::Color::White);
	m_hitNotesValueText.setOutlineColor(sf::Color::Black);
	m_hitNotesValueText.setOutlineThickness(2.0f);
	m_hitNotesValueText.setCharacterSize(24U);
	yPos2 += typeDist;

	// Average Notes Per Second
	m_anpsText.setPosition(sf::Vector2f{ xPos + secondStatColDist, yPos2 });
	m_anpsText.setString("Avg Notes Per Second:");
	m_anpsText.setFillColor(sf::Color::White);
	m_anpsText.setOutlineColor(sf::Color::Black);
	m_anpsText.setOutlineThickness(2.0f);
	m_anpsText.setCharacterSize(24U);
	// Value
	m_anpsValueText.setPosition(sf::Vector2f{ xPos + secondStatColDist, yPos2 + valueDist });
	m_anpsValueText.setString("?");
	m_anpsValueText.setFillColor(sf::Color::White);
	m_anpsValueText.setOutlineColor(sf::Color::Black);
	m_anpsValueText.setOutlineThickness(2.0f);
	m_anpsValueText.setCharacterSize(24U);
}

void GameOver::setSessionStats(SessionStats& t_stats)
{
	m_sessionStats = t_stats;

	m_score = t_stats.m_score;
	m_earlyNotes = t_stats.m_earlyNotes;
	m_perfectNotes = t_stats.m_perfectNotes;
	m_lateNotes = t_stats.m_lateNotes;
	m_missedNotes = t_stats.m_missedNotes;
	m_wrongNotes = t_stats.m_wrongNotes;
	m_noteCountTotal = t_stats.m_noteCountTotal;
	m_currentNotesHit = t_stats.m_currentNotesHit;
	m_anps = t_stats.m_anps;

	m_scoreValueText.setString(std::to_string(m_score));
	m_earlyNotesValueText.setString(std::to_string(m_earlyNotes));
	m_perfectNotesValueText.setString(std::to_string(m_perfectNotes));
	m_lateNotesValueText.setString(std::to_string(m_lateNotes));
	m_missedNotesValueText.setString(std::to_string(m_missedNotes));
	m_wrongNotesValueText.setString(std::to_string(m_wrongNotes));

	m_hitNotesValueText.setString(std::to_string(m_currentNotesHit) + " / " + std::to_string(m_noteCountTotal));

	int hitPercentage = 0;
	if (m_noteCountTotal > 0)
	{
		hitPercentage = (m_currentNotesHit * 100) / m_noteCountTotal;
	}
	m_hitpercentageValueText.setString(std::to_string(hitPercentage) + "%");

	//m_anpsValueText.setString(std::to_string(static_cast<int>(m_anps)));
	m_anpsValueText.setString(std::to_string(std::roundf(m_anps * 100) / 100));

	updatePBScore();
}

void GameOver::resetSessionStats()
{
	m_score = 0;
	m_earlyNotes = 0;
	m_perfectNotes = 0;
	m_lateNotes = 0;
	m_missedNotes = 0;
	m_wrongNotes = 0;
	m_noteCountTotal = 0;
	m_currentNotesHit = 0;
	m_anps = 0.0f;
}

void GameOver::handleEvent(sf::Event& t_event)
{
	m_saveServerField.handleEvent(t_event);
	m_saveMidiField.handleEvent(t_event);

	if (const auto* mousePressed = t_event.getIf<sf::Event::MouseButtonPressed>())
	{
		if (mousePressed->button == sf::Mouse::Button::Left)
		{
			float xPos = static_cast<float>(mousePressed->position.x);
			float yPos = static_cast<float>(mousePressed->position.y);
			sf::Vector2f mousePos{ xPos, yPos };

			if (m_saveMidiField.checkIfAreaClicked(mousePos, m_saveMidiButton.getPosition(), m_saveMidiButton.getSize()))
			{
				std::string fileName = m_saveMidiField.getString();
				if (!fileName.empty())
				{
					m_midiWrite.writeFile(fileName);
					m_saveMidiField.clearString();
				}
			}
			
			if (m_saveServerField.checkIfAreaClicked(mousePos, m_saveServerButton.getPosition(), m_saveServerButton.getSize()))
			{
				std::string username = m_saveServerField.getString();
				if (!username.empty())
				{
					std::string midiPath = "ASSETS\\AUDIO\\MUSIC\\SavedMidi\\" + m_songName + ".mid";
					m_midiWrite.writeFile(m_songName);

					// server upload
					m_database->submitResult(username, m_songName, m_sessionStats, midiPath);
					m_saveServerField.clearString();
				}
			}

		}
	}
}

void GameOver::update(float t_deltatime)
{
	m_saveServerField.update(t_deltatime);
	m_saveMidiField.update(t_deltatime);
}

void GameOver::render(sf::RenderWindow& t_window)
{
	// UI
	t_window.draw(m_scoreUIFrame);
	t_window.draw(m_statisticUIFrame);
	t_window.draw(m_statisticFrameBorder);

	// Text
	t_window.draw(m_titleText);
	t_window.draw(m_scoreText);
	t_window.draw(m_scoreValueText);
	t_window.draw(m_pbScoreText);
	t_window.draw(m_pbScoreValueText);
	t_window.draw(m_songNameText);

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

	// Fields
	m_saveServerField.render(t_window);
	m_saveMidiField.render(t_window);

	t_window.draw(m_saveMidiButton);
	t_window.draw(m_saveServerButton);
	t_window.draw(m_saveMidiButtonText);
	t_window.draw(m_saveServerButtonText);
}
