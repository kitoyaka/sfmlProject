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
    btn.setPosition(20.f, 20.f);

    // Add textField
    textField loginField(200.f, 50.f);
    loginField.setPosition(300.f, 50.f);
    textField passwordField(200.f,50.f);
    passwordField.setPosition(300.f, 150.f);


    // Load a music to play
    sf::Music music("../music/gimn_ukrainyi.ogg");
    bool musicPlaying = true;
    bool keyPressed = false;

    // Load image for cursor
    sf::Image cursorImage("../image/cursor_1.png");

    // Cursor
    const auto cursor = sf::Cursor::createFromPixels(cursorImage.getPixelsPtr(), cursorImage.getSize(), sf::Vector2u(0, 0));

    int leftButtonPressedTimes=1;
    bool leftButtonPressed = true;

    // Start the game loop
    while (window.isOpen()) {
        // Process events
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            // Close window: exit
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            // Pass event to textField
            loginField.textEntering(window, *event);
            passwordField.textEntering(window,*event);



            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                if (leftButtonPressed) {
                    std::cout<<"button pressed "<<leftButtonPressedTimes<<" times"<<std::endl;
                    leftButtonPressedTimes++;
                    leftButtonPressed = false;
                } else {
                    leftButtonPressed = true;
                }
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
        window.clear();

        // Draw objects
        window.draw(sprite);  // фон
        btn.draw(window);     // кнопка
        loginField.draw(window); // поле вводу
        passwordField.draw(window);
        window.setMouseCursor(cursor.value()); // курсор

        // Update the window
        window.display();
    }
    return 0;
}
