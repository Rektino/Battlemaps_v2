#include "Dashboard.h"


Dashboard::Dashboard() = default;

Dashboard::Dashboard(const int actions, const int pieces, const double avg_hp)
	:actions_left(actions), pieces_alive(pieces), average_hp(avg_hp)
{
	m_font.loadFromFile(font_paths[0]);
	m_text.setFont(m_font);	
}

//updates player's actions left for this turn	
void Dashboard::updateActions(int actionsLeft)
{
	actions_left = actionsLeft;
}

void Dashboard::updatePiecesAlive(int piecesAlive)
{
	pieces_alive = piecesAlive;
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

void Dashboard::move_text(sf::Vector2f pos_vector2f)
{
	m_text.setPosition(pos_vector2f); 
}

void Dashboard::draw(sf::RenderTarget& window)
{
	window.draw(m_text); 
}

std::string Dashboard::getInfoAsString() const {
	std::stringstream ss;
	ss << "PLAYER INFO\n"<< "\n";  //should be replaced with the player's username
	ss << "Actions Left: " << actions_left << "\n";
	ss << "Pieces Alive: " << pieces_alive << "\n";
	ss << "Average HP: " << average_hp << "\n";
	//std::cout << "Got info as str for dashboard: " << ss.str() << "\n"; 
	return ss.str();
}