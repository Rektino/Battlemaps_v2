#include "cell.h"

cell::cell(sf::RenderWindow& window ,int x, int y) : posX(x) , posY(y)
{
	piece_here = nullptr; 
	
	sf::Vector2f cell_size(
		static_cast<float>(window.getSize().x) / GRID_SIZE_X,
		static_cast<float>(window.getSize().y) / GRID_SIZE_Y
	);
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
		float rect_center_x = x * cell_size.x + m_rectangle.getGlobalBounds().width / 2.0f;
		float rect_center_y = y * cell_size.y + m_rectangle.getGlobalBounds().height / 2.0f;
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

bool cell::contains(sf::Vector2f position_f)
{
	return (m_rectangle.getGlobalBounds().contains(position_f)) ;
}
