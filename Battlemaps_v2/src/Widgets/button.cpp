#include "button.h"



Button::Button() {
	m_font.loadFromFile(font_paths[0]); 
	text.setString(""); 
	text.setFont(m_font); 
	text.setCharacterSize(25U); 
	text.setFillColor(sf::Color::Black); 
	outline_rectangle.setSize(sf::Vector2f{ 400.0f, 200.0f } );
	outline_rectangle.setFillColor(sf::Color::White); 
	outline_rectangle.setOutlineColor(sf::Color::Black); 
	outline_rectangle.setOutlineThickness(2.0f); 
	std::cout << "Default button created\n"; 
}

Button::Button(sf::RenderWindow& window, int x, int y, float width, float height, const char* descr)
{
	float cell_size_x = static_cast<float>(window.getSize().x) / GRID_SIZE_X;
	float cell_size_y = static_cast<float>(window.getSize().y) / GRID_SIZE_Y;
	m_font.loadFromFile(font_paths[0]);
	outline_rectangle.setOutlineThickness(2.0f); 
	outline_rectangle.setFillColor(sf::Color::Yellow); 
	outline_rectangle.setOutlineColor(sf::Color::Black); 
	outline_rectangle.setSize(sf::Vector2f{ width , height }); 
	outline_rectangle.setPosition(x * cell_size_x, y * cell_size_y);
	text.setString(descr);
	text.setCharacterSize(DEFAULT_CHAR_SIZE); 	 
	text.setFont(m_font); 
	text.setFillColor(sf::Color::Black); 
	text.setPosition(x * cell_size_x, y * cell_size_y); 
	std::cout << "Button created...\n";
}


void Button::setFont(sf::Font& font)
{
	text.setFont(font); 
}

void Button::setTextSize(unsigned int size)
{
	text.setCharacterSize(size);
}

void Button::setTextString(const char* descr)
{
	text.setString(descr); 
}


void Button::setPosition(Grid& grid , sf::Vector2f new_pos)
{	 
	outline_rectangle.setPosition(new_pos); 
	sf::Vector2f offset = this->getTextOffset(grid); 
	text.setPosition(sf::Vector2f{ new_pos.x + offset.x  , new_pos.y + 0.8f* offset.y});
}

void Button::setRectSize(sf::Vector2f size)
{
	outline_rectangle.setSize(size); 
}

void Button::setRectOutlineThickness(float thickness)
{
	outline_rectangle.setOutlineThickness(thickness); 
}

void Button::setRectFillColor(const sf::Color& color)
{
	outline_rectangle.setFillColor(color); 
}

bool Button::contains(sf::Vector2f position)
{
	return (outline_rectangle.getGlobalBounds().contains(position));
}

void Button::draw(sf::RenderWindow& window)
{
	window.draw(outline_rectangle); 
	window.draw(text); 	
}


sf::Vector2f Button::getTextOffset(Grid& grid)
{
	float text_width = text.getGlobalBounds().width; 
	float text_height = text.getGlobalBounds().height; 
	//std::cout << "text width is : " << text_width << " and height is : " << text_height << "\n";
	float diff_x = outline_rectangle.getGlobalBounds().width - text_width;
	float diff_y = outline_rectangle.getGlobalBounds().height - text_height;
	return (sf::Vector2f{ diff_x / 2.0f , diff_y / 2.0f }); 
}

sf::FloatRect Button::getGlobalBounds()
{
	return outline_rectangle.getGlobalBounds(); 
}
