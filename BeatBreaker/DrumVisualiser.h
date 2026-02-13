#pragma once
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "MIDIParse.h"
#include <vector>
#include "SoundManager.h"


/*
	List of drum parts: Kick, Snare, Hit hat, Cymbol 1, Floor Tom, TomTom 1, TomTom 2.
	Match the instruments labelled in the Midi with the corresponding sprite names.
	Colour a sprite when the sound of that piece is being played, then back to default when it's not.

	#When we click on a drum hitbox we print off the string that is associated with it -> "pieceName".
	Easy way of checking which hitbox is which when we are setting up the positions.
*/

struct DrumPiece
{
	sf::RectangleShape shape;
	std::string pieceName;
	bool b_isPressed;
	sf::Color originalColour;
};

enum DrumStatus
{
	On,
	Off
};

class DrumVisualiser
{
public:
	DrumVisualiser(std::shared_ptr<const sf::Font> font, SoundManager& t_soundManager);
	void setupDrums();
	void setupDrumSprites();
	void setupDrumHitbox();
	void setupDrumSounds();

	void renderDrums(sf::RenderWindow& t_window);
	void changeDrumColourOn(int t_trackNumber);
	void changeDrumColourOff(int t_trackNumber);

	void updateIntroAnim(float t_deltaTime);

	void handleClick(sf::Vector2f t_mousePos);
	bool checkIfPieceClicked(sf::Vector2f t_mousePos, const DrumPiece& t_piece);

	void toggleHitboxVis();

private:
	SoundManager* m_soundManager;

	std::vector<DrumPiece> m_drums;

	DrumPiece m_kickPiece;
	DrumPiece m_snarePiece;
	DrumPiece m_Crash1Piece;
	DrumPiece m_Crash2Piece;
	DrumPiece m_FloorTomPiece;
	DrumPiece m_Tom1Piece;
	DrumPiece m_Tom2Piece;
	DrumPiece m_HiHatPiece;
	DrumPiece m_clapPiece;


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
	sf::Texture m_hiHatTexture;
	sf::Sprite m_hiHatSprite;
	sf::Texture m_clapTexture;
	sf::Sprite m_clapSprite;

	// Drum hitbox
	sf::Vector2f m_drumHitboxSize = { 100.0f, 100.0f };
	sf::Vector2f m_kickHitboxSize = { 200.0f, 200.0f };
	sf::Color m_drumHitboxColour = sf::Color(255, 50, 50, 100);
	bool b_isHitboxVis = true;

	sf::Vector2f m_kickHitboxPos = { 440.0f, 430.0f };
	sf::Vector2f m_snareHitboxPos = { 650.0f, 310.0f };
	sf::Vector2f m_floorTomHitboxPos = { 330.0f, 300.0f };
	sf::Vector2f m_tom1HitboxPos = { 420.0f, 220.0f };
	sf::Vector2f m_tom2HitboxPos = { 580.0f, 220.0f };
	sf::Vector2f m_crash1HitboxPos = { 250.0f, 125.0f };
	sf::Vector2f m_crash2HitboxPos = { 700.0f, 80.0f };
	sf::Vector2f m_hiHatHitboxPos = { 700.0f, 200.0f };
	sf::Vector2f m_clapHitboxPos = { 80.0f, 300.0f };

	std::vector<sf::Sprite*> m_drumSprites;

	// Images are 1080 by 720 and the sprite's origins are halfed
	sf::Vector2f m_drumPositions{ 1080.0f / 2.0f, 720.0f / 2.0f}; 
	sf::Color m_noteOnColour = sf::Color::Green;
	sf::Color m_noteOffColour = sf::Color::White;

	// Text
	std::shared_ptr<const sf::Font> m_font;
	std::vector<sf::Text> m_trackNameTexts;


	// Drum intro animation
	float m_introDelayAmount = 0.2f;
	float m_introTimer = 0.0f;

	int m_drumPieceIndexIntro = 0;
	float m_drumPieceDelayIntro = 0.04f;
	float m_drumPieceTimerIntro = 0.0f;

	bool b_isIntroFinished = false;

	DrumStatus drumStatus = DrumStatus::Off;
};

