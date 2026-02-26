#pragma once
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Globals.h"


struct Button
{
	sf::RectangleShape m_buttonShape;
	sf::Text m_buttonText;
	std::string midiPath = " ";

	Button(std::shared_ptr<const sf::Font> font) : m_buttonText(*font)
	{

	}
};

struct Paths
{
	std::string name = " ";
	std::string path = " ";
};

class MidiFileSelect
{
public:
	MidiFileSelect(std::shared_ptr<const sf::Font> font);

	void setupPathStrings();
	void setupButtons();
	void setupSprites();
	void render(sf::RenderWindow& t_window);

	void mouseClick(sf::Vector2f t_mousePos);
	bool returnClick(sf::Vector2f t_mousePos);
	bool checkIfAreaClicked(sf::Vector2f t_mousePos, sf::Vector2f t_topLeft, sf::Vector2f t_size);

	std::string getMidiPathString();


private:
	std::vector<Button> m_buttons;
	std::shared_ptr<const sf::Font> m_font;
	std::string m_selectedPath = "ASSETS\\AUDIO\\MUSIC\\Kick_and_Clap_2_track.mid"; // Default midi file

	sf::RectangleShape m_returnButton;
	sf::Texture m_returnTexture;
	sf::Sprite m_returnSprite{ m_returnTexture };
	
	// Button 
	float m_posX = paddingX;
	float m_poY = paddingY;
	float m_spacing = 60.0f;
	sf::Vector2f m_buttonSize = { 200.0f, 40.0f };

	int m_pathsCount = 10; // Change this in setup paths function to be consistent

	// File Paths
	std::string m_3_4_TimeSigPath = "ASSETS\\AUDIO\\MUSIC\\3-4.mid";
	std::string m_5_4_TimeSigPath = "ASSETS\\AUDIO\\MUSIC\\5-4.mid";
	std::string m_6_8_TimeSigPath = "ASSETS\\AUDIO\\MUSIC\\6-8.mid";
	std::string m_7_4_TimeSigPath = "ASSETS\\AUDIO\\MUSIC\\7-4.mid";

	std::string m_KickAndClapPath = "ASSETS\\AUDIO\\MUSIC\\Kick_and_Clap_2_track.mid";
	std::string m_DrumVisPath = "ASSETS\\AUDIO\\MUSIC\\Kick_and_Clap_2_track.mid";

	std::string m_PianoVisPath = "ASSETS\\AUDIO\\MUSIC\\Kick_and_Clap_2_track.mid";

	std::vector<Paths> m_pathVector;
};

