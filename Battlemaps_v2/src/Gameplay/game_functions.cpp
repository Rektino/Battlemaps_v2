#include "game_functions.h"

bool check_end_turn(bool player1_turn, Player& player1, Player& player2)
{
	if (player1_turn) {
		return (player1.all_pieces_on_map());
	}
	else {
		return (player2.all_pieces_on_map());
	}
}
