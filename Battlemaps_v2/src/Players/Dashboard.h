#pragma once
#include "global_constants.h"
#include "Grid.h"
#include <sstream>


class Dashboard {
public:
	Dashboard();
	Dashboard(const int actions, const int pieces, const double avg_hp) :
		actions_left(actions), pieces_alive(pieces), average_hp(avg_hp) {
	};
	std::string getInfoAsString() const;
	void updateActions(int actionsLeft);
	void updatePiecesAlive(int piecesAlive);
	void updateAvgHp(double avgHP);
	int get_actions() const { return actions_left; }//returns number of actions left
	int get_pieces() const { return pieces_alive; } //returns number of alive pieces
	double get_average_hp() { return average_hp; }
private:
	int actions_left{ 0 };
	int pieces_alive{ 0 };
	double average_hp{ 0 };
};