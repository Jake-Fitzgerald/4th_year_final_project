#include "HUD.h"

HUD::HUD(const sf::Font& font) : m_fpsText(font),
								 m_midiFileNameText(font),
								 m_midiTimeSigText(font),
								 m_midiBPMText(font),
								 m_playButtonSprite(m_playButtonTexture),
								 m_pauseButtonSprite(m_pauseButtonTexture),
								 m_skipEndButtonSprite(m_skipEndButtonTexture),
								 m_skipStartButtonSprite(m_skipStartButtonTexture),
								 m_stopButtonSprite(m_stopButtonTexture),
								 m_muteButtonSprite(m_muteButtonTexture),
								 m_unmuteButtonSprite(m_unmuteButtonTexture),
	                             m_midiKeyboardText(font)
{
	// FPS
	m_fpsText.setPosition(sf::Vector2f{ SCREEN_CENTRE.x + 600.0f, SCREEN_CENTRE.y - 350.0f });
	m_fpsText.setFillColor(sf::Color::White);
	m_fpsText.setOutlineColor(sf::Color::Black);
	m_fpsText.setOutlineThickness(2.0f);
	m_fpsText.setCharacterSize(20U);
	m_fpsText.setString("???");
	b_isFPSVisible = true;

	// Midi Info
	b_isFPSVisible = true;
	m_midiFileNameText.setPosition(m_midiTextPos);
	m_midiFileNameText.setFillColor(sf::Color::White);
	m_midiFileNameText.setOutlineColor(sf::Color::Black);
	m_midiFileNameText.setOutlineThickness(2.0f);
	m_midiFileNameText.setCharacterSize(20U);
	m_midiFileNameText.setString("Midi File: ");
	// Time Signature
	m_midiTimeSigText.setPosition(sf::Vector2f{ m_midiTextPos.x + 400.0f, m_midiTextPos.y });
	m_midiTimeSigText.setFillColor(sf::Color::White);
	m_midiTimeSigText.setOutlineColor(sf::Color::Black);
	m_midiTimeSigText.setOutlineThickness(2.0f);
	m_midiTimeSigText.setCharacterSize(20U);
	m_midiTimeSigText.setString("Time Signature: X / X");
	// BPM
	m_midiBPMText.setPosition(sf::Vector2f{ m_midiTextPos.x + 600.0f, m_midiTextPos.y });
	m_midiBPMText.setFillColor(sf::Color::White);
	m_midiBPMText.setOutlineColor(sf::Color::Black);
	m_midiBPMText.setOutlineThickness(2.0f);
	m_midiBPMText.setCharacterSize(20U);
	m_midiBPMText.setString("BPM: ");
	
	// UI Polish
	m_bottomBorderBar.setPosition(m_midiTextPos);
	m_bottomBorderBar.setFillColor(sf::Color(50, 50, 50, 150));
	m_bottomBorderBar.setOutlineColor(sf::Color::Black);
	m_bottomBorderBar.setOutlineThickness(2.0f);
	m_bottomBorderBar.setSize(sf::Vector2f{ 800.0f, 25.0f });

	// Beat Markers
	setupBeatMarkers();

	setupButtonSprites();

	// Midi Keyboard Text
	m_midiKeyboardText.setPosition(sf::Vector2f{ m_midiTextPos.x + 900.0f, m_midiTextPos.y });
	m_midiKeyboardText.setFillColor(sf::Color::White);
	m_midiKeyboardText.setOutlineColor(sf::Color::Black);
	m_midiKeyboardText.setOutlineThickness(2.0f);
	m_midiKeyboardText.setCharacterSize(20U);
	m_midiKeyboardText.setString("Midi Keyboard: OFF");
}

void HUD::setupBeatMarkers()
{
	// Clear the original rectangle colours if a new time signature is parsed
	for (int i = 0; i < m_beatMarkers.size(); i++)
	{
		m_beatMarkers[i].setFillColor(c_beatMarkerClear);
	}

	for (int i = 0; i < m_nominator; i++)
	{
		sf::RectangleShape beatRectangle;

		beatRectangle.setOutlineColor(sf::Color::Black);
		beatRectangle.setOutlineThickness(2.0f);
		beatRectangle.setSize(m_beatMarkerSize);
		beatRectangle.setPosition(sf::Vector2f{ m_beatMarkerLeftPos.x + (50.0f * i), m_beatMarkerLeftPos.y });


		if (i == m_nominator - 1)
		{
			beatRectangle.setFillColor(c_beatMarkerSetWholeNote);
		}
		else
		{
			beatRectangle.setFillColor(c_beatMarkerClear);
		}

		m_beatMarkers.push_back(beatRectangle);  
	}
}

void HUD::setupButtonSprites()
{
	// Play
	if (!m_playButtonTexture.loadFromFile("ASSETS\\IMAGES\\UI\\button_play.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading play button" << std::endl;
	}
	m_playButtonSprite.setTexture(m_playButtonTexture, true);
	m_playButtonSprite.setScale(sf::Vector2f(1.0f, 1.0f));
	m_playButtonSprite.setPosition(sf::Vector2f{ buttonsLeftPos.x, buttonsLeftPos.y });


	// Pause
	if (!m_pauseButtonTexture.loadFromFile("ASSETS\\IMAGES\\UI\\button_pause.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading pause button" << std::endl;
	}
	m_pauseButtonSprite.setTexture(m_pauseButtonTexture, true);
	m_pauseButtonSprite.setScale(sf::Vector2f(1.0f, 1.0f));
	m_pauseButtonSprite.setPosition(sf::Vector2f{ buttonsLeftPos.x + 50.0f, buttonsLeftPos.y });

	// Skip to End Button
	if (!m_skipEndButtonTexture.loadFromFile("ASSETS\\IMAGES\\UI\\button_skip_to_end.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading skip to end button" << std::endl;
	}
	m_skipEndButtonSprite.setTexture(m_skipEndButtonTexture, true);
	m_skipEndButtonSprite.setScale(sf::Vector2f(1.0f, 1.0f));
	m_skipEndButtonSprite.setPosition(sf::Vector2f{ buttonsLeftPos.x + 100.0f, buttonsLeftPos.y });

	// Skip to Start Button
	if (!m_skipStartButtonTexture.loadFromFile("ASSETS\\IMAGES\\UI\\button_skip_to_start.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading skip to end button" << std::endl;
	}
	m_skipStartButtonSprite.setTexture(m_skipStartButtonTexture, true);
	m_skipStartButtonSprite.setScale(sf::Vector2f(1.0f, 1.0f));
	m_skipStartButtonSprite.setPosition(sf::Vector2f{ buttonsLeftPos.x + 150.0f, buttonsLeftPos.y });

	// Stop Button
	if (!m_stopButtonTexture.loadFromFile("ASSETS\\IMAGES\\UI\\button_stop.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading stop button" << std::endl;
	}
	m_stopButtonSprite.setTexture(m_stopButtonTexture, true);
	m_stopButtonSprite.setScale(sf::Vector2f(1.0f, 1.0f));
	m_stopButtonSprite.setPosition(sf::Vector2f{ buttonsLeftPos.x + 200.0f, buttonsLeftPos.y });

	// Mute Button
	if (!m_muteButtonTexture.loadFromFile("ASSETS\\IMAGES\\UI\\button_audio_on.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading mute button" << std::endl;
	}
	m_muteButtonSprite.setTexture(m_muteButtonTexture, true);
	m_muteButtonSprite.setScale(sf::Vector2f(1.0f, 1.0f));
	m_muteButtonSprite.setPosition(sf::Vector2f{ buttonsLeftPos.x + 250.0f, buttonsLeftPos.y });

	// Unmute Button
	if (!m_unmuteButtonTexture.loadFromFile("ASSETS\\IMAGES\\UI\\button_audio_off.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading unmute button" << std::endl;
	}
	m_unmuteButtonSprite.setTexture(m_unmuteButtonTexture, true);
	m_unmuteButtonSprite.setScale(sf::Vector2f(1.0f, 1.0f));
	m_unmuteButtonSprite.setPosition(sf::Vector2f{ buttonsLeftPos.x + 300.0f, buttonsLeftPos.y });

	// Return Button
	if (!m_returnTexture.loadFromFile("ASSETS\\IMAGES\\UI\\Return_Button.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading Return button in HUD" << std::endl;
	}

	m_returnSprite.setTexture(m_returnTexture, true);
	m_returnSprite.setPosition(sf::Vector2f{ buttonsLeftPos.x + 400.0f, buttonsLeftPos.y });
	m_returnSprite.setScale(sf::Vector2f{ 0.5, 0.5 });
}

void HUD::updateFPSText(float & t_fpsNumber)
{
	m_fpsNumber = t_fpsNumber;
	m_fpsText.setString(std::to_string(static_cast<int>(m_fpsNumber)));
}

void HUD::setFPSBool()
{
	if (b_isFPSVisible == true)
	{
		b_isFPSVisible = false;
	}
	else
	{
		b_isFPSVisible = true;
	}
}

bool HUD::getFPSBool()
{
	return b_isFPSVisible;
}

void HUD::drawHUD(sf::RenderWindow &t_window)
{
	if (b_isFPSVisible)
	{
		t_window.draw(m_fpsText);
	}

	// Buttons
	t_window.draw(m_playButtonSprite);
	t_window.draw(m_pauseButtonSprite);
	t_window.draw(m_skipEndButtonSprite);
	t_window.draw(m_skipStartButtonSprite);
	t_window.draw(m_stopButtonSprite);
	t_window.draw(m_muteButtonSprite);
	t_window.draw(m_unmuteButtonSprite);
	t_window.draw(m_returnSprite);
	
	// Beat Markers
	/*
	for (int i = 0; i < m_beatMarkersLeft.size(); i++)
	{
		t_window.draw(m_beatMarkersLeft[i]);
	}
	for (int i = 0; i < m_beatMarkersRight.size(); i++)
	{
		t_window.draw(m_beatMarkersRight[i]);
	}
	t_window.draw(m_beatMarkerWholeNote);
	*/
	for (int i = 0; i < m_beatMarkers.size(); i++)
	{
		t_window.draw(m_beatMarkers[i]);
	}

	// Midi Info
	t_window.draw(m_midiFileNameText);
	t_window.draw(m_midiTimeSigText);
	t_window.draw(m_midiBPMText);

	// UI Polish
	t_window.draw(m_bottomBorderBar);

	// Midi Keyboard
	t_window.draw(m_midiKeyboardText);
}

void HUD::loadMidiData(const std::vector<MidiTrack>& t_tracks, std::string t_timeSig, double t_bpm, std::string t_midiFileName, int t_nom, int t_denom)
{
	std::string midiNameOnly = removePathData(t_midiFileName);
	m_midiFileName = midiNameOnly;

	m_midiTimeSig = t_timeSig;
	m_nominator = t_nom;
	m_denomator = t_denom;

	// Truncate the tempo becuase we don't need to show it's decimals
	int bpmInt = t_bpm;
	m_midiBPM = std::to_string(bpmInt);

	updateMidiInfo();
}

void HUD::updateMidiInfo()
{
	m_midiFileNameText.setString("Midi File: " + m_midiFileName);
	m_midiTimeSigText.setString("Time Signature: " + m_midiTimeSig);
	m_midiBPMText.setString("BPM: " + m_midiBPM);
	setupBeatMarkers();
}

std::string HUD::removePathData(std::string t_midiPathName)
{
	//int pathIndex = std::stoi(t_midiPathName);
	int pathIndex = (int)t_midiPathName.length();
	
	// Find last slash
	int lastSlash = -1;
	for (int i = 0; i < pathIndex; i++)
	{
		if (t_midiPathName[i] == '\\')
		{
			lastSlash = i;
		}
			
	}

	// Copy everything after the last slash
	std::string filename = "";
	for (int i = lastSlash + 1; i < pathIndex; i++)
	{
		filename += t_midiPathName[i];
	}

	int extensionDot = -1;
	int fileNameLength = (int)filename.length();
	for (int i = 0; i < fileNameLength; i++)
	{
		if (filename[i] == '.')
		{
			extensionDot = i;
		}
			
	}

	// Keep only up to the dot
	std::string baseName = "";
	for (int i = 0; i < extensionDot; i++)
	{
		baseName += filename[i];
	}


	return filename;
}

void HUD::mouseClick(sf::Vector2f t_mousePos)
{
	//for (auto& button : m_buttons)
	//{
	//	// Reset colours if you click again
	//	button.m_buttonShape.setFillColor(sf::Color::Blue);


	//	sf::Vector2f topLeft = button.m_buttonShape.getPosition();
	//	sf::Vector2f size = button.m_buttonShape.getSize();

	//	if (checkIfAreaClicked(t_mousePos, topLeft, size) == true)
	//	{
	//		m_selectedPath = button.midiPath;
	//		std::cerr << "Selected Path is: " << m_selectedPath << std::endl;

	//		// Turn it red to show it has been clicked
	//		button.m_buttonShape.setFillColor(sf::Color::Red);
	//	}
	//}
}

bool HUD::returnClick(sf::Vector2f t_mousePos)
{
	// Return Button
	sf::Vector2f spriteTopLeft = m_returnSprite.getPosition();
	sf::Vector2f spriteSize = sf::Vector2f{ m_returnSprite.getGlobalBounds().size.x, m_returnSprite.getGlobalBounds().size.y };

	if (checkIfAreaClicked(t_mousePos, spriteTopLeft, spriteSize) == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool HUD::playClick(sf::Vector2f t_mousePos)
{
	// Play Button
	sf::Vector2f spriteTopLeft = m_playButtonSprite.getPosition();
	sf::Vector2f spriteSize = sf::Vector2f{ m_playButtonSprite.getGlobalBounds().size.x, m_playButtonSprite.getGlobalBounds().size.y };

	if (checkIfAreaClicked(t_mousePos, spriteTopLeft, spriteSize) == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool HUD::pauseClick(sf::Vector2f t_mousePos)
{
	// Pause Button
	sf::Vector2f spriteTopLeft = m_pauseButtonSprite.getPosition();
	sf::Vector2f spriteSize = sf::Vector2f{ m_pauseButtonSprite.getGlobalBounds().size.x, m_pauseButtonSprite.getGlobalBounds().size.y };

	if (checkIfAreaClicked(t_mousePos, spriteTopLeft, spriteSize) == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool HUD::stopClick(sf::Vector2f t_mousePos)
{
	// Stop Button
	sf::Vector2f spriteTopLeft = m_stopButtonSprite.getPosition();
	sf::Vector2f spriteSize = sf::Vector2f{ m_stopButtonSprite.getGlobalBounds().size.x, m_stopButtonSprite.getGlobalBounds().size.y };

	if (checkIfAreaClicked(t_mousePos, spriteTopLeft, spriteSize) == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool HUD::skipToStart(sf::Vector2f t_mousePos)
{
	// Skip to Start Button
	sf::Vector2f spriteTopLeft = m_skipStartButtonSprite.getPosition();
	sf::Vector2f spriteSize = sf::Vector2f{ m_skipStartButtonSprite.getGlobalBounds().size.x, m_skipStartButtonSprite.getGlobalBounds().size.y };

	if (checkIfAreaClicked(t_mousePos, spriteTopLeft, spriteSize) == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool HUD::skipToEnd(sf::Vector2f t_mousePos)
{
	// Skip to End Button
	sf::Vector2f spriteTopLeft = m_skipEndButtonSprite.getPosition();
	sf::Vector2f spriteSize = sf::Vector2f{ m_skipEndButtonSprite.getGlobalBounds().size.x, m_skipEndButtonSprite.getGlobalBounds().size.y };

	if (checkIfAreaClicked(t_mousePos, spriteTopLeft, spriteSize) == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool HUD::muteClick(sf::Vector2f t_mousePos)
{
	// Mute Button
	sf::Vector2f spriteTopLeft = m_muteButtonSprite.getPosition();
	sf::Vector2f spriteSize = sf::Vector2f{ m_muteButtonSprite.getGlobalBounds().size.x, m_muteButtonSprite.getGlobalBounds().size.y };

	if (checkIfAreaClicked(t_mousePos, spriteTopLeft, spriteSize) == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool HUD::checkIfAreaClicked(sf::Vector2f t_mousePos, sf::Vector2f t_topLeft, sf::Vector2f t_size)
{
	if (t_mousePos.x >= t_topLeft.x &&
		t_mousePos.x <= t_topLeft.x + t_size.x &&
		t_mousePos.y >= t_topLeft.y &&
		t_mousePos.y <= t_topLeft.y + t_size.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void HUD::updateMidiKeyboardConnnection(bool t_connectStatus)
{
	b_isMidiKeyboardConnected = t_connectStatus;

	if (b_isMidiKeyboardConnected == true)
	{
		m_midiKeyboardText.setString("Midi Keyboard: ON");
	}
	else
	{
		m_midiKeyboardText.setString("Midi Keyboard: OFF");
	}
}
