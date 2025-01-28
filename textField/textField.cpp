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
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
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
/*
void textField::handleHover(sf::RenderWindow &window) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    if(m_rect.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)))
    {
        sf::Color grayColor(128,128,128);
        m_rect.setFillColor(grayColor);
    }
    else
    {
        m_rect.setFillColor(sf::Color::White);
    }
}*/


void textField::handeTextInput(sf::Event event) {
    if (m_isActive) {
        if (auto* textEntered = event.getIf<sf::Event::TextEntered>()) {

            if (textEntered->unicode < 128 && textEntered->unicode != 8) {
                if(m_userInput.size() < 15) {
                    m_userInput += static_cast<char>(textEntered->unicode);
                    m_text.setString(m_userInput);

                }
            } else if (textEntered->unicode == 8) {
                if (!m_userInput.empty()) {
                    m_userInput.pop_back();
                    m_text.setString(m_userInput);
                }
            }

        }
    }
}



std::string textField::getUserInput() {
    return m_userInput;
}

void textField::setActive(bool checkActive) {
    sf::Color lightGray(200, 200, 200);
    m_isActive = checkActive;
    if (m_isActive) {
        m_rect.setFillColor(lightGray);  // Если активное, делаем светло-серым
    } else {
        m_rect.setFillColor(sf::Color::White);  // Если не активное, белым
    }
}
void textField::setUnActive() {
    m_isActive = false;
}


bool textField::checkActive() {
    return m_isActive;
}

