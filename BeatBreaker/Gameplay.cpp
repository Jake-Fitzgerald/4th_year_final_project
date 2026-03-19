#include "Gameplay.h"

Gameplay::Gameplay(SoundManager& t_soundManager) : m_soundManager(&t_soundManager), m_keyboard(t_soundManager)
{

}

void Gameplay::setup()
{
	setupKeyboard();
}

void Gameplay::setupKeyboard()
{
	m_keyboard.setupKeys();
	m_keyboard.setupSounds();
}

void Gameplay::update(float t_deltaTime)
{

}

void Gameplay::render(sf::RenderWindow& t_window)
{
	m_keyboard.render(t_window);
}

void Gameplay::handleClick(sf::Vector2f t_mousePos)
{
	m_keyboard.handleClick(t_mousePos);
}

void Gameplay::handleRelease(sf::Vector2f t_mousePos)
{
	m_keyboard.handleRelease(t_mousePos);
}

void Gameplay::noteOn(std::string& t_noteName)
{
	m_keyboard.noteOn(t_noteName);
}

void Gameplay::noteOff(std::string& t_noteName)
{
	m_keyboard.noteOff(t_noteName);
}
