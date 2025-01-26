#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "button/button.h"
#include "textField/textField.h"
#include <SFML/Window/Cursor.hpp>
#include "loginSystem/UserManager.h"
#include "gameMenu.h"

void changeCursor(sf::RenderWindow &window,sf::Cursor &textCursor,textField &loginField,textField &passwordField,const auto &activeCursor,const auto &cursor) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    bool isOverLoginField = loginField.getRect().getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
    bool isOverPasswordField = passwordField.getRect().getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
    if (isOverLoginField || isOverPasswordField) {
        window.setMouseCursor(textCursor);
    } else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        window.setMouseCursor(activeCursor.value());
    }
    else {
        window.setMouseCursor(cursor.value());
    }
}
void musicSettings(bool &keyPressed, sf::Music &music, bool &musicPlaying) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M) && !keyPressed) {
        if (musicPlaying) {
            music.setVolume(0);
            musicPlaying = false;
        } else {
            music.setVolume(100);
            musicPlaying = true;
        }
        keyPressed = true;
    } else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M)) {
        keyPressed = false;
    }
    if (music.getStatus() != sf::SoundSource::Status::Playing && musicPlaying) {
        music.play();
    }
}

int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode({800, 400}), "Big patric");

    // Load a sprite to display
    const sf::Texture texture("../image/main_menu.png");
    sf::Sprite sprite(texture);

    // Add button
    button btn(false,200, 50, "HELLO BUTTON");
    btn.setPosition(300.f, 300.f);

    // Add textField
    textField loginField(200.f, 50.f, "Login Button");
    loginField.setPosition(300.f, 100.f);

    // Add textField
    textField passwordField(200.f, 50.f, "Password Button");
    passwordField.setPosition(300.f, 200.f);

    // Load a music to play
    sf::Music music("../music/gimn_ukrainyi.ogg");
    bool musicPlaying = true;
    bool keyPressed = false;

    // Load image for cursor
    sf::Image cursorImage("../image/notActiveCursor.png");
    sf::Image activeCursorImage("../image/activeCursor.png");

    // UserManager
    UserManager userManager("../loginSystem/loginData.txt");

    // Cursor
    const auto cursor = sf::Cursor::createFromPixels(cursorImage.getPixelsPtr(), cursorImage.getSize(), sf::Vector2u(0, 0));
    const auto activeCursor = sf::Cursor::createFromPixels(activeCursorImage.getPixelsPtr(), activeCursorImage.getSize(), sf::Vector2u(0, 0));

    // Create a text cursor for text fields
    sf::Cursor textCursor(sf::Cursor::Type::Text);  // Create a Text cursor



    //sf::RenderWindow (sf::VideoMode({800, 400}), "Small patric");

    // Start the game loop
    while (window.isOpen()) {
        // Process events
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            // Close window: exit
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            // Pass event to textField
            loginField.handleClick(window, *event);
            passwordField.handleClick(window, *event);

            loginField.handeTextInput(*event);
            passwordField.handeTextInput(*event);
        }

        changeCursor(window,textCursor,loginField,passwordField,activeCursor,cursor);
        musicSettings(keyPressed,music,musicPlaying);


        if (btn.isButtonClicked(window)) {
            music.stop();
            window.close();
            if(userManager.loginUser(loginField.getUserInput(), passwordField.getUserInput())) {
                gameMenu startGameMenu;
                startGameMenu.showGameMenu();
            }
        }
            window.clear();
            window.draw(sprite);  // фон
            btn.draw(window);     // кнопка
            loginField.draw(window); // поле вводу login
            passwordField.draw(window); // поле вводу password
            window.display();
    }
    return 0;
}
