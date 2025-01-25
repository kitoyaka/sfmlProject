//
// Created by Sasha on 25.01.2025.
//

#include "gameMenu.h"

void gameMenu::showGameMenu() {
    // New window
    //sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    //sf::RenderWindow menuWindow(desktop, "Small patric", sf::Style::None);
    sf::RenderWindow menuWindow(sf::VideoMode({1920, 1080}), "Small patric",sf::Style::None);
    menuWindow.setMouseCursorVisible(false);

    while (menuWindow.isOpen()) {
        if (const std::optional<sf::Event> newEvent = menuWindow.pollEvent()) {
            if (newEvent->is<sf::Event::Closed>()) {
                menuWindow.close();
            }
        }
        menuWindow.clear();
        menuWindow.draw(newSprite);
        Start.draw(menuWindow);
        Options.draw(menuWindow);
        Quit.draw(menuWindow);
        menuWindow.display();
    }
}
