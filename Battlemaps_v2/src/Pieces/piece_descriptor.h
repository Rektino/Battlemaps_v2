#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "global_constants.h"
#include <sstream>

class piece_descriptor
{
public : 
	piece_descriptor();
	void draw(sf::RenderTarget& window);
	void set_all_text(const std::string piece_type , const std::string description ,
		const int hp , const int dmg ,const int attacks_left , const int moves_left, bool effect_available); 
	void set_sprite_view(sf::Sprite piece_sprite); 
	void set_position(sf::Vector2f position_vector2f); 
	void make_visible(); 
	void hide(); 
private : 
	bool is_hidden{ true }; 
	int m_hp{0};
	int m_dmg{0};
	bool effect_is_available; 
	sf::Sprite m_sprite; 
	sf::Text title_text; 
	sf::Font title_font; 
	unsigned int title_char_size{ DEFAULT_TITLES_SIZE }; 
	sf::Text description_text; 
	sf::Font description_font; 
	unsigned int description_char_size{ DEFAULT_CHAR_SIZE + 2 }; 
	sf::Text effect_text; 
	sf::Font effect_font; 
	unsigned int effect_char_size{ DEFAULT_CHAR_SIZE + 6 }; 
	sf::RectangleShape outline_rectangle; 
};

