#pragma once
#include <SFML//Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Globals.h"
#include <iostream>
/*
Displays the recorded data that was collected during the run.
 - Total Depth,
 - Total Time,
 - Total Score,


 Score Calculation: 
 What depth was reached, how many lives were lost (if none then give bonus points), how on beat you were (perfect hits)

 Grab the song's details 
 - Song name
 - Song difficulty
 - Song length (pbTime - total s0ng time to calculate the percentage of the song completed)

*/

class Results
{
public:

private:
	// Current run
	int m_depthReached;
	int m_timeReached;
	int m_scoreReached;

	// Load from saved data
	int m_pbDepth;
	int m_pbTime;
	int m_pbScore;
};

