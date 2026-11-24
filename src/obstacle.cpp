
#include <experimental/random>

#include "obstacle.hpp"
#include "properties.hpp"

Obstacle::Obstacle(const sf::Vector2f& p)
{
    using namespace std::experimental;
    sf::Vector2f size(randint(50, 100), randint(50, 100));
    shape.setOrigin(size / 2.0f);
    shape.setSize(size);
    shape.setPosition(randint(0U, SCREEN_WIDTH), randint(0U, SCREEN_HEIGHT));

    shape.setFillColor(sf::Color(80, 80, 120));  // bleu-gris
    shape.setPosition(p);
    
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color::Black);
}
