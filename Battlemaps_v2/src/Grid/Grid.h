#pragma once
#include <SFML/Graphics.hpp>
#include "cell.h"
#include <memory>
#include <cassert>

sf::Vector2i bound_check(sf::Window& window); 

class Grid
{
public : 
	Grid(sf::RenderWindow& window); 	
	void draw(sf::RenderWindow& window); 
	void clean_map(); 
	std::vector<int> get_mouse_cell(sf::Window& window); 
	float getCellPositionX(int x, int y); 
	float getCellPositionY(int x, int y); 
	sf::Vector2f get_position_vector2f(int x, int y); 
	sf::Vector2f get_position_vector2f(std::vector<int> coords_i); 
	sf::Vector2f get_cell_size() { return cell_size; }
	void set_piece_on_cell(std::shared_ptr<Piece> piece, int x, int y);
	void activate_particular_cell(std::vector<int> coords);
	void activate_available_cells(const std::vector<std::vector<int>>& coords, sf::Color color); 
	void deactivate_all_cells(); 
	//void set_selected_piece(bool player1_turn , int posX, int posY); 
	std::shared_ptr<Piece> set_selected_piece(bool player1_turn , std::vector<int> coords); 
	void set_previous_piece(std::shared_ptr<Piece> piece) { previous_piece = piece;  } 
	void clear_selected_piece() { selected_piece = nullptr;  }
	std::shared_ptr<Piece> get_selected_piece() { return selected_piece; }
	std::shared_ptr<Piece> get_previous_piece() { return previous_piece;  }
	std::vector<int> get_start_coords() { return movement_start_coords;  }
	std::vector<int> get_previous_start_coords() { return previous_piece_start_coords; }
	std::shared_ptr<Piece> get_piece_on_cell(int x, int y); 
	std::shared_ptr<Piece> get_piece_on_cell(std::vector<int> coords_i); 	
	bool is_free_cell(int posX, int posY); 
	friend bool mouse_over_piece(Grid& grid, sf::Vector2f position_f);
private: 	
	static std::shared_ptr<Piece> previous_piece; 
	static std::shared_ptr<Piece> selected_piece;	 
	static std::vector<int> movement_start_coords; 
	static std::vector<int> previous_piece_start_coords; 
	sf::Vector2f cell_size; 
	std::vector<std::vector<cell>> map; 	
};

