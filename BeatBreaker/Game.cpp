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
		m_beatBreakerText(*m_jerseyFont), 
		m_startText(*m_jerseyFont),
		m_midiSelectText(*m_jerseyFont),
		m_testInputText(*m_jerseyFont),
		m_MIDIParseText(*m_jerseyFont),
		m_visSelectText(*m_jerseyFont),
		m_optionsText(*m_jerseyFont),
		m_exitText(*m_jerseyFont),
		m_hud(*m_jerseyFont),
		m_options(*m_jerseyFont),
		trackVisualiser(m_jerseyFont),
	    drumVisualiser(m_jerseyFont, m_soundManager),
		m_midiFileSelectScene(m_jerseyFont),
		m_visSelect(m_jerseyFont),
		pianoVisualiser(m_soundManager, m_collisionManager),
	    m_songSelect(m_jerseyFont),
	    m_leaderboard(m_jerseyFont)

{
	setupTexts(); // load font 
	setupSprites(); // load texture
	setupAudio(); // load sounds
	setupMainMenu();

	setupGrid();

	// MIDI
	setupMidiParser();

	// Sound Manager
	setupSounds();
	
	m_testBlockShape.setSize(sf::Vector2f(100.0f, 100.0f));
	m_testBlockShape.setPosition(sf::Vector2f{ 400.0f, 50.0f });
	m_collisionManager.addCollidable(m_testBlockShape, "BLOCK");
	// Floor
	m_floorShape.setSize(sf::Vector2f(800.0f, 10.0f));
	m_floorShape.setPosition(sf::Vector2f{ 100.0f, 200.0f });
	m_floorShape.setFillColor(sf::Color::Black);
	m_collisionManager.addCollidable(m_floorShape, "FLOOR");
	// Left Wall
	m_wallLeftShape.setSize(sf::Vector2f(10.0f, 800.0f));
	m_wallLeftShape.setPosition(sf::Vector2f{ 50.0f, 10.0f });
	m_wallLeftShape.setFillColor(sf::Color::Black);
	m_collisionManager.addCollidable(m_wallLeftShape, "WALL");
	// Right Wall
	m_wallRightShape.setSize(sf::Vector2f(10.0f, 800.0f));
	m_wallRightShape.setPosition(sf::Vector2f{ 500.0f, 10.0f });
	m_wallRightShape.setFillColor(sf::Color::Black);
	m_collisionManager.addCollidable(m_wallRightShape, "WALL");

	// Block Gen Test
	m_blockGen.setDifficulty("EASY");
	//m_blockGen.setDifficulty("HARD");
	m_blockGen.genRandomPattern(10);

	// ----- VIUALISERS -----
	// Track Visualiser
	trackVisualiser.setupShapes();
	trackVisualiser.loadMidiTracks(midiParser.getMidiTracks(), midiParser.getTicksPerQuarter(), midiParser.getBPM());

	// Piano Visualiser
	pianoVisualiser.setupPianoShapes();
	pianoVisualiser.setupPianoSounds();

	// Drum Visualiser
	drumVisualiser.setupDrumSprites();
	//drumVisualiser.setupDrums();

	// HUD
	m_hud.loadMidiData( midiParser.getMidiTracks(),
						midiParser.getTimeSignature(),
						midiParser.getBPM(),
						midiParser.getMidiFileName(),
						midiParser.getNominator(),
						midiParser.getDenominator() );

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

	// Custom Icon
	setupCustomIcon();


	// Midi Input
	setupMidiInput();

	// Leaderboard
	m_leaderboard.setupLeaderboard();
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
		if (newEvent->is<sf::Event::KeyPressed>())
		{
			processKeysRelease(newEvent);
		}
		if (newEvent->is<sf::Event::MouseButtonReleased>())
		{
			processMouseRelease(newEvent);
		}
	}
}

void Game::processKeys(const std::optional<sf::Event> t_event)
{
	const sf::Event::KeyPressed *newKeypress = t_event->getIf<sf::Event::KeyPressed>();
	if (sf::Keyboard::Key::Escape == newKeypress->code)
	{
		m_DELETEexitGame = true; 
	}
	// Return to Main Menu
	if (sf::Keyboard::Key::Backspace == newKeypress->code)
	{
		m_currentGameState = GameStates::MainMenu;
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
	if (m_currentGameState == GameStates::MainMenu)
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
		if (m_database.sqlConnect("Driver={ODBC Driver 18 for SQL Server};Server=beatbreakerserversql.database.windows.net,1433;Database=beatbreakerSQL;Uid=JakeAdmin;Pwd=ToyMachine7;Encrypt=yes;TrustServerCertificate=no;Connection Timeout=30;") == true)
		{
			std::vector<USERDATA> leaderboard = m_database.getLeaderboardData();

			for (const USERDATA& entry : leaderboard)
			{
				std::cerr << entry.id << " " << entry.username << " " << entry.score << std::endl;
			}
		}
	}
}

void Game::processKeysPressed(const std::optional<sf::Event> t_event)
{
	const sf::Event::KeyPressed* newKeyPress = t_event->getIf<sf::Event::KeyPressed>();
}

void Game::processKeysRelease(const std::optional<sf::Event> t_event)
{
}

void Game::processMouseRelease(const std::optional<sf::Event> t_event)
{
	const sf::Event::MouseButtonReleased* newMouseReleased = t_event->getIf<sf::Event::MouseButtonReleased>();
	const sf::Vector2f mouseWorldPos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));

	if (m_currentGameState == MainMenu)
	{
		// Gameplay
		if (checkIfAreaClicked(mouseWorldPos, m_startButton.getPosition(), m_startButton.getSize()))
		{
			stopMidiMCI();
			//m_currentGameState = GameStates::Gameplay;
			m_currentGameState = GameStates::SongSelectionScene;
			std::cout << "Start button clicked!" << std::endl;
			m_testSound.play();
		}

		// Visual Select Button
		if (checkIfAreaClicked(mouseWorldPos, m_visSelectButton.getPosition(), m_visSelectButton.getSize()))
		{
			m_currentGameState = GameStates::VisualiserSelectScene;
		}
		// Options
		if (checkIfAreaClicked(mouseWorldPos, m_optionsButton.getPosition(), m_optionsButton.getSize()))
		{
			m_currentGameState = GameStates::OptionsScene;
			m_soundManager.play("ui_confirm"/*, SoundType::MUSIC*/);
		}
		// Midi Select Button
		if (checkIfAreaClicked(mouseWorldPos, m_midiSelectButton.getPosition(), m_midiSelectButton.getSize()))
		{
			m_soundManager.play("ui_cancel"/*, SoundType::SFX*/);
			m_soundManager.play("ui_confirm"/*, SoundType::MUSIC*/);
			m_currentGameState = GameStates::MidiFileSelectScene;
		}
		// Midi Parse Button
		if (checkIfAreaClicked(mouseWorldPos, m_MIDIParseButton.getPosition(), m_MIDIParseButton.getSize()))
		{
			m_soundManager.play("ui_cancel"/*, SoundType::SFX*/);
			m_soundManager.play("ui_confirm"/*, SoundType::MUSIC*/);
			// Reset Midi Tracks
			midiParser.resetTrack();
			setupMidiParser();
		}
		// Exit
		if (checkIfAreaClicked(mouseWorldPos, m_exitButton.getPosition(), m_exitButton.getSize()))
		{
			m_DELETEexitGame = true;
		}
	}
	else if (m_currentGameState == OptionsScene)
	{
		if (m_options.handleMouseClick(mouseWorldPos, m_hud, m_soundManager))
		{
			// If handleMouseClick returns true, go back to main menu
			m_currentGameState = MainMenu;
		}
	}
	else if (m_currentGameState == GameStates::MidiFileSelectScene) // File Selection
	{
		m_midiFileSelectScene.mouseClick(mouseWorldPos);

		m_midiPath = m_midiFileSelectScene.getMidiPathString();

		if (m_midiFileSelectScene.returnClick(mouseWorldPos) == true)
		{
			m_currentGameState = GameStates::MainMenu;
		}
	}
	else if (m_currentGameState == GameStates::VisualiserSelectScene) // Visualiser Selection
	{
		int buttonSelected = m_visSelect.mouseClick(mouseWorldPos);

		if (buttonSelected >= 0)  
		{
			switch (buttonSelected)
			{
			case 0:
				m_currentGameState = GameStates::TrackVis;
				break;
			case 1:
				m_currentGameState = GameStates::PianoVis;
				break;
			case 2:
				m_currentGameState = GameStates::DrumVis;
				break;
			default:
				break;
			}
		}

		if (m_visSelect.returnClick(mouseWorldPos) == true)
		{
			m_currentGameState = GameStates::MainMenu;
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

		if (m_songSelect.returnClick(mouseWorldPos) == true)
		{
			stopMidiMCI();
			m_currentGameState = GameStates::MainMenu;
		}
	}
	
	// HUD

	// Play
	if (m_hud.playClick(mouseWorldPos) == true)
	{
		std::cerr << "Play button clicked" << std::endl;
		
	}

	// Pause
	if (m_hud.pauseClick(mouseWorldPos) == true)
	{
		std::cerr << "Pause button clicked" << std::endl;

	}

	// Stop
	if (m_hud.stopClick(mouseWorldPos) == true)
	{
		std::cerr << "Stop button clicked" << std::endl;

	}

	// Skip to Start
	if (m_hud.skipToStart(mouseWorldPos) == true)
	{
		std::cerr << "Skip to start button clicked" << std::endl;

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
		m_currentGameState = GameStates::MainMenu;
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		pianoVisualiser.spawnTestNote();
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
	
	// Block Collision															// LOOK AT THIS FOR REFERENCE FOR COLLIDERS FOR KEYS
	//if (m_collisionManager.checkCollision(m_player.getHitbox(), "BLOCK"))
	//{
	//	m_player.revertPosition();
	//	m_player.updatePlayer(dtConverted);
	//}

	drumVisualiser.updateIntroAnim(dtConverted);

	// Piano Note Test
	pianoVisualiser.updateNotes(dtConverted);
}


void Game::render()
{
	m_window.clear(BG_COLOUR);
	
	// Main Menu
	//mainMenu.render(m_window);
	if (m_currentGameState == GameStates::MainMenu)
	{
		m_window.draw(m_beatBreakerText);
		// Start
		m_window.draw(m_startButton);
		m_window.draw(m_startText);
		// Rand Gen
		m_window.draw(m_midiSelectButton);
		m_window.draw(m_midiSelectText);
		// Input Test
		m_window.draw(m_testInputButton);
		m_window.draw(m_testInputText);
		// MIDI Parse
		m_window.draw(m_MIDIParseButton);
		m_window.draw(m_MIDIParseText);
		// Character
		m_window.draw(m_visSelectButton);
		m_window.draw(m_visSelectText);
		// Options
		m_window.draw(m_optionsButton);
		m_window.draw(m_optionsText);
		// Exit Button
		m_window.draw(m_exitButton);
		m_window.draw(m_exitText);
	}

	if (m_currentGameState == GameStates::Gameplay)
	{
		for (const auto& cell : m_grid)
		{
			m_window.draw(cell);
		}
	}
	// Options
	if (m_currentGameState == GameStates::OptionsScene)
	{
		m_options.renderOptions(m_window);
	}
	// Rand Gen
	if (m_currentGameState == GameStates::RandGen)
	{
		m_blockGen.renderBlocks(m_window);
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

	// UI
	m_hud.drawHUD(m_window);
	gridDisplay.renderGrid(m_window);
	
	m_window.display();
}

void Game::setupTexts()
{
	//auto font = std::make_shared<sf::Font>();
	//if (!font->openFromFile("ASSETS\\FONTS\\Jersey20-Regular.ttf"))
	//{
	//	std::cout << "problem loading arial black font" << std::endl;
	//}
	//m_jerseyFont = std::static_pointer_cast<const sf::Font>(font);


	//m_beatBreakerText.setFont(m_jerseyFont);
	m_beatBreakerText = sf::Text(*m_jerseyFont);
	m_beatBreakerText.setString("Beat Breaker");
	m_beatBreakerText.setPosition(sf::Vector2f{ SCREEN_CENTRE.x - 200.0f, SCREEN_CENTRE.y - 350.0f});
	m_beatBreakerText.setCharacterSize(80U);
	m_beatBreakerText.setOutlineColor(sf::Color::Black);
	m_beatBreakerText.setFillColor(sf::Color::Red);
	m_beatBreakerText.setOutlineThickness(2.0f);


	// Start Text
	m_startText = sf::Text(*m_jerseyFont);
	m_startText.setString("Start");
	m_startText.setPosition(m_startButton.getPosition());
	m_startText.setCharacterSize(40U);
	m_startText.setFillColor(sf::Color::Black);
	// Rand Gen Text
	//m_midiSelectText.setFont(*m_jerseyFont);
	m_midiSelectText = sf::Text(*m_jerseyFont);
	m_midiSelectText.setString("Midi Selection");
	m_midiSelectText.setPosition(m_midiSelectButton.getPosition());
	m_midiSelectText.setCharacterSize(40U);
	m_midiSelectText.setFillColor(sf::Color::Black);
	// Input Test Text
	//m_testInputText.setFont(*m_jerseyFont);
	m_testInputText = sf::Text(*m_jerseyFont);
	m_testInputText.setString("Input Test");
	m_testInputText.setPosition(m_testInputButton.getPosition());
	m_testInputText.setCharacterSize(40U);
	m_testInputText.setFillColor(sf::Color::Black);
	// MIDI Parse Text
	//m_MIDIParseText.setFont(*m_jerseyFont);
	m_MIDIParseText = sf::Text(*m_jerseyFont);
	m_MIDIParseText.setString("MIDI Parse");
	m_MIDIParseText.setPosition(m_MIDIParseButton.getPosition());
	m_MIDIParseText.setCharacterSize(40U);
	m_MIDIParseText.setFillColor(sf::Color::Black);
	// Character Text
	//m_visSelectText.setFont(*m_jerseyFont);
	m_visSelectText = sf::Text(*m_jerseyFont);
	m_visSelectText.setString("Vis Selection");
	m_visSelectText.setPosition(m_visSelectButton.getPosition());
	m_visSelectText.setCharacterSize(40U);
	m_visSelectText.setFillColor(sf::Color::Black);
	// Options Menu Text
	//m_optionsText.setFont(*m_jerseyFont);
	m_optionsText = sf::Text(*m_jerseyFont);
	m_optionsText.setString("Options");
	m_optionsText.setPosition(m_optionsButton.getPosition());
	m_optionsText.setCharacterSize(40U);
	m_optionsText.setFillColor(sf::Color::Black);
	// Exit Menu Text
	//m_exitText.setFont(*m_jerseyFont);
	m_exitText = sf::Text(*m_jerseyFont);
	m_exitText.setString("EXIT");
	m_exitText.setPosition(m_exitButton.getPosition());
	m_exitText.setCharacterSize(40U);
	m_exitText.setFillColor(sf::Color::Black);

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

void Game::setupMainMenu()
{
	// Start
	m_startButton.setPosition(sf::Vector2f{ m_topLeftStart.x, m_topLeftStart.y });
	m_startButton.setSize(m_buttonSize);
	m_startButton.setFillColor(sf::Color::Blue);
	sf::Vector2f startTextOffset = { m_startButton.getPosition().x + m_startButton.getSize().x / 4.0f, m_startButton.getPosition().y };
	m_startText.setPosition(startTextOffset);

	// Midi Select
	m_midiSelectButton.setPosition(sf::Vector2f{ m_topLeftStart.x, m_topLeftStart.y + m_buttonSpacing});
	m_midiSelectButton.setSize(m_buttonSize);
	m_midiSelectButton.setFillColor(sf::Color::Blue);
	sf::Vector2f midiSelectTextOffset = { m_midiSelectButton.getPosition().x + 20.0f, m_midiSelectButton.getPosition().y };
	m_midiSelectText.setPosition(midiSelectTextOffset);

	// Input Test
	m_testInputButton.setPosition(sf::Vector2f{ m_topLeftStart.x, m_topLeftStart.y + m_buttonSpacing * 2});
	m_testInputButton.setSize(m_buttonSize);
	m_testInputButton.setFillColor(sf::Color::Blue);
	sf::Vector2f inputTestOffset = { m_testInputButton.getPosition().x + 20.0f, m_testInputButton.getPosition().y };
	m_testInputText.setPosition(inputTestOffset);

	// MIDI Parse
	m_MIDIParseButton.setPosition(sf::Vector2f{ m_topLeftStart.x, m_topLeftStart.y + m_buttonSpacing * 3 });
	m_MIDIParseButton.setSize(m_buttonSize);
	m_MIDIParseButton.setFillColor(sf::Color::Blue);
	sf::Vector2f midiTextOffset = { m_MIDIParseButton.getPosition().x + 20.0f, m_MIDIParseButton.getPosition().y };
	m_MIDIParseText.setPosition(midiTextOffset);

	// Character Test
	m_visSelectButton.setPosition(sf::Vector2f{ m_topLeftStart.x, m_topLeftStart.y + m_buttonSpacing * 4 });
	m_visSelectButton.setSize(m_buttonSize);
	m_visSelectButton.setFillColor(sf::Color::Blue);
	sf::Vector2f characterTextOffset = { m_visSelectButton.getPosition().x + 20.0f, m_visSelectButton.getPosition().y };
	m_visSelectText.setPosition(characterTextOffset);

	// Options
	m_optionsButton.setPosition(sf::Vector2f{ m_topLeftStart.x + 500.0f, m_topLeftStart.y + m_buttonSpacing });
	m_optionsButton.setSize(m_buttonSize);
	m_optionsButton.setFillColor(sf::Color::Blue);
	sf::Vector2f optionsTextOffset = { m_optionsButton.getPosition().x + 20.0f, m_optionsButton.getPosition().y };
	m_optionsText.setPosition(optionsTextOffset);

	// Exit 
	m_exitButton.setPosition(sf::Vector2f{ m_topLeftStart.x + 500.0f, m_topLeftStart.y + m_buttonSpacing * 2 });
	m_exitButton.setSize(m_buttonSize);
	m_exitButton.setFillColor(sf::Color::Magenta);
	sf::Vector2f exitTextOffset = { m_exitButton.getPosition().x + 20.0f, m_exitButton.getPosition().y };
	m_exitText.setPosition(exitTextOffset);
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

void Game::setupGrid()
{
	// Reserve space for each cell
	m_grid.reserve(COLS * ROWS);

	for (int i = 0; i < ROWS; ++i)
	{
		for (int j = 0; j < COLS; ++j)
		{
			sf::RectangleShape cell(sf::Vector2f(CELL_WIDTH, CELL_HEIGHT));
			cell.setOutlineThickness(1.f);
			cell.setOutlineColor(sf::Color::Black);

			// Pick a random colour from the vectpr
			int index = std::rand() % colors.size();
			cell.setFillColor(colors[index]);

			cell.setPosition(sf::Vector2f{ j * CELL_WIDTH, i * CELL_HEIGHT });

			// Add to the end of the vector
			m_grid.push_back(cell);
		}
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
			bool b_result = midiInGetDevCaps(i, &deviceInfo, sizeof(MIDIINCAPS));

			if (b_result == MMSYSERR_NOERROR)
			{
				std::cerr << "[KEYBOARD " << i << "]" << std::endl;
				std::cerr << deviceInfo.szPname << std::endl;
				//std::cerr << deviceInfo.vDriverVersion << std::endl;
				//std::cerr << HIWORD(deviceInfo.vDriverVersion) << " || " << LOWORD(deviceInfo.vDriverVersion) << std::endl; 
				//std::cerr << deviceInfo.wMid << std::endl; // Manufacturer ID (useless)
				//std::cerr << deviceInfo.wPid << std::endl; // Product ID (useless)
				//std::cerr << deviceInfo.dwSupport << std::endl; // "Reserved; must be zero" (unsure but not needed)
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
		//MMRESULT m_resultMidiOpen = midiInOpen(&handleMidiIn, validMidiID, (DWORD_PTR)&MidiInProc, 0, CALLBACK_FUNCTION);  

		m_midiCallbackData = { &pianoVisualiser, &drumVisualiser };
		//MMRESULT m_resultMidiOpen = midiInOpen(&handleMidiIn, validMidiID, (DWORD_PTR)&MidiInProc, (DWORD_PTR)&pianoVisualiser, CALLBACK_FUNCTION);
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
			

			if ((msgType & messageTypeMask) == noteOn && msgVel > 0)
			{
				std::cout << "Note ON: " << noteName << " Velocity: " << msgVel << std::endl;

				if (pianoListener)
				{
					pianoListener->noteOn(noteName);
				}
			}

			if ((msgType & messageTypeMask) == noteOff || (msgType & messageTypeMask) == noteOn && msgVel == 0)
			{
				std::cout << "Note OFF:" << noteName << " Velocity: " << msgVel << std::endl;

				if (pianoListener)
				{
					pianoListener->noteOff(noteName);
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
	midiParser.parseFile(m_midiPath);
	//midiParser.parseFile("ASSETS\\AUDIO\\MUSIC\\Kick_and_Clap_2_track.mid");
	
	m_hud.loadMidiData( midiParser.getMidiTracks(),
						midiParser.getTimeSignature(),
						midiParser.getBPM(),
						midiParser.getMidiFileName(),
						midiParser.getNominator(),
						midiParser.getDenominator() );
}
