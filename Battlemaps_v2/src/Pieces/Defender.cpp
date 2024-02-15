#include "Defender.h"


Defender::Defender(int player) : owner(player), m_descriptor() {};

const int Defender::get_hp() { return hp; }
const int Defender::get_dmg() { return dmg; }
void Defender::set_hp(int val) { hp = val; }
void Defender::set_dmg(int val) { dmg = val; }

const std::string Defender::description = { "(Wall) : \nFor this round and\nyour opponent's round, become\ninvulnerable to any damage. " };