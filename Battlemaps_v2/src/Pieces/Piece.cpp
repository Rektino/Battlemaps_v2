#include "Piece.h"
#include "Piece.h" 
#include <cstdint>


Piece::Piece(short int posX, short int posY, std::shared_ptr<sf::Sprite> sprite_ptr)
	: m_x(posX),
	m_y(posY),
	sprite_ptr(sprite_ptr)
{};
//==========================================================================
Piece::Piece() {
	hp_bar.setOrigin(sf::Vector2f(HP_BAR_SIZE_X, HP_BAR_SIZE_Y));
	hp_bar.setSize(sf::Vector2f(HP_BAR_SIZE_X, HP_BAR_SIZE_Y));
	hp_bar.setFillColor(sf::Color(102, 255, 102));
	hp_outter.setOrigin(sf::Vector2f(HP_BAR_SIZE_X, HP_BAR_SIZE_Y));
	hp_outter.setSize(sf::Vector2f(HP_BAR_SIZE_X, HP_BAR_SIZE_Y));
	hp_outter.setFillColor(sf::Color::Transparent);
	hp_outter.setOutlineThickness(1.2f);
	hp_outter.setOutlineColor(sf::Color::Black);
}
//==========================================================================
int Piece::getX() const { return m_x; }
int Piece::getY() const { return m_y; }
//==========================================================================
void Piece::setX(short int posx) { m_x = posx; }
void Piece::setY(short int posy) { m_y = posy; }
//==========================================================================
const std::string_view Piece::getType() { return "Piece"; }

//==========================================================================	
// Function to move a piece
Piece& Piece::move(sf::Vector2f newPos, int posX, int posY) {
	assert((posX < GRID_SIZE_X) && (posY < GRID_SIZE_Y));
	m_x = posX;
	m_y = posY;
	//Write code to change the Sprites position to the correct Point_2d position within the map : 	
	float sprite_radius_x = sprite_ptr->getGlobalBounds().width / 2;
	float sprite_radius_y = sprite_ptr->getGlobalBounds().height / 2;
	sf::Vector2f spritePos = { newPos.x - sprite_radius_x , newPos.y - sprite_radius_y };
	sf::Vector2f hp_bar_pos = { spritePos.x + 3.0f * HP_BAR_OFFSET , spritePos.y + 15.0f };
	hp_bar.setPosition(hp_bar_pos);
	hp_outter.setPosition(hp_bar_pos);
	sprite_ptr->setPosition(spritePos);
	return *this;
}
//==========================================================================
// updates the hp bar rectangle size and color based on current HP and maximum hp of this piece
void Piece::update_hp_bar()
{
	int max_hp{ 200 }, current_hp{ get_hp() };
	float percentage;
	std::string_view type = getType();
	if (type == "Warrior") {
		max_hp = WARRIOR_HP;
	}
	else if (type == "Archer") {
		max_hp = ARCHER_HP;
	}
	else if (type == "Defender") {
		max_hp = DEFENDER_HP;
	}
	else if (type == "Mage") {
		max_hp = MAGE_HP;
	}
	else if (type == "Assassin") {
		max_hp = ASSASSIN_HP;
	}
	else if (type == "Sniper") {
		max_hp = SNIPER_HP;
	}
	else if (type == "Healer") {
		max_hp = HEALER_HP;
	}
	else if (type == "Commander") {
		max_hp = COMMANDER_HP;
	}
	percentage = static_cast<float>(current_hp) / static_cast<float>(max_hp);

	if (percentage < 0.05) {
		percentage = 0.05f;
	}
	if (percentage < 0.25) {
		hp_bar.setFillColor(sf::Color(253, 51, 28));
	}
	else if (percentage < 0.5) {
		hp_bar.setFillColor(sf::Color(226, 100, 28));
	}
	else if (percentage < 0.85) {
		hp_bar.setFillColor(sf::Color(230, 205, 50));
	}
	const sf::Vector2f hp_scale = { 1.0f , percentage };
	hp_bar.setScale(hp_scale);
}

//==========================================================================

void Piece::update_moves_left(int moves)
{
	assert(moves >= 0);
	moves_left = moves;
}

//==========================================================================

void Piece::update_attacks_left(int attacks) {
	attacks_left = attacks;
}

//==========================================================================

void Piece::toggle_effect() {
	has_effect = !has_effect;
}