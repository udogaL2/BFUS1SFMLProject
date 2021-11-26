#include <SFML/Graphics.hpp>

#include <thread>
#include <chrono>
#include <vector>
#include <iostream>
#include <cmath>

#define WIDTH 1136
#define HEIGHT 640
const float G = 9.8;
const float D_T = 0.04;
const double PI = acos(-1);

using namespace std::chrono_literals;

class Circle {
public:
    Circle(float x, float y, float R, sf::Color Color, float angle, float v0) {
        s_y = y;
        s_x = x;
        s_x0 = x;
        s_y0 = y;
        radius = R;
        color = Color;
        s_angle = angle;
        s_v0 = v0;
        m_shape = new sf::CircleShape(radius);
        m_shape->setFillColor(color);
        m_shape->setOrigin(radius, radius);
        m_shape->setPosition(s_x, s_y);
    }

    ~Circle() {
        delete m_shape;
    }

    sf::CircleShape *getShape() {
        return m_shape;
    }

    void setStartPosition(float x0, float y0) {
        s_x0 = x0;
        s_y0 = y0;
    }

    void setAngle(float angle) {
        s_angle = angle;
    }

    void setInitialSpeed(float v0) {
        s_v0 = v0;
    }

    void setPosition(float x, float y) {
        if (x - radius <= 0)
            s_x = radius;
        else if (x + radius > WIDTH)
            s_x = WIDTH - radius;
        else
            s_x = x;
        if (y - radius < 0)
            s_y = radius;
        else if (y + radius > HEIGHT)
            s_y = HEIGHT - radius;
        else
            s_y = y;
        m_shape->setPosition(s_x, s_y);
    }

    void Move(float t) {
        float x = s_x0 + s_v0 * cos(s_angle) * t;
        float y = s_y0 + s_v0 * sin(s_angle) * t + G * t * t / 2;
        this->setPosition(x, y);
        isCollisionWithWall();
    }

    void isCollisionWithWall() {
        if (s_y + radius == HEIGHT) {
            this->s_angle += PI;
            this->s_v0 /= 2;
            std::cout << "Collision" << '\n';
        }
    }

    float getX() {
        return s_x;
    }

    float getY() {
        return s_y;
    }

    float getRadius() {
        return radius;
    }

    float getAngle() {
        return s_angle;
    }

private:
    float s_x;
    float s_y;
    float s_x0;
    float s_y0;
    float radius;
    float s_angle;
    float s_v0;

    sf::CircleShape *m_shape;
    sf::Color color;
};

void update(sf::RenderWindow &window, Circle &circle) {
    window.clear();
    window.draw(*circle.getShape());
    window.display();
}

bool moveWhenPush(sf::RenderWindow &window, Circle &circle) {
    sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
    if (pow((circle.getX() - mouse_position.x), 2) + pow((circle.getY() - mouse_position.y), 2) <=
        pow(circle.getRadius(), 2)) {
        while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            mouse_position = sf::Mouse::getPosition(window);
            circle.setPosition(mouse_position.x, mouse_position.y);
            update(window, circle);
        }
        return true;
    }
    return false;
}

int main() {
    float t = 0;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML_Project", sf::Style::Close);
    window.setFramerateLimit(120);
    Circle circle(20., 20., 20, sf::Color::Blue, 0, 20);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                delete circle.getShape();
            }
        }


        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (moveWhenPush(window, circle)) {
                std::this_thread::sleep_for(40ms);
                sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
                float x0 = circle.getX();
                float y0 = circle.getY();
                int x1 = mouse_position.x;
                int y1 = mouse_position.y;

                float d = sqrt(pow((x1 - x0), 2) + pow(y1 - y0, 2));
                float dy = y1 - y0;
                float dx = x1 - x0;

                float angle = atan(dy / dx);
                if (dx < 0)
                    angle += PI;

                if (dx == 0 and dy == 0) {
                    angle = 0;
                    d = 0;
                }
                circle.setStartPosition(circle.getX(), circle.getY());
                circle.setInitialSpeed(d);
                circle.setAngle(angle);
                std::cout << circle.getAngle() << '\n';
                t = 0;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
            delete circle.getShape();
        }

        circle.Move(t);

        update(window, circle);
//        std::this_thread::sleep_for(10ms);
        t += D_T;
    }

    return 0;
}