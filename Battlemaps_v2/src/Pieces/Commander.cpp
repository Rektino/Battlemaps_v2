#include "Commander.h"

Commander::Commander(int player) : owner(player) , m_descriptor() {};

const int Commander::get_hp() { return hp; }
const int Commander::get_dmg() { return dmg; }
void Commander::set_hp(int val) { hp = val; }
void Commander::set_dmg(int val) { dmg = val; }

const std::string Commander::description{ "(War cry) Buff \nall adjacentpieces(distance 1),\nincreasing their\
damage by\n20 % for the rest of the game" };