#include "Dashboard.h"


Dashboard::Dashboard() = default;


Dashboard::Dashboard(const std::string player_name , const int actions, const double avg_hp )
	:m_name(player_name) , actions_left(actions), average_hp(avg_hp)
{
	m_textfont.loadFromFile(font_paths[0]);
	m_text.setFont(m_textfont);		
	m_titlefont.loadFromFile(font_paths[3]); 
	m_titletext.setFont(m_titlefont); 
	m_titletext.setFillColor(sf::Color(64U, 64U, 64U)); 
	m_titletext.setCharacterSize(DEFAULT_TITLES_SIZE + 10);
	m_titletext.setString(m_name); 
	hp_bar.setSize(sf::Vector2f(2*HP_BAR_SIZE_X, 2*HP_BAR_SIZE_Y));
	hp_bar.setFillColor(sf::Color(102, 255, 102));
	hp_outter.setSize(sf::Vector2f(2*HP_BAR_SIZE_X, 2*HP_BAR_SIZE_Y));
	hp_outter.setFillColor(sf::Color::Transparent);
	hp_outter.setOutlineThickness(2.0f);
	hp_outter.setOutlineColor(sf::Color::Black);
}

//updates player's actions left for this turn	
void Dashboard::updateActions(int actionsLeft)
{
	actions_left = actionsLeft;
}

void Dashboard::updateAvgHp(double avgHP)
{
	average_hp = avgHP;
}

void Dashboard::set_text(std::string new_text , unsigned charSize , sf::Color color )
{
	m_text.setString(new_text);
	m_text.setCharacterSize(charSize); 	
	m_text.setFillColor(color); 
}

void Dashboard::set_avg_hp(float hp, float max)
{
	float percentage = hp / max; 
	const sf::Vector2f hp_scale = { 1.0f , percentage };
	hp_bar.setScale(hp_scale); 
	if (percentage < 0.0) {
		percentage = 0.0;
	}
	if (percentage < 0.25) {
		hp_bar.setFillColor(sf::Color(253, 51, 28));
	}
	else if (percentage < 0.5) {
		hp_bar.setFillColor(sf::Color(226, 100, 28));
	}
	else if (percentage < 0.85) {
		hp_bar.setFillColor(sf::Color(230, 205, 50));
	}
}

void Dashboard::move_text(sf::Vector2f pos_vector2f)
{
	m_titletext.setPosition({ pos_vector2f.x , pos_vector2f.y - 70.0f }); 
	m_text.setPosition(pos_vector2f); 
	hp_bar.setPosition({ pos_vector2f.x + m_titletext.getGlobalBounds().width + 50.0f ,
						 pos_vector2f.y - 70.0f});
	hp_outter.setPosition({ pos_vector2f.x + m_titletext.getGlobalBounds().width + 50.0f,
						 pos_vector2f.y - 70.0f });
}

void Dashboard::draw(sf::RenderTarget& window)
{
	window.draw(m_text); 
	window.draw(m_titletext); 
	window.draw(hp_bar); 
	window.draw(hp_outter); 
}

std::string Dashboard::getInfoAsString() const {
	std::stringstream ss;
	ss << "Actions Left: " << actions_left << "\n\n";
	ss << "Average HP: " << average_hp << "\n";
	//std::cout << "Got info as str for dashboard: " << ss.str() << "\n"; 
	return ss.str();
}