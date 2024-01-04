#pragma once
#include <SFML/Graphics.hpp>

constexpr int GRID_SIZE_X = 18; 
constexpr int GRID_SIZE_Y = 10;

class Grid
{
public : 
	Grid(sf::RenderWindow& window); 	
	void draw(sf::RenderWindow& window); 
	std::vector<int> get_mouse_cell(sf::Window& window); 
	float getCellPositionX(int x, int y); 
	float getCellPositionY(int x, int y); 
	sf::Vector2f get_position_vector2f(int x, int y); 
private: 
	sf::Vector2f cell_size; 
	std::vector<std::vector<sf::RectangleShape>> cells;
	
};

