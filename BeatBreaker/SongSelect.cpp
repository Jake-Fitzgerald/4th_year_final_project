#include "SongSelect.h"

SongSelect::SongSelect(std::shared_ptr<const sf::Font> font) : m_font(font), m_beginText(*font)
{
	b_isSongChosen = false;
}


void SongSelect::setupPathStrings()
{
	m_pathVector =
	{
		{"C Scale", "ASSETS\\AUDIO\\MUSIC\\C_Scale.mid", SONGDIFFICULTIES::EASY},
		{"Major / Minor Chords", "ASSETS\\AUDIO\\MUSIC\\Major_and_Minor_Chords.mid", SONGDIFFICULTIES::MEDIUM},
		{"Hard Song", "ASSETS\\AUDIO\\MUSIC\\Full_MIDI_Range.mid", SONGDIFFICULTIES::HARD},
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
		button.m_buttonShape.setPosition(sf::Vector2f{ paddingX , paddingY + i * m_spacing });
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
																button.m_buttonShape.getPosition().x + m_difficultyTextSpacing + 400.0f,
																button.m_buttonShape.getPosition().y + 10.f });
		button.m_musicNoteSprite.setScale(sf::Vector2f{ 0.6f, 0.6f });

		button.midiPath = m_pathVector[i].path;
		m_buttons.push_back(button);
	}

	setupBeginButton();
}

void SongSelect::setupBeginButton()
{
	// Position the Begin button below the last song row
	float beginY = paddingY + m_pathsCount * m_spacing + 20.0f;

	m_beginButton.setSize(sf::Vector2f{ 200.0f, 50.0f });
	m_beginButton.setPosition(sf::Vector2f{ paddingX + 900.0f, beginY + 300.0f});
	m_beginButton.setFillColor(sf::Color(100, 100, 100));
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

void SongSelect::render(sf::RenderWindow& t_window)
{
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
}


SongClickResult SongSelect::mouseClick(sf::Vector2f t_mousePos)
{
	// Songs
	for (auto& button : m_buttons)
	{
		// Reset colours if you click again
		button.m_buttonShape.setFillColor(sf::Color::Blue);

		// Song Button
		sf::Vector2f topLeft = button.m_buttonShape.getPosition();
		sf::Vector2f size = button.m_buttonShape.getSize();

		if (checkIfAreaClicked(t_mousePos, topLeft, size) == true)
		{
			m_selectedPath = button.midiPath;
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

	return SongClickResult::None;
}

bool SongSelect::returnClick(sf::Vector2f t_mousePos)
{
	// Stop any alias if it's currently playing
	//stopMidiMCIPreview();
	

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

std::string SongSelect::getMidiPathString()
{
	return m_selectedPath;
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


