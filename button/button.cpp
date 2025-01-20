#include "button.h"

void button::setPosition(float x, float y) {
    m_rect.setPosition(sf::Vector2f(x-2.f, y));
    m_text.setPosition(sf::Vector2f(x, y+10.f));
}


void button::draw(sf::RenderWindow& window) const {
    window.draw(m_rect);
    window.draw(m_text);
}

void button::isButtonClicked(sf::RenderWindow& window) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

        // Проверяем, попадает ли мышь в область кнопки
        if (m_rect.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
            if (leftButtonPressed) {
                std::cout << m_buttonText << " pressed " << leftButtonPressedTimes << " times" << std::endl;
                m_rect.setFillColor(sf::Color::Blue);
                leftButtonPressedTimes++;
                leftButtonPressed = false;
            }
        }
    } else {
        m_rect.setFillColor(sf::Color::Green);
        leftButtonPressed = true;
    }

}


