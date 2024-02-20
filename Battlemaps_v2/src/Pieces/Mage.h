#pragma once
#include <cstdint>
#include "Piece.h"

class Mage :  public Piece
{
public:
	Mage() = delete;
	Mage(int player);
	const int get_hp() override;
	const int get_max_hp() override;
	const int get_dmg() override;
	const int get_range() override { return range; }
	const int get_owner() override { return owner; }
	const std::string_view getType() override { return "Mage"; }
	const std::string_view get_description() override { return static_cast<std::string_view>(description); }
	void set_hp(int val);
	void set_dmg(int val);
	void set_owner(int player) { owner = player; }
	static const std::string description; 
private:
	int owner{};
	const int max_hp{ MAGE_HP };
	int hp{ MAGE_HP };
	int dmg{ MAGE_DMG };
	int range{ MAGE_RANGE };
};

