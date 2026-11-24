
#include "screamer.hpp"
#include <experimental/random>
#include <iostream>

std::vector<std::shared_ptr<Screamer>> Screamer::all;

Screamer::Screamer(const sf::Texture& t, const sf::SoundBuffer& sb):
    sprite(t), s(sb), alpha(255.0f), clock()
{

}

void Screamer::show(const sf::Texture& t, const sf::SoundBuffer& sound)
{
    std::shared_ptr<Screamer> s_ptr = std::shared_ptr<Screamer>(new Screamer(t, sound));
    Screamer& s = *s_ptr;

    s.sprite.setPosition(sf::Vector2f(std::experimental::randint(200, 600), std::experimental::randint(200, 400)));
    s.sprite.setRotation(std::experimental::randint(-25, 25));

    s.s.play();
    all.push_back(s_ptr);
}

void Screamer::updateall()
{
    auto it = all.begin();
    while (it != all.end()) {
        if ((*it)->update()) {
            it = all.erase(it);
        } else {
            ++it;
        }
    }
}

bool Screamer::update()
{
    // Fondu rapide, 185 semble optimal pour que le son ne s'arrête pas avant (sachant que les screamers sont libérés quand alpha = 0)
    alpha -= 100 * clock.restart().asSeconds(); 
    if (alpha <= 0) {
        alpha = 0;

        auto it = std::find_if(all.begin(), all.end(),
            [this](const std::shared_ptr<Screamer>& ptr) {
                return ptr.get() == this;
            });

        if (it != all.end()) {
            return true;
        }
    }

    sprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));
    return false;
}

void Screamer::drawAll(sf::RenderTarget& target) {
    for (const std::shared_ptr<Screamer>& c: all) {
        if(c) target.draw(*c);
    }
}
