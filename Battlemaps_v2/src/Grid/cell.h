#pragma once
#include "Piece.h"
#include <SFML/Graphics.hpp>
#include "global_constants.h"
#include <iostream>

/*
Defines the cells of the playable game map, where pieces move/attack or get placed to. 
*/
class cell
{
public : 
	cell()= delete ;
	cell(sf::RenderWindow& window,  int x, int y);
	std::shared_ptr<Piece> getPiece() { return piece_here;  };
	void draw(sf::RenderWindow& window); 
	sf::Vector2f getPosition(); 
	float getHeight(); 
	float getWidth(); 
private : 
	int posX{}; 
	int posY{}; 
	sf::Vector2f cell_size; 
	std::shared_ptr<Piece> piece_here;
	sf::RectangleShape m_rectangle;
	sf::CircleShape m_circle; 
};

