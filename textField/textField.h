//
// Created by rigry on 18.01.2025.
//

#ifndef SFMLPROJECT_TEXTFIELD_H
#define SFMLPROJECT_TEXTFIELD_H

#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>

inline bool showWrongLogPass = false;

class textField
{
private:
    int m_width, m_height;
    sf::RectangleShape m_rect;
    std::string m_userInput;
    sf::Font font;
    sf::Text m_text;
    sf::Event::TextEntered textEntered;
    int i=0;
    int leftButtonPressedTimes=1;
    bool leftButtonPressed = true;
    std::string m_buttonName;
    bool m_isActive;
    sf::Texture m_texture;
public:
    textField(int width, int height, std::string buttonName, const std::string& texturePath = "") :
    m_width(width), m_height(height), m_buttonName(buttonName), m_isActive(false),
    font("../font/ArialMT.ttf"), m_text(font, m_userInput, 50) {

        if (!texturePath.empty()) {
            if (!m_texture.loadFromFile(texturePath)) {
                throw std::runtime_error("Failed to load texture: " + texturePath);
            }
            m_rect.setTexture(&m_texture);
        } else {
            m_rect.setFillColor(sf::Color::Green);
        }

        m_rect.setSize(sf::Vector2f(m_width, m_height));

        m_text.setFont(font);
        m_text.setString(m_userInput);
        m_text.setCharacterSize(24);
        m_text.setFillColor(sf::Color::White);
        m_text.setStyle(sf::Text::Bold);
        m_text.setOutlineColor(sf::Color::Black);
        m_text.setOutlineThickness(2.f);

    }


    void draw(sf::RenderWindow& window) const;
    void setPosition(float x, float y);
    void clear();
    void setActive(bool checkActive);
    void handleClick(sf::RenderWindow& window, sf::Event event);
    void handeTextInput(sf::Event event);
    bool checkActive();
    void setUnActive();
    std::string getUserInput();
    sf::RectangleShape& getRect() {
        return m_rect;
    }

};

#endif //SFMLPROJECT_TEXTFIELD_H