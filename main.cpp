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
    loginField.setPosition(300.f, 200.f);

    // Load a music to play
    sf::Music music("../music/bgm_1.ogg");
    music.play();

    // Load image for cursor
    sf::Image cursorImage("../image/cursor_1.png");

    // Cursor
    const auto cursor = sf::Cursor::createFromPixels(cursorImage.getPixelsPtr(), cursorImage.getSize(), sf::Vector2u(0, 0));


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
        // Проверка: если музыка остановилась, запустить снова
        if (music.getStatus() != sf::SoundSource::Status::Playing) {
            music.play();
        }


        // Clear the window
        window.clear();

        // Draw objects
        window.draw(sprite);  // фон
        btn.draw(window);     // кнопка
        loginField.draw(window); // поле вводу
        window.setMouseCursor(cursor.value()); // курсор


        // Update the window
        window.display();
    }

    return 0;
}
