
#include <experimental/random>

#include "startscreen.hpp"
#include "properties.hpp"

using namespace std::experimental;

StartScreen::StartScreen(const sf::Font& font):
    title("COURSE DE BATEAU", font, 50),
    startbutton("Commencer", font),
    boatoption{
        BoatOption(font, 1, 5, true),
        BoatOption(font, 2),
        BoatOption(font, 3),
        BoatOption(font, 4)
    }
{
    // button de lancement
    startbutton.setPosition(sf::Vector2f(
        SCREEN_WIDTH / 2.f - startbutton.getSize().x / 2.f,
        (51.f / 60.f) * SCREEN_HEIGHT)
    ),

    // titre
    title.setFillColor(sf::Color::White);
    title.setPosition(SCREEN_WIDTH / 2.f - title.getGlobalBounds().width / 2.f, (1.f / 12.f) * SCREEN_HEIGHT);
}