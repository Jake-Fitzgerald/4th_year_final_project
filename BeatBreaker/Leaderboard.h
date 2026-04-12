#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Database.h"


struct LeaderboardData
{
	sf::RectangleShape m_headerShape;
	sf::Text m_headerIDText;
	sf::Text m_headerUsernameText;
	sf::Text m_headerScoreText;

	sf::RectangleShape m_userShape;

	int m_id = -1;
	std::string m_username = " ";
	int m_score = -1;

	sf::Text m_IDText;
	sf::Text m_usernameText;
	sf::Text m_scoreText;

	LeaderboardData(std::shared_ptr<const sf::Font> font)
		: 
		m_headerIDText(*font),
		m_headerUsernameText(*font),
		m_headerScoreText(*font),
		m_IDText(*font),
		m_usernameText(*font),
		m_scoreText(*font)
	{

	}
};

class Leaderboard
{
public:
	Leaderboard(std::shared_ptr<const sf::Font> font, Database& t_database);

	void getSQLData(int t_id, std::string t_username, int t_score);

	void setupLeaderboard();
	void setupUI();

	void fetchSongs();
	void fetchSongsForCurrentSong();

	void populateFromDatabase(const std::vector<USERDATA>& t_data);

	void handleClick(sf::Vector2f t_mousePos);

	void render(sf::RenderWindow& t_window);

private:
	Database* m_database;
	std::shared_ptr<const sf::Font> m_font;

	std::vector<SONGDATA> m_songs;
	int m_currentSongIndex = 0;

	std::vector<LeaderboardData> m_leaderboardVec;

	sf::RectangleShape m_previousButton;
	sf::RectangleShape m_nextButton;
	sf::Text m_previousText;
	sf::Text m_nextText;
	sf::Text m_songNameText;

	// Tab var
	float m_posX = paddingX;
	float m_poY = paddingY;
	float m_spacing = 40.0f;
	sf::Vector2f m_buttonSize = { 600.0f, 40.0f };
	float m_difficultyTextSpacing = 200.0f;

	// Text offsets
	float m_offsetX_ID = 10.0f;
	float m_offsetX_Username = 100.0f;
	float m_offsetX_Score = 400.0f;
	float m_offsetY_text = 8.0f;

	int m_pageCount = 10;

	// UI
	std::vector<sf::RectangleShape> m_verticalLines;
	std::vector<sf::RectangleShape> m_horizontalLines;
	sf::Vector2f m_verticalLineSize = { 4.0f, 450.0f };
	sf::Vector2f m_horizintalLineSize = { 100.0f, 2.0f };

	// Colours
	sf::Color c_headerShape{ 200,200,200,200 };
	sf::Color c_userShapeEven{ 100,100,100,200 };
	sf::Color c_userShapeOdd{ 150,150,150,200 };
	sf::Color c_currentUserShape{ 200,100,100,200 };
	sf::Color c_navButtonColour{ 50,100,150,220 };


};

