
#pragma once

#include "SFML/Graphics.hpp"
#include "barebutton.hpp"

class Button: public BareButton {
private:
    sf::Text text;

public:
    /// @brief if wanted, button without text exists in the BareButton class
    /// @param text string to put in the button
    /// @param font font for the text
    /// @param pos position of the button
    Button(const sf::Vector2f& pos, const std::string& text, const sf::Font& font, const int& font_size=24);
    Button(const std::string& text, const sf::Font& font, const int& font_size=24);
    Button() = default;
    Button(const Button&) = delete;
    Button& operator=(const Button&) = delete;
    virtual ~Button() {}

    inline void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        BareButton::draw(target, states);
        target.draw(text, states);
    };

    inline void center_text()
    {
        text.setPosition(
            box.getPosition().x + box.getSize().x / 2.f - text.getGlobalBounds().width / 2.f,
            box.getPosition().y + box.getSize().y / 2.f - text.getGlobalBounds().height
        );
    }

    inline Button& setPosition(const sf::Vector2f pos) override
    { BareButton::setPosition(pos); center_text(); return *this; }

    inline Button& setSize(const sf::Vector2f& size) override
    { BareButton::setSize(size); center_text(); return *this; }

    inline Button& setString(const sf::String& string)
    { text.setString(string); return *this; }

    inline Button& setFont(const sf::Font& font)
    { text.setFont(font); return *this; }

    inline Button& setCharacterSize(const unsigned int& size)
    { text.setCharacterSize(size); return *this; }
};
