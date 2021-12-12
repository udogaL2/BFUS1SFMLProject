#include "../inc/Scoreboard.h"


namespace dg {
    Scoreboard::Scoreboard() {
        textBox = new TextBox(20, 20, "Number of points: " + std::to_string(s_score));
    }

    Scoreboard::~Scoreboard() {
        delete textBox;
    }

    void Scoreboard::addScore(int score) {
        d_s = score;
        s_score += score;
        update();
    };

    void Scoreboard::update() {
        textBox->setText(
                "Number of points: " + std::to_string(s_score) + " (added " + std::to_string(d_s) + " points)");
    }

    sf::Text *Scoreboard::getShape() {
        return textBox->getShape();
    }

    void Scoreboard::deleteMyself() {
        delete textBox->getShape();
        delete textBox;
    }

}