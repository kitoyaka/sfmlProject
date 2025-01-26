//
// Created by Sasha on 25.01.2025.
//

#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <SFML/Graphics.hpp>
#include "button/button.h"
#include <vector>


class gameMenu {
private:
    const sf::Texture newTexture;
    sf::Sprite newSprite;
    button Start;
    button Options;
    button Quit;
    bool active;


public:
    gameMenu() : newTexture(("../image/menuBackground.png")),newSprite(newTexture), Start(true,360, 100, "", "../image/StartButtonRed.png"),
    Options(false,360, 100, "", "../image/OptionsButtonWhite.png"), Quit(false,360, 100, "", "../image/QuitButtonWhite.png") {

        Start.setPosition(780.f, 240.f);
        Options.setPosition(780.f, 410.f);
        Quit.setPosition(780.f, 560.f);
    };
    void showGameMenu();

    void updateButtonStates();

};



#endif //GAMEMENU_H
