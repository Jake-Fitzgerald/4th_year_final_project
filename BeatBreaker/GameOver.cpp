#include "GameOver.h"

GameOver::GameOver(std::shared_ptr<const sf::Font> font) 
	: m_titleText(*font),
	  m_scoreText(*font),
	  m_scoreValueText(*font),
	  m_pbScoreText(*font),
	  m_pbScoreValueText(*font),
	  m_saveMidiButtonText(*font),
	  m_saveServerButtonText(*font),
	  m_songNameText(*font),
	  m_saveServerField(font, m_serverFieldPos, m_fieldSize, m_characterSize),
	  m_saveMidiField(font, m_midiFieldPos, m_fieldSize, m_characterSize)
{
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
}

void GameOver::setupUIFrames()
{
	m_scoreUIFrame.setSize(m_frameSize);
	m_scoreUIFrame.setPosition(sf::Vector2f{ paddingX + 100.0f, paddingY + 100.0f });
	m_scoreUIFrame.setFillColor(c_scoreFrameColour);
	m_scoreUIFrame.setOutlineThickness(2.0f);
	m_scoreUIFrame.setOutlineColor(sf::Color::Black);

	m_statisticUIFrame.setSize(m_frameSize);
	m_statisticUIFrame.setPosition(sf::Vector2f{ paddingX + 500.0f, paddingY + 100.0f });
	m_statisticUIFrame.setFillColor(c_statisticFrameColour);
	m_statisticUIFrame.setOutlineThickness(2.0f);
	m_statisticUIFrame.setOutlineColor(sf::Color::Black);
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
	std::cerr << "setSongName called with: " << t_name << std::endl;
	m_songName = t_name;
	m_songNameText.setString(m_songName);
	m_saveMidiField.setPlaceholderString(m_songName);
}


void GameOver::setScore(int t_score)
{
	m_score = t_score;
	m_scoreValueText.setString(std::to_string(m_score));
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
				std::string fileName = m_saveServerField.getString();
				if (!fileName.empty())
				{
					// server upload
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

	// Text
	t_window.draw(m_titleText);
	t_window.draw(m_scoreText);
	t_window.draw(m_scoreValueText);
	t_window.draw(m_pbScoreText);
	t_window.draw(m_pbScoreValueText);
	t_window.draw(m_songNameText);

	// Fields
	m_saveServerField.render(t_window);
	m_saveMidiField.render(t_window);

	t_window.draw(m_saveMidiButton);
	t_window.draw(m_saveServerButton);
	t_window.draw(m_saveMidiButtonText);
	t_window.draw(m_saveServerButtonText);
}
