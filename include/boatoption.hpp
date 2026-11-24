
#pragma once

#include "SFML/Graphics.hpp"
#include "radiobutton.hpp"
#include "button.hpp"
#include <iostream>
#include "boatplayer.hpp"

inline constexpr int NB_COLOR_OPTION = 10;
inline constexpr int NB_SKIN = 3;

class BoatOption: public sf::Drawable {
private:
    RadioButtonG<NB_COLOR_OPTION, BareButton, sf::Color> color_choice;
    RadioButton<NB_SKIN, sf::Vector2f> skin_choice;
    sf::Text title;
    Button quit;
    BoatPlayer boat;
    Button addplayerboat;
    Button addbotboat;

    bool _is_player;

    /// @brief only to know if this boatoption is added (and so a page with boat configuration will be drawn) or not
    bool active;

public:
    /// @param font font of the text
    /// @param screen_width the screen's width
    /// @param i index of the boatoption on screen [1-NB_COLOR_OPTION]
    /// @param padx the pad between the buttons and the border
    BoatOption(const sf::Font& font, const int& i, const int& padx=5, const bool& _active=false);
    BoatOption(const BoatOption&) = delete;
    BoatOption& operator=(const BoatOption&) = delete;

    inline void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        if(active){
            for(auto& rb: color_choice) target.draw(rb.button, states);
            for(auto& rb: skin_choice) target.draw(rb.button, states);
            target.draw(quit, states);
            target.draw(boat, states);
            target.draw(title, states);
        } else {
            target.draw(addplayerboat, states);
            target.draw(addbotboat, states);
        }
    };

    /// @brief Get the decided boatcolor for the player i
    /// @return the color chosen
    inline const sf::Color& get_boatcolor() const { return color_choice.get_selected(); }
    inline const sf::Vector2f& getScale() const { return skin_choice.get_selected(); }

    inline void withdraw_boat()
    {
        active = false;
        for(auto& rb: color_choice) rb.button.disable();
        for(auto& rb: skin_choice) rb.button.disable();
        quit.disable();
        addplayerboat.enable();
        addbotboat.enable();
    }
    
    inline void add_boat()
    {
        active = true;
        for(auto& rb: color_choice) rb.button.enable();
        for(auto& rb: skin_choice) rb.button.enable();
        quit.enable();
        addplayerboat.disable();
        addbotboat.disable();
    }

    inline void disable()
    {
        for(auto& rb: color_choice) rb.button.disable();
        for(auto& rb: skin_choice) rb.button.disable();
        quit.disable();
        addplayerboat.disable();
        addbotboat.disable();
    }

    inline void enable()
    {
        if(active) {
            for(auto& rb: color_choice) rb.button.enable();
            for(auto& rb: skin_choice) rb.button.enable();
            quit.enable();
        } else {
            addplayerboat.enable();
            addbotboat.enable();
        }
    }

    inline bool is_player() const { return _is_player; }
    inline bool is_active() const { return active; }

    inline void turnboat()
    {
        boat.TurningLeft();
    }

    inline void update()
    {
        boat.update();
    }
};
