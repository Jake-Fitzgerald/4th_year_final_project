#include "PianoVisualiser.h"

PianoVisualiser::PianoVisualiser(SoundManager& t_soundManager) : m_soundManager(&t_soundManager)
{
    
}

void PianoVisualiser::setupPianoShapes()
{
    int keyIndex = 0;

    for (int octave = 2; octave <= 5; octave++)
    {
        setupWhiteKey(keyIndex++, "C", octave);   // C
        setupBlackKey(keyIndex - 1, "C#", octave); // C#
        setupWhiteKey(keyIndex++, "D", octave);   // D
        setupBlackKey(keyIndex - 1, "D#", octave); // D#
        setupWhiteKey(keyIndex++, "E", octave);   // E
        setupWhiteKey(keyIndex++, "F", octave);   // F
        setupBlackKey(keyIndex - 1, "F#", octave); // F#
        setupWhiteKey(keyIndex++, "G", octave);   // G
        setupBlackKey(keyIndex - 1, "G#", octave); // G#
        setupWhiteKey(keyIndex++, "A", octave);   // A
        setupBlackKey(keyIndex - 1, "A#", octave); // A#
        setupWhiteKey(keyIndex++, "B", octave);   // B
    }

    // Final C6
    setupWhiteKey(keyIndex++, "C", 6);

    // UI
    m_keyboardBase.setFillColor(sf::Color::Black);

    float firstKeyPosX = m_keys.at(0).shape.getPosition().x;
    float firstKeyPosY = m_keys.at(0).shape.getPosition().y;
    int keyVecSize = static_cast<int>(m_keys.size() - 1);
    std::cerr << "keyvec size: " << keyVecSize << std::endl;
    float lastKeyPosX = m_keys.at(keyVecSize).shape.getPosition().x;
    float lastKeyPosY = m_keys.at(keyVecSize).shape.getPosition().y;


    m_keyboardBase.setPosition(sf::Vector2f{ firstKeyPosX, firstKeyPosY });

    sf::Vector2f firstKey = sf::Vector2f{ firstKeyPosX, firstKeyPosY };
    sf::Vector2f lastKey = sf::Vector2f{ lastKeyPosX, lastKeyPosY };

    m_keyboardBase.setSize(sf::Vector2f{ firstKey.x, lastKey.y });
}

void PianoVisualiser::setupWhiteKey(int t_index, std::string t_noteLetter, int t_octave)
{
    //sf::RectangleShape keyShape;
    //keyShape.setSize(whiteKeySize);
    //keyShape.setFillColor(sf::Color::White);
    //keyShape.setOutlineThickness(1.0f);
    //keyShape.setOutlineColor(sf::Color::Black);
    //keyShape.setPosition(sf::Vector2f{pianoPosX + t_index * (whiteKeySize.x + whiteSpacing), pianoPosY });

    PianoKey key; 

    key.shape.setSize(whiteKeySize);
    key.shape.setFillColor(sf::Color::White);
    key.shape.setOutlineThickness(1.0f);
    key.shape.setOutlineColor(sf::Color::Black);
    key.shape.setPosition(sf::Vector2f{ pianoPosX + t_index * (whiteKeySize.x + whiteSpacing), pianoPosY });

    // key.noteName = ;
    key.b_isSharpKey = false;
    key.b_isPressed = false;
    key.originalColor = sf::Color::White;

    m_keys.push_back(key);
}

void PianoVisualiser::setupBlackKey(int t_whiteKeyIndex, std::string t_noteLetter, int t_octave)
{
    //sf::RectangleShape keyShape;
    //keyShape.setSize(blackKeySize);
    //keyShape.setFillColor(sf::Color::Black);
    //keyShape.setOutlineThickness(1.0f);
    //keyShape.setOutlineColor(sf::Color::Black);
    //float blackKeyOffsetX = (whiteKeySize.x + whiteSpacing) * t_whiteKeyIndex + whiteKeySize.x * 0.7f;
    //keyShape.setPosition(sf::Vector2f{pianoPosX + blackKeyOffsetX, pianoPosY});

    PianoKey key;

    key.shape.setSize(blackKeySize);
    key.shape.setFillColor(sf::Color::Black);
    key.shape.setOutlineThickness(1.0f);
    key.shape.setOutlineColor(sf::Color(10.0, 10.0, 10.0, 255));
    float blackKeyOffsetX = (whiteKeySize.x + whiteSpacing) * t_whiteKeyIndex + whiteKeySize.x * 0.7f;
    key.shape.setPosition(sf::Vector2f{ pianoPosX + blackKeyOffsetX, pianoPosY });

    // key.noteName = ;
    key.b_isSharpKey = true;
    key.b_isPressed = false;
    key.originalColor = sf::Color::Black;

    m_keys.push_back(key);

}

void PianoVisualiser::setupPianoSounds()
{
    std::string noteNames[] = { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };
    int keysLoaded = 0;


    // The piano sound pack is sorted as A to G which is awkward when the piano is always from C to B.
    // We have to load the last three notes in an octave (A, A#, B)
    
    // Load full octaves 2 through 5
    for (int octave = 2; octave <= 5; octave++)
    {
        for (int note = 0; note < 12; note++)
        {
            std::string soundName = noteNames[note] + std::to_string(octave);
            std::string filename = "ASSETS\\AUDIO\\Piano\\" + soundName + ".WAV";
            std::cerr << "WAV loading: " << filename << std::endl;
            m_soundManager->loadBuffer(soundName, filename, SoundType::MUSIC);
        }
    }

    // Load the final C6
    m_soundManager->loadBuffer("C6", "ASSETS\\AUDIO\\Piano\\C6.WAV", SoundType::MUSIC);
}

void PianoVisualiser::keysTurnOn(int t_KeyPos)
{
    // Get the midi data's key position and change the colour to red
    if (t_KeyPos >= 0 && t_KeyPos < m_keys.size())
    {
        m_keys[t_KeyPos].b_isPressed = true;
        m_keys[t_KeyPos].shape.setFillColor(sf::Color::Red);
    }
}

void PianoVisualiser::keysTurnOff(int t_KeyPos)
{
    // Reset the key back to it's original colour (white or black)
    if (t_KeyPos >= 0 && t_KeyPos < m_keys.size())
    {
        m_keys[t_KeyPos].b_isPressed = false;
        m_keys[t_KeyPos].shape.setFillColor(m_keys[t_KeyPos].originalColor);
    }
}

void PianoVisualiser::renderKeys(sf::RenderWindow& t_window)
{
    // UI
    t_window.draw(m_keyboardBase);

    // White keys first
    for (int i = 0; i < m_keys.size(); i++)
    {
        //if (keyShapes[i].getFillColor() == sf::Color::White)
        //{
        //    t_window.draw(keyShapes[i]);
        //}
        if (m_keys[i].b_isSharpKey == false)
        {
            t_window.draw(m_keys[i].shape);
        }
    }

    // Black keys on top of the white ones
    for (int i = 0; i < m_keys.size(); i++)
    {
        //if (keyShapes[i].getFillColor() == sf::Color::Black)
        //{
        //    t_window.draw(keyShapes[i]);
        //}
        if (m_keys[i].b_isSharpKey == true)
        {
            t_window.draw(m_keys[i].shape);
        }
    }
}

void PianoVisualiser::handleClick(sf::Vector2f t_mousePos)
{

    // Black keys (they are ontop so check first)
    for (int i = 0; i < m_keys.size(); i++)
    {
        if (m_keys[i].b_isSharpKey && checkIfKeyClicked(t_mousePos, m_keys[i]))
        {
            // Turn on the key visually
            keysTurnOn(i);

            // Play the sound
            std::string soundName = m_keys[i].noteName;
            m_soundManager->play(soundName);

            std::cerr << "Clicked black key: " << soundName << std::endl;
            // Don't check white keys if we clicked a black key
            return;
        }
    }

    // White keys
    for (int i = 0; i < m_keys.size(); i++)
    {
        if (!m_keys[i].b_isSharpKey && checkIfKeyClicked(t_mousePos, m_keys[i]))
        {
            // Turn on the key visually
            keysTurnOn(i);

            // Play the sound
            std::string soundName = m_keys[i].noteName;
            //m_soundManager->play(soundName);

            std::cerr << "Clicked white key: " << soundName << std::endl;
            return;
        }

    }

}

bool PianoVisualiser::checkIfKeyClicked(sf::Vector2f t_mousePos, const PianoKey& t_key)
{
    sf::Vector2f topLeft = t_key.shape.getPosition();
    sf::Vector2f size = t_key.shape.getSize();

    if (t_mousePos.x >= topLeft.x &&
        t_mousePos.x <= topLeft.x + size.x &&
        t_mousePos.y >= topLeft.y &&
        t_mousePos.y <= topLeft.y + size.y)
    {
        return true;
    }
    return false;
}

