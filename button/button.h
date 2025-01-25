#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <iostream>


class button {
private:
    int m_width, m_height;
    sf::RectangleShape m_rect;
    std::string m_buttonText;
    const sf::Font font;//("ArialMT.ttf");
    sf::Text m_text;//(font,m_buttonText , 50);
    int leftButtonPressedTimes=1;
    bool leftButtonPressed = true;
    sf::Texture m_texture;  // Текстура для кнопки
    bool textureSet = false;  // Флаг для проверки, установлена ли текстура

public:

    button(int width, int height, std::string buttonText,const std::string& texturePath = "") : m_width(width), m_height(height), m_buttonText(buttonText),font("../font/ArialMT.ttf"),
                                                            m_text(font,m_buttonText , 50)
    {
        // Малювання прямокутника
        m_rect.setSize(sf::Vector2f(m_width, m_height));
        //m_rect.setOutlineColor(sf::Color::Black);
        //m_rect.setOutlineThickness(2);
        //m_rect.setFillColor(sf::Color::Green);

        // Загрузка текстуры (если указана)
        if (!texturePath.empty()) {
            if (!m_texture.loadFromFile(texturePath)) {
                throw std::runtime_error("Failed to load texture: " + texturePath);
            }
            m_rect.setTexture(&m_texture);  // Установка текстуры на прямоугольник
            textureSet = true;  // Устанавливаем флаг текстуры
        } else {
            m_rect.setFillColor(sf::Color::Green);  // Если текстура не задана, используем цвет
        }

        // Текст
        m_text.setFont(font);
        m_text.setString(m_buttonText);
        m_text.setCharacterSize(24);
        m_text.setFillColor(sf::Color::White);
        m_text.setStyle(sf::Text::Bold);
        m_text.setOutlineColor(sf::Color::Black);
        m_text.setOutlineThickness(2.f);
    }
    int m_zalupa;

    void draw(sf::RenderWindow& window) const;
    void setPosition(float x, float y);
    bool isButtonClicked(sf::RenderWindow& window);
};

#endif // BUTTON_H
