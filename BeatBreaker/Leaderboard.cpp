#include "Leaderboard.h"

Leaderboard::Leaderboard(std::shared_ptr<const sf::Font> font) : m_font(font)
{

}

void Leaderboard::getSQLData(int t_id, std::string t_username, int t_score)
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

	for (int i = 0; i < m_pageCount; i++)
	{
		userdata.m_userShape.setSize(m_buttonSize);
		userdata.m_userShape.setPosition(sf::Vector2f{ paddingX , paddingY + i * m_spacing });
		userdata.m_userShape.setFillColor(c_userShapeOdd);
		userdata.m_userShape.setOutlineThickness(2.0f);
		userdata.m_userShape.setOutlineColor(sf::Color::Black);

		// Text
		userdata.m_IDText.setFont(*m_font);
		userdata.m_IDText.setString("?");
		userdata.m_IDText.setCharacterSize(20);
		userdata.m_IDText.setFillColor(sf::Color::White);
		userdata.m_IDText.setPosition(sf::Vector2f{ userdata.m_userShape.getPosition().x + m_offsetX_ID, userdata.m_userShape.getPosition().y + m_offsetY_text });

		userdata.m_usernameText.setFont(*m_font);
		userdata.m_usernameText.setString("?????");
		userdata.m_usernameText.setCharacterSize(20);
		userdata.m_usernameText.setFillColor(sf::Color::White);
		userdata.m_usernameText.setPosition(sf::Vector2f{ userdata.m_userShape.getPosition().x + m_offsetX_Username, userdata.m_userShape.getPosition().y + m_offsetY_text });

		userdata.m_scoreText.setFont(*m_font);
		userdata.m_scoreText.setString("???");
		userdata.m_scoreText.setCharacterSize(20);
		userdata.m_scoreText.setFillColor(sf::Color::White);
		userdata.m_scoreText.setPosition(sf::Vector2f{ userdata.m_userShape.getPosition().x + m_offsetX_Score, userdata.m_userShape.getPosition().y + m_offsetY_text });
		m_leaderboardVec.push_back(userdata);
	}

	m_leaderboardVec.push_back(userdata);

	setupUI();
}

void Leaderboard::setupUI()
{
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

void Leaderboard::render(sf::RenderWindow& t_window)
{
	for (auto& LeaderboardData : m_leaderboardVec)
	{
		// Header
		t_window.draw(LeaderboardData.m_headerShape);
		t_window.draw(LeaderboardData.m_headerIDText);
		t_window.draw(LeaderboardData.m_headerUsernameText);
		t_window.draw(LeaderboardData.m_headerScoreText);

		// User tabs
		t_window.draw(LeaderboardData.m_userShape);
		t_window.draw(LeaderboardData.m_IDText);
		t_window.draw(LeaderboardData.m_usernameText);
		t_window.draw(LeaderboardData.m_scoreText);
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
}
