//
// Created by Admin on 29.11.2021.
//
#pragma once
#ifndef SFML_SAMPLE_TEXTBOX_H
#define SFML_SAMPLE_TEXTBOX_H
#include <iostream>
#include "SFML/Graphics.hpp"

namespace dg {
    class TextBox {
    public:
        TextBox(float x, float y, const std::string &text);

        ~TextBox();

        void setText(std::string text);

        void setPosition(float x, float y);

        sf::Text *getShape();

    private:
        float s_x, s_y;

        sf::Font Font;
        sf::Text *Text;

        void loadFont();
    };
}

#endif //SFML_SAMPLE_TEXTBOX_H
