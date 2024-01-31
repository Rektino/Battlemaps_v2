#include "Dashboard.h"


Dashboard::Dashboard() = default;



void Dashboard::updateActions(int actionsLeft)
{
	actions_left = actionsLeft;
}

void Dashboard::updatePiecesAlive(int piecesAlive)
{
	pieces_alive = piecesAlive;
}

void Dashboard::updateAvgHp(double avgHP)
{
	average_hp = avgHP;
}

std::string Dashboard::getInfoAsString() const {
	std::stringstream ss;
	ss << "--- PLAYER INFO --- " << "\n";  //should be replaced with the player's username
	ss << "Actions Left: " << actions_left << "\n";
	ss << "Pieces Alive: " << pieces_alive << "\n";
	ss << "Average HP: " << average_hp << "\n";
	//std::cout << "Got info as str for dashboard: " << ss.str() << "\n"; 
	return ss.str();
}