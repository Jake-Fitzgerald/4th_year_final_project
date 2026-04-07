#pragma once
#include <SFML//Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Globals.h"
#include <iostream>
#include "InputField.h"

/*
	TODO:
	Buttons 
	- Retry
	- Upload to Leaderboards
	- Go to Leaderboards

	compare if current score is greater than pb score
*/

class GameOver
{
public:
	GameOver(std::shared_ptr<const sf::Font> font);

	void setupGameOver();
	void setupUIFrames();
	void setupText();
	void setupServerField();
	void setupMidiField();
	
	void setScore(int t_score);
	void updateScore();
	void updatePBScore();

	void saveScore();

	void handleEvent(sf::Event& t_event);
	void update(float t_deltatime);

	void render(sf::RenderWindow& t_window);

private:
	int m_score = 0;
	int m_pbScore = 0;

	sf::Text m_titleText; 
	sf::Vector2f m_screenCentre = SCREEN_CENTRE;
	sf::Vector2f m_titlePos = sf::Vector2f{ m_screenCentre.x - 100.0f, m_screenCentre.y - 350.0f };

	// Score Text
	sf::Text m_scoreText;
	sf::Text m_scoreValueText;
	sf::Text m_pbScoreText;
	sf::Text m_pbScoreValueText;

	// Statistic Text


	// UI
	sf::RectangleShape m_scoreUIFrame;
	sf::RectangleShape m_statisticUIFrame;
	sf::Vector2f m_frameSize{ 300.0f, 500.0f };
	sf::Vector2f m_frameTextSize{ 200.0f, 50.0f };
	sf::Color c_scoreFrameColour = sf::Color(50, 200, 150, 100);
	sf::Color c_statisticFrameColour = sf::Color(100, 100, 250, 100);

	// Fields
	sf::Vector2f m_serverFieldPos{ paddingX + 100.0f, paddingY + 100.0f };
	sf::Vector2f m_midiFieldPos{ 100.0f, 200.0f };
	sf::Vector2f m_fieldSize{ 500.0f, 100.0f };
	int m_characterSize = 40;

	// InputField(std::shared_ptr<const sf::Font> font, sf::Vector2f t_pos, sf::Vector2f t_size, int t_charSize);
	//InputField m_saveServerField(&m_font, m_serverFieldPos, m_fieldSize, m_characterSize);
	InputField m_saveServerField;
	InputField m_saveMidiField;
};

