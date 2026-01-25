#pragma once
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Globals.h"


/*
	List of drum parts: Kick, Snare, Hit hat, Cymbol 1, Cymbol 2, Tom 1, Tom2

*/
class DrumVisualiser
{
public:
	void setupDrums();

	void renderDrums(sf::RenderWindow& t_window);

private:

};

