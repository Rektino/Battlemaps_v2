#include "Sniper.h"


Sniper::Sniper(int player) : owner(player), m_descriptor() { };

const int Sniper::get_hp() { return hp; }
const int Sniper::get_dmg() { return dmg; }
void Sniper::set_hp(int val) { hp = val; }
void Sniper::set_dmg(int val) { dmg = val; }

const std::string Sniper::description = { "For this round, \ngain +2 range. The next attack\nwill be a critical hit (+50% damage)" };