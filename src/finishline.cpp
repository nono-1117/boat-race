
#include <iostream>

#include "finishline.hpp"
#include "properties.hpp"

FinishLine::FinishLine()
{   
    sf::Vector2f size(25, SCREEN_HEIGHT);
    shape.setOrigin(size / 2.0f);
    shape.setSize(size);
    shape.setPosition((15.f / 16.f) * SCREEN_WIDTH, (3.f / 6.f) * SCREEN_HEIGHT);
    
    if (!texture.loadFromFile("oui.png")) {
        std::cerr << "Erreur : impossible de charger la texture" << std::endl;
    }

    shape.setTexture(&texture);
}

FinishLine::~FinishLine()
{

}
