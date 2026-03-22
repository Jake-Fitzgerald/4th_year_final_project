#include "MainMenu.h"

MainMenu::MainMenu(std::shared_ptr<const sf::Font> t_font) : m_font(t_font), m_titleText(*t_font), m_topLeftStart({ paddingX, paddingY + 100.0f })
{


	//setupRectangles();
}

void MainMenu::setupMainMenu()
{

	m_buttonData =
	{
		{ "Start", { m_topLeftStart.x, m_topLeftStart.y }, sf::Color::Blue },
		{ "Midi Selection", { m_topLeftStart.x, m_topLeftStart.y + m_buttonSpacing }, sf::Color::Blue },
		{ "Record Midi", { m_topLeftStart.x, m_topLeftStart.y + m_buttonSpacing * 2 }, sf::Color::Blue },
		{ "MIDI Parse", { m_topLeftStart.x, m_topLeftStart.y + m_buttonSpacing * 3 }, sf::Color::Blue },
		{ "Vis Selection", { m_topLeftStart.x, m_topLeftStart.y + m_buttonSpacing * 4 }, sf::Color::Blue },
		{ "Options", { m_topLeftStart.x + 500.0f, m_topLeftStart.y + m_buttonSpacing }, sf::Color::Blue },
		{ "Leaderboard", { m_topLeftStart.x + 500.0f, m_topLeftStart.y + m_buttonSpacing * 2}, sf::Color::Blue },
		{ "EXIT", { m_topLeftStart.x + 500.0f, m_topLeftStart.y + m_buttonSpacing * 3 }, sf::Color::Magenta },
	};

	// Shapes
	for (int i = 0; i < m_buttonData.size(); i++)
	{
		MenuButton button(m_font);

		button.m_label = m_buttonData[i].m_label;
		button.m_buttonShape.setSize(m_buttonSize);
		button.m_buttonShape.setPosition(m_buttonData[i].m_position);
		button.m_buttonShape.setFillColor(m_buttonData[i].m_colour);
		button.m_buttonShape.setOutlineThickness(2.0f);
		button.m_buttonShape.setOutlineColor(sf::Color::Black);
		button.m_buttonText.setString(m_buttonData[i].m_label);
		button.m_buttonText.setCharacterSize(40U);
		button.m_buttonText.setFillColor(sf::Color::Black);
		button.m_buttonText.setPosition({ button.m_buttonShape.getPosition().x + 20.0f, button.m_buttonShape.getPosition().y });
		m_buttons.push_back(button);
	}

	// Title
	m_titleText.setString("Beat Breaker");
	m_titleText.setCharacterSize(80U);
	m_titleText.setFillColor(sf::Color::Red);
	m_titleText.setOutlineColor(sf::Color::Black);
	m_titleText.setOutlineThickness(2.0f);
	m_titleText.setPosition({ SCREEN_CENTRE.x - 200.0f, SCREEN_CENTRE.y - 350.0f });
}

void MainMenu::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_titleText);

	for (auto& button : m_buttons)
	{
		t_window.draw(button.m_buttonShape);
		t_window.draw(button.m_buttonText);
	}
}

void MainMenu::MoveUp()
{
}

void MainMenu::MoveDown()
{
}


std::string MainMenu::mouseClick(sf::Vector2f t_mousePos)
{
	for (auto& button : m_buttons)
	{
		// Reset colour on each click
		button.m_buttonShape.setFillColor(sf::Color::Blue);

		sf::Vector2f topLeft = button.m_buttonShape.getPosition();
		sf::Vector2f size = button.m_buttonShape.getSize();

		if (checkIfAreaClicked(t_mousePos, topLeft, size) == true)
		{
			//button.m_buttonShape.setFillColor(sf::Color::Red);

			std::cerr << "Menu button clicked: " << button.m_label << std::endl;
			return button.m_label;
		}
	}

	return "";
}

bool MainMenu::checkIfAreaClicked(sf::Vector2f t_mousePos, sf::Vector2f t_topLeft, sf::Vector2f t_size)
{
	if (t_mousePos.x >= t_topLeft.x &&
		t_mousePos.x <= t_topLeft.x + t_size.x &&
		t_mousePos.y >= t_topLeft.y &&
		t_mousePos.y <= t_topLeft.y + t_size.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}
