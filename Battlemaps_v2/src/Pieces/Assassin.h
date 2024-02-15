#pragma once
#include <cstdint>
#include "Piece.h"

class Assassin :  public Piece
{
public:
	Assassin() = delete;
	Assassin(int player);
	const int get_hp() override;
	const int get_dmg() override;
	const int get_range() override { return range; }
	const int get_owner() override { return owner; }
	const std::string_view get_description() override { return static_cast<std::string_view>(description); }
	void set_hp(int val);
	void set_dmg(int val);
	void set_owner(int player) { owner = player; }
	const std::string_view getType() override { return "Assassin"; } 
	static const std::string description; 
private:
	int owner{};
	int hp{ ASSASSIN_HP };
	int dmg{ ASSASSIN_DMG};
	int range{ ASSASSIN_RANGE };
};

