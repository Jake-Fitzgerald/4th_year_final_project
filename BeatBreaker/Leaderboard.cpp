#include "Leaderboard.h"

Leaderboard::Leaderboard(std::shared_ptr<const sf::Font> font, Database& t_database) 
	: m_font(font),
	m_database(&t_database),
	m_previousText(*font),
	m_nextText(*font),
	m_songNameText(*font)
{

}

void Leaderboard::setupLeaderboard()
{
	LeaderboardData userdata(m_font);

	// Header
	userdata.m_headerShape.setSize(m_buttonSize);
	userdata.m_headerShape.setPosition(sf::Vector2f{ paddingX , paddingY });
	userdata.m_headerShape.setFillColor(c_headerShape);
	userdata.m_headerShape.setOutlineThickness(2.0f);
	userdata.m_headerShape.setOutlineColor(sf::Color::Black);

	userdata.m_headerIDText.setFont(*m_font);
	userdata.m_headerIDText.setString("ID");
	userdata.m_headerIDText.setCharacterSize(24);
	userdata.m_headerIDText.setFillColor(sf::Color::White);
	userdata.m_headerIDText.setPosition(sf::Vector2f{ userdata.m_headerShape.getPosition().x + m_offsetX_ID, userdata.m_headerShape.getPosition().y + m_offsetY_text });

	userdata.m_headerUsernameText.setFont(*m_font);
	userdata.m_headerUsernameText.setString("USERNAME");
	userdata.m_headerUsernameText.setCharacterSize(24);
	userdata.m_headerUsernameText.setFillColor(sf::Color::White);
	userdata.m_headerUsernameText.setPosition(sf::Vector2f{ userdata.m_headerShape.getPosition().x + m_offsetX_Username, userdata.m_headerShape.getPosition().y + m_offsetY_text });

	userdata.m_headerScoreText.setFont(*m_font);
	userdata.m_headerScoreText.setString("SCORE");
	userdata.m_headerScoreText.setCharacterSize(24);
	userdata.m_headerScoreText.setFillColor(sf::Color::White);
	userdata.m_headerScoreText.setPosition(sf::Vector2f{ userdata.m_headerShape.getPosition().x + m_offsetX_Score, userdata.m_headerShape.getPosition().y + m_offsetY_text });

	m_leaderboardVec.push_back(userdata);

	for (int i = 0; i < m_pageCount; i++)
	{
		LeaderboardData rowData(m_font);

		rowData.m_userShape.setSize(m_buttonSize);
		rowData.m_userShape.setPosition(sf::Vector2f{ paddingX , paddingY + (i +1) * m_spacing });
		rowData.m_userShape.setFillColor(c_userShapeOdd);
		rowData.m_userShape.setOutlineThickness(2.0f);
		rowData.m_userShape.setOutlineColor(sf::Color::Black);

		// Text
		rowData.m_IDText.setFont(*m_font);
		rowData.m_IDText.setString("?");
		rowData.m_IDText.setCharacterSize(20);
		rowData.m_IDText.setFillColor(sf::Color::White);
		rowData.m_IDText.setPosition(sf::Vector2f{ rowData.m_userShape.getPosition().x + m_offsetX_ID, rowData.m_userShape.getPosition().y + m_offsetY_text });

		rowData.m_usernameText.setFont(*m_font);
		rowData.m_usernameText.setString("?????");
		rowData.m_usernameText.setCharacterSize(20);
		rowData.m_usernameText.setFillColor(sf::Color::White);
		rowData.m_usernameText.setPosition(sf::Vector2f{ rowData.m_userShape.getPosition().x + m_offsetX_Username, rowData.m_userShape.getPosition().y + m_offsetY_text });

		rowData.m_scoreText.setFont(*m_font);
		rowData.m_scoreText.setString("???");
		rowData.m_scoreText.setCharacterSize(20);
		rowData.m_scoreText.setFillColor(sf::Color::White);
		rowData.m_scoreText.setPosition(sf::Vector2f{ rowData.m_userShape.getPosition().x + m_offsetX_Score, rowData.m_userShape.getPosition().y + m_offsetY_text });

		// Midi
		rowData.m_downloadButton.setSize(sf::Vector2f{ 60.0f, 30.0f });
		rowData.m_downloadButton.setFillColor(c_songTitleFrameColour);
		rowData.m_downloadButton.setOutlineColor(c_songTitleFrameColourOutline);
		rowData.m_downloadButton.setOutlineThickness(2.0f);
		rowData.m_downloadButton.setPosition(sf::Vector2f{
															paddingX + m_buttonSize.x + 10.0f,
															paddingY + (i + 1) * m_spacing + 5.0f 
														});

		rowData.m_downloadText.setCharacterSize(20U);
		rowData.m_downloadText.setString("Midi");
		rowData.m_downloadText.setFillColor(sf::Color::White);
		rowData.m_downloadText.setOutlineColor(sf::Color::Black);
		rowData.m_downloadText.setOutlineThickness(2.0f);
		rowData.m_downloadText.setPosition(sf::Vector2f{
															rowData.m_downloadButton.getPosition().x + 13.0f,
															rowData.m_downloadButton.getPosition().y + 3.0f
														});

		m_leaderboardVec.push_back(rowData);
	}

	setupUI();
}

void Leaderboard::setupUI()
{
	m_songNameText.setCharacterSize(40U);
	m_songNameText.setFillColor(sf::Color::White);
	m_songNameText.setOutlineColor(sf::Color::Black);
	m_songNameText.setOutlineThickness(2.0f);
	m_songNameText.setString("Song name");
	m_songNameText.setPosition(sf::Vector2f{ paddingX + 700.0f, paddingY + 100.0f });

	m_previousButton.setSize(sf::Vector2f{ 100.0f, 40.0f });
	m_previousButton.setPosition(sf::Vector2f{ paddingX + 700.0f, paddingY + 160.0f });
	m_previousButton.setFillColor(sf::Color(c_navButtonColour));
	m_previousButton.setOutlineColor(sf::Color::Black);
	m_previousButton.setOutlineThickness(2.0f);
	m_previousText.setString("<");
	m_previousText.setCharacterSize(60U);
	m_previousText.setPosition(sf::Vector2f{ paddingX + 730.0f, paddingY + 140.0f });
	m_previousText.setFillColor(sf::Color::Blue);
	m_previousText.setOutlineColor(sf::Color::Black);
	m_previousText.setOutlineThickness(2.0f);

	m_nextButton.setSize(sf::Vector2f{ 100.0f, 40.0f });
	m_nextButton.setPosition(sf::Vector2f{ paddingX + 800.0f, paddingY + 160.0f });
	m_nextButton.setFillColor(sf::Color(c_navButtonColour));
	m_nextButton.setOutlineColor(sf::Color::Black);
	m_nextButton.setOutlineThickness(2.0f);
	m_nextText.setString(">");
	m_nextText.setCharacterSize(60U);
	m_nextText.setPosition(sf::Vector2f{ paddingX + 830.0f, paddingY + 140.0f });
	m_nextText.setFillColor(sf::Color::Blue);
	m_nextText.setOutlineColor(sf::Color::Black);
	m_nextText.setOutlineThickness(2.0f);

	// UI Frames
	m_songTitleFrame.setPosition(sf::Vector2f{ m_songNameText.getPosition().x - 5.0f, m_songNameText.getPosition().y + 10.0f });
	m_songTitleFrame.setFillColor(c_songTitleFrameColour);
	m_songTitleFrame.setSize(sf::Vector2f{ 225.0f, 40.0f });

	m_songFrame.setPosition(sf::Vector2f{ m_songNameText.getPosition().x - 10.0f, m_songNameText.getPosition().y - 10.0f });
	m_songFrame.setFillColor(c_songFrameColour);
	m_songFrame.setSize(sf::Vector2f{ 240.0f, 120.0f });
	m_songFrame.setOutlineColor(sf::Color(c_songFrameColourOutline));
	m_songFrame.setOutlineThickness(2.0f);

	sf::RectangleShape idLine;
	idLine.setSize(m_verticalLineSize);
	idLine.setPosition(sf::Vector2f{ paddingX , paddingY });
	idLine.setFillColor(sf::Color::Black);
	m_verticalLines.push_back(idLine);
	
	sf::RectangleShape usernameLine;
	usernameLine.setSize(m_verticalLineSize);
	usernameLine.setPosition(sf::Vector2f{ m_offsetX_Username , paddingY });
	usernameLine.setFillColor(sf::Color::Black);
	m_verticalLines.push_back(usernameLine);

	sf::RectangleShape scoreLine;
	scoreLine.setSize(m_verticalLineSize);
	scoreLine.setPosition(sf::Vector2f{ m_offsetX_Score , paddingY });
	scoreLine.setFillColor(sf::Color::Black);
	m_verticalLines.push_back(scoreLine);

	sf::RectangleShape rightHandLine;
	rightHandLine.setSize(m_verticalLineSize);
	rightHandLine.setPosition(sf::Vector2f{ m_offsetX_Score + 240.0f , paddingY });
	rightHandLine.setFillColor(sf::Color::Black);
	m_verticalLines.push_back(rightHandLine);
}

void Leaderboard::fetchSongs()
{
	m_songs = m_database->getAllSongs();

	if (m_songs.empty())
	{
		std::cerr << "[Leaderboard] Songs not found" << std::endl;
	}

	m_currentSongIndex = 0;
	fetchSongsForCurrentSong();
}

void Leaderboard::fetchSongsForCurrentSong()
{
	// Extra check again incase we call this again else whee
	if (m_songs.empty())
	{
		std::cerr << "[Leaderboard] Songs not found" << std::endl;
		return;
	}

	SONGDATA currentSong = m_songs[m_currentSongIndex];
	m_songNameText.setString(currentSong.songName);

	std::vector<USERDATA> userData = m_database->getLeaderboardBySong(currentSong.id);
	populateFromDatabase(userData);
}

void Leaderboard::populateFromDatabase(const std::vector<USERDATA>& t_data)
{
	int count = -1;

	if (t_data.size() < m_pageCount)
	{
		count = t_data.size();
	}
	else
	{
		count = m_pageCount;
	}

	for (int i = 0; i < count; i++)
	{
		// index 0 is the header so we add 1
		m_leaderboardVec[i + 1].m_id = t_data[i].id;
		m_leaderboardVec[i + 1].m_username = t_data[i].username;
		m_leaderboardVec[i + 1].m_score = t_data[i].score;

		m_leaderboardVec[i + 1].m_IDText.setString(std::to_string(i + 1));
		m_leaderboardVec[i + 1].m_usernameText.setString(t_data[i].username);
		m_leaderboardVec[i + 1].m_scoreText.setString(std::to_string(t_data[i].score));

		sf::Color rowColor;
		if (i % 2 == 0)
		{
			rowColor = c_userShapeEven;
		}
		else
		{
			rowColor = c_userShapeOdd;
		}
		m_leaderboardVec[i + 1].m_userShape.setFillColor(rowColor);
	}
}

void Leaderboard::handleClick(sf::Vector2f t_mousePos)
{
	if (m_songs.empty())
	{
		std::cerr << "[Leaderboard] No songs loaded" << std::endl;
		return;
	}

	// Wrapping
	if (m_previousButton.getGlobalBounds().contains(t_mousePos))
	{
		m_currentSongIndex--;
		if (m_currentSongIndex < 0)
		{
			m_currentSongIndex = static_cast<int>(m_songs.size() - 1);
		}
		fetchSongsForCurrentSong();
	}


	// Wrapping
	if (m_nextButton.getGlobalBounds().contains(t_mousePos))
	{
		m_currentSongIndex++;
		if (m_currentSongIndex >= static_cast<int>(m_songs.size()))
		{
			m_currentSongIndex = 0;
		}
		fetchSongsForCurrentSong();
	}
}

void Leaderboard::render(sf::RenderWindow& t_window)
{
	for (auto& LeaderboardData : m_leaderboardVec)
	{
		t_window.draw(LeaderboardData.m_headerShape);
		t_window.draw(LeaderboardData.m_headerIDText);
		t_window.draw(LeaderboardData.m_headerUsernameText);
		t_window.draw(LeaderboardData.m_headerScoreText);

		// User tabs
		t_window.draw(LeaderboardData.m_userShape);
		t_window.draw(LeaderboardData.m_IDText);
		t_window.draw(LeaderboardData.m_usernameText);
		t_window.draw(LeaderboardData.m_scoreText);

		// Midi
		t_window.draw(LeaderboardData.m_downloadButton);
		t_window.draw(LeaderboardData.m_downloadText);
	}

	// UI
	for (int i = 0; i < m_verticalLines.size(); i++)
	{
		t_window.draw(m_verticalLines[i]);
	}

	for (int i = 0; i < m_horizontalLines.size(); i++)
	{
		t_window.draw(m_horizontalLines[i]);
	}

	t_window.draw(m_songFrame);
	t_window.draw(m_songTitleFrame);

	t_window.draw(m_previousButton);
	t_window.draw(m_nextButton);
	t_window.draw(m_previousText);
	t_window.draw(m_nextText);
	t_window.draw(m_songNameText);
}
