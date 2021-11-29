#include "Darts_game.h"
#include "Dart.h"
#include "Scoreboard.h"


int main() {
    dg::Scoreboard scoreboard;
    sf::Sprite background;

    sf::Texture texture;
    if (!texture.loadFromFile("../img/background.jpg")) {
        std::cout << "ERROR when loading background.jpg" << std::endl;
    }
    background.setTexture(texture);

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML_Project", sf::Style::Close);
    window.setFramerateLimit(120);
    dg::Dart dart(250., 150., 102 / 2, 25 / 2, 0, 0);

    dg::startGame(window, dart, scoreboard, background);

    return 0;
}