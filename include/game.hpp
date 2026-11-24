
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <experimental/random>

#include "finishline.hpp"
#include "players.hpp"
#include "obstacle.hpp"
#include "endscreen.hpp"
#include "startscreen.hpp"

enum class GameMode {START_SCREEN, END_SCREEN, PLAYING};

class Game {
private:
    //////////// Donnés en paramètres //////////
    sf::RenderWindow& window;
	GameMode playing;
    bool screamer;

    ///////////// Gérés par la classe //////////

    /// @brief écran de début de jeu
    StartScreen start;

    /// @brief écran de fin de jeu
    EndScreen end;

    /// @brief Ligne d'arrivée
    FinishLine finishline;

    /// @brief Les 4 joueurs, présents ou non
    Players players;

    /// @brief La liste des textures qui apparaissent sur l'écran lors d'un "kill"
    std::vector<sf::Texture> tv;

    /// @brief Le son qui se lance lors d'un "kill"
    sf::SoundBuffer sb;

    /// @brief la police principale
    sf::Font font;

    /// @brief liste d'obstacles
    ObstacleVect ov;

public:
    Game(sf::RenderWindow& _window, const sf::Font& font, const bool& _screamer, const GameMode& _playing = GameMode::START_SCREEN);
    void mainloop();
};
