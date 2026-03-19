#pragma once
#include <SFML//Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Globals.h"
#include <iostream>
#include "Keyboard.h"
#include "SoundManager.h"


/*
Similar to synthesia (program that teaches how to play piano songs) https://www.youtube.com/watch?v=urKSKHXsU3I
It will be a showcase of the Midi parsing and the Live Midi input combined and interacting with one another.
You gain points based on on early/late a note was hit. Also if you actually held the note for that long.
(Guitar Hero reference for scoring)

*/

class Gameplay
{
public:
	Gameplay(SoundManager& t_soundManager);

    void setup();
    void setupKeyboard();

    void update(float t_deltaTime);
    void render(sf::RenderWindow& t_window);

    void handleClick(sf::Vector2f t_mousePos);
    void handleRelease(sf::Vector2f t_mousePos);

    void noteOn(std::string& t_noteName);
    void noteOff(std::string& t_noteName);

private:
    SoundManager* m_soundManager;
    Keyboard m_keyboard;

    
};

