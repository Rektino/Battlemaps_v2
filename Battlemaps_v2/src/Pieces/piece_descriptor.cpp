#include "piece_descriptor.h"

piece_descriptor::piece_descriptor()
{
	std::cout << "Non-default piece_descriptor constructor called\n"; 
	title_font.loadFromFile(font_paths[2]); 	
	title_text.setCharacterSize(title_char_size); 
	title_text.setFont(title_font); 
	title_text.setFillColor(sf::Color::Black); 
	title_text.setPosition(1200, 250); 
	description_text.setCharacterSize(description_char_size);
	description_font.loadFromFile(font_paths[1]);
	description_text.setFont(description_font); 
	description_text.setFillColor(sf::Color::Black); 
	description_text.setPosition(1200, 320); 
	outline_rectangle.setFillColor(sf::Color::Transparent); 
	outline_rectangle.setOutlineColor(sf::Color::Magenta); 
	outline_rectangle.setOutlineThickness(2.0f); 
	outline_rectangle.setSize({ description_text.getGlobalBounds().width + 50.0f, 
								description_text.getGlobalBounds().height + title_text.getGlobalBounds().height  + 90.0f});
	outline_rectangle.setPosition(title_text.getPosition().x - 20.0f , title_text.getPosition().y - 20.0f); 
}

void piece_descriptor::draw(sf::RenderTarget& window)
{
	if (!is_hidden) {
		window.draw(title_text); 
		window.draw(description_text); 
		window.draw(outline_rectangle);
		window.draw(m_sprite); 
	}
}

void piece_descriptor::set_all_text(const std::string piece_type, const std::string piece_description,
	const int hp, const int dmg, const int attacks_left, const int moves_left)
{
	title_text.setString(piece_type);
	std::stringstream ss_all_data;
	ss_all_data << piece_description << "\n\nHP : " << hp << "\nDMG : " << dmg << "\n---------------\n" << 
		"Attacks left : " << attacks_left << "\nMoves left : " << moves_left <<"\n";
	auto all_details_str = ss_all_data.str();
	description_text.setString(all_details_str);
	outline_rectangle.setSize({ description_text.getGlobalBounds().width + 50.0f,
								description_text.getGlobalBounds().height + title_text.getGlobalBounds().height + 90.0f });
	m_sprite.setPosition({ title_text.getPosition().x + title_text.getGlobalBounds().width + 10.0f ,
						  title_text.getPosition().y });
}

void piece_descriptor::set_sprite_view(sf::Sprite piece_sprite)
{
	m_sprite = piece_sprite;	
}

void piece_descriptor::set_position(sf::Vector2f position_vector2f)
{
	title_text.setPosition(position_vector2f); 
	description_text.setPosition({ position_vector2f.x , position_vector2f.y + 70.0f }); 
	outline_rectangle.setPosition(title_text.getPosition().x - 20.0f, title_text.getPosition().y - 20.0f);
	m_sprite.setPosition({ title_text.getPosition().x + title_text.getGlobalBounds().width + 10.0f ,
						  title_text.getPosition().y });
}

void piece_descriptor::make_visible()
{
	is_hidden = false; 
}

void piece_descriptor::hide()
{
	is_hidden = true; 
}
