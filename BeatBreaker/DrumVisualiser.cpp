#include "DrumVisualiser.h"

DrumVisualiser::DrumVisualiser(std::shared_ptr<const sf::Font> font) :
	m_font(font),
	m_kickSprite(m_kickTexture),
	m_snareSprite(m_snareTexture),
	m_floorTomSprite(m_floorTomTexture),
	m_TomTom1Sprite(m_TomTom1Texture),
	m_TomTom2Sprite(m_TomTom2Texture),
	m_crash1Sprite(m_crash1Texture),
	m_crash2Sprite(m_crash2Texture),
	m_hitHatSprite(m_hitHatTexture),
	m_clapSprite(m_clapTexture)
{
	setupDrums();
}

void DrumVisualiser::setupDrums()
{
	setupDrumSprites();
}

void DrumVisualiser::setupDrumSprites()
{
	// Kick
	if (!m_kickTexture.loadFromFile("ASSETS\\IMAGES\\Drum_Pieces\\Kick.png"))
	{
		std::cout << "problem loading Kick image" << std::endl;
	}
	m_kickSprite.setTexture(m_kickTexture, true);
	m_kickSprite.setScale(sf::Vector2f(1.0f, 1.0f));
	m_kickSprite.setPosition(sf::Vector2f{ m_drumPositions.x, m_drumPositions.y });

	// Snare
	if (!m_snareTexture.loadFromFile("ASSETS\\IMAGES\\Drum_Pieces\\Snare.png"))
	{
		std::cout << "problem loading Snare image" << std::endl;
	}
	m_snareSprite.setTexture(m_snareTexture, true);
	m_snareSprite.setScale(sf::Vector2f(1.0f, 1.0f));
	m_snareSprite.setPosition(sf::Vector2f{ m_drumPositions.x, m_drumPositions.y });

	// Floor Tom
	if (!m_floorTomTexture.loadFromFile("ASSETS\\IMAGES\\Drum_Pieces\\Floor Tom.png"))
	{
		std::cout << "problem loading Floor Tom image" << std::endl;
	}
	m_floorTomSprite.setTexture(m_floorTomTexture, true);
	m_floorTomSprite.setScale(sf::Vector2f(1.0f, 1.0f));
	m_floorTomSprite.setPosition(sf::Vector2f{ m_drumPositions.x, m_drumPositions.y });

	// Crash 1
	if (!m_crash1Texture.loadFromFile("ASSETS\\IMAGES\\Drum_Pieces\\Crash 1.png"))
	{
		std::cout << "problem loading Crash image" << std::endl;
	}
	m_crash1Sprite.setTexture(m_crash1Texture, true);
	m_crash1Sprite.setScale(sf::Vector2f(1.0f, 1.0f));
	m_crash1Sprite.setPosition(sf::Vector2f{ m_drumPositions.x, m_drumPositions.y });

	// Crash 2
	if (!m_crash2Texture.loadFromFile("ASSETS\\IMAGES\\Drum_Pieces\\Crash 2.png"))
	{
		std::cout << "problem loading Crash image" << std::endl;
	}
	m_crash2Sprite.setTexture(m_crash2Texture, true);
	m_crash2Sprite.setScale(sf::Vector2f(1.0f, 1.0f));
	m_crash2Sprite.setPosition(sf::Vector2f{ m_drumPositions.x, m_drumPositions.y });

	// Hi Hat
	if (!m_hitHatTexture.loadFromFile("ASSETS\\IMAGES\\Drum_Pieces\\Hi Hat.png"))
	{
		std::cout << "problem loading Hi Hat image" << std::endl;
	}
	m_hitHatSprite.setTexture(m_hitHatTexture, true);
	m_hitHatSprite.setScale(sf::Vector2f(1.0f, 1.0f));
	m_hitHatSprite.setPosition(sf::Vector2f{ m_drumPositions.x, m_drumPositions.y });

	// Tom Tom 1
	if (!m_TomTom1Texture.loadFromFile("ASSETS\\IMAGES\\Drum_Pieces\\TomTom 1.png"))
	{
		std::cout << "problem loading Tom Tom 1 image" << std::endl;
	}
	m_TomTom1Sprite.setTexture(m_TomTom1Texture, true);
	m_TomTom1Sprite.setScale(sf::Vector2f(1.0f, 1.0f));
	m_TomTom1Sprite.setPosition(sf::Vector2f{ m_drumPositions.x, m_drumPositions.y });

	// Tom Tom 2
	if (!m_TomTom2Texture.loadFromFile("ASSETS\\IMAGES\\Drum_Pieces\\TomTom 2.png"))
	{
		std::cout << "problem loading Tom Tom 2 image" << std::endl;
	}
	m_TomTom2Sprite.setTexture(m_TomTom2Texture, true);
	m_TomTom2Sprite.setScale(sf::Vector2f(1.0f, 1.0f));
	m_TomTom2Sprite.setPosition(sf::Vector2f{ m_drumPositions.x, m_drumPositions.y });

	// Clap
	if (!m_clapTexture.loadFromFile("ASSETS\\IMAGES\\Drum_Pieces\\Clap.png"))
	{
		std::cout << "problem loading Clap image" << std::endl;
	}
	m_clapSprite.setTexture(m_clapTexture, true);
	m_clapSprite.setScale(sf::Vector2f(1.0f, 1.0f));
	m_clapSprite.setPosition(sf::Vector2f{ m_drumPositions.x, m_drumPositions.y });
}

void DrumVisualiser::renderDrums(sf::RenderWindow& t_window)
{
	// Render pieces from back to front so they overlap like in the photoshop file
	t_window.draw(m_TomTom1Sprite);
	t_window.draw(m_TomTom2Sprite);
	t_window.draw(m_snareSprite);
	t_window.draw(m_floorTomSprite);
	t_window.draw(m_hitHatSprite);
	t_window.draw(m_crash1Sprite);
	t_window.draw(m_crash2Sprite);
	t_window.draw(m_kickSprite);
	t_window.draw(m_clapSprite);
}
