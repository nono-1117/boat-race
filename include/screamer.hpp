
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> // Pour le son
#include <experimental/random>
#include <memory>

class Screamer: public sf::Drawable {
public:
    static std::vector<std::shared_ptr<Screamer>> all;
    static void show(const sf::Texture&, const sf::SoundBuffer&);
    static void updateall();
    static void drawAll(sf::RenderTarget& target);

    Screamer() = delete;
    Screamer(Screamer&) = delete;
    Screamer& operator=(Screamer&) = delete;

    bool update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(sprite, states);
    };
private:
    Screamer(const sf::Texture&, const sf::SoundBuffer&);

    sf::Sprite sprite;
    sf::Sound s;

    float alpha;

    sf::Clock clock;
};
