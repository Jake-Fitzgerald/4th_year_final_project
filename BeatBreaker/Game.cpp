#include "Game.h"
#include <iostream>
#include "GridDisplay.h"

// Defined before midiInput() function so it can be called later
void CALLBACK MidiInProc(
	HMIDIIN hMidiIn,
	UINT wMsg, // event type
	DWORD_PTR dwInstance, // custom user data (Piano Visualiser, Drum Visualiser)
	DWORD_PTR dwParam1, // more message data
	DWORD_PTR dwParam2 // timestamp for when it was received 
);


std::shared_ptr<const sf::Font> Game::loadFont()
{
	auto font = std::make_shared<const sf::Font>("ASSETS\\FONTS\\Jersey20-Regular.ttf");
	return font;
}

Game::Game() :
	m_window{ sf::VideoMode{ sf::Vector2u{SCREEN_WIDTH, SCREEN_HEIGHT}, 32U }, "Beat Breaker" },
	m_DELETEexitGame{false},
		m_jerseyFont(loadFont()),
		m_hud(*m_jerseyFont),
	    m_gameplay(m_soundManager, m_jerseyFont),
		m_options(m_jerseyFont, m_gameplay),
		trackVisualiser(m_jerseyFont),
	    drumVisualiser(m_jerseyFont, m_soundManager),
		m_midiFileSelectScene(m_jerseyFont),
		m_visSelect(m_jerseyFont),
		pianoVisualiser(m_soundManager, m_collisionManager),
	    m_songSelect(m_jerseyFont),
	    m_leaderboard(m_jerseyFont),
		m_mainMenu(m_jerseyFont),
	    m_gameOver(m_jerseyFont)
		//m_keyboard(m_soundManager),
		
{
	setupSprites(); // load texture
	setupAudio(); // load sounds

	// MIDI
	setupMidiParser();
	//setupMidiWrite();

	// Sound Manager
	setupSounds();

	// ----- VIUALISERS -----
	// Track Visualiser
	trackVisualiser.setupShapes();
	trackVisualiser.loadMidiTracks(m_midiParser.getMidiTracks(), m_midiParser.getTicksPerQuarter(), m_midiParser.getBPM());

	// Piano Visualiser
	pianoVisualiser.setupPianoShapes();
	pianoVisualiser.setupPianoSounds();

	// Drum Visualiser
	drumVisualiser.setupDrumSprites();
	//drumVisualiser.setupDrums();

	// HUD
	m_hud.loadMidiData( m_midiParser.getMidiTracks(),
						m_midiParser.getTimeSignature(),
						m_midiParser.getBPM(),
						m_midiParser.getMidiFileName(),
						m_midiParser.getNominator(),
						m_midiParser.getDenominator() );

	// Selection Scenes
	// Midi File Select
	m_midiFileSelectScene.setupPathStrings();
	m_midiFileSelectScene.setupSprites();
	m_midiFileSelectScene.setupButtons();
	// Visualiser Select
	m_visSelect.setupButtonsVisSelect();
	m_visSelect.setupSprites();
	// Song Select
	m_songSelect.setupPathStrings();
	m_songSelect.setupButtons();

	// UI 
	gridDisplay.setupGrid();
	gridDisplay.setupSprites();

	// Custom Icon
	setupCustomIcon();


	// Midi Input
	setupMidiInput();

	// Leaderboard / Results
	m_leaderboard.setupLeaderboard();
	m_leaderboard.populateFromDatabase(m_localLeaderboard);
	m_gameOver.setupGameOver();

	// Main Menu
	m_mainMenu.setupMainMenu();

	// Gameplay
	m_gameplay.setup();
}

Game::~Game()
{
}

void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}

void Game::processEvents()
{
	while (const std::optional newEvent = m_window.pollEvent())
	{
		if ( newEvent->is<sf::Event::Closed>()) // close window message 
		{
			m_DELETEexitGame = true;
		}
		if (newEvent->is<sf::Event::KeyPressed>()) //user pressed a key
		{
			processKeys(newEvent);
		}
		if (newEvent->is<sf::Event::KeyPressed>())
		{
			processKeysPressed(newEvent);
		}
		if (newEvent->is<sf::Event::MouseButtonReleased>())
		{
			processMouseRelease(newEvent);
		}
		sf::Event event = *newEvent;
		m_gameOver.handleEvent(event);
	}
}

void Game::processKeys(const std::optional<sf::Event> t_event)
{
	const sf::Event::KeyPressed *newKeypress = t_event->getIf<sf::Event::KeyPressed>();
	if (sf::Keyboard::Key::Escape == newKeypress->code)
	{
		m_DELETEexitGame = true; 
	}
	if (sf::Keyboard::Key::F1 == newKeypress->code)
	{
		if (b_isDebugActive == true)
		{
			b_isDebugActive = false;
		}
		else
		{
			b_isDebugActive = true;
		}
	}

	if (b_isDebugActive == true)
	{
		// Return to Main Menu
		if (sf::Keyboard::Key::Backspace == newKeypress->code)
		{
			m_currentGameState = GameStates::MainMenuScene;
		}
		// Toggle Grid Display
		if (sf::Keyboard::Key::G == newKeypress->code)
		{
			gridDisplay.toggleGridVisible();
		}

		// Drum Visualiser
		if (m_currentGameState == GameStates::DrumVis)
		{
			// Hitbox visible
			if (sf::Keyboard::Key::V == newKeypress->code)
			{
				drumVisualiser.toggleHitboxVis();
			}
		}

		// MCI Midi playback
		if (m_currentGameState == GameStates::MainMenuScene)
		{
			if (sf::Keyboard::Key::P == newKeypress->code)
			{
				playMidiMCI();
			}

			if (sf::Keyboard::Key::S == newKeypress->code)
			{
				stopMidiMCI();
			}
		}

		// SQL  
		if (sf::Keyboard::Key::L == newKeypress->code)
		{
			std::cerr << " " << std::endl;
			std::cerr << "========================" << std::endl;
			std::cerr << "Connecting to the server" << std::endl;
			std::cerr << "========================" << std::endl;
			std::cerr << " " << std::endl;

			if (m_database.sqlConnect(ODBCString) == true)
			{
				m_localLeaderboard = m_database.getLeaderboardData();
				m_leaderboard.populateFromDatabase(m_localLeaderboard);

				for (const USERDATA& entry : m_localLeaderboard)
				{
					std::cerr << entry.id << " " << entry.username << " " << entry.score << std::endl;
				}
			}
		}
		// Upload to database
		if (sf::Keyboard::Key::K == newKeypress->code)
		{

			std::string m_playerName = "TestName";
			int m_tempScore = 100;

			if (m_database.sqlConnect(ODBCString) == true)
			{
				//m_database.submitScore(m_playerName, m_tempScore);
				m_database.submitScoreFromFile(m_highscorePath);
			}
		}

		// Gamplay
		if (m_currentGameState == GameStates::GameplayScene)
		{
			if (sf::Keyboard::Key::P == newKeypress->code)
			{
				m_gameplay.startSong();
			}

			if (sf::Keyboard::Key::T == newKeypress->code)
			{
				bool triggerDisplay = m_gameplay.getTriggerDisplayFlag();
				if (triggerDisplay == true)
				{
					m_gameplay.setTriggerDisplayFlag(!triggerDisplay);
				}
				else
				{
					m_gameplay.setTriggerDisplayFlag(!triggerDisplay);
				}
			}
		}
	}

}

void Game::processKeysPressed(const std::optional<sf::Event> t_event)
{
	const sf::Event::KeyPressed* newKeyPress = t_event->getIf<sf::Event::KeyPressed>();
}

void Game::processMouseRelease(const std::optional<sf::Event> t_event)
{
	const sf::Event::MouseButtonReleased* newMouseReleased = t_event->getIf<sf::Event::MouseButtonReleased>();
	const sf::Vector2f mouseWorldPos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));

	if (m_currentGameState == MainMenuScene)
	{
		std::string clicked = m_mainMenu.mouseClick(mouseWorldPos);

		if (clicked == "Start")
		{
			stopMidiMCI();
			m_currentGameState = GameStates::SongSelectionScene;
			m_gameplay.resetSession();
			std::cout << "Start button clicked!" << std::endl;
			m_soundManager.play("ui_confirm");
		}
		if (clicked == "Midi Selection")
		{
			m_currentGameState = GameStates::MidiFileSelectScene;
			m_soundManager.play("ui_confirm");
		}
		if (clicked == "Record Midi")
		{
			setupMidiWrite();


		}
		if (clicked == "MIDI Parse")
		{
			m_midiParser.resetTrack();
			setupMidiParser();
			m_soundManager.play("ui_confirm");
		}
		if (clicked == "Vis Selection")
		{
			m_currentGameState = GameStates::VisualiserSelectScene;
			m_soundManager.play("ui_confirm");
		}
		if (clicked == "Options")
		{
			m_currentGameState = GameStates::OptionsScene;
			m_soundManager.play("ui_confirm");
		}
		if (clicked == "Leaderboard")
		{
			m_currentGameState = GameStates::LeaderboardScene;
			m_soundManager.play("ui_confirm");
		}
		if (clicked == "EXIT")
		{
			m_DELETEexitGame = true;
			m_soundManager.play("ui_confirm");
		}
	}
	else if (m_currentGameState == OptionsScene)
	{
		if (m_options.handleMouseClick(mouseWorldPos, m_hud, m_soundManager))
		{
			// If handleMouseClick returns true, go back to main menu
			m_currentGameState = MainMenuScene;
		}
	}
	else if (m_currentGameState == GameStates::MidiFileSelectScene) // File Selection
	{
		m_midiFileSelectScene.mouseClick(mouseWorldPos);

		m_midiPath = m_midiFileSelectScene.getMidiPathString();

		if (m_midiFileSelectScene.returnClick(mouseWorldPos) == true)
		{
			m_currentGameState = GameStates::MainMenuScene;
		}
	}
	else if (m_currentGameState == GameStates::VisualiserSelectScene) // Visualiser Selection
	{
		int buttonSelected = m_visSelect.mouseClick(mouseWorldPos);

		if (buttonSelected >= 0)  
		{
			m_visSelect.resetButtons();

			switch (buttonSelected)
			{
			case 0:
				m_currentGameState = GameStates::TrackVis;
				m_soundManager.play("ui_confirm");
				break;
			case 1:
				m_currentGameState = GameStates::PianoVis;
				m_soundManager.play("ui_confirm");
				break;
			case 2:
				m_currentGameState = GameStates::DrumVis;
				m_soundManager.play("ui_confirm");
				break;
			default:
				break;
			}
		}

		if (m_visSelect.returnClick(mouseWorldPos) == true)
		{
			m_visSelect.resetButtons();
			m_currentGameState = GameStates::MainMenuScene;
		}
	}
	else if (m_currentGameState == GameStates::PianoVis) // Piano Vis
	{
		pianoVisualiser.handleClick(mouseWorldPos);
	}
	else if (m_currentGameState == GameStates::DrumVis) // Piano Vis
	{
		drumVisualiser.handleClick(mouseWorldPos);
	}
	else if (m_currentGameState == GameStates::SongSelectionScene) // Song Selection
	{
		SongClickResult clickResult = m_songSelect.mouseClick(mouseWorldPos);

		if (clickResult == SongClickResult::SongSelected)
		{
			stopMidiMCI();
			m_midiPath = m_songSelect.getMidiPathString();
		}
		else if (clickResult == SongClickResult::PreviewClicked)
		{
			stopMidiMCI();
			m_midiPath = m_songSelect.getPreviewPathString();
			playMidiMCI();
		}
		else if (clickResult == SongClickResult::BeginClicked)
		{
			stopMidiMCI();

			m_selectedSong = m_songSelect.getMidiPathString();

			m_midiParser.parseFile(m_selectedSong);
			std::cerr << "Parsing song: " << m_selectedSong << std::endl;

			// Third track is the instrument track
			m_gameplay.loadTrack(m_midiParser.getMidiTracks()[2], m_midiParser.getBPM());

			std::filesystem::path path(m_selectedSong);
			std::string fileName = path.filename().string();
			m_gameplay.setSongName(fileName);

			m_soundManager.play("start_game");
			m_currentGameState = GameStates::GameplayScene;
		}

		if (m_songSelect.returnClick(mouseWorldPos) == true)
		{
			stopMidiMCI();
			m_currentGameState = GameStates::MainMenuScene;
		}
	}
	else if (m_currentGameState == GameStates::GameplayScene)
	{
		// Debugging with mouse
		m_gameplay.handleClick(mouseWorldPos);
		m_gameplay.handleRelease(mouseWorldPos);
	}
	
	// HUD
	// Play
	if (m_hud.playClick(mouseWorldPos) == true)
	{
		std::cerr << "Play button clicked" << std::endl;
		m_gameplay.startSong();
		m_soundManager.play("ui_cancel");
	}
	// Pause
	if (m_hud.pauseClick(mouseWorldPos) == true)
	{
		std::cerr << "Pause button clicked" << std::endl;
		m_gameplay.togglePause();
	}
	// Stop
	if (m_hud.stopClick(mouseWorldPos) == true)
	{
		std::cerr << "Stop button clicked" << std::endl;
		m_gameplay.resetSession();
	}
	// Skip to Start
	if (m_hud.skipToStart(mouseWorldPos) == true)
	{
		std::cerr << "Skip to start button clicked" << std::endl;
		m_gameplay.resetSession();
		m_gameplay.startSong();
	}
	// Skip to End
	if (m_hud.skipToEnd(mouseWorldPos) == true)
	{
		std::cerr << "Skip to end button clicked" << std::endl;
	}
	// Mute
	if (m_hud.muteClick(mouseWorldPos) == true)
	{
		std::cerr << "Mute button clicked" << std::endl; 
		m_options.muteSound(m_soundManager);
	}
	if (m_hud.returnClick(mouseWorldPos) == true)
	{
		m_soundManager.play("ui_cancel");
		if (m_currentGameState == GameStates::GameplayScene)
		{
			m_gameplay.resetSession();
		}
		
		m_currentGameState = GameStates::MainMenuScene;
	}

	// Check Modes Buttons
	bool buttonFound = false;
}


void Game::checkKeyboardState()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
	{
		m_DELETEexitGame = true; 
	}
}

void Game::processKeyboard(float dtSeconds)
{

}


void Game::update(sf::Time t_deltaTime)
{
	float dtConverted = t_deltaTime.asSeconds();

	checkKeyboardState();
	if (m_DELETEexitGame)
	{
		freeMidiHandler();

		m_window.close();
	}

	// FPS
	m_frameCount++;
	// Update FPS every 1 second
	if (m_fpsClock.getElapsedTime().asSeconds() >= 1.0f)
	{
		m_fps = m_frameCount / m_fpsClock.getElapsedTime().asSeconds();
		m_frameCount = 0;
		m_fpsClock.restart();
	}

	// UI
	if (m_hud.getFPSBool() == true)
	{
		m_hud.updateFPSText(m_fps);
	}

	drumVisualiser.updateIntroAnim(dtConverted);

	// Piano Note Test
	pianoVisualiser.updateNotes(dtConverted);

	// Gameplay
	if (m_currentGameState == GameStates::GameplayScene)
	{
		m_gameplay.update(dtConverted);

		if (m_gameplay.getSongFinishedFlag() == true)
		{
			m_gameOver.setScore(m_gameplay.getScore());
			m_gameOver.setRecordedNotes(m_gameplay.getRecordedNotes());
			m_gameOver.setSongName(m_gameplay.getSongName());
			m_gameOver.setupGameOver();
			m_currentGameState = GameStates::ResultsScene;
		}
	}
	if (m_currentGameState == GameStates::ResultsScene)
	{
		m_gameOver.update(dtConverted);

	}
}


void Game::render()
{
	m_window.clear(BG_COLOUR);
	
	// Main Menu
	if (m_currentGameState == GameStates::MainMenuScene)
	{
		m_mainMenu.render(m_window);
	}

	if (m_currentGameState == GameStates::GameplayScene)
	{
		m_gameplay.render(m_window);
	}
	// Options
	if (m_currentGameState == GameStates::OptionsScene)
	{
		m_options.renderOptions(m_window);
	}

	// ----- Selection Scenes -----
	// Midi File Select
	if (m_currentGameState == GameStates::MidiFileSelectScene)
	{
		m_midiFileSelectScene.render(m_window);
	}
	// Visualiser Select
	if (m_currentGameState == GameStates::VisualiserSelectScene)
	{
		m_visSelect.renderVisSelect(m_window);
	}
	// Song Select
	if (m_currentGameState == GameStates::SongSelectionScene)
	{
		m_songSelect.render(m_window);
	}

	// ----- Visualisers -----
	// Track Visualiser
	if (m_currentGameState == GameStates::TrackVis)
	{
		// visualiser shapes
		trackVisualiser.renderTrackVis(m_window);
	}
	// Piano Visualiser
	if (m_currentGameState == GameStates::PianoVis)
	{
		// visualiser shapes
		pianoVisualiser.renderKeys(m_window);
	}
	// Drum Visualiser
	if (m_currentGameState == GameStates::DrumVis)
	{
		// visualiser shapes
		drumVisualiser.renderDrums(m_window);
	}

	// Leaderboard
	if (m_currentGameState == GameStates::LeaderboardScene)
	{
		m_leaderboard.render(m_window);
	}
	// Leaderboard
	if (m_currentGameState == GameStates::ResultsScene)
	{
		m_gameOver.render(m_window);
	}

	// UI
	m_hud.drawHUD(m_window);
	gridDisplay.renderGrid(m_window);
	
	m_window.display();
}

void Game::setupSprites()
{
	if (!m_DELETElogoTexture.loadFromFile("ASSETS\\IMAGES\\SFML-LOGO.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	
	m_DELETElogoSprite.setTexture(m_DELETElogoTexture,true);// to reset the dimensions of texture
	m_DELETElogoSprite.setPosition(sf::Vector2f{ 150.0f, 50.0f });
}

void Game::setupAudio()
{
	if (!m_DELETEsoundBuffer.loadFromFile("ASSETS\\AUDIO\\beep.wav"))
	{
		std::cout << "Error loading beep sound" << std::endl;
	}
	//m_DELETEsound.play(); // test sound
	if (!m_soundBuffer.loadFromFile("ASSETS\\AUDIO\\SFX\\UI\\ui_cancel.wav"))
	{
		std::cout << "Error loading test sound" << std::endl;
	}
	//m_testSound.play();
}

bool Game::checkIfAreaClicked(sf::Vector2f t_mousePos, sf::Vector2f t_topLeft, sf::Vector2f t_size)
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

void Game::setupSounds()
{
	// UI
	m_soundManager.loadBuffer("ui_cancel", "ASSETS\\AUDIO\\SFX\\UI\\ui_cancel.wav", SoundType::SFX);
	m_soundManager.loadBuffer("ui_confirm", "ASSETS\\AUDIO\\SFX\\UI\\ui_confirm.wav", SoundType::MUSIC); // Test sound types [temp]
	m_soundManager.loadBuffer("difficulty_select", "ASSETS\\AUDIO\\SFX\\UI\\difficulty_select.wav", SoundType::SFX);
	m_soundManager.loadBuffer("results_scene_load", "ASSETS\\AUDIO\\SFX\\UI\\results_scene_load.wav", SoundType::SFX);
	m_soundManager.loadBuffer("start_game", "ASSETS\\AUDIO\\SFX\\UI\\start_game.wav", SoundType::SFX);

	// Music
	m_soundManager.loadBuffer("Test_MIDI_MUSIC", "ASSETS\\AUDIO\\MUSIC\\WAV\\Test_MIDI.wav", SoundType::MUSIC);

	// Player
	m_soundManager.loadBuffer("health_drain", "ASSETS\\AUDIO\\SFX\\PLAYER\\health_drain.wav", SoundType::SFX);
	m_soundManager.loadBuffer("player_crushed", "ASSETS\\AUDIO\\SFX\\PLAYER\\player_crushed.wav", SoundType::SFX);
	m_soundManager.loadBuffer("player_respawn", "ASSETS\\AUDIO\\SFX\\PLAYER\\player_respawn.wav", SoundType::SFX);

	// Gameplay
	m_soundManager.loadBuffer("block_break", "ASSETS\\AUDIO\\SFX\\GAMEPLAY\\block_break.wav", SoundType::SFX);
	m_soundManager.loadBuffer("item_health", "ASSETS\\AUDIO\\SFX\\GAMEPLAY\\item_health.wav", SoundType::SFX);
	m_soundManager.loadBuffer("item_life", "ASSETS\\AUDIO\\SFX\\GAMEPLAY\\item_life.wav", SoundType::SFX);
	m_soundManager.loadBuffer("next_track_phase", "ASSETS\\AUDIO\\SFX\\GAMEPLAY\\next_track_phase.wav", SoundType::SFX);
}

void Game::setupCustomIcon()
{
	// Custom Icon
	if (!m_customIcon.loadFromFile("ASSETS\\IMAGES\\UI\\Icons\\CustomIcon.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading Custom Image Icon" << std::endl;
	}

	m_window.setIcon(m_customIcon);
}

void Game::changeMidiPath(std::string t_pathName)
{
	m_midiPath = t_pathName;
}

void Game::setupMidiInput()
{
	midiKeyboardAmount = midiInGetNumDevs();
	std::cerr << "Midi keyboard amount connected: " << midiKeyboardAmount << std::endl;

	bool b_connectionStatus = false;

	if (midiKeyboardAmount == 0)
	{
		std::cerr << "No MIDI keyboads connected" << std::endl;

		// Update HUD's text
		b_connectionStatus = false;
		m_hud.updateMidiKeyboardConnnection(b_connectionStatus);
	}
	else
	{
		int validMidiID = -1;

		std::cerr << " " << std::endl;
		std::cerr << "Midi keyboard names: " << std::endl;
		std::cerr << " " << std::endl;

	    // https://learn.microsoft.com/en-us/windows/win32/api/mmeapi/ns-mmeapi-midiincaps // reference 
		for (int i = 0; i < midiKeyboardAmount; i++)
		{
			MIDIINCAPS deviceInfo;
	
		    // https://learn.microsoft.com/en-us/windows/win32/api/mmeapi/nf-mmeapi-midiingetdevcaps // reference 
			// Error check if the device can actually be used
			// device ID, pointer to MIDIINCAPS, size of MIDIINCAPS for error checking
			//bool b_result = midiInGetDevCaps(i, &deviceInfo, sizeof(MIDIINCAPS));
			MMRESULT b_result = midiInGetDevCaps(i, &deviceInfo, sizeof(MIDIINCAPS));

			if (b_result == MMSYSERR_NOERROR)
			{
				std::cerr << "[KEYBOARD " << i << "]" << std::endl;
				std::cerr << deviceInfo.szPname << std::endl;
				std::string deviceName = deviceInfo.szPname;
				//std::cerr << deviceInfo.vDriverVersion << std::endl;
				//std::cerr << HIWORD(deviceInfo.vDriverVersion) << " || " << LOWORD(deviceInfo.vDriverVersion) << std::endl; 
				//std::cerr << deviceInfo.wMid << std::endl; // Manufacturer ID (useless)
				//std::cerr << deviceInfo.wPid << std::endl; // Product ID (useless)
				//std::cerr << deviceInfo.dwSupport << std::endl; // "Reserved; must be zero" (unsure but not needed)

				if (deviceName == "MIDI function" || deviceName == "Microsoft GS Wavetable Synth")
				{
					std::cerr << "Skip mircrosoft midi: " << deviceName << std::endl;
					continue;
				}
				std::cerr << " " << std::endl;

				validMidiID = i;
				break;
			}
		}

		// Check if the device is valid if it got stopped by the error check
		if (validMidiID == -1)
		{
			std::cerr << "No MIDI keyboads connected" << std::endl;

			// Update HUD's text
			b_connectionStatus = false;
			m_hud.updateMidiKeyboardConnnection(b_connectionStatus);
			return;
		}

		// --------------------------------------------------------------------------------------------
		// Open a specific midi device for receiving messages
		// https://learn.microsoft.com/en-us/windows/win32/api/mmeapi/nf-mmeapi-midiinopen
		// handle is 'LPHMIDIIN', which is a pointer to 'HMIDIIN', 
		
		// https://learn.microsoft.com/en-us/dotnet/framework/interop/callback-functions
		//MMRESULT m_resultMidiOpen = midiInOpen(&handleMidiIn, validMidiID, (DWORD_PTR)&MidiInProc, 0, CALLBACK_FUNCTION);  

		m_midiCallbackData = { &pianoVisualiser, &drumVisualiser, &m_gameplay, &m_currentGameState };
		MMRESULT m_resultMidiOpen = midiInOpen(&handleMidiIn, validMidiID, (DWORD_PTR)&MidiInProc, (DWORD_PTR)&m_midiCallbackData, CALLBACK_FUNCTION);

		if (m_resultMidiOpen != MMSYSERR_NOERROR)
		{
			std::cerr << "Couldn't open midi keyboard: " << validMidiID << std::endl;

			// Update HUD's text
			b_connectionStatus = false;
			m_hud.updateMidiKeyboardConnnection(b_connectionStatus);
			return;
		}

		// --------------------------------------------------------------------------------------------
		midiInStart(handleMidiIn);

		std::cerr << "Midi keyboard: " << validMidiID << " opened" << std::endl;
		// Update HUD's text
		b_connectionStatus = true;
		m_hud.updateMidiKeyboardConnnection(b_connectionStatus);


		// --------------------------------------------------------------------------------------------
		// Specific Midi connection
		//int midiID = midiInGetID(hMidiIn, puDeviceID);

		//mciGetDeviceID();
		//LPHMIDIIN
		//midiInOpen();

	}
}

// Midi Callback
// https://learn.microsoft.com/en-us/previous-versions//dd798460(v=vs.85)
// Handle to the MIDI input device, MIDI input message, Instance data supplied with the midiInOpen function, Message parameter, Message parameter 
void CALLBACK MidiInProc(
	HMIDIIN hMidiIn,
	UINT wMsg, // event type
	DWORD_PTR dwInstance, // custom user data 
	DWORD_PTR dwParam1, // Note value, note velocity
	DWORD_PTR dwParam2 // timestamp for when it was received 
)
{
	// https://learn.microsoft.com/en-gb/windows/win32/multimedia/mim-data?redirectedfrom=MSDN
	UINT16 metaEvent = 0xFF;
	UINT16 messageTypeMask = 0xF0; 
	UINT16 channelTypeMask = 0x0F; // 0 - 15
	UINT16 noteOn = 0x90;
	UINT16 noteOff = 0x80;

	// Control Change flags 
	// Found in "Control Change Messages (Data Bytes).pdf" in documents
	UINT16 cc_flag = 0xB0;
	//UINT16 cc_volume = 0xB7;
	const int CC_BANKSELECT = 0;
	const int CC_MODWHEEL = 1;
	const int CC_CHANNELVOLUME = 7;
	const int CC_PAN = 10;
	const int CC_LSB_VOLUME = 27; 

	if (wMsg == MIM_DATA)
	{
		// Use unsigned char since it's 8 bits we need to read
		unsigned char msgFlag = dwParam1 & metaEvent; // low
		unsigned char msgData1 = (dwParam1 >> 8) & metaEvent; // middle
		unsigned char msgData2 = (dwParam1 >> 16) & metaEvent; // high

		// Channel
		unsigned char channel = msgFlag & channelTypeMask;

		// CC
		unsigned char cc_number = (dwParam1 >> 8) & 0xFF;
		unsigned char cc_type = (dwParam1 >> 16) & 0xFF;

		//std::cerr << "Message type: " << static_cast<int>(msgFlag) << std::endl;
		//std::cerr << "Message data 1 : " << static_cast<int>(msgData1) << std::endl;
		//std::cerr << "Message data 2 : " << static_cast<int>(msgData2) << std::endl;

		int msgType = static_cast<int>(msgFlag);
		int msgNote = static_cast<int>(msgData1);
		int msgVel = static_cast<int>(msgData2);

		if (msgType == cc_flag)
		{
			//if (cc_number == cc_modWheel)
			//{
			//	std::cerr << "CC - Modulator Wheel: " << static_cast<int>(cc_type) << std::endl;
			//}

			switch (cc_number)
			{
				case CC_BANKSELECT:
					std::cerr << "CC - Bank Select: " << static_cast<int>(cc_type) << std::endl;
					break;
				case CC_MODWHEEL:
					std::cerr << "CC - Modulator Wheel: " << static_cast<int>(cc_type) << std::endl;
					break;

			}
		}

		MidiCallbackData* callbackData = reinterpret_cast<MidiCallbackData*>(dwInstance);
		PianoVisualiser* pianoListener = callbackData->piano;
		DrumVisualiser* drumListener = callbackData->drums;
		Gameplay* gameplayListener = callbackData->gameplay;

		// Channel 10 is always drums
		if (channel == 9)
		{
			std::cerr << "Drum Pad: " << "Note: " << msgNote << " Velocity: " << msgVel << std::endl;

			if ((msgType & messageTypeMask) == noteOn && msgVel > 0)
			{
				if (drumListener)
				{
					drumListener->drumNoteOn(msgNote);
				}
			}
			if ((msgType & messageTypeMask) == noteOff || ((msgType & messageTypeMask) == noteOn && msgVel == 0))
			{
				if (drumListener)
				{
					drumListener->drumNoteOff(msgNote);
				}
			}
		}
		else
		{
			// 0 - 127 nad the middle C is at 60 (C4)
			// The note value for the lowest C on our keyboard is 48, so 48 / 12 = 4, 4 - 1 = 3, so we are in the third octave
			int octave = (msgNote / 12) - 1;
			std::string noteNames[12] = { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };
			std::string noteName = noteNames[msgNote % 12] + std::to_string(octave);

			// Get the Piano Visualiser pointer we are after passing into midiInOpen 
			// The compiler will know this address is our Piano Visualiser
			//PianoVisualiser* pianoListener = static_cast<PianoVisualiser*>((void*)dwInstance);
			//PianoVisualiser* pianoListener = reinterpret_cast<PianoVisualiser*>(dwInstance);
			
			//if (m_currentGameState == GameStates::PianoVis)
			if ((msgType & messageTypeMask) == noteOn && msgVel > 0)
			{
				std::cout << "Note ON: " << noteName << " Velocity: " << msgVel << std::endl;

				if (callbackData->currentState && *callbackData->currentState == GameStates::GameplayScene)
				{
					if (gameplayListener)
					{
						gameplayListener->noteOn(noteName, msgNote, msgVel);
					}
				}
				else 
				{
					if (pianoListener)
					{
						pianoListener->noteOn(noteName);
					}
				}
			}

			if ((msgType & messageTypeMask) == noteOff || (msgType & messageTypeMask) == noteOn && msgVel == 0)
			{
				std::cout << "Note OFF:" << noteName << " Velocity: " << msgVel << std::endl;

				if (callbackData->currentState && *callbackData->currentState == GameStates::GameplayScene)
				{
					if (gameplayListener)
					{
						gameplayListener->noteOff(noteName, msgNote, msgVel);
					}
				}
				else 
				{
					if (pianoListener)
					{
						pianoListener->noteOff(noteName);
					}
				}
			}
		}
	}
}

void Game::freeMidiHandler()
{
	// Check if a handler exists then reset it
	if (handleMidiIn != nullptr)
	{
		midiInStop(handleMidiIn);
		midiInClose(handleMidiIn);
		handleMidiIn = nullptr;
	}
}

// Uses window's built in midi player
void Game::playMidiMCI()
{
	std::cerr << "Playing MIDI File: " << m_midiPath << std::endl;
	MCIERROR err;
	// We need to convert the patha and the command to a c style string
	std::string pathAndCommand = "open \"" + m_midiPath + "\" type sequencer alias mciMIDI";
	

	// Open the MIDI file
	err = mciSendString(
		pathAndCommand.c_str(),
		//"open \"ASSETS\\AUDIO\\MUSIC\\test.mid\" type sequencer alias mymidi",
		NULL,
		0,
		NULL
	);

	if (err != 0)
	{
		std::cerr << "Can't open the Midi File" << std::endl;
	}
	else
	{
		mciSendString("play mciMIDI", NULL, 0, NULL);
	}

}

void Game::stopMidiMCI()
{
	std::cerr << "Stopping MIDI File: " << m_midiPath << std::endl;
	mciSendString("stop mciMIDI", NULL, 0, NULL);
	mciSendString("close mciMIDI", NULL, 0, NULL);
}


void Game::setupMidiParser()
{
	m_midiPath = m_midiFileSelectScene.getMidiPathString();
	m_midiParser.parseFile(m_midiPath);
	
	m_hud.loadMidiData( m_midiParser.getMidiTracks(),
						m_midiParser.getTimeSignature(),
						m_midiParser.getBPM(),
						m_midiParser.getMidiFileName(),
						m_midiParser.getNominator(),
						m_midiParser.getDenominator() );
}

void Game::setupMidiWrite()
{
	std::cerr << "Midi Write" << std::endl;
	std::string m_tempName = "temp"; // [DEBUGGING]
	m_midiWrite.writeFile(m_tempName);
}
