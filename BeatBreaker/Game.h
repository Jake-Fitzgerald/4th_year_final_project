#ifndef GAME_HPP
#define GAME_HPP
#pragma warning( push )
#pragma warning( disable : 4275 )
// ignore this warning
// C:\SFML - 3.0.0\include\SFML\System\Exception.hpp(41, 47) : 
// warning C4275 : non dll - interface class 'std::runtime_error' used as base for dll - interface class 'sf::Exception'

// Libraries
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Components
#include "MainMenu.h"


const sf::Color ULTRAMARINE{ 5, 55,242,255 }; // const colour

class Game
{
public:
	Game();
	~Game();
	void run();

private:

	void processEvents();
	void processKeys(const std::optional<sf::Event> t_event);
	void checkKeyboardState();
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupTexts();
	void setupSprites();
	void setupAudio();

	
	sf::RenderWindow m_window; 
	sf::Font m_jerseyFont;
	
	sf::Text m_DELETEwelcomeMessage{ m_jerseyFont }; 
	sf::Texture m_DELETElogoTexture;
	sf::Sprite m_DELETElogoSprite{ m_DELETElogoTexture }; 
	
	sf::SoundBuffer m_DELETEsoundBuffer; 
	sf::Sound m_DELETEsound{ m_DELETEsoundBuffer }; 
	bool m_DELETEexitGame; 

	// Main Menu
	MainMenu mainMenu;
};

#pragma warning( pop ) 
#endif // !GAME_HPP

