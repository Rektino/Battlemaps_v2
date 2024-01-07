#include "Events_mouse_key.h"

bool ESC_pressed(sf::Event& event) {
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
		return true;
	}
	return false;
}

bool H_pressed(sf::Event& event) {
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::H) {
		return true;
	}
	return false;
}