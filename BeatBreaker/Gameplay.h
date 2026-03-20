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

Statistics: (show this in the statistics tab on the left hand side of the screen)
- Hit percentage 
- Hits notes (45/50)
- Average notes per second?

- Missed notes
- Early notes
- Late notes
- Wrong Key pressed

Score: (right hand side)
- Current score
- Personal best score

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
	Gameplay(SoundManager& t_soundManager, std::shared_ptr<const sf::Font> font);

    void setup();
    void setupKeyboard();
    void setupUIFrames();

    void setupScoreText();
    void setupStatisticText();

    void update(float t_deltaTime);
    void updateScore();
    void render(sf::RenderWindow& t_window);

    void handleClick(sf::Vector2f t_mousePos);
    void handleRelease(sf::Vector2f t_mousePos);

    void noteOn(std::string& t_noteName);
    void noteOff(std::string& t_noteName);

    // Note Generation
    void loadTrack(MidiTrack& t_track, double t_BPM);
    void spawnNote(MidiNote& t_note);

    // Playback
    void startSong();

    bool getNoteOnColliderFlag();
    void setNoteOnColliderFlag(bool t_bool);
    bool getEasyInputFlag();
    void setEasyInputFlag(bool t_bool);

private:
    SoundManager* m_soundManager;
    std::shared_ptr<const sf::Font> m_font;
    Keyboard m_keyboard;

    const MidiTrack* m_currentTrack = nullptr;
    double m_playbackTime = 0.0;
    int m_spawnIndex = 0;
    std::vector<FallingNote> m_fallingNotes;
    // BPM
    float m_noteSpeed = 0.0f;
    float m_noteSpeedMultiplier = 3.0f; // might need this if it doesn't sync up with the screen resolution


    sf::Vector2f m_flatNoteSize{ 36.0f, 100.0f };
    sf::Vector2f m_sharpNoteSize{ 20.0f, 100.0f };

    sf::Color c_activeNoteColour = sf::Color::Blue;
    sf::Color c_lateNoteColour = sf::Color::Red;
    sf::Color c_earlyNoteColour = sf::Color::Yellow;
    sf::Color c_perfectNoteColour = sf::Color::Green;

    

    // UI Background Frames
    sf::RectangleShape m_scoreFrame;
    sf::RectangleShape m_statisticFrame;
    sf::Vector2f m_frameSize{ 300.0f, 525.0f };
    sf::Vector2f m_frameTextSize{ 200.0f, 50.0f };
    sf::Color c_frameColour = sf::Color(100, 100, 100, 100);
    // Frame Texts
    sf::Text m_statisticFrameText;
    sf::Text m_scoreFrameText;

    // Score Text
    int m_score = 0;
    sf::Text m_currentScoreText;
    sf::Text m_currentScoreValueText;
    sf::Text m_pbScoreText;
    sf::Text m_pbScoreValueText;

    // Statistic Text
    sf::Text m_missedNotesText;
    sf::Text m_missedNotesValueText;
    sf::Text m_earlyNotesText;
    sf::Text m_earlyNotesValueText;
    sf::Text m_lateNotesText;
    sf::Text m_lateNotesValueText;
    sf::Text m_wrongNotesText;
    sf::Text m_wrongNotesValueText;

    // Bools
    bool b_isPlaying = false;

    bool b_playNotesNoInput = true;
    bool b_easyInputMode = true;

    bool b_isPreviewMode = false;
};

