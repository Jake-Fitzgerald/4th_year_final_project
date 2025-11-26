#include "Game.h"
#include <iostream>


Game::Game() :
	m_window{ sf::VideoMode{ sf::Vector2u{SCREEN_WIDTH, SCREEN_HEIGHT}, 32U }, "Beat Breaker" },
	m_DELETEexitGame{false}, m_hud(m_jerseyFont), m_options(m_jerseyFont)
{
	setupTexts(); // load font 
	setupSprites(); // load texture
	setupAudio(); // load sounds
	setupMainMenu();

	setupGrid();

	// MIDI
	setupMidiParser();
	
	// Player
	setupPlayer();
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
}

void Game::processKeysPressed(const std::optional<sf::Event> t_event)
{
	const sf::Event::KeyPressed* newKeyPress = t_event->getIf<sf::Event::KeyPressed>();

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	//{
	//	m_player.moveLeft();
	//}
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	//{
	//	m_player.moveRight();
	//}
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
			m_currentGameState = GameStates::Gameplay;
			std::cout << "Start button clicked!" << std::endl;
		}

		// Character
		if (checkIfAreaClicked(mouseWorldPos, m_characterButton.getPosition(), m_characterButton.getSize()))
		{
			m_currentGameState = GameStates::Gameplay;
			std::cout << "Start button clicked!" << std::endl;
		}
		// Options
		if (checkIfAreaClicked(mouseWorldPos, m_optionsButton.getPosition(), m_optionsButton.getSize()))
		{
			m_currentGameState = GameStates::OptionsScene;
			std::cout << "Options button clicked!" << std::endl;
		}
		// Exit
		if (checkIfAreaClicked(mouseWorldPos, m_exitButton.getPosition(), m_exitButton.getSize()))
		{
			m_DELETEexitGame = true;
		}
	}
	else if (m_currentGameState == OptionsScene)
	{
		if (m_options.handleMouseClick(mouseWorldPos, m_hud))
		{
			// If handleMouseClick returns true, go back to main menu
			m_currentGameState = MainMenu;
		}
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		m_player.moveLeft(dtSeconds);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		m_player.moveRight(dtSeconds);
	}
}


void Game::update(sf::Time t_deltaTime)
{
	float dtConverted = t_deltaTime.asSeconds();

	checkKeyboardState();
	if (m_DELETEexitGame)
	{
		m_window.close();
	}

	if (m_currentGameState == GameStates::Character)
	{
		processKeyboard(dtConverted);
		m_player.updatePlayer(dtConverted);
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
		m_window.draw(m_randGenButton);
		m_window.draw(m_randGenText);
		// Input Test
		m_window.draw(m_testInputButton);
		m_window.draw(m_testInputText);
		// MIDI Parse
		m_window.draw(m_MIDIParseButton);
		m_window.draw(m_MIDIParseText);
		// Character
		m_window.draw(m_characterButton);
		m_window.draw(m_characterText);
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
	// Character
	if (m_currentGameState == GameStates::Character)
	{
		m_player.renderPlayer(m_window);
	}

	// UI
	m_hud.drawHUD(m_window);
	
	
	m_window.display();
}


void Game::setupTexts()
{
	if (!m_jerseyFont.openFromFile("ASSETS\\FONTS\\Jersey20-Regular.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_beatBreakerText.setFont(m_jerseyFont);
	m_beatBreakerText.setString("Beat Breaker");
	m_beatBreakerText.setPosition(sf::Vector2f{ SCREEN_CENTRE.x - 200.0f, SCREEN_CENTRE.y - 350.0f});
	m_beatBreakerText.setCharacterSize(80U);
	m_beatBreakerText.setOutlineColor(sf::Color::Black);
	m_beatBreakerText.setFillColor(sf::Color::Red);
	m_beatBreakerText.setOutlineThickness(2.0f);


	// Start Text
	m_startText.setFont(m_jerseyFont);
	m_startText.setString("Start");
	m_startText.setPosition(m_startButton.getPosition());
	m_startText.setCharacterSize(40U);
	m_startText.setFillColor(sf::Color::Black);
	// Rand Gen Text
	m_randGenText.setFont(m_jerseyFont);
	m_randGenText.setString("Random Gen");
	m_randGenText.setPosition(m_randGenButton.getPosition());
	m_randGenText.setCharacterSize(40U);
	m_randGenText.setFillColor(sf::Color::Black);
	// Input Test Text
	m_testInputText.setFont(m_jerseyFont);
	m_testInputText.setString("Input Test");
	m_testInputText.setPosition(m_testInputButton.getPosition());
	m_testInputText.setCharacterSize(40U);
	m_testInputText.setFillColor(sf::Color::Black);
	// MIDI Parse Text
	m_MIDIParseText.setFont(m_jerseyFont);
	m_MIDIParseText.setString("MIDI Parse");
	m_MIDIParseText.setPosition(m_MIDIParseButton.getPosition());
	m_MIDIParseText.setCharacterSize(40U);
	m_MIDIParseText.setFillColor(sf::Color::Black);
	// Character Text
	m_characterText.setFont(m_jerseyFont);
	m_characterText.setString("Character");
	m_characterText.setPosition(m_characterButton.getPosition());
	m_characterText.setCharacterSize(40U);
	m_characterText.setFillColor(sf::Color::Black);
	// Options Menu Text
	m_optionsText.setFont(m_jerseyFont);
	m_optionsText.setString("Options");
	m_optionsText.setPosition(m_optionsButton.getPosition());
	m_optionsText.setCharacterSize(40U);
	m_optionsText.setFillColor(sf::Color::Black);
	// Exit Menu Text
	m_exitText.setFont(m_jerseyFont);
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
}

void Game::setupMainMenu()
{
	// Start
	m_startButton.setPosition(sf::Vector2f{ SCREEN_CENTRE.x - 400.0f, SCREEN_CENTRE.y - 200.0f });
	m_startButton.setSize(sf::Vector2f(250, 50));
	m_startButton.setFillColor(sf::Color::Blue);
	sf::Vector2f startTextOffset = { m_startButton.getPosition().x + m_startButton.getSize().x / 4.0f, m_startButton.getPosition().y };
	m_startText.setPosition(startTextOffset);

	// Rand Gen
	m_randGenButton.setPosition(sf::Vector2f{ SCREEN_CENTRE.x - 400.0f , SCREEN_CENTRE.y - 100.0f});
	m_randGenButton.setSize(sf::Vector2f(250, 50));
	m_randGenButton.setFillColor(sf::Color::Blue);
	sf::Vector2f randGenTextOffset = { m_randGenButton.getPosition().x + 20.0f, m_randGenButton.getPosition().y };
	m_randGenText.setPosition(randGenTextOffset);

	// Input Test
	m_testInputButton.setPosition(sf::Vector2f{ SCREEN_CENTRE.x - 400.0f, SCREEN_CENTRE.y });
	m_testInputButton.setSize(sf::Vector2f(250, 50));
	m_testInputButton.setFillColor(sf::Color::Blue);
	sf::Vector2f inputTestOffset = { m_testInputButton.getPosition().x + 20.0f, m_testInputButton.getPosition().y };
	m_testInputText.setPosition(inputTestOffset);

	// MIDI Parse
	m_MIDIParseButton.setPosition(sf::Vector2f{ SCREEN_CENTRE.x - 400.0f, SCREEN_CENTRE.y + 100.0f });
	m_MIDIParseButton.setSize(sf::Vector2f(250, 50));
	m_MIDIParseButton.setFillColor(sf::Color::Blue);
	sf::Vector2f midiTextOffset = { m_MIDIParseButton.getPosition().x + 20.0f, m_MIDIParseButton.getPosition().y };
	m_MIDIParseText.setPosition(midiTextOffset);

	// Character Test
	m_characterButton.setPosition(sf::Vector2f{ SCREEN_CENTRE.x - 400.0f, SCREEN_CENTRE.y + 200.0f });
	m_characterButton.setSize(sf::Vector2f(250, 50));
	m_characterButton.setFillColor(sf::Color::Blue);
	sf::Vector2f characterTextOffset = { m_characterButton.getPosition().x + 20.0f, m_characterButton.getPosition().y };
	m_characterText.setPosition(characterTextOffset);

	// Options
	m_optionsButton.setPosition(sf::Vector2f{ SCREEN_CENTRE.x - 400.0f, SCREEN_CENTRE.y + 300.0f });
	m_optionsButton.setSize(sf::Vector2f(250, 50));
	m_optionsButton.setFillColor(sf::Color::Blue);
	sf::Vector2f optionsTextOffset = { m_optionsButton.getPosition().x + 20.0f, m_optionsButton.getPosition().y };
	m_optionsText.setPosition(optionsTextOffset);

	// Exit 
	m_exitButton.setPosition(sf::Vector2f{ SCREEN_CENTRE.x, SCREEN_CENTRE.y + 300.0f });
	m_exitButton.setSize(sf::Vector2f(250, 50));
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

void Game::setupPlayer()
{
	m_player.setupPlayer();
	m_player.setSpawnPos(sf::Vector2f{ 100.0f, 100.0f });
}

void Game::setupMidiParser()
{
	midiParser.parseFile("ASSETS\\AUDIO\\MUSIC\\Test_MIDI.mid");
}
