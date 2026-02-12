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
#include "Block.h"
#include "BlockGenerator.h"
#include "Player.h"
#include "SoundManager.h"
#include "CollisionManager.h"

// Scenes
#include "MainMenu.h"
#include "Options.h"
#include "MidiFileSelect.h"
#include "VisualiserSelect.h"

// MIDI
#include "MIDIParse.h"

// UI
#include "HUD.h"
#include "GridDisplay.h"

// Utilities
#include "Globals.h"
// window's midi player Vimm ?

// Visualisers
#include "TrackVisualiser.h"
#include "PianoVisualiser.h"
#include "DrumVisualiser.h"
#include "SheetVisualiser.h"

const sf::Vector2u WINDOW_SIZE = sf::VideoMode::getDesktopMode().size;

enum GameStates 
{
	MainMenu,
	Gameplay,
	RandGen,
	OptionsScene,
	Character,
	GameOver,

	// Selection scenes
	MidiFileSelectScene,
	VisualiserSelectScene,

	// Visualisers
	TrackVis,
	PianoVis,
	DrumVis
	//SheetVis
};

enum Difficulties
{
	Easy,
	Medium,
	Hard
};

class Game
{
public:
	Game();
	~Game();
	void run();

private:
	static std::shared_ptr<const sf::Font> loadFont();


	void processEvents();
	void processKeys(const std::optional<sf::Event> t_event);
	void processKeysPressed(const std::optional<sf::Event> t_event);
	void processKeysRelease(const std::optional<sf::Event> t_event);
	void processMouseRelease(const std::optional<sf::Event> t_event);
	void checkKeyboardState();
	void processKeyboard(float dtSeconds); // By frame
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupTexts();
	void setupSprites();
	void setupAudio();
	void setupMainMenu();

	bool checkIfAreaClicked(sf::Vector2f t_mousePos, sf::Vector2f t_topLeft, sf::Vector2f t_size);
	void setupGrid();

	void setupPlayer();

	void setupSounds();

	void setupCustomIcon();

	void changeMidiPath(std::string t_pathName);
	void changeGameState();

	
	sf::RenderWindow m_window; 
	//sf::Font m_jerseyFont;
	std::shared_ptr<const sf::Font> m_jerseyFont;
	
	sf::Text m_beatBreakerText/*{ m_jerseyFont }*/; 
	sf::Texture m_DELETElogoTexture;
	sf::Sprite m_DELETElogoSprite{ m_DELETElogoTexture }; 
	
	sf::SoundBuffer m_DELETEsoundBuffer; 
	sf::Sound m_DELETEsound{ m_DELETEsoundBuffer }; 
	bool m_DELETEexitGame; 

	// Main Menu
	//MainMenu mainMenu;

	// Main Menu Variables
	sf::Vector2f m_topLeftStart{ paddingX, paddingY + 100.0f };
	float m_buttonSpacing = 100.0f;
	sf::Vector2f m_buttonSize = { 300.0f, 50.0f };


	// Main Menu Text
	//std::unique_ptr<sf::Text>m_title;
	// ----------- Buttons ----------- 
	// Start Gameplay
	sf::RectangleShape m_startButton;
	sf::Text m_startText/*{ m_jerseyFont }*/;
	// Midi Select 
	sf::RectangleShape m_midiSelectButton;
	sf::Text m_midiSelectText/*{ m_jerseyFont }*/;
	// Input Test
	sf::RectangleShape m_testInputButton;
	sf::Text m_testInputText/*{ m_jerseyFont }*/;
	// MIDI Parse
	sf::RectangleShape m_MIDIParseButton;
	sf::Text m_MIDIParseText/*{ m_jerseyFont }*/;
	// Visualiser Select
	sf::RectangleShape m_visSelectButton;
	sf::Text m_visSelectText/*{ m_jerseyFont }*/;
	// Options 
	sf::RectangleShape m_optionsButton;
	sf::Text m_optionsText/*{ m_jerseyFont }*/;
	// Exit 
	sf::RectangleShape m_exitButton;
	sf::Text m_exitText/*{ m_jerseyFont }*/;

	// States
	GameStates m_currentGameState = GameStates::MainMenu;

	// Test Blocks
	const int COLS = 8;   
	const int ROWS = 12;  
	const float CELL_WIDTH = 50.f;
	const float CELL_HEIGHT = 50.f;
	std::vector<sf::RectangleShape> m_grid;

	// Block colours				[DEBUG]
	sf::Color BLUE = sf::Color::Blue;
	sf::Color PINK = sf::Color::Magenta;
	sf::Color GREEN = sf::Color::Green;
	sf::Color YELLOW = sf::Color::Yellow;
	// Colour vector
	std::vector<sf::Color> colors = { BLUE, PINK, GREEN, YELLOW };

	// MIDI
	MIDIParse midiParser;
	void setupMidiParser();
	std::string m_midiPath = "ASSETS\\AUDIO\\MUSIC\\Kick_and_Clap_2_track.mid";
	
	// Player
	Player m_player;

	// UI
	HUD m_hud;
	// FPS
	sf::Clock m_fpsClock;
	float m_fps = 0.0f;
	int m_frameCount = 0;
	// BG
	const sf::Color BG_COLOUR{ 60, 30, 80, 50 };

	// Options
	Options m_options;

	// Audio
	sf::SoundBuffer m_soundBuffer;
	sf::Sound m_testSound{ m_soundBuffer };
	const int m_soundPoolSize = 50;
	SoundManager m_soundManager;
	SoundType m_soundType;

	// TEST Collision
	sf::RectangleShape m_testBlockShape;
	sf::RectangleShape m_floorShape;
	sf::RectangleShape m_wallLeftShape;
	sf::RectangleShape m_wallRightShape;

	CollisionManager m_collisionManager;

	// Block Generation
	BlockGenerator m_blockGen;

	// ----- Visualisers -----
	// Track Visualiser
	TrackVisualiser trackVisualiser;
	PianoVisualiser pianoVisualiser;
	DrumVisualiser drumVisualiser;
	SheetVisualiser sheetVisualiser;

	// UI
	// Overlays
	GridDisplay gridDisplay;

	// Selection Scenes
	MidiFileSelect m_midiFileSelectScene;
	VisualiserSelect m_visSelect;


	// Custom Icon
	sf::Image m_customIcon;

};

#pragma warning( pop ) 
#endif // !GAME_HPP

