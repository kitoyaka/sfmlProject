//
// Created by Sasha on 25.01.2025.
//

#include "gameMenu.h"


int gameMenu::showGameMenu(sf::RenderWindow &window) {
    musicSettings(keyPressed,music,musicPlaying);
    // Проверяем, прошло ли достаточно времени
    if (clock.getElapsedTime().asSeconds() >= delayTime) {
        // Обрабатываем нажатие стрелки вниз
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
            clock.restart(); // Перезапускаем таймер после изменения состояния
        }

        // Обрабатываем нажатие стрелки вверх
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
            clock.restart(); // Перезапускаем таймер после изменения состояния
        }
    }
    // Обработка нажатия Enter, если активна кнопка Quit
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) && Start.getActive()) {
        return 1;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) && Options.getActive()) {
        return 2;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) && Quit.getActive()) {
        return 3;
    }

    // Рисуем фоновое изображение и кнопки
    window.draw(newSprite);
    Start.draw(window);
    Options.draw(window);
    Quit.draw(window);
    return 0;
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