// Battlemaps_v2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Battlemaps_v2.h"


int main()
{
    sf::VideoMode fullscreenMode = sf::VideoMode::getFullscreenModes()[0]; // Get the first available fullscreen mode
    sf::RenderWindow main_window(fullscreenMode, "BattleMaps", sf::Style::Close);    
    Grid my_grid(main_window);     
    menu game_menu(main_window , my_grid);    
    while (main_window.isOpen())
    {
        main_window.clear(sf::Color(255, 245, 220));
        my_grid.draw(main_window);        
        if (game_menu.is_active()) {
            game_menu.draw(main_window); 
        }        
        main_window.display();
        sf::Event event; 
        while (main_window.pollEvent(event)) {  
            if (event.type == sf::Event::Closed) {
                std::cout << "CLOSED !!!";
                main_window.close();
            }
            if (ESC_pressed(event)) {
                std::cout << "ESCAPE key pressed\n"; 
                game_menu.toggle_state();                 
            }
        }
    }


    return 0; 
}
