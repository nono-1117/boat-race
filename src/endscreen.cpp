
#include "endscreen.hpp"
#include "properties.hpp"

EndScreen::EndScreen(const sf::Font& font):
    title("Fin du jeu", font, 50),
    instruction("Appuyez sur Echap pour quitter", font, 24),
    restartbutton("Recommencer", font)
{
    // Bouton pour retourner au titre
    restartbutton.setPosition(sf::Vector2f(
        SCREEN_WIDTH / 2.f - restartbutton.getSize().x / 2.f,
        (2.f / 3.f) * SCREEN_HEIGHT)
    );

    // Titre "Fin du jeu"
    title.setFillColor(sf::Color::White);
    title.setPosition(SCREEN_WIDTH / 2.f - title.getGlobalBounds().width / 2.f, (1.f / 3.f) * SCREEN_HEIGHT);
    
    // Message secondaire
    instruction.setFillColor(sf::Color(200, 200, 200));
    instruction.setPosition(SCREEN_WIDTH / 2.f - instruction.getGlobalBounds().width / 2.f, (3.f / 6.f) * SCREEN_HEIGHT);
}