#pragma once
#include "global_constants.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Piece.h"

enum Sounds {
	selection,
	swords,
	arrow,
	knife,
	spell,
	heal,
	snipe,
	shield,
	commander,
	success,
	piece_move,
	press_endturn, 
	victory, 
	number_of_sounds
};

void playSound(Sounds sound, std::vector<sf::Sound>& sounds_vector);
void playPieceSound(std::shared_ptr<Piece> piece_ptr, std::vector<sf::Sound>& sounds_vector);

std::unique_ptr<sf::SoundBuffer> create_buffer_from_file(const std::string& path);


