
#include <SFML/System/Clock.hpp>

#include <iostream>
#include <chrono>
#include <unistd.h>

#include "properties.hpp"
#include "game.hpp"

int main(int argc, char *argv[]) {
    int opt;
	bool screamer = false;

    // Analyse des options
    while ((opt = getopt(argc, argv, "s")) != -1) {
        switch (opt) {
            case 's':
                screamer = true;
                break;

            case '?':
                std::cerr << "Usage: " << argv[0] << " [-s]\n";
                return EXIT_FAILURE;
        }
    }

	sf::Clock clock;
	float elapsed = clock.getElapsedTime().asSeconds();
	clock.restart();
	std::cout << "Everything OK : " << elapsed << std::endl;

	sf::Font font;
	font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "COURSE DE BATEAU");

	Game game(window, font, screamer);
	game.mainloop();

	return 0;
}
