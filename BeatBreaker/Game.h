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
#include <vector>

// Components
#include "MainMenu.h"
#include "Block.h"
#include "BlockGenerator.h"

const sf::Vector2u WINDOW_SIZE = sf::VideoMode::getDesktopMode().size;

enum GameStates 
{
	MainMenu,
	Gameplay,
	GameOver
};

class Game
{
public:
	Game();
	~Game();
	void run();

private:

	void processEvents();
	void processKeys(const std::optional<sf::Event> t_event);
	void processMouseRelease(const std::optional<sf::Event> t_event);
	void checkKeyboardState();
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupTexts();
	void setupSprites();
	void setupAudio();
	void setupMainMenu();

	bool checkIfAreaClicked(sf::Vector2f t_mousePos, sf::Vector2f t_topLeft, sf::Vector2f t_size);
	void setupGrid();

	
	sf::RenderWindow m_window; 
	sf::Font m_jerseyFont;
	
	sf::Text m_DELETEwelcomeMessage{ m_jerseyFont }; 
	sf::Texture m_DELETElogoTexture;
	sf::Sprite m_DELETElogoSprite{ m_DELETElogoTexture }; 
	
	sf::SoundBuffer m_DELETEsoundBuffer; 
	sf::Sound m_DELETEsound{ m_DELETEsoundBuffer }; 
	bool m_DELETEexitGame; 

	// Main Menu
	//MainMenu mainMenu;

	// Main Menu Variables
	sf::Vector2f m_topLeftStart{ 200,200 };
	float m_buttonSep = 30;

	// Main Menu Text
	std::unique_ptr<sf::Text>m_title;
	// ----------- Buttons ----------- 
	// Start Gameplay
	sf::RectangleShape m_startButton;
	sf::Text m_startText{ m_jerseyFont };
	// Random Gen
	sf::RectangleShape m_randGenButton;
	sf::Text m_randGenText{ m_jerseyFont };
	// Input Test
	sf::RectangleShape m_testInputButton;
	sf::Text m_testInputText{ m_jerseyFont };
	// MIDI Parse
	sf::RectangleShape m_MIDIParseButton;
	sf::Text m_MIDIParseText{ m_jerseyFont };
	// Character Test
	sf::RectangleShape m_characterButton;
	sf::Text m_characterText{ m_jerseyFont };

	// States
	GameStates m_currentGameState = GameStates::MainMenu;

	// Test Blocks
	const int COLS = 8;   
	const int ROWS = 12;  
	const float CELL_WIDTH = 50.f;
	const float CELL_HEIGHT = 50.f;
	std::vector<sf::RectangleShape> m_grid;

	// Block colours
	sf::Color BLUE = sf::Color::Blue;
	sf::Color PINK = sf::Color::Magenta;
	sf::Color GREEN = sf::Color::Green;
	sf::Color YELLOW = sf::Color::Yellow;
	// Colour vector
	std::vector<sf::Color> colors = { BLUE, PINK, GREEN, YELLOW };

	
	
};

#pragma warning( pop ) 
#endif // !GAME_HPP

