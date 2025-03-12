//
// Created by Sasha on 25.01.2025.
//

#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <SFML/Graphics.hpp>
#include "button/button.h"
#include <SFML/Audio.hpp>
#include<cmath>

void musicSettings(sf::Music &music);


class gameMenu {
private:
    const sf::Texture newTexture;
    sf::Sprite newSprite;
    button Start;
    button Options;
    button Quit;
    sf::SoundBuffer buffer;
    sf::Sound buttonSound;
    bool musicPlaying = true;
    bool keyPressed = false;
    sf::Clock clock;
    const float delayTime = 0.2f;
    button settingsField;

    sf::Font font;
    sf::Text volume;
    sf::Text resolution;
    sf::Text difficulty;
    sf::Text fallIncrease;
    sf::Text saveSettings;

    bool changeVolume = true;
    sf::Clock volumeClock;
    const float volumeDelay = 0.1f;


    int activeSettingIndex = 0;
    sf::Clock settingClock;
    const float settingDelay = 0.2f;
    const int numSettings = 5;

    bool enterPressed = false;
    std::string stateDeleteStat;

    int windowMode = 0;

    sf::Clock modeSwitchClock;
    const float modeSwitchDelay = 0.3f; // задержка в секундах


public:
    gameMenu(sf::RenderWindow &window) : newTexture(("../image/background.png")),
    newSprite(newTexture), Start(true,420, 142, "", "../image/StartButtonRed.png"),
    Options(false,567, 139, "", "../image/OptionsButtonWhite.png"),
    Quit(false,296, 147, "", "../image/QuitButtonWhite.png"),
    buffer("../music/Blip_select 6.wav"),
    buttonSound(buffer),
    settingsField(false,810, 800, "", "../image/SettingsField.png"),
    font(("../font/hermanomayor.ttf")),
    volume(font),
    resolution(font),
    difficulty(font),
    fallIncrease(font),
    saveSettings(font)


    {
        buttonSound.setVolume(20);
        Start.setPosition(744.f, 144.f);
        Options.setPosition(675.f, 432.f);
        Quit.setPosition(804.f, 720.f);

        settingsField.setPosition(555, 142);

        volume.setCharacterSize(90);
        volume.setStyle(sf::Text::Bold);
        volume.setOutlineThickness(1.0f);
        volume.setPosition(sf::Vector2f(612, 214));

        resolution.setCharacterSize(90);
        resolution.setStyle(sf::Text::Bold);
        resolution.setOutlineThickness(1.0f);
        resolution.setPosition(sf::Vector2f(612, 360));

        difficulty.setCharacterSize(90);
        difficulty.setStyle(sf::Text::Bold);
        difficulty.setFillColor(sf::Color::Green);
        difficulty.setOutlineThickness(1.0f);
        difficulty.setPosition(sf::Vector2f(612, 504));

        fallIncrease.setCharacterSize(90);
        fallIncrease.setStyle(sf::Text::Bold);
        fallIncrease.setOutlineThickness(1.0f);
        fallIncrease.setPosition(sf::Vector2f(612, 648));

        saveSettings.setCharacterSize(90);
        saveSettings.setFillColor(sf::Color::Blue);
        saveSettings.setStyle(sf::Text::Bold);
        saveSettings.setOutlineThickness(1.0f);
        saveSettings.setPosition(sf::Vector2f(688, 792));

    };


    int showGameMenu(sf::RenderWindow &window);
    void updateButtonStates();
    void showSettings(sf::RenderWindow &window, sf::Music &music);

};



#endif //GAMEMENU_H
