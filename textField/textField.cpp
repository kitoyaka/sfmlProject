//
// Created by rigry on 18.01.2025.
//

#include "textField.h"

void textField::setPosition(float x, float y) {
    m_rect.setPosition(sf::Vector2f(x-2.f, y));
    m_text.setPosition(sf::Vector2f(x-1.f, y+10.f));

}
void textField::draw(sf::RenderWindow& window) const {
    window.draw(m_rect);
    window.draw(m_text);
}

void textField::clear() {
    m_userInput.clear();
    m_text.setString("");
}

void textField::isButtonClicked(sf::RenderWindow& window, sf::Event event) {

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

        // Проверяем, попадает ли мышь в область кнопки
        if (m_rect.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
            if (leftButtonPressed) {

                std::cout<<m_buttonName << " pressed " << leftButtonPressedTimes << " times" << std::endl;
                m_rect.setFillColor(sf::Color::Blue);
                leftButtonPressedTimes++;
                leftButtonPressed = false;

            }
            else if (leftButtonPressedTimes % 2 != 0) {
                m_rect.setFillColor(sf::Color::White);
            }
        }
    } else {
        leftButtonPressed = true;
    }

    if (m_rect.getFillColor() == sf::Color::Blue) {
        if (auto* textEntered = event.getIf<sf::Event::TextEntered>()) {
            if (textEntered->unicode == '\b') {
                if (!m_userInput.empty()) {
                    m_userInput.pop_back();  // Handle backspace
                }
            } else if (textEntered->unicode < 128) {
                if (i % 15 == 0) {
                    clear();  // Clear text after certain characters
                } else {
                    m_userInput += static_cast<char>(textEntered->unicode);  // Add typed character
                }
                i++;
                m_text.setString(m_userInput);
            }
        }
    }

}



