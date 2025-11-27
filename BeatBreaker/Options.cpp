#include "Options.h"

Options::Options(const sf::Font& font)
	: m_OptionsText(font), m_musicText(font), m_sfxText(font), m_fpsText(font), m_returnText(font), m_saveText(font), m_loadText(font)
{
	setupOptionsTexts();
	setupOptionsButtons();
	// Sprites
	setupOptionsTextures();
}

void Options::setupOptionsTexts()
{
	// Options (title)
	m_OptionsText.setString("OPTIONS");
	m_OptionsText.setPosition(m_optionsPos);
	m_OptionsText.setFillColor(sf::Color::White);
	m_OptionsText.setOutlineColor(sf::Color::Black);
	m_OptionsText.setOutlineThickness(2.0f);
	m_OptionsText.setCharacterSize(50U);
	// Music Text
	m_musicText.setString("Music");
	m_musicText.setPosition(m_musicPos);
	m_musicText.setFillColor(sf::Color::White);
	m_musicText.setOutlineColor(sf::Color::Black);
	m_musicText.setOutlineThickness(2.0f);
	m_musicText.setCharacterSize(30U);
	// SFX Text
	m_sfxText.setString("SFX");
	m_sfxText.setPosition(m_sfxPos);
	m_sfxText.setFillColor(sf::Color::White);
	m_sfxText.setOutlineColor(sf::Color::Black);
	m_sfxText.setOutlineThickness(2.0f);
	m_sfxText.setCharacterSize(30U);
	// FPS Text
	m_fpsText.setString("FPS Display");
	m_fpsText.setPosition(m_fpsPos);
	m_fpsText.setFillColor(sf::Color::White);
	m_fpsText.setOutlineColor(sf::Color::Black);
	m_fpsText.setOutlineThickness(2.0f);
	m_fpsText.setCharacterSize(30U);
	// Return Text
	m_returnText.setString("RETURN");
	m_returnText.setPosition(m_returnPos);
	m_returnText.setFillColor(sf::Color::White);
	m_returnText.setOutlineColor(sf::Color::Black);
	m_returnText.setOutlineThickness(2.0f);
	m_returnText.setCharacterSize(30U);
	// Save Text
	m_saveText.setString("Save");
	m_saveText.setPosition(m_savePos);
	m_saveText.setFillColor(sf::Color::White);
	m_saveText.setOutlineColor(sf::Color::Black);
	m_saveText.setOutlineThickness(2.0f);
	m_saveText.setCharacterSize(30U);
	// Load Text
	m_loadText.setString("Load");
	m_loadText.setPosition(m_loadPos);
	m_loadText.setFillColor(sf::Color::White);
	m_loadText.setOutlineColor(sf::Color::Black);
	m_loadText.setOutlineThickness(2.0f);
	m_loadText.setCharacterSize(30U);

}

void Options::setupOptionsButtons()
{
	// Music
	m_musicButton.setFillColor(sf::Color::Blue);
	m_musicButton.setSize(m_buttonScale);
	m_musicButton.setPosition(m_musicPos);
	// Music Test 
	m_musicTestButton.setFillColor(sf::Color::White);
	m_musicTestButton.setSize(m_buttonTestScale);
	m_musicTestButton.setPosition(m_musicTestPos);

	// SFX
	m_sfxButton.setFillColor(sf::Color::Blue);
	m_sfxButton.setSize(m_buttonScale);
	m_sfxButton.setPosition(m_sfxPos);
	// SFX Test 
	m_sfxTestButton.setFillColor(sf::Color::White);
	m_sfxTestButton.setSize(m_buttonTestScale);
	m_sfxTestButton.setPosition(m_sfxTestPos);

	// FPS
	m_fpsButton.setFillColor(sf::Color::Blue);
	m_fpsButton.setSize(m_buttonScale);
	m_fpsButton.setPosition(m_fpsPos);
	// Return
	m_returnButton.setFillColor(sf::Color::Blue);
	m_returnButton.setSize(m_buttonScale);
	m_returnButton.setPosition(m_returnPos);
	// Save
	m_saveButton.setFillColor(sf::Color::Magenta);
	m_saveButton.setSize(m_buttonSmallScale);
	m_saveButton.setPosition(m_savePos);
	// Load
	m_loadButton.setFillColor(sf::Color::Magenta);
	m_loadButton.setSize(m_buttonSmallScale);
	m_loadButton.setPosition(m_loadPos);
}

void Options::renderOptions(sf::RenderWindow& t_window)
{
	// Background
	t_window.draw(m_bgSprite);

	// BUTTONS
	t_window.draw(m_musicButton);
	t_window.draw(m_musicTestButton);
	t_window.draw(m_sfxButton);
	t_window.draw(m_sfxTestButton);
	t_window.draw(m_fpsButton);
	t_window.draw(m_returnButton);
	t_window.draw(m_saveButton);
	t_window.draw(m_loadButton);

	// TEXTS
	// Title
	t_window.draw(m_OptionsText);
	// Audio
	t_window.draw(m_musicText);
	t_window.draw(m_sfxText);
	// Utilities
	t_window.draw(m_fpsText);
	t_window.draw(m_returnText);
	t_window.draw(m_saveText);
	t_window.draw(m_loadText);

	// Sprites
	t_window.draw(m_musicNoteSprite);
	t_window.draw(m_sfxNoteSprite);
}

bool Options::handleMouseClick(sf::Vector2f t_mousePos, HUD& t_hud, SoundManager& t_soundManager)
{
	// Music
	if (m_musicButton.getGlobalBounds().contains(t_mousePos))
	{
		if (m_currentMusicVolume > 0.0f)
		{
			m_currentMusicVolume = 0.0f;
			m_musicButton.setFillColor(sf::Color::Red);
		}
		else
		{
			m_currentMusicVolume = 100.0f;
			m_musicButton.setFillColor(sf::Color::Blue);
		}

		t_soundManager.setTypeVolume(SoundType::MUSIC, m_currentMusicVolume);
	}
	// Music Test
	if (m_musicTestButton.getGlobalBounds().contains(t_mousePos))
	{
		t_soundManager.play("ui_confirm", SoundType::MUSIC);
	}
	// SFX
	if (m_sfxButton.getGlobalBounds().contains(t_mousePos))
	{
		if (m_currentSFXVolume > 0.0f)
		{
			m_currentSFXVolume = 0.0f;
			changeButtonColours();
		}
		else
		{
			m_currentSFXVolume = 100.0f;
			changeButtonColours();
		}

		t_soundManager.setTypeVolume(SoundType::SFX, m_currentSFXVolume);
	}
	// SFX Test
	if (m_sfxTestButton.getGlobalBounds().contains(t_mousePos))
	{
		t_soundManager.play("ui_cancel", SoundType::SFX);
	}
	// FPS
	if (m_fpsButton.getGlobalBounds().contains(t_mousePos))
	{
		t_hud.setFPSBool();
	}
	// Return
	if (m_returnButton.getGlobalBounds().contains(t_mousePos))
	{
		// Go back to the main menu bool
		return true;
	}
	// Save
	if (m_saveButton.getGlobalBounds().contains(t_mousePos))
	{
		savePreferences();
	}
	// Load
	if (m_loadButton.getGlobalBounds().contains(t_mousePos))
	{
		loadPreferences(t_soundManager);
	}

	return false;
}

void Options::getSoundTypes()
{
	// to do
	// get the sound manager again?
}

void Options::savePreferences()
{
	std::ofstream MyFile("ASSETS/SAVEDATA/Preferences_Saves/preferences_saves.txt");

	if (!MyFile)
	{
		std::cerr << "Couldn't open the save file for options" << std::endl;
		return;
	}

	// Save the floats line by line
	MyFile << "Music_volume=" << m_currentMusicVolume << "\n";
	MyFile << "SFX_volume=" << m_currentSFXVolume << "\n";

	MyFile.close();
}

void Options::loadPreferences(SoundManager& t_soundManager)
{
	// Read from the text file
	std::ifstream MyFile("ASSETS/SAVEDATA/Preferences_Saves/preferences_saves.txt");

	if (!MyFile)
	{
		std::cerr << "Couldn't open the save file for options" << std::endl;
		return;
	}

	std::string currentLine;
	// Use a while loop together with the getline() function to read the file line by line
	while (std::getline(MyFile, currentLine))
	{
		// Print out what's in the file
		std::cerr << currentLine << std::endl;

		int pos = -1;

		// Find '=' using a normal for loop
		for (int i = 0; i < currentLine.length(); i++)
		{
			if (currentLine[i] == '=')
			{
				pos = i;
				break;
			}
		}

		// Skip any bad lines
		if (pos == -1)
		{
			continue; 
		}
			

		// Split key and value (before = is name, after = is float)
		std::string name = currentLine.substr(0, pos);
		std::string amount = currentLine.substr(pos + 1);

		// Convert the string to a number
		float value = std::stof(amount);

		// Store values
		if (name == "Music_volume")
		{
			m_currentMusicVolume = value;
			std::cerr << "Music volume: " << m_currentMusicVolume << std::endl;
		}
		else if (name == "SFX_volume")
		{
			m_currentSFXVolume = value;
			std::cerr << "SFX volume: " << m_currentSFXVolume << std::endl;
		}
	}
	
	// Update the sound manager
	t_soundManager.setTypeVolume(SoundType::MUSIC, m_currentMusicVolume);
	t_soundManager.setTypeVolume(SoundType::SFX, m_currentSFXVolume);

	// Change buttons
	changeButtonColours();

	// Close the file
	MyFile.close();
}

void Options::changeButtonColours()
{
	if (m_currentMusicVolume == 0.0f)
	{
		m_musicButton.setFillColor(sf::Color::Red);
	}
	else
	{
		m_musicButton.setFillColor(sf::Color::Blue);
	}

	if (m_currentSFXVolume == 0.0f)
	{
		m_sfxButton.setFillColor(sf::Color::Red);
	}
	else
	{
		m_sfxButton.setFillColor(sf::Color::Blue);
	}
}

void Options::setupOptionsTextures()
{
	// Music Note
	if (!m_musicNoteTex.loadFromFile("ASSETS\\IMAGES\\UI\\sound_test_MUSIC.png"))
	{
		std::cerr << "problem loading options music texture" << std::endl;
	}

	m_musicNoteSprite.setTexture(m_musicNoteTex, true);
	m_musicNoteSprite.setPosition(m_musicTestPos);
	m_musicNoteSprite.setScale(sf::Vector2f{ 0.8f, 0.8f });

	// SFX Note
	if (!m_sfxNoteTex.loadFromFile("ASSETS\\IMAGES\\UI\\sound_test_SFX.png"))
	{
		std::cerr << "problem loading options sfx texture" << std::endl;
	}

	m_sfxNoteSprite.setTexture(m_sfxNoteTex, true);
	m_sfxNoteSprite.setPosition(m_sfxTestPos);
	m_sfxNoteSprite.setScale(sf::Vector2f{ 0.8f, 0.8f });

	// Background
	if (!m_bgTex.loadFromFile("ASSETS\\IMAGES\\Backgrounds\\test_BG_1.png"))
	{
		std::cerr << "problem loading options background texture" << std::endl;
	}

	m_bgSprite.setTexture(m_bgTex, true);
	m_bgSprite.setPosition(sf::Vector2f{0.0f, 0.0f});
	//m_bgSprite.setScale(sf::Vector2f{ 0.8f, 0.8f });
}


