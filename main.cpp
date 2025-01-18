#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "button/button.h"
#include "textField/textField.h"

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
    loginField.setPosition(300.f, 200.f);

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
        }

        // Clear the window
        window.clear();

        // Draw objects
        window.draw(sprite);  // фон
        btn.draw(window);     // кнопка
        loginField.draw(window); // поле вводу

        // Update the window
        window.display();
    }

    return 0;
}
