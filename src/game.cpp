
#include "game.hpp"

#include "boat.hpp"
#include "boatAI.hpp"
#include "screamer.hpp"

/// @brief fwd_key, bwd_key, left_key, right_key, shoot_left_key, shoot_right_key
static const sf::Keyboard::Key players_controls[4][6] = {
	{
		sf::Keyboard::Key::Z,
		sf::Keyboard::Key::S,
		sf::Keyboard::Key::Q,
		sf::Keyboard::Key::D,
		sf::Keyboard::Key::A,
		sf::Keyboard::Key::E
	},
	{
		sf::Keyboard::Key::T,
		sf::Keyboard::Key::G,
		sf::Keyboard::Key::F,
		sf::Keyboard::Key::H,
		sf::Keyboard::Key::R,
		sf::Keyboard::Key::Y
	},
	{
		sf::Keyboard::Key::I,
		sf::Keyboard::Key::K,
		sf::Keyboard::Key::J,
		sf::Keyboard::Key::L,
		sf::Keyboard::Key::U,
		sf::Keyboard::Key::O
	},
	{
		sf::Keyboard::Key::Numpad8,
		sf::Keyboard::Key::Numpad5,
		sf::Keyboard::Key::Numpad4,
		sf::Keyboard::Key::Numpad6,
		sf::Keyboard::Key::Numpad7,
		sf::Keyboard::Key::Numpad9
	}
};

Game::Game(sf::RenderWindow& _window, const sf::Font& font, const bool& _screamer, const GameMode& _playing):
    window(_window), playing(_playing), screamer(_screamer), start(font), end(font)
{
    tv = {
        sf::Texture(),
        sf::Texture()
    };

    tv[0].loadFromFile("snocked_cat.png");
    tv[1].loadFromFile("despair.png");

    sb.loadFromFile("vine_boom_sound.wav");

    using namespace std::experimental;

    ov.inst(randint(5, 10));

    start.set_start_f([this](){
        for(unsigned int i = 0U; i < NB_BOAT_MAX; i++){
            const BoatOption& boatoption = start.get_boat_option(i);
            if(!boatoption.is_active()) continue; // S'il n'y a pas de bateau, on en ajoute pas

            if(boatoption.is_player()){
                players[i] = std::make_unique<BoatPlayer>(BoatPlayer::create(((i + 1) * (1.f / 6.f) * SCREEN_HEIGHT)));
                players[i]->set_keys_controls(
                    players_controls[i][0],
                    players_controls[i][1],
                    players_controls[i][2],
                    players_controls[i][3],
                    players_controls[i][4],
                    players_controls[i][5]
                );
            } else {
                players[i] = std::make_unique<BoatAI>(BoatAI::create(((i + 1) * (1.f / 6.f) * SCREEN_HEIGHT), 200));
            }

            players[i]->setFillColor(boatoption.get_boatcolor());
            players[i]->setScale(boatoption.getScale());
        }

        start.disable();
        playing = GameMode::PLAYING;
    });
    start.enable();

    end.set_restart_f([this](){
        players.reset();
        ov.reset();

        end.disable();
        start.enable();
        playing = GameMode::START_SCREEN;
    });
}

void Game::mainloop(){
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                window.close();

            // Gérer le clic sur le bouton
            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) {
        
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                Button::checkAllClicks(mousePos);
            }

            if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Space){
                    players.reset();
                    ov.reset();
            
                    end.disable();
                    start.enable();
                    playing = GameMode::START_SCREEN;
                }
            }
        }

        if(playing == GameMode::PLAYING){
    
            for(auto it = players.begin(); it != players.end();) {
                if(!(*it)) { ++it; continue; }
                bool crossed = false;
            
                for (auto it_c = Cannonball::all.begin(); it_c != Cannonball::all.end();it_c++) {
                    if ((*it)->hasCrossed(**it_c)) {
                        crossed = true;
                        Cannonball::delInst(it_c);
                        break;
                    }
                }
    
                for (auto& o: ov) {
                    if ((*it)->hasCrossed(o)) {
                        (*it)->resetVelocity();
                    }
                }

                if (crossed) {
                    it = players.erase(it); // erase renvoie le suivant
                    //if(screamer) Screamer::show(tv[randint(0UL, tv.size() - 1)], sb);
                    if(screamer) Screamer::show(tv[randint(static_cast<size_t>(0), tv.size() - 1)], sb);
                } else {
                    ++it;
                }
            }
            
            players.handle_controls();
            
            engine.step(0.016f);
            players.update();

            Screamer::updateall();
        }

        window.clear(sf::Color(50, 100, 255));

        for(unsigned int i = 0U; i < players.size(); i++){
            if(players[i] && players[i]->hasCrossed(finishline))
            {
                playing = GameMode::END_SCREEN;
                end.enable("Joueur n" + std::to_string(i + 1) + " a atteint la ligne d'arrivee");
            }
        }

        if(playing == GameMode::END_SCREEN)
        {
            window.draw(end);

        } else if(playing == GameMode::START_SCREEN)
        {
            for(unsigned int i = 0U; i < NB_BOAT_MAX; i++){
                start.get_boat_option(i).turnboat();
            }
            engine.step(0.016f);
            for(unsigned int i = 0U; i < NB_BOAT_MAX; i++){
                start.get_boat_option(i).update();
            }
            window.draw(start);

        } else
        {
        // Mettre à jour la simulation
            players.draw(window);

            players.draw(window);
            for(Obstacle& o: ov) window.draw(o);

            Cannonball::drawAll(window);
            Screamer::drawAll(window);
            window.draw(finishline);
        }

        window.display();
    }
}
