#pragma once
#include <iostream> 
#include <string>
#include <SFML/Graphics.hpp>
#include "global_constants.h"
#include <cassert>
#include "Grid.h"

class Button {
public:
	Button() ; 
	Button(sf::RenderWindow& window , int x, int y, float width, float height, const char* text); 	
	void setFont(sf::Font& font); 
	void setTextSize(unsigned int size); 
	void setTextString(const char* descr);	 
	void setPosition(Grid& grid ,  sf::Vector2f new_pos);
	void setRectSize(sf::Vector2f size); 
	void setRectOutlineThickness(float thickness); 
	void setRectFillColor(const sf::Color& color); 	
	bool contains(sf::Vector2f position); 
	void draw(sf::RenderWindow& window); 
	sf::Vector2f getTextOffset(Grid& grid);
private:
	sf::Font m_font; 
	sf::Text text; 
	sf::RectangleShape outline_rectangle; 	
};