#include "button.h"

void button::setPosition(float x, float y) {
    m_rect.setPosition(sf::Vector2f(x-2.f, y));
    m_text.setPosition(sf::Vector2f(x, y+10.f));

}
void button::draw(sf::RenderWindow& window) const {
    window.draw(m_rect);
    window.draw(m_text);
}
