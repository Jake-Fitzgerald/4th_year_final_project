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
#include <filesystem>

// Components
#include "SoundManager.h"
#include "CollisionManager.h"

// Scenes
#include "MainMenu.h"
#include "Options.h"

// Selection Scenes
#include "MidiFileSelect.h"
#include "VisualiserSelect.h"
#include "SongSelect.h"

// MIDI
#include "MIDIParse.h"
#include "MidiWrite.h"

// UI
#include "HUD.h"
#include "GridDisplay.h"
#include "BG_Scroll.h"

// Utilities
#include "Globals.h"
// winmm.lib
#include <windows.h>
#include "Keyboard.h"

// Visualisers
#include "TrackVisualiser.h"
#include "PianoVisualiser.h"
#include "DrumVisualiser.h"

// SQL
#include "Database.h"
#include <sql.h>
#include <sqlext.h>
#pragma comment(lib, "odbc32.lib")

// Leaderboard / Results
#include "Leaderboard.h"
#include "GameOver.h";

// Gameplay
#include "Gameplay.h"

const sf::Vector2u WINDOW_SIZE = sf::VideoMode::getDesktopMode().size;

enum GameStates 
{
	MainMenuScene,
	GameplayScene,
	OptionsScene,
	ResultsScene,

	// Selection scenes
	MidiFileSelectScene,
	VisualiserSelectScene,
	SongSelectionScene,

	// Visualisers
	TrackVis,
	PianoVis,
	DrumVis,

	// Leaderboard
	LeaderboardScene,

	RecordScene
};

struct MidiCallbackData
{
	PianoVisualiser* piano;
	DrumVisualiser* drums;
	Gameplay* gameplay;
	GameStates* currentState;
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
	void processMouseRelease(const std::optional<sf::Event> t_event);
	void checkKeyboardState();
	void processKeyboard(float dtSeconds); // By frame
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupSprites();
	void setupAudio();
	void setupSounds();
	void setupCustomIcon();

	bool checkIfAreaClicked(sf::Vector2f t_mousePos, sf::Vector2f t_topLeft, sf::Vector2f t_size);

	void changeMidiPath(std::string t_pathName);
	void changeGameState();

	// Midi Input
	void setupMidiInput();
	void freeMidiHandler();

	// MCI Midi Playback
	void playMidiMCI();
	void stopMidiMCI();


	sf::RenderWindow m_window; 
	//sf::Font m_jerseyFont;
	std::shared_ptr<const sf::Font> m_jerseyFont;
	
	sf::Texture m_DELETElogoTexture;
	sf::Sprite m_DELETElogoSprite{ m_DELETElogoTexture }; 
	
	sf::SoundBuffer m_DELETEsoundBuffer; 
	sf::Sound m_DELETEsound{ m_DELETEsoundBuffer }; 
	bool m_DELETEexitGame; 
	bool b_isDebugActive = false;

	// States
	GameStates m_currentGameState = GameStates::ResultsScene;

	// MIDI
	MIDIParse m_midiParser;
	void setupMidiParser();
	void updateHUDMidi();
	std::string m_midiPath = "ASSETS\\AUDIO\\MUSIC\\Kick_and_Clap_2_track.mid";
	MidiWrite m_midiWrite;
	std::string m_midiWritePath = "ASSETS\\AUDIO\\MUSIC\\SavedMidi\\";
	void setupMidiWrite();

	// UI
	HUD m_hud;
	BG_Scroll m_bgScroll_1;

	// FPS
	sf::Clock m_fpsClock;
	float m_fps = 0.0f;
	int m_frameCount = 0;
	// BG
	const sf::Color BG_COLOUR{ 100, 150, 200, 80 };

	// Options
	Options m_options;

	// Audio
	sf::SoundBuffer m_soundBuffer;
	const int m_soundPoolSize = 200;
	SoundManager m_soundManager;
	SoundType m_soundType;

	CollisionManager m_collisionManager;

	// ----- Visualisers -----
	// Track Visualiser
	TrackVisualiser trackVisualiser;
	PianoVisualiser pianoVisualiser;
	DrumVisualiser drumVisualiser;

	// Overlays
	GridDisplay gridDisplay;

	// Selection Scenes
	MidiFileSelect m_midiFileSelectScene;
	VisualiserSelect m_visSelect;
	SongSelect m_songSelect;
	std::string m_selectedSong = "";
	MainMenu m_mainMenu;

	// Custom Icon
	sf::Image m_customIcon;

	// MIDI Input
	int midiKeyboardAmount = 0;
	HMIDIIN handleMidiIn = nullptr;

	// Midi Input Custom Data
	MidiCallbackData m_midiCallbackData;

	// SQL
	Database m_database;
	std::vector<USERDATA> m_localLeaderboard;
	std::string ODBCString = "Driver={ODBC Driver 18 for SQL Server};Server=beatbreakerserversql.database.windows.net,1433;Database=beatbreakerSQL;Uid=JakeAdmin;Pwd=ToyMachine7;Encrypt=yes;TrustServerCertificate=no;Connection Timeout=30;";
	std::string m_highscorePath = "ASSETS/SAVEDATA/Highscores_Saves/saved scores.txt";

	// Leaderboard
	Leaderboard m_leaderboard;
	GameOver m_gameOver;

	// Gameplay
	Gameplay m_gameplay;
	//Keyboard m_keyboard;
};

#pragma warning( pop ) 
#endif // !GAME_HPP

