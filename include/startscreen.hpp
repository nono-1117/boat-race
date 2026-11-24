
#pragma once

#include <iostream>

#include "SFML/Graphics.hpp"
#include "button.hpp"
#include "boatoption.hpp"
#include "properties.hpp"

class StartScreen: public sf::Drawable {
private:
    sf::Text title;
    Button startbutton;
    BoatOption boatoption[NB_BOAT_MAX];

public:
    StartScreen(const sf::Font&);
    inline void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(title, states);
        target.draw(startbutton, states);
        for(unsigned int i = 0U; i < NB_BOAT_MAX; i++) target.draw(boatoption[i], states);
    };
    inline BoatOption& get_boat_option(const unsigned int& index)
    {
        if(index < NB_BOAT_MAX) return boatoption[index];
        else {
            std::cerr << "IndexError: Tentative d'accès à des options de bâteau non existantes à l'index : " << index << std::endl;
            exit(1);
        }
    }
    inline void set_start_f(const std::function<void()>& f) { startbutton.set_on_click(f); }
    inline void disable()
    {
        for(unsigned int i = 0U; i < NB_BOAT_MAX; i++) boatoption[i].disable();
        startbutton.disable();
    }

    inline void enable()
    {
        for(unsigned int i = 0U; i < NB_BOAT_MAX; i++) boatoption[i].enable();
        startbutton.enable();
    }
};
