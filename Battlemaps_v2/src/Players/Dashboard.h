#pragma once
#include "global_constants.h"
#include "Grid.h"
#include <sstream>


class Dashboard {
public:
	Dashboard();
	Dashboard(const std::string player_name , const int actions, const double avg_hp);
	std::string getInfoAsString() const;
	void updateActions(int actionsLeft);
	void updateAvgHp(double avgHP);
	int get_actions() const { return actions_left; }//returns number of actions left
	double get_average_hp() { return average_hp; }
	void set_text(std::string new_text , unsigned charSize = DEFAULT_CHAR_SIZE, sf::Color color = sf::Color::Black);
	void move_text(sf::Vector2f pos_vector2f); 
	void set_avg_hp(float hp, float max); 
	void draw(sf::RenderTarget& window); 
private:
	int actions_left{ 0 };
	const std::string m_name; 
	double average_hp{ 0 };
	sf::Text m_text;
	sf::Text m_titletext; 
	sf::Font m_textfont; 
	sf::Font m_titlefont; 
	float avg_hp{}; 
	sf::RectangleShape hp_bar{};
	sf::RectangleShape hp_outter{};
};