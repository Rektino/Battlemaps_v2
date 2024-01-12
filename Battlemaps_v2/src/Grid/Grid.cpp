#include "Grid.h"
#include <iostream>

Grid::Grid(sf::RenderWindow& window) {	
	unsigned window_width = window.getSize().x;
	unsigned window_height = window.getSize().y;
	cell_size = { static_cast<float>(window_width / GRID_SIZE_X),
				 static_cast<float>(window_height / GRID_SIZE_Y) };
	std::vector<cell> cell_row; 		
	for (int y = 0; y < GRID_SIZE_Y; y++) {
		for (int x = 0; x < GRID_SIZE_X; x++) {			
			cell_row.emplace_back(cell(window , x , y));			
		}
		map.emplace_back(cell_row); 
		cell_row.clear(); 
	}
	std::cout << "Grid creation finished!\n"; 
	std::cout << "map size is : " << map.size() << std::endl; 
	std::cout << "map[1] size is : " << map[1].size() << std::endl; 
}

void Grid::draw(sf::RenderWindow& window)
{
	for (int y{}; y < GRID_SIZE_Y; ++y) {
		for (int x{}; x < GRID_SIZE_X; ++x) {
			auto& tmp_cell = map[y][x]; 
			tmp_cell.draw(window); 			
		}
	}
}

std::vector<int> Grid::get_mouse_cell(sf::Window& window)
{
	return std::vector<int>();
}

float Grid::getCellPositionX(int x, int y)
{
	assert(x < GRID_SIZE_X && y < GRID_SIZE_Y);
	return std::floor(map[y][x].getPosition().x + map[y][x].getWidth() / 2.0f);	
}

float Grid::getCellPositionY(int x, int y)
{
	assert(x < GRID_SIZE_X && y < GRID_SIZE_Y);
	return std::floor(map[y][x].getPosition().y + map[y][x].getHeight() / 2.0f);
}

sf::Vector2f Grid::get_position_vector2f(int x, int y)
{	 
	return sf::Vector2f{ getCellPositionX(x , y) ,  getCellPositionY(x , y) };
}
