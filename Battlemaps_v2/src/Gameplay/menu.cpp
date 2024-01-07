#include "menu.h"

menu::menu(sf::RenderWindow& window , Grid& grid)
{
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode(); 
	unsigned int width = desktop.width; 
	unsigned int height = desktop.height; 
	btn_font.loadFromFile(font_paths[0]); 
	active = false; 
	resume_btn.setTextString("Resume");
	resume_btn.setTextSize(MENU_BTN_TEXT_SIZE);	
	resume_btn.setPosition(grid, sf::Vector2f{ grid.getCellPositionX(6,2) , grid.getCellPositionY(6,2) });	
	sounds_btn.setTextString("Sounds");
	sounds_btn.setTextSize(MENU_BTN_TEXT_SIZE); 
	sounds_btn.setPosition(grid, sf::Vector2f{ grid.getCellPositionX(6,4) , grid.getCellPositionY(6,4) });
	rules_btn.setTextString("Rulebook");
	rules_btn.setTextSize(MENU_BTN_TEXT_SIZE);
	rules_btn.setPosition(grid, sf::Vector2f{ grid.getCellPositionX(6,6) ,  grid.getCellPositionY(6,6) });
	buttons_created = true;
}

//draws the buttons. Make sure that create_buttons() has been called prior to drawing them. 
void menu::draw(sf::RenderWindow& window)
{
	if (!buttons_created) {
		std::cerr << "Error ! Buttons have not been created\n"; 
		return; 
	}	
	resume_btn.draw(window); 
	sounds_btn.draw(window); 
	rules_btn.draw(window); 	
}

