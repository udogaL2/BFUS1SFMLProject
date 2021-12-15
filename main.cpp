#include "Darts_game.h"
#include "Dart.h"
#include "Scoreboard.h"


int main() {
    dg::Scoreboard scoreboard;
    sf::Sprite background;

    sf::Texture texture;
    if (!texture.loadFromFile("data/img/background.jpg")) {
        std::cout << "ERROR when loading background.jpg" << std::endl;
        return -1;
    }
    background.setTexture(texture);

    sf::Image icon;
    if (!icon.loadFromFile("data/img/dart.png")) {
        std::cout << "ERROR when loading dart.png" << std::endl;
        return -1;
    }

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML_Project", sf::Style::Close);
    window.setFramerateLimit(120);
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    // создание дротика с начальной позицией (250, 150) и цетром в точке (где 102 и 25 размеры изображения)
    dg::Dart dart(250., 150., 102 / 2, 25 / 2, 0, 0);

    dg::startGame(window, dart, scoreboard, background);

    return 0;
}