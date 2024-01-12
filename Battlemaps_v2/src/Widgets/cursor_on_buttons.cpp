#include "cursor_on_buttons.h"

void cursor_on_menu(sf::RenderWindow& window, Grid& grid, Menu& game_menu)
{	
	sf::Cursor my_cursor; 
	sf::Vector2i mousePos_i{ sf::Mouse::getPosition(window) };
	sf::Vector2f mousePos_f = { static_cast<float>(mousePos_i.x) , static_cast<float>(mousePos_i.y) };
	if (game_menu.rules_btn.getGlobalBounds().contains(mousePos_f) || 
		game_menu.resume_btn.getGlobalBounds().contains(mousePos_f) ||
		game_menu.sounds_btn.getGlobalBounds().contains(mousePos_f)) 
	{
		my_cursor.loadFromSystem(sf::Cursor::Hand); 
		window.setMouseCursor(my_cursor);
	}
	else {
		my_cursor.loadFromSystem(sf::Cursor::Arrow); 
		window.setMouseCursor(my_cursor); 
	}
}
