#pragma once
#include <SFML/Graphics.hpp>
#include "global_constants.h"
#include "Grid.h"

bool ESC_pressed(sf::Event&); 
bool H_pressed(sf::Event&); 

bool DRAGGING_PIECE(sf::Event& event, Event_states& event_state, Grid& grid);
bool SELECTING_PIECE(sf::Event& event, Event_states& event_state);
bool MOUSE_HOVERING(sf::Event& event, Event_states& event_state);
bool RELEASING_PIECE(sf::Event& event, Event_states& event_state);
bool KEEP_SELECTION(sf::Event& event, Event_states& event_state);
