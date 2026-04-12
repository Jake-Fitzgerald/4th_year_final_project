#pragma once
#include <SFML//Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Globals.h"
#include <iostream>
#include "InputField.h"
#include "MidiWrite.h"
#include "Database.h"
#include "ScoreManager.h"

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
	GameOver(std::shared_ptr<const sf::Font> font, Database& t_database, ScoreManager& t_scoreManager);

	void setupGameOver();
	void setupUIFrames();
	void setupText();
	void setupFieldButtons();
	void setupTextures();
	void setSongName(std::string t_name);

	void updateScore();
	void updatePBScore();

	void saveScore();
	void setBPM(double t_BPM);
	void setRecordedNotes(std::vector<MidiNote> t_notes);

	void setupStatisticText();
	void setSessionStats(SessionStats& t_stats);
	void resetSessionStats();

	void handleEvent(sf::Event& t_event);
	void update(float t_deltatime);

	void render(sf::RenderWindow& t_window);

	void calculateRank();
	void setRank(float t_rankAmount);

private:
	Database* m_database;
	ScoreManager* m_scoreManager;
	std::string ODBCString = "Driver={ODBC Driver 18 for SQL Server};Server=beatbreakerserversql.database.windows.net,1433;Database=beatbreakerSQL;Uid=JakeAdmin;Pwd=ToyMachine7;Encrypt=yes;TrustServerCertificate=no;Connection Timeout=30;";
	bool b_isConnected = false;
	SessionStats m_sessionStats;

	int m_score = 0;
	int m_pbScore = 0;
	double m_BPM = 120.0;

	sf::Text m_titleText; 
	sf::Vector2f m_screenCentre = SCREEN_CENTRE;
	sf::Vector2f m_titlePos = sf::Vector2f{ m_screenCentre.x - 100.0f, m_screenCentre.y - 350.0f };

	std::string m_songName = "";

	// Score Text
	sf::Text m_scoreText;
	sf::Text m_scoreValueText;
	sf::Text m_pbScoreText;
	sf::Text m_pbScoreValueText;

	sf::Text m_songNameText;

	// UI
	sf::RectangleShape m_scoreUIFrame;
	sf::RectangleShape m_scoreFrameBorder;
	sf::RectangleShape m_statisticUIFrame;
	sf::RectangleShape m_statisticFrameBorder;
	sf::Vector2f m_frameScoreSize{ 300.0f, 400.0f };
	sf::Vector2f m_frameStatsSize{ 500.0f, 400.0f };
	sf::Vector2f m_frameTextSize{ 200.0f, 50.0f };
	sf::Color c_scoreFrameColour = sf::Color(50, 200, 150, 100);
	sf::Color c_scoreBorderColour = sf::Color(40, 40, 40, 170);
	sf::Color c_statisticFrameColour = sf::Color(100, 100, 250, 100);
	sf::Color c_statisticBorderColour = sf::Color(40, 40, 40, 170);
	sf::RectangleShape m_titleFrame;

	sf::Vector2f m_serverFieldPos{ paddingX + 25.0f, paddingY + 525.0f };
	sf::Vector2f m_midiFieldPos{ paddingX + 650.0f, paddingY + 525.0f };
	sf::Vector2f m_fieldSize{ 400.0f, 50.0f };
	int m_characterSize = 40;
	int m_maxLength = 20;

	InputField m_saveServerField;
	InputField m_saveMidiField;

	MidiWrite m_midiWrite;

	// Save Button
	sf::Vector2f m_buttonSize{ 150.0f, 50.0f };
	sf::Color c_inactiveColour = sf::Color(230, 200, 200, 240);
	sf::Color c_activeColour = sf::Color(0, 250, 20, 240);

	sf::RectangleShape m_saveMidiButton;
	sf::Text m_saveMidiButtonText;
	sf::RectangleShape m_saveServerButton;
	sf::Text m_saveServerButtonText;

	int m_earlyNotes = 0;
	int m_perfectNotes = 0;
	int m_lateNotes = 0;
	int m_missedNotes = 0;
	int m_wrongNotes = 0;

	int m_noteCountTotal = 0;
	int m_currentNotesHit = 0;
	float m_anps = 0.0f;

	sf::Text m_missedNotesText;
	sf::Text m_missedNotesValueText;
	sf::Text m_earlyNotesText;
	sf::Text m_earlyNotesValueText;
	sf::Text m_perfectNotesText;
	sf::Text m_perfectNotesValueText;
	sf::Text m_lateNotesText;
	sf::Text m_lateNotesValueText;
	sf::Text m_wrongNotesText;
	sf::Text m_wrongNotesValueText;

	sf::Text m_hitpercentageText;
	sf::Text m_hitpercentageValueText;
	sf::Text m_hitNotesText;
	sf::Text m_hitNotesValueText;
	sf::Text m_anpsText; 
	sf::Text m_anpsValueText;

	sf::Texture m_serverTex;
	sf::Sprite m_serverSprite{ m_serverTex };
	sf::Texture m_midiTex;
	sf::Sprite m_midiSprite{ m_midiTex };

	sf::Text m_rankText;
	sf::Text m_rankValueText;
};

