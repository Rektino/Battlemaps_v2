#include "Grid.h"
#include <iostream>

std::shared_ptr<Piece> Grid::selected_piece = nullptr; 
std::shared_ptr<Piece> Grid::previous_piece = nullptr; 
std::vector<int> Grid::movement_start_coords = { 0,0 }; 
std::vector<int> Grid::previous_piece_start_coords = { 0 , 0 }; 

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
	sf::Vector2i mousePos = bound_check(window);
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

sf::Vector2f Grid::get_position_vector2f(std::vector<int> coords_i)
{
	return sf::Vector2f{ getCellPositionX(coords_i.at(0) , coords_i.at(1)) ,
						 getCellPositionY(coords_i.at(0) , coords_i.at(1)) };
}

void Grid::set_piece_on_cell(std::shared_ptr<Piece> piece, int x, int y)
{
	map.at(x).at(y).setPiece(piece);
	return;
}
//set the active cell green 
void Grid::activate_particular_cell(std::vector<int> coords)
{
	if (coords.at(0) > MAPSIZE - 1 || coords.at(1) > MAPSIZE - 1) {
		std::cerr << "Error: Outside map limits for cell activation\n";
		return;
	}
	deactivate_all_cells(); 
	map.at(coords.at(0)).at(coords.at(1)).activate_selection();
	return;
}

void Grid::activate_available_cells(const std::vector<std::vector<int>>& available_cells, sf::Color color)
{
	for (auto& point : available_cells) {
		auto x = point.at(0); 
		auto y = point.at(1); 
		map.at(x).at(y).activate_selection(color); 
	}
}


void Grid::deactivate_all_cells()

{
	for (auto& row : map) {
		for (auto& cell : row) {
			if (cell.is_active()) {
				cell.deactivate(); 
			}
		}
	}
}


//sets the sellected piece on these coordinates if valid. If out of bounds or wrong player_id, returns nullptr
std::shared_ptr<Piece> Grid::set_selected_piece(bool player1_turn, std::vector<int> coords)
{
	assert(coords.size() == 2);
	auto piece_on_coords = map.at(coords.at(0)).at(coords.at(1)).getPiece(); 
	if (piece_on_coords == nullptr) {
		previous_piece = selected_piece;
		if (previous_piece != nullptr) {
			previous_piece_start_coords = { previous_piece->getX() , previous_piece->getY() };
		}
		selected_piece = nullptr; 
		return nullptr;
	}
	//idea : allow the return of enemy piece also, to assist attack evaluation. Make sure afterwards to block moves. 
	/*int piece_owner = piece_on_coords->get_owner();
	if (((piece_owner == 2) && player1_turn)
		|| (piece_owner == 1) && !player1_turn) {
		previous_piece = selected_piece;
		if (previous_piece != nullptr) {
			previous_piece_start_coords = { previous_piece->getX() , previous_piece->getY() };
		}
		selected_piece = nullptr; 
		return nullptr;
	}*/
	previous_piece = selected_piece; 
	selected_piece = piece_on_coords;
	movement_start_coords = { selected_piece->getX() , selected_piece->getY() };
	activate_particular_cell(coords);
	return selected_piece;
}

std::shared_ptr<Piece> Grid::get_piece_on_cell(int x, int y)
{
	auto piece = map.at(x).at(y).getPiece();
	if (piece == nullptr) {
		std::cout << "-- Null piece returned from get_piece_on_cell(" << x << "," << y << ")\n";
		return nullptr;
	}
	return piece;
}

std::shared_ptr<Piece> Grid::get_piece_on_cell(std::vector<int> coords_i)
{
	assert(coords_i.size() == 2);
	auto x = coords_i.at(0);
	auto y = coords_i.at(1);
	return get_piece_on_cell(x, y);
}

//returns true if a) the cell coords are valid and b) no piece stands there 
bool Grid::is_free_cell(int posX, int posY)
{
	if (posX > MAPSIZE-1 || posY > MAPSIZE-1 || posX < 0 || posY < 0) {
		return false;
	}	
	if (get_piece_on_cell(posX, posY) != nullptr) {
		return false;
	}
	return true ;
}

std::vector<int> Grid::obtain_target(int posX, int posY, int enemy)
{	
	if (posX >= MAPSIZE || posY >= MAPSIZE || posX < 0 || posY < 0) {
		return {}; 
	}
	auto piece_on_coords = map.at(posX).at(posY).getPiece(); 
	if (piece_on_coords == nullptr || piece_on_coords->get_owner() != enemy) {
		return {}; 
	}
	return { posX , posY }; 
}
