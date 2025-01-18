//
// Created by rigry on 18.01.2025.
//

#include "writeArea.h"

void writeArea::setPosition(float x, float y) {
    m_rect.setPosition(sf::Vector2f(x-2.f, y));
}
void writeArea::draw(sf::RenderWindow& window) const {
    window.draw(m_rect);
}
