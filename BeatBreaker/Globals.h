#pragma once

// Screen Width + Height
const int SCREEN_WIDTH = 1280U;
const int SCREEN_HEIGHT = 720U;
const sf::Vector2f SCREEN_CENTRE = sf::Vector2f(1280 / 2.0f, 720 / 2.0f);


// Grid
const float GRID_SPACE_SIZE = 100.0f;
const int TRACK_COUNT = 12;

// Extra 
const float TRACK_SIZE_X = 1200.0f;

// Padding
const float paddingX = 40.0f;
const float paddingY = 10.0f;

//// Midi Event flags
//enum EventType : uint8_t
//{
//	metaEvent = 0xFF,
//
//	// Meta types:
//	tempo = 0x51,
//	timeSignature = 0x58,
//	keySignature = 0x59,
//	trackName = 0x03,
//	instrumentName = 0x04, // TO DO - MIGHT BE BROKEN SINCE IT CAN'T FIND ONE FROM OUR CURRENT MIDI?
//
//	// Status bytes (higher than 80)
//	statusByte = 0x80,
//
//	// Message type mask 
//	// Keep only the upper 4 bits (message type) and ignore lower 4 bits (channel)
//	messageTypeMask = 0xF0,
//
//	noteOff = 0x80,
//	noteOn = 0x90,
//	afterTouch = 0xA0,
//	controlChange = 0xB0,
//	programChange = 0xC0,
//	channelAftertouch = 0xD0,
//	pitchBend = 0xE0,
//	systemExclusive = 0xF0
//};
