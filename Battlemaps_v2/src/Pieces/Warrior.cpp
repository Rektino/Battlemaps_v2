#include "Warrior.h"
#include <cstdint>

const std::string Warrior::description = { "For this round, attack up\nto 3 times and move up to 3 times.\n\
Using all attacks and\n moves is not mandatory." };

Warrior::Warrior(int player) : owner(player) , m_descriptor()  {};

const int Warrior::get_hp()  { return hp; }
const int Warrior::get_dmg() { return dmg; }
void Warrior::set_hp(int val) { hp = val;  }
void Warrior::set_dmg(int val) { dmg = val;  }

