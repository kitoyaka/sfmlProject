#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>


class button {
private:
    int m_width, m_height;
    sf::RectangleShape m_rect;
    std::string m_buttonText;
    const sf::Font font;//("ArialMT.ttf");
    sf::Text m_text;//(font,m_buttonText , 50);

public:
    // Конструктор кнопки, принимающий ширину и высоту
    button(int width, int height, std::string buttonText) : m_width(width), m_height(height), m_buttonText(buttonText),font("../font/ArialMT.ttf"),
                                                            m_text(font,m_buttonText , 50)
    {
        // Прямоугольник
        m_rect.setSize(sf::Vector2f(m_width, m_height));
        m_rect.setOutlineColor(sf::Color::Black);
        m_rect.setOutlineThickness(2);
        m_rect.setFillColor(sf::Color::Green);

        // Текст
        m_text.setFont(font);
        m_text.setString(m_buttonText);
        m_text.setCharacterSize(24);
        m_text.setFillColor(sf::Color::White);
        m_text.setStyle(sf::Text::Bold);
        m_text.setOutlineColor(sf::Color::Black);
        m_text.setOutlineThickness(2.f);
    }

    void draw(sf::RenderWindow& window) const;
    void setPosition(float x, float y);
};

#endif // BUTTON_H
