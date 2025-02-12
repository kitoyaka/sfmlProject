//
// Created by rigry on 11.02.2025.
//

#include "Field.h"


void Field::draw(sf::RenderWindow& window) {
    musicSettings(keyPressed, music, musicPlaying);

    window.draw(newSprite);

    for (int row = 0; row < HEIGHT; ++row) {
        for (int col = 0; col < WIDTH; ++col) {
            cell.setPosition(sf::Vector2f (offset.x + col * TILE_SIZE, offset.y + row * TILE_SIZE));
            window.draw(cell);
        }
    }

    for (int i = 0; i < 4; i++) {
        spriteBlueBlock.setPosition(sf::Vector2f (
                offset.x + currentShape[i].x * (TILE_SIZE + SPACING),
                offset.y + currentShape[i].y * (TILE_SIZE + SPACING)
        ));
        window.draw(spriteBlueBlock);
    }


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
        music.stop();
    }
}


void Field::generateNewFigure() {
    if(isActiveFigure) return;
    int n = rand() % 7;

    for (int i = 0; i < 4; ++i) {
        currentShape[i].x = figures[n][i] % 2 + WIDTH / 2 - 1;
        currentShape[i].y = figures[n][i] / 2;
    }
    isActiveFigure = true;
}
