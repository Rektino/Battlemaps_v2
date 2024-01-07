#pragma once
#include <SFML/Graphics.hpp>
#include "Events_mouse_key.h"
#include "button.h"
#include "Grid.h"

class menu {
public : 
	menu() = delete; 
	menu(sf::RenderWindow& window , Grid& grid); 	
	void draw(sf::RenderWindow& window); 
	void toggle_state() { active = !active;  }
	inline bool is_active() { return active;  }
private : 	 	
	sf::Font btn_font; 
	Button rules_btn;
	Button sounds_btn;
	Button resume_btn;
	bool active{ false }; 
	bool buttons_created{ false }; 
	
};