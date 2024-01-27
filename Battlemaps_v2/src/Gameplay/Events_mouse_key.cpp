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

//returns true if the user is moving the mouse anywhere, and the event_state is 'neutral'
bool MOUSE_HOVERING(sf::Event& event, Event_states& event_state) {
	return ((event_state == neutral || event_state == hold_selection) &&
		(event.type == sf::Event::MouseMoved));
}

//returns true if the user clicked on somewhere and the event_state is 'neutral'
bool SELECTING_PIECE(sf::Event& event, Event_states& event_state) {
	return ((event_state == neutral || event_state == hold_selection) && 
		(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left));
}

//returns true if the user is currently draggin a piece and the event_state is 'selected_piece' OR 'moving_piece'
bool DRAGGING_PIECE(sf::Event& event, Event_states& event_state, Grid& grid) {
	return ((event_state == selected_piece || event_state == moving_piece) && (event.type == sf::Event::MouseMoved && sf::Mouse::isButtonPressed(sf::Mouse::Left)
		&& grid.get_selected_piece() != nullptr));
}

//returns true if the user is releasing a piece and event_state is 'moving_piece'
bool RELEASING_PIECE(sf::Event& event, Event_states& event_state) {
	return (event_state == moving_piece && (event.type == sf::Event::MouseButtonReleased)) ;	
}	

bool KEEP_SELECTION(sf::Event& event, Event_states& event_state){
	return (event_state == selected_piece && event.type == sf::Event::MouseButtonReleased); 
}

