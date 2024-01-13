#include "Mage.h"

Mage::Mage(int player) : owner(player) {}; 

const int Mage::get_hp() { return hp; }
const int Mage::get_dmg() { return dmg; }
void Mage::set_hp(int val) { hp = val; }
void Mage::set_dmg(int val) { dmg = val; }

const std::string Mage::description = { "For this round,\nattack up to 3 times and\nmove up to 3 times.\n\
Using all attacks and moves is not mandatory." };