//
// Created by rigry on 11.02.2025.
//

#ifndef SFMLPROJECT_FIELD_H
#define SFMLPROJECT_FIELD_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <SFML/Audio.hpp>

void musicSettings(bool &isPlaying, sf::Music &music, bool &stopMusic);

class Field {
private:
    static constexpr int WIDTH = 15;
    static constexpr int HEIGHT = 15;
    static constexpr int TILE_SIZE = 72;
    static constexpr  int SPACING = 0;

    sf::RectangleShape cell;
    std::vector<std::vector<int>> grid;
    sf::Vector2f offset;

    const sf::Texture newTexture;
    sf::Sprite newSprite;

    sf::Music music;
    bool musicPlaying = true;
    bool keyPressed = false;


    sf::Texture textureBlueBlock;
    sf::Sprite spriteBlueBlock;
    sf::Texture textureYellowBlock;
    sf::Sprite spriteYellowBlock;
    sf::Texture texturePinkBlock;
    sf::Sprite spritePinkBlock;
    sf::Texture textureGreenBlock;
    sf::Sprite spriteGreenBlock;
    sf::Texture textureRedBlock;
    sf::Sprite spriteRedBlock;

    const int figures[7][4] = {
            {1, 3, 5, 7},
            {2, 4, 5, 7},
            {3, 5, 4, 6},
            {3, 5, 4, 7},
            {2, 3, 5, 7},
            {3, 5, 7, 6},
            {2, 3, 4, 5}
    };

    struct Point {int x, y;};
    Point currentShape[4];

    bool isActiveFigure = false;


public:
    Field(sf::RenderWindow& window)
            : grid(HEIGHT, std::vector<int>(WIDTH, 0)), cell(sf::Vector2f(TILE_SIZE - 2, TILE_SIZE - 2)),
            newTexture(("../image/Tetris_backgroundv2.png")), newSprite(newTexture),
            music("../music/bgm_2.ogg"),
            textureBlueBlock(("../image/blue_squarev2.png")), spriteBlueBlock(textureBlueBlock),
            textureYellowBlock(("../image/yellow_squarev2.png")), spriteYellowBlock(textureYellowBlock),
            texturePinkBlock(("../image/pink_squarev2.png")), spritePinkBlock(texturePinkBlock),
            textureGreenBlock(("../image/green_squarev2.png")), spriteGreenBlock(textureGreenBlock),
            textureRedBlock(("../image/red_squarev2.png")), spriteRedBlock(textureRedBlock)
    {
        music.setVolume(30);
        spriteBlueBlock.setPosition(sf::Vector2f(150, 150));
        spriteYellowBlock.setPosition(sf::Vector2f(250, 250));
        spritePinkBlock.setPosition(sf::Vector2f(350, 350));
        spriteGreenBlock.setPosition(sf::Vector2f(450, 450));
        spriteRedBlock.setPosition(sf::Vector2f(550, 550));

        cell.setFillColor(sf::Color(0, 0, 0,50));



        float fieldWidth = WIDTH * TILE_SIZE;
        float fieldHeight = HEIGHT * TILE_SIZE;

        offset.x = (window.getSize().x - fieldWidth) / 2;
        offset.y = 0;
    }


    void draw(sf::RenderWindow& window);
    void generateNewFigure();
};


#endif //SFMLPROJECT_FIELD_H
