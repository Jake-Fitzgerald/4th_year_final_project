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
                                    Count how many notes in the vector and use that for the hit percentage and hit notes counter. [TODO]
                                    Count how long the song is by looking at the timestamp for the last note in the vector and adding 5 seconds to it.

    

- Missed notes
- Early notes
- Late notes
- Wrong Key pressed

Score: (right hand side)
- Current score
- Personal best score

Combo
- 5 notes in sequence hit with perfect timing?

Practice Mode:
- Practice Trigger is placed at the bottom of every note and when it hits the top of the keyboard it will trigger a call to pause the playback,
then it will only resume when the user is after pressing the correct key on the keyboard.


*/

struct FallingNote
{
    sf::RectangleShape shape;
    sf::RectangleShape earlyTrigger;
    sf::RectangleShape lateTrigger;
    sf::RectangleShape perfectTrigger;

    std::string noteName;   
    float speed = 200.0f;
    bool b_isActive = true;
};

enum class HitType
{
    Early,
    Perfect,
    Late,
    Miss,
    Wrong
};

class Gameplay
{
public:
	Gameplay(SoundManager& t_soundManager, std::shared_ptr<const sf::Font> font);

    void setup();
    void setupKeyboard();
    void setupUIFrames();

    void setupPlaybackText();
    void setupScoreText();
    void setupStatisticText();
    void setupStatistics();

    void update(float t_deltaTime);
    void updateScore();
    void updateStatistics();

    void resetSession();
    void resetScore();
    void resetStatistics();
    int getScore();
    SessionStats getSessionStats();

    void render(sf::RenderWindow& t_window);

    void handleClick(sf::Vector2f t_mousePos);
    void handleRelease(sf::Vector2f t_mousePos);

    void noteOn(std::string& t_noteName, int t_pitch, int t_velocity);
    void noteOff(std::string& t_noteName, int t_pitch, int t_velocity);

    // Note Generation
    void loadTrack(MidiTrack& t_track, double t_BPM);
    void loadGhostTrack(MidiTrack& t_track, double t_BPM);
    void spawnNote(MidiNote& t_note);
    void spawnGhostNote(MidiNote& t_note);


    // Playback
    void startSong();
    void togglePause();
    bool getPausedFlag();
    void setPracticeModeFlag(bool t_bool);
    bool getPracticeModeFlag();
    void setRecordingFlag(bool t_bool);
    bool getRecordingFlag();
    void setPreviewModeFlag(bool t_bool);
    bool getPreviewModeFlag();
    void setGhostModeFlag(bool t_bool);
    bool getGhostModeFlag();

    bool getNoteOnColliderFlag();
    void setNoteOnColliderFlag(bool t_bool);
    bool getEasyInputFlag();
    void setEasyInputFlag(bool t_bool);
    bool getTriggerDisplayFlag();
    void setTriggerDisplayFlag(bool t_bool);
    bool getSongFinishedFlag();

    std::vector<MidiNote> getRecordedNotes(); 
    void setSongName(std::string t_name);
    std::string getSongName();

private:
    SoundManager* m_soundManager;
    std::shared_ptr<const sf::Font> m_font;
    Keyboard m_keyboard;

    const MidiTrack* m_currentTrack = nullptr;
    double m_playbackTime = 0.0;
    double m_songEndTime = 0.0;
    double m_songEndWaitTime = 0.0;

    std::vector<FallingNote> m_fallingNotes;

    // Recorded Midi
    std::vector<MidiNote> m_recordedNotes;
    std::string m_songName = "";
    bool b_isRecording = true;

    // Ghost Midi
    std::vector<FallingNote> m_ghostNotes;
    bool b_isGhostMode = false;

    // Playback Text
    sf::Vector2f m_playbackTextPos{ paddingX + 25.0f, paddingY + 400.0f };
    sf::Text m_songTimeText;
    sf::Text m_songEndTimeText;

    // BPM
    float m_noteSpeed = 0.0f;                                                                                                                     

    sf::Vector2f m_flatNoteSize{ 36.0f, 100.0f };
    sf::Vector2f m_sharpNoteSize{ 20.0f, 100.0f };

    // Note Colours
    sf::Color c_activeNoteColour = sf::Color(20,20,240, 220);
    sf::Color c_lateNoteColour = sf::Color(240, 20, 20, 220);
    sf::Color c_earlyNoteColour = sf::Color(240, 250, 20, 220);
    sf::Color c_perfectNoteColour = sf::Color(20, 240, 20, 220);
    sf::Color c_ghostNoteColour = sf::Color(240, 240, 240, 150);
    // Trigger Colours
    sf::Color c_earlyTriggerColour = sf::Color(255, 255, 50, 150);
    sf::Color c_perfectTriggerColour = sf::Color(50, 255, 50, 150);
    sf::Color c_lateTriggerColour = sf::Color(255, 50, 50, 150);

    // UI Background Frames
    sf::RectangleShape m_scoreFrame;
    sf::RectangleShape m_statisticFrame;
    sf::Vector2f m_frameSize{ 300.0f, 525.0f };
    sf::Vector2f m_frameTextSize{ 200.0f, 50.0f };
    sf::Color c_frameColour = sf::Color(100, 100, 100, 100);
    // Frame Texts
    sf::Text m_statisticFrameText;
    sf::Text m_scoreFrameText;

    // Score
    int m_score = 0;
    int m_scoreEarly = 75;
    int m_scorePerfect = 100;
    int m_scoreLate = 50;
    int m_scoreMiss = 5;
    int m_scoreWrong = 10;
    // Score Text
    sf::Text m_currentScoreText;
    sf::Text m_currentScoreValueText;
    sf::Text m_pbScoreText;
    sf::Text m_pbScoreValueText;

    // Statistics
    int m_earlyNotes = 0;
    int m_perfectNotes = 0;
    int m_lateNotes = 0;
    int m_missedNotes = 0;
    int m_wrongNotes = 0;
    std::vector<std::string> m_expectedNotes;

    int m_noteCountTotal = 0;
    int m_currentNotesHit = 0;
    float m_anps = 0.0f;

    // Statistic Text
    sf::Text m_missedNotesText;
    sf::Text m_missedNotesValueText;
    sf::Text m_earlyNotesText;
    sf::Text m_earlyNotesValueText;
    sf::Text m_perfectNotesText;                                                                                                     
    sf::Text m_perfectNotesValueText;                                                                                                
    sf::Text m_lateNotesText;
    sf::Text m_lateNotesValueText;
    sf::Text m_wrongNotesText;
    sf::Text m_wrongNotesValueText;

    sf::Text m_hitpercentageText;
    sf::Text m_hitpercentageValueText;
    sf::Text m_hitNotesText;
    sf::Text m_hitNotesValueText;
    sf::Text m_anpsText;
    sf::Text m_anpsValueText;

    sf::Text m_previewModeText;
    sf::Text m_ghostModeText;

    // Bools
    bool b_isPlaying = false;
    bool b_isPaused = false;
    bool b_isSongFinished = false;
    
    bool b_playNotesNoInput = true;
    bool b_easyInputMode = false;

    bool b_isPreviewMode = false;

    bool b_isPracticeMode = false;
    bool b_isPracticePaused = false;
    std::vector<std::string> m_practiceWaitForNotes;
    bool b_isWaitingForThisNote = false;

    bool b_displayTriggers = false;

};

