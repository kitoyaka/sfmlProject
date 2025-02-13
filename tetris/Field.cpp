//
// Created by rigry on 11.02.2025.
//

#include "Field.h"

void Field::draw(sf::RenderWindow& window) {
    if (gameOverMusicPlaying == false)
        musicSettings(keyPressed, music, musicPlaying);
    else if (gameOverMusicPlaying == true)
        musicSettings(keyPressed, musicGameOver, musicPlaying);
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

    for (int row = 0; row < HEIGHT; ++row) {
        for (int col = 0; col < WIDTH; ++col) {
            if (grid[row][col] != 0) {
                int colorIndex = grid[row][col] - 1;
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
            blockSprite[randomColor].setPosition(sf::Vector2f(
                offset.x + currentShape[i].x * TILE_SIZE,
                offset.y + currentShape[i].y * TILE_SIZE
            ));
            window.draw(blockSprite[randomColor]);
        }
    }

    if (isGameOver == true) {
        if (gameOverMusicPlaying == false) {
            music.stop();
            gameOverMusicPlaying = true;
        }
        window.draw(gameOverRectangle);
        window.draw(gameOverSprite);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
        music.stop();
        musicGameOver.stop();
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
            isGameOver = true;
            return;
        }
    }
    isActiveFigure = true;
}


void Field::handleInput() {
    if (!isActiveFigure) return;
    // Обработка ускоренного падения
    isFastFalling = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        bool canMove = true;
        for (int i = 0; i < 4; ++i) {
            int newX = currentShape[i].x - 1;
            if (newX < 0 || grid[currentShape[i].y][newX] != 0) {
                canMove = false;
                break;
            }
        }
        if (canMove) {
            for (int i = 0; i < 4; ++i)
                currentShape[i].x -= 1;
        }
    }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        bool canMove = true;
        for (int i = 0; i < 4; ++i) {
            int newX = currentShape[i].x + 1;
            if (newX >= WIDTH || grid[currentShape[i].y][newX] != 0) {
                canMove = false;
                break;
            }
        }
        if (canMove) {
            for (int i = 0; i < 4; ++i)
                currentShape[i].x += 1;
        }
    }
}

void Field::moveFigure(float deltaTime) {
    if (!isActiveFigure) return;

    // Выбираем задержку в зависимости от состояния клавиши
    float currentDropDelay = isFastFalling ? fastDropDelay : baseDropDelay;

    dropTimer += deltaTime;

    if (dropTimer >= currentDropDelay) {
        dropTimer = 0;

        bool canMoveDown = true;
        for (int i = 0; i < 4; ++i) {
            int newY = currentShape[i].y + 1;
            if (newY >= HEIGHT || grid[newY][currentShape[i].x] != 0) {
                canMoveDown = false;
                break;
            }
        }

        if (!canMoveDown) {
            // Фиксация фигуры
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

        // Перемещение вниз
        for (int i = 0; i < 4; ++i) {
            currentShape[i].y += 1;
        }
    }

    // Обработка бокового движения с задержкой
    moveSideTimer += deltaTime;
    if (moveSideTimer >= moveSideDelay) {
        handleInput();
        moveSideTimer = 0;
    }
}


