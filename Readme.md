### Schedule Timeline

/////////////////////////////////////
PHASE ONE
(28/09/2025 -> Project proposal)
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
PHASE TWO 
(11/11/2025 -> Proposal approved)
/////////////////////////////////////
### File Structure setup (SFML)
- [x] Basic SFML shapes displaying, text, sprites, textures working.
- [x] Test Main Menu that contains different buttons to load different scenes for future testing.
- [x] Basic Gameplay test scene that loads in different sf::rectangle shapes to see if the different game states are changing when changing scenes.
- [x] Started structure for generating different Block Sections with a Block and BlockGeneration classes.

/////////////////////////////////////
### MIDI Parser and saving MIDI data
- [] MIDI Parser testing with a basic MIDI file containing a test channel to capture from.
- [] Simple saving specific MIDI data (BPM, Channel names) to a .TXT file.
- [] Simple loading saved MIDI data from a .TXT file.
- [x] Create simple MIDI track to be imported (easy to parse, obvious timings, 4/4).

/////////////////////////////////////
### Gameplay
- [] Screen Scrolling
- [x] Simple Character Controller with movement, collision and sf::rectangle to represent different collisons.
- [x] Different hitboxes for detecting collision with general objects, 
- [] Different colours on the base sf::rectangle shape to represent states (Idle, Moving, Breaking, Falling, Death).
- [] Simple HUD with UI text for displaying gameplay info (scores, hit result, health).
- [] Depth metre that runs along the side of the stage to show how far the player has travelled.
	(useful for checking if the screen is scrolling correctly).
- [] Timeline scroll with music's BPM (simple only movement no Block Clearing).
- [x] Difficulty options (basic).
- [] Difficulty selection from Options Menu.

/////////////////////////////////////
### Main Menu
- [x] Select different buttons to enter different test game states
 (Start game, Random Gen, Input Test, MIDI Parse, Character Controller, Options Menu, Exit)

/////////////////////////////////////
### Options Menu
- [x] Toggle different sound type's volumes (MUSIC, SFX).
- [x] Test different sound types with two testing buttons (MUSIC, SFX).
- [x] Toggle the FPS display text while the program is running.
- [x] Save these preferences to a .TXT file.
- [x] Load these preferences from a .TXT file.
- [x] Return button to go back to the Main Menu scene and persist data.

/////////////////////////////////////
### Sound Manager
- [x] Pool sounds in a vector that we reuse when calling to play a sound.
- [x] Unordered map to store the sf::sound's name and the actual sf::soundbuffer it uses.
- [x] Different sound types that all sounds are assigned to (MUSIC, SFX).
	- [x] Set volume based on sound type. (Options Menu controls volume amount)
- [] Randomise pitch function that randomises a sound's pitch within a range. (used for Block Breaking SFX)

/////////////////////////////////////
### Collision Manager
- [x] Using an unordered map so we call check what layer is the sf::rectangle shape is attatched to.
- [x] Depending on the layer ("WALL", "BLOCK") we will return a bool to say if they are colliding or not:
  (i.e. if the player is colliding with the Wall Shape with a "WALL" tag, then it not pass through it).
- [] Create more tags for different object layer types ("END_FLOOR", "BARRIER", "HEALTH", "EXTRA_LIFE", etc.

/////////////////////////////////////
### Block Generation
- [x]Generate using the Block class and passing it's attributes to be read (colour, position, type, etc). 
- [x] Difficulty influences how patterns are generation:
 ("EASY", "MEDIUM", "HARD" -> Scales the percentage of Health, Barrier blocks).

/////////////////////////////////////
### UI
- [x] Buttons created for Menus (Main Menu, Option Menu).
- [x] HUD object created that persists through different scenes (FPS display currently implemented).
- [x] Setup shapes/vectors for Beat Marker HUD elements :
  (Beat Markers Quarters Left, Beat Markers Quarters Right, Beat Marker Whole Note)

/////////////////////////////////////
### Structure
- [x] Sorted every .h and .cpp into their own filters for easier navigationa/organisation.
- [x] Created folders for the different sounds:
  (UI, MUSIC, PLAYER, GAMEPLAY), save data (Block Gen, High scores, MIDI saves, options preferences),
- [x] Downloaded SFX sounds and loaded them into the game on game start.

/////////////////////////////////////
### Presentation
= [x] Basic layout with what topics will be discussed.
- [x] Specific code snippeds to be used for a slide (MIDI Parsing, Sound Manager, etc)
= [x] Created different pie charts to represent how much of the core has been worked on.
- [x] Presentation polish

/////////////////////////////////////
PHASE THREE 
(28/11/2025 -> Base code implemented to work on core)
/////////////////////////////////////


/////////////////////////////////////
PHASE FOUR 
(01/01/2026
/////////////////////////////////////

/////////////////////////////////////
PHASE FIVE 
(01/02/2026
/////////////////////////////////////