#include "Commander.h"

Commander::Commander(int player) : owner(player){};

const int Commander::get_hp() { return hp; }
const int Commander::get_dmg() { return dmg; }
void Commander::set_hp(int val) { hp = val; }
void Commander::set_dmg(int val) { dmg = val; }
const int Commander::get_max_hp()
{
	return max_hp;
}
const std::string Commander::description{ "(War cry) : \nBuff all adjacent pieces(distance 1),\nincreasing their\
damage by 20%\nfor the rest of the game" };