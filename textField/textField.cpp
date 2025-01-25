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



void textField::handleClick(sf::RenderWindow &window, sf::Event event) {
    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        sf::Vector2i  mousePosition = sf::Mouse::getPosition(window);
        if(m_rect.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)))
        {
            setActive(true);
        }
        else
        {
            setActive(false);
        }
    }
}

void textField::handeTextInput(sf::Event event) {
    if (m_isActive) {
        if (auto* textEntered = event.getIf<sf::Event::TextEntered>()) {
            if (textEntered->unicode == '\b') {
                if (!m_userInput.empty()) {
                    m_userInput.pop_back();
                }
            } else if (textEntered->unicode < 128) {
                m_userInput += static_cast<char>(textEntered->unicode);
                i++;
                if (i % 15 == 0) {
                    clear();
                }
                m_text.setString(m_userInput);
            }
        }
    }
}



std::string textField::getUserInput() {
    return m_userInput;
}

void textField::setActive(bool checkActive) {
    m_isActive = checkActive;
    m_rect.setFillColor(m_isActive ? sf::Color::Blue : sf::Color::White);
}

bool textField::checkActive() {
    return m_isActive;
}

