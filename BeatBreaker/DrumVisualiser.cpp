#include "DrumVisualiser.h"

DrumVisualiser::DrumVisualiser(std::shared_ptr<const sf::Font> font, SoundManager& t_soundManager) :
	m_font(font),
	m_soundManager(&t_soundManager),
	m_kickSprite(m_kickTexture),
	m_snareSprite(m_snareTexture),
	m_floorTomSprite(m_floorTomTexture),
	m_TomTom1Sprite(m_TomTom1Texture),
	m_TomTom2Sprite(m_TomTom2Texture),
	m_crash1Sprite(m_crash1Texture),
	m_crash2Sprite(m_crash2Texture),
	m_hiHatSprite(m_hiHatTexture),
	m_clapSprite(m_clapTexture)
	
{
	setupDrums();
}

void DrumVisualiser::setupDrums()
{
	setupDrumSprites();
	setupDrumSounds();
	
	m_kickPiece.shape.setFillColor(m_drumHitboxColour);
	m_kickPiece.shape.setPosition(m_kickHitboxPos);
	m_kickPiece.shape.setSize(m_kickHitboxSize);
	m_kickPiece.b_isPressed = false;
	m_kickPiece.pieceName = "Kick";

	m_snarePiece.shape.setFillColor(m_drumHitboxColour);
	m_snarePiece.shape.setPosition(m_snareHitboxPos);
	m_snarePiece.shape.setSize(m_drumHitboxSize);
	m_snarePiece.b_isPressed = false;
	m_snarePiece.pieceName = "Snare";
	
	m_Crash1Piece.shape.setFillColor(m_drumHitboxColour);
	m_Crash1Piece.shape.setPosition(m_crash1HitboxPos);
	m_Crash1Piece.shape.setSize(m_drumHitboxSize);
	m_Crash1Piece.b_isPressed = false;
	m_Crash1Piece.pieceName = "Crash1";

	m_Crash2Piece.shape.setFillColor(m_drumHitboxColour);
	m_Crash2Piece.shape.setPosition(m_crash2HitboxPos);
	m_Crash2Piece.shape.setSize(m_drumHitboxSize);
	m_Crash2Piece.b_isPressed = false;
	m_Crash2Piece.pieceName = "Crash2";

	m_FloorTomPiece.shape.setFillColor(m_drumHitboxColour);
	m_FloorTomPiece.shape.setPosition(m_floorTomHitboxPos);
	m_FloorTomPiece.shape.setSize(m_drumHitboxSize);
	m_FloorTomPiece.b_isPressed = false;
	m_FloorTomPiece.pieceName = "FloorTom";

	m_Tom1Piece.shape.setFillColor(m_drumHitboxColour);
	m_Tom1Piece.shape.setPosition(m_tom1HitboxPos);
	m_Tom1Piece.shape.setSize(m_drumHitboxSize);
	m_Tom1Piece.b_isPressed = false;
	m_Tom1Piece.pieceName = "Tom1";

	m_Tom2Piece.shape.setFillColor(m_drumHitboxColour);
	m_Tom2Piece.shape.setPosition(m_tom2HitboxPos);
	m_Tom2Piece.shape.setSize(m_drumHitboxSize);
	m_Tom2Piece.b_isPressed = false;
	m_Tom2Piece.pieceName = "Tom2";

	m_HiHatPiece.shape.setFillColor(m_drumHitboxColour);
	m_HiHatPiece.shape.setPosition(m_hiHatHitboxPos);
	m_HiHatPiece.shape.setSize(m_drumHitboxSize);
	m_HiHatPiece.b_isPressed = false;
	m_HiHatPiece.pieceName = "HiHat";

	m_clapPiece.shape.setFillColor(m_drumHitboxColour);
	m_clapPiece.shape.setPosition(m_clapHitboxPos);
	m_clapPiece.shape.setSize(m_drumHitboxSize);
	m_clapPiece.b_isPressed = false;
	m_clapPiece.pieceName = "Clap";

	m_drums.push_back(m_Tom1Piece);
	m_drums.push_back(m_Tom2Piece);
	m_drums.push_back(m_snarePiece);
	m_drums.push_back(m_FloorTomPiece);
	m_drums.push_back(m_HiHatPiece);
	m_drums.push_back(m_Crash1Piece);
	m_drums.push_back(m_Crash2Piece);
	m_drums.push_back(m_kickPiece);
	m_drums.push_back(m_clapPiece);
}

void DrumVisualiser::setupDrumSprites()
{
	// Kick
	if (!m_kickTexture.loadFromFile("ASSETS\\IMAGES\\Drum_Pieces\\Kick.png"))
	{
		std::cout << "problem loading Kick image" << std::endl;
	}
	m_kickSprite.setTexture(m_kickTexture, true);
	m_kickSprite.setScale(sf::Vector2f(1.0f, 1.0f));
	m_kickSprite.setPosition(sf::Vector2f{ m_drumPositions.x, m_drumPositions.y });

	// Snare
	if (!m_snareTexture.loadFromFile("ASSETS\\IMAGES\\Drum_Pieces\\Snare.png"))
	{
		std::cout << "problem loading Snare image" << std::endl;
	}
	m_snareSprite.setTexture(m_snareTexture, true);
	m_snareSprite.setScale(sf::Vector2f(1.0f, 1.0f));
	m_snareSprite.setPosition(sf::Vector2f{ m_drumPositions.x, m_drumPositions.y });

	// Floor Tom
	if (!m_floorTomTexture.loadFromFile("ASSETS\\IMAGES\\Drum_Pieces\\Floor Tom.png"))
	{
		std::cout << "problem loading Floor Tom image" << std::endl;
	}
	m_floorTomSprite.setTexture(m_floorTomTexture, true);
	m_floorTomSprite.setScale(sf::Vector2f(1.0f, 1.0f));
	m_floorTomSprite.setPosition(sf::Vector2f{ m_drumPositions.x, m_drumPositions.y });

	// Crash 1
	if (!m_crash1Texture.loadFromFile("ASSETS\\IMAGES\\Drum_Pieces\\Crash 1.png"))
	{
		std::cout << "problem loading Crash image" << std::endl;
	}
	m_crash1Sprite.setTexture(m_crash1Texture, true);
	m_crash1Sprite.setScale(sf::Vector2f(1.0f, 1.0f));
	m_crash1Sprite.setPosition(sf::Vector2f{ m_drumPositions.x, m_drumPositions.y });

	// Crash 2
	if (!m_crash2Texture.loadFromFile("ASSETS\\IMAGES\\Drum_Pieces\\Crash 2.png"))
	{
		std::cout << "problem loading Crash image" << std::endl;
	}
	m_crash2Sprite.setTexture(m_crash2Texture, true);
	m_crash2Sprite.setScale(sf::Vector2f(1.0f, 1.0f));
	m_crash2Sprite.setPosition(sf::Vector2f{ m_drumPositions.x, m_drumPositions.y });

	// Hi Hat
	if (!m_hiHatTexture.loadFromFile("ASSETS\\IMAGES\\Drum_Pieces\\Hi Hat.png"))
	{
		std::cout << "problem loading Hi Hat image" << std::endl;
	}
	m_hiHatSprite.setTexture(m_hiHatTexture, true);
	m_hiHatSprite.setScale(sf::Vector2f(1.0f, 1.0f));
	m_hiHatSprite.setPosition(sf::Vector2f{ m_drumPositions.x, m_drumPositions.y });

	// Tom Tom 1
	if (!m_TomTom1Texture.loadFromFile("ASSETS\\IMAGES\\Drum_Pieces\\TomTom 1.png"))
	{
		std::cout << "problem loading Tom Tom 1 image" << std::endl;
	}
	m_TomTom1Sprite.setTexture(m_TomTom1Texture, true);
	m_TomTom1Sprite.setScale(sf::Vector2f(1.0f, 1.0f));
	m_TomTom1Sprite.setPosition(sf::Vector2f{ m_drumPositions.x, m_drumPositions.y });

	// Tom Tom 2
	if (!m_TomTom2Texture.loadFromFile("ASSETS\\IMAGES\\Drum_Pieces\\TomTom 2.png"))
	{
		std::cout << "problem loading Tom Tom 2 image" << std::endl;
	}
	m_TomTom2Sprite.setTexture(m_TomTom2Texture, true);
	m_TomTom2Sprite.setScale(sf::Vector2f(1.0f, 1.0f));
	m_TomTom2Sprite.setPosition(sf::Vector2f{ m_drumPositions.x, m_drumPositions.y });

	// Clap
	if (!m_clapTexture.loadFromFile("ASSETS\\IMAGES\\Drum_Pieces\\Clap.png"))
	{
		std::cout << "problem loading Clap image" << std::endl;
	}
	m_clapSprite.setTexture(m_clapTexture, true);
	m_clapSprite.setScale(sf::Vector2f(1.0f, 1.0f));
	m_clapSprite.setPosition(sf::Vector2f{ m_drumPositions.x, m_drumPositions.y });

	// Add to vector (back to front like in photoshop)
	m_drumSprites.push_back(&m_TomTom1Sprite);
	m_drumSprites.push_back(&m_TomTom2Sprite);
	m_drumSprites.push_back(&m_snareSprite);
	m_drumSprites.push_back(&m_floorTomSprite);
	m_drumSprites.push_back(&m_crash2Sprite);
	m_drumSprites.push_back(&m_crash1Sprite);
	m_drumSprites.push_back(&m_hiHatSprite);
	m_drumSprites.push_back(&m_kickSprite);
	m_drumSprites.push_back(&m_clapSprite);

	// Centre origins
	for (int i = 0; i < m_drumSprites.size(); i++)
	{
		sf::FloatRect spriteSize = m_drumSprites.at(i)->getLocalBounds();
		m_drumSprites.at(i)->setOrigin(sf::Vector2f{ spriteSize.size.x / 2.0f, spriteSize.size.y / 2.0f });
	}
}

void DrumVisualiser::setupDrumSounds()
{
	std::string kickPath = "ASSETS\\AUDIO\\Drums\\Kick.WAV";
	m_soundManager->loadBuffer("Kick", kickPath, SoundType::MUSIC);

	std::string snarePath = "ASSETS\\AUDIO\\Drums\\Snare.WAV";
	m_soundManager->loadBuffer("Snare", snarePath, SoundType::MUSIC);

	std::string crash1Path = "ASSETS\\AUDIO\\Drums\\Crash1.WAV";
	m_soundManager->loadBuffer("Crash1", crash1Path, SoundType::MUSIC);

	std::string crash2Path = "ASSETS\\AUDIO\\Drums\\Crash2.WAV";
	m_soundManager->loadBuffer("Crash2", crash2Path, SoundType::MUSIC);

	std::string floorTomPath = "ASSETS\\AUDIO\\Drums\\FloorTom.WAV";
	m_soundManager->loadBuffer("FloorTom", floorTomPath, SoundType::MUSIC);

	std::string tom1Path = "ASSETS\\AUDIO\\Drums\\Tom1.WAV";
	m_soundManager->loadBuffer("Tom1", tom1Path, SoundType::MUSIC);

	std::string tom2Path = "ASSETS\\AUDIO\\Drums\\Tom2.WAV";
	m_soundManager->loadBuffer("Tom2", tom2Path, SoundType::MUSIC);

	std::string hiHatPath = "ASSETS\\AUDIO\\Drums\\HiHat.WAV";
	m_soundManager->loadBuffer("HiHat", hiHatPath, SoundType::MUSIC);

	std::string clapPath = "ASSETS\\AUDIO\\Drums\\Clap.WAV";
	m_soundManager->loadBuffer("Clap", clapPath, SoundType::MUSIC);
}

void DrumVisualiser::renderDrums(sf::RenderWindow& t_window)
{
	for (int i = 0; i < m_drumSprites.size(); i++)
	{
		t_window.draw(*m_drumSprites[i]);
	}

	if (b_isHitboxVis == true)
	{
		for (int i = 0; i < m_drums.size(); i++)
		{
			t_window.draw(m_drums[i].shape);
		}
	}

}



void DrumVisualiser::changeDrumColourOn(int t_trackNumber)
{
	//for (int i = 0; i < m_drumSprites.size(); i++)
	//{
	//	m_drumSprites.at(t_trackNumber)->setColor(m_noteOnColour);
	//	m_drumSprites.at(t_trackNumber)->setScale(sf::Vector2f{ 5.0f, 2.0f });
	//}

	sf::Sprite* sprite = m_drumSprites.at(t_trackNumber);

	sprite->setColor(m_noteOnColour);
	//sprite->setScale(sf::Vector2f{ 50.0f, 2.0f });
}

void DrumVisualiser::changeDrumColourOff(int t_trackNumber)
{
	sf::Sprite* sprite = m_drumSprites.at(t_trackNumber);

	sprite->setColor(m_noteOffColour);
	//sprite->setScale(sf::Vector2f{ 5.0f, 2.0f });
}

void DrumVisualiser::updateIntroAnim(float t_deltaTime)
{
	// Check if intro has played already
	if (b_isIntroFinished == true)
	{
		return;
	}

	if (m_introTimer < m_introDelayAmount)
	{
		m_introTimer += t_deltaTime;
		return;
	}


	// Current piece increment
	m_drumPieceTimerIntro += t_deltaTime;

	if (m_drumPieceIndexIntro < m_drumSprites.size())
	{
		m_drumSprites[m_drumPieceIndexIntro]->setColor(m_noteOnColour);
	}
	//m_drumSprites[m_drumPieceIndexIntro]->setColor(m_noteOnColour);

	if (m_drumPieceTimerIntro >= m_drumPieceDelayIntro)
	{
		m_drumSprites[m_drumPieceIndexIntro]->setColor(m_noteOffColour);

		// Reset timer
		m_drumPieceTimerIntro = 0.0f;   
		m_drumPieceIndexIntro++;       
	}

	// Check if every piece has played once
	if (m_drumPieceIndexIntro >= m_drumSprites.size())
	{
		b_isIntroFinished = true;
	}
}

void DrumVisualiser::handleClick(sf::Vector2f t_mousePos)
{
	for (int i = 0; i < m_drums.size(); i++)
	{
		if (checkIfPieceClicked(t_mousePos, m_drums[i]))
		{
			// Turn on the key visually
			changeDrumColourOn(i);

			// Play the sound
			std::string soundName = m_drums[i].pieceName;
			m_soundManager->play(soundName);

			std::cerr << "Clicked drum piece: " << soundName << std::endl;
			return;
		}

	}
}

bool DrumVisualiser::checkIfPieceClicked(sf::Vector2f t_mousePos, const DrumPiece& t_piece)
{
	sf::Vector2f topLeft = t_piece.shape.getPosition();
	sf::Vector2f size = t_piece.shape.getSize();

	if (t_mousePos.x >= topLeft.x &&
		t_mousePos.x <= topLeft.x + size.x &&
		t_mousePos.y >= topLeft.y &&
		t_mousePos.y <= topLeft.y + size.y)
	{
		return true;
	}
	return false;
}

void DrumVisualiser::toggleHitboxVis()
{
	if (b_isHitboxVis == true)
	{
		b_isHitboxVis = false;
	}
	else
	{
		b_isHitboxVis = true;
	}
}

void DrumVisualiser::drumNoteOn(int t_midiNote)
{
	int index = -1;

	switch (t_midiNote)
	{
		case 48: // Tom1
		{
			index = 0;
			break; 
		}
		case 50: // Tom2
		{
			index = 1;
			break; 
		}
		case 52: // Snare
		{
			index = 2;
			break;
		}
		case 53: // FloorTom
		{
			index = 3;
			break; 
		}
		case 55: // HiHat
		{
			index = 4;
			break; 
		}
		case 57: // Crash1
		{
			index = 5;
			break;
		}
		case 59: // Clap
		{
			index = 8;
			break; 
		}
		case 60: // Kick
		{
			index = 7;
			break; 
		}
		default:
		{
			return;
		}
	}

	changeDrumColourOn(index);
	m_soundManager->play(m_drums[index].pieceName);
}

void DrumVisualiser::drumNoteOff(int t_midiNote)
{
	int index = -1;

	switch (t_midiNote)
	{
		case 48:  // Tom1
		{
			index = 0;
			break;
		}
		case 50: // Tom2
		{
			index = 1;
			break;
		}
		case 52: // Snare
		{
			index = 2;
			break;
		}
		case 53: // FloorTom
		{
			index = 3;
			break;
		}
		case 55: // HiHat
		{
			index = 4;
			break;
		}
		case 57: // Crash1
		{
			index = 5;
			break;
		}
		case 59: // Clap
		{
			index = 8;
			break;
		}
		case 60: // Kick
		{
			index = 7;
			break;
		}
		default:
		{
			return;
		}
	}

	changeDrumColourOff(index);
}
