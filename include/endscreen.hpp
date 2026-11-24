
#pragma once

#include "SFML/Graphics.hpp"
#include "button.hpp"

class EndScreen: public sf::Drawable {
private:
    sf::Text title;
    sf::Text instruction;
    Button restartbutton;

public:
    EndScreen(const sf::Font&);
    inline void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(title, states);
        target.draw(instruction, states);
        target.draw(restartbutton, states);
    };

    inline EndScreen& set_restart_f(const std::function<void()>& f) { restartbutton.set_on_click(f); return *this; }
    inline void disable()
    {
        restartbutton.disable();
    }

    inline void enable(const std::string& msg)
    {
        instruction.setString(msg + "\nAppuyez sur Echap pour quitter");
        restartbutton.enable();
    }
};
