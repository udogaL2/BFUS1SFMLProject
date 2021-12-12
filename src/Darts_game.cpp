#include "SFML/Graphics.hpp"
#include "../inc/Darts_game.h"

namespace dg {
    float getAngle(float x0, float y0, float x1, float y1) {
        float dy = y1 - y0;
        float dx = x1 - x0;
        float angle = atan(dy / dx);
        if (dx < 0)
            angle += acos(-1);
        if (dx == 0 and dy == 0) {
            angle = 0;
        }
        return angle;
    }

    void update(sf::RenderWindow &window, Dart &dart, Scoreboard &scoreboard, sf::Sprite background) {
        window.clear();
        window.draw(background);
        window.draw(*scoreboard.getShape());
        window.draw(*dart.getShape());
        window.display();
    }

    bool moveWhenPush(sf::RenderWindow &window, Dart &dart, Scoreboard &scoreboard, sf::Sprite background) {
        sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
        if ((dart.getX() + dart.getWidth() >= mouse_position.x and
             dart.getX() - dart.getWidth() <= mouse_position.x) and
            (dart.getY() + dart.getWidth() >= mouse_position.y and
             dart.getY() - dart.getWidth() <= mouse_position.y) and mouse_position.x <= 500) {
            dart.setPushed(true);
            while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                mouse_position = sf::Mouse::getPosition(window);
                if (mouse_position.x <= 500) {
                    if (dart.getX() != mouse_position.x and dart.getY() != mouse_position.y)
                        dart.getShape()->setRotation(
                                dg::getAngle(dart.getX(), dart.getY(), mouse_position.x, mouse_position.y) *
                                (180.0 / PI));
                    dart.setPosition(mouse_position.x, mouse_position.y);
                } else {
                    sf::Mouse::setPosition(sf::Vector2i(500, mouse_position.y), window);
                }
                update(window, dart, scoreboard, background);
            }
            return true;
        }
        return false;
    }

    float getDistance(float x0, float y0, float x1, float y1) {
        return sqrt(pow((x1 - x0), 2) + pow(y1 - y0, 2));
    }

    void startGame(sf::RenderWindow &window, Dart &dart, Scoreboard &scoreboard, sf::Sprite background){
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }


            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (dg::moveWhenPush(window, dart, scoreboard, background)) {
                    std::this_thread::sleep_for(40ms);
                    sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
                    float x0 = dart.getX();
                    float y0 = dart.getY();
                    int x1 = mouse_position.x;
                    int y1 = mouse_position.y;

                    dart.setStartPosition(dart.getX(), dart.getY());

                    dart.setInitialSpeed(dg::getDistance(x0, y0, x1, y1));
                    dart.setAngle(dg::getAngle(x0, y0, x1, y1));

                    dart.setSelfTime(0);
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }

            dart.Move(scoreboard);

            update(window, dart, scoreboard, background);
            dart.addSelfTime(dg::D_T);
        }

    }

}