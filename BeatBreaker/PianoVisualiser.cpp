#include "PianoVisualiser.h"

PianoVisualiser::PianoVisualiser(SoundManager& t_soundManager)
{
}

void PianoVisualiser::setupPianoShapes()
{
    int keyIndex = 0;

    for (int i = 0; i < octavesAmount; i++)
    {
        setupWhiteKey(keyIndex++); // C
        setupBlackKey(keyIndex - 1); // C#
        setupWhiteKey(keyIndex++); // D
        setupBlackKey(keyIndex - 1); // D#
        setupWhiteKey(keyIndex++); // E
        setupWhiteKey(keyIndex++); // F
        setupBlackKey(keyIndex - 1); // F#
        setupWhiteKey(keyIndex++); // G
        setupBlackKey(keyIndex - 1); // G#
        setupWhiteKey(keyIndex++); // A
        setupBlackKey(keyIndex - 1); // A#
        setupWhiteKey(keyIndex++); // B
    }

    // UI
    m_keyboardBase.setFillColor(sf::Color::Black);

    float firstKeyPosX = keyShapes.at(0).getPosition().x;
    float firstKeyPosY = keyShapes.at(0).getPosition().y;
    int keyVecSize = static_cast<int>(keyShapes.size() - 1);
    std::cerr << "keyvec size: " << keyVecSize << std::endl;
    float lastKeyPosX = keyShapes.at(keyVecSize).getPosition().x;
    float lastKeyPosY = keyShapes.at(keyVecSize).getPosition().y;


    m_keyboardBase.setPosition(sf::Vector2f{ firstKeyPosX, firstKeyPosY });

    sf::Vector2f firstKey = sf::Vector2f{ firstKeyPosX, firstKeyPosY };
    sf::Vector2f lastKey = sf::Vector2f{ lastKeyPosX, lastKeyPosY };

    m_keyboardBase.setSize(sf::Vector2f{ firstKey.x, lastKey.y });
}

void PianoVisualiser::setupWhiteKey(int t_index)
{
    sf::RectangleShape keyShape;
    keyShape.setSize(whiteKeySize);
    keyShape.setFillColor(sf::Color::White);
    keyShape.setOutlineThickness(1.0f);
    keyShape.setOutlineColor(sf::Color::Black);
    keyShape.setPosition(sf::Vector2f{pianoPosX + t_index * (whiteKeySize.x + whiteSpacing), pianoPosY });

    keyShapes.push_back(keyShape);
}

void PianoVisualiser::setupBlackKey(int t_whiteKeyIndex)
{
    sf::RectangleShape keyShape;
    keyShape.setSize(blackKeySize);
    keyShape.setFillColor(sf::Color::Black);
    keyShape.setOutlineThickness(1.0f);
    keyShape.setOutlineColor(sf::Color::Black);
    float blackKeyOffsetX = (whiteKeySize.x + whiteSpacing) * t_whiteKeyIndex + whiteKeySize.x * 0.7f;
    keyShape.setPosition(sf::Vector2f{pianoPosX + blackKeyOffsetX, pianoPosY});

    keyShapes.push_back(keyShape);
}

void PianoVisualiser::setupPianoSounds()
{
    // Load each wav
}

void PianoVisualiser::keysTurnOn()
{
    // Get the midi data's key position and change the colour to red
}

void PianoVisualiser::keysTurnOff()
{
    // Reset the key back to it's original colour (white or black)
    // How do we know which key is which colour? We could count them manually...
}

void PianoVisualiser::renderKeys(sf::RenderWindow& t_window)
{
    // UI
    t_window.draw(m_keyboardBase);

    // White keys first
    for (int i = 0; i < keyShapes.size(); i++)
    {
        if (keyShapes[i].getFillColor() == sf::Color::White)
        {
            t_window.draw(keyShapes[i]);
        }
    }

    // Black keys on top of the white ones
    for (int i = 0; i < keyShapes.size(); i++)
    {
        if (keyShapes[i].getFillColor() == sf::Color::Black)
        {
            t_window.draw(keyShapes[i]);
        }
    }
}
