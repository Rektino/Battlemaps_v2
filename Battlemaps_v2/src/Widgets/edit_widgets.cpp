#include "edit_widgets.h"

void edit_text(sf::Text& text, const sf::Color& color, unsigned int char_size, sf::Vector2f position)
{
	text.setFillColor(color);
	text.setCharacterSize(char_size);
	text.setPosition(position);
}

void edit_text(sf::Text& text, const sf::Color& color, unsigned int char_size)
{
	text.setFillColor(color);
	text.setCharacterSize(char_size);
}

void edit_text(sf::Text& text, const sf::Color& color, unsigned int char_size, float pos_x, float pos_y)
{
	text.setFillColor(color);
	text.setCharacterSize(char_size);
	text.setPosition(pos_x, pos_y);
}