#include "Sniper.h"


Sniper::Sniper(int player) : owner(player){ };

const int Sniper::get_hp() { return hp; }
const int Sniper::get_dmg() { return dmg; }
void Sniper::set_hp(int val) { hp = val; }
void Sniper::set_dmg(int val) { dmg = val; }

const std::string Sniper::description = { "(Deadly bullet) :\nFor this round, gain +2 range.\nThe next attack will be \na critical hit (+50% damage)" };