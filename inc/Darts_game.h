#pragma once
#ifndef SFML_SAMPLE_DARTS_GAME_H
#define SFML_SAMPLE_DARTS_GAME_H

#include "SFML/Graphics.hpp"
#include "Dart.h"
#include "Textbox.h"
#include "Scoreboard.h"

#include <thread>
#include <chrono>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std::chrono_literals;

#define WIDTH 1136
#define HEIGHT 640

namespace dg {
    const float G = 9.8;
    const float D_T = 0.04;
    const double PI = acos(-1);

    float getAngle(float x0, float y0, float x1, float y1);

    void update(sf::RenderWindow &window, Dart &dart, Scoreboard &scoreboard, sf::Sprite background);

    bool moveWhenPush(sf::RenderWindow &window, Dart &dart, Scoreboard &scoreboard, sf::Sprite background);

    float getDistance(float x0, float y0, float x1, float y1);

    void startGame(sf::RenderWindow &window, Dart &dart, Scoreboard &scoreboard, sf::Sprite background);
}

#endif //SFML_SAMPLE_DARTS_GAME_H
