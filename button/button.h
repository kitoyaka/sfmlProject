#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <iostream>

void changeTexture(sf::RectangleShape &rect, sf::Texture &m_texture, const std::string& texturePath);


class button {
private:
    int m_width, m_height;

    std::string m_buttonText;
    const sf::Font font;//("ArialMT.ttf");
    sf::Text m_text;//(font,m_buttonText , 50);
    bool leftButtonPressed = true;
    sf::Texture m_texture;
    sf::RectangleShape m_rect;

    bool isActive;
public:

    button(bool active, int width, int height, std::string buttonText,const std::string& texturePath = "") :
    m_width(width),
    m_height(height),
    m_buttonText(buttonText),
    font("../font/ArialMT.ttf"),
    isActive(active),
    m_text(font,m_buttonText , 50)
    {
        // Малювання прямокутника
        m_rect.setSize(sf::Vector2f(m_width, m_height));

        m_texture.loadFromFile(texturePath);
        m_rect.setTexture(&m_texture);


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
    bool isButtonClicked(sf::RenderWindow& window,const std::string& oldTexturePath, const std::string& newTexturePath);
    //void changeTexture(const std::string& newTexturePath);
    void setActive(bool active, const std::string& activeTexturePath, const std::string& inactiveTexturePath);
    void changeTextureButton();
    bool checkActive() { return isActive; }
    bool getActive() const { return isActive; }
    void setActive(bool active) { isActive = active; }
};

#endif // BUTTON_H
