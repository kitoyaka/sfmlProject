//
// Created by Sasha on 25.01.2025.
//

#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <SFML/Graphics.hpp>
#include "button/button.h"
#include <SFML/Audio.hpp>
#include <vector>

void musicSettings(bool &isPlaying, sf::Music &music, bool &stopMusic);


class gameMenu {
private:
    const sf::Texture newTexture;
    sf::Sprite newSprite;
    button Start;
    button Options;
    button Quit;
    bool active;
    sf::SoundBuffer buffer;
    sf::Sound buttonSound;
    sf::Music music;
    bool musicPlaying = true;
    bool keyPressed = false;

    sf::Clock clock;
    const float delayTime = 0.2f;

    button settingsField;
public:
    gameMenu(sf::RenderWindow &window) : newTexture(("../image/menuBackground_v2.png")),
    newSprite(newTexture), Start(true,360, 100, "", "../image/StartButtonRed.png"),
    Options(false,360, 100, "", "../image/OptionsButtonWhite.png"),
    Quit(false,360, 100, "", "../image/QuitButtonWhite.png"),
    buffer("../music/Blip_select 6.wav"),
    buttonSound(buffer),
    music("../music/bgm_17.ogg"),
    settingsField(false,810, 800, "", "../image/SettingsField.png")

    {
        music.setVolume(30);
        buttonSound.setVolume(20);
        Start.setPosition(780.f, 240.f);
        Options.setPosition(780.f, 410.f);
        Quit.setPosition(780.f, 560.f);


        settingsField.setPosition(555.f, 150);
    };


    int showGameMenu(sf::RenderWindow &window);
    void updateButtonStates();
    void showSettings(sf::RenderWindow &window);

};



#endif //GAMEMENU_H
