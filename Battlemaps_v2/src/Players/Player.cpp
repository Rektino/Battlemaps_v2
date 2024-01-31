#include "Player.h"

Player::Player(int id, sf::RenderWindow& window, Grid& grid)
	: m_id(id), m_dashboard(3, numPieces, 100)
{
	const std::string(&texture_paths)[8] { id == 1 ? p1_texturePaths : p2_texturePaths };
	std::cout << "PLayer constructor has been called\n";
	cumulative_piece_sum[0] = numWarriors;
	for (int i = 1; i < numPieceTypes; i++) {
		cumulative_piece_sum[i] = cumulative_piece_sum[i - 1] + numPieces_array[i];
	}
	for (int i = 0; i < numPieces; i++) {
		auto index = std::lower_bound(cumulative_piece_sum.begin(), cumulative_piece_sum.end(), i) - cumulative_piece_sum.begin();
		if (cumulative_piece_sum[index] == i) index++;
		m_textures.push_back(assign_texture(texture_paths, index));			
	}
	for (int i = 0; i < numPieces; i++) {
		m_sprites.push_back(create_sprite(m_textures[i]));
	}
	create_pieces(); 
	std::cout << "pieces vector size is = " << m_pieces.size() << "\n"; 
	std::cout << "sprites vector size is = " << m_sprites.size() << "\n"; 
	std::cout << "textures vector size is = " << m_textures.size() << "\n"; 
	int j = 0; 
	for (auto& piece : m_pieces) {
		piece->setSprite(m_sprites[j]); 
		j++; 
	}
}

void Player::draw(sf::RenderTarget& window, Grid& grid)
{
	for (auto& piece_ptr : m_pieces) {
		piece_ptr->draw(window);
	}
}

//Evaluates available moves and attacks of the current player, based on the selected piece
void Player::evaluate_actions(Grid& grid, std::shared_ptr<Piece> selected_piece)
{
	std::cout << "Evaluating actions!!\n"; 
	available_moves.clear(); 
	available_attacks.clear(); 
	short int enemy; 
	if (selected_piece->get_owner() == 1) {
		enemy = 2; 
	}
	else {
		enemy = 1; 
	}
	int x = selected_piece->getX();
	int y = selected_piece->getY();
	int attack_range = selected_piece->get_range();
	for (int dir = NORTH; dir <= TOTAL_DIRECTIONS; dir++) {
		int posX{}, posY{};
		std::vector<int> free_cell_coords; 
		if (dir == NORTH) {
			posX = x;
			posY = y - 1;
			if (grid.is_free_cell(posX, posY)) {
				free_cell_coords.emplace_back(posX);
				free_cell_coords.emplace_back(posY); 
				available_moves.emplace_back(free_cell_coords); 
			}
		}
		else
		if (dir == NORTHEAST) {
			posX = x + 1;
			posY = y - 1;
			if (grid.is_free_cell(posX, posY)) {
				free_cell_coords.emplace_back(posX);
				free_cell_coords.emplace_back(posY);
				available_moves.emplace_back(free_cell_coords);
			}
		}
		else
		if (dir == EAST) {
			posX = x + 1;
			posY = y;
			if (grid.is_free_cell(posX, posY)) {
				free_cell_coords.emplace_back(posX);
				free_cell_coords.emplace_back(posY);
				available_moves.emplace_back(free_cell_coords);
			}
		}
		else
		if (dir == SOUTHEAST) {
			posX = x + 1;
			posY = y + 1;
			if (grid.is_free_cell(posX, posY)) {
				free_cell_coords.emplace_back(posX);
				free_cell_coords.emplace_back(posY);
				available_moves.emplace_back(free_cell_coords);
			}
		}
		else
		if (dir == SOUTH) {
			posX = x;
			posY = y + 1;
			if (grid.is_free_cell(posX, posY)) {
				free_cell_coords.emplace_back(posX);
				free_cell_coords.emplace_back(posY);
				available_moves.emplace_back(free_cell_coords);
			}
		}
		else
		if (dir == SOUTHWEST) {
			posX = x - 1;
			posY = y + 1;
			if (grid.is_free_cell(posX, posY)) {
				free_cell_coords.emplace_back(posX);
				free_cell_coords.emplace_back(posY);
				available_moves.emplace_back(free_cell_coords);
			}
		}
		else
		if (dir == WEST) {
			posX = x - 1;
			posY = y;
			if (grid.is_free_cell(posX, posY)) {
				free_cell_coords.emplace_back(posX);
				free_cell_coords.emplace_back(posY);
				available_moves.emplace_back(free_cell_coords);
			}
		}
		else
		if (dir == NORTHWEST) {
			posX = x - 1;
			posY = y - 1;
			if (grid.is_free_cell(posX, posY)) {
				free_cell_coords.emplace_back(posX);
				free_cell_coords.emplace_back(posY);
				available_moves.emplace_back(free_cell_coords);
			}
		}
		std::cout << "DBG : -- Added available move cell : (" << posX << "," << posY << ") \n"; 
	}
	std::cout << "DBG : ALL AVAILABLE MOVES FOR THIS PIECE : \n"; 
	for (auto& moves : available_moves) {
		std::cout << moves.at(0) << " , " << moves.at(1) << "\n"; 
	}
}

void Player::drag_piece(std::shared_ptr<Piece> piece, sf::Vector2f mousePos_f, int x, int y, Grid& grid)
{	
	piece->move(mousePos_f, x, y);
}

void Player::release_piece(Game_states game_state , std::shared_ptr<Piece> piece, int x, int y, Grid& grid)
{
	assert(piece != nullptr); 
	std::vector<int> pos_vect_i = { x , y }; 
	sf::Vector2f pos_vect_f = grid.get_position_vector2f(x, y); 
	std::vector<int> start_coords = grid.get_start_coords(); 
	switch (game_state) {
	case(placement):
		bool valid_square;
		if (this->m_id == 1) {
			valid_square = (x < MAPSIZE && y < MAPSIZE / 2);
		}
		else {
			valid_square = (x < MAPSIZE && y >= MAPSIZE / 2);
		}
		if (valid_square && grid.get_piece_on_cell(pos_vect_i) == nullptr) {
			piece->move(pos_vect_f, x, y);
			grid.set_piece_on_cell(nullptr, start_coords.at(0), start_coords.at(1));
			grid.set_piece_on_cell(piece, x, y);
			std::cout << "DBG msg : Placed piece on " << x << "," << y << "and deleted piece_ptr from map(" << start_coords[0] <<
				"," << start_coords[1] << ")\n";
			std::cout << std::boolalpha << "piece on starting coords = nullptr :  "
				<< (grid.get_piece_on_cell(start_coords[0], start_coords[1]) == nullptr) << "\n";
		}
		else if (valid_square && grid.get_piece_on_cell(pos_vect_i) != nullptr) {
			std::shared_ptr<Piece> other_piece = grid.get_piece_on_cell(pos_vect_i);
			other_piece->move(grid.get_position_vector2f(start_coords), start_coords.at(0), start_coords.at(1));
			grid.set_piece_on_cell(other_piece, start_coords.at(0), start_coords.at(1));
			piece->move(pos_vect_f, x, y);
			grid.set_piece_on_cell(piece, x, y);
			std::cout << "DBG msg : Swapped on " << x << "," << y << " with piece from map(" << start_coords[0] <<
				"," << start_coords[1] << ")\n";
			std::cout << std::boolalpha << "piece on starting coords = nullptr :  "
				<< (grid.get_piece_on_cell(start_coords[0], start_coords[1]) == nullptr) << "\n";
		}
		else {
			piece->move(grid.get_position_vector2f(start_coords.at(0), start_coords.at(1)), start_coords.at(0), start_coords.at(1));
			std::cout << "DBG msg : Cancelled move\n";
		}
		break; 
	case(action):
		valid_square = false; 
		for (auto& square : available_moves) {
			if (square.at(0) == x && square.at(1) == y) {
				valid_square = true; 
				break;
			}
		}
		if (valid_square) {
			piece->move(pos_vect_f , x ,y);
			grid.set_piece_on_cell(nullptr, start_coords.at(0), start_coords.at(1));
			grid.set_piece_on_cell(piece, x, y); 
			std::cout << "DBG msg : Placed piece on " << x << "," << y << "and deleted piece_ptr from map(" << start_coords[0] <<
				"," << start_coords[1] << ")\n";
			std::cout << std::boolalpha << "piece on starting coords = nullptr :  "
				<< (grid.get_piece_on_cell(start_coords[0], start_coords[1]) == nullptr) << "\n";
		}
		else {
			piece->move(grid.get_position_vector2f(start_coords.at(0), start_coords.at(1)), start_coords.at(0), start_coords.at(1));
			std::cout << "DBG msg : Cancelled move\n";
		}
		break;
	}
	
	//TODO  : Releasing piece on ACTION_STAGE of the game. Need to evaluate available moves etc
	grid.clear_selected_piece(); 
}

bool Player::all_pieces_on_map()
{
	for (auto& piece_ptr : m_pieces) {
		if (piece_ptr->getX() >= MAPSIZE || piece_ptr->getY() >= MAPSIZE) {
			return false;
		}
	}
	return true;
}

std::string Player::get_piece_info(std::shared_ptr<Piece> piece_ptr)
{
	std::stringstream ss;
	ss << piece_ptr->getType() << "\n";
	ss << "Attacks left : " << piece_ptr->get_attacks_left() << "\n";
	ss << "Moves left : " << piece_ptr->get_moves_left() << "\n";
	ss << "Has ability : " << (piece_ptr->effect_is_available() ? "Yes\n" : "No\n");
	ss << "---------------------------------------\n";
	ss << "DMG : " << piece_ptr->get_dmg() << "\n";
	ss << "HP : " << piece_ptr->get_hp() << "\n";
	ss << "RANGE : " << piece_ptr->get_range() << "\n";
	ss << "---------------------------------------\n";
	ss << "ABILITY : " << piece_ptr->get_description() << "\n";
	return ss.str();
}

sf::Texture Player::assign_texture(const std::string* paths, ptrdiff_t i) {
	sf::Texture texture;
	try {
		if (!texture.loadFromFile(paths[i])) {
			throw std::runtime_error("Failed to load image"); // Throw an exception if loading fails
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return texture; 
}

std::shared_ptr<sf::Sprite> Player::create_sprite(sf::Texture& texture)
{
	std::shared_ptr<sf::Sprite> my_sprite_ptr = std::make_shared<sf::Sprite>() ; 
	try {
		my_sprite_ptr->setTexture(texture);
		std::cout << "Set the texture : " << my_sprite_ptr->getTexture() << "\n" ;
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return my_sprite_ptr;
}

void Player::create_pieces()
{
	for (int i{}; i < numWarriors; i++) {
		m_pieces.push_back(std::make_shared<Warrior>(m_id));
	}
	for (int i{}; i < numDefenders; i++) {
		m_pieces.push_back(std::make_shared<Defender>(m_id));
	}
	for (int i{}; i < numArchers; i++) {
		m_pieces.push_back(std::make_shared<Archer>(m_id));
	}
	for (int i{}; i < numMages; i++) {
		m_pieces.push_back(std::make_shared<Mage>(m_id));
	}
	for (int i{}; i < numAssassins; i++) {
		m_pieces.push_back(std::make_shared<Assassin>(m_id));
	}
	for (int i{}; i < numSnipers; i++) {
		m_pieces.push_back(std::make_shared<Sniper>(m_id));
	}
	for (int i{}; i < numHealers; i++) {
		m_pieces.push_back(std::make_shared<Healer>(m_id));
	}
	for (int i{}; i < numCommanders; i++) {
		m_pieces.push_back(std::make_shared<Commander>(m_id));
	}
}

void Player::place_pieces(Grid& grid)
{
	int i = 0; 
	int y_offset = (m_id == 1 ? 1 : 7); 
	const int piecesPerRow = numPieces / 2;
	for (auto& piece_ptr : m_pieces) {
		int posX = 11 + (i % piecesPerRow);
		int posY = y_offset + (i / piecesPerRow);
		sf::Vector2f pos_float ={ grid.get_position_vector2f(posX , posY)};
		piece_ptr->move(pos_float, posX, posY);
		grid.set_piece_on_cell(piece_ptr, posX, posY);
		i++;
	}
}
