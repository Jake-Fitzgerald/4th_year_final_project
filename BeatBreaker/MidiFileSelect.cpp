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
		{"Drum Visualiser", "ASSETS\\AUDIO\\MUSIC\\DrumVis.mid"},
		{"Piano Visualiser", "ASSETS\\AUDIO\\MUSIC\\PianoVis.mid"},
		{"Chord", "ASSETS\\AUDIO\\MUSIC\\Chord.mid"},
		{"Full MIDI Range", "ASSETS\\AUDIO\\MUSIC\\Full_MIDI_Range.mid"},
		{"Saved Midi", "ASSETS\\AUDIO\\MUSIC\\SavedMidi\\temp.midi"}

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

		button.midiPath = m_pathVector[i].path;
		m_buttons.push_back(button);
		//std::cerr << "Pushed back a selection button" << std::endl;
	}

	//setupSprites();

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

	t_window.draw(m_returnSprite);
}

void MidiFileSelect::mouseClick(sf::Vector2f t_mousePos)
{
	for (auto& button : m_buttons)
	{
		// Reset colours if you click again
		button.m_buttonShape.setFillColor(sf::Color::Blue);


		sf::Vector2f topLeft = button.m_buttonShape.getPosition();
		sf::Vector2f size = button.m_buttonShape.getSize();

		if (checkIfAreaClicked(t_mousePos, topLeft, size) == true)
		{
			m_selectedPath = button.midiPath;
			std::cerr << "Selected Path is: " << m_selectedPath << std::endl;

			// Turn it red to show it has been clicked
			button.m_buttonShape.setFillColor(sf::Color::Red);
		}
	}
}

bool MidiFileSelect::returnClick(sf::Vector2f t_mousePos)
{
	// Return Button
	sf::Vector2f spriteTopLeft = m_returnSprite.getPosition();
	sf::Vector2f spriteSize = sf::Vector2f{ m_returnSprite.getGlobalBounds().size.x, m_returnSprite.getGlobalBounds().size.y };

	if (checkIfAreaClicked(t_mousePos, spriteTopLeft, spriteSize) == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool MidiFileSelect::checkIfAreaClicked(sf::Vector2f t_mousePos, sf::Vector2f t_topLeft, sf::Vector2f t_size)
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

std::string MidiFileSelect::getMidiPathString()
{
	return m_selectedPath;
}

void MidiFileSelect::setupSprites()
{
	if (!m_returnTexture.loadFromFile("ASSETS\\IMAGES\\UI\\Return_Button.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading Return button in Midi File Selector" << std::endl;
	}

	m_returnSprite.setTexture(m_returnTexture, true);
	m_returnSprite.setPosition(sf::Vector2f{ 1120.0f, 0.0f });

}