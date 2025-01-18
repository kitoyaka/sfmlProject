#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "cmake-build-debug/_deps/sfml-src/src/SFML/Graphics/GLLoader.hpp"

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML window");

    // Start the game loop
    while (window.isOpen())
    {
        sf::Event event;
        // Process events
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update the window
        window.display();
    }
}
