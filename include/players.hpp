
#pragma once

#include <memory>
#include <iostream>

#include "boat.hpp"
#include "properties.hpp"

class Players {
private:
    std::unique_ptr<Boat> players[NB_BOAT_MAX];

public:
    Players(): players{nullptr, nullptr, nullptr, nullptr} {};
    using iterator = std::unique_ptr<Boat>*;
    using const_iterator = const std::unique_ptr<Boat>*;
    inline iterator begin() { return &players[0]; }
    inline iterator end()   { return &players[NB_BOAT_MAX]; }

    inline const_iterator begin() const { return &players[0]; }
    inline const_iterator end()   const { return &players[NB_BOAT_MAX]; }
    inline std::size_t size() { return NB_BOAT_MAX; }
    inline iterator erase(const iterator& it) {
        (*it) = nullptr;
        return it + 1;
    }

    inline std::unique_ptr<Boat>& operator[](const unsigned int& index)
    {
        if(index < NB_BOAT_MAX) return players[index];
        else {
            std::cerr << "Tentative d'accès à un joueur qui n'existe pas: " << index << std::endl;
            exit(0);
        }
    }

    inline void reset()
    {
        for(std::unique_ptr<Boat>& boat: *this) if(boat) boat->reset();
    }

    inline void update()
    {
        for(std::unique_ptr<Boat>& boat: *this) if(boat) boat->update();
    }

    inline void draw(sf::RenderWindow& window)
    {
        for(std::unique_ptr<Boat>& boat: *this) if(boat) window.draw(*boat);
    }

    inline void handle_controls()
    {
        for(std::unique_ptr<Boat>& boat: *this) if(boat) boat->handle_controls();
    }
};