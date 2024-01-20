#include "Grid.h"
#include <iostream>

std::shared_ptr<Piece> Grid::selected_piece = nullptr; 
std::vector<int> Grid::movement_start_coords = { 0,0 }; 

Grid::Grid(sf::RenderWindow& window) {	
	unsigned window_width = window.getSize().x;
	unsigned window_height = window.getSize().y;
	cell_size = { static_cast<float>(window_width / GRID_SIZE_X),
				 static_cast<float>(window_height / GRID_SIZE_Y) };
	std::vector<cell> cell_col; 		
	for (int x = 0; x < GRID_SIZE_X; x++) {
		for (int y= 0; y < GRID_SIZE_Y; y++) {			
			cell_col.emplace_back(cell(window , x , y));			
		}
		map.emplace_back(cell_col); 
		cell_col.clear(); 
	}
	std::cout << "Grid creation finished!\n"; 
	std::cout << "map size is : " << map.size() << std::endl; 
	std::cout << "map[1] size is : " << map[1].size() << std::endl; 
}

void Grid::draw(sf::RenderWindow& window)
{
	for (int x{}; x < GRID_SIZE_X; ++x) {
		for (int y{}; y < GRID_SIZE_Y; ++y) {
			auto& tmp_cell = map[x][y]; 
			tmp_cell.draw(window); 			
		}
	}
}

void Grid::clean_map()
{
	for (auto& col : map) {
		for (auto& cell : col) {
			cell.clean(); 
		}
	}
}

 sf::Vector2i bound_check(sf::Window& window) {
	sf::Vector2i mousePos{ sf::Mouse::getPosition(window) };
	if (mousePos.x < 20) mousePos.x = 20;
	if (mousePos.y < 20) mousePos.y = 20;
	if (mousePos.x > static_cast<int>(window.getSize().x)-20) mousePos.x = static_cast<int>(window.getSize().x - 20);
	if (mousePos.y > static_cast<int>(window.getSize().y)-20) mousePos.y = static_cast<int>(window.getSize().y - 20);	
	return mousePos;
}

std::vector<int> Grid::get_mouse_cell(sf::Window& window)
{
	sf::Vector2i mousePos = bound_check(window) ; 
	sf::Vector2f mousePos_f = { static_cast<float>(mousePos.x) ,
							static_cast<float>(mousePos.y) }; 	
	int cell_x = static_cast<int>(mousePos.x / this->cell_size.x); 
	int cell_y = static_cast<int>(mousePos.y / this->cell_size.y);
	return { cell_x , cell_y }; //due to map being [row][column]
}

float Grid::getCellPositionX(int x, int y)
{
	std::cout << "Trying to access cell (" << x << "," << y << ")\n"; 
	assert(x < GRID_SIZE_X && y < GRID_SIZE_Y);
	return std::floor(map[x][y].getPosition().x + map[x][y].getWidth() / 2.0f);	
}

float Grid::getCellPositionY(int x, int y)
{
	assert(x < GRID_SIZE_X && y < GRID_SIZE_Y);
	return std::floor(map[x][y].getPosition().y + map[x][y].getHeight() / 2.0f);
}

sf::Vector2f Grid::get_position_vector2f(int x, int y)
{	 
	return sf::Vector2f{ getCellPositionX(x , y) ,  getCellPositionY(x , y) };
}

void Grid::set_piece_on_cell(std::shared_ptr<Piece> piece, int x, int y)
{
	map.at(x).at(y).setPiece(piece);
	return; 
}

void Grid::set_selected_piece(bool player1_turn , int posX, int posY)
{
	/*auto& piece = map.at(posX).at(posY).getPiece(); 
	if (player1_turn) {
		if (piece->get_owner() == 1) {
			selected_piece = piece; 
		}		
	}
	else {
		if (piece->get_owner() == 2) {
			selected_piece = piece; 
		}
	}*/
}

void Grid::set_selected_piece(bool player1_turn , std::vector<int> coords)
{
	assert(coords.size() == 2); 
	selected_piece = map.at(coords.at(0)).at(coords.at(1)).getPiece() ;
	if (selected_piece != nullptr) {
		movement_start_coords = { selected_piece->getX() , selected_piece->getY() };
	}	
}

std::shared_ptr<Piece> Grid::get_piece_on_cell(int x, int y)
{
	auto piece = map.at(x).at(y).getPiece();
	if (piece == nullptr) {
		std::cerr << "(!)-- Null piece returned from get_piece_on_cell(" << x << "," << y << ")\n"; 
		return nullptr; 
	}
	return piece; 
}

std::shared_ptr<Piece> Grid::get_piece_on_cell(std::vector<int> coords_i)
{
	assert(coords_i.size() == 2); 
	auto x = coords_i.at(0); 
	auto y = coords_i.at(1); 
	return get_piece_on_cell(x , y) ;
}
