// Battlemaps_v2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Grid.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(1400, 800), "BattleMaps", sf::Style::Close);
    Grid my_grid(window);     
    while (window.isOpen())
    {
        window.clear(sf::Color(255, 245, 220));
        my_grid.draw(window); 
        window.display();
        sf::Event event; 
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                std::cout << "CLOSED !!!";
                window.close();
            }
        }
    }


    return 0; 
}
