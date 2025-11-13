#include "Game.h"
#include <iostream>


Game::Game() :
	m_window{ sf::VideoMode{ sf::Vector2u{1280U, 720U}, 32U }, "Beat Breaker" },
	m_DELETEexitGame{false}
{
	setupTexts(); // load font 
	setupSprites(); // load texture
	setupAudio(); // load sounds
	setupMainMenu();

	
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

void Game::processMouseRelease(const std::optional<sf::Event> t_event)
{
	const sf::Event::MouseButtonReleased* newMouseReleased = t_event->getIf<sf::Event::MouseButtonReleased>();
	const sf::Vector2f mouseWorldPos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));

	if (m_currentGameState == MainMenu)
	{
		if (checkIfAreaClicked(mouseWorldPos, m_startButton.getPosition(), m_startButton.getSize()))
		{
			m_currentGameState = GameStates::Gameplay;
			std::cout << "Start button clicked!" << std::endl;
		}

		if (mouseWorldPos.x >= m_startButton.getPosition().x &&
			mouseWorldPos.x <= m_startButton.getPosition().x + m_startButton.getSize().x &&
			mouseWorldPos.y >= m_startButton.getPosition().y &&
			mouseWorldPos.y <= m_startButton.getPosition().y + m_startButton.getSize().y)
			{
				m_currentGameState = GameStates::Gameplay;
				std::cout << "Start button clicked!" << std::endl;
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


void Game::update(sf::Time t_deltaTime)
{
	checkKeyboardState();
	if (m_DELETEexitGame)
	{
		m_window.close();
	}
}


void Game::render()
{
	m_window.clear(sf::Color::Black);

	//m_window.draw(m_DELETElogoSprite);
	m_window.draw(m_DELETEwelcomeMessage);

	// Main Menu
	//mainMenu.render(m_window);
	if (m_currentGameState == GameStates::MainMenu)
	{
		// Start
		m_window.draw(m_startButton);
		m_window.draw(m_startText);
		// Rand Gen
		m_window.draw(m_randGenButton);
		m_window.draw(m_randGenText);
	}
	
	m_window.display();
}


void Game::setupTexts()
{
	if (!m_jerseyFont.openFromFile("ASSETS\\FONTS\\Jersey20-Regular.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_DELETEwelcomeMessage.setFont(m_jerseyFont);
	m_DELETEwelcomeMessage.setString("Beat Breaker");
	m_DELETEwelcomeMessage.setPosition(sf::Vector2f{ 200.0f, 50.0f });
	m_DELETEwelcomeMessage.setCharacterSize(80U);
	m_DELETEwelcomeMessage.setOutlineColor(sf::Color::Black);
	m_DELETEwelcomeMessage.setFillColor(sf::Color::Red);
	m_DELETEwelcomeMessage.setOutlineThickness(2.0f);


	// Start Text
	m_startText.setFont(m_jerseyFont);
	m_startText.setString("Start");
	m_startText.setPosition(m_startButton.getPosition());
	m_startText.setCharacterSize(40U);
	m_startText.setFillColor(sf::Color::Black);

	m_randGenText.setFont(m_jerseyFont);
	m_randGenText.setString("Random Gen");
	m_randGenText.setPosition(m_randGenButton.getPosition());
	m_randGenText.setCharacterSize(40U);
	m_randGenText.setFillColor(sf::Color::Black);

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
	m_startButton.setPosition(m_topLeftStart);
	m_startButton.setSize(sf::Vector2f(200, 50));
	m_startButton.setFillColor(sf::Color::Blue);
	sf::Vector2f startTextOffset = { m_startButton.getPosition().x + m_startButton.getSize().x / 4.0f, m_startButton.getPosition().y };
	m_startText.setPosition(startTextOffset);

	// Rand Gen
	m_randGenButton.setPosition(sf::Vector2f{ m_topLeftStart.x , m_topLeftStart.y + 100.0f});
	m_randGenButton.setSize(sf::Vector2f(200, 50));
	m_randGenButton.setFillColor(sf::Color::Blue);
	sf::Vector2f randGenTextOffset = { m_randGenButton.getPosition().x + 20.0f, m_randGenButton.getPosition().y };
	m_randGenText.setPosition(randGenTextOffset);

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
