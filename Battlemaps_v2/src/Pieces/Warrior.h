#pragma once
#include <cstdint>
#include "Piece.h"

class Warrior : public Piece
{
public: 
	Warrior() = delete; 
	Warrior(int player); 
	const int get_hp() override ; 
	const int get_dmg() override ;
	const int get_range() override { return range; }
	const int get_owner() override { return owner; }
	const std::string_view get_description() override { return static_cast<std::string_view>(description) ; }
	void set_hp(int val) override ; 
	void set_dmg(int val) override;
	void set_owner(int player) { owner = player; }	
	const std::string_view getType() override { return "Warrior"; }	
	void draw_descriptor(sf::RenderTarget& window) override { m_descriptor.draw(window);  }
	static const std::string description;
	piece_descriptor& get_descriptor() override { return m_descriptor;  }
private:
	piece_descriptor m_descriptor;
	int owner{};
	int hp{ WARRIOR_HP };
	int dmg{ WARRIOR_DMG };
	int range{ WARRIOR_RANGE};
};

