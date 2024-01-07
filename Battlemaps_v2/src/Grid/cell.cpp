#include "cell.h"

cell::cell(sf::RenderWindow& window ,int x, int y) : posX(x) , posY(y)
{
	piece_here = nullptr; 
	unsigned window_width = window.getSize().x;
	unsigned window_height = window.getSize().y;
	cell_size = { static_cast<float>(window_width / GRID_SIZE_X),
				 static_cast<float>(window_height / GRID_SIZE_Y) };
	m_rectangle.setSize(cell_size);
	m_rectangle.setFillColor(sf::Color::Transparent);
	m_rectangle.setOutlineThickness(0.5f);
	m_rectangle.setOutlineColor(sf::Color::Black);
	m_rectangle.setPosition(x * cell_size.x, y * cell_size.y); 
	if (x < MAPSIZE) {
		m_circle.setRadius(CIRCLE_RADIUS);
		m_circle.setPointCount(POINTS_COUNT);
		m_circle.setOutlineThickness(OUTLINE_THICKNESS);
		m_circle.setOutlineColor(sf::Color::Black);
		m_circle.setFillColor(sf::Color(165, 180, 255));
		float rect_center_x = x * cell_size.x + m_rectangle.getGlobalBounds().width / 2.0;
		float rect_center_y = y * cell_size.y + m_rectangle.getGlobalBounds().height / 2.0;
		m_circle.setPosition(rect_center_x - CIRCLE_RADIUS, rect_center_y - CIRCLE_RADIUS);
	}	
	std::cout << "Created cell x,y = " << x << "," << y << " positioned at " << x * cell_size.x << " , " << y * cell_size.y << "\n"; 
}

void cell::draw(sf::RenderWindow& window)
{
	window.draw(m_rectangle); 
	window.draw(m_circle); 
}

sf::Vector2f cell::getPosition()
{
	return m_rectangle.getPosition(); 
}

float cell::getHeight()
{
	return m_rectangle.getGlobalBounds().width ; 
}

float cell::getWidth()
{
	return m_rectangle.getGlobalBounds().height ; 
}
