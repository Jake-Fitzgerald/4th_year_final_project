#include "InputField.h"


InputField::InputField(std::shared_ptr<const sf::Font> font, sf::Vector2f t_pos, sf::Vector2f t_size, int t_charSize)
	: m_inputText(*font),
	  m_placeholderText(*font)
{
	// Text box
	m_textBoxFrame.setSize(t_size);
	m_textBoxFrame.setPosition(t_pos);
	m_textBoxFrame.setFillColor(c_inactiveColour);
	m_textBoxFrame.setOutlineColor(c_outlineColour);
	m_textBoxFrame.setOutlineThickness(2.0f);

	// Text
	m_inputText.setFillColor(c_textColour);
	m_inputText.setOutlineColor(sf::Color::Black);
	m_inputText.setOutlineThickness(2.0f);
	m_inputText.setPosition(sf::Vector2f{t_pos.x + 10.0f, t_pos.y + (t_size.y / t_charSize) / 2.0f});
	m_placeholderText.setFillColor(c_textPlaceholderColour);
	m_placeholderText.setOutlineColor(sf::Color::White);
	m_placeholderText.setOutlineThickness(1.0f);
	m_placeholderText.setPosition(m_inputText.getPosition());

	m_cursorShape.setSize(sf::Vector2f{ m_inputText.getPosition().x, m_inputText.getPosition().y + 20.0f });
	m_cursorShape.setFillColor(sf::Color::White);
}

void InputField::setupInputField()
{
	
}

bool InputField::checkIfAreaClicked(sf::Vector2f t_mousePos, sf::Vector2f t_topLeft, sf::Vector2f t_size)
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

void InputField::update(float t_deltaTime)
{
}

void InputField::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_textBoxFrame);

	if (m_storedString.empty() == true)
	{
		t_window.draw(m_placeholderText);
	}
	else
	{
		t_window.draw(m_inputText);
	}

	if (b_isActive == true)
	{
		t_window.draw(m_cursorShape);
	}
}

void InputField::setPos(sf::Vector2f t_pos)
{
	m_textBoxFrame.setPosition(t_pos);
	m_inputText.setPosition(sf::Vector2f{ t_pos.x + 10.0f, m_inputText.getPosition().y });
	m_placeholderText.setPosition(m_inputText.getPosition());
}

void InputField::setIsActive(bool t_bool)
{
	b_isActive = t_bool;

	if (b_isActive == true)
	{
		m_textBoxFrame.setFillColor(c_activeColour);
	}
	else
	{
		m_textBoxFrame.setFillColor(c_inactiveColour);
	}
}

void InputField::setMaxLength(int t_maxLength)
{
	m_maxLength = t_maxLength;
}

void InputField::setPlaceholderString(std::string t_placeholderString)
{

}

void InputField::clearString()
{
	m_storedString.clear();
}

std::string InputField::getString()
{
	return m_storedString;
}

bool InputField::getIsActive()
{
	return b_isActive;
}
