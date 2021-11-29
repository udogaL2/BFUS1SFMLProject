//
// Created by Admin on 29.11.2021.
//
#pragma once
#ifndef SFML_SAMPLE_SCOREBOARD_H
#define SFML_SAMPLE_SCOREBOARD_H
#include <SFML/Graphics.hpp>
#include "Textbox.h"

namespace dg{
    class Scoreboard {
    public:
        Scoreboard();

        ~Scoreboard();

        void addScore(int score);

        void update();

        sf::Text *getShape();

        void deleteMyself();

    private:
        long int s_score = 0;
        int d_s;

        TextBox *textBox;
    };
}

#endif //SFML_SAMPLE_SCOREBOARD_H
