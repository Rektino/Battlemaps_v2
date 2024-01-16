#include "menu.h"

Menu::Menu(Grid& grid)
{		
	btn_font.loadFromFile(font_paths[0]); 
	active = false; 
	resume_btn.setTextString("Resume");
	resume_btn.setTextSize(MENU_BTN_TEXT_SIZE);	
	resume_btn.setPosition(grid, grid.get_position_vector2f(6,2));	
	sounds_btn.setTextString("Sounds");
	sounds_btn.setTextSize(MENU_BTN_TEXT_SIZE); 
	sounds_btn.setPosition(grid, grid.get_position_vector2f(6, 4));
	rules_btn.setTextString("Rulebook");
	rules_btn.setTextSize(MENU_BTN_TEXT_SIZE);
	rules_btn.setPosition(grid, grid.get_position_vector2f(6, 6));
	buttons_created = true;
}

//draws the buttons. Make sure that create_buttons() has been called prior to drawing them. 
void Menu::draw(sf::RenderWindow& window)
{
	if (!buttons_created) {
		std::cerr << "Error ! Buttons have not been created\n"; 
		return; 
	}	
	resume_btn.draw(window); 
	sounds_btn.draw(window); 
	rules_btn.draw(window); 	
}

bool Menu::contains(sf::Vector2f position_f)
{	
	return (resume_btn.contains(position_f) || sounds_btn.contains(position_f) || rules_btn.contains(position_f)) ;
}

//=================================================

Rulebook::Rulebook(Grid& grid) {
	sf::Vector2f cell_size = grid.get_cell_size(); 
	sf::Vector2f pos_vect{ grid.get_position_vector2f(1 , 0) }; 
	sf::Vector2f rect_size = { 15.0f * cell_size.x  , 9.0f * cell_size.y };
	m_font.loadFromFile(font_paths[0]); 
	m_text.setFont(m_font); 
	m_text.setCharacterSize(20); 
	m_text.setPosition(pos_vect.x + 20.0f, pos_vect.y + 70.0f); 
	m_text.setFillColor(sf::Color::Black); 
	m_text.setString(description); 
	m_rectangle.setFillColor(sf::Color(166,239,102)); 
	m_rectangle.setPosition(pos_vect); 
	m_rectangle.setSize(rect_size); 
	m_font.loadFromFile(font_paths[1]); 
	title_goal.setFont(m_font); 
	title_goal.setCharacterSize(32); 
	title_goal.setFillColor(sf::Color::Black); 
	title_goal.setPosition(pos_vect.x + 20.0f, pos_vect.y + 5.0f);
	title_goal.setString(goal_str); 

	title_gameplay.setFont(m_font);
	title_gameplay.setCharacterSize(32);
	title_gameplay.setFillColor(sf::Color::Black);
	title_gameplay.setPosition(pos_vect.x + 20.0f, pos_vect.y + 140.0f);
	title_gameplay.setString(gameplay_str); 

	title_piece_info.setFont(m_font);
	title_piece_info.setCharacterSize(32);
	title_piece_info.setFillColor(sf::Color::Black);
	title_piece_info.setPosition(pos_vect.x + 20.0f, pos_vect.y + 490.0f);
	title_piece_info.setString(piece_info_str); 
}

void Rulebook::draw(sf::RenderWindow& window)
{
	window.draw(m_rectangle); 
	window.draw(m_text); 	
	window.draw(title_gameplay); 
	window.draw(title_goal); 
	window.draw(title_piece_info); 
	std::cout << "printed string : " << description << "\n"; 
}


