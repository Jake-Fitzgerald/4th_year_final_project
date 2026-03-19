#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "SoundManager.h"
#include "CollisionManager.h"

/*
    25-key keyboard: C3 to C5 (2 full octaves + final C)
    14 white keys, 10 black keys = 24 keys + 1 final C5 white = 25 total

    Key pattern per octave: W B W B W W B W B W B W
    (C C# D D# E F F# G G# A A# B)
*/


struct Key
{
    sf::RectangleShape shape;
    std::string noteName;
    bool b_isSharpKey;
    bool b_isPressed;
    sf::Color originalColour;
};

class Keyboard
{
public:
    Keyboard(SoundManager& t_soundManager);

    void setupKeys();
    void setupSounds();

    void render(sf::RenderWindow& t_window);

    void handleClick(sf::Vector2f t_mousePos);
    void handleRelease(sf::Vector2f t_mousePos);

    void noteOn(const std::string& t_noteName);
    void noteOff(const std::string& t_noteName);
    void resetAllKeys();

    void setupWhiteKey(int t_whiteIndex, std::string t_noteLetter, int t_octave);
    void setupBlackKey(int t_whiteIndex, std::string t_noteLetter, int t_octave);

    void keyTurnOn(int t_index);
    void keyTurnOff(int t_index);

    bool checkIfKeyClicked(sf::Vector2f t_mousePos, Key& t_key);

    bool checkInputCollision();

private:
    SoundManager* m_soundManager;

    std::vector<Key> m_keys;

    sf::RectangleShape m_keyboardBase;

    float m_posX = paddingX + 300.0f;
    float m_posY = paddingY + 400.0f;

    // Key sizes
    sf::Vector2f m_whiteKeySize{ 38.0f, 120.0f };
    sf::Vector2f m_blackKeySize{ 22.0f, 70.0f };
    float m_whiteSpacing = 2.0f;

    sf::Color c_pressedColour = sf::Color::Red;

    bool b_testNoteActive = false;
};

