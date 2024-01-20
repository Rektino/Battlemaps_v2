#include "sounds.h"



void playSound(Sounds sound, std::vector<sf::Sound>& sounds_vector)
{
	sounds_vector[sound].setVolume(100);
	sounds_vector[sound].play();
	std::cout << "----PLAYED SOUND : " << sound << "\n";
}

void playPieceSound(std::shared_ptr<Piece> piece_ptr, std::vector<sf::Sound>& sounds_vector)
{
	if (piece_ptr == nullptr) return; 

	std::string_view type = piece_ptr->getType();
	if (type == "Warrior") {
		playSound(swords, sounds_vector);
	}
	else if (type == "Archer") {
		playSound(arrow, sounds_vector);
	}
	else if (type == "Mage") {
		playSound(spell, sounds_vector);
	}
	else if (type == "Assassin") {
		playSound(knife, sounds_vector);
	}
	else if (type == "Healer") {
		playSound(heal, sounds_vector);
	}
	else if (type == "Sniper") {
		playSound(snipe, sounds_vector);
	}
	else if (type == "Defender") {
		playSound(shield, sounds_vector);
	}
	else if (type == "Commander") {
		playSound(commander, sounds_vector);
	}
}

std::unique_ptr<sf::SoundBuffer> create_buffer_from_file(const std::string& path)
{
	auto buf = std::make_unique<sf::SoundBuffer>();
	buf->loadFromFile(path);
	return buf;
}