//
// Created by rigry on 18.01.2025.
//

#ifndef SFMLPROJECT_WRITEAREA_H
#define SFMLPROJECT_WRITEAREA_H
#include <string>
#include "SFML/Graphics.hpp"

class writeArea {
private:
    std::string m_text;
    int m_width, m_height;
    sf::RectangleShape m_rect;
    const sf::Font font;//("ArialMT.ttf");
public:
    writeArea(int width, int height): m_width(width), m_height(height) {


        m_rect.setSize(sf::Vector2f(m_width, m_height));
        m_rect.setOutlineColor(sf::Color::Black);
        m_rect.setOutlineThickness(2);
        m_rect.setFillColor(sf::Color::White);

    }


    void draw(sf::RenderWindow& window) const;
    void setPosition(float x, float y);
};


#endif //SFMLPROJECT_WRITEAREA_H
