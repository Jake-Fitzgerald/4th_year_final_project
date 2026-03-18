#pragma once
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Globals.h"

struct VisButton
{
	sf::RectangleShape m_buttonShape;
	sf::Text m_buttonText;

	VisButton(std::shared_ptr<const sf::Font> font) : m_buttonText(*font)
	{

	}
};

class VisualiserSelect
{
public:
	VisualiserSelect(std::shared_ptr<const sf::Font> font);

	void setupButtonsVisSelect();
	void setupSprites();
	void renderVisSelect(sf::RenderWindow& t_window);

	int mouseClick(sf::Vector2f t_mousePos);
	bool returnClick(sf::Vector2f t_mousePos);
	bool checkIfAreaClicked(sf::Vector2f t_mousePos, sf::Vector2f t_topLeft, sf::Vector2f t_size);

	void resetButtons();


private:
	std::vector<VisButton> m_buttons;
	std::vector<sf::RectangleShape> m_buttonShapes;

	// Button 
	float m_posX = paddingX;
	float m_poY = paddingY;
	float m_spacing = 60.0f;
	sf::Vector2f m_buttonSize = { 200.0f, 40.0f };

	std::shared_ptr<const sf::Font> m_font;
	std::vector<sf::Text> m_buttonTexts;

	int m_visualiserCounts = 3;

	sf::RectangleShape m_returnButton;
	sf::Texture m_returnTexture;
	sf::Sprite m_returnSprite{ m_returnTexture };

};

