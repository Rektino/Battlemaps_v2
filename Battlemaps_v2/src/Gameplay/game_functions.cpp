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
}
