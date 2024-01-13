// Battlemaps_v2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Battlemaps_v2.h"


int main()
{
    sf::VideoMode fullscreenMode = sf::VideoMode::getFullscreenModes()[0]; // Get the first available fullscreen mode
    sf::RenderWindow main_window(fullscreenMode, "BattleMaps", sf::Style::Close);    
    Grid grid(main_window);     
    Menu game_menu(grid);
    Menu_icon menu_icon(main_window , grid) ;     
    Help_icon help_icon(main_window, grid); 
    Rulebook my_rulebook(grid);
    Player player1(1, main_window, grid); 
    player1.place_sprites(grid); 
    Player player2(2, main_window, grid);
    player2.place_sprites(grid); 
    while (main_window.isOpen())
    {
        main_window.clear(sf::Color(255, 245, 220));
        grid.draw(main_window); 
        menu_icon.draw(main_window); 
        help_icon.draw(main_window);
        player1.draw(main_window, grid);
        player2.draw(main_window, grid); 
        if (my_rulebook.is_active()) {
            my_rulebook.draw(main_window);
        }        
        if (game_menu.is_active()) {
            game_menu.draw(main_window); 
            cursor_on_menu(main_window , grid , game_menu) ; 
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
            if (H_pressed(event)) {
                std::cout << "H key pressed\n"; 
                my_rulebook.toggle_state(); 
            }
        }
    }


    return 0; 
}
