
#pragma once

#include "entity.hpp"
#include <memory>

class Cannonball: public Entity<sf::CircleShape>
{
private:
    const sf::Vector2f st_pos;
    const sf::Vector2f d;
 
    Cannonball(const sf::Vector2f& starting_pos, const sf::Vector2f& pdirection);

public:
    static std::vector<std::shared_ptr<Cannonball>> all;
    Cannonball() = delete;
    Cannonball(const Cannonball&) = delete;
    Cannonball& operator=(const Cannonball&) = delete;

    virtual ~Cannonball() noexcept = default;

    static Cannonball& create(const sf::Vector2f& starting_pos, const sf::Vector2f& pdirection);

    // Retourne si le boulet doit être supprimé ou non 
    bool update();

    static void drawAll(sf::RenderTarget& target);
    inline static void delInst(const std::vector<std::shared_ptr<Cannonball>>::iterator& it) { all.erase(it); }
};
