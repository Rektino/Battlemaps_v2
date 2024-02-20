#pragma once
#include "Piece.h"

class Healer : public Piece
{
public:
	Healer() = delete;
	Healer(int player);
	const int get_hp() override;
	const int get_max_hp() override;
	const int get_dmg() override;
	const int get_range() override { return range; }
	const int get_owner() override { return owner; }
	const std::string_view get_description() override { return static_cast<std::string_view>(description); }
	void set_hp(int val);
	void set_dmg(int val);
	void set_owner(int player) { owner = player; }
	const std::string_view getType() override { return "Healer"; }
	static const std::string description;
private:
	int owner{};
	const int max_hp{ HEALER_HP };
	int hp{ HEALER_HP };
	int dmg{ HEALER_DMG };
	int range{ HEALER_RANGE };
};
