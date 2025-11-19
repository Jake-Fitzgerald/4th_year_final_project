### Schedule Timeline

/////////////////////////////////////
### Documentation
- [x] Proposal 1 - Rhythm Batter
	- [x] Planning
	- [x] Research
	- [x] Final Documentation submited
	
- [x] Proposal 2 - Beat Breaker
	- [x] Planning
	- [x] Research
	- [x] Final Documentation submited
	
/////////////////////////////////////
### Research

	Music technology
	
		MIDI (C++ Parser)
		- [x] Reading from MIDI
		- [x] Writing to MIDI
		
		Conductor (Estimate using .WAV)
		- [x] Calculating the time signature
	
	Input detection
	- [x] Joystick detection (SFML)

/////////////////////////////////////
### File Structure setup (SFML)
- [x] Basic SFML shapes displaying, text, sprites, textures working.
- [x] Test Main Menu that contains different buttons to load different scenes for future testing.
- [x] Basic Gameplay test scene that loads in different sf::rectangle shapes to see if the different game states are changing when changing scenes.
- [x] Started structure for generating different Block Sections with a Block and BlockGeneration classes.

/////////////////////////////////////
### MIDI Parser and saving MIDI data
- [x] MIDI Parser testing with a basic MIDI file containing a test channel to capture from.
- [x] Simple saving specific MIDI data (BPM, Channel names) to a .TXT file.
- [x] Simple loading saved MIDI data from a .TXT file.
- [x] Create simple MIDI track to be imported (easy to parse, obvious timings, 4/4).

/////////////////////////////////////
### Gampeplay
- [] Screen Scrolling
- [] Simple Character Controller with movement, collision and sf::rectangle to represent different collisons.
- [] Different colours on the base sf::rectangle shape to represent states (Idle, Moving, Breaking, Falling, Death).
- [] Simple HUD with UI text for displaying gameplay info (scores, hit result, health).
- [] Depth metre that runs along the side of the stage to show how far the player has travelled.
	(useful for checking if the screen is scrolling correctly).
- [] Timeline scroll with music's BPM (simple only movement no Block Clearing).


/////////////////////////////////////
### Presentation
= [x] Basic layout with what topics will be discussed.
- [] Specific code snippeds to ne used for a slide (MIDI Parsing, MIDI data saving/loading, etc)
- [] Presentation polish


