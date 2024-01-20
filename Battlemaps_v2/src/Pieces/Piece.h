#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cassert>
#include "global_constants.h"

enum PieceType {
	War,
	Def,
	Arc,
	Mag,
	Assa,
	Sni,
	Heal,
	Comm,
	num_of_piece_types
};

class Piece {
protected:
	Piece();
	virtual ~Piece() = default;
	//friend void drawPieces(sf::RenderTarget& window, std::vector<std::shared_ptr<Piece>>& player1_piece_vect, std::vector<std::shared_ptr<Piece>>& player2_piece_vect);
public:	
	int getX() const;
	int getY() const;
	void setX(short int);
	void setY(short int);
	void update_hp_bar();
	void update_moves_left(int moves);
	void update_attacks_left(int attacks);
	void toggle_effect();
	void setSprite(std::shared_ptr<sf::Sprite> sprite_ptr) { m_sprite = sprite_ptr;	}
	int get_attacks_left() { return attacks_left; }
	int get_moves_left() { return moves_left; }
	bool effect_is_available() { return has_effect; }
	virtual const int get_dmg() = 0;
	virtual const int get_hp() = 0;
	virtual const int get_range() = 0;
	virtual const int get_owner() = 0;
	virtual void set_hp(int val) = 0;
	virtual void set_dmg(int val) = 0;
	virtual const std::string_view get_description() = 0;
	virtual const std::string_view getType() = 0;
	Piece& move(sf::Vector2f newPos, int posX, int posY);
	void draw(sf::RenderTarget& window); 
private:
	std::shared_ptr<sf::Sprite> m_sprite; 
	int m_x{}, m_y{};
	int moves_left{ 1 };
	int attacks_left{ 1 };
	bool has_effect{ true };
	//int effect_turn_counter{} ;
	sf::RectangleShape hp_bar{};
	sf::RectangleShape hp_outter{};	
};
