
#pragma once

#include "SFML/Graphics.hpp"
#include <functional>

class BareButton: public sf::Drawable {
protected:
    sf::RectangleShape box;
    bool enabled;
    std::function<void()> on_click;

public:
    static std::vector<BareButton*> all;
    static void checkAllClicks(const sf::Vector2f& mousePos);

    BareButton();
    virtual ~BareButton() { all.erase(std::find(all.begin(), all.end(), this)); }
    BareButton(const sf::Vector2f& pos);
    BareButton(const BareButton&) = delete;
    BareButton& operator=(const BareButton&) = delete;

    inline void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(box, states);
    };

    inline bool contains(const sf::Vector2f& pos)
    {
        return box.getGlobalBounds().contains(pos);
    }

    virtual inline BareButton& setPosition(const sf::Vector2f pos)
    {
        box.setPosition(pos);
        return *this;
    }
    inline BareButton& setFillColor(const sf::Color& color) { box.setFillColor(color); return *this; }
    virtual inline BareButton& setSize(const sf::Vector2f& size)
    {
        box.setSize(size);
        return *this;
    }
    inline BareButton& set_on_click(const std::function<void()>& f) { on_click = f; return *this; }
    inline const sf::Vector2f& getPosition() const { return box.getPosition(); }
    inline const sf::Vector2f& getSize() const { return box.getSize(); }
    inline BareButton& enable() { enabled = true; return *this; }
    inline BareButton& disable() { enabled = false; return *this; }
};
