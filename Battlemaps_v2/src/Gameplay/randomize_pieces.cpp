#include "randomize_pieces.h"


void randomize_pieces(sf::RenderTarget& window, Grid& grid, Player& player1, Player& player2)
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	for (auto& piece : player1.m_pieces) {
		int pos_x = std::rand() % 10;
		int pos_y = std::rand() % 5;
		while (grid.get_piece_on_cell(pos_x, pos_y) != nullptr) {
			pos_x = std::rand() % 10;
			pos_y = std::rand() % 5;
		}
		sf::Vector2f float_pos{ grid.getCellPositionX(pos_x , pos_y) , grid.getCellPositionY(pos_x , pos_y) };
		piece->move(float_pos, pos_x, pos_y);
		int max = get_max_hp(piece);
		int rand_hp = std::rand() % max;
		piece->set_hp(rand_hp);
		piece->update_hp_bar();
		grid.set_piece_on_cell(piece, pos_x, pos_y);
	}
	for (auto& piece : player2.m_pieces) {
		int pos_x = std::rand() % 10;
		int pos_y = std::rand() % 5;
		if (pos_y < 5) pos_y += 5;
		while (grid.get_piece_on_cell(pos_x, pos_y) != nullptr) {
			pos_x = std::rand() % 10;
			pos_y = std::rand() % 5;
			if (pos_y < 5) pos_y += 5;
		}
		sf::Vector2f float_pos{ grid.getCellPositionX(pos_x , pos_y) , grid.getCellPositionY(pos_x , pos_y) };
		piece->move(float_pos, pos_x, pos_y);
		int max = get_max_hp(piece);
		int rand_hp = std::rand() % max;
		piece->set_hp(rand_hp);
		piece->update_hp_bar();
		grid.set_piece_on_cell(piece, pos_x, pos_y);
	}
}


int get_max_hp(std::shared_ptr<Piece> piece) {
	auto type = piece->getType(); 
	if (type == "Warrior") {
		return WARRIOR_HP ;
	}
	else if (type == "Archer") {
		return ARCHER_HP;
	}
	else if (type == "Defender") {
		return DEFENDER_HP;
	}
	else if (type == "Mage") {
		return MAGE_HP;
	}
	else if (type == "Assassin") {
		return ASSASSIN_HP;
	}
	else if (type == "Sniper") {
		return SNIPER_HP;
	}
	else if (type == "Healer") {
		return HEALER_HP;
	}
	else if (type == "Commander") {
		return COMMANDER_HP;
	}
	else {
		std::cout << "Error return from get_max_hp()\n"; 
		return -1; 
	}
}
