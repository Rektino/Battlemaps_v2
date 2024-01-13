#pragma once
#include "Piece.h"

class Sniper : public Piece
{
public:
	Sniper() = delete;
	Sniper(int player); 
	const int get_hp() override;
	const int get_dmg() override;
	const int get_range() override { return range; }
	const int get_owner() override { return owner; }
	const std::string_view get_description() override { return static_cast<std::string_view>(description); }
	void set_hp(int val);
	void set_dmg(int val);
	void set_owner(int player) { owner = player; }
	const std::string_view getType() override { return "Sniper"; }
	static const std::string description ;
private:
	int owner{};	
	int hp{ SNIPER_HP };
	int dmg{ SNIPER_DMG };
	int range{ SNIPER_RANGE };
};
