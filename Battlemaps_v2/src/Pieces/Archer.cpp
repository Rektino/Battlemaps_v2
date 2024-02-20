#include "Archer.h"

Archer::Archer(int player) : owner(player) {};

const int Archer::get_hp() { return hp; }
const int Archer::get_dmg() { return dmg; }
void Archer::set_hp(int val) { hp = val; }
void Archer::set_dmg(int val) { dmg = val; }
const int Archer::get_max_hp()
{
	return max_hp;
}
const std::string Archer::description{ "(Heaven's shot) : \n For this round, gain +1 range and \nyou are able\
to attack a piece\nwhich stands behind another piece." };