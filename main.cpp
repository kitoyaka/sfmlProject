#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "button/button.h"
#include "writeArea/writeArea.h"

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode({800, 400}), "Big patric");

    // Load a sprite to display
    const sf::Texture texture("../image/main_menu.png");
    sf::Sprite sprite(texture);

    // Load a music to play
    //sf::Music music("../music/lei.ogg");
    //music.play();

    // Add button
    button btn(200,50,"HELLO BUTTON");
    btn.setPosition(20.f, 20.f);

    // Add writeArea
    writeArea zone1(200, 50);
    zone1.setPosition(300.f,200.f);

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
        //  Clear the window
        window.clear();

        window.draw(sprite);  //фон
        btn.draw(window);  //кнопка
        zone1.draw(window);

        // Update the window
        window.display();
    }
}
