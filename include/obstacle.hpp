
#pragma once

#include <vector>
#include <experimental/random>

#include "entity.hpp"
#include "physics/common.h"
#include "properties.hpp"

using namespace std::experimental;

class Obstacle: public Entity<sf::RectangleShape> {
public:
    Obstacle(const sf::Vector2f&);
    inline void setPosition(const sim::common::Vector2& p)
    {
        Entity::setPosition(p);
    }
};

class ObstacleVect: public std::vector<Obstacle> {
public:
    inline void inst(const int& nb)
    {
		for(int i = 0; i < nb; ++i)
        {
            this->push_back(Obstacle(sf::Vector2f(randint(200U, SCREEN_WIDTH), randint(0U, SCREEN_HEIGHT))));
        }
    }

    inline void reset()
    {
        for(Obstacle& o: *this)
        {
            o.setPosition(sim::common::Vector2(randint(200U, SCREEN_WIDTH), randint(0U, SCREEN_HEIGHT)));
        }
    }
};
