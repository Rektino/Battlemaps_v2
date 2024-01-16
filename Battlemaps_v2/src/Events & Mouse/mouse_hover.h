#include "Grid.h"
#include "button.h"
#include "menu.h"
#include <SFML/Graphics.hpp>

bool mouse_over_piece(Grid& grid, sf::Vector2f position_f); 

void mouse_hover(sf::RenderWindow& window , Grid& grid , Button& end_turn_btn, Menu& menu); 