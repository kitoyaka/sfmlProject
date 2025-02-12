//
// Created by rigry on 11.02.2025.
//

#include "Field.h"


void Field::draw(sf::RenderWindow& window) {
    musicSettings(keyPressed, music, musicPlaying);
    window.draw(gameBackgroundSprite);

    // Отрисовка сетки
    for (int row = 0; row < HEIGHT; ++row) {
        for (int col = 0; col < WIDTH; ++col) {
            cell.setPosition(sf::Vector2f(
                offset.x + col * TILE_SIZE,
                offset.y + row * TILE_SIZE));
            window.draw(cell);
        }
    }

    // Отрисовка накопленных блоков
    for (int row = 0; row < HEIGHT; ++row) {
        for (int col = 0; col < WIDTH; ++col) {
            if (grid[row][col] != 0) {
                int colorIndex = grid[row][col] - 1; // Конвертируем в индекс 0-4
                if (colorIndex >= 0 && colorIndex < 5) {
                    blockSprite[colorIndex].setPosition(sf::Vector2f(
                        offset.x + col * TILE_SIZE,
                        offset.y + row * TILE_SIZE)
                    );
                    window.draw(blockSprite[colorIndex]);
                }
            }
        }
    }

    // Отрисовка активной фигуры
    if (isActiveFigure) {
        for (int i = 0; i < 4; i++) {
            blockSprite[randomColor].setPosition(sf::Vector2f(offset.x + currentShape[i].x * TILE_SIZE,
                offset.y + currentShape[i].y * TILE_SIZE)
            );
            window.draw(blockSprite[randomColor]);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
        music.stop();
    }
}

void Field::generateNewFigure() {
    if (isActiveFigure) return;
    int n = rand() % 7;
    randomColor = rand() % 5;

    for (int i = 0; i < 4; ++i) {
        currentShape[i].x = figures[n][i] % 2 + WIDTH / 2 - 1;
        currentShape[i].y = figures[n][i] / 2;

        // Проверка на столкновение с существующими блоками
        if (grid[currentShape[i].y][currentShape[i].x] != 0) {
            // Игра завершена (можно добавить обработку)
            isActiveFigure = false;
            return;
        }
    }
    isActiveFigure = true;
}

void Field::moveFigure(float deltaTime) {
    if (!isActiveFigure) return;
    dropTimer += deltaTime;
    if (dropTimer < dropDelay) return;

    dropTimer = 0;

    // Проверяем, может ли фигура двигаться вниз
    bool canMoveDown = true;
    for (int i = 0; i < 4; ++i) {
        int newY = currentShape[i].y + 1;
        if (newY >= HEIGHT) {
            canMoveDown = false;
            break;
        }
        if (grid[newY][currentShape[i].x] != 0) {
            canMoveDown = false;
            break;
        }
    }

    if (!canMoveDown) {
        for (int i = 0; i < 4; ++i) {
            int x = currentShape[i].x;
            int y = currentShape[i].y;
            if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
                grid[y][x] = randomColor + 1;
            }
        }
        isActiveFigure = false;
        return;
    }

    for (int i = 0; i < 4; ++i) {
        currentShape[i].y += 1;
    }
}

