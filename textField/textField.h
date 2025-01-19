//
// Created by rigry on 18.01.2025.
//

#ifndef SFMLPROJECT_TEXTFIELD_H
#define SFMLPROJECT_TEXTFIELD_H

#include "SFML/Graphics.hpp"

class textField
{
private:
    int m_width, m_height;
    sf::RectangleShape m_rect;
    std::string m_userInput;
    const sf::Font font;
    sf::Text m_text;
    sf::Event::TextEntered textEntered;
    int i=0;

public:
    textField(int width, int height) : m_width(width), m_height(height),
    font("../font/ArialMT.ttf"), m_text(font, m_userInput, 50) {

        m_rect.setSize(sf::Vector2f(m_width, m_height));
        m_rect.setOutlineColor(sf::Color::Black);
        m_rect.setOutlineThickness(2);
        m_rect.setFillColor(sf::Color::White);

        m_text.setFont(font);
        m_text.setString(m_userInput);
        m_text.setCharacterSize(24);
        m_text.setFillColor(sf::Color::White);
        m_text.setStyle(sf::Text::Bold);
        m_text.setOutlineColor(sf::Color::Black);
        m_text.setOutlineThickness(2.f);
    }


    void textEntering(sf::RenderWindow& window, sf::Event event);
    void draw(sf::RenderWindow& window) const;
    void setPosition(float x, float y);
    void clear();
};

#endif //SFMLPROJECT_TEXTFIELD_H
