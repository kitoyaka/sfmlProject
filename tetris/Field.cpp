//
// Created by rigry on 11.02.2025.
//

#include "Field.h"


void Field::draw(sf::RenderWindow& window) {
    window.draw(newSprite);
    for (int row = 0; row < HEIGHT; ++row) {
        for (int col = 0; col < WIDTH; ++col) {
            cell.setPosition(sf::Vector2f (offset.x + col * TILE_SIZE, offset.y + row * TILE_SIZE));
            window.draw(cell);
        }
    }

}
