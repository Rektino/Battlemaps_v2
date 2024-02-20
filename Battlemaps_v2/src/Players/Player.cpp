#include "Player.h"

template<typename T>
requires std::totally_ordered<T>
static inline T max(T val1, T val2) {
	return (val1 > val2 ? val1 : val2); 
}

Player::Player(const std::string username , int id, sf::RenderWindow& window, Grid& grid)
	: m_username(username) ,  m_id(id), m_dashboard(username, 3, 100)
{
	const std::string(&texture_paths)[8] { id == 1 ? p1_texturePaths : p2_texturePaths };
	std::cout << "Player constructor has been called\n";
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
		sf::Sprite sprite_copy(*m_sprites[j])  ;
		piece->get_descriptor().set_sprite_view(sprite_copy); 
		j++; 
	}
}

void Player::draw(sf::RenderTarget& window, Grid& grid)
{
	for (auto& piece_ptr : m_pieces) {
		piece_ptr->draw(window);
	}
	m_dashboard.draw(window); 
}

//Evaluates available moves and attacks of the current player, based on the selected piece
void Player::evaluate_actions(Grid& grid, std::shared_ptr<Piece> selected_piece)
{
	std::cout << "Evaluating actions!!\n"; 
	available_moves.clear(); 
	available_attacks.clear(); 
	if (selected_piece->get_owner() != m_id) {
		std::cout << "Enemy piece was selected. Not evaluating actions...\n"; 
		return; 
	}
	short int enemy; 
	if (m_id == 1) {
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
	//TODO : Evaluate available attacks : 
	std::vector<int> target{}; 
	int posX{}, posY{}; 
	for (int dir = NORTH; dir < TOTAL_DIRECTIONS; dir++) {
		for (int distance = 1; distance <= attack_range; distance++) {
			if (dir == NORTH) {
				posX = x;
				posY = y - distance;
				target = grid.obtain_target(posX, posY, enemy); 
			}else
			if (dir == NORTHEAST) {
				posX = x + distance;
				posY = y - distance;
				target = grid.obtain_target(posX, posY, enemy);
			}
			else
			if (dir == EAST) {
				posX = x + distance;
				posY = y;			
				target = grid.obtain_target(posX, posY, enemy);
			}
			else
			if (dir == SOUTHEAST) {
				posX = x + distance;
				posY = y + distance;
				target = grid.obtain_target(posX, posY, enemy);
			}
			else
			if (dir == SOUTH) {
				posX = x;
				posY = y + distance;
				target = grid.obtain_target(posX, posY, enemy);
			}
			else
			if (dir == SOUTHWEST) {
				posX = x - distance;
				posY = y + distance;
				target = grid.obtain_target(posX, posY, enemy);
			
			}
			else
			if (dir == WEST) {
				posX = x - distance;
				posY = y;			
				target = grid.obtain_target(posX, posY, enemy);
			}
			else
			if (dir == NORTHWEST) {
				posX = x - distance;
				posY = y - distance;
				target = grid.obtain_target(posX, posY, enemy);
			}
			if (target.size() != 0) {
				available_attacks.emplace_back(target); 
				break; // don't search deeper in that direction, cause piece is blocking !
				std::cout << "AVAILABLE TARGET AT : (" << target.at(0) << "," << target.at(1) << ")\n";
			}
		}
	}
	std::cout << "DBG : ALL AVAILABLE ATTACKS FOR THIS PIECE : \n";
	for (auto& attack: available_attacks) {
		std::cout << attack.at(0) << " , " << attack.at(1) << "\n";
	}
}

void Player::drag_piece(std::shared_ptr<Piece> piece, sf::Vector2f mousePos_f, int x, int y, Grid& grid)
{	
	piece->move(mousePos_f, x, y);
}


//used to place a piece only after dragging it (for both Placement and Action game stages ) 
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
		if (valid_square && piece->get_moves_left() > 0 ) {
			piece->move(pos_vect_f , x ,y);
			piece->update_moves_left(piece->get_moves_left() - 1);
			grid.set_piece_on_cell(nullptr, start_coords.at(0), start_coords.at(1));
			grid.set_piece_on_cell(piece, x, y); 
			m_dashboard.updateActions(m_dashboard.get_actions() - 1); 
			if (m_dashboard.get_actions() == 0) {
				lock_player_actions(); 
				grid.deactivate_all_cells(); 
			}
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

void Player::move_piece(std::shared_ptr<Piece> piece, int x, int y, Grid& grid)
{
	assert(piece != nullptr); 
	sf::Vector2f pos_vect_f = grid.get_position_vector2f(x, y);
	std::vector<int> start_coords = grid.get_start_coords();
	piece->move(pos_vect_f, x, y); 
	piece->update_moves_left(piece->get_moves_left() - 1); 
	grid.set_piece_on_cell(nullptr, start_coords.at(0), start_coords.at(1)); 
	grid.set_piece_on_cell(piece, x, y); 
	m_dashboard.updateActions(m_dashboard.get_actions() - 1);
	if (m_dashboard.get_actions() == 0) {
		lock_player_actions(); 
		grid.deactivate_all_cells(); 
	}
}

void Player::attack_piece(std::shared_ptr<Piece> my_piece, std::shared_ptr<Piece> enemy_piece)
{
	std::cout << "Attack piece called\n";
	std::cout << "Attacking piece at " << enemy_piece->getX() << " , " << enemy_piece->getY() << "\n"; 
	int attacker_dmg = my_piece->get_dmg(); 
	int defender_dmg = enemy_piece->get_dmg(); 
	int attacker_hp = my_piece->get_hp(); 
	int defender_hp = enemy_piece->get_hp();
	int defender_range = enemy_piece->get_range(); 
	int dx = abs(my_piece->getX() - enemy_piece->getX()); 
	int dy = abs(my_piece->getY() - enemy_piece->getY()); 
	int distance = max(dx, dy); 
	//Perform attack : 
	enemy_piece->set_hp(defender_hp - attacker_dmg); 
	if (enemy_piece->get_hp() > 0 && defender_range >= distance) {
		my_piece->set_hp(attacker_hp - defender_dmg);  
		my_piece->update_hp_bar();
	}	
	enemy_piece->update_hp_bar(); 
	my_piece->update_attacks_left(my_piece->get_attacks_left() - 1); 	
	m_dashboard.updateActions(m_dashboard.get_actions() - 1); 
	if (m_dashboard.get_actions() == 0) {
		lock_player_actions();
	}
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

void Player::reset_piece_player_actions()
{
	for (auto& piece : m_pieces) {
		piece->update_moves_left(1); 
		piece->update_attacks_left(1); 
		//TODO : what if an effect is active allowing extra moves/attack even in next turn ? 
		//idea : update these pieces separately (effect active) and use a turn_counter_effect private value to 
		//count the turns for which the effect has been active.  
	}
	m_dashboard.updateActions(PLAYER_ACTIONS); 
	locked_actions = false; 
}

void Player::lock_player_actions()
{
	locked_actions = true;
}

bool Player::is_available_move(std::vector<int> coords)
{
	for (const auto& move_coords : available_moves) {
		if (move_coords.at(0) == coords.at(0) && move_coords.at(1) == coords.at(1)) {
			return true; 
		}
	}
	return false;
}

bool Player::is_available_attack(std::vector<int> coords)
{
	for (const auto& attack_coords : available_attacks) {
		if (attack_coords.at(0) == coords.at(0) && attack_coords.at(1) == coords.at(1)) {
			return true;
		}
	}
	return false;
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

void Player::place_descriptors(Grid& grid)
{
	for (auto& piece : m_pieces) {
		piece->set_descriptor_position2f(grid.get_position_vector2f(13, 3));
	}
}

void Player::update_dashboard_text(Grid& grid)
{
	std::string info_str = m_dashboard.getInfoAsString(); 
	m_dashboard.set_text(info_str, 26U, sf::Color::Black);
	if (m_id == 1) {
		m_dashboard.move_text(grid.get_position_vector2f(10, 2));
	}
	else {
		m_dashboard.move_text(grid.get_position_vector2f(10, 7));
	}
	
	//edit_text(p1_dashboard_info, sf::Color::Black, 24U, grid.get_position_vector2f(15, 2));
	//edit_text(p2_dashboard_info, sf::Color::Black, 24U, grid.get_position_vector2f(15, 6));	
}

void Player::update_average_hp()
{
	float sum = 0; 
	float max_sum = 0 ; 
	int counter = 0; 
	float avg; 
	float max_avg; 
	for (const auto& piece : m_pieces) {
		sum += piece->get_hp(); 
		max_sum += piece->get_max_hp(); 
		counter += 1; 
	}
	if (counter >= 0) {
		avg = sum / counter;
		max_avg = max_sum / counter; 
	}
	else {
		return; 
	}	
	m_dashboard.set_avg_hp(avg , max_avg); 
}

void Player::update_piece_descriptors()
{
	for (auto& piece : m_pieces) {
		piece->get_descriptor().set_all_text( static_cast<std::string>(piece->getType()) , static_cast<std::string>(piece->get_description()),
											piece->get_hp(), piece->get_dmg() , piece->get_attacks_left() , piece->get_moves_left());
	}
}

