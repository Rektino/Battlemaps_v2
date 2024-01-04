#include "Grid.h"
#include <iostream>

Grid::Grid(sf::RenderWindow& window) {
	unsigned window_width = window.getSize().x; 
	unsigned window_height = window.getSize().y; 
	cell_size = {static_cast<float>(window_width / GRID_SIZE_X),
				 static_cast<float>(window_height / GRID_SIZE_Y) }; 
	std::vector<sf::RectangleShape> tmp_row; 
	sf::RectangleShape tmp_cell; 
	tmp_cell.setSize(cell_size);	
	tmp_cell.setFillColor(sf::Color::Transparent); 
	tmp_cell.setOutlineThickness(0.5f);
	tmp_cell.setOutlineColor(sf::Color::Black);
	for (int y = 0; y < GRID_SIZE_Y; y++) {
		for (int x = 0; x < GRID_SIZE_X; x++) {
			tmp_cell.setPosition(x * cell_size.x, y * cell_size.y); 
			tmp_row.push_back(tmp_cell); 
			std::cout << "Created the cell (x,y) = " << x << "," << y << " positioned at : " <<\
				x * cell_size.x << " , " << y * cell_size.y << 	"\n";
		}
		cells.push_back(tmp_row); 
		tmp_row.clear(); 
	}
	std::cout << "Grid creation finished!\n"; 
}

void Grid::draw(sf::RenderWindow& window)
{
	for (int y{}; y < GRID_SIZE_Y; ++y) {
		for (int x{}; x < GRID_SIZE_X; ++x) {
			window.draw(cells[y][x]); 
			std::cout << "Drew cell (" << x << "," << y << ")\n"; 
		}
	}
}

std::vector<int> Grid::get_mouse_cell(sf::Window& window)
{
	return std::vector<int>();
}

float Grid::getCellPositionX(int x, int y)
{
	return 0.0f;
}

float Grid::getCellPositionY(int x, int y)
{
	return 0.0f;
}

sf::Vector2f Grid::get_position_vector2f(int x, int y)
{
	return sf::Vector2f();
}
