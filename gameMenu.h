//
// Created by Sasha on 25.01.2025.
//

#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <SFML/Graphics.hpp>
#include "button/button.h"
#include "button/button.h"


class gameMenu {
private:
    const sf::Texture newTexture;
    sf::Sprite newSprite;
    button Start;
    button Options;
    button Quit;



public:
    gameMenu() : newTexture(("../image/menuBackground.png")),newSprite(newTexture), Start(360, 100, "", "../image/StartButtonWhite.png"),
    Options(360, 100, "", "../image/OptionsButtonWhite.png"), Quit(360, 100, "", "../image/QuitButtonWhite.png") {

        Start.setPosition(780.f, 240.f);
        Options.setPosition(780.f, 410.f);
        Quit.setPosition(780.f, 560.f);
    };
    void showGameMenu();
};



#endif //GAMEMENU_H
