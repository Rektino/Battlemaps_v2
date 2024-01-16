// Battlemaps_v2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Battlemaps_v2.h"


int main()
{
    sf::VideoMode fullscreenMode = sf::VideoMode::getFullscreenModes()[0]; // Get the first available fullscreen mode
    sf::RenderWindow main_window(fullscreenMode, "BattleMaps", sf::Style::Close);    
    sf::Image icon; 
    icon.loadFromFile("icons/game_icon.png"); 
    main_window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr()); 
    Grid grid(main_window);     
    Menu game_menu(grid);
    Menu_icon menu_icon(main_window , grid) ;     
    Help_icon help_icon(main_window, grid); 
    Rulebook my_rulebook(grid);
    Player player1(1, main_window, grid); 
    player1.place_pieces(grid); 
    Player player2(2, main_window, grid);
    player2.place_pieces(grid); 
    Game_states state = Game_states::placement; 
    bool moving_piece = false; 
    Button end_turn_btn(main_window, grid, 2 * grid.get_cell_size().x, grid.get_cell_size().y, "END TURN"); 
    end_turn_btn.setTextSize(25); 
    end_turn_btn.setRectFillColor(sf::Color::Color(154, 246, 148)); 
    end_turn_btn.setPosition(grid,grid.get_position_vector2f(12,4)); 
    //randomize_pieces(main_window, grid, player1, player2);     
    while (main_window.isOpen())
    {
        main_window.clear(sf::Color(255, 245, 220));
        grid.draw(main_window); 
        menu_icon.draw(main_window); 
        help_icon.draw(main_window);
        player1.draw(main_window, grid);
        player2.draw(main_window, grid);  
        end_turn_btn.draw(main_window); 
        if (my_rulebook.is_active()) {
            my_rulebook.draw(main_window);
        }        
        if (game_menu.is_active()) {
            game_menu.draw(main_window);            
        }        
        main_window.display();      
        sf::Event event; 
        while (main_window.pollEvent(event)) {  
            if (event.type == sf::Event::Closed) {
                std::cout << "WINDOW CLOSED !!";
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
            if (event.type == sf::Event::MouseMoved && !moving_piece) {
                mouse_hover(main_window, grid, end_turn_btn, game_menu); 
            }
        }
    }


    return 0; 
}
