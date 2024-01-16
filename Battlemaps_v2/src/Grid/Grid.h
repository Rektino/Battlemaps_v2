#pragma once
#include <SFML/Graphics.hpp>
#include "cell.h"
#include <memory>


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
	sf::Vector2f get_cell_size() { return cell_size; }
	void set_piece_on_cell(std::shared_ptr<Piece> piece, int x, int y);
	void set_selected_piece(int posX, int posY); 
	std::shared_ptr<Piece> get_selected_piece() { return selected_piece; }
	std::shared_ptr<Piece> get_piece_on_cell(int x, int y); 	
	friend bool mouse_over_piece(Grid& grid, sf::Vector2f position_f);
private: 	
	static std::shared_ptr<Piece> selected_piece;
	sf::Vector2f cell_size; 
	//std::vector<std::vector<sf::RectangleShape>> cells;
	std::vector<std::vector<cell>> map; 	
};

