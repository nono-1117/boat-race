
#include "cannonball.hpp"
#include <cmath>

inline constexpr int CANNONBALL_DISTANCE = 400;

std::vector<std::shared_ptr<Cannonball>> Cannonball::all;

static double distance(const sf::Vector2f& a, const sf::Vector2f& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}

Cannonball::Cannonball(const sf::Vector2f& starting_pos, const sf::Vector2f& pdirection):
    st_pos(starting_pos), d(pdirection)
{
    shape.setRadius(5.0f);
    shape.setPosition(starting_pos);
    shape.setFillColor(sf::Color::Black);
}

bool Cannonball::update()
{
    setPosition(sim::common::Vector2(shape.getPosition().x + d.x, shape.getPosition().y + d.y));
    if(distance(st_pos, shape.getPosition()) >= CANNONBALL_DISTANCE){
        return true;
    }
    return false;
}

Cannonball& Cannonball::create(const sf::Vector2f& starting_pos, const sf::Vector2f& pdirection){
    std::shared_ptr<Cannonball> c = std::shared_ptr<Cannonball>(new Cannonball(starting_pos, pdirection));
    all.push_back(c);

    return *c;
}

void Cannonball::drawAll(sf::RenderTarget& target) {
    auto it = all.begin();
    while (it != all.end()) {
        if ((*it)->update()) {
            it = all.erase(it);
        } else {
            target.draw(**it);
            ++it;
        }
    }
}
