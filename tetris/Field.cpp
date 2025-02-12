//
// Created by rigry on 11.02.2025.
//

#include "Field.h"


void Field::draw(sf::RenderWindow& window) {
    musicSettings(keyPressed, music, musicPlaying);

    window.draw(newSprite);
    window.draw(spriteBlueBlock);
    window.draw(spriteYellowBlock);
    window.draw(spritePinkBlock);
    window.draw(spriteGreenBlock);
    window.draw(spriteRedBlock);

    for (int row = 0; row < HEIGHT; ++row) {
        for (int col = 0; col < WIDTH; ++col) {
            cell.setPosition(sf::Vector2f (offset.x + col * TILE_SIZE, offset.y + row * TILE_SIZE));
            window.draw(cell);
        }
    }


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
        music.stop();
    }
}
