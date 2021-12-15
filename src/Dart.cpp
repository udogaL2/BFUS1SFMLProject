#include "../inc/Dart.h"
#include "../inc/Darts_game.h"

namespace dg {
    Dart::Dart(float x, float y, float w, float h, float angle, float v0) {
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

    Dart::~Dart() {
        delete m_shape;
    }

    bool Dart::uploadTexture() {
        if (!m_texture.loadFromFile("data/img/darts.png")) {
            std::cout << "ERROR when loading darts.png" << std::endl;
            return false;
        }
        m_texture.setSmooth(true);
        return true;
    }

    sf::Sprite *Dart::getShape() {
        return m_shape;
    }

    void Dart::setPushed(bool put) {
        isPushed = put;
    }

    void Dart::setStartPosition(float x0, float y0) {
        s_x0 = x0;
        s_y0 = y0;
        m_shape->setRotation(0);
    }

    void Dart::setAngle(float angle) {
        s_angle = angle;
    }

    void Dart::setInitialSpeed(float v0) {
        s_v0 = v0;
    }

    void Dart::setSelfTime(float time) {
        s_t = time;
    }

    void Dart::addSelfTime(float time) {
        s_t += time;
    }

    void Dart::setPosition(float x, float y) {
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

    void Dart::Move(Scoreboard & scoreboard) {
        // если дротик попал в правую часть экрана с мишенью, то начисляем очки и сбрасываем параметры
        if ((s_x + s_w - 30 >= WIDTH and (s_y < 64 or s_y > 414)) or
            (s_x + s_w - 10 >= WIDTH and !(s_y < 64 or s_y > 414))) {
            scoreboard.addScore(getPoints());
            std::this_thread::sleep_for(500ms);
            this->s_v0 = 5;
            this->s_angle = PI / 2;
            this->setPosition(250, 150);
            this->setStartPosition(250, 150);
            s_t = 0;
            isPushed = false;
        // иначе проверяем был ли брошен дротик или он находится в стартовой позиции
        // если его бросили, то меняем координаты и угол по формулам
        // если он находится в стартовой позиции, то дротик падает до тех пор, пока не врежется в стол
        } else if ((!isPushed and s_y + s_h <= 400) or
                   (isPushed and s_x - s_w + 30 > 0 and s_y - s_h > 0 and s_y + s_h < HEIGHT)) {
            float x = s_x0 + s_v0 * cos(s_angle) * s_t;
            float y = s_y0 + s_v0 * sin(s_angle) * s_t + G * s_t * s_t / 2;
            this->setPosition(x, y);
            m_shape->setRotation(dg::getAngle(s_x0, s_y0, s_x, s_y) * (180.0 / PI));
        } else {
            // если дротик попал в другие части экрана, то отнимаем очки и возвращаем в стартовую позицию
            if (isPushed) {
                scoreboard.addScore(-10);
                std::this_thread::sleep_for(500ms);
                this->s_v0 = 5;
                this->s_angle = PI / 2;
                this->setPosition(240, 150);
                this->setStartPosition(240, 150);
                s_t = 0;
                isPushed = false;
            }
        }
    }

    float Dart::getX() {
        return s_x;
    }

    float Dart::getY() {
        return s_y;
    }

    float Dart::getHeight() {
        return s_h;
    }

    float Dart::getWidth() {
        return s_w;
    }

    float Dart::getAngle() {
        return s_angle;
    }

    void Dart::deleteMyself() {
        delete m_shape;
    }

    int Dart::getPoints() {
        // обработка попадания по зонам мишени, в зависимости от которой начисляются определенные очки
        if (64 <= s_y and s_y <= 139 or 339 <= s_y and s_y <= 414) {
            return 1;
        } else if (139 < s_y and s_y <= 189 or 289 <= s_y and s_y < 339) {
            return 3;
        } else if (189 < s_y and s_y <= 224 or 254 <= s_y and s_y < 289) {
            return 5;
        } else if (224 <= s_y and s_y <= 254) {
            return 10;
        } else
            return -5;
    }

}

