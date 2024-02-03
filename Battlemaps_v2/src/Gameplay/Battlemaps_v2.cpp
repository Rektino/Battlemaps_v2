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
    /************************************/
    /* Initialize menu - icons - players*/
    /************************************/
    Grid grid(main_window);     
    Menu game_menu(grid);
    Menu_icon menu_icon(main_window , grid) ;     
    Help_icon help_icon(main_window, grid); 
    Rulebook my_rulebook(grid);
    Player player1(1, main_window, grid); 
    Player player2(2, main_window, grid);
    player1.place_pieces(grid);    
    player2.place_pieces(grid); 
    sf::Font default_font;
    default_font.loadFromFile(font_paths[0]); 
    sf::Text current_piece_info("", default_font, 18);
    sf::Text dashboard_info(player1.get_dashboard().getInfoAsString(), default_font, 24);
    edit_text(dashboard_info, sf::Color::Black, 24U, grid.get_position_vector2f(15, 4));
    /**************************************/
    /*------ Create sounds -----*/
    /**************************************/
    std::vector<std::unique_ptr<sf::SoundBuffer>> buffers;
    std::vector<sf::Sound> sounds_vector(number_of_sounds);
    for (int i{}; i < number_of_sounds; i++) {
        buffers.push_back(create_buffer_from_file(soundPaths[i]));
        sounds_vector[i].setBuffer(*buffers[i]);
    }
    Game_states game_state = Game_states::placement; 
    Event_states event_state = Event_states::neutral;    
    Button end_turn_btn(main_window, grid, 2 * grid.get_cell_size().x, grid.get_cell_size().y, "END TURN"); 
    end_turn_btn.setTextSize(25); 
    //end_turn_btn.setRectFillColor(sf::Color::Color(154, 246, 148)); 
    end_turn_btn.setRectFillColor(sf::Color::Transparent); 
    end_turn_btn.setPosition(grid,grid.get_position_vector2f(12,4)); 
    bool player1_turn = true;    
    randomize_pieces(main_window, grid, player1, player2);   
    game_state = Game_states::action; 
    // 
    /************************************/
    /*********MAIN WINDOW LOOP***********/
    /************************************/
    while (main_window.isOpen())
    {
        main_window.clear(sf::Color(255, 245, 220));
        grid.draw(main_window); 
        menu_icon.draw(main_window); 
        help_icon.draw(main_window);
        player1.draw(main_window, grid);
        player2.draw(main_window, grid);
        main_window.draw(current_piece_info); 
        end_turn_btn.draw(main_window); 
        main_window.draw(dashboard_info); 
        if (my_rulebook.is_active()) {
            my_rulebook.draw(main_window);
        }        
        if (game_menu.is_active()) {
            game_menu.draw(main_window);            
        }
        if (check_end_turn(game_state , player1_turn, player1, player2)) {
            end_turn_btn.activate();              
        }
        else {
            end_turn_btn.deactivate(); 
        }
        main_window.display();      
        sf::Event event; 
        while (main_window.pollEvent(event)) {  
            Timer t1; 
            std::vector<int> mouse_cell_i = grid.get_mouse_cell(main_window);            
            sf::Vector2f mousePos_f = main_window.mapPixelToCoords(sf::Mouse::getPosition(main_window));                    
            if (event.type == sf::Event::Closed) {
                std::cout << "WINDOW CLOSED !!";
                main_window.close();
            }
            else if (ESC_pressed(event)) {
                std::cout << "ESCAPE key pressed\n"; 
                game_menu.toggle_state();                 
            }
            else if (H_pressed(event)) {
                std::cout << "H key pressed\n"; 
                my_rulebook.toggle_state(); 
            }
            else if (SELECTING_PIECE(event , event_state)) {
                std::cout << "@@ SELECTION @@\n";  
                Player& player = (player1_turn ? player1 : player2);
                if (grid.set_selected_piece(player1_turn, mouse_cell_i) != nullptr) {
                    event_state = Event_states::selected_piece; 
                    playSound(Sounds::selection, sounds_vector);
                    current_piece_info.setString(player.get_piece_info(grid.get_selected_piece()));
                    edit_text(current_piece_info, sf::Color::Black, 18U, grid.get_position_vector2f(11, 0));
                    if (game_state == action) {
                        player.evaluate_actions(grid, grid.get_selected_piece()); 
                        grid.activate_available_cells(player.get_available_moves(), sf::Color::Magenta); 
                    }
                }
                else if (end_turn_btn.contains(mousePos_f) && end_turn_btn.is_active()) {
                    player1_turn = !player1_turn;
                    if (player1_turn) game_state = Game_states::action;
                    playSound(Sounds::victory, sounds_vector);
                    current_piece_info.setString("");
                }
                else {
                    current_piece_info.setString("");
                    bool is_move = (grid.get_previous_piece() != nullptr) && (game_state == action) && (player.is_available_move(mouse_cell_i)) ; 
                    if (is_move) {
                        //TODO  : Fix bug here. The previous piece starting coords are not getting deleted/upadted on the grid
                        // ,unlike the selected piece.
                        auto start_coords = grid.get_start_coords();
                        player.move_piece(grid.get_previous_piece(), mouse_cell_i.at(0), mouse_cell_i.at(1) , grid); 
                        grid.set_piece_on_cell(nullptr, start_coords.at(0), start_coords.at(1));
                        grid.set_piece_on_cell(grid.get_previous_piece(), mouse_cell_i.at(0), mouse_cell_i.at(1)) ;
                        grid.deactivate_all_cells(); 
                    }
                    grid.set_previous_piece(nullptr); 
                }                
            }
            else if (MOUSE_HOVERING(event , event_state)) {
                mouse_hover(main_window, grid, end_turn_btn, game_menu);
            }
            else if (DRAGGING_PIECE(event , event_state , grid)) {   
                event_state = Event_states::moving_piece; 
                Player& player = (player1_turn ? player1 : player2) ;                
                player.drag_piece(grid.get_selected_piece() , mousePos_f , mouse_cell_i[0] , mouse_cell_i[1] , grid);                
            }
            else if (RELEASING_PIECE(event , event_state)) { 
                event_state = Event_states::neutral; 
                Player& player = (player1_turn ? player1 : player2);
                player.release_piece(game_state, grid.get_selected_piece(), mouse_cell_i[0], mouse_cell_i[1], grid); 
                current_piece_info.setString("");
                grid.deactivate_all_cells(); 
                playSound(Sounds::piece_move, sounds_vector);                   
            }         
            else if (KEEP_SELECTION(event, event_state)) {
                event_state = Event_states::hold_selection; 
            }
        }
    }
    return 0; 
}
