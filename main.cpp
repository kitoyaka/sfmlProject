#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "button/button.h"

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode({800, 400}), "Big patric");

    // Load a sprite to display
    const sf::Texture texture("../image/main_menu.png");
    sf::Sprite sprite(texture);

    // Load a music to play
    sf::Music music("../music/lei.ogg");
    music.play();

    // Add button
    button btn(200,50,"HELLO BUTTON");
    btn.setPosition(300.f, 200.f);

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        // Очищаем экран
        window.clear();

        window.draw(sprite);  //фон
        btn.draw(window);  //кнопка

        // Update the window
        window.display();
    }
}
