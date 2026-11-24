
#include "barebutton.hpp"
#include <iostream>

std::vector<BareButton*> BareButton::all;

BareButton::BareButton(const sf::Vector2f& pos):
    box(sf::Vector2f(200, 60)), enabled(false)
{
    box.setFillColor(sf::Color(100, 100, 250));
    box.setPosition(pos);

    all.push_back(this);
}

BareButton::BareButton():
    box(sf::Vector2f(200, 60)), enabled(false)
{
    box.setFillColor(sf::Color(100, 100, 250));
    all.push_back(this);
}

void BareButton::checkAllClicks(const sf::Vector2f& mousePos) {
    for (BareButton* btn : BareButton::all) {
        if (btn->contains(mousePos) && btn->enabled) {
            btn->on_click();
        }
    }
}
