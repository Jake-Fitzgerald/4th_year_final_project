#pragma once
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "MIDIParse.h"
#include <vector>


/*
	List of drum parts: Kick, Snare, Hit hat, Cymbol 1, Floor Tom, TomTom 1, TomTom 2.
	Match the instruments labelled in the Midi with the corresponding sprite names.
	Colour a sprite when the sound of that piece is being played, then back to default when it's not.

*/
class DrumVisualiser
{
public:
	DrumVisualiser(std::shared_ptr<const sf::Font> font);
	void setupDrums();
	void setupDrumSprites();

	void renderDrums(sf::RenderWindow& t_window);
	void changeDrumColourOn(int t_trackNumber);
	void changeDrumColourOff(int t_trackNumber);

private:
	// Drum Sprites
	sf::Texture m_kickTexture;
	sf::Sprite m_kickSprite;
	sf::Texture m_snareTexture;
	sf::Sprite m_snareSprite;
	sf::Texture m_floorTomTexture;
	sf::Sprite m_floorTomSprite;
	sf::Texture m_TomTom1Texture;
	sf::Sprite m_TomTom1Sprite;
	sf::Texture m_TomTom2Texture;
	sf::Sprite m_TomTom2Sprite;
	sf::Texture m_crash1Texture;
	sf::Sprite m_crash1Sprite;
	sf::Texture m_crash2Texture;
	sf::Sprite m_crash2Sprite;
	sf::Texture m_hitHatTexture;
	sf::Sprite m_hitHatSprite;
	sf::Texture m_clapTexture;
	sf::Sprite m_clapSprite;

	std::vector<sf::Sprite*> m_drumSprites;

	// Images are 1080 by 720 and the sprite's origins are halfed
	sf::Vector2f m_drumPositions{ 1080.0f / 2.0f, 720.0f / 2.0f}; 
	sf::Color m_noteOnColour = sf::Color::Green;
	sf::Color m_noteOffColour = sf::Color::White;

	// Text
	std::shared_ptr<const sf::Font> m_font;
	std::vector<sf::Text> m_trackNameTexts;
};

