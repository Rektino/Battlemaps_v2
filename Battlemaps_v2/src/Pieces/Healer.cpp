#include "Healer.h"


Healer::Healer(int player) : owner(player), m_descriptor() {};

const int Healer::get_hp() { return hp; }
const int Healer::get_dmg() { return dmg; }
void Healer::set_hp(int val) { hp = val; }
void Healer::set_dmg(int val) { dmg = val; }



const std::string Healer::description = { "(Bliss) : \nFor this round,\nit can heal 3 times" };