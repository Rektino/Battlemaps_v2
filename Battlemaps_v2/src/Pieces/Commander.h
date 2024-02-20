#pragma once
#include <cstdint>
#include "Piece.h"



class Commander : public Piece
{
public:
	Commander() = delete;
	Commander(int player);
	const int get_hp() override;
	const int get_max_hp() override;
	const int get_dmg() override;
	const int get_range() override { return range; }
	const int get_owner() override { return owner; }
	const std::string_view get_description() override { return static_cast<std::string_view>(description); }
	const std::string_view getType() override { return "Commander"; }
	void set_hp(int val);
	void set_dmg(int val);
	void set_owner(int player) { owner = player; }
	static const std::string description; 
private:
	int owner{};
	const int max_hp{ COMMANDER_HP };
	int hp{ COMMANDER_HP };
	int dmg{ COMMANDER_DMG };
	int range{ COMMANDER_RANGE };
};