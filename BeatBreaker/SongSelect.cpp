#include "SongSelect.h"

SongSelect::SongSelect(std::shared_ptr<const sf::Font> font) 
						: m_font(font),
						  m_beginText(*font),
						  m_previewText(*font),
						  m_ghostext(*font),
						  m_songListFrameText(*font),
						  m_modeButtonsFrameText(*font),
				          m_loadMidiField(font, m_loadMidiFieldPos, m_fieldSize, m_characterSize),
						  m_loadCustomMidiButtonText(*font)
{
	b_isSongChosen = false;
}


void SongSelect::setupPathStrings()
{
	m_pathVector =
	{
		/*{"Debug Gameplay", "ASSETS\\AUDIO\\MUSIC\\Debug Gameplay.mid", SONGDIFFICULTIES::EASY},*/
		{"C Scale", "ASSETS\\AUDIO\\MUSIC\\C_Scale.mid", SONGDIFFICULTIES::EASY},
		{"Ode To Joy", "ASSETS\\AUDIO\\MUSIC\\OdeToJoy.mid", SONGDIFFICULTIES::EASY},
		/*{"Note Length", "ASSETS\\AUDIO\\MUSIC\\NoteLengthExample.mid", SONGDIFFICULTIES::EASY},*/
		{"Major / Minor Chords", "ASSETS\\AUDIO\\MUSIC\\Major_and_Minor_Chords.mid", SONGDIFFICULTIES::MEDIUM},
		{"The Scientist", "ASSETS\\AUDIO\\MUSIC\\TheScientist.mid", SONGDIFFICULTIES::MEDIUM},
		//{"Fast BPM", "ASSETS\\AUDIO\\MUSIC\\Fast_BPM.mid", SONGDIFFICULTIES::HARD},
		{"Thousand Miles", "ASSETS\\AUDIO\\MUSIC\\ThousandMilesRiff.mid", SONGDIFFICULTIES::HARD},
		//{"Full MCI Example [TEST]", "ASSETS\\AUDIO\\MUSIC\\Full_MIDI_Range.mid", SONGDIFFICULTIES::UNKNOWN},
		//{"Saved Midi", "ASSETS\\AUDIO\\MUSIC\\SavedMidi\\custom.mid", SONGDIFFICULTIES::UNKNOWN},
		//{"Test Riff", "ASSETS\\AUDIO\\MUSIC\\SavedMidi\\TestRiff.mid", SONGDIFFICULTIES::UNKNOWN},
	};

	m_pathsCount = m_pathVector.size();
}

void SongSelect::setupButtons()
{
	m_buttons.reserve(m_pathsCount);

	// Shapes
	for (int i = 0; i < m_pathsCount; i++)
	{
		SongButton button(m_font);

		button.m_buttonShape.setSize(m_buttonSize);
		button.m_buttonShape.setPosition(sf::Vector2f{ m_posX , m_posY + i * m_spacing });
		button.m_buttonShape.setFillColor(sf::Color::Blue);
		button.m_buttonShape.setOutlineThickness(2.0f);
		button.m_buttonShape.setOutlineColor(sf::Color::Black);

		// Song name
		button.m_songNameText.setFont(*m_font);
		button.m_songNameText.setString(m_pathVector[i].name);
		button.m_songNameText.setCharacterSize(20);
		button.m_songNameText.setFillColor(sf::Color::White);
		button.m_songNameText.setPosition(sf::Vector2f{
														button.m_buttonShape.getPosition().x + 10.f,
														button.m_buttonShape.getPosition().y + 10.f });

		// Diffulty
		button.m_difficultyText.setFont(*m_font);
		button.m_difficultyText.setString("Difficulty: ");
		button.m_difficultyText.setCharacterSize(20);
		button.m_difficultyText.setFillColor(sf::Color::White);
		button.m_difficultyText.setPosition(sf::Vector2f{
															button.m_buttonShape.getPosition().x + m_difficultyTextSpacing,
															button.m_buttonShape.getPosition().y + 10.f });

		// Song Difficulty (temp)
		button.m_songDifficultyText.setFont(*m_font);
		button.m_songDifficultyText.setString(DifficultyToString(m_pathVector[i].difficulty));
		button.m_songDifficultyText.setCharacterSize(20);

		// Difficulty Text colour change
		if (m_pathVector[i].difficulty == SONGDIFFICULTIES::EASY)
		{
			button.m_songDifficultyText.setFillColor(c_Easy);
		}
		else if (m_pathVector[i].difficulty == SONGDIFFICULTIES::MEDIUM)
		{
			button.m_songDifficultyText.setFillColor(c_Medium);
		}
		else if (m_pathVector[i].difficulty == SONGDIFFICULTIES::HARD)
		{
			button.m_songDifficultyText.setFillColor(c_Hard);
		}
		else
		{
			button.m_songDifficultyText.setFillColor(c_Unknown);
		}

		button.m_songDifficultyText.setPosition(sf::Vector2f{
																button.m_buttonShape.getPosition().x + m_difficultyTextSpacing + 100.0f,
																button.m_buttonShape.getPosition().y + 10.f });

		// Personal Best Score Text (temp)
		button.m_pbScoreText.setFont(*m_font);
		button.m_pbScoreText.setString("PB Score: ");
		button.m_pbScoreText.setCharacterSize(20);
		button.m_pbScoreText.setFillColor(sf::Color::White);
		button.m_pbScoreText.setPosition(sf::Vector2f{
																button.m_buttonShape.getPosition().x + m_difficultyTextSpacing + 200.0f,
																button.m_buttonShape.getPosition().y + 10.f });

		// Personal Best Score (temp)
		button.m_pbScore.setFont(*m_font);
		button.m_pbScore.setString("12345");
		button.m_pbScore.setCharacterSize(20);
		button.m_pbScore.setFillColor(sf::Color::White);
		button.m_pbScore.setPosition(sf::Vector2f{
																button.m_buttonShape.getPosition().x + m_difficultyTextSpacing + 300.0f,
																button.m_buttonShape.getPosition().y + 10.f });


		// Music Note
		if (!button.m_musicNoteTex->loadFromFile("ASSETS\\IMAGES\\UI\\button_play.png"))
		{
			std::cerr << "problem loading options music texture [Song Selection]" << std::endl;
		}

		button.m_musicNoteSprite.setTexture(*button.m_musicNoteTex, true);
		button.m_musicNoteSprite.setPosition(sf::Vector2f{
																button.m_buttonShape.getPosition().x + m_difficultyTextSpacing + 420.0f,
																button.m_buttonShape.getPosition().y + 5.f });
		button.m_musicNoteSprite.setScale(sf::Vector2f{ 0.6f, 0.6f });

		button.midiPath = m_pathVector[i].path;
		button.songName = m_pathVector[i].name;
		m_buttons.push_back(button);
	}

	setupBeginButton();
	setupPreviewButton();
	setupGhostButton();
	setupUIFrames();
	setupInputFieldButton();
}

void SongSelect::setupBeginButton()
{
	// Position the Begin button below the last song row
	float beginY = paddingY + m_pathsCount * m_spacing - 150.0f;

	m_beginButton.setSize(m_playButtonSize);
	m_beginButton.setPosition(sf::Vector2f{ paddingX + 900.0f, beginY + 100.0f});
	m_beginButton.setFillColor(c_buttonInactive);
	m_beginButton.setOutlineThickness(2.0f);
	m_beginButton.setOutlineColor(sf::Color::Black);

	m_beginText.setFont(*m_font);
	m_beginText.setString("Begin");
	m_beginText.setCharacterSize(30);
	m_beginText.setFillColor(sf::Color::White);

	sf::FloatRect textBounds = m_beginText.getLocalBounds();
	m_beginText.setPosition(sf::Vector2f
	{
			m_beginButton.getPosition().x + (m_beginButton.getSize().x - textBounds.size.x) / 2.0f,
			m_beginButton.getPosition().y + (m_beginButton.getSize().y - textBounds.size.y) / 2.0f - textBounds.position.y 
	});
}

void SongSelect::setupPreviewButton()
{
	float beginY = paddingY + m_pathsCount * m_spacing - 160.0f;

	m_previewButton.setSize(m_playButtonSize);
	m_previewButton.setPosition(sf::Vector2f{ paddingX + 900.0f, beginY + 200.0f });
	m_previewButton.setFillColor(c_buttonInactive);
	m_previewButton.setOutlineThickness(2.0f);
	m_previewButton.setOutlineColor(sf::Color::Black);

	m_previewText.setFont(*m_font);
	m_previewText.setString("Preview");
	m_previewText.setCharacterSize(30);
	m_previewText.setFillColor(sf::Color::White);

	sf::FloatRect textBounds = m_previewText.getLocalBounds();
	m_previewText.setPosition(sf::Vector2f
		{
				m_previewButton.getPosition().x + (m_previewButton.getSize().x - textBounds.size.x) / 2.0f,
				m_previewButton.getPosition().y + (m_previewButton.getSize().y - textBounds.size.y) / 2.0f - textBounds.position.y
		});
}

void SongSelect::setupGhostButton()
{
	float beginY = paddingY + m_pathsCount * m_spacing - 160.0f;

	m_ghostButton.setSize(m_ghostButtonSize);
	m_ghostButton.setPosition(sf::Vector2f{ paddingX + 900.0f, beginY + 300.0f });
	m_ghostButton.setFillColor(c_buttonInactive);
	m_ghostButton.setOutlineThickness(2.0f);
	m_ghostButton.setOutlineColor(sf::Color::Black);

	m_ghostext.setFont(*m_font);
	m_ghostext.setString("Ghost");
	m_ghostext.setCharacterSize(30);
	m_ghostext.setFillColor(sf::Color::White);

	sf::FloatRect textBounds = m_ghostext.getLocalBounds();
	m_ghostext.setPosition(sf::Vector2f
		{
				m_ghostButton.getPosition().x + (m_ghostButton.getSize().x - textBounds.size.x) / 2.0f,
				m_ghostButton.getPosition().y + (m_ghostButton.getSize().y - textBounds.size.y) / 2.0f - textBounds.position.y
		});
}

void SongSelect::setupUIFrames()
{
	m_songListFrame.setSize(sf::Vector2f{ m_buttonSize.x + 100.0f, m_buttonSize.y + 475.0f });
	m_songListFrame.setPosition(sf::Vector2f{ m_posX - 20.0f, m_posY - 25.0f });
	m_songListFrame.setFillColor(c_frameColour);
	m_songListFrame.setOutlineThickness(2.0f);
	m_songListFrame.setOutlineColor(sf::Color::Blue);

	m_songListFrameText.setString("Songs");
	m_songListFrameText.setPosition(sf::Vector2f{ m_posX, m_posY - 75.0f });
	m_songListFrameText.setFillColor(sf::Color::Blue);
	m_songListFrameText.setOutlineColor(sf::Color::Black);
	m_songListFrameText.setOutlineThickness(2.0f);
	m_songListFrameText.setCharacterSize(40U);

	m_songListTextFrame.setSize(sf::Vector2f{ 150.0f, 50.0f });
	m_songListTextFrame.setPosition(sf::Vector2f{ m_posX - 20.0f, m_posY - 75.0f });
	m_songListTextFrame.setFillColor(c_frameColour);
	m_songListTextFrame.setOutlineThickness(3.0f);
	m_songListTextFrame.setOutlineColor(sf::Color::Blue);


	m_modeButtonsFrame.setSize(sf::Vector2f{ m_playButtonSize.x + 50.0f, m_playButtonSize.y + 135.0f });
	m_modeButtonsFrame.setPosition(sf::Vector2f{ m_beginButton.getPosition().x - 25.0f, m_beginButton.getPosition().y - 25.0f });
	m_modeButtonsFrame.setFillColor(c_frameColour);
	m_modeButtonsFrame.setOutlineThickness(2.0f);
	m_modeButtonsFrame.setOutlineColor(sf::Color::Green);

	m_modeButtonsFrameText.setString("Modes");
	m_modeButtonsFrameText.setPosition(sf::Vector2f{ m_beginButton.getPosition().x, m_beginButton.getPosition().y - 75.0f });
	m_modeButtonsFrameText.setFillColor(sf::Color::Green);
	m_modeButtonsFrameText.setOutlineColor(sf::Color::Black);
	m_modeButtonsFrameText.setOutlineThickness(2.0f);
	m_modeButtonsFrameText.setCharacterSize(40U);
	
	m_modeButtonsTextFrame.setSize(sf::Vector2f{ 150.0f, 50.0f });
	m_modeButtonsTextFrame.setPosition(sf::Vector2f{ m_beginButton.getPosition().x - 25.0f, m_beginButton.getPosition().y - 75.0f });
	m_modeButtonsTextFrame.setFillColor(c_frameColour);
	m_modeButtonsTextFrame.setOutlineThickness(3.0f);
	m_modeButtonsTextFrame.setOutlineColor(sf::Color::Green);

	m_songListBottomBorder.setSize(sf::Vector2f{ m_buttonSize.x + 60.0f, 4.0f });
	m_songListBottomBorder.setPosition(sf::Vector2f{ m_posX , m_posY + 400.0f });
	m_songListBottomBorder.setFillColor(sf::Color(0, 0, 250, 130));
}

void SongSelect::setupInputFieldButton()
{
	m_loadCustomMidiButton.setPosition({ m_loadMidiFieldPos.x + 450, m_loadMidiFieldPos.y });
	m_loadCustomMidiButton.setSize(m_fieldButtonSize);
	m_loadCustomMidiButton.setFillColor(c_inactiveColour);
	m_loadCustomMidiButton.setOutlineColor(sf::Color::Black);
	m_loadCustomMidiButton.setOutlineThickness(2.0f);
	m_loadCustomMidiButtonText.setString("LOAD");
	m_loadCustomMidiButtonText.setPosition({ m_loadCustomMidiButton.getPosition().x + 20.0f, m_loadCustomMidiButton.getPosition().y - 12.0f });
	m_loadCustomMidiButtonText.setFillColor(sf::Color::White);
	m_loadCustomMidiButtonText.setOutlineColor(sf::Color::Black);
	m_loadCustomMidiButtonText.setOutlineThickness(2.0f);
	m_loadCustomMidiButtonText.setCharacterSize(50U);

	// Music Note
	if (!m_loadCustomMCITex.loadFromFile("ASSETS\\IMAGES\\UI\\button_play.png"))
	{
		std::cerr << "problem loading MCI sprite for custom midi input field [Song Selection]" << std::endl;
	}

	m_loadCustomMCISprite.setTexture(m_loadCustomMCITex, true);
	m_loadCustomMCISprite.setPosition(sf::Vector2f{
															m_loadMidiFieldPos.x + m_difficultyTextSpacing + 420.0f,
															m_loadMidiFieldPos.y + 5.f });
	m_loadCustomMCISprite.setScale(sf::Vector2f{ 0.8f, 0.8f });
	
}

void SongSelect::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_songListTextFrame);
	t_window.draw(m_modeButtonsTextFrame);
	t_window.draw(m_songListFrame);
	t_window.draw(m_modeButtonsFrame);
	t_window.draw(m_songListBottomBorder);

	for (auto& button : m_buttons)
	{
		t_window.draw(button.m_buttonShape);
		t_window.draw(button.m_songNameText);
		t_window.draw(button.m_difficultyText);
		t_window.draw(button.m_songDifficultyText);
		t_window.draw(button.m_pbScoreText);
		t_window.draw(button.m_pbScore);
		t_window.draw(button.m_musicNoteSprite);
	}

	t_window.draw(m_beginButton);
	t_window.draw(m_beginText);
	t_window.draw(m_previewButton);
	t_window.draw(m_previewText);
	t_window.draw(m_songListFrameText);
	t_window.draw(m_modeButtonsFrameText);
	t_window.draw(m_ghostButton);
	t_window.draw(m_ghostext);

	m_loadMidiField.render(t_window); 
	t_window.draw(m_loadCustomMidiButton);
	t_window.draw(m_loadCustomMidiButtonText);
	t_window.draw(m_loadCustomMCISprite);
}

SongClickResult SongSelect::mouseClick(sf::Vector2f t_mousePos)
{
	for (auto& button : m_buttons)
	{
		// Reset colours if you click again
		button.m_buttonShape.setFillColor(sf::Color::Blue);
	}

	for (auto& button : m_buttons)
	{
		sf::Vector2f topLeft = button.m_buttonShape.getPosition();
		sf::Vector2f size = button.m_buttonShape.getSize();

		if (checkIfAreaClicked(t_mousePos, topLeft, size) == true)
		{
			m_selectedPath = button.midiPath;
			m_selectedName = button.songName;
			std::cerr << "Selected [SONG] Path is: " << m_selectedPath << std::endl;
			b_isSongChosen = true;

			// Turn it red to show it has been clicked
			button.m_buttonShape.setFillColor(sf::Color::Red);
			return SongClickResult::SongSelected;
		}

		// Preview Sprite Button
		sf::Vector2f topLeftPreview = button.m_musicNoteSprite.getPosition();
		sf::Vector2f sizePreview = sf::Vector2f{
												button.m_musicNoteSprite.getGlobalBounds().size.x,
												button.m_musicNoteSprite.getGlobalBounds().size.y };

		if (checkIfAreaClicked(t_mousePos, topLeftPreview, sizePreview) == true)
		{
			std::cerr << "Preview clicked for: " << button.midiPath << std::endl;
			m_previewPath = button.midiPath;
			return SongClickResult::PreviewClicked;
		}
	}

	// Begin button
	if (b_isSongChosen == true)
	{
		sf::Vector2f beginTopLeft = m_beginButton.getPosition();
		sf::Vector2f beginSize = m_beginButton.getSize();

		if (checkIfAreaClicked(t_mousePos, beginTopLeft, beginSize) == true)
		{
			std::cerr << "Begin button with song: " << m_selectedPath << std::endl;
			return SongClickResult::BeginClicked;
		}
	}

	// Preview Mode
	sf::Vector2f beginTopLeft = m_previewButton.getPosition();
	sf::Vector2f beginSize = m_previewButton.getSize();

	if (checkIfAreaClicked(t_mousePos, beginTopLeft, beginSize) == true)
	{
		return SongClickResult::PreviewDemoClicked;
	}

	// Ghost Mode
	sf::Vector2f ghostTopLeft = m_ghostButton.getPosition();
	sf::Vector2f ghostSize = m_ghostButton.getSize();

	if (checkIfAreaClicked(t_mousePos, ghostTopLeft, ghostSize) == true)
	{
		return SongClickResult::GhostClicked;
	}

	// Custom
	sf::Vector2f loadTopLeft = m_loadCustomMidiButton.getPosition();
	sf::Vector2f loadSize = m_loadCustomMidiButton.getSize();

	if (checkIfAreaClicked(t_mousePos, loadTopLeft, loadSize) == true)
	{
		std::string customMidi = m_loadMidiField.getString();
		if (!customMidi.empty())
		{
			m_selectedPath = "ASSETS\\AUDIO\\MUSIC\\SavedMidi\\" + customMidi + ".mid";
			m_selectedName = customMidi; 
			b_isSongChosen = true;

			std::cerr << "Custom Midi loaded: " << customMidi << std::endl;
			return SongClickResult::CustomLoadClicked;
		}
	}

	// MCI
	sf::Vector2f customMCITopLeft = m_loadCustomMCISprite.getPosition();
	sf::Vector2f customMCISize = sf::Vector2f{
												m_loadCustomMCISprite.getGlobalBounds().size.x,
												m_loadCustomMCISprite.getGlobalBounds().size.y };

	if (checkIfAreaClicked(t_mousePos, customMCITopLeft, customMCISize) == true)
	{
		std::cerr << "Preview clicked for: " << m_selectedPath << std::endl;
		m_previewPath = m_selectedPath;
		return SongClickResult::PreviewClicked;

		std::string customMidi = m_loadMidiField.getString();
		if (!customMidi.empty())
		{
			std::cerr << "You must load a midi first!" << std::endl;
		}
	}

	return SongClickResult::None;
}

bool SongSelect::returnClick(sf::Vector2f t_mousePos)
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

bool SongSelect::checkIfAreaClicked(sf::Vector2f t_mousePos, sf::Vector2f t_topLeft, sf::Vector2f t_size)
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

void SongSelect::handleEvent(sf::Event& t_event)
{
	m_loadMidiField.handleEvent(t_event);
}

void SongSelect::update(float t_deltaTime)
{
	m_loadMidiField.update(t_deltaTime);
}

std::string SongSelect::getMidiPathString()
{
	return m_selectedPath;
}

std::string SongSelect::getSongName()
{
	return m_selectedName;
}

std::string SongSelect::getPreviewPathString()
{
	return m_previewPath;
}

std::string SongSelect::DifficultyToString(SONGDIFFICULTIES t_difficulty)
{
	switch (t_difficulty)
	{
		case SONGDIFFICULTIES::EASY:
		{
			return "Easy";
		}
		case SONGDIFFICULTIES::MEDIUM:
		{
			return "Medium";
		}
		case SONGDIFFICULTIES::HARD:
		{
			return "Hard";
		}
		default:
		{
			return "Unknown";
		}
	}
}

void SongSelect::togglePreviewColour(bool t_bool)
{
	bool clickResult = t_bool;

	if (clickResult == true)
	{
		m_previewButton.setFillColor(c_buttonActive);
	}
	else
	{
		m_previewButton.setFillColor(c_buttonInactive);
	}
}

void SongSelect::toggleGhostColour(bool t_bool)
{
	bool clickResult = t_bool;

	if (clickResult == true)
	{
		m_ghostButton.setFillColor(c_buttonActive);
	}
	else
	{
		m_ghostButton.setFillColor(c_buttonInactive);
	}
}


