#include "Keyboard.h"

Keyboard::Keyboard(SoundManager& t_soundManager) : m_soundManager(&t_soundManager)
{
    
}

void Keyboard::setupKeys()
{
    m_keys.clear();
    int whiteIndex = 0;

    // Two full octaves: C3 to B4
    for (int octave = 3; octave <= 4; octave++)
    {
        setupWhiteKey(whiteIndex++, "C", octave);
        setupBlackKey(whiteIndex - 1, "C#", octave);
        setupWhiteKey(whiteIndex++, "D", octave);
        setupBlackKey(whiteIndex - 1, "D#", octave);
        setupWhiteKey(whiteIndex++, "E", octave);
        setupWhiteKey(whiteIndex++, "F", octave);
        setupBlackKey(whiteIndex - 1, "F#", octave);
        setupWhiteKey(whiteIndex++, "G", octave);
        setupBlackKey(whiteIndex - 1, "G#", octave);
        setupWhiteKey(whiteIndex++, "A", octave);
        setupBlackKey(whiteIndex - 1, "A#", octave);
        setupWhiteKey(whiteIndex++, "B", octave);
    }

    // Final C5
    setupWhiteKey(whiteIndex++, "C", 5);

    float baseWidth = (whiteIndex) * (m_whiteKeySize.x + m_whiteSpacing) - m_whiteSpacing;
    m_keyboardBase.setSize(sf::Vector2f{ baseWidth, m_whiteKeySize.y + 6.0f });
    m_keyboardBase.setPosition(sf::Vector2f{ m_posX, m_posY - 3.0f });
    m_keyboardBase.setFillColor(sf::Color::Black);

    m_killTrigger.setSize(sf::Vector2f{ baseWidth, 10.0f });
    m_killTrigger.setPosition(sf::Vector2f{ m_posX, m_posY });
    m_killTrigger.setFillColor(c_killTriggerColour);

   
    m_inputTrigger.setSize(sf::Vector2f{ baseWidth, m_inputTriggerSizeY });
    m_inputTrigger.setOrigin(sf::Vector2f{ 0.0f, m_inputTriggerSizeY });
    m_inputTrigger.setPosition(sf::Vector2f{ m_posX, m_posY });
    m_inputTrigger.setFillColor(c_inputTriggerColour);

    resetAllKeys();
}

void Keyboard::setEasyInput()
{
    //m_inputTrigger

    //if (b_EasyInput == true)
    //{

    //}
}

void Keyboard::setupWhiteKey(int t_whiteIndex, std::string t_noteLetter, int t_octave)
{
    Key key;

    key.shape.setSize(m_whiteKeySize);
    key.shape.setFillColor(sf::Color::White);
    key.shape.setOutlineThickness(1.0f);
    key.shape.setOutlineColor(sf::Color::Black);
    key.shape.setPosition(sf::Vector2f{m_posX + t_whiteIndex * (m_whiteKeySize.x + m_whiteSpacing), m_posY });

    key.noteName = t_noteLetter + std::to_string(t_octave);
    key.b_isSharpKey = false;
    key.b_isPressed = false;
    key.originalColour = sf::Color::White;

    m_keys.push_back(key);
}

void Keyboard::setupBlackKey(int t_whiteIndex, std::string t_noteLetter, int t_octave)
{
    Key key;

    key.shape.setSize(m_blackKeySize);
    key.shape.setFillColor(sf::Color::Black);
    key.shape.setOutlineThickness(1.0f);
    key.shape.setOutlineColor(sf::Color(10, 10, 10, 255));

    // Position the black key between the two white keys it sits above
    float blackOffsetX = (m_whiteKeySize.x + m_whiteSpacing) * t_whiteIndex + m_whiteKeySize.x * 0.7f;
    key.shape.setPosition(sf::Vector2f{ m_posX + blackOffsetX, m_posY });

    key.noteName = t_noteLetter + std::to_string(t_octave);
    key.b_isSharpKey = true;
    key.b_isPressed = false;
    key.originalColour = sf::Color::Black;

    m_keys.push_back(key);
}

void Keyboard::setupSounds()
{
    std::string noteNames[] = { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };

    for (int octave = 3; octave <= 4; octave++)
    {
        for (const auto& note : noteNames)
        {
            std::string soundName = note + std::to_string(octave);
            std::string filename = "ASSETS\\AUDIO\\Piano\\" + soundName + ".WAV";
            std::cerr << "WAV loading: " << filename << std::endl;
            m_soundManager->loadBuffer(soundName, filename, SoundType::MUSIC);
        }
    }

    // Final C5
    m_soundManager->loadBuffer("C5", "ASSETS\\AUDIO\\Piano\\C5.WAV", SoundType::MUSIC);
}

void Keyboard::render(sf::RenderWindow& t_window)
{
    t_window.draw(m_keyboardBase);

    // White keys first so black keys render on top
    for (auto& key : m_keys)
    {
        if (!key.b_isSharpKey == true)
        {
            t_window.draw(key.shape);
        }
    }

    for (auto& key : m_keys)
    {
        if (key.b_isSharpKey == true)
        {
            t_window.draw(key.shape);
        }
    }

    t_window.draw(m_killTrigger);
    t_window.draw(m_inputTrigger);
}

void Keyboard::handleClick(sf::Vector2f t_mousePos)
{
    // Check black keys first — they sit on top visually
    for (int i = 0; i < static_cast<int>(m_keys.size()); i++)
    {
        if (m_keys[i].b_isSharpKey && checkIfKeyClicked(t_mousePos, m_keys[i]))
        {
            keyTurnOn(i);
            m_soundManager->play(m_keys[i].noteName);
            std::cerr << "Clicked black key: " << m_keys[i].noteName << std::endl;
            return; // Don't fall through to white key check
        }
    }

    for (int i = 0; i < static_cast<int>(m_keys.size()); i++)
    {
        if (!m_keys[i].b_isSharpKey && checkIfKeyClicked(t_mousePos, m_keys[i]))
        {
            keyTurnOn(i);
            m_soundManager->play(m_keys[i].noteName);
            std::cerr << "Clicked white key: " << m_keys[i].noteName << std::endl;
            return;
        }
    }
}

bool Keyboard::checkIfKeyClicked(sf::Vector2f t_mousePos, Key& t_key)
{
    sf::Vector2f topLeft = t_key.shape.getPosition();
    sf::Vector2f size = t_key.shape.getSize();

    return t_mousePos.x >= topLeft.x &&
        t_mousePos.x <= topLeft.x + size.x &&
        t_mousePos.y >= topLeft.y &&
        t_mousePos.y <= topLeft.y + size.y;
}

bool Keyboard::checkInputCollision(sf::RectangleShape& t_noteShape)
{
    return t_noteShape.getGlobalBounds().findIntersection(m_inputTrigger.getGlobalBounds()).has_value();
}

float Keyboard::getKeyPosX(std::string& t_noteName)
{
    for (const auto& key : m_keys)
    {
        if (key.noteName == t_noteName)
        {
            return key.shape.getPosition().x;
        }
    }

    std::cerr << "Key not found: " << t_noteName << std::endl;
    return -1.0f; 
}

float Keyboard::getKillTriggerY()
{
    return m_killTrigger.getPosition().y;
}

int Keyboard::getScore()
{
    return m_score;
}


void Keyboard::handleRelease(sf::Vector2f t_mousePos)
{
    for (int i = 0; i < m_keys.size(); i++)
    {
        if (m_keys[i].b_isPressed /*&& checkIfKeyClicked(t_mousePos, m_keys[i])*/)
        {
            keyTurnOff(i);
            //return;
        }
    }
}

void Keyboard::noteOn(const std::string& t_noteName)
{
    for (int i = 0; i < m_keys.size(); i++)
    {
        if (m_keys[i].noteName == t_noteName)
        {
            keyTurnOn(i);
            m_soundManager->play(t_noteName);
            return; // stop the loop
        }
    }
}

void Keyboard::noteOff(const std::string& t_noteName)
{
    for (int i = 0; i < m_keys.size(); i++)
    {
        if (m_keys[i].noteName == t_noteName)
        {
            keyTurnOff(i);
            return;
        }
    }
}

void Keyboard::keyTurnOn(int t_index)
{
    if (t_index >= 0 && t_index < static_cast<int>(m_keys.size()))
    {
        m_keys[t_index].b_isPressed = true;
        m_keys[t_index].shape.setFillColor(c_pressedColour);
    }
}

void Keyboard::keyTurnOff(int t_index)
{
    if (t_index >= 0 && t_index < static_cast<int>(m_keys.size()))
    {
        m_keys[t_index].b_isPressed = false;
        m_keys[t_index].shape.setFillColor(m_keys[t_index].originalColour);
    }
}

void Keyboard::resetAllKeys()
{
    for (int i = 0; i < static_cast<int>(m_keys.size()); i++)
    {
        keyTurnOff(i);
    }
}

