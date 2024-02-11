#pragma once

#include <SFML/Graphics.hpp>
#include "global_constants.h"
#include <iostream>
#include <memory>
#include <cassert>
#include "Piece.h"

/*class Piece; /*fwd declaration of piece because of circular dependency found between Grid and Piece classes.
This informs the compiler about the existence of Piece class, which will be defined at another point. Because if I
include the Piece.h header here instead, the compilation will fail, since Piece.h includes the grid which includes the cell
which does not know about the Piece :D*/


/*
Defines the cells of the playable game map, where pieces move/attack or get placed to. 
*/
class cell
{
public : 
	cell()= delete ;
	cell(sf::RenderWindow& window,  int x, int y);
	std::shared_ptr<Piece>& getPiece() { return piece_here;  };
	void setPiece(std::shared_ptr<Piece> piece) {		
		piece_here = piece;  
	}
	void clean() { piece_here = nullptr;  }
	void draw(sf::RenderWindow& window);
	void activate_selection(sf::Color color = sf::Color::Green);
	void deactivate(); 
	bool is_active() { return activated;  }
	sf::Vector2f getPosition(); 
	float getHeight(); 
	float getWidth(); 
	bool contains(sf::Vector2f position_f); 
private : 
	int posX{}; 
	int posY{}; 
	bool activated{ false } ;
	sf::Vector2f cell_size; 
	std::shared_ptr<Piece> piece_here;
	sf::RectangleShape m_rectangle;
	sf::CircleShape m_circle; 
};

