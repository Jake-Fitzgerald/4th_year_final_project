#include "MidiFileSelect.h"
#include "VisualiserSelect.h"

MidiFileSelect::MidiFileSelect(std::shared_ptr<const sf::Font> font) : m_font(font)
{
	//Button button;
}

void MidiFileSelect::setupPathStrings()
{
	m_pathVector = 
	{
		{"3/4 Time", "ASSETS\\AUDIO\\MUSIC\\3-4.mid"},
		{"5/4 Time", "ASSETS\\AUDIO\\MUSIC\\5-4.mid"},
		{"6/8 Time", "ASSETS\\AUDIO\\MUSIC\\6-8.mid"},
		{"7/4 Time", "ASSETS\\AUDIO\\MUSIC\\7-4.mid"},
		{"Kick and Clap", "ASSETS\\AUDIO\\MUSIC\\Kick_and_Clap_2_track.mid"},
		{"Drum Visualiser", "ASSETS\\AUDIO\\MUSIC\\Kick_and_Clap_2_track.mid"},
		{"Piano Visualiser", "ASSETS\\AUDIO\\MUSIC\\Kick_and_Clap_2_track.mid"}

	};
	
	m_pathsCount = m_pathVector.size();
}

void MidiFileSelect::setupButtons()
{
	// Shapes
	for (int i = 0; i < m_pathsCount; i++)
	{
		Button button(m_font);
		
		button.m_buttonShape.setSize(m_buttonSize);
		button.m_buttonShape.setPosition(sf::Vector2f{ paddingX , paddingY + i * m_spacing });
		button.m_buttonShape.setFillColor(sf::Color::Blue);
		button.m_buttonShape.setOutlineThickness(2.0f);
		button.m_buttonShape.setOutlineColor(sf::Color::Black);

		button.m_buttonText.setFont(*m_font);
		button.m_buttonText.setString(m_pathVector[i].name);
		button.m_buttonText.setCharacterSize(20);
		button.m_buttonText.setFillColor(sf::Color::White);
		button.m_buttonText.setPosition(sf::Vector2f{ button.m_buttonShape.getPosition().x + 10.f, button.m_buttonShape.getPosition().y + 10.f });

		m_buttons.push_back(button);
		std::cerr << "Pushed back a selection button" << std::endl;
	}
}


void MidiFileSelect::render(sf::RenderWindow& t_window)
{
	//for (int i = 0; i < m_pathsCount; i++)
	//{
	//	t_window.draw(m_buttons[i].m_buttonShape);
	//	t_window.draw(m_buttons[i].m_buttonText);
	//}
	for (auto& button : m_buttons)
	{
		t_window.draw(button.m_buttonShape);
		t_window.draw(button.m_buttonText);
	}
}
