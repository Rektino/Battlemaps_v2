#include <SFML/Graphics.hpp>
#include "global_constants.h"
#include <iostream>
#include "Grid.h"

class Menu_icon {
public:
	Menu_icon(sf::RenderWindow& window , Grid& grid);
	void draw(sf::RenderWindow& window);
private:
	sf::Sprite m_sprite;
	sf::Texture m_texture; 
	sf::Text m_text; 
	sf::Font m_font; 	
};

class Help_icon {
public:
	Help_icon(sf::RenderWindow& window, Grid& grid);
	void draw(sf::RenderWindow& window);
private:
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::Text m_text;
	sf::Font m_font;
};