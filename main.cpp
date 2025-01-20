#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "button/button.h"
#include "textField/textField.h"
#include <SFML/Window/Cursor.hpp>

int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode({800, 400}), "Big patric");

    // Load a sprite to display
    const sf::Texture texture("../image/main_menu.png");
    sf::Sprite sprite(texture);

    // Add button
    button btn(200, 50, "HELLO BUTTON");
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
    sf::Image cursorImage("../image/cursor_1.png");

    // Cursor
    const auto cursor = sf::Cursor::createFromPixels(cursorImage.getPixelsPtr(), cursorImage.getSize(), sf::Vector2u(0, 0));

    // Create a text cursor for text fields
    sf::Cursor textCursor(sf::Cursor::Type::Text);  // Create a Text cursor


    // Start the game loop
    while (window.isOpen()) {
        // Process events
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            // Close window: exit
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            // Pass event to textField
            loginField.isButtonClicked(window,*event);
            passwordField.isButtonClicked(window,*event);

            // Change the cursor to text cursor when over text fields
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            bool isOverLoginField = loginField.getRect().getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
            bool isOverPasswordField = passwordField.getRect().getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
            if (isOverLoginField || isOverPasswordField) {
                window.setMouseCursor(textCursor);
            } else {
                window.setMouseCursor(cursor.value());
            }
        }

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
        // Clear the window
        window.clear(sf::Color::Black);

        // Draw objects
        window.draw(sprite);  // фон
        btn.draw(window);     // кнопка
        loginField.draw(window); // поле вводу login
        passwordField.draw(window); // поле вводу password

        // Проверяем нажатие кнопки
        btn.isButtonClicked(window);

        // Update the window
        window.display();
    }
    return 0;
}
