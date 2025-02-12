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

    sf::RectangleShape cell;
    std::vector<std::vector<int>> grid;
    sf::Vector2f offset;

    const sf::Texture newTexture;
    sf::Sprite newSprite;

    sf::Music music;
    bool musicPlaying = true;
    bool keyPressed = false;


public:
    Field(sf::RenderWindow& window)
            : grid(HEIGHT, std::vector<int>(WIDTH, 0)), cell(sf::Vector2f(TILE_SIZE - 2, TILE_SIZE - 2)),
            newTexture(("../image/Tetris_backgroundv2.png")), newSprite(newTexture),
            music("../music/bgm_2.ogg")
    {
        music.setVolume(30);

        cell.setFillColor(sf::Color::White);


        float fieldWidth = WIDTH * TILE_SIZE;
        float fieldHeight = HEIGHT * TILE_SIZE;

        offset.x = (window.getSize().x - fieldWidth) / 2;
        offset.y = 0;
    }


    void draw(sf::RenderWindow& window);
};


#endif //SFMLPROJECT_FIELD_H
