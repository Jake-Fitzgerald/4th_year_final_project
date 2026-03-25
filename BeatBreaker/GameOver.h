#pragma once
#include <SFML//Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Globals.h"
#include <iostream>

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
	
	void setScore(int t_score);
	void updateScore();
	void updatePBScore();

	void saveScore();

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
};

