#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include <iostream>


class HUD
{
public:
	HUD(const sf::Font& font);

	void updateFPSText(float &t_fpsNumber);
	void setFPSBool();
	bool getFPSBool();

	void drawHUD(sf::RenderWindow &t_window);

private:
	// FPS
	float m_fpsNumber;
	sf::Text m_fpsText;
	bool b_isFPSVisible;
};

