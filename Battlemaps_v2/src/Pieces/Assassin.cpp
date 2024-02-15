#include "Assassin.h"

Assassin::Assassin(int player) : owner(player) {};

const int Assassin::get_hp() { return hp; }
const int Assassin::get_dmg() { return dmg; }
void Assassin::set_hp(int val) { hp = val; }
void Assassin::set_dmg(int val) { dmg = val; }

const std::string Assassin::description { "(Invisibility Cloak) :\n Become invisible\nto your opponent's pieces, \nfor their next 2 rounds,\
or\nuntil it attacks. The next attack\nwill be a critical hit(+50 % damage)" };