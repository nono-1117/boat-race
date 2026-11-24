
#include "button.hpp"

Button::Button(const sf::Vector2f& pos, const std::string& text_str, const sf::Font& font, const int& font_size):
    BareButton(pos), text(text_str, font, font_size)
{
    text.setFillColor(sf::Color::White);
    center_text();
}

Button::Button(const std::string& text_str, const sf::Font& font, const int& font_size):
    BareButton(), text(text_str, font, font_size)
{
    text.setFillColor(sf::Color::White);
    center_text();
}
