
#include <experimental/random>

#include "boatoption.hpp"
#include "properties.hpp"

using namespace std::experimental;
static const char* skin_names[NB_SKIN] = {
    "RIDICULOUS", "NORMAL", "OUTRAGEOUSLY HARD"
};

BoatOption::BoatOption(const sf::Font& font, const int& i, const int& padx, const bool& _active):
    color_choice(), skin_choice("", font, 16, 1),
    title("", font, 16),
    quit("Retirer le bateau", font, 16),
    boat(BoatPlayer::create(0)),
    addplayerboat("Ajouter un joueur", font, 16),
    addbotboat("Ajouter un bot", font, 16),
    _is_player(true),
    active(_active)
{
    const int largeur_grand_rectangle = SCREEN_WIDTH / NB_BOAT_MAX;
    const float center_x = largeur_grand_rectangle * i - (largeur_grand_rectangle / 2);

    // ADD PLAYER BUTTON
    addplayerboat.set_on_click([this, i](){
        add_boat();
        _is_player = true;
        title.setString("Joueur n" + std::to_string(i));

    }).setSize({150, 30}).setPosition({center_x - (addplayerboat.getSize().x / 2), (7.f / 12.f) * SCREEN_HEIGHT});

    // ADD BOT BUTTON
    addbotboat.set_on_click([this, i](){
        add_boat();
        _is_player = false;
        title.setString("Robot n" + std::to_string(i));

    }).setSize({150, 30}).setPosition({center_x - (addbotboat.getSize().x / 2), (8.f / 12.f) * SCREEN_HEIGHT});

    // QUIT BUTTON
    quit.set_on_click([this](){
        withdraw_boat();

    }).setSize({150, 30}).setPosition({center_x - (quit.getSize().x / 2), (47.f / 60.f) * SCREEN_HEIGHT});

    const int espace_utilisable = largeur_grand_rectangle - 2 * padx;

    // RADIOBUTTON COLOR_CHOICE
    float largeur_petit_rect = espace_utilisable / color_choice.size();
    for(unsigned int j = 0U; j < color_choice.size(); j++){
        sf::Color color(randint(0, 255), randint(0, 255), randint(0, 255));

        float x = (largeur_grand_rectangle * (i - 1)) + padx + j * largeur_petit_rect;

        color_choice[j].value = color;
        color_choice[j].button.setSize({largeur_petit_rect, 25})
        .setFillColor(color)
        .setPosition({x, (43.f / 60.f) * SCREEN_HEIGHT});
    }

    color_choice.set_on_update([this](const sf::Color& new_color){
        boat.setFillColor(new_color);
    });

    // RADIOBUTTON SKIN_CHOICE
    largeur_petit_rect = espace_utilisable / skin_choice.size();
    for(unsigned int j = 0U; j < skin_choice.size(); j++){
        float x = (largeur_grand_rectangle * (i - 1)) + padx + j * largeur_petit_rect;

        skin_choice[j].value = {.2f + j * .4f,.2f + j * .4f};
        skin_choice[j].button.setSize({largeur_petit_rect, 25})
        .setString(skin_names[j])
        .setCharacterSize(14 - (j * 3))
        .setPosition({x, (40.f / 60.f) * SCREEN_HEIGHT});
    }

    skin_choice.set_on_update([this](const sf::Vector2f& boattype){
        boat.setScale(boattype);
    });

    // BOAT
    boat.setPosition(sf::Vector2f(center_x, (5.f / 12.f) * SCREEN_HEIGHT));

    title.setPosition({
        center_x,
        (3.f / 12.f) * SCREEN_HEIGHT
    });
}