#include "GameOver.h"

GameOver::GameOver(std::shared_ptr<const sf::Font> font) 
	: m_titleText(*font),
	  m_scoreText(*font),
	  m_scoreValueText(*font),
	  m_pbScoreText(*font),
	  m_pbScoreValueText(*font)
{
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
}
