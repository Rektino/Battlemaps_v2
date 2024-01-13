#pragma once
#include <SFML/Graphics.hpp>
#include "cell.h"


class Grid
{
public : 
	Grid(sf::RenderWindow& window); 	
	void draw(sf::RenderWindow& window); 
	std::vector<int> get_mouse_cell(sf::Window& window); 
	float getCellPositionX(int x, int y); 
	float getCellPositionY(int x, int y); 
	sf::Vector2f get_position_vector2f(int x, int y); 
	sf::Vector2f get_cell_size() { return cell_size; }
	void set_piece_on_cell(std::shared_ptr<Piece>, int x, int y); 
	std::shared_ptr<Piece> get_piece_on_cell(int x, int y); 
private: 
	sf::Vector2f cell_size; 
	//std::vector<std::vector<sf::RectangleShape>> cells;
	std::vector<std::vector<cell>> map; 	
};

