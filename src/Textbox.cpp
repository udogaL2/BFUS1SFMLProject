#include "../inc/Textbox.h"

namespace dg {
    TextBox::TextBox(float x, float y, const std::string &text) {
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

    TextBox::~TextBox() {
        delete Text;
    }

    void TextBox::setText(std::string text) {
        Text->setString(text);
    }

    void TextBox::setPosition(float x, float y) {
        s_x = x;
        s_y = y;
        Text->setPosition(s_x, s_y);
    }

    sf::Text *TextBox::getShape() {
        return Text;
    }

    void TextBox::loadFont() {
        if (!Font.loadFromFile("data/ttf/arial.ttf")) {
            std::cout << "ERROR when loading arial.ttf" << '\n';
        }
    }
}