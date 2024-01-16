#pragma once
#include <cstdlib>
#include <random>
#include "Player.h"

void randomize_pieces(sf::RenderTarget& window , Grid& grid , Player& player1 , Player& player2);

int get_max_hp(std::shared_ptr<Piece> piece); 