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

void PianoVisualiser::setupWhiteKey(int t_index)
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

void PianoVisualiser::setupBlackKey(int t_whiteKeyIndex)
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
    // Load each wav
}

void PianoVisualiser::keysTurnOn(int t_KeyPos)
{
    // Get the midi data's key position and change the colour to red
}

void PianoVisualiser::keysTurnOff(int t_KeyPos)
{
    // Reset the key back to it's original colour (white or black)
    // How do we know which key is which colour? We could count them manually...
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

