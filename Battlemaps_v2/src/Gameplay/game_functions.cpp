#include "game_functions.h"

bool check_end_turn(Game_states game_stage, bool player1_turn, Player& player1, Player& player2)
{
	switch (game_stage) {
	case(Game_states::placement):
		if (player1_turn) {
			return (player1.all_pieces_on_map());
		}
		else {
			return (player2.all_pieces_on_map());
		}
		break;
	case(Game_states::action):
		//....TODO
		const Dashboard& player_db = player1_turn ? player1.get_dashboard() : player2.get_dashboard() ; 
		if (player_db.get_actions() == 0) {
			return true;
		}
		return false; 
		break;
	}
	return false; 
}

void remove_dead_pieces(Grid& grid, Player& player1, Player& player2)
{
	auto& p1_pieces = player1.m_pieces;
	auto& p2_pieces = player2.m_pieces; 
	p1_pieces.erase(std::remove_if(p1_pieces.begin() , p1_pieces.end() , 
		[](const auto& piece_ptr) {
			return (piece_ptr->get_hp() <= 0);
		}),
		p1_pieces.end());
	p2_pieces.erase(std::remove_if(p2_pieces.begin(), p2_pieces.end(),
		[](const auto& piece_ptr) {
			return (piece_ptr->get_hp() <= 0);
		}),
		p2_pieces.end()); 
	grid.remove_dead_from_grid(); 
}
