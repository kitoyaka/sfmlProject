//
// Created by rigry on 18.01.2025.
//

#include "textField.h"

void textField::setPosition(float x, float y) {
    m_rect.setPosition(sf::Vector2f(x-2.f, y));
    m_text.setPosition(sf::Vector2f(x, y+10.f));

}
void textField::draw(sf::RenderWindow& window) const {
    window.draw(m_rect);
    window.draw(m_text);
}

void textField::textEntering(sf::RenderWindow& window, sf::Event event) {
    if(auto* textEntered = event.getIf<sf::Event::TextEntered>())
    {
        if(textEntered->unicode == '\b')
        {
            if(!m_userInput.empty())
            {
                m_userInput.pop_back();
            }
        }
        else if(textEntered->unicode < 128)
        {
            m_userInput =+ static_cast<char>(textEntered->unicode);
        }
        m_text.setString(m_userInput);
    }
}
