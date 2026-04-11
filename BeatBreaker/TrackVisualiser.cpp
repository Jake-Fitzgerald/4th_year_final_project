#include "TrackVisualiser.h"

TrackVisualiser::TrackVisualiser(std::shared_ptr<const sf::Font> font) : m_font(font)
{

}

void TrackVisualiser::setupShapes()
{
    // Track Dividers
    for (int i = 0; i < lineCount; i++)
    {
        sf::RectangleShape line;
        line.setSize(sf::Vector2f(lineWidth, lineHeight));
        line.setFillColor(sf::Color::White);
        line.setPosition(sf::Vector2f{ visualiserOrigin.x + i * spacing, visualiserOrigin.y });

        trackLinesVertical.push_back(line);
    }

    // Horizontal Lines
    for (int i = 0; i < horizontalLineCount; i++)
    {
        sf::RectangleShape line;
        line.setSize({ visualiserWidth, horizontalLineHeight });
        line.setFillColor(sf::Color(50, 50, 150));
        line.setPosition(sf::Vector2f{ visualiserOrigin.x, visualiserOrigin.y + i * 110.0f });

        trackLinesHorizontal.push_back(line);
    }

    // Bottom UI
    for (int i = 0; i < 3; i++)
    {
        sf::RectangleShape borderLines;
        borderLines.setSize(sf::Vector2f(visualiserWidth, bottomBorderHeight));
        borderLines.setFillColor(sf::Color::White);
        borderLines.setPosition(sf::Vector2f{ visualiserOrigin.x, (visualiserOrigin.y + bottomBorderStartY) + i * 50.0f });

        bottomBorders.push_back(borderLines);
    }

    // Track Name Boxes
    for (int row = 0; row < 2; row++)  // 2 rows
    {

        for (int i = 0; i < lineCount; i++)
        {
            sf::RectangleShape box;
            box.setOrigin(sf::Vector2f{ boxWidth * 0.5f, 0.0f });
            box.setSize(sf::Vector2f{ boxWidth, boxHeight });
            box.setFillColor(sf::Color(50, 50, 50, 100));
            box.setOutlineThickness(1.0f);
            box.setOutlineColor(sf::Color::White);

            float boxX = visualiserOrigin.x + (i * spacing) + (spacing * 0.5f);

            float boxY = visualiserOrigin.y + visualiserYStart + boxYOffset + (row * (boxHeight + 20.f));

            box.setPosition(sf::Vector2f{ boxX , boxY });

            trackNameBox.push_back(box);


            // Instrument Channel Texts
            if (row == 0)
            {
                sf::Text trackChannelText(*m_font);
                trackChannelText.setString("Channel " + std::to_string(i + 1)); // Change this to the current instrument from that track
                trackChannelText.setCharacterSize(20U);
                trackChannelText.setFillColor(sf::Color::White);
                trackChannelText.setOutlineColor(sf::Color::Black);
                trackChannelText.setOutlineThickness(2.0f);

                trackChannelText.setPosition(sf::Vector2f{ boxX - 35.0f , boxY });

                m_trackNameTexts.push_back(trackChannelText);
            }
            // Track Number Texts
            if (row == 1)
            {
                sf::Text trackNumText(*m_font);
                trackNumText.setString("Track " + std::to_string(i + 1)); 
                trackNumText.setCharacterSize(20U);
                trackNumText.setFillColor(sf::Color::White);
                trackNumText.setOutlineColor(sf::Color::Black);
                trackNumText.setOutlineThickness(2.0f);

                trackNumText.setPosition(sf::Vector2f{ boxX - 35.0f , boxY});

                m_trackNumberTexts.push_back(trackNumText);
            }
        }
    }

    setupColours();
}

void TrackVisualiser::setupColours()
{
    trackColours.push_back(trackCol1);
    trackColours.push_back(trackCol2);
    trackColours.push_back(trackCol3);
    trackColours.push_back(trackCol4);
    trackColours.push_back(trackCol5);
    trackColours.push_back(trackCol6);
    trackColours.push_back(trackCol7);
    trackColours.push_back(trackCol8);
}

void TrackVisualiser::renderTrackVis(sf::RenderWindow& t_window)
{
    // Track Dividers
    for (int i = 0; i < trackLinesVertical.size(); i++)
    {
        t_window.draw(trackLinesVertical[i]);
    }

    // Horizontal Lines
    for (int i = 0; i < trackLinesHorizontal.size(); i++)
    {
        t_window.draw(trackLinesHorizontal[i]);
    }

    // Bottom UI
    // Bottom Borders
    for (int i = 0; i < bottomBorders.size(); i++)
    {
        t_window.draw(bottomBorders[i]);
    }

    // Track Boxes
    for (int i = 0; i < trackNameBox.size(); i++)
    {
        t_window.draw(trackNameBox[i]);
    }

    // Track Name Texts
    for (int i = 0; i < m_trackNameTexts.size(); i++)
    {
        t_window.draw(m_trackNameTexts[i]);
    }

    // TrackNumbers
    for (int i = 0; i < m_trackNumberTexts.size(); i++)
    {
        t_window.draw(m_trackNumberTexts[i]);
    }
}

void TrackVisualiser::update(float t_deltaTime)
{

}

void TrackVisualiser::loadMidiTracks(const std::vector<MidiTrack>& t_tracks, int t_ticksPerQuarter, double t_bpm)
{
    m_midiTracks = t_tracks;
    m_ticksPerQuarter = t_ticksPerQuarter;
    m_bpm = t_bpm;

    // Track 0 is Time Signature, Track 1 is the Tempo data
    for (int i = 0; i < m_midiTracks.size(); i++)
    {
        m_trackNameTexts[i].setString(m_midiTracks[i].trackName);
        std::cerr << "Track " << i << " - " << m_midiTracks[i].trackName << std::endl;
    }
}

void TrackVisualiser::playSong()
{
    b_isSongPlaying = true;
}

void TrackVisualiser::pauseSong()
{
    b_isSongPlaying = false;
}

void TrackVisualiser::stopSong()
{
    b_isSongPlaying = false;
    // Rest song time
    m_songCurrentTime = 0.0f;

    // Reset Midi Track stuff
    for (int i = 0; i < m_midiTracks.size(); i++)
    {
       // m_midiTracks[i].
    }
}
