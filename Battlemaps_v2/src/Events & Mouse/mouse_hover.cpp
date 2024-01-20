#include "mouse_hover.h"

bool mouse_over_piece(Grid& grid, sf::Vector2f position_f)
{
	for (auto& row : grid.map) {
		for (auto& cell : row) {
			if (cell.contains(position_f) && cell.getPiece() != nullptr) {
				return true; 				
			}
		}
	}
	return false;
}

void mouse_hover(sf::RenderWindow& window, Grid& grid, Button& end_turn_btn, Menu& menu)
{
	sf::Cursor cursor;
	sf::Vector2i mouse_pos_i = bound_check(window); 
	sf::Vector2f mouse_pos_f = { static_cast<float>(mouse_pos_i.x) , static_cast<float>(mouse_pos_i.y) };
	if (end_turn_btn.contains(mouse_pos_f) || (menu.is_active() && menu.contains(mouse_pos_f))
		|| mouse_over_piece(grid, mouse_pos_f)) {
		cursor.loadFromSystem(sf::Cursor::Hand);
		window.setMouseCursor(cursor);
	}
	else {
		cursor.loadFromSystem(sf::Cursor::Arrow); 
		window.setMouseCursor(cursor); 
	}
}
