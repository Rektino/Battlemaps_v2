#include "Piece.h"
#include "Piece.h" 
#include <cstdint>

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

void Piece::set_descriptor_position2f(sf::Vector2f new_position)
{
	std::cout << "Moving piece descriptor...\n"; 
	m_descriptor.set_position(new_position); 
}

//==========================================================================	
// Function to move a piece
Piece& Piece::move(sf::Vector2f newPos, int posX, int posY) {
	assert((posX < GRID_SIZE_X) && (posY < GRID_SIZE_Y));
	m_x = posX;
	m_y = posY;
	//Write code to change the Sprites position to the correct Point_2d position within the map : 	
	float sprite_radius_x = m_sprite->getGlobalBounds().width / 2;
	float sprite_radius_y = m_sprite->getGlobalBounds().height / 2;
	sf::Vector2f spritePos = { newPos.x - sprite_radius_x , newPos.y - sprite_radius_y };
	sf::Vector2f hp_bar_pos = { spritePos.x + 3.0f * HP_BAR_OFFSET , spritePos.y + 15.0f };
	hp_bar.setPosition(hp_bar_pos);
	hp_outter.setPosition(hp_bar_pos);
	m_sprite->setPosition(spritePos);	
	return *this;
}
void Piece::draw(sf::RenderTarget& window)
{
	window.draw(*m_sprite);
	window.draw(hp_bar);
	window.draw(hp_outter); 
}

void Piece::draw_descriptor(sf::RenderTarget& window)
{
	m_descriptor.draw(window); 
}

//==========================================================================
// updates the hp bar rectangle size and color based on current HP and maximum hp of this piece
void Piece::update_hp_bar()
{
	int max_hp{ get_max_hp()};
	int current_hp{ get_hp() };
	float percentage;
	std::string_view type = getType();	
	percentage = static_cast<float>(current_hp) / static_cast<float>(max_hp);
	if (percentage < 0.0) {
		percentage = 0.0; 
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

void Piece::activate_effect()
{
	const std::string_view piece_type = getType();
	if (piece_type == "Warrior") {
		//TODO : change actions & moves, set turn counter for the effect !
	}
}
