#include "secondary_icons.h"

Menu_icon::Menu_icon(sf::RenderWindow& window , Grid& grid)
{
	if (!m_texture.loadFromFile(icons_texture_paths[0])) {
		std::cerr << "Failed to load menu icon texture \n"; 
	}
	m_sprite.setTexture(m_texture); 
	sf::Vector2f sprite_pos = grid.get_position_vector2f(16, 0);
	sprite_pos.x = sprite_pos.x - m_sprite.getGlobalBounds().width / 2.0f;
	sprite_pos.y = sprite_pos.y - m_sprite.getGlobalBounds().height / 2.0f;
	m_sprite.setPosition(sprite_pos);
	std::cout << "Created menu icon at position : " << sprite_pos.x << " , " << sprite_pos.y << "\n"; 
	m_font.loadFromFile(font_paths[0]); 
	m_text.setFont(m_font); 
	m_text.setCharacterSize(16); 
	m_text.setFillColor(sf::Color::Black); 
	m_text.setString("Menu\n[ESC]"); 
	m_text.setPosition(sf::Vector2f{ sprite_pos.x  , sprite_pos.y + 40.0f });
}

void Menu_icon::draw(sf::RenderWindow& window) {
	window.draw(m_sprite); 
	window.draw(m_text); 
}
/*==============================================================================================================
*==============================================================================================================*/

Help_icon::Help_icon(sf::RenderWindow& window, Grid& grid)
{
	if (!m_texture.loadFromFile(icons_texture_paths[1])) {
		std::cerr << "Failed to load help icon texture \n";
	}
	m_sprite.setTexture(m_texture);
	sf::Vector2f sprite_pos = grid.get_position_vector2f(17, 0);
	sprite_pos.x = sprite_pos.x - m_sprite.getGlobalBounds().width / 2.0f;
	sprite_pos.y = sprite_pos.y - m_sprite.getGlobalBounds().height / 2.0f;
	m_sprite.setPosition(sprite_pos);
	std::cout << "Created help icon at position : " << sprite_pos.x << " , " << sprite_pos.y << "\n";
	m_font.loadFromFile(font_paths[0]);
	m_text.setFont(m_font);
	m_text.setCharacterSize(16);
	m_text.setFillColor(sf::Color::Black);
	m_text.setString("Help\n[H]");
	m_text.setPosition(sf::Vector2f{ sprite_pos.x + 10.0f  , sprite_pos.y + 40.0f });
}

void Help_icon::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
	window.draw(m_text);
}
