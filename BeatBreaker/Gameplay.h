#pragma once
#include <SFML//Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Globals.h"
#include <iostream>
#include "Keyboard.h"
#include "SoundManager.h"
#include "MIDIParse.h"

/*
Similar to synthesia (program that teaches how to play piano songs) https://www.youtube.com/watch?v=urKSKHXsU3I
It will be a showcase of the Midi parsing and the Live Midi input combined and interacting with one another.
You gain points based on on early/late a note was hit. Also if you actually held the note for that long.
(Guitar Hero reference for scoring)

*/

struct FallingNote
{
    sf::RectangleShape shape;
    sf::RectangleShape earlyTrigger;
    sf::RectangleShape lateTrigger;

    std::string noteName;   
    float speed = 200.0f;
    bool b_isActive = true;
};

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

    // Note Generation
    void loadTrack(MidiTrack& t_track, double t_BPM);
    void spawnNote(MidiNote& t_note);

private:
    SoundManager* m_soundManager;
    Keyboard m_keyboard;

    const MidiTrack* m_currentTrack = nullptr;
    double m_playbackTime = 0.0;
    int m_spawnIndex = 0;
    std::vector<FallingNote> m_fallingNotes;
    // BPM
    float m_noteSpeed = 0.0f;
    float m_noteSpeedMultiplier = 3.0f; // might need this if it doesn't sync up with the screen resolution


    sf::Vector2f m_flatNoteSize{ 36.0f, 10.0f };
    sf::Vector2f m_sharpNoteSize{ 20.0f, 10.0f };

    sf::Color c_activeNoteColour = sf::Color::Blue;
    sf::Color c_lateNoteColour = sf::Color::Red;
    sf::Color c_earlyNoteColour = sf::Color::Yellow;
    sf::Color c_perfectNoteColour = sf::Color::Green;
};

