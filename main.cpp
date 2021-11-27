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


class TextBox {
public:
    TextBox(float x, float y, const std::string &text) {
        s_x = x;
        s_y = y;

        loadFont();
        Text = new sf::Text;
        Text->setFont(Font);
        Text->setCharacterSize(24);
        Text->setString(text);
        Text->setFillColor(sf::Color::White);
        Text->setPosition(s_x, s_y);
    }

    ~TextBox() {
        delete Text;
    }

    void setText(std::string text) {
        Text->setString(text);
    }

    void setPosition(float x, float y) {
        s_x = x;
        s_y = y;
        Text->setPosition(s_x, s_y);
    }

    sf::Text *getShape() {
        return Text;
    }

private:
    float s_x, s_y;

    sf::Font Font;
    sf::Text *Text;

    void loadFont() {
        if (!Font.loadFromFile("../ttf/arial.ttf")) {
            std::cout << "ERROR when loading arial.ttf" << '\n';
        }
    }
};


class Scoreboard {
public:
    Scoreboard() {
        textBox = new TextBox(20, 20, "Number of points: " + std::to_string(s_score));
    }

    ~Scoreboard() {
        deleteMyself();
    }

    void addScore(int score) {
        s_score += score;
        update();
    };

    void update() {
        textBox->setText("Number of points: " + std::to_string(s_score));
    }

    sf::Text *getShape() {
        return textBox->getShape();
    }

    void deleteMyself(){
        delete textBox->getShape();
        delete textBox;
    }

private:
    long int s_score = 0;

    ::TextBox *textBox;
};

Scoreboard scoreboard;

class Dart {
public:
    Dart(float x, float y, float w, float h, float angle, float v0) {
        s_y = y;
        s_x = x;
        s_x0 = x;
        s_y0 = y;
        s_w = w;
        s_h = h;
        s_angle = angle;
        s_v0 = v0;
        s_t = 0;

        uploadTexture();

        m_shape = new sf::Sprite();
        m_shape->setTexture(m_texture);
        m_shape->setOrigin(s_w, s_h);
        m_shape->setPosition(s_x, s_y);
    }

    ~Dart() {
        deleteMyself();
    }

    bool uploadTexture() {
        if (!m_texture.loadFromFile("../img/darts.png")) {
            std::cout << "ERROR when loading darts.png" << std::endl;
            return false;
        }
        m_texture.setSmooth(true);
        return true;
    }

    sf::Sprite *getShape() {
        return m_shape;
    }

    void setPushed(bool put) {
        isPushed = put;
    }

    void setStartPosition(float x0, float y0) {
        s_x0 = x0;
        s_y0 = y0;
        m_shape->setRotation(0);
    }

    void setAngle(float angle) {
        s_angle = angle;
    }

    void setInitialSpeed(float v0) {
        s_v0 = v0;
    }

    void setSelfTime(float time) {
        s_t = time;
    }

    void addSelfTime(float time) {
        s_t += time;
    }

    void setPosition(float x, float y) {
        if (x - s_w + 30 < 0)
            s_x = s_w - 30;
        else if (x + s_w - 30 > WIDTH)
            s_x = WIDTH - s_w + 30;
        else
            s_x = x;
        if (y - s_h < 0)
            s_y = s_h;
        else if (y + s_h > HEIGHT)
            s_y = HEIGHT - s_h;
        else
            s_y = y;
        m_shape->setPosition(s_x, s_y);
    }

    void Move() {
        if (s_x + s_w - 30 >= WIDTH) {
            scoreboard.addScore(5);
            std::this_thread::sleep_for(500ms);
            this->s_v0 = 5;
            this->s_angle = PI / 2;
            this->setPosition(250, 150);
            this->setStartPosition(250, 150);
            s_t = 0;
            isPushed = false;
        } else if ((!isPushed and s_y + s_h <= 400) or
                   (isPushed and s_x - s_w + 30 > 0 and s_y - s_h > 0 and s_y + s_h < HEIGHT)) {
            float x = s_x0 + s_v0 * cos(s_angle) * s_t;
            float y = s_y0 + s_v0 * sin(s_angle) * s_t + G * s_t * s_t / 2;
            this->setPosition(x, y);
            m_shape->setRotation(::getAngle(s_x0, s_y0, s_x, s_y) * (180.0 / PI));
        } else {
            if (isPushed) {
                scoreboard.addScore(-10);
                std::this_thread::sleep_for(500ms);
                this->s_v0 = 5;
                this->s_angle = PI / 2;
                this->setPosition(250, 150);
                this->setStartPosition(250, 150);
                s_t = 0;
                isPushed = false;
            }
        }
    }

    float getX() {
        return s_x;
    }

    float getY() {
        return s_y;
    }

    float getHeight() {
        return s_h;
    }

    float getWidth() {
        return s_w;
    }

    float getAngle() {
        return s_angle;
    }

    void deleteMyself() {
        delete m_shape;
    }

private:
    float s_x;
    float s_y;
    float s_x0;
    float s_y0;
    float s_h;
    float s_w;
    float s_angle;
    float s_v0;
    float s_t;

    bool isPushed = false;

    sf::Texture m_texture;
    sf::Sprite *m_shape;
};

void update(sf::RenderWindow &window, Dart &dart, Scoreboard &scoreboard) {
    window.clear();
    window.draw(*scoreboard.getShape());
    window.draw(*dart.getShape());
    window.display();
}

bool moveWhenPush(sf::RenderWindow &window, Dart &dart) {
    sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
    if ((dart.getX() + dart.getWidth() >= mouse_position.x and dart.getX() - dart.getWidth() <= mouse_position.x) and
        (dart.getY() + dart.getWidth() >= mouse_position.y and dart.getY() - dart.getWidth() <= mouse_position.y)) {
        dart.setPushed(true);
        while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            mouse_position = sf::Mouse::getPosition(window);
            if (mouse_position.x <= 500) {
                if (dart.getX() != mouse_position.x and dart.getY() != mouse_position.y)
                    dart.getShape()->setRotation(
                            getAngle(dart.getX(), dart.getY(), mouse_position.x, mouse_position.y) * (180.0 / PI));
                dart.setPosition(mouse_position.x, mouse_position.y);
            } else {
                sf::Mouse::setPosition(sf::Vector2i(500, mouse_position.y), window);
            }
            update(window, dart, scoreboard);
        }
        return true;
    }
    return false;
}

float getDistance(float x0, float y0, float x1, float y1) {
    return sqrt(pow((x1 - x0), 2) + pow(y1 - y0, 2));
}



int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML_Project", sf::Style::Close);
    window.setFramerateLimit(120);
    Dart dart(250., 150., 102 / 2, 25 / 2, 0, 0);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                dart.deleteMyself();
                scoreboard.deleteMyself();
            }
        }


        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (moveWhenPush(window, dart)) {
                std::this_thread::sleep_for(40ms);
                sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
                float x0 = dart.getX();
                float y0 = dart.getY();
                int x1 = mouse_position.x;
                int y1 = mouse_position.y;

                dart.setStartPosition(dart.getX(), dart.getY());

                dart.setInitialSpeed(getDistance(x0, y0, x1, y1));
                dart.setAngle(getAngle(x0, y0, x1, y1));

                dart.setSelfTime(0);
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
            dart.deleteMyself();
            scoreboard.deleteMyself();
        }

        dart.Move();

        update(window, dart, scoreboard);
//        std::this_thread::sleep_for(10ms);
        dart.addSelfTime(D_T);
    }

    return 0;
}