#include "button.h"

void button::setPosition(float x, float y) {
    m_rect.setPosition(sf::Vector2f(x-2.f, y));
    m_text.setPosition(sf::Vector2f(x, y+10.f));
}


void button::draw(sf::RenderWindow& window) const {
    window.draw(m_rect);
    window.draw(m_text);
}

bool button::isButtonClicked(sf::RenderWindow& window, const std::string& oldTexturePath, const std::string& newTexturePath) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);


        if (m_rect.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
            if (leftButtonPressed) {
                leftButtonPressed = false;
                changeTexture(m_rect,m_texture,newTexturePath);
                return true;
            }
        }
    } else {
        changeTexture(m_rect,m_texture, oldTexturePath);
        leftButtonPressed = true;
    }
    return false;
}

void button::changeTextureButton() {
    if (leftButtonPressed) {

    }
}

void button::setActive(bool active, const std::string& activeTexturePath, const std::string& inactiveTexturePath){
    if(active) {
        m_texture.loadFromFile( activeTexturePath);
    }
    else if(!active) {
        m_texture.loadFromFile(inactiveTexturePath);
    }
    m_rect.setTexture(&m_texture);
    isActive = active;
}
