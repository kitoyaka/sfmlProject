//
// Created by Sasha on 25.01.2025.
//

#include "gameMenu.h"

void gameMenu::showGameMenu() {
    // New window
    sf::RenderWindow menuWindow(sf::VideoMode({1920, 1080}), "Small patric",sf::Style::None);
    menuWindow.setMouseCursorVisible(false);
    sf::Clock clock;
    const float delayTime = 0.2f;

    while (menuWindow.isOpen()) {
        if (const std::optional<sf::Event> newEvent = menuWindow.pollEvent()) {
            if (newEvent->is<sf::Event::Closed>()) {
                menuWindow.close();
            }
        }
        if(clock.getElapsedTime().asSeconds() >= delayTime) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
                if (Start.getActive()) {
                    Start.setActive(false);
                    Options.setActive(true);
                } else if (Options.getActive()) {
                    Options.setActive(false);
                    Quit.setActive(true);
                } else if (Quit.getActive()) {
                    Quit.setActive(false);
                    Start.setActive(true);
                }
                buttonSound.play();
                updateButtonStates();
                clock.restart();
            }
        }
        if(clock.getElapsedTime().asSeconds() >= delayTime) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
                if (Start.getActive()) {
                    Start.setActive(false);
                    Quit.setActive(true);
                } else if (Options.getActive()) {
                    Options.setActive(false);
                    Start.setActive(true);
                } else if (Quit.getActive()) {
                    Quit.setActive(false);
                    Options.setActive(true);
                }
                buttonSound.play();
                updateButtonStates();
                clock.restart();
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

void gameMenu::updateButtonStates() {

    if(Start.checkActive())
    {
        Start.setActive(true, "../image/StartButtonRed.png", "../image/StartButtonWhite.png");
        Options.setActive(false, "../image/OptionsButtonRed.png", "../image/OptionsButtonWhite.png");
        Quit.setActive(false, "../image/QuitButtonRed.png", "../image/QuitButtonWhite.png");
    }
    else if(Options.checkActive())
    {
        Start.setActive(false, "../image/StartButtonRed.png", "../image/StartButtonWhite.png");
        Options.setActive(true, "../image/OptionsButtonRed.png", "../image/OptionsButtonWhite.png");
        Quit.setActive(false, "../image/QuitButtonRed.png", "../image/QuitButtonWhite.png");
    }
    else if(Quit.checkActive())
    {
        Start.setActive(false, "../image/StartButtonRed.png", "../image/StartButtonWhite.png");
        Options.setActive(false, "../image/OptionsButtonRed.png", "../image/OptionsButtonWhite.png");
        Quit.setActive(true, "../image/QuitButtonRed.png", "../image/QuitButtonWhite.png");
    }


}