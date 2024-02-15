#include "Mage.h"

Mage::Mage(int player) : owner(player) {};

const int Mage::get_hp() { return hp; }
const int Mage::get_dmg() { return dmg; }
void Mage::set_hp(int val) { hp = val; }
void Mage::set_dmg(int val) { dmg = val; }

const std::string Mage::description = { "(Hellfire) : \nSelect any 2x2 area on\nthe map. The area becomes\nburnt, causing pieces \n\
that stand there\nat the end of your turn to\n\receive damage equal\nto 10 % of their current health." };