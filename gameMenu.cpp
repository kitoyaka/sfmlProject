//
// Created by Sasha on 25.01.2025.
//

#include "gameMenu.h"
#include <fstream>

int gameMenu::showGameMenu(sf::RenderWindow &window) {
    if (clock.getElapsedTime().asSeconds() >= delayTime) {
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


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) && Start.getActive()) {
        return 1; // Начало игры
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) && Options.getActive()) {
        return 2; // Настройки
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) && Quit.getActive()) {
        return 3; // Выход
    }


    window.draw(newSprite);
    Start.draw(window);
    Options.draw(window);
    Quit.draw(window);

    return 0;
}

void gameMenu::showSettings(sf::RenderWindow &window, sf::Music &music) {
    window.draw(newSprite);
    settingsField.draw(window);

    // Проверка файла статистики
    std::ifstream checkFile("game_data.txt");
    bool fileIsEmpty = true;
    if (checkFile.good()) {
        if (checkFile.peek() != std::ifstream::traits_type::eof()) {
            fileIsEmpty = false;
        }
    }
    checkFile.close();
    stateDeleteStat = fileIsEmpty ? "EMPTY" : "game_data.txt";

    if(windowMode == 0)
        resolution.setString("RESOLUTION: FULLSCREEN");
    else
        resolution.setString("RESOLUTION: TITLEBAR");

    if (settingClock.getElapsedTime().asSeconds() >= settingDelay) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            activeSettingIndex = (activeSettingIndex + 1) % numSettings;
            settingClock.restart();
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            activeSettingIndex = (activeSettingIndex - 1 + numSettings) % numSettings;
            settingClock.restart();
        }
    }

    // Обновление визуального состояния пунктов
    volume.setFillColor(activeSettingIndex == 0 ? sf::Color::Red : sf::Color::Yellow);
    resolution.setFillColor(activeSettingIndex == 1 ? sf::Color::Red : sf::Color::Yellow);
    difficulty.setFillColor(activeSettingIndex == 2 ? sf::Color::Red : sf::Color::Yellow);
    fallIncrease.setFillColor(activeSettingIndex == 3 ? sf::Color::Red : sf::Color::Yellow);
    saveSettings.setFillColor(activeSettingIndex == 4 ? sf::Color::Red : sf::Color::Yellow);

    if (activeSettingIndex == 1 && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) &&
        modeSwitchClock.getElapsedTime().asSeconds() >= modeSwitchDelay) {
        windowMode = (windowMode + 1) % 2;
        sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

        if (windowMode == 0) {
            window.create(desktop, "Game", sf::Style::None);
            resolution.setString("RESOLUTION: FULLSCREEN");
        } else {
            window.create(desktop, "Game", sf::Style::Default);
            window.setPosition(sf::Vector2i(0, 0));
            resolution.setString("RESOLUTION: TITLEBAR");
        }

        window.setView(window.getDefaultView());
        window.setVerticalSyncEnabled(true);
        sf::sleep(sf::milliseconds(100));

        modeSwitchClock.restart();
        }

    // Обработка громкости
    int displayedVolume = static_cast<int>(std::round(music.getVolume()));
    volume.setString("VOLUME: " + std::to_string(displayedVolume) + "%");

    if (activeSettingIndex == 0 && volumeClock.getElapsedTime().asSeconds() > volumeDelay) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Add) && music.getVolume() < 100) {
            music.setVolume(music.getVolume() + 1);
            volumeClock.restart();
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Subtract) && music.getVolume() > 0) {
            music.setVolume(music.getVolume() - 1);
            volumeClock.restart();
        }
    }

    // Обработка удаления статистики
    if (activeSettingIndex == 3 && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) &&
        settingClock.getElapsedTime().asSeconds() >= settingDelay) {
        if (stateDeleteStat != "EMPTY") {
            std::ofstream file("game_data.txt", std::ios::trunc);
            file.close();
            stateDeleteStat = "EMPTY";
            settingClock.restart();
        }
    }

    // Установка текста пунктов
    difficulty.setString("FALL INCREASE: ON");
    fallIncrease.setString("DELETE STATISTIC: " + stateDeleteStat);
    saveSettings.setString("SAVE SETTINGS");

    // Отрисовка всех пунктов
    window.draw(volume);
    window.draw(resolution);
    window.draw(difficulty);
    window.draw(fallIncrease);
    window.draw(saveSettings);
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