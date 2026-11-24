
#pragma once

#include "entity.hpp"
#include "physics/physicsEngine.h"

class FinishLine: public Entity<sf::RectangleShape> {
public:
    FinishLine();
    ~FinishLine();

private:
    sf::Texture texture;
};