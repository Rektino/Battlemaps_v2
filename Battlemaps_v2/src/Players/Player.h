#pragma once
#include "Grid.h"
#include "global_constants.h"
#include "Dashboard.h"
#include <array>
#include "Warrior.h"
#include "Defender.h"
#include "Archer.h"
#include "Mage.h"
#include "Assassin.h"
#include "Sniper.h"
#include "Healer.h"
#include "Commander.h"

enum Directions {
	NORTH,
	NORTHEAST,
	EAST,
	SOUTHEAST,
	SOUTH,
	SOUTHWEST,
	WEST,
	NORTHWEST,
	TOTAL_DIRECTIONS
};

class Player {
public : 
	Player() = delete; 
	Player(int id , sf::RenderWindow& window , Grid& grid); 
	friend void randomize_pieces(sf::RenderTarget&, Grid& grid, Player&, Player&); 
	void draw(sf::RenderTarget& window, Grid& grid); 
	void evaluate_actions(Grid& grid, std::shared_ptr<Piece> selected_piece); 	
	void drag_piece(std::shared_ptr<Piece> piece, sf::Vector2f mouse_float, int x, int y, Grid& grid); 
	void release_piece(Game_states game_state , std::shared_ptr<Piece> piece, int x, int y, Grid& grid);
	void attack_piece(std::shared_ptr<Piece> my_piece, std::shared_ptr<Piece> enemy_piece);	
	bool all_pieces_on_map(); 
	std::string get_piece_info(std::shared_ptr<Piece> piece_ptr);	
	sf::Texture assign_texture(const std::string* paths, ptrdiff_t i);
	//sf::Sprite create_sprite(sf::Texture& texture); 
	std::shared_ptr<sf::Sprite> create_sprite(sf::Texture& texture); 
	void create_pieces(); 
	void place_pieces(Grid& grid); 
	const Dashboard& get_dashboard() { return m_dashboard; }
private : 
	int m_id; 
	Dashboard m_dashboard; 
	std::vector<std::shared_ptr<Piece>> m_pieces; 
	std::vector<std::shared_ptr<sf::Sprite>> m_sprites; 
	std::vector<sf::Texture> m_textures; 
	std::vector<int> movement_start_coords; 
	std::vector<std::vector<int>> available_moves; 
	std::vector<std::vector<int>> available_attacks; 
	std::array<int, numPieceTypes> cumulative_piece_sum{ 0 }; 
};
